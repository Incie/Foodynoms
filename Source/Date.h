#pragma once

#include<wx/string.h>

class Date
{
public:
	static wxString GetCurrentDate();
	static bool ChooseDate(wxString &selectedDate);
private:
	Date(){}
	~Date(){}
};