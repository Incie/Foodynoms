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

	wxStaticBox *boxDescription = new wxStaticBox(mainPanel, wxID_ANY, wxString("Description"), wxPoint(160, 5), wxSize(480, 100));
	wxStaticBox *boxRecipe = new wxStaticBox(mainPanel, wxID_ANY, wxString("Ingredients"), wxPoint(160, 110), wxSize(480, 150));
	wxStaticBox *boxStats = new wxStaticBox(mainPanel, wxID_ANY, wxString("Statistics"), wxPoint(160, 270), wxSize(480, 205));

	Show();
}

MainFrame::~MainFrame()
{
}

void MainFrame::OnButtonNew( wxCommandEvent &evt )
{
	FoodManipulator foodManipulator(this);

	if( foodManipulator.ShowModal() == FoodManipulator::ID_OK )
	{
		Food newFood;

		foodManipulator.GetFood(newFood);
		foodData.CreateFood(newFood);

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
}
