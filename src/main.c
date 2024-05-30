#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <math.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>

// Based on https://github.com/vbsw/opengl-win32-example/blob/master/Main.cpp
// For Microsoft Visual C++ 4.0 for Windows versions 95 - 11

const float PI = 3.14159265358979323846;

void drawCube(float x, float y, float z) {
	float north = y + 0.5;
	float east = x + 0.5;
	float south = y - 0.5;
	float west = x - 0.5;
	float top = z + 0.5;
	float bottom = z - 0.5;
	// North
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(east, north, top); // Top left
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(east, north, bottom); // Bottom left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(west, north, bottom); // Bottom right

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(east, north, top); // Top left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(west, north, bottom); // Bottom right
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(west, north, top); // Top right
	// East
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(east, south, top); // Top left
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(east, south, bottom); // Bottom left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, north, bottom); // Bottom right

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(east, south, top); // Top left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, north, bottom); // Bottom right
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(east, north, top); // Top right
	// South
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, south, top); // Top left
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(west, south, bottom); // Bottom left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, south, bottom); // Bottom right

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, south, top); // Top left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, south, bottom); // Bottom right
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(east, south, top); // Top right
	// West
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, north, top); // Top left
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(west, north, bottom); // Bottom left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(west, south, bottom); // Bottom right

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, north, top); // Top left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(west, south, bottom); // Bottom right
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(west, south, top); // Top right
	// Top
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, north, top); // Top left
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(west, south, top); // Bottom left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, south, top); // Bottom right

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, north, top); // Top left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, south, top); // Bottom right
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(east, north, top); // Top right
	// Bottom
	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, north, bottom); // Top left
	glColor3f(0.0f, 1.0f, 0.0f); // Green
	glVertex3f(west, south, bottom); // Bottom left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, south, bottom); // Bottom right

	glColor3f(1.0f, 0.0f, 0.0f); // Red
	glVertex3f(west, north, bottom); // Top left
	glColor3f(0.0f, 0.0f, 1.0f); // Blue
	glVertex3f(east, south, bottom); // Bottom right
	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
	glVertex3f(east, north, bottom); // Top right
}

static LRESULT CALLBACK windowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_PAINT:
		{
			UINT width = 320;
			UINT height = 240;
			//float zoomFactor = ((float)width / (float)height) / 1;
			PAINTSTRUCT paintStruct;

			glEnable(GL_DEPTH_TEST);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45, (float)width/(float)height, 0.1, 100);
			gluLookAt(3, -3, 2, 0, 0, 0, 0, 0, 1);

			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_TRIANGLES);

			drawCube(0, 0, 0);

			drawCube(0, 3, 0);

			glEnd();
			glFlush();

			BeginPaint(window, &paintStruct);
			EndPaint(window, &paintStruct);
			break;
		}
	case WM_CLOSE:
		DestroyWindow(window);
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		{
			UINT width = LOWORD(lParam);
			UINT height = HIWORD(lParam);
		}
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
	int pixelFormat;
	BOOL boolResult;
	HGLRC renderContext;
	// Register window class
	{
		WNDCLASSA windowClassData;
		memset(&windowClassData, 0, sizeof(windowClassData));
		windowClassData.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		windowClassData.lpfnWndProc = (WNDPROC)windowProcess;
		windowClassData.cbClsExtra = 0;
		windowClassData.cbWndExtra = 0;
		windowClassData.hInstance = instance;
		windowClassData.hIcon = LoadIcon(NULL, IDI_WINLOGO);
		windowClassData.hCursor = LoadCursor(NULL, IDC_ARROW);
		windowClassData.hbrBackground = NULL;
		windowClassData.lpszMenuName = NULL;
		windowClassData.lpszClassName = "Windows OpenGL";
		windowClass = RegisterClassA(&windowClassData);
	}
	if (windowClass == 0)
	{
		MessageBoxA(NULL, "RegisterClassA failed", "Error", MB_OK);
		return 0;
	}
	// Create window
	window = CreateWindowA((LPCSTR)windowClass, "Windows OpenGL", WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, 100, 100, 320, 240, NULL, NULL, instance, NULL);
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
	// Create render context
	{
		PIXELFORMATDESCRIPTOR pixelFormatData;
		memset(&pixelFormatData, 0, sizeof(pixelFormatData));
		pixelFormatData.nSize = sizeof(pixelFormatData);
		pixelFormatData.nVersion = 1;
		pixelFormatData.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL;
		pixelFormatData.iPixelType = PFD_TYPE_RGBA; //PFD_TYPE_COLORINDEX;
		pixelFormatData.cColorBits = 32;
		pixelFormatData.cDepthBits = 24;
		pixelFormatData.cAlphaBits = 8;
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
}
