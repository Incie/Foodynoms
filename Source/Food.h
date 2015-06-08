#pragma once

#include<wx/string.h>
#include<wx/tokenzr.h>

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
		if( datesEaten.Cmp(food.datesEaten) != 0 ) datesEaten = food.datesEaten;
	}

	void RemoveDateEaten( const wxString &date )
	{
		wxString newDatesEaten;

		wxStringTokenizer dateTokens(datesEaten, wxT(";"));
		while( dateTokens.HasMoreTokens() )
		{
			const wxString token = dateTokens.GetNextToken();

			if( token.Cmp(date) == 0 )
				continue;

			newDatesEaten += wxT(";");
			newDatesEaten += date;
		}

		if( newDatesEaten.Cmp(datesEaten) != 0 )
			datesEaten = newDatesEaten;
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