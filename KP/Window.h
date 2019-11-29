#pragma once
class Window
{
private:
	ATOM ClassRegister();
	BOOL InitInstance(int nCmdShow);

	HWND      _handle;
	LPTSTR    _className;
	LPTSTR    _title;
	HINSTANCE _hInstance;
	UINT      _style, _exStyle;
	WNDPROC   _processMessages;
	int    _width;
	int    _height;
	int    _x;
	int    _y;

public:
	Window();
	Window(HINSTANCE p_hInstance);
	Window(HINSTANCE p_hInstance, LPTSTR p_className, LPTSTR p_title, WNDPROC p_processMessages);

	HWND      getHwnd();
	int       run(int p_nCmdShow);
	void      setStyle(UINT p_style);
	void      setSize(int p_width, int p_height);
	void      setLocation(int p_x, int p_y);
	HINSTANCE getHInsatnce();

	~Window();
};

