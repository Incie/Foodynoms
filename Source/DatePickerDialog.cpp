#include"DatePickerDialog.h"
#include<wx/panel.h>
#include<wx/button.h>

DatePickerDialog::DatePickerDialog(wxWindow*parent)
	:wxDialog(parent, wxID_ANY, "Choose a date")
{
	CenterOnParent();
	wxSize clientSize(150,75);
	SetClientSize(clientSize);

	wxPanel *mainPanel = new wxPanel(this, wxID_ANY, wxPoint(0,0), clientSize);
	datePicker = new wxDatePickerCtrl(mainPanel, wxID_ANY, wxDefaultDateTime, wxPoint(5,5), wxSize(140, 25), wxDP_DROPDOWN);

	wxSize buttonSize(40,20);
	wxButton *btnOk = new wxButton(mainPanel, wxID_ANY, "Ok", wxPoint(5,50), buttonSize);
	wxButton *btnCancel = new wxButton(mainPanel, wxID_ANY, "Cancel", wxPoint(5 + buttonSize.x,50),buttonSize);

	Connect(btnOk->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DatePickerDialog::OnOk));
	Connect(btnCancel->GetId(), wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(DatePickerDialog::OnCancel));
}

DatePickerDialog::~DatePickerDialog()
{
}

wxDateTime DatePickerDialog::GetSelectedDate()
{
	return datePicker->GetValue();
}

void DatePickerDialog::OnOk( wxCommandEvent &evt )
{
	EndModal(wxOK);
}

void DatePickerDialog::OnCancel( wxCommandEvent &evt )
{
	EndModal(wxCANCEL);
}

