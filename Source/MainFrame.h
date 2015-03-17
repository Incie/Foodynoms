#pragma once


#include<wx/frame.h>
#include"FoodData.h"

class wxPanel;
class wxListCtrl;

class MainFrame : public wxFrame
{
public:
	MainFrame();
	~MainFrame();

	void OnButtonNew( wxCommandEvent &evt );

private:
	wxPanel* mainPanel;
	wxListCtrl* listFood;

	FoodData foodData;
};
