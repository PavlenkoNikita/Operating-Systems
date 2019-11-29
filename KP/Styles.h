#pragma once
#include <windows.h>
#include <commctrl.h>
#include <tchar.h>

#include <vector>
#include <string>

    struct DialogTab
	{
		HWND    hwnd;
		LPCTSTR szText;
		UINT    id;
		WNDPROC dlgproc;
	};

	struct StyleLookupType
	{
		UINT    style;
		LPCTSTR szName;
	};

	struct StyleLookupEx
	{
		DWORD   style;	
		LPCTSTR name;	
		DWORD   cmp_mask;
		DWORD   depends;
		DWORD   excludes;

	};

	struct ClassStyleLookup
	{
		LPCTSTR        szClassName;
		StyleLookupEx  *stylelist;
		DWORD			dwData;
	};

	class StyleWindow
	{
	private:
		HWND _handle;
		TCHAR _className[MAX_PATH];

		std::vector<std::basic_string<TCHAR>> _styles;
		std::vector<std::basic_string<TCHAR>> _exStyles;

		void FillStyleExLists(BOOL fAllStyles, BOOL fExtControl);
		void FillStyleLists(BOOL fAllStyles, BOOL fExtControl);
		DWORD EnumStyles(std::vector<std::basic_string<TCHAR>>& styles,
			StyleLookupEx *StyleList,
			DWORD dwStyle,
			BOOL fAllStyles);
	    StyleLookupEx *FindStyleList(ClassStyleLookup *pClassList, DWORD *pdwData);
	public:
		StyleWindow();
		StyleWindow(HWND handle);

		std::vector<std::basic_string<TCHAR>> GetStyles();
		std::vector<std::basic_string<TCHAR>> GetStylesEx();
	};