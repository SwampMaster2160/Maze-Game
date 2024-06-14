#include "main.h"

const TILE_INFO TILE_INFOS[TILE_COUNT] =
{
	{0,                                       0,                                       0              }, // Null
	{TEXTURE_TEST,                            TEXTURE_TEST,                            0              }, // Test
	{TEXTURE_STONE_BRICKS,                    TEXTURE_STONE_BRICKS,                    TILE_FLAGS_WALL}, // Stone bricks
	{TEXTURE_WOOD_PLANKS,                     TEXTURE_WOOD_PLANKS,                     0              }, // Wood planks
	{TEXTURE_STONE_BRICKS_LANDSCAPE_PAINTING, TEXTURE_STONE_BRICKS_LANDSCAPE_PAINTING, TILE_FLAGS_WALL}, // Stone bricks with landscape painting
	{TEXTURE_STONE_BRICKS_WOOD_DOOR,          TEXTURE_STONE_BRICKS_WOOD_DOOR,          TILE_FLAGS_WALL}, // Stone bricks with wood door
	{TEXTURE_WOOD_PLANKS,                     TEXTURE_WOOD_PLANKS_HOLE,                0              }, // Wood planks floor hole
	{TEXTURE_WOOD_PLANKS_HOLE,                TEXTURE_WOOD_PLANKS_EXTRA_PLANKS,        0              }, // Wood planks ceiling hole
	{TEXTURE_STONE_BRICKS_WOOD_DOOR_SKY,      TEXTURE_STONE_BRICKS_WOOD_DOOR_SKY,      TILE_FLAGS_WALL}, // Stone bricks with wood door and sky
	{TEXTURE_STONE_BRICKS_STAIRS,             TEXTURE_STONE_BRICKS_STAIRS,             TILE_FLAGS_WALL}, // Stone bricks with stairs
};

const TILE_EXTRA_DATA BLANK_EXTRA_DATA[] = { TILE_EXTRA_DATA_END_NEW };
const TILE_EXTRA_DATA ROOM_TEST_EXTRA_DATA[] =
{
	TILE_EXTRA_DATA_WARP_NEW(2, 10, ROOM_G_0, 0),
	TILE_EXTRA_DATA_WARP_DESTINATION_NEW(9, 13, 1),
	TILE_EXTRA_DATA_WARP_NEW(9, 11, -1, 1),
	TILE_EXTRA_DATA_END_NEW,
};
const TILE_EXTRA_DATA ROOM_G_0_EXTRA_DATA[] =
{
	TILE_EXTRA_DATA_WARP_NEW(3, 6, -1, -1),
	TILE_EXTRA_DATA_WARP_NEW(11, 6, -1, -1),
	TILE_EXTRA_DATA_WARP_NEW(7, 8, -1, -1),
	TILE_EXTRA_DATA_WARP_NEW(0, 7, ROOM_B1_0, 0),
	TILE_EXTRA_DATA_WARP_NEW(7, 2, ROOM_B1_0, 1),
	TILE_EXTRA_DATA_WARP_NEW(14, 7, ROOM_G_1, 2),
	TILE_EXTRA_DATA_END_NEW,
};
const TILE_EXTRA_DATA ROOM_G_1_EXTRA_DATA[] =
{
	TILE_EXTRA_DATA_WARP_NEW(0, 3, ROOM_G_0, 2),
	TILE_EXTRA_DATA_END_NEW,
};
const TILE_EXTRA_DATA ROOM_B1_0_EXTRA_DATA[] =
{
	TILE_EXTRA_DATA_WARP_NEW(5, 7, ROOM_G_0, 0),
	TILE_EXTRA_DATA_WARP_NEW(9, 2, -1, -1),
	TILE_EXTRA_DATA_WARP_DESTINATION_NEW(12, 2, 1),
	TILE_EXTRA_DATA_END_NEW,
};

const ROOM_INFO ROOM_INFOS[ROOM_COUNT] =
{
	{(const TILE *)ROOM_TEST_TILES, ROOM_TEST_EXTRA_DATA},
	{(const TILE *)ROOM_G_0_TILES, ROOM_G_0_EXTRA_DATA},
	{(const TILE *)ROOM_G_1_TILES, ROOM_G_1_EXTRA_DATA},
	{(const TILE *)ROOM_B1_0_TILES, ROOM_B1_0_EXTRA_DATA},
};