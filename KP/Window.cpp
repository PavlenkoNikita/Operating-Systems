#pragma once
#include "resource.h"
#include <Windows.h>
#include "Window.h"


Window::Window()
{
	_className = (LPTSTR)"Window Deafult";
	_title = (LPTSTR)"Title Default";
	_width     = 600;
	_height    = 400;
	_x         = (GetSystemMetrics(SM_CXSCREEN) - _width) / 2;
	_y         = (GetSystemMetrics(SM_CYSCREEN) - _height) / 2;
	_style     = CS_HREDRAW | CS_VREDRAW;
}

Window::Window(HINSTANCE p_hInstance)
	: _hInstance(p_hInstance)
{
	_className = (LPTSTR)"Window Deafult";
	_title = (LPTSTR)"Title Default";
	_width = 600;
	_height = 400;
	_x = (GetSystemMetrics(SM_CXSCREEN) - _width) / 2;
	_y = (GetSystemMetrics(SM_CYSCREEN) - _height) / 2;
	_style = CS_HREDRAW | CS_VREDRAW;
	_exStyle = NULL;
}

Window::Window(HINSTANCE p_hInstance, LPTSTR p_className, LPTSTR p_title, WNDPROC p_processMessages)
	: _hInstance(p_hInstance), _className(p_className), _title(p_title), _processMessages(p_processMessages)
{
	_width  = 700;
	_height = 520;
	_x = (GetSystemMetrics(SM_CXSCREEN) - _width) / 2;
	_y = (GetSystemMetrics(SM_CYSCREEN) - _height) / 2;
	_style = CS_HREDRAW | CS_VREDRAW;
	_exStyle = NULL;
}

void Window::setStyle(UINT style)
{
	_style = style;
}

HINSTANCE Window::getHInsatnce()
{
	return _hInstance;
}

void Window::setSize(int width, int height)
{
	_width  = width;
	_height = height;
	_x      = (GetSystemMetrics(SM_CXSCREEN) - _width) / 2;
	_y      = (GetSystemMetrics(SM_CYSCREEN) - _height) / 2;
}

void Window::setLocation(int x, int y)
{
	_x = x;
	_y = y;
}

ATOM Window::ClassRegister()
{
	WNDCLASSEX wcex;
	ZeroMemory(&wcex, sizeof(wcex));

	wcex.cbSize        = sizeof(WNDCLASSEX);
	wcex.style         = _style;
	wcex.lpfnWndProc   = _processMessages;
	wcex.hInstance     = _hInstance;
	wcex.hIcon         = LoadIcon(_hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wcex.hCursor       = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.lpszClassName = _className;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_ICON1));

	return RegisterClassEx(&wcex);
}

BOOL Window::InitInstance(int nCmdShow)
{
	_handle = CreateWindowEx(_exStyle, _className, _title, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX,
		                    _x, _y, _width, _height,
		                    nullptr, nullptr, _hInstance, nullptr);
	int t = 0;
	if (_handle)
	{
		ShowWindow(_handle, nCmdShow);
		UpdateWindow(_handle);
	}
	return _handle != NULL;
}

HWND Window::getHwnd()
{
	return _handle;
}

int Window::run(int nCmdShow)
{
	ClassRegister();
	MSG msg;
	ZeroMemory(&msg, sizeof(msg));
	
	if (InitInstance(nCmdShow))
	{
		/*while (true)
		{
			if (PeekMessage(&msg, handle, 0, 0, PM_REMOVE))
			{
				if (msg.message == WM_QUIT )
					break;

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}*/
		
		while (GetMessage(&msg, NULL, 0, 0) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
	return (int)msg.wParam;
}


Window::~Window()
{
}
