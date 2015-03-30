#pragma once


class wxWindow;
class wxListCtrl;
class wxPoint;
class wxSize;
class wxString;

class ListController
{
public:
	ListController( wxWindow* parent, const wxPoint&, const wxSize& );
	~ListController();

	enum ErrorCode
	{
		EC_SUCCESS,
		ENTRY_ALREADY_EXISTS,
		ENTRY_NOT_FOUND
	};

	ErrorCode UpdateEntry(const wxString &currentName, const wxString &newName );

	ErrorCode SetSelected(const wxString &entryName);
	ErrorCode GetSelected(wxString &selection);

	ErrorCode AddEntry(const wxString &entryName );
	ErrorCode RemoveEntry( const wxString &entryName );

	int GetListID();
private:
	int GetSelectedIndex();
	int GetListIndexByName(const wxString &name);
	ErrorCode GetItemTextFromIndex(int index, wxString &text);
	

	wxListCtrl* list;
};