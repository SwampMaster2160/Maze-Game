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
	float playerX;
	float playerY;
	DWORD lastTime;
	BOOL isFullscreen;
	GLuint texture;
	BYTE *textures;
	BOOL hasFocus;
	SHORT cursorX;
	BOOL didSetCursorPosLast;
	BOOL upPressed;
	BOOL downPressed;
	BOOL leftPressed;
	BOOL rightPressed;
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

enum tagError
{
	MGERROR_NONE,
	MGERROR_REGISTER_CLASS,
	MGERROR_CREATE_WINDOW,
	MGERROR_GET_WINDOW_DC,
	MGERROR_CREATE_TIMER,
	MGERROR_CREATE_PIXEL_FROMAT,
	MGERROR_SET_PIXEL_FROMAT,
	MGERROR_CREATE_OPENGL_RENDER_CONTEXT,
	MGERROR_MAKE_OPENGL_RENDER_CONTEXT_CURRENT,
	MGERROR_ALLOCATE_MEMORY_FOR_TEXTURES,
	MGERROR_GET_TEXTURES_BITMAP_RESOURCE,
	MGERROR_LOAD_TEXTURES_BITMAP_RESOURCE,
	MGERROR_TEXTURES_BITMAP_RESOURCE_BAD_IMAGE_FROMAT,
	MGERROR_TEXTURES_BITMAP_RESOURCE_DELETE,
	MGERROR_GET_MESSAGE,
	MGERROR_COUNT,
};
typedef int MGERROR;

// --- Constants ---

#define WINDOW_STYLE_WINDOWED WS_OVERLAPPEDWINDOW
#define WINDOW_STYLE_FULLSCREEN WS_VISIBLE
#define PI 3.14159265358979323846
#define FPS 60
#define TPS 100
#define RENDER_TIMER 1
#define TICK_TIMER 2
#define MOVEMENT_SPEED 0.015
#define CAMERA_MOVEMENT_SPEED (2 * PI * 0.002)

// --- Tables ---

/// Info about each type tile, a tile ID is the index.
const TILE_INFO TILE_INFOS[TILE_COUNT];
const BYTE ROOM[16][16];
const LPCSTR ERROR_MESSAGES[MGERROR_COUNT - 1];

// --- Functions ---

static LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
int DisplayError(MGERROR error);

#endif
#define MAIN_H