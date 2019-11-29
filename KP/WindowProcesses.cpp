#include "stdafx.h"
#include <CommCtrl.h>

LRESULT WindowProcesses::MainWindowProcess(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, MainWindow::OnCreate);
		HANDLE_MSG(hWnd, WM_DESTROY, MainWindow::OnDestroy);
		HANDLE_MSG(hWnd, WM_NOTIFY, MainWindow::OnNotify);
	case WM_CTLCOLORSTATIC:
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (LRESULT)GetStockObject(WHITE_BRUSH);

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	
}
