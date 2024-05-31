#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
#pragma comment(lib, "src/opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <math.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
WINGDIAPI void glGenTextures(GLsizei n, GLuint *textures);
WINGDIAPI void glBindTexture(GLenum target, GLuint texture);

// Based on https://github.com/vbsw/opengl-win32-example/blob/master/Main.cpp
// For Microsoft Visual C++ 4.0 for Windows versions 95 - 11

typedef struct tagClassExtraData
{
	WORD windowWidth;
	WORD windowHeight;
	WORD windowWidthBeforeFullscreen;
	WORD windowHeightBeforeFullscreen;
	SHORT windowXBeforeFullscreen;
	SHORT windowYBeforeFullscreen;
	int windowShowStateBeforeFullscreen;
	float cameraRotation;
	DWORD lastTime;
	BOOL isFullscreen;
	GLuint texture;
	//BITMAP bitmap;
} ClassExtraData;

const float PI = 3.14159265358979323846;
const DWORD WINDOW_STYLE_WINDOWED = WS_OVERLAPPEDWINDOW;
const DWORD WINDOW_STYLE_FULLSCREEN = WS_VISIBLE;

const BYTE ROOM[16][16] = {
	{1, 2, 3, 4, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
};

//void drawCube(float x, float y, float z) {
//	float north = y + 0.5;
//	float east = x + 0.5;
//	float south = y - 0.5;
//	float west = x - 0.5;
//	float top = z + 0.5;
//	float bottom = z - 0.5;
//	// North
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(east, north, top); // Top left
//	glColor3f(0.0f, 1.0f, 0.0f); // Green
//	glVertex3f(east, north, bottom); // Bottom left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(west, north, bottom); // Bottom right
//
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(east, north, top); // Top left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(west, north, bottom); // Bottom right
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//	glVertex3f(west, north, top); // Top right
//	// East
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(east, south, top); // Top left
//	glColor3f(0.0f, 1.0f, 0.0f); // Green
//	glVertex3f(east, south, bottom); // Bottom left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, north, bottom); // Bottom right
//
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(east, south, top); // Top left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, north, bottom); // Bottom right
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//	glVertex3f(east, north, top); // Top right
//	// South
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, south, top); // Top left
//	glColor3f(0.0f, 1.0f, 0.0f); // Green
//	glVertex3f(west, south, bottom); // Bottom left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, south, bottom); // Bottom right
//
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, south, top); // Top left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, south, bottom); // Bottom right
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//	glVertex3f(east, south, top); // Top right
//	// West
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, north, top); // Top left
//	glColor3f(0.0f, 1.0f, 0.0f); // Green
//	glVertex3f(west, north, bottom); // Bottom left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(west, south, bottom); // Bottom right
//
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, north, top); // Top left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(west, south, bottom); // Bottom right
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//	glVertex3f(west, south, top); // Top right
//	// Top
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, north, top); // Top left
//	glColor3f(0.0f, 1.0f, 0.0f); // Green
//	glVertex3f(west, south, top); // Bottom left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, south, top); // Bottom right
//
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, north, top); // Top left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, south, top); // Bottom right
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//	glVertex3f(east, north, top); // Top right
//	// Bottom
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, north, bottom); // Top left
//	glColor3f(0.0f, 1.0f, 0.0f); // Green
//	glVertex3f(west, south, bottom); // Bottom left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, south, bottom); // Bottom right
//
//	glColor3f(1.0f, 0.0f, 0.0f); // Red
//	glVertex3f(west, north, bottom); // Top left
//	glColor3f(0.0f, 0.0f, 1.0f); // Blue
//	glVertex3f(east, south, bottom); // Bottom right
//	glColor3f(1.0f, 1.0f, 0.0f); // Yellow
//	glVertex3f(east, north, bottom); // Top right
//}
const BYTE BITS[52] =
{
	255, 0, 0, 0, 255, 0, 255, 255, 255, 255, 255, 255,
	0, 0, 255, 255, 255, 0, 255, 255, 255, 255, 255, 255,
	255, 0, 0, 127, 0, 0, 0, 255, 0, 0, 255, 0,
	127, 0, 0, 255, 0, 0, 0, 255, 0, 0, 255, 0,
};
//const BYTE BITS2[16] = {255, 0, 0, 127, 127, 127, 0, 0, 190, 190, 190, 255, 127, 255, 0};

static LRESULT CALLBACK windowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
{
	ClassExtraData *classExtraData;
	classExtraData = (ClassExtraData *)GetClassLong(window, 0);
	if (classExtraData == NULL)
	{
		return DefWindowProc(window, message, wParam, lParam);
	}
	switch (message)
	{
	case WM_PAINT:
		{
			UINT width = classExtraData->windowWidth;
			UINT height = classExtraData->windowHeight;
			PAINTSTRUCT paintStruct;
			int x;

			glBindTexture(GL_TEXTURE_2D, classExtraData->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, classExtraData->bitmap.bmWidth, classExtraData->bitmap.bmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, classExtraData->bitmap.bmBits);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 4, 4, 0, GL_RGB, GL_UNSIGNED_BYTE, BITS);

			glViewport(0, 0, width, height);
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			gluPerspective(45, (float)width/(float)height, 0.1, 100);
			gluLookAt(3 * cos(classExtraData->cameraRotation), 3 * sin(classExtraData->cameraRotation), 2, 0, 0, 0, 0, 0, 1);

			glClear(GL_COLOR_BUFFER_BIT);
			glBegin(GL_TRIANGLES);

			for (x = 0; x < 16; x++)
			{
				int y;
				for (y = 0; y < 16; y++)
				{
					BYTE tile = ROOM[x][y];
					if (!tile) continue;

					{
						float north = y + 0.5;
						float east = x + 0.5;
						float south = y - 0.5;
						float west = x - 0.5;
						float bottom = -0.5;
						float textureLeft = (tile + 1) % 2 * 0.5;
						float textureRight = textureLeft + 0.5;
						float textureTop = 1 - ((tile + 1) / 2 * 0.5);
						float textureBottom = textureTop - 0.5;
						
						glTexCoord2f(textureLeft, textureTop);
						glVertex3f(west, north, bottom); // Top left
						glTexCoord2f(textureLeft, textureBottom);
						glVertex3f(west, south, bottom); // Bottom left
						glTexCoord2f(textureRight, textureBottom);
						glVertex3f(east, south, bottom); // Bottom right
						glTexCoord2f(textureLeft, textureTop);
						glVertex3f(west, north, bottom); // Top left
						glTexCoord2f(textureRight, textureBottom);
						glVertex3f(east, south, bottom); // Bottom right
						glTexCoord2f(textureRight, textureTop);
						glVertex3f(east, north, bottom); // Top right
					}
				}
			}

			glEnd();
			glFlush();

			BeginPaint(window, &paintStruct);
			SwapBuffers(paintStruct.hdc);
			EndPaint(window, &paintStruct);
			break;
		}
	case WM_CLOSE:
		DestroyWindow(window);
		PostQuitMessage(0);
		break;
	case WM_SIZE:
		classExtraData->windowWidth = LOWORD(lParam);
		classExtraData->windowHeight = HIWORD(lParam);
		break;
	case WM_TIMER:
		{
			DWORD time = GetTickCount();
			DWORD deltaTime = time - classExtraData->lastTime;
			if (deltaTime < 10) break;
			classExtraData->cameraRotation += (float)deltaTime / 1000 / 1;
			RedrawWindow(window, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
			classExtraData->lastTime = time;
			break;
		}
	case WM_KEYUP:
		switch (wParam)
		{
		case VK_F11:
			classExtraData->isFullscreen = !classExtraData->isFullscreen;
			if (classExtraData->isFullscreen)
			{
				RECT windowRect;
				BOOL result = GetWindowRect(window, &windowRect);
				int screenWidth = GetSystemMetrics(SM_CXSCREEN);
				int screenHeight = GetSystemMetrics(SM_CYSCREEN);
				if (!result) break;
				classExtraData->windowWidthBeforeFullscreen = windowRect.right - windowRect.left;
				classExtraData->windowHeightBeforeFullscreen = windowRect.bottom - windowRect.top;
				classExtraData->windowXBeforeFullscreen = windowRect.left;
				classExtraData->windowYBeforeFullscreen = windowRect.top;
				classExtraData->windowShowStateBeforeFullscreen = SW_SHOW;
				if (IsZoomed(window)) classExtraData->windowShowStateBeforeFullscreen = SW_SHOWMAXIMIZED;
				SetWindowLongA(window, GWL_STYLE, WINDOW_STYLE_FULLSCREEN);
				SetWindowPos(window, HWND_TOPMOST, 0, 0, screenWidth, screenHeight, SWP_SHOWWINDOW);
				break;
			}
			SetWindowLongA(window, GWL_STYLE, WINDOW_STYLE_WINDOWED);
			SetWindowPos
			(
				window, HWND_TOPMOST,
				classExtraData->windowXBeforeFullscreen,
				classExtraData->windowYBeforeFullscreen,
				classExtraData->windowWidthBeforeFullscreen,
				classExtraData->windowHeightBeforeFullscreen,
				SWP_HIDEWINDOW
			);
			ShowWindow(window, classExtraData->windowShowStateBeforeFullscreen);
			break;
		case VK_ESCAPE:
			DestroyWindow(window);
			PostQuitMessage(0);
			break;
		}
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
	int intResult;
	HGLRC renderContext;
	ClassExtraData classExtraData;
	UINT timer;
	// Register window class
	{
		WNDCLASSA windowClassData;
		memset(&windowClassData, 0, sizeof(windowClassData));
		windowClassData.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		windowClassData.lpfnWndProc = (WNDPROC)windowProcess;
		windowClassData.cbClsExtra = sizeof(LONG);
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
	window = CreateWindowA((LPCSTR)windowClass, "Windows OpenGL", WINDOW_STYLE_WINDOWED, 100, 100, 320, 240, NULL, NULL, instance, NULL);
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
	SetClassLongA(window, 0, (LONG)&classExtraData);
	// Create render context
	{
		PIXELFORMATDESCRIPTOR pixelFormatData;
		memset(&pixelFormatData, 0, sizeof(pixelFormatData));
		pixelFormatData.nSize = sizeof(pixelFormatData);
		pixelFormatData.nVersion = 1;
		pixelFormatData.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
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
	//
	OutputDebugStringA("A");
	{
		//HBITMAP hBitmap = LoadBitmapA(instance, "TEST");
		////BITMAP bitmap;
		//GLuint tex[2];
		//if (hBitmap == NULL)
		//{
		//	MessageBoxA(NULL, "LoadBitmapA failed", "Error", MB_OK);
		//	return 0;
		//}
		//intResult = GetObjectA(hBitmap, sizeof(BITMAP), &classExtraData.bitmap);
		//if (intResult == 0)
		//{
		//	MessageBoxA(NULL, "GetObjectA failed", "Error", MB_OK);
		//	return 0;
		//}
		//glTexImage2D
		//glTexImage2D
		glGenTextures(1, &classExtraData.texture);
		if (classExtraData.texture == 0)
		{
			MessageBoxA(NULL, "glGenTextures failed", "Error", MB_OK);
			return 0;
		}
		//glBindTexture(GL_TEXTURE_2D, tex);
		//classExtraData.tex = tex;
		//if (((BYTE *)bitmap.bmBits)[0] != 85) {
		//	MessageBoxA(NULL, "A failed", "Error", MB_OK);
		//	return 0;
		//}
		//glBindTexture(GL_TEXTURE_2D, 0);
	}
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
}
