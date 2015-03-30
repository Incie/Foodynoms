#include"ListController.h"
#include<wx/listctrl.h>

ListController::ListController( wxWindow* parent, const wxPoint &position, const wxSize &size )
{
	list = new wxListCtrl(parent, wxID_ANY, position, size, wxLC_REPORT|wxLC_SINGLE_SEL);

	wxSize listClientSize = list->GetClientSize();	
	int columnIndex = list->InsertColumn(0, "Fud");
	list->SetColumnWidth(columnIndex, listClientSize.x);	
}

ListController::~ListController()
{
}

int ListController::GetListID() 
{
	if( !list ) 
		return -1; 
	return list->GetId(); 
}

ListController::ErrorCode ListController::SetSelected(const wxString &entryName)
{
	int index = GetListIndexByName(entryName);
	
	if( index == -1 )
		return ENTRY_NOT_FOUND;

	list->SetItemState(index, wxLIST_STATE_SELECTED,wxLIST_STATE_SELECTED);
	return ListController::EC_SUCCESS;
}

ListController::ErrorCode ListController::GetSelected(wxString &selection)
{
	int index = GetSelectedIndex();
	
	if( index == -1 )
		return ENTRY_NOT_FOUND;

	return GetItemTextFromIndex(index, selection);
}

ListController::ErrorCode ListController::AddEntry(const wxString& entryName )
{
	list->InsertItem(0, entryName);
	return ListController::EC_SUCCESS;
}

ListController::ErrorCode ListController::UpdateEntry(const wxString &currentName, const wxString &newName )
{
	int index = GetListIndexByName(currentName);

	if( index == -1 )
		return ListController::ENTRY_NOT_FOUND;

	wxListItem listItem;
	listItem.m_itemId = index;
	listItem.m_col = 0;
	listItem.m_mask = wxLIST_MASK_TEXT;
	listItem.m_text = newName;
	list->SetItem(listItem);

	return ListController::EC_SUCCESS;
}

ListController::ErrorCode ListController::RemoveEntry( const wxString &entryName )
{
	int index = GetListIndexByName(entryName);

	if( index == -1 )
		return ListController::ENTRY_NOT_FOUND;

	list->DeleteItem(index);
	return ListController::EC_SUCCESS;
}

ListController::ErrorCode ListController::GetItemTextFromIndex(int index, wxString &text)
{
	wxListItem listitem;
	listitem.m_itemId = index;
	listitem.m_col = 0;
	listitem.m_mask = wxLIST_MASK_TEXT;
		
	if( !list->GetItem(listitem) )
		return ENTRY_NOT_FOUND;
	
	text = listitem.GetText();
	return EC_SUCCESS;
}

int ListController::GetSelectedIndex()
{
	return list->GetNextItem(-1, wxLIST_NEXT_ALL, wxLIST_STATE_SELECTED);
}

int ListController::GetListIndexByName(const wxString &name)
{
	int itemIndex = -1;
	while( -1 != (itemIndex = list->GetNextItem(itemIndex, wxLIST_NEXT_ALL,wxLIST_STATE_DONTCARE)) )
	{
		wxString itemText;
		ErrorCode ecode = GetItemTextFromIndex(itemIndex, itemText);

		if( ecode != EC_SUCCESS )
			continue;

		if( itemText.Cmp(name) == 0 )
			return itemIndex;
	}

	return -1;
}
