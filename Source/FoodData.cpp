#include"FoodData.h"
#include"Food.h"
#include"XMLFoodHandler.h"

FoodData::FoodData()
{
	data.reserve(256);
}

FoodData::~FoodData()
{
	ClearData();
}

void FoodData::ClearData()
{
	for( Food* food : data )
		delete food;

	data.clear();
}

std::vector<wxString> FoodData::GetFoodNameList()
{
	std::vector<wxString> foodNames;

	for( auto food : data )
		foodNames.push_back(food->name);

	return foodNames;
}

bool FoodData::LoadDataFromFile(const wxString &file)
{
	ClearData();

	XMLFoodHandler xmlFood;
	xmlFood.LoadDocument(file, data);

	return true;
}

bool FoodData::SaveDataToFile( const wxString &file)
{
	XMLFoodHandler xmlFood;
	xmlFood.SaveDocument(file, data);

	return true;
}

bool FoodData::CreateFood(const Food& food)
{
	Food* newFood = new Food(food);
	data.push_back(newFood);

	return true;
}

bool FoodData::UpdateFood(const Food& oldFood, Food& newFood)
{
	Food *fud = 0;
	for( auto food : data )
	{
		if( food->name.Cmp(oldFood.name) == 0 )
		{
			fud = food;
			break;
		}
	}

	if( !fud )
		return false;

	fud->UpdateChanged(newFood);

	return true;
}

bool FoodData::DeleteFoodByName( const wxString &name )
{
	for( auto it = data.begin(); it != data.end(); ++it )
	{
		Food* food = (*it);
		if( food->name.Cmp(name) == 0 )
		{
			data.erase(it);
			return true;
		}

	}

	return false;
}

const Food* FoodData::GetFoodByName( const wxString &name )
{
	for( auto food : data )
	{
		if( food->name.Cmp(name) == 0 )
			return food;
	}

	return nullptr;
}
