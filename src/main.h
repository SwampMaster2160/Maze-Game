#ifndef MAIN_H

#include <windows.h>
#include <gl/GLU.h>

// --- Types ---

/// A list of room IDs.
enum tagROOM
{
	ROOM_TEST,
	ROOM_G_0,
	ROOM_G_1,
	ROOM_B1_0,
	ROOM_COUNT,
};
/// A room ID, `-1` in a warp ill warp to the same room.
typedef char ROOM;

/// A list of animations.
enum tagANIMATION
{
	ANIMATION_NULL,
	ANIMATION_WARP_TO_BLACK,
	ANIMATION_FADE_FROM_BLACK,
};
/// An animation ID.
typedef BYTE ANIMATION;

typedef BYTE TILE_POS;
#define TILE_POS_GET_X(pos) ((pos) & 0x0F)
#define TILE_POS_GET_Y(pos) ((pos) >> 4)
#define TILE_POS_NEW(x, y) ((x) | ((y) << 4))

/// A warp pair id, `-1` means warp to the same tile that we are warpin from.
typedef char WARP_PAIR;

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
	ROOM playerRoom;
	DWORD lastRedrawTime;
	DWORD lastTickTime;
	BOOLEAN isFullscreen;
	BOOLEAN hasFocus;
	SHORT cursorX;
	BOOLEAN didSetCursorPosLast;
	BOOLEAN upPressed;
	BOOLEAN downPressed;
	BOOLEAN leftPressed;
	BOOLEAN rightPressed;
	ANIMATION animation;
	BYTE animationTickCounter;
	ROOM roomWarpingTo;
	WARP_PAIR warpPair;
	signed char movingTileDeltaX;
	signed char movingTileDeltaY;
	BOOLEAN isPausedForAnimation;
	DWORD tickTimeCarry;
	TILE_POS posWarpingFrom;
} ClassExtraData;

/// A list of textures in the texture bitmap.
enum tagTEXTURE
{
	TEXTURE_TEST,
	TEXTURE_WOOD_PLANKS,
	TEXTURE_STONE_BRICKS,
	TEXTURE_STONE_BRICKS_LANDSCAPE_PAINTING,
	TEXTURE_PLASTER_WALL,
	TEXTURE_CARPET_VERTICAL,
	TEXTURE_CARPET_T,
	TEXTURE_CARPET_CROSS,
	TEXTURE_CARPET_CORNER,
	TEXTURE_CARPET_END,
	TEXTURE_STONE_BRICKS_WOOD_DOOR,
	TEXTURE_WOOD_PLANKS_HOLE,
	TEXTURE_WOOD_PLANKS_EXTRA_PLANKS,
	TEXTURE_STONE_BRICKS_WOOD_DOOR_SKY,
	TEXTURE_STONE_BRICKS_STAIRS,
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
	TILE_STONE_BRICKS_LANDSCAPE_PAINTING,
	TILE_STONE_BRICKS_WOOD_DOOR,
	TILE_WOOD_PLANKS_FLOOR_HOLE,
	TILE_WOOD_PLANKS_CEILING_HOLE,
	TILE_STONE_BRICKS_WOOD_DOOR_SKY,
	TILE_STONE_BRICKS_STAIRS,
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
	TEXTURE ceilingNorthSouthTexture;
	TEXTURE floorEastWestTexture;
	BYTE flags;
} TILE_INFO;

/// What type of extra data a `TILE_EXTRA_DATA` entry is.
enum tagTILE_EXTRA_DATA_DISCRIMINANT
{
	TILE_EXTRA_DATA_END = 0,
	TILE_EXTRA_DATA_WARP,
	TILE_EXTRA_DATA_WARP_DESTINATION,
};
typedef BYTE TILE_EXTRA_DATA_DISCRIMINANT;

/// Defines extra data for a tile in the room.
typedef struct tagTILE_EXTRA_DATA
{
	/// What type of extra data this is.
	TILE_EXTRA_DATA_DISCRIMINANT discriminant;
	/// What tile in the room has this extra data.
	TILE_POS pos;
	union
	{
		BYTE data0;
		/// If `discriminant` is `TILE_EXTRA_DATA_WARP`, this is the room to warp to.
		ROOM destinationRoom;
	};
	union
	{
		BYTE data1;
		/// If `discriminant` is `TILE_EXTRA_DATA_WARP`, will warp to the other warp in the destination room with the same pair id.
		/// If `descriminant` is `TILE_EXTRA_DATA_WARP` or `TILE_EXTRA_DATA_WARP_DESTINATION`, this is the pair id that will be searched for.
		WARP_PAIR pairId;
	};
} TILE_EXTRA_DATA;

#define TILE_EXTRA_DATA_END_NEW { TILE_EXTRA_DATA_END }
#define TILE_EXTRA_DATA_WARP_NEW(x, y, destinationRoom, pairId) { TILE_EXTRA_DATA_WARP, TILE_POS_NEW(x, y), destinationRoom, pairId }
#define TILE_EXTRA_DATA_WARP_DESTINATION_NEW(x, y, pairIdIn) { TILE_EXTRA_DATA_WARP_DESTINATION, TILE_POS_NEW(x, y), 0, pairIdIn }

/// The type of each members of the `ROOM_INFOS` array.
typedef struct tagROOM_INFO
{
	const TILE *tiles;
	const TILE_EXTRA_DATA *extraData;
} ROOM_INFO;

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
#define MOVEMENT_SPEED (1. / TPS)
#define CAMERA_MOVEMENT_SPEED (2 * PI * 0.002)
#define TEXTURE_SHEET_WIDTH 256
#define TEXTURE_SHEET_HEIGHT 256

// --- Tables ---

/// Info about each type tile, a tile ID is the index.
const TILE_INFO TILE_INFOS[TILE_COUNT];
/// Info about each room, a room ID is the index.
const ROOM_INFO ROOM_INFOS[ROOM_COUNT];
const LPCSTR ERROR_MESSAGES[MGERROR_COUNT - 1];

const TILE ROOM_TEST_TILES[16][16];
const TILE ROOM_G_0_TILES[16][16];
const TILE ROOM_G_1_TILES[16][16];
const TILE ROOM_B1_0_TILES[16][16];

// --- Functions ---

static LRESULT CALLBACK WindowProcess(HWND window, UINT message, WPARAM wParam, LPARAM lParam);
int DisplayError(MGERROR error);

#endif
#define MAIN_H