#include"FoodData.h"
#include"Food.h"
#include"XMLFoodHandler.h"
#include<algorithm>

bool SortByFoodNames( const Food* left, const Food* right )
{
	return left->name.Cmp( right->name ) < 0;
}

FoodData::FoodData()
{
	data.reserve(256);
}

FoodData::~FoodData()
{
	ClearData();
}

struct Statistic 
{
	wxString food;
	wxString date;
};

bool SortStatistics( const Statistic &s0, const Statistic &s1 )
{
	return s0.date.Cmp( s1.date ) < 0;
}

wxString AddJSONField(const wxString &fieldName, const wxString &fieldValue, wxString end = "")
{
	return wxString::Format("\"%s\":\"%s\"%s", fieldName, fieldValue, end);	
}

wxString FoodData::ExportJSON()
{
	wxString json = "{";

	for( const Food* food : data )
	{
		json += "{";
		json += AddJSONField("name", food->name, ",");
		json += AddJSONField("description", food->description, ",");
		json += AddJSONField("ingredients", food->ingredients);
		json += "}";
	}

	json += "}";


	return json;
}

wxString FoodData::GenerateDateStatistics()
{
	std::vector<Statistic> statisticList;

	for( const Food* food : data )
	{
		wxStringTokenizer tokens(food->datesEaten, ";");
		while( tokens.HasMoreTokens() )
		{
			statisticList.push_back( Statistic() );
			Statistic &s = statisticList.back();

			s.date = tokens.GetNextToken();
			s.food = food->name;
		}
	}

	std::sort(statisticList.begin(), statisticList.end(), SortStatistics);

	wxString statistics;
	for( auto &s : statisticList )
	{
		statistics += s.date;
		statistics += " - ";
		statistics += s.food;
		statistics += "\n";
	}

	return statistics;
}

bool FoodData::AddDateToFood( const wxString &name, const wxString &date )
{
	Food* food = GetFood(name);

	if( !food )
		return false;

	//Make sure it ends with a ;
	if( !food->datesEaten.IsEmpty() )
	{
		if( food->datesEaten.EndsWith(wxT(";")) == false )
			food->datesEaten += ";";
	}

	food->datesEaten += (date + ";");
	return true;
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

std::vector<wxString> FoodData::GetSortedFoodNameList()
{
	//Make Copy
	std::vector<const Food*> foodCopy;
	for( const auto food : data )
		foodCopy.push_back(food);

	//Sort Pointers by Criteria
	std::sort(foodCopy.begin(), foodCopy.end(), SortByFoodNames);

	//return namelist
	std::vector<wxString> sortedFood;
	for( auto food : foodCopy )
		sortedFood.push_back(food->name);

	return sortedFood;
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


Food* FoodData::GetFood( const wxString &name )
{
	for( auto food : data )
	{
		if( food->name.Cmp(name) == 0 )
			return food;
	}

	return nullptr;
}


const Food* FoodData::GetFoodByName( const wxString &name )
{
	return GetFood(name);
}
