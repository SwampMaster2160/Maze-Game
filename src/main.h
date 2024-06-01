#ifndef MAIN_H

#include <windows.h>
#include <gl/GLU.h>

// --- Types ---

/// The main data struct for the window class.
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
	BOOL hasFocus;
	SHORT cursorX;
	BOOL didSetCursorPosLast;
} ClassExtraData;

/// A list of textures in the texture bitmap.
enum tagTEXTURE
{
	TEXTURE_TEST,
	TEXTURE_WOOD_PLANKS,
	TEXTURE_STONE_BRICKS,
};
/// A texture ID.
typedef BYTE TEXTURE;

/// A list of tile IDs.
enum tagTILE
{
	TILE_NULL,
	TILE_TEST,
	TILE_STONE_BRICK_WALL,
	TILE_WOOD_PLANKS,
	TILE_COUNT,
};
/// A tile ID.
typedef BYTE TILE;

/// A set of flags for tiles.
enum tagTILE_FLAGS
{
	TILE_FLAGS_WALL = 1,
};

/// The type of each members of the `TILE_INFOS` array.
typedef struct tagTILE_INFO
{
	TEXTURE texture;
	BYTE flags;
} TILE_INFO;

// --- Constants ---

const DWORD WINDOW_STYLE_WINDOWED = WS_OVERLAPPEDWINDOW;
const DWORD WINDOW_STYLE_FULLSCREEN = WS_VISIBLE;
const float PI = 3.14159265358979323846;

/// Info about each type tile, a tile ID is the index.
const TILE_INFO TILE_INFOS[TILE_COUNT];
const BYTE ROOM[16][16];

// --- Functions ---

static LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

#endif
#define MAIN_H