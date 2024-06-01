#pragma comment(lib, "user32.lib")
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "opengl32.lib")
//#pragma comment(lib, "src/opengl32.lib")
#pragma comment(lib, "glu32.lib")
#include <math.h>
#include <stdio.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
//WINGDIAPI void glGenTextures(GLsizei n, GLuint *textures);
//void glBindTexture(GLenum target, GLuint texture);

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
	BYTE *textures;
} ClassExtraData;

const float PI = 3.14159265358979323846;
const DWORD WINDOW_STYLE_WINDOWED = WS_OVERLAPPEDWINDOW;
const DWORD WINDOW_STYLE_FULLSCREEN = WS_VISIBLE;

enum _TEXTURES
{
	TEXTURE_TEST,
	TEXTURE_WOOD_PLANKS,
	TEXTURE_STONE_BRICKS,
};

enum _TILES
{
	TILE_NULL,
	TILE_TEST,
	TILE_STONE_BRICK_WALL,
	TILE_WOOD_PLANKS,
	TILE_COUNT,
};

enum _TILE_INFO_FLAGS
{
	TILE_INFO_FLAGS_WALL = 1,
};

typedef struct _TILE_INFO
{
	BYTE texture;
	BYTE flags;
} TILE_INFO;

const TILE_INFO TILE_INFOS[TILE_COUNT] =
{
	{0, 0},
	{TEXTURE_TEST, 0},
	{TEXTURE_STONE_BRICKS, TILE_INFO_FLAGS_WALL},
	{TEXTURE_WOOD_PLANKS, 0},
};

const BYTE ROOM[16][16] = {
	{TILE_TEST,             TILE_STONE_BRICK_WALL, TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_STONE_BRICK_WALL, TILE_WOOD_PLANKS,      TILE_STONE_BRICK_WALL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_STONE_BRICK_WALL, TILE_WOOD_PLANKS,      TILE_STONE_BRICK_WALL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_STONE_BRICK_WALL, TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
	{TILE_NULL,             TILE_NULL,             TILE_NULL,             TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL, TILE_NULL},
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
			int y;
			// Filter mode	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			// Other
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			// Camera
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, width, height);
			gluPerspective(45, (float)width/(float)height, 0.1, 100);
			gluLookAt(3 * cos(classExtraData->cameraRotation), 3 * sin(classExtraData->cameraRotation), 2, 0, 0, 0, 0, 0, 1);
			// Set texture to draw with
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, classExtraData->textures);
			// Start
			glBegin(GL_TRIANGLES);
			// Draw each tile
			for (y = 0; y < 16; y++)
			{
				int x;
				for (x = 0; x < 16; x++)
				{
					// Get tile
					BYTE tile = ROOM[y][x];
					BYTE northTile = TILE_NULL;
					BYTE eastTile = TILE_NULL;
					BYTE southTile = TILE_NULL;
					BYTE westTile = TILE_NULL;
					TILE_INFO *tileInfo = &TILE_INFOS[tile];
					BYTE texture = tileInfo->texture;
					BYTE tileFlags = tileInfo->flags;
					// Do not render null tiles
					if (tile == TILE_NULL) continue;
					// Get tiles around tile
					if (y != 0) northTile = ROOM[y - 1][x];
					if (x != 0) westTile = ROOM[y][x - 1];
					if (y != 15) southTile = ROOM[y + 1][x];
					if (x != 15) eastTile = ROOM[y][x + 1];

					{
						// Calculate tile positions
						float north = -y + 0.5;
						float east = x + 0.5;
						float south = -y - 0.5;
						float west = x - 0.5;
						float top = 0.5;
						float bottom = -0.5;
						// Calculate texture positions
						float textureLeft = texture % 16 * (1. / 16.);
						float textureRight = textureLeft + (1. / 16.);
						float textureTop = 1 - (texture / 16 * (1. / 16.));
						float textureBottom = textureTop - (1. / 16.);
						// Get which walls should be drawn
						BOOL drawNorth = FALSE;
						BOOL drawEast = FALSE;
						BOOL drawSouth = FALSE;
						BOOL drawWest = FALSE;
						BOOL drawTop = FALSE;
						BOOL drawBottom = FALSE;
						if (tileFlags & TILE_INFO_FLAGS_WALL)
						{
							drawNorth = northTile != TILE_NULL && (!(TILE_INFOS[northTile].flags & TILE_INFO_FLAGS_WALL));
							drawEast = eastTile != TILE_NULL && (!(TILE_INFOS[eastTile].flags & TILE_INFO_FLAGS_WALL));
							drawSouth = southTile != TILE_NULL && (!(TILE_INFOS[southTile].flags & TILE_INFO_FLAGS_WALL));
							drawWest = westTile != TILE_NULL && (!(TILE_INFOS[westTile].flags & TILE_INFO_FLAGS_WALL));
						}
						if (!(tileFlags & TILE_INFO_FLAGS_WALL))
						{
							drawTop = TRUE;
							drawBottom = TRUE;
						}
						// Draw sides
						if (drawTop)
						{
							// Top
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(textureLeft, textureBottom);
							glVertex3f(west, south, top); // Bottom left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(east, south, top); // Bottom right
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(east, south, top); // Bottom right
							glTexCoord2f(textureRight, textureTop);
							glVertex3f(east, north, top); // Top right
						}
						if (drawBottom)
						{
							// Bottom
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
						if (drawNorth)
						{
							// North
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(east, north, top); // Top left
							glTexCoord2f(textureLeft, textureBottom);
							glVertex3f(east, north, bottom); // Bottom left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(west, north, bottom); // Bottom right
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(east, north, top); // Top left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(west, north, bottom); // Bottom right
							glTexCoord2f(textureRight, textureTop);
							glVertex3f(west, north, top); // Top right
						}
						if (drawEast)
						{
							// East
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(east, south, top); // Top left
							glTexCoord2f(textureLeft, textureBottom);
							glVertex3f(east, south, bottom); // Bottom left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(east, north, bottom); // Bottom right
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(east, south, top); // Top left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(east, north, bottom); // Bottom right
							glTexCoord2f(textureRight, textureTop);
							glVertex3f(east, north, top); // Top right
						}
						if (drawSouth)
						{
							// South
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(west, south, top); // Top left
							glTexCoord2f(textureLeft, textureBottom);
							glVertex3f(west, south, bottom); // Bottom left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(east, south, bottom); // Bottom right
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(west, south, top); // Top left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(east, south, bottom); // Bottom right
							glTexCoord2f(textureRight, textureTop);
							glVertex3f(east, south, top); // Top right
						}
						if (drawWest)
						{
							// West
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(textureLeft, textureBottom);
							glVertex3f(west, north, bottom); // Bottom left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(west, south, bottom); // Bottom right
							glTexCoord2f(textureLeft, textureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(textureRight, textureBottom);
							glVertex3f(west, south, bottom); // Bottom right
							glTexCoord2f(textureRight, textureTop);
							glVertex3f(west, south, top); // Top right
						}
					}
				}
			}
			// End
			glEnd();
			glFlush();
			// Swap buffers
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
				DWORD outputPixelIndex = (x + y * 256) * 3;
				DWORD inputX = x;
				DWORD inputY = y;
				DWORD inputPixelIndex = (inputX + inputY * 256) * 3;
				classExtraData.textures[outputPixelIndex] = ((BYTE *)bitmap.bmBits)[inputPixelIndex + 2];
				classExtraData.textures[outputPixelIndex + 1] = ((BYTE *)bitmap.bmBits)[inputPixelIndex + 1];
				classExtraData.textures[outputPixelIndex + 2] = ((BYTE *)bitmap.bmBits)[inputPixelIndex];
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
