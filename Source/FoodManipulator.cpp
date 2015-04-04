#include"FoodManipulator.h"
#include"Food.h"

#include<wx/textctrl.h>
#include<wx/panel.h>
#include<wx/stattext.h>
#include<wx/button.h>

FoodManipulator::FoodManipulator(wxWindow *parent, bool AddOkPlusButton)
	: wxDialog(parent, wxID_ANY, "Food Manipulator")
{
	CenterOnParent();

	wxSize clientSize(480, 240);
	SetClientSize(clientSize);
	SetMaxClientSize(clientSize);
	SetMinClientSize(clientSize);

	wxPanel *panel = new wxPanel(this, wxID_ANY, wxPoint(0,0), wxSize(clientSize));
	
	wxPoint currentPosition(5,5);

	tcName = CreateInputGroup(panel, "Name", currentPosition);
	tcDescription = CreateInputGroup(panel, "Description", currentPosition, 3);
	tcIngredients = CreateInputGroup(panel, "Ingredients", currentPosition, 3);

	//move position to bottom right corner
	currentPosition.x = clientSize.x - 3*55;
	currentPosition.y = clientSize.y - 25;

	wxSize buttonSize = wxSize(50, 20);

	wxButton *buttonOKPlus = new wxButton(panel, wxID_OK, "Ok+", currentPosition, buttonSize);
	currentPosition.x += 55;

	wxButton *buttonOK = new wxButton(panel, wxID_ANY, "Ok", currentPosition, buttonSize);
	currentPosition.x += 55;

	wxButton *buttonCancel = new wxButton(panel, wxID_ANY, "Cancel", currentPosition, buttonSize);

	Connect(buttonOKPlus->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FoodManipulator::OnButtonOKPlus));
	Connect(buttonOK->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FoodManipulator::OnButtonOK));
	Connect(buttonCancel->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(FoodManipulator::OnButtonCancel));

	if( !AddOkPlusButton )
		buttonOKPlus->Show(false);
}

FoodManipulator::~FoodManipulator()
{
}

wxTextCtrl* FoodManipulator::CreateInputGroup(wxWindow* parent, const wxString& name, wxPoint& position, unsigned int nLines)
{
	new wxStaticText(parent, wxID_ANY, name, position); 
	position.y += 20;

	int boxHeight = 18 * nLines;
	wxTextCtrl* tcCtrl = new wxTextCtrl(parent, wxID_ANY, wxEmptyString, position, wxSize(470, boxHeight));
	position.y += boxHeight + 5;

	return tcCtrl;
}

void FoodManipulator::SetFood( const Food &food )
{
	wxASSERT(tcName && tcDescription && tcIngredients);

	tcName->SetValue(food.name);
	tcDescription->SetValue(food.description);
	tcIngredients->SetValue(food.ingredients);
}

void FoodManipulator::GetFood( Food &food )
{
	food.name = tcName->GetValue();
	food.description = tcDescription->GetValue();
	food.ingredients = tcIngredients->GetValue();
}

void FoodManipulator::ClearFields()
{
	tcName->SetValue("");
	tcDescription->SetValue("");
	tcIngredients->SetValue("");
}

void FoodManipulator::OnButtonOK(wxCommandEvent &evt)
{
	EndModal(FoodManipulator::ID_OK);
}

void FoodManipulator::OnButtonOKPlus(wxCommandEvent &evt)
{
	EndModal(FoodManipulator::ID_OK_AND_MORE);
}

void FoodManipulator::OnButtonCancel(wxCommandEvent &evt)
{
	EndModal(FoodManipulator::ID_CANCEL);
}
