#include"Date.h"
#include<wx/datetime.h>
#include"DatePickerDialog.h"

wxString Date::GetCurrentDate()
{
	return wxDateTime::Today().FormatISODate();
}

bool Date::ChooseDate(wxString &selectedDate)
{
	DatePickerDialog datePicker(0);

	if( datePicker.ShowModal() == wxOK )
	{
		selectedDate =  datePicker.GetSelectedDate().FormatISODate();
		return true;
	}
	
	return false;
}