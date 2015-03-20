#pragma once


#include<wx/frame.h>
#include"FoodData.h"

class wxPanel;
class ListController;

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

	void OnButtonNew( wxCommandEvent &evt );
	void OnButtonModify( wxCommandEvent &evt );
	void OnButtonRemove( wxCommandEvent &evt );

private:
	wxPanel* mainPanel;
	
	ListController *listFood;
	FoodData foodData;
};
