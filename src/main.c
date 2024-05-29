#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#include <windows.h>
#include <gl/GL.h>

// Based on https://github.com/vbsw/opengl-win32-example/blob/master/Main.cpp
// For Microsoft Visual C++ 4.0 for Windows versions 95 - 11

static LRESULT CALLBACK windowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam) {
	PAINTSTRUCT paintStruct;
	switch (message) {
		case WM_PAINT:
			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_TRIANGLES);
			glColor3f(1.0f, 0.0f, 0.0f);
			glVertex2i(0, 1);
			glColor3f(0.0f, 1.0f, 0.0f);
			glVertex2i(-1, -1);
			glColor3f(0.0f, 0.0f, 1.0f);
			glVertex2i(1, -1);
			glEnd();
			glFlush();

			BeginPaint(window, &paintStruct);
			EndPaint(window, &paintStruct);
			break;
		case WM_CLOSE:
			DestroyWindow(window);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(window, message, wParam, lParam);
	}
}

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR szCmdLine, int iCmdShow)
{
	ATOM windowClass;
	HWND window;
	HDC windowDeviceContext;
	union {
		WNDCLASSA windowClassData;
		PIXELFORMATDESCRIPTOR pixelFormatData;
		MSG windowMessage;
	} temp;
	int pixelFormat;
	BOOL boolResult;
	HGLRC renderContext;
	// Register window class
	memset(&temp.windowClassData, 0, sizeof(temp.windowClassData));
	temp.windowClassData.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	temp.windowClassData.lpfnWndProc = (WNDPROC)windowProcess;
	temp.windowClassData.cbClsExtra = 0;
	temp.windowClassData.cbWndExtra = 0;
	temp.windowClassData.hInstance = instance;
	temp.windowClassData.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	temp.windowClassData.hCursor = LoadCursor(NULL, IDC_ARROW);
	temp.windowClassData.hbrBackground = NULL;
	temp.windowClassData.lpszMenuName = NULL;
	temp.windowClassData.lpszClassName = "Windows OpenGL";
	windowClass = RegisterClassA(&temp.windowClassData);
	if (windowClass == 0) {
		MessageBoxA(NULL, "RegisterClassA failed", "Error", MB_OK);
		return 0;
	}
	// Create window
	window = CreateWindowA((LPCSTR)windowClass, "Windows OpenGL", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 0, 0, 320, 240, NULL, NULL, instance, NULL);
	if (window == NULL) {
		MessageBoxA(NULL, "CreateWindowA failed", "Error", MB_OK);
		return 0;
	}
	windowDeviceContext = GetDC(window);
	if (windowDeviceContext == NULL) {
		MessageBoxA(NULL, "GetDC failed", "Error", MB_OK);
		return 0;
	}
	// Create render context
	memset(&temp.pixelFormatData, 0, sizeof(temp.pixelFormatData));
	temp.pixelFormatData.nSize = sizeof(temp.pixelFormatData);
	temp.pixelFormatData.nVersion = 1;
	temp.pixelFormatData.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
	temp.pixelFormatData.iPixelType = PFD_TYPE_RGBA; //PFD_TYPE_COLORINDEX;
	temp.pixelFormatData.cColorBits = 32;
	temp.pixelFormatData.cDepthBits = 24;
	temp.pixelFormatData.cAlphaBits = 8;
	pixelFormat = ChoosePixelFormat(windowDeviceContext, &temp.pixelFormatData);
	if (pixelFormat == 0) {
		MessageBoxA(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
		return 0;
	}
	boolResult = SetPixelFormat(windowDeviceContext, pixelFormat, &temp.pixelFormatData);
	if (!boolResult) {
		MessageBoxA(NULL, "SetPixelFormat failed", "Error", MB_OK);
		return 0;
	}
	renderContext = wglCreateContext(windowDeviceContext);
	if (renderContext == NULL) {
		MessageBoxA(NULL, "wglCreateContext failed", "Error", MB_OK);
		return 0;
	}
	// Set render context
	boolResult = wglMakeCurrent(windowDeviceContext, renderContext);
	if (!boolResult) {
		MessageBoxA(NULL, "wglMakeCurrent failed", "Error", MB_OK);
		return 0;
	}
	// Show window
	ShowWindow(window, iCmdShow);
	UpdateWindow(window);
	// Message loop
	while (TRUE) {
		BOOL result;
		result = GetMessageA(&temp.windowMessage, NULL, 0, 0);
		if (result == 0) {
			break;
		}
		if (result == -1) {
			MessageBoxA(NULL, "GetMessageA failed", "Error", MB_OK);
			return 0;
		}
		TranslateMessage(&temp.windowMessage);
		DispatchMessageA(&temp.windowMessage);
	}
}
