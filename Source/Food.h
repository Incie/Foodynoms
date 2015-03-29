#pragma once

#include<wx/string.h>

class Food
{
public:
	Food() {}
	Food(const Food& food):name(food.name), description(food.description), ingredients(food.ingredients), timesEaten(food.timesEaten), datesEaten(food.datesEaten) {}
	~Food() {}

	//Todo
	//int SetField( const wxString &field, const wxString &value);
	//int GetField( const wxString &field, const wxString &value);
	//wxString* GetFieldPointer(const wxString &field);

//private:
	wxString name;
	wxString description;
	wxString ingredients;
	wxString timesEaten;
	wxString datesEaten;
};