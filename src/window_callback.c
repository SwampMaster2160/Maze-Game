#include <gl/GL.h>
#include <math.h>

#include "main.h"

static LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam)
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
			float fadeAmount = 1;
			int y;
			// Get fade color
			switch (classExtraData->animation)
			{
			case ANIMATION_NULL:
				break;
			case ANIMATION_WARP_TO_BLACK:
				fadeAmount = 1. - classExtraData->animationTickCounter / (float)(TPS / 4);
				break;
			case ANIMATION_FADE_FROM_BLACK:
				fadeAmount = classExtraData->animationTickCounter / (float)(TPS / 2);
				break;
			}
			// Start
			// Filter mode	
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			// Other
			glEnable(GL_DEPTH_TEST);
			glEnable(GL_TEXTURE_2D);
			glClear(GL_DEPTH_BUFFER_BIT);
			glColor3f(fadeAmount, fadeAmount, fadeAmount);
			// Camera
			glMatrixMode(GL_PROJECTION);
			glLoadIdentity();
			glViewport(0, 0, width, height);
			gluPerspective(90, (float)width/(float)height, 0.05, 100);
			gluLookAt(classExtraData->playerX, classExtraData->playerY, 0, classExtraData->playerX + cos(classExtraData->cameraRotation), classExtraData->playerY + sin(classExtraData->cameraRotation), 0, 0, 0, 1);
			// Start
			glBegin(GL_TRIANGLES);
			// Draw each tile
			for (y = 0; y < 16; y++)
			{
				int x;
				for (x = 0; x < 16; x++)
				{
					// Get tile
					const TILE *roomTiles = ROOM_INFOS[classExtraData->playerRoom].tiles;
					TILE tile = roomTiles[x + y * 16];
					TILE northTile = TILE_NULL;
					TILE eastTile = TILE_NULL;
					TILE southTile = TILE_NULL;
					TILE westTile = TILE_NULL;
					TILE_INFO tileInfo = TILE_INFOS[tile];
					TEXTURE floorEastWestTexture = tileInfo.floorEastWestTexture;
					TEXTURE ceilingNorthSouthTexture = tileInfo.ceilingNorthSouthTexture;
					BYTE tileFlags = tileInfo.flags;
					// Do not render null tiles
					if (tile == TILE_NULL) continue;
					// Get tiles around tile
					if (y != 0) northTile = roomTiles[x + (y - 1) * 16];
					if (x != 0) westTile = roomTiles[x - 1 + y * 16];
					if (y != 15) southTile = roomTiles[x + (y + 1) * 16];
					if (x != 15) eastTile = roomTiles[x + 1 + y * 16];

					{
						// Calculate tile positions
						float north = -y + 0.5;
						float east = x + 0.5;
						float south = -y - 0.5;
						float west = x - 0.5;
						float top = 0.5;
						float bottom = -0.5;
						// Calculate texture positions
						float floorEastWestTextureLeft = floorEastWestTexture % 16 * (1. / 16.);
						float floorEastWestTextureRight = floorEastWestTextureLeft + (1. / 16.);
						float floorEastWestTextureTop = 1 - (floorEastWestTexture / 16 * (1. / 16.));
						float floorEastWestTextureBottom = floorEastWestTextureTop - (1. / 16.);
						float ceilingNorthSouthTextureLeft = ceilingNorthSouthTexture % 16 * (1. / 16.);
						float ceilingNorthSouthTextureRight = ceilingNorthSouthTextureLeft + (1. / 16.);
						float ceilingNorthSouthTextureTop = 1 - (ceilingNorthSouthTexture / 16 * (1. / 16.));
						float ceilingNorthSouthTextureBottom = ceilingNorthSouthTextureTop - (1. / 16.);
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
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureBottom);
							glVertex3f(west, south, top); // Bottom left
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureBottom);
							glVertex3f(east, south, top); // Bottom right
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureBottom);
							glVertex3f(east, south, top); // Bottom right
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureTop);
							glVertex3f(east, north, top); // Top right
						}
						if (drawBottom)
						{
							// Bottom
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureTop);
							glVertex3f(west, north, bottom); // Top left
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureBottom);
							glVertex3f(west, south, bottom); // Bottom left
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureBottom);
							glVertex3f(east, south, bottom); // Bottom right
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureTop);
							glVertex3f(west, north, bottom); // Top left
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureBottom);
							glVertex3f(east, south, bottom); // Bottom right
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureTop);
							glVertex3f(east, north, bottom); // Top right
						}
						if (drawNorth)
						{
							// North
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureTop);
							glVertex3f(east, north, top); // Top left
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureBottom);
							glVertex3f(east, north, bottom); // Bottom left
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureBottom);
							glVertex3f(west, north, bottom); // Bottom right
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureTop);
							glVertex3f(east, north, top); // Top left
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureBottom);
							glVertex3f(west, north, bottom); // Bottom right
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureTop);
							glVertex3f(west, north, top); // Top right
						}
						if (drawEast)
						{
							// East
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureTop);
							glVertex3f(east, south, top); // Top left
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureBottom);
							glVertex3f(east, south, bottom); // Bottom left
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureBottom);
							glVertex3f(east, north, bottom); // Bottom right
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureTop);
							glVertex3f(east, south, top); // Top left
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureBottom);
							glVertex3f(east, north, bottom); // Bottom right
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureTop);
							glVertex3f(east, north, top); // Top right
						}
						if (drawSouth)
						{
							// South
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureTop);
							glVertex3f(west, south, top); // Top left
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureBottom);
							glVertex3f(west, south, bottom); // Bottom left
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureBottom);
							glVertex3f(east, south, bottom); // Bottom right
							glTexCoord2f(ceilingNorthSouthTextureLeft, ceilingNorthSouthTextureTop);
							glVertex3f(west, south, top); // Top left
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureBottom);
							glVertex3f(east, south, bottom); // Bottom right
							glTexCoord2f(ceilingNorthSouthTextureRight, ceilingNorthSouthTextureTop);
							glVertex3f(east, south, top); // Top right
						}
						if (drawWest)
						{
							// West
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureBottom);
							glVertex3f(west, north, bottom); // Bottom left
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureBottom);
							glVertex3f(west, south, bottom); // Bottom right
							glTexCoord2f(floorEastWestTextureLeft, floorEastWestTextureTop);
							glVertex3f(west, north, top); // Top left
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureBottom);
							glVertex3f(west, south, bottom); // Bottom right
							glTexCoord2f(floorEastWestTextureRight, floorEastWestTextureTop);
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
		{
			classExtraData->windowWidth = LOWORD(lParam);
			classExtraData->windowHeight = HIWORD(lParam);
			break;
		}
	case WM_TIMER:
		switch (wParam) {
		case RENDER_TIMER:
			{
				DWORD time;
				DWORD deltaTime;
				BOOL boolResult;
				RECT clientArea;
				POINT clientPos = {0, 0};
				boolResult = ClientToScreen(window, &clientPos);
				if (!boolResult) break;
				clientArea.left = clientPos.x;
				clientArea.top = clientPos.y;
				clientArea.right = clientArea.left + classExtraData->windowWidth;
				clientArea.bottom = clientArea.top + classExtraData->windowHeight;
				if (classExtraData->hasFocus) ClipCursor(&clientArea);
				// Don't redraw if less than 10ms has passed since the last redraw
				time = GetTickCount();
				deltaTime = time - classExtraData->lastRedrawTime;
				if (deltaTime < 10) break;
				// Redraw
				RedrawWindow(window, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW | RDW_ERASE);
				// Set the time the redraw was done at
				classExtraData->lastRedrawTime = time;
				break;
			}
		case TICK_TIMER:
			{
				const ROOM_INFO *roomInfo;
				const TILE *roomTiles;
				const TILE_EXTRA_DATA *roomExtraData;
				float x;
				float y;
				unsigned xTryingToMoveTo;
				unsigned yTryingToMoveTo;
				unsigned currentTileX;
				unsigned currentTileY;
				unsigned i;
				BOOL isNorthWall;
				BOOL isEastWall;
				BOOL isSouthWall;
				BOOL isWestWall;
				BOOL isNorthEastWall;
				BOOL isSouthEastWall;
				BOOL isSouthWestWall;
				BOOL isNorthWestWall;
				float northWallY;
				float southWallY;
				float westWallX;
				float eastWallX;
				DWORD tickTime = GetTickCount();
				DWORD deltaTime = tickTime - classExtraData->lastTickTime + classExtraData->tickTimeCarry;
				DWORD ticksToDo = deltaTime / (1000 / TPS);
				DWORD tick;

				classExtraData->lastTickTime = tickTime;
				classExtraData->tickTimeCarry = deltaTime % (1000 / TPS);
				// Do ticks
				for (tick = 0; tick < ticksToDo; tick++)
				{
				// Do animations
					if (classExtraData->animation != ANIMATION_NULL) classExtraData->animationTickCounter++;
					switch (classExtraData->animation)
					{
					case ANIMATION_NULL:
						break;
					case ANIMATION_WARP_TO_BLACK:
						{
							TILE tileOn;
							if (classExtraData->animationTickCounter != TPS / 4) break;
							classExtraData->animation = ANIMATION_FADE_FROM_BLACK;
							classExtraData->isPausedForAnimation = FALSE;
							classExtraData->animationTickCounter = 0;
							classExtraData->playerRoom = classExtraData->roomWarpingTo;
							classExtraData->playerX = TILE_POS_GET_X(classExtraData->posWarpingTo);
							classExtraData->playerY = -TILE_POS_GET_Y(classExtraData->posWarpingTo);
							tileOn = ROOM_INFOS[classExtraData->playerRoom].tiles[classExtraData->posWarpingTo];
							if (TILE_INFOS[tileOn].flags & TILE_FLAGS_WALL)
							{
								classExtraData->playerX += classExtraData->movingTileDeltaX * 0.65;
								classExtraData->playerY -= classExtraData->movingTileDeltaY * 0.65;
							}
							break;
						}
					case ANIMATION_FADE_FROM_BLACK:
						if (classExtraData->animationTickCounter == TPS / 2) classExtraData->animation = ANIMATION_NULL;
						break;
					}
					// Tick the world if the game is not paused
					if (classExtraData->isPausedForAnimation) continue;
					// Get room
					roomInfo = &ROOM_INFOS[classExtraData->playerRoom];
					roomTiles = roomInfo->tiles;
					roomExtraData = roomInfo->extraData;
					// Get player pos from struct
					x = classExtraData->playerX;
					y = classExtraData->playerY;
					// Get tile player is in
					currentTileX = floor(x + 0.5);
					currentTileY = floor(-y + 0.5);
					// Get is surrounding tiles are walls
					isNorthWall = (TILE_INFOS[roomTiles[(currentTileY - 1) * 16 + currentTileX]].flags & TILE_FLAGS_WALL);
					isEastWall = (TILE_INFOS[roomTiles[currentTileY * 16 + currentTileX + 1]].flags & TILE_FLAGS_WALL);
					isSouthWall = (TILE_INFOS[roomTiles[(currentTileY + 1) * 16 + currentTileX]].flags & TILE_FLAGS_WALL);
					isWestWall = (TILE_INFOS[roomTiles[currentTileY * 16 + currentTileX - 1]].flags & TILE_FLAGS_WALL);
					isNorthEastWall = (TILE_INFOS[roomTiles[(currentTileY - 1) * 16 + currentTileX + 1]].flags & TILE_FLAGS_WALL);
					isSouthEastWall = (TILE_INFOS[roomTiles[(currentTileY + 1) * 16 + currentTileX + 1]].flags & TILE_FLAGS_WALL);
					isSouthWestWall = (TILE_INFOS[roomTiles[(currentTileY + 1) * 16 + currentTileX - 1]].flags & TILE_FLAGS_WALL);
					isNorthWestWall = (TILE_INFOS[roomTiles[(currentTileY - 1) * 16 + currentTileX - 1]].flags & TILE_FLAGS_WALL);
					// Get the collision positions of the surrounding tiles
					northWallY = 0. - currentTileY + 0.4;
					southWallY = 0. - currentTileY - 0.4;
					westWallX = currentTileX - 0.4;
					eastWallX = currentTileX + 0.4;
					// Calculate a new position where player should move to based on movement keys pressed
					if (classExtraData->upPressed)
					{
						x += cos(classExtraData->cameraRotation) * MOVEMENT_SPEED;
						y += sin(classExtraData->cameraRotation) * MOVEMENT_SPEED;
					}
					if (classExtraData->leftPressed)
					{
						x += cos(classExtraData->cameraRotation + PI * 0.5) * MOVEMENT_SPEED;
						y += sin(classExtraData->cameraRotation + PI * 0.5) * MOVEMENT_SPEED;
					}
					if (classExtraData->downPressed)
					{
						x += cos(classExtraData->cameraRotation + PI) * MOVEMENT_SPEED;
						y += sin(classExtraData->cameraRotation + PI) * MOVEMENT_SPEED;
					}
					if (classExtraData->rightPressed)
					{
						x += cos(classExtraData->cameraRotation + PI * 1.5) * MOVEMENT_SPEED;
						y += sin(classExtraData->cameraRotation + PI * 1.5) * MOVEMENT_SPEED;
					}
					// Save the tile pos we are trying to move to so that we can see if we are trying to move to a warp tile later
					xTryingToMoveTo = floor(x + 0.5);
					yTryingToMoveTo = floor(-y + 0.5);
					// If the new position is inside a surrounding tile that is a wall, adjust the new position to be outside the wall
					classExtraData->movingTileDeltaX = 0;
					classExtraData->movingTileDeltaY = 0;
					if (isNorthWall && y > northWallY)
					{
						y = northWallY;
						yTryingToMoveTo--;
						classExtraData->movingTileDeltaY = -1;
					}
					if (isSouthWall && y < southWallY)
					{
						y = southWallY;
						yTryingToMoveTo++;
						classExtraData->movingTileDeltaY = 1;
					}
					if (isWestWall && x < westWallX)
					{
						x = westWallX;
						xTryingToMoveTo--;
						classExtraData->movingTileDeltaX = -1;
					}
					if (isEastWall && x > eastWallX)
					{
						x = eastWallX;
						xTryingToMoveTo++;
						classExtraData->movingTileDeltaX = 1;
					}
					if (isNorthEastWall && x > eastWallX && y > northWallY)
					{
						x = eastWallX;
						y = northWallY;
					}
					if (isSouthEastWall && x > eastWallX && y < southWallY)
					{
						x = eastWallX;
						y = southWallY;
					}
					if (isSouthWestWall && x < westWallX && y < southWallY)
					{
						x = westWallX;
						y = southWallY;
					}
					if (isNorthWestWall && x < westWallX && y > northWallY)
					{
						x = westWallX;
						y = northWallY;
					}
					// Set the player pos to the new pos
					classExtraData->playerX = x;
					classExtraData->playerY = y;
					// Do warps by looping over all tile extra datas and warping the player if they move onto a warp tile
					for (i = 0;; i++)
					{
						// Get tile extra data
						TILE_EXTRA_DATA extraDataEntry = roomExtraData[i];
						TILE_POS pos;
						// Skip non-warps and end at an end element
						if (extraDataEntry.discriminant == TILE_EXTRA_DATA_END) break;
						if (extraDataEntry.discriminant != TILE_EXTRA_DATA_WARP) continue;
						// Skip if the player is not trying to move to this warp tile
						pos = extraDataEntry.pos;
						if (TILE_POS_GET_X(pos) != xTryingToMoveTo || TILE_POS_GET_Y(pos) != yTryingToMoveTo) continue;
						// Start animation
						classExtraData->animation = ANIMATION_WARP_TO_BLACK;
						classExtraData->animationTickCounter = 0;
						classExtraData->roomWarpingTo = extraDataEntry.destination_room;
						classExtraData->posWarpingTo = extraDataEntry.destination_pos;
						classExtraData->isPausedForAnimation = TRUE;
						break;
					}
				}
				break;
			}
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case 0x57: // W
		case VK_UP:
			classExtraData->upPressed = TRUE;
			break;
		case 0x41: // A
		case VK_LEFT:
			classExtraData->leftPressed = TRUE;
			break;
		case 0x53: // S
		case VK_DOWN:
			classExtraData->downPressed = TRUE;
			break;
		case 0x44: // D
		case VK_RIGHT:
			classExtraData->rightPressed = TRUE;
			break;
		}
		break;
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
			SetFocus(NULL);
			break;
		case 0x57: // W
		case VK_UP:
			classExtraData->upPressed = FALSE;
			break;
		case 0x41: // A
		case VK_LEFT:
			classExtraData->leftPressed = FALSE;
			break;
		case 0x53: // S
		case VK_DOWN:
			classExtraData->downPressed = FALSE;
			break;
		case 0x44: // D
		case VK_RIGHT:
			classExtraData->rightPressed = FALSE;
			break;
		}
		break;
	case WM_MOUSEMOVE:
		{
			RECT windowRect;
			BOOL result = GetWindowRect(window, &windowRect);
			SHORT x = (SHORT)LOWORD(lParam);
			SHORT centerX = windowRect.left + classExtraData->windowWidth / 2;
			SHORT lastCursorX = classExtraData->cursorX;
			classExtraData->cursorX = x;
			if (!result) break;
			if (classExtraData->didSetCursorPosLast)
			{
				classExtraData->didSetCursorPosLast = FALSE;
				break;
			}
			if (!classExtraData->hasFocus) break;
			SetCursorPos(centerX, windowRect.top + classExtraData->windowHeight / 2);
			classExtraData->cameraRotation -= CAMERA_MOVEMENT_SPEED * (x - lastCursorX);
			if (classExtraData->cameraRotation < 0) classExtraData->cameraRotation += 2 * PI;
			if (classExtraData->cameraRotation > 2 * PI) classExtraData->cameraRotation -= 2 * PI;
			classExtraData->didSetCursorPosLast = TRUE;
			break;
		}
	case WM_LBUTTONDOWN:
		if (!classExtraData->hasFocus) SetFocus(window);
		break;
	case WM_SETFOCUS:
		classExtraData->hasFocus = TRUE;
		ShowCursor(FALSE);
		break;
	case WM_KILLFOCUS:
		classExtraData->hasFocus = FALSE;
		ShowCursor(TRUE);
		ClipCursor(NULL);
		break;
	default:
		return DefWindowProc(window, message, wParam, lParam);
	}
}