#pragma once
#include "stdafx.h"
#include <vector>
#include <map>
#include <string>


class TreeItemInformation
{
public:
	virtual std::basic_string<TCHAR> toString() = 0;
	std::vector<TreeItemInformation*> getChilds() const { return childs; }
	virtual ~TreeItemInformation() {}

protected:
	std::basic_string<TCHAR> stringElement;
	std::vector<TreeItemInformation*> childs;
};


class TreeWindow : public TreeItemInformation
{
private:
	HWND handle;
	static std::map<std::basic_string<TCHAR>, HWND> listItems;
	
	void initChildsBranch();
	void setStringElement();
public:
	TreeWindow();
	TreeWindow(HWND p_handle);

	HWND getHandle() const { return handle; }
	std::basic_string<TCHAR> toString() override;
	static HWND getHandleSelectedItem(std::basic_string<TCHAR> selectedText);

	~TreeWindow();
};