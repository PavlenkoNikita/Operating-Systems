#include "GlobalData.h"

Window mainWindow;

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	LPTSTR NameClass = (LPTSTR)"WindowKP";
	LPTSTR TitleWindow = (LPTSTR)"Программа исследования окон приложений";

	mainWindow = Window(hInstance, NameClass, TitleWindow, WindowProcesses::MainWindowProcess);
	return mainWindow.run(nCmdShow);
}