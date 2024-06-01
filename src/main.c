#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <math.h>
#include <stdio.h>

#include "main.h"
#include "window_callback.c"
#include "data.c"

// For Microsoft Visual C++ 4.0 for Windows versions 95 - 11

//const float PI = 3.14159265358979323846;

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR szCmdLine, int iCmdShow)
{
	ATOM windowClass;
	HWND window;
	HDC windowDeviceContext;
	int pixelFormat;
	BOOL boolResult;
	int intResult;
	HGLRC renderContext;
	ClassExtraData classExtraData;
	UINT timer;
	// Register window class
	{
		WNDCLASSA windowClassData;
		memset(&windowClassData, 0, sizeof(windowClassData));
		windowClassData.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		windowClassData.lpfnWndProc = (WNDPROC)WindowProcess;
		windowClassData.cbClsExtra = sizeof(LONG);
		windowClassData.hInstance = instance;
		windowClassData.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		windowClassData.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClassData.hbrBackground = NULL;
		windowClassData.lpszMenuName = NULL;
		windowClassData.lpszClassName = "Maze Game";
		windowClass = RegisterClassA(&windowClassData);
	}
	if (windowClass == 0)
	{
		MessageBoxA(NULL, "RegisterClassA failed", "Error", MB_OK);
		return 0;
	}
	// Create window
	window = CreateWindowA((LPCSTR)windowClass, "Maze Game", WINDOW_STYLE_WINDOWED, 100, 100, 320, 240, NULL, NULL, instance, NULL);
	if (window == NULL)
	{
		MessageBoxA(NULL, "CreateWindowA failed", "Error", MB_OK);
		return 0;
	}
	windowDeviceContext = GetDC(window);
	if (windowDeviceContext == NULL)
	{
		MessageBoxA(NULL, "GetDC failed", "Error", MB_OK);
		return 0;
	}
	// Create timer
	timer = SetTimer(window, 0, 1000 / 60, NULL);
	if (timer == 0)
	{
		MessageBoxA(NULL, "SetTimer failed", "Error", MB_OK);
		return 0;
	}
	// Set window extra data
	classExtraData.cameraRotation = 0;
	classExtraData.isFullscreen = FALSE;
	classExtraData.lastTime = GetTickCount();
	classExtraData.cursorX = 0;
	classExtraData.didSetCursorPosLast = FALSE;
	SetClassLongA(window, 0, (LONG)&classExtraData);
	// Create render context
	{
		PIXELFORMATDESCRIPTOR pixelFormatData;
		memset(&pixelFormatData, 0, sizeof(pixelFormatData));
		pixelFormatData.nSize = sizeof(pixelFormatData);
		pixelFormatData.nVersion = 1;
		pixelFormatData.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelFormatData.iPixelType = PFD_TYPE_RGBA; //PFD_TYPE_COLORINDEX;
		pixelFormatData.cColorBits = 24;
		pixelFormatData.cDepthBits = 24;
		pixelFormatData.cAlphaBits = 0;
		pixelFormat = ChoosePixelFormat(windowDeviceContext, &pixelFormatData);
		if (pixelFormat == 0)
		{
			MessageBoxA(NULL, "ChoosePixelFormat failed", "Error", MB_OK);
			return 0;
		}
		boolResult = SetPixelFormat(windowDeviceContext, pixelFormat, &pixelFormatData);
	}
	if (!boolResult)
	{
		MessageBoxA(NULL, "SetPixelFormat failed", "Error", MB_OK);
		return 0;
	}
	renderContext = wglCreateContext(windowDeviceContext);
	if (renderContext == NULL)
	{
		MessageBoxA(NULL, "wglCreateContext failed", "Error", MB_OK);
		return 0;
	}
	// Set render context
	boolResult = wglMakeCurrent(windowDeviceContext, renderContext);
	if (!boolResult)
	{
		MessageBoxA(NULL, "wglMakeCurrent failed", "Error", MB_OK);
		return 0;
	}
	// Allocate memory for texture sheet
	classExtraData.textures = malloc(256 * 256 * 3 * sizeof(BYTE));
	if (classExtraData.textures == NULL)
	{
		MessageBoxA(NULL, "malloc failed", "Error", MB_OK);
		return 0;
	}
	// Load texture sheet from bitmap resource
	{
		HBITMAP hBitmap;
		BITMAP bitmap;
		DWORD y;
		// Load bitmap resource
		hBitmap = LoadImageA(instance, "TEXTURES", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		if (hBitmap == NULL)
		{
			MessageBoxA(NULL, "LoadBitmapA failed", "Error", MB_OK);
			return 0;
		}
		intResult = GetObjectA(hBitmap, sizeof(BITMAP), &bitmap);
		if (intResult == 0)
		{
			MessageBoxA(NULL, "GetObjectA failed", "Error", MB_OK);
			return 0;
		}
		// Check that the bitmap has the right properties
		if (bitmap.bmWidth != 256 || bitmap.bmHeight != 256 || bitmap.bmBitsPixel != 24 || bitmap.bmPlanes != 1 || bitmap.bmType != 0 || bitmap.bmBits == NULL)
		{
			MessageBoxA(NULL, "Bad image format", "Error", MB_OK);
			return 0;
		}
		// Copy the pixels from the bitmap to the texture sheet
		for (y = 0; y < 256; y++)
		{
			DWORD x;
			for (x = 0; x < 256; x++)
			{
				DWORD pixelIndex = (x + y * 256) * 3;
				classExtraData.textures[pixelIndex] = ((BYTE *)bitmap.bmBits)[pixelIndex + 2];
				classExtraData.textures[pixelIndex + 1] = ((BYTE *)bitmap.bmBits)[pixelIndex + 1];
				classExtraData.textures[pixelIndex + 2] = ((BYTE *)bitmap.bmBits)[pixelIndex];
			}
		}
		// Delete bitmap
		boolResult = DeleteObject(hBitmap);
		if (!boolResult)
		{
			MessageBoxA(NULL, "DeleteObject failed", "Error", MB_OK);
			return 0;
		}
	}
	// Show window
	ShowWindow(window, iCmdShow);
	UpdateWindow(window);
	// Message loop
	while (TRUE)
	{
		MSG windowMessage;
		BOOL result;
		result = GetMessageA(&windowMessage, NULL, 0, 0);
		if (result == 0) break;
		if (result == -1)
		{
			MessageBoxA(NULL, "GetMessageA failed", "Error", MB_OK);
			return 0;
		}
		TranslateMessage(&windowMessage);
		DispatchMessageA(&windowMessage);
	}
	// Cleanup
	wglMakeCurrent(NULL, NULL);
	KillTimer(window, timer);
	free(classExtraData.textures);
}
