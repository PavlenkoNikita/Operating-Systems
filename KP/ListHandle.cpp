#include "ListItemsTree.h"


Item::Item()
{
}

Item::Item(std::basic_string<TCHAR> stringItem, HWND p_handle)
	: stringHandle(stringItem),
	handle(p_handle)
{
}

HWND Item::getHandle()
{
	return handle;
}

ListItemsTree::ListItemsTree()
{
}

void ListItemsTree::addItem(Item p_element)
{
	elements.push_back(p_element);
}

void ListItemsTree::addItem(std::basic_string<TCHAR> stringItem, HWND handle)
{
	elements.push_back(Item(stringItem, handle));
}

HWND ListItemsTree::getItemHandle(TCHAR p_string[])
{
	int size = elements.size();
	for (int i = 0; i < size; i++)
	{
		if (strcmp(elements[i].getStringItem().c_str() ,p_string))
		{
			return elements[i].getHandle();
		}
	}
	return nullptr;
}

Item ListItemsTree::operator[](int index)
{
	return elements[index];
}