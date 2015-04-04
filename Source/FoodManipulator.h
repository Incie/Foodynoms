#pragma once

#include<wx/dialog.h>

class Food;
class wxPoint;
class wxTextCtrl;

class FoodManipulator : public wxDialog
{
public:
	FoodManipulator(wxWindow* parent, bool AddOkPlusButton = false);
	~FoodManipulator();

	void SetFood( const Food &food );
	void GetFood( Food &food );


	enum {
		ID_OK,
		ID_OK_AND_MORE,
		ID_CANCEL
	};

private:
	wxTextCtrl* CreateInputGroup(wxWindow* parent, const wxString& name, wxPoint& position, unsigned int nLines = 1);
	void ClearFields();
	void OnButtonOK(wxCommandEvent &evt);
	void OnButtonOKPlus(wxCommandEvent &evt);
	void OnButtonCancel(wxCommandEvent &evt);
	
	wxTextCtrl *tcName;
	wxTextCtrl *tcDescription;
	wxTextCtrl *tcIngredients;
};