#include"MainFrame.h"
#include"FoodManipulator.h"
#include"Food.h"
#include"ListController.h"
#include"Date.h"

#include<wx/panel.h>
#include<wx/listctrl.h>
#include<wx/stattext.h>
#include<wx/statbox.h>
#include<wx/image.h>
#include<wx/button.h>
#include<wx/textctrl.h>
#include<wx/msgdlg.h>

MainFrame::MainFrame()
	: wxFrame(nullptr, wxID_ANY, wxT("Foodynoms 0.1.1"))
{
	wxInitAllImageHandlers();
	Center();

	wxSize clientSize(640,500);
	SetClientSize(clientSize);
	SetMaxClientSize(clientSize);
	SetMinClientSize(clientSize);

	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), clientSize);

	wxButton* buttonNew = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(5,5), wxSize(24,24) );
	buttonNew->SetBitmap(wxBitmap("Images/Add.png", wxBITMAP_TYPE_PNG));
	wxButton* buttonMod = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(32,5), wxSize(24,24));
	buttonMod->SetBitmap(wxBitmap("Images/Modify.png", wxBITMAP_TYPE_PNG));
	wxButton* buttonDel = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(59,5), wxSize(24,24));
	buttonDel->SetBitmap(wxBitmap("Images/Remove.png", wxBITMAP_TYPE_PNG));
	wxButton* buttonNom = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(89,5), wxSize(24,24));
	buttonNom->SetBitmap(wxBitmap("Images/Nom.png", wxBITMAP_TYPE_PNG));
	wxButton* buttonNomWhen = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(89+27,5), wxSize(24,24));
	buttonNomWhen->SetBitmap(wxBitmap("Images/NomWhen.png", wxBITMAP_TYPE_PNG));

	Connect(buttonNew->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonNew));
	Connect(buttonMod->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonModify));
	Connect(buttonDel->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonRemove));
	Connect(buttonNom->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonNom));
	Connect(buttonNomWhen->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonNomWhen));

	wxTextCtrl *search = new wxTextCtrl(mainPanel, wxID_ANY, "Filter...", wxPoint(5,32), wxSize(150, 20));

	listFood = new ListController(mainPanel, wxPoint(5,55), wxSize(150,480-55));
	listFood->SetColumnName("Fud");

	Connect(listFood->GetListID(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(MainFrame::OnListSelection));
	
	statFoodHeader = new wxStaticText(mainPanel, wxID_ANY, "<No Selection>", wxPoint(160, 5));
	wxFont font = statFoodHeader->GetFont();
	font.SetPointSize(12);
	statFoodHeader->SetFont(font);


	int textCtrlStyle = wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL;
	wxPoint textCtrlPosition(5,15);

	wxStaticBox *boxDescription = new wxStaticBox(mainPanel, wxID_ANY, wxString("Description"), wxPoint(160, 25), wxSize(480, 100));
	description = new wxTextCtrl(boxDescription, wxID_ANY, wxEmptyString, textCtrlPosition, wxSize(470,80), textCtrlStyle);
	description->Disable();

	wxStaticBox *boxRecipe = new wxStaticBox(mainPanel, wxID_ANY, wxString("Ingredients"), wxPoint(160, 130), wxSize(480, 150));
	ingredients = new wxTextCtrl(boxRecipe, wxID_ANY, wxEmptyString, textCtrlPosition, wxSize(470,130), textCtrlStyle);
	ingredients->Disable();

	wxStaticBox *boxStats = new wxStaticBox(mainPanel, wxID_ANY, wxString("Statistics"), wxPoint(160, 290), wxSize(480, 205));
	statistics = new wxTextCtrl(boxStats, wxID_ANY, wxEmptyString, textCtrlPosition, wxSize(150,185), textCtrlStyle);
	statistics->Disable();

	listDates = new ListController(boxStats, wxPoint(160, 15), wxSize(150, 185) );
	listDates->SetColumnName("Dates Eaten");

	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::OnClose));

	Show();


	foodData.LoadDataFromFile("FoodData.xml");
	//auto nameList = foodData.GetFoodNameList();
	auto nameList = foodData.GetSortedFoodNameList();
	for( auto name : nameList )
		listFood->AddEntry(name);
}

MainFrame::~MainFrame()
{
}

void MainFrame::UpdateFoodUI( const wxString &foodName )
{
	const Food *food = foodData.GetFoodByName(foodName);

	if( food )
		UpdateFoodUI(*food);
}

void MainFrame::UpdateFoodUI( const Food &food )
{
	statFoodHeader->SetLabel(food.name);
	listDates->ParseList( food.datesEaten );

	description->SetValue( food.description );
	ingredients->SetValue( food.ingredients );
}


void MainFrame::OnButtonNom( wxCommandEvent &evt )
{
	wxString selectedName;
	listFood->GetSelected(selectedName);
	
	wxString date = Date::GetCurrentDate();
	foodData.AddDateToFood(selectedName, date);

	UpdateFoodUI(selectedName);
}

void MainFrame::OnButtonNomWhen( wxCommandEvent &evt )
{
	wxString selectedDate;
	if( Date::ChooseDate(selectedDate) )
	{
		wxString selectedName;
		listFood->GetSelected(selectedName);
		foodData.AddDateToFood(selectedName, selectedDate);

		UpdateFoodUI(selectedName);
	}
}

void MainFrame::OnClose( wxCloseEvent &evt )
{
	foodData.SaveDataToFile("FoodData.xml");
	evt.Skip();
}

void MainFrame::OnListSelection( wxListEvent &evt )
{
	auto item = evt.GetItem();
	auto itemName = item.GetText();

	const Food *selectedFood = foodData.GetFoodByName( itemName );

	if( !selectedFood )
	{
		wxMessageBox("Could not find: " + itemName + "in FoodData");
		return;
	}

	UpdateFoodUI(*selectedFood);
}

void MainFrame::OnButtonNew( wxCommandEvent &evt )
{
	FoodManipulator foodManipulator(this, FoodManipulator::ID_OKPLUS_BUTTON);
	int retCode = -1;

	//FoodManipulator can return Ok, Ok+ and Cancel
	//Ok+ means re-run the dialog.
	do {
		foodManipulator.SetFood(emptyFood); //clear the dialog before opening the dialog. [Also clears the dlg for ok+]
		retCode = foodManipulator.ShowModal();

		if( retCode == FoodManipulator::ID_CANCEL )
			break;

		Food newFood;

		//DataSide
		foodManipulator.GetFood(newFood);
		foodData.CreateFood(newFood);

		//UI Side
		listFood->AddEntry(newFood.name);
	} while(retCode == FoodManipulator::ID_OK_AND_MORE);
}

void MainFrame::OnButtonModify( wxCommandEvent &evt )
{
	wxString foodName;
	listFood->GetSelected(foodName);

	const Food *foodCurrentPtr = foodData.GetFoodByName(foodName);

	if( !foodCurrentPtr )
	{
		wxMessageBox("Could not find " + foodName );
		return;
	}

	const Food foodCurrent = *foodCurrentPtr;

	FoodManipulator foodManipulator(this);
	foodManipulator.SetFood(foodCurrent);

	if( foodManipulator.ShowModal() == FoodManipulator::ID_OK )
	{
		Food foodNew;
		foodManipulator.GetFood(foodNew);
		foodData.UpdateFood(foodCurrent, foodNew);

		//replace food in UI
		if( foodNew.name.Cmp(foodCurrent.name) != 0 )
			listFood->UpdateEntry(foodCurrent.name, foodNew.name);

		UpdateFoodUI(foodNew);
	}
}

void MainFrame::OnButtonRemove( wxCommandEvent &evt )
{
	//Message Dialog -> Are you sure?

	wxString foodName;
	listFood->GetSelected(foodName);
	listFood->RemoveEntry(foodName);

	UpdateFoodUI( emptyFood );

	//Remove Data
	foodData.DeleteFoodByName(foodName);
}
