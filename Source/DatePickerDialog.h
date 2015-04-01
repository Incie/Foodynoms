#pragma once

#include<wx/dialog.h>
#include<wx/datectrl.h>

class DatePickerDialog : public wxDialog
{
public:
	DatePickerDialog(wxWindow*parent);
	~DatePickerDialog();

	wxDateTime GetSelectedDate();

private:
	void OnOk( wxCommandEvent &evt );
	void OnCancel( wxCommandEvent &evt );

	wxDatePickerCtrl *datePicker;
};