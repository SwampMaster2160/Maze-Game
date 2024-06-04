#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <math.h>

#include "main.h"

// For Microsoft Visual C++ 4.0 for Windows versions 95 - 11

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR szCmdLine, int iCmdShow)
{
	MGERROR result = Main(instance, prevInstance, szCmdLine, iCmdShow);
	return DisplayError(result);
}

int Main(HINSTANCE instance, HINSTANCE prevInstance, PSTR szCmdLine, int iCmdShow)
{
	ClassExtraData classExtraData;
	ATOM windowClass;
	HWND window;
	HDC windowDeviceContext;
	int pixelFormat;
	BOOL boolResult;
	int intResult;
	HGLRC renderContext;
	UINT timer;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	BYTE *textures;
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
	if (windowClass == 0) return MGERROR_REGISTER_CLASS;
	// Create window
	{
		int windowWidth = WINDOW_WIDTH;
		int windowHeight = WINDOW_HEIGHT;
		if (screenWidth < 800 || screenHeight < 600)
		{
			windowWidth /= 2;
			windowHeight /= 2;
		}
		window = CreateWindowA((LPCSTR)windowClass, "Maze Game", WINDOW_STYLE_WINDOWED, (screenWidth - windowWidth) / 2, (screenHeight - windowHeight) / 2, windowWidth, windowHeight, NULL, NULL, instance, NULL);
	}
	if (window == NULL) return MGERROR_CREATE_WINDOW;
	windowDeviceContext = GetDC(window);
	if (windowDeviceContext == NULL) return MGERROR_GET_WINDOW_DC;
	// Create timer
	timer = SetTimer(window, RENDER_TIMER, 1000 / FPS, NULL);
	if (timer == 0) return MGERROR_CREATE_TIMER;
	timer = SetTimer(window, TICK_TIMER, 1000 / TPS, NULL);
	if (timer == 0) return MGERROR_CREATE_TIMER;
	// Set window extra data
	classExtraData.cameraRotation = PI * 1.5;
	classExtraData.playerX = 1;
	classExtraData.playerY = -1;
	classExtraData.isFullscreen = FALSE;
	classExtraData.lastTime = GetTickCount();
	classExtraData.cursorX = 0;
	classExtraData.didSetCursorPosLast = FALSE;
	classExtraData.upPressed = FALSE;
	classExtraData.downPressed = FALSE;
	classExtraData.leftPressed = FALSE;
	classExtraData.rightPressed = FALSE;
	SetClassLongA(window, 0, (LONG)&classExtraData);
	// Create render context
	{
		PIXELFORMATDESCRIPTOR pixelFormatData;
		memset(&pixelFormatData, 0, sizeof(pixelFormatData));
		pixelFormatData.nSize = sizeof(pixelFormatData);
		pixelFormatData.nVersion = 1;
		pixelFormatData.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
		pixelFormatData.iPixelType = PFD_TYPE_RGBA;
		pixelFormatData.cColorBits = 24;
		pixelFormatData.cDepthBits = 8;
		pixelFormatData.cAlphaBits = 0;
		pixelFormat = ChoosePixelFormat(windowDeviceContext, &pixelFormatData);
		if (pixelFormat == 0) return MGERROR_CREATE_PIXEL_FROMAT;
		boolResult = SetPixelFormat(windowDeviceContext, pixelFormat, &pixelFormatData);
	}
	if (!boolResult) return MGERROR_SET_PIXEL_FROMAT;
	renderContext = wglCreateContext(windowDeviceContext);
	if (renderContext == NULL) return MGERROR_CREATE_OPENGL_RENDER_CONTEXT;
	// Set render context
	boolResult = wglMakeCurrent(windowDeviceContext, renderContext);
	if (!boolResult) return MGERROR_MAKE_OPENGL_RENDER_CONTEXT_CURRENT;
	// Load texture sheet from bitmap resource
	{
		HBITMAP hBitmap;
		BITMAP bitmap;
		DWORD y;
		// Load bitmap resource
		hBitmap = LoadImageA(instance, "TEXTURES", IMAGE_BITMAP, 0, 0, LR_CREATEDIBSECTION | LR_DEFAULTSIZE);
		if (hBitmap == NULL) return MGERROR_GET_TEXTURES_BITMAP_RESOURCE;
		intResult = GetObjectA(hBitmap, sizeof(BITMAP), &bitmap);
		if (intResult == 0) return MGERROR_LOAD_TEXTURES_BITMAP_RESOURCE;
		// Check that the bitmap has the right properties
		if (bitmap.bmBitsPixel != 24 || bitmap.bmPlanes != 1 || bitmap.bmType != 0 || bitmap.bmBits == NULL) return MGERROR_TEXTURES_BITMAP_RESOURCE_BAD_IMAGE_FROMAT;
		// Allocate memory for texture sheet
		textures = malloc(bitmap.bmWidth * bitmap.bmHeight * 3 * sizeof(BYTE));
		if (textures == NULL) return MGERROR_ALLOCATE_MEMORY_FOR_TEXTURES;
		// Copy the pixels from the bitmap to the texture sheet
		for (y = 0; y < bitmap.bmHeight; y++)
		{
			DWORD x;
			for (x = 0; x < bitmap.bmWidth; x++)
			{
				DWORD pixelIndex = (x + y * bitmap.bmWidth) * 3;
				textures[pixelIndex] = ((BYTE *)bitmap.bmBits)[pixelIndex + 2];
				textures[pixelIndex + 1] = ((BYTE *)bitmap.bmBits)[pixelIndex + 1];
				textures[pixelIndex + 2] = ((BYTE *)bitmap.bmBits)[pixelIndex];
			}
		}
		// Set the rendering image to the image we loaded from the bitmap resource
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, bitmap.bmWidth, bitmap.bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, textures);
		// Delete bitmap
		boolResult = DeleteObject(hBitmap);
		if (!boolResult) return MGERROR_TEXTURES_BITMAP_RESOURCE_DELETE;
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
		if (result == -1) return MGERROR_GET_MESSAGE;
		TranslateMessage(&windowMessage);
		DispatchMessageA(&windowMessage);
	}
	// Cleanup
	wglMakeCurrent(NULL, NULL);
	KillTimer(window, timer);
	free(textures);

	return MGERROR_NONE;
}

#include "window_callback.c"
#include "data.c"
#include "error.c"