#include "WindowInformation.h"
#include "GlobalData.h"
#include <CommCtrl.h>

std::map<std::basic_string<TCHAR>, HWND> TreeWindow::listItems;

TreeWindow::TreeWindow()
{
}

TreeWindow::TreeWindow(HWND p_handle)
	: handle(p_handle)
{
	initChildsBranch();
	setStringElement();
	listItems.insert(std::pair<std::basic_string<TCHAR>, HWND>(stringElement, handle));
}

void TreeWindow::initChildsBranch()
{	
	HWND tempHwnd = GetWindow(handle, GW_CHILD);
	while (tempHwnd != 0)
	{
		childs.push_back(new TreeWindow(tempHwnd));
		tempHwnd = GetWindow(tempHwnd, GW_HWNDNEXT);
	}
}

void TreeWindow::setStringElement()
{
	std::basic_string<TCHAR> str, nameClass, title;
	int length = GetWindowTextLength(handle);
	if (length > 0)
	{
		str.resize(length + 1);
		length = GetWindowText(handle, &str[0], str.size());
		str.resize(length);
	}
	TCHAR result[60];
	sprintf_s(result, "%08X", handle);

	TCHAR buffer[MAX_PATH];
	if (GetWindowText(handle, buffer, MAX_PATH))
		title = buffer;
	if (GetClassName(handle, buffer, MAX_PATH))
		nameClass = buffer;

	stringElement = std::basic_string<TCHAR>("Окно " + std::basic_string<TCHAR>(result) + (LPTSTR)" \"" + title + (LPTSTR)"\" " + nameClass);
}

std::basic_string<TCHAR> TreeWindow::toString()
{
	return stringElement;
}

HWND TreeWindow::getHandleSelectedItem(std::basic_string<TCHAR> selectedText)
{
	return listItems[selectedText];
}

TreeWindow::~TreeWindow()
{
	int n = childs.size();
	for (int i = 0; i < n; i++)
	{
		delete childs[i];
	}
}

