#include "WindowData.h"

#ifdef _UNICODE
	#define to_tstring(x) std::to_wstring(x)
#else
	#define to_tstring(x) std::to_string(x)
#endif

//TCHAR szHexFmt[] = _T("%08X");

WindowData::WindowData()
{
}

void WindowData::checkEmptyStr(std::basic_string<TCHAR>& str)
{
	if (str.size() == 0)
		str = "NULL";
}

WindowData::WindowData(HWND p_handle)
	: _handle(p_handle)
{
	TCHAR buffer[MAX_PATH];
	sprintf_s(buffer,  "%08X", _handle);
	_strHandle = buffer;

	if (GetWindowText(_handle, buffer, MAX_PATH))
		_title = buffer;
	if (GetClassName(_handle, buffer, MAX_PATH))
		_nameClass = buffer;

	_styles = StyleWindow(_handle);

	RECT tempRect;
	if (GetWindowRect(_handle, &tempRect))
	{
		_strSize = std::basic_string<TCHAR>("[" + to_tstring(tempRect.right - tempRect.left) + " x " + to_tstring(tempRect.bottom - tempRect.top) + "]");
		_strLocation = std::basic_string<TCHAR>("[" + to_tstring(tempRect.left) + ", " + to_tstring(tempRect.top) + "]");
	}

	sprintf_s(buffer, "%08X", GetParent(_handle));
	_strParentHandle = buffer;
}

std::basic_string<TCHAR> WindowData::getStringHandle()
{
	checkEmptyStr(_strHandle);
	return _strHandle;
}

std::basic_string<TCHAR> WindowData::getTitle()
{
	checkEmptyStr(_title);
	return _title;
}

std::basic_string<TCHAR> WindowData::getNameClass() 
{
	checkEmptyStr(_nameClass);
	return _nameClass;
}

std::basic_string<TCHAR> WindowData::getStrParentHandle()
{
	checkEmptyStr(_strParentHandle);
	return _strParentHandle;
}

std::basic_string<TCHAR> WindowData::getStrLocation()
{
	checkEmptyStr(_strLocation);
	return _strLocation;
}

std::basic_string<TCHAR> WindowData::getStrSize()
{
	checkEmptyStr(_strSize);
	return _strSize;
}

std::vector<std::basic_string<TCHAR>> WindowData::getListStyles()
{
	return _styles.GetStyles();
}

std::vector<std::basic_string<TCHAR>> WindowData::getListStylesEx()
{
	return _styles.GetStylesEx();
}

WindowData::~WindowData()
{
}
