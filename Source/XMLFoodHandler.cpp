#include"XMLFoodHandler.h"
#include"Food.h"
#include<wx/xml/xml.h>


XMLFoodHandler::XMLFoodHandler()
{
}

XMLFoodHandler::~XMLFoodHandler()
{
}

int XMLFoodHandler::LoadDocument( const wxString &file, std::vector<Food*> &foodData )
{
	wxXmlDocument document;

	if( !document.Load(file) )
		return -1;

	wxXmlNode *root = document.GetRoot();
	wxXmlNode *foodNode = root->GetChildren();

	while( foodNode )
	{
		Food* food = new Food();
		foodData.push_back(food);

		food->name = foodNode->GetAttribute("ID");

		wxXmlNode *dataNode = foodNode->GetChildren();

		while( dataNode )
		{
			const wxString &nodeName = dataNode->GetName();

			if( nodeName.Cmp("description") == 0 )
			{
				wxXmlNode *child = dataNode->GetChildren();

				if( child )
					food->description = child->GetContent();
			}
			else if( nodeName.Cmp("ingredients") == 0 )
			{
				wxXmlNode *child = dataNode->GetChildren();

				if( child )
					food->ingredients = child->GetContent();
			}
			else if( nodeName.Cmp("dates_eaten") == 0 )
			{
				wxXmlNode *child = dataNode->GetChildren();

				if( child )
					food->datesEaten = child->GetContent();
			}

			dataNode = dataNode->GetNext();
		}

		foodNode = foodNode->GetNext();
	}

	return 1;
}


int XMLFoodHandler::SaveDocument( const wxString &file, const std::vector<Food*> &foodData )
{
	wxXmlDocument document;

	wxXmlNode *root = new wxXmlNode(wxXML_ELEMENT_NODE, "food" );
	document.SetRoot( root );

	for( auto food : foodData )
	{
		wxXmlNode *foodNode = new wxXmlNode(root, wxXML_ELEMENT_NODE, "name");
		foodNode->AddAttribute("ID", food->name );

		wxXmlNode *descNode = new wxXmlNode(foodNode, wxXML_ELEMENT_NODE, "description");
		wxXmlNode *descTextNode = new wxXmlNode(descNode, wxXML_TEXT_NODE, food->description);
		descTextNode->SetContent(food->description);

		wxXmlNode *recipeNode = new wxXmlNode(foodNode, wxXML_ELEMENT_NODE, "ingredients");
		wxXmlNode *recipeTextNode = new wxXmlNode(recipeNode, wxXML_TEXT_NODE, food->ingredients);
		recipeTextNode->SetContent( food->ingredients );
		
		wxXmlNode *datesEatenNode = new wxXmlNode(foodNode, wxXML_ELEMENT_NODE, "dates_eaten");
		wxXmlNode *datesEatenTextNode = new wxXmlNode(datesEatenNode, wxXML_TEXT_NODE, food->datesEaten);
		datesEatenTextNode->SetContent(food->datesEaten);
	}

	if( !document.Save(file) )
	{
		return -1;
	}
	
	return 1;
}
