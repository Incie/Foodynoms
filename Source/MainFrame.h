#pragma once


#include<wx/frame.h>
#include"Food.h"
#include"FoodData.h"

class wxStaticText;
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

private:
	void OnButtonNew( wxCommandEvent &evt );
	void OnButtonModify( wxCommandEvent &evt );
	void OnButtonRemove( wxCommandEvent &evt );
	void OnButtonNom( wxCommandEvent &evt );
	void OnButtonNomWhen( wxCommandEvent &evt );
	void OnButtonRemoveNom( wxCommandEvent &evt );
	void OnButtonStats( wxCommandEvent &evt );
	void OnClose( wxCloseEvent &evt );
	//void OnFilter( wxSomeEvent &evt );

	void OnListSelection( wxListEvent &evt );

	void UpdateFoodUI( const wxString &foodName );
	void UpdateFoodUI( const Food &food );

	wxPanel* mainPanel;

	wxStaticText* statFoodHeader;
	ListController* listFood;
	ListController* listDates;
	wxTextCtrl* ingredients;
	wxTextCtrl* description;
	wxTextCtrl* statistics;

	FoodData foodData;
	const Food emptyFood;
};
