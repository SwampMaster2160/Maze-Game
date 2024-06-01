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
} ClassExtraData;

/// A list of textures in the texture bitmap.
enum tagTEXTURES
{
	TEXTURE_TEST,
	TEXTURE_WOOD_PLANKS,
	TEXTURE_STONE_BRICKS,
};

/// A list of tile IDs.
enum tagTILES
{
	TILE_NULL,
	TILE_TEST,
	TILE_STONE_BRICK_WALL,
	TILE_WOOD_PLANKS,
	TILE_COUNT,
};

/// A set of flags for tiles.
enum tagTILE_FLAGS
{
	TILE_FLAGS_WALL = 1,
};

/// The type of each members of the `TILE_INFOS` array.
typedef struct tagTILE_INFO
{
	BYTE texture;
	BYTE flags;
} TILE_INFO;

// --- Constants ---

const DWORD WINDOW_STYLE_WINDOWED = WS_OVERLAPPEDWINDOW;
const DWORD WINDOW_STYLE_FULLSCREEN = WS_VISIBLE;

/// Info about each type tile, a tile ID is the index.
const TILE_INFO TILE_INFOS[TILE_COUNT];
const BYTE ROOM[16][16];

// --- Functions ---

static LRESULT CALLBACK windowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam);

#endif
#define MAIN_H