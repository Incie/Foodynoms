#pragma once

#include<wx/string.h>

class Food
{
public:
	Food() {}
	Food(const Food& food):name(food.name), description(food.description), ingredients(food.ingredients), timesEaten(food.timesEaten), datesEaten(food.datesEaten) {}
	~Food() {}

	void UpdateChanged(const Food& food)
	{
		if( name.Cmp(food.name) != 0 ) name = food.name;
		if( description.Cmp(food.description) != 0 ) description = food.description;
		if( ingredients.Cmp(food.ingredients) != 0 ) ingredients = food.ingredients;
	}

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