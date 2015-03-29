#pragma once

#include<vector>

class wxString;
class Food;

class XMLFoodHandler
{
public:
	XMLFoodHandler();
	~XMLFoodHandler();

	int LoadDocument( const wxString &file, std::vector<Food*> &foodData );
	int SaveDocument( const wxString &file, const std::vector<Food*> &foodData );
};