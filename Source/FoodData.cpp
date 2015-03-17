#include"FoodData.h"
#include"Food.h"

FoodData::FoodData()
{
	data.reserve(256);
}

FoodData::~FoodData()
{
	for( auto food : data )
		delete food;
}

bool FoodData::CreateFood(const Food& food)
{
	Food* newFood = new Food(food);
	data.push_back(newFood);

	return true;
}

bool FoodData::DeleteFoodByName( const wxString &name )
{
	for( auto food : data )
	{
		if( food->name.Cmp(name) == 0 )
		{
			//data.erase(food);
		}

	}

	return true;
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
