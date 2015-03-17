#pragma once

#include<wx/string.h>

class Food
{
public:
	Food() {}
	Food(const Food& food):name(food.name), description(food.description), ingredients(food.ingredients), timesEaten(food.timesEaten), datesEaten(food.datesEaten) {}
	~Food() {}

//private:
	wxString name;
	wxString description;
	wxString ingredients;
	wxString timesEaten;
	wxString datesEaten;
};