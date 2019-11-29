#include "stdafx.h"
#include <CommCtrl.h>
#include "MainWindow.h"
#include "WindowInformation.h"
#include "GlobalData.h"
#include "WindowData.h"
#include <string>
#include "Control.h"


TreeView treeWindows;
Combobox boxHandlesWindows;
TreeWindow* wInformation;
TextBox g_titleWindow, g_sizeWindow, g_classWindow, g_parentWindow, g_locationWindow;
ListBox g_styleWindow, g_StyleExWindow;

BOOL MainWindow::OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	int xLabel = 340, xData = 460, xLengthData = 210;
	TCHAR textDefault[] = "NULL";
	int idControl = 1;

	wInformation = new TreeWindow(GetDesktopWindow());
		
	treeWindows = TreeView(0,
		WS_VISIBLE | WS_CHILD | WS_BORDER | TVS_HASLINES | TVS_HASBUTTONS | TVS_LINESATROOT | TVS_EX_DOUBLEBUFFER | TVS_EX_FADEINOUTEXPANDOS,
		0, 0, 330, 481, hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	treeWindows.createRoot((LPTSTR)wInformation->toString().c_str(), wInformation);
	
	Label title = Label((TCHAR*)"Заголовок окна:",
		WS_CHILD | WS_VISIBLE, xLabel, 15, 120, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	g_titleWindow = TextBox(textDefault,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, xData, 15, xLengthData, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	
	Label size = Label((TCHAR*)"Размер:",
		WS_CHILD | WS_VISIBLE, xLabel, 55, 80, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	g_sizeWindow = TextBox(textDefault,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, xData, 55, xLengthData, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);

	Label location = Label((TCHAR*)"Положение:",
		WS_CHILD | WS_VISIBLE, xLabel, 95, 80, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	g_locationWindow = TextBox(textDefault,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, xData, 95, xLengthData, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);

	Label Class = Label((TCHAR*)"Класс окна:",
		WS_CHILD | WS_VISIBLE, xLabel, 135, 80, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	g_classWindow = TextBox(textDefault,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, xData, 135, xLengthData, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);

	Label style = Label((TCHAR*)"Стили окна:",
		WS_CHILD | WS_VISIBLE, xLabel, 175, 80, 120,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	g_styleWindow = ListBox(textDefault,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | WS_VSCROLL | LBS_NOINTEGRALHEIGHT | LBS_DISABLENOSCROLL, xData, 175, xLengthData, 120,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);

	Label exStyle = Label((TCHAR*)"Расширенные стили окна:",
		WS_CHILD | WS_VISIBLE, xLabel, 310, 120, 120,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	g_StyleExWindow = ListBox(textDefault,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | WS_VSCROLL | LBS_NOINTEGRALHEIGHT | LBS_DISABLENOSCROLL, xData, 310, xLengthData, 120,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	
	Label parent = Label((TCHAR*)"Родитель:",
		WS_CHILD | WS_VISIBLE , xLabel, 445, 80, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	g_parentWindow = TextBox(textDefault,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_AUTOHSCROLL | ES_READONLY, xData, 445, xLengthData, 20,
		hwnd, (HMENU)idControl++, mainWindow.getHInsatnce(), NULL);
	return TRUE;
}

LRESULT MainWindow::OnNotify(HWND hWnd, int idFrom, LPNMHDR pnmhdr)
{
	if (pnmhdr->hwndFrom == treeWindows.getHwnd())
	{
		if (pnmhdr->code == NM_DBLCLK)
		{
			WindowData temp { wInformation->getHandleSelectedItem(treeWindows.getSelectedItem()) };

			g_titleWindow.setText(temp.getTitle());
			g_sizeWindow.setText(temp.getStrSize());
			g_locationWindow.setText(temp.getStrLocation());
			g_classWindow.setText(temp.getNameClass());
			g_styleWindow.setList(temp.getListStyles());
			g_StyleExWindow.setList(temp.getListStylesEx());
			g_parentWindow.setText(temp.getStrParentHandle());
		}
	}
	return FALSE;
}

void MainWindow::OnDestroy(HWND hwnd)
{	
	PostQuitMessage(0);
	DestroyWindow(hwnd);
}