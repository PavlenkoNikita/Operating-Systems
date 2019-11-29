#pragma once
#include <windows.h>
#include <windowsx.h>
#include <CommCtrl.h>
#include "WindowInformation.h"
#include <vector>
#include <string>

class Control
{
protected: 
	LPTSTR    _nameClass, _nameWindow;
	DWORD     _style, _exStyle;
	int       _x, _y, _width, _height;
	HMENU     _code;
	HINSTANCE _hInstance;
	HWND      _hParent, _handle;
	LPVOID    _param;

public:
	Control();

	Control(LPTSTR nameClass,
		LPTSTR nameWindow,
		DWORD style,
		int x, 
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	Control(DWORD exStyle,
		LPTSTR nameClass,
		LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU p_code,
		HINSTANCE hInstance,
		LPVOID param);

	HWND getHwnd() const   { return _handle; }
	int  getWidth() const  { return _width;  }
	int  getHeight() const { return _height; }
	BOOL reSize(int width, int height, BOOL rePaint);
	BOOL move(int x, int y, BOOL rePaint);

	~Control();
};

class Combobox : public Control
{
public:
	Combobox();

	Combobox(LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	Combobox(DWORD exStyle,
		LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	void addString(TCHAR* p_string);
	void getSelectString(LPTSTR p_result);
	void clear();
	int getCount() const;
};

class Label : public Control
{
public:
	Label();

	Label(LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	Label(DWORD exStyle,
		LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	void setText(std::basic_string<TCHAR> p_string);
};

class TreeView : public Control
{
private:
	TreeItemInformation* _treeInformation;
	HTREEITEM _handleTreeRootItem;

	void initializationTree(HTREEITEM hParent, TreeItemInformation* wInfo);

public:
	TreeView();

	TreeView(LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	TreeView(DWORD exStyle,
		LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	HTREEITEM createRoot(LPCTSTR p_string, TreeItemInformation* p_tInformation);
	HTREEITEM insertChild(HTREEITEM parent, LPTSTR p_string);
	std::basic_string<TCHAR> getSelectedItem();
	void clear();
};

class TextBox : public Control
{
public:
	TextBox();

	TextBox(LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	TextBox(DWORD exStyle,
		LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	std::basic_string<TCHAR> getText() const;
	void setText(const std::basic_string<TCHAR> Text) const;
};

class ListBox : public Control
{
public:
	ListBox();

	ListBox(LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	ListBox(DWORD exStyle,
		LPTSTR nameWindow,
		DWORD style,
		int x,
		int y,
		int width,
		int height,
		HWND hParent,
		HMENU code,
		HINSTANCE hInstance,
		LPVOID param);

	void addString(std::basic_string<TCHAR> string);
	void setList(std::vector<std::basic_string<TCHAR>> string);
	void clear();
};