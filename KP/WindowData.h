#pragma once
#include <Windows.h>
#include "Styles.h"
#include <string>

class WindowData
{
private:
	StyleWindow _styles;
	HWND _handle;
	std::basic_string<TCHAR> _strHandle, _title, _nameClass, _strParentHandle, _strLocation, _strSize;

	void checkEmptyStr(std::basic_string<TCHAR>& str);
public:
	WindowData();
	WindowData(HWND p_handle);

	std::basic_string<TCHAR> getStringHandle();
	std::basic_string<TCHAR> getTitle();
	std::basic_string<TCHAR> getNameClass();
	std::basic_string<TCHAR> getStrParentHandle();
	std::basic_string<TCHAR> getStrLocation();
	std::basic_string<TCHAR> getStrSize();
	std::vector<std::basic_string<TCHAR>> getListStyles();
	std::vector<std::basic_string<TCHAR>> getListStylesEx();

	~WindowData();
};