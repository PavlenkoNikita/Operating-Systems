#pragma once
#include <Windows.h>
#include <string>
#include <vector>

class Item
{
private:
	std::basic_string<TCHAR> stringHandle;
	HWND  handle;
public:
	Item();
	Item(std::basic_string<TCHAR>, HWND );
	HWND getHandle();
	std::basic_string<TCHAR> getStringItem() {	return stringHandle; }
};

class ListItemsTree
{
private:
	std::vector<Item> elements;
public:
	ListItemsTree();
	void addItem(Item p_element);
	void addItem(std::basic_string<TCHAR> itemString, HWND handle);
	HWND getItemHandle(TCHAR p_string[]);
	int getCount() const { return elements.size(); }
	void clear() { elements.clear(); }
	Item operator[](int index);
};