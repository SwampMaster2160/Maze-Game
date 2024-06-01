#include <gl/GL.h>

#include "main.h"

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
						if (tileFlags & TILE_FLAGS_WALL)
						{
							drawNorth = northTile != TILE_NULL && (!(TILE_INFOS[northTile].flags & TILE_FLAGS_WALL));
							drawEast = eastTile != TILE_NULL && (!(TILE_INFOS[eastTile].flags & TILE_FLAGS_WALL));
							drawSouth = southTile != TILE_NULL && (!(TILE_INFOS[southTile].flags & TILE_FLAGS_WALL));
							drawWest = westTile != TILE_NULL && (!(TILE_INFOS[westTile].flags & TILE_FLAGS_WALL));
						}
						if (!(tileFlags & TILE_FLAGS_WALL))
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