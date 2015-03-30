#pragma once


#include<vector>

class Food;
class wxString;

class FoodData
{
public:
	FoodData();
	~FoodData();

	void ClearData();

	bool LoadDataFromFile(const wxString &file);
	bool SaveDataToFile( const wxString &file);

	bool CreateFood(const Food& food);
	bool UpdateFood(const Food& oldFood, Food& newFood);
	bool DeleteFoodByName( const wxString &name );

	const Food* GetFoodByName( const wxString &name );
	std::vector<wxString> GetFoodNameList();

private:
	std::vector<Food*> data;
};