#include"MainFrame.h"
#include"FoodManipulator.h"
#include"Food.h"
#include"ListController.h"
#include<wx/panel.h>
#include<wx/listctrl.h>
#include<wx/stattext.h>
#include<wx/statbox.h>
#include<wx/image.h>
#include<wx/button.h>
#include<wx/textctrl.h>

MainFrame::MainFrame()
	: wxFrame(nullptr, wxID_ANY, wxT("Foodynoms alpha 1"))
{
	wxInitAllImageHandlers();
	Center();

	wxSize clientSize(640,480);
	SetClientSize(clientSize);

	mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), clientSize);

	wxButton* buttonNew = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(5,5), wxSize(24,24) );
	buttonNew->SetBitmap(wxBitmap("Images/Add.png", wxBITMAP_TYPE_PNG));
	wxButton* buttonMod = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(32,5), wxSize(24,24));
	buttonMod->SetBitmap(wxBitmap("Images/Modify.png", wxBITMAP_TYPE_PNG));
	wxButton* buttonDel = new wxButton(mainPanel, wxID_ANY, wxEmptyString, wxPoint(59,5), wxSize(24,24));
	buttonDel->SetBitmap(wxBitmap("Images/Remove.png", wxBITMAP_TYPE_PNG));

	Connect(buttonNew->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonNew));
	Connect(buttonMod->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonModify));
	Connect(buttonDel->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(MainFrame::OnButtonRemove));

	wxTextCtrl *search = new wxTextCtrl(mainPanel, wxID_ANY, "Filter...", wxPoint(5,32), wxSize(150, 20));

	listFood = new ListController(mainPanel, wxPoint(5,55), wxSize(150,480-55));

	Connect(listFood->GetListID(), wxEVT_COMMAND_LIST_ITEM_SELECTED, wxListEventHandler(MainFrame::OnListSelection));
	
	int textCtrlStyle = wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL;
	wxPoint textCtrlPosition(5,15);

	wxStaticBox *boxDescription = new wxStaticBox(mainPanel, wxID_ANY, wxString("Description"), wxPoint(160, 5), wxSize(480, 100));
	description = new wxTextCtrl(boxDescription, wxID_ANY, wxEmptyString, textCtrlPosition, wxSize(470,80), wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL);
	description->Disable();

	wxStaticBox *boxRecipe = new wxStaticBox(mainPanel, wxID_ANY, wxString("Ingredients"), wxPoint(160, 110), wxSize(480, 150));
	ingredients = new wxTextCtrl(boxRecipe, wxID_ANY, wxEmptyString, textCtrlPosition, wxSize(470,130), textCtrlStyle);
	ingredients->Disable();

	wxStaticBox *boxStats = new wxStaticBox(mainPanel, wxID_ANY, wxString("Statistics"), wxPoint(160, 270), wxSize(480, 205));
	statistics = new wxTextCtrl(boxStats, wxID_ANY, wxEmptyString, textCtrlPosition, wxSize(150,250), wxTE_BESTWRAP|wxTE_MULTILINE|wxTE_NO_VSCROLL);
	statistics->Disable();

	Connect(wxEVT_CLOSE_WINDOW, wxCloseEventHandler(MainFrame::OnClose));

	Show();


	foodData.LoadDataFromFile("FoodData.xml");
	auto nameList = foodData.GetFoodNameList();
	for( auto name : nameList )
		listFood->AddEntry(name);
}

MainFrame::~MainFrame()
{
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

	description->SetValue( selectedFood->description );
	ingredients->SetValue( selectedFood->ingredients );
}

void MainFrame::OnButtonNew( wxCommandEvent &evt )
{
	FoodManipulator foodManipulator(this);

	if( foodManipulator.ShowModal() == FoodManipulator::ID_OK )
	{
		Food newFood;

		//DataSide
		foodManipulator.GetFood(newFood);
		foodData.CreateFood(newFood);

		//UI Side
		listFood->AddEntry(newFood.name);
	}
}

void MainFrame::OnButtonModify( wxCommandEvent &evt )
{
	wxString foodName;
	listFood->GetSelected(foodName);

	const Food *foodCurrent = foodData.GetFoodByName(foodName);

	FoodManipulator foodManipulator(this);
	foodManipulator.SetFood(*foodCurrent);

	if( foodManipulator.ShowModal() == wxID_OK )
	{
		//replace food in data
		//replace food in UI
		//deselect 
		//and reselect new data

		//investigate if selecting an already selected index triggers event
	}
}

void MainFrame::OnButtonRemove( wxCommandEvent &evt )
{
	//Message Dialog

	wxString foodName;
	listFood->GetSelected(foodName);
	listFood->RemoveEntry(foodName);

	//Remove Data
	//Clear UI
}
