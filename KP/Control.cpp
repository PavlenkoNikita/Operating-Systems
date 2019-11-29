#include "Control.h"
#include <string>

Control::Control(DWORD exStyle, LPTSTR nameClass, LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: _exStyle(exStyle),
	_nameClass(nameClass),
	_nameWindow(nameWindow),
	_style(style),
	_x(x),
	_y(y),
	_width(width),
	_height(height),
	_hParent(hParent),
	_code(code),
	_hInstance(hInstance),
	_param(param)
{
	_handle = CreateWindowEx(_exStyle, _nameClass, _nameWindow, _style, _x, _y, _width, _height, _hParent, _code, _hInstance, _param);
}

Control::Control()
{
}

Control::Control(LPTSTR nameClass, LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: _nameClass(nameClass),
	_nameWindow(nameWindow),
	_style(style),
	_x(x),
	_y(y),
	_width(width),
	_height(height),
	_hParent(hParent),
	_code(code),
	_hInstance(hInstance),
	_param(param)
{
	_exStyle = NULL;
	_handle = CreateWindow(_nameClass, _nameWindow, _style, _x, _y, _width, _height, _hParent, _code, _hInstance, _param);
}

BOOL Control::reSize(int width, int height, BOOL p_rePaint)
{
	if (MoveWindow(_handle, _x, _y, width, height, p_rePaint))
	{
		_width = width;
		_height = height;
		return TRUE;
	}
	else
		return FALSE;
}

BOOL Control::move(int x, int y, BOOL rePaint)
{
	if (MoveWindow(_handle, x, y, _width, _height, rePaint))
	{
		_x = x;
		_y = y;
		return TRUE;
	}
	else
		return FALSE;
}

Control::~Control()
{
}

/*-------------------------------------------ComboBox----------------------------------------------------*/
Combobox::Combobox()
{
}

Combobox::Combobox(LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: Control((LPTSTR)"Combobox",
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

Combobox::Combobox(DWORD exStyle, LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: Control(exStyle,
	(LPTSTR)"Combobox",
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

void Combobox::addString(TCHAR * p_string)
{
	ComboBox_AddString(_handle, p_string);
	_height = getCount() * 16 + 26;
	reSize(_width, _height, 0);
}

void Combobox::getSelectString(LPTSTR p_result)
{
	int index = ComboBox_GetCurSel(_handle);
	ComboBox_GetLBText(_handle,	index, p_result);
}

void Combobox::clear()
{
	ComboBox_ResetContent(_handle);
	_height = 26;
	reSize(_width, _height, 0);
}

int Combobox::getCount() const
{
	return ComboBox_GetCount(_handle);
}

/*-------------------------------------------Label----------------------------------------------------*/
Label::Label()
{
}

Label::Label(LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: Control((LPTSTR)"Static",
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

Label::Label(DWORD exStyle, LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: Control(exStyle,
		(LPTSTR)"Static",
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

void Label::setText(std::basic_string<TCHAR> p_string)
{
	Static_SetText(_handle, p_string.c_str());
}

/*-------------------------------------------TreeView----------------------------------------------------*/
TreeView::TreeView()
{
	_handleTreeRootItem = NULL;
}

TreeView::TreeView(LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: _handleTreeRootItem(NULL), Control((LPTSTR)WC_TREEVIEW,
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

TreeView::TreeView(DWORD exStyle, LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: _handleTreeRootItem(NULL), 
	Control(exStyle,
	(LPTSTR)WC_TREEVIEW,
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

HTREEITEM TreeView::createRoot(LPCTSTR p_string, TreeItemInformation* p_tInformation)
{
	TVINSERTSTRUCT treeViewInsert;   
	memset(&treeViewInsert, 0, sizeof(TVINSERTSTRUCT));
	treeViewInsert.hParent = NULL;      
	treeViewInsert.hInsertAfter = TVI_ROOT; 
	treeViewInsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	treeViewInsert.item.pszText = (LPTSTR)p_string;
	treeViewInsert.item.iImage = 0;
	treeViewInsert.item.iSelectedImage = 0;
	_handleTreeRootItem = (HTREEITEM)TreeView_InsertItem(_handle, &treeViewInsert);

	initializationTree(_handleTreeRootItem, p_tInformation);

	return _handleTreeRootItem;
}

void TreeView::initializationTree(HTREEITEM hParent, TreeItemInformation* wInfo)
{
	std::vector<TreeItemInformation*> temp = wInfo->getChilds();
	if (temp.size() == 0)
		return;

	for (int i = 0; i < temp.size(); i++)
	{
		HTREEITEM hChild = insertChild(hParent, (LPTSTR)temp[i]->toString().c_str());
		if (temp[i]->getChilds().size() != 0)
			initializationTree(hChild, temp[i]);
	}
}

HTREEITEM TreeView::insertChild(HTREEITEM parent, LPTSTR p_string) 
{
	TVINSERTSTRUCT tvinsert;   
	memset(&tvinsert, 0, sizeof(TVINSERTSTRUCT));
	tvinsert.hParent = parent;      
	tvinsert.hInsertAfter = TVI_LAST; 
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = p_string;
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 0;
	return  (HTREEITEM)TreeView_InsertItem(_handle, &tvinsert);
}

std::basic_string<TCHAR> TreeView::getSelectedItem()
{
	HTREEITEM hTreeItem = TreeView_GetSelection(_handle);
	TVITEMEX treeViewItem;
	TCHAR szText[MAX_PATH];
	memset(&treeViewItem, 0, sizeof(treeViewItem));
	treeViewItem.mask = TVIF_TEXT;
	treeViewItem.pszText = szText;
	treeViewItem.cchTextMax = MAX_PATH;
	treeViewItem.hItem = hTreeItem;
	TreeView_GetItem(_handle, &treeViewItem);
	return std::basic_string<TCHAR>(szText);
}

void TreeView::clear()
{
	if (_handleTreeRootItem) {
		TreeView_DeleteAllItems(_handle);
	}
}

TextBox::TextBox()
{
}

TextBox::TextBox(LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
: Control((LPTSTR)"Edit",
	nameWindow,
	style, x,
	y,
	width,
	height,
	hParent,
	code,
	hInstance,
	param)
{
}

TextBox::TextBox(DWORD exStyle, LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
: Control(exStyle,
	(LPTSTR)"Edit",
	nameWindow,
	style, x,
	y,
	width,
	height,
	hParent,
	code,
	hInstance,
	param)
{
}

std::basic_string<TCHAR> TextBox::getText() const
{
	TCHAR Text[MAX_PATH];
	Edit_GetText(_handle, Text, MAX_PATH);
	return std::basic_string<TCHAR>(Text);
}

void TextBox::setText(const std::basic_string<TCHAR> text) const
{
	Edit_SetText(_handle, text.c_str());
}

ListBox::ListBox()
{
}

ListBox::ListBox(LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: Control((LPTSTR)"listbox",
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

ListBox::ListBox(DWORD exStyle, LPTSTR nameWindow, DWORD style, int x, int y, int width, int height, HWND hParent, HMENU code, HINSTANCE hInstance, LPVOID param)
	: Control(exStyle,
	(LPTSTR)"listbox",
		nameWindow,
		style, x,
		y,
		width,
		height,
		hParent,
		code,
		hInstance,
		param)
{
}

void ListBox::addString(std::basic_string<TCHAR> string)
{
	ListBox_AddString(_handle, string.c_str());
}

void ListBox::setList(std::vector<std::basic_string<TCHAR>> string)
{
	clear();
	for (int i = 0; i < string.size(); i++)
	{
		ListBox_AddString(_handle, string[i].c_str());
	}
}

void ListBox::clear()
{
	ListBox_ResetContent(_handle);
}