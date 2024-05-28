#pragma comment(lib, "user32.lib")
#include <windows.h>

int WINAPI WinMain (HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR szCmdLine, int iCmdShow)
{
	MessageBox(NULL, TEXT("Hello"), TEXT("Hello"), 0);
}
