#pragma once


#include<wx/frame.h>
#include"FoodData.h"

class wxPanel;
class wxTextCtrl;
class wxListCtrl;
class wxListEvent;

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

	void OnButtonNew( wxCommandEvent &evt );
	void OnListSelection( wxListEvent &evt );

private:
	wxPanel* mainPanel;
	wxListCtrl* listFood;
	wxTextCtrl* ingredients;
	wxTextCtrl* description;
	wxTextCtrl* statistics;

	FoodData foodData;
};
