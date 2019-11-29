#pragma once
class MainWindow
{
public:
	static LRESULT OnNotify(HWND hWnd, int idFrom, LPNMHDR pnmhdr);
	static BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
	static void OnDestroy(HWND hwnd);
};

