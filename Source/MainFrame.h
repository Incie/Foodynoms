#pragma once


#include<wx/frame.h>
#include"Food.h"
#include"FoodData.h"

class wxPanel;
class ListController;
class wxTextCtrl;
class wxListCtrl;
class wxListEvent;

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

	void OnButtonNew( wxCommandEvent &evt );
	void OnButtonModify( wxCommandEvent &evt );
	void OnButtonRemove( wxCommandEvent &evt );
	void OnClose( wxCloseEvent &evt );

private:
	void OnListSelection( wxListEvent &evt );

	void UpdateFoodUI( const Food &food );

	wxPanel* mainPanel;

	ListController *listFood;
	wxTextCtrl* ingredients;
	wxTextCtrl* description;
	wxTextCtrl* statistics;

	FoodData foodData;
	const Food emptyFood;
};
