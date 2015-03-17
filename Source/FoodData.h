#pragma once


#include<vector>

class Food;
class wxString;

class FoodData
{
public:
	FoodData();
	~FoodData();

	bool CreateFood(const Food& food);
	bool DeleteFoodByName( const wxString &name );

	const Food* GetFoodByName( const wxString &name );
private:
	std::vector<Food*> data;
};