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
};

const TILE_EXTRA_DATA BLANK_EXTRA_DATA[] = { TILE_EXTRA_DATA_END_NEW };
const TILE_EXTRA_DATA ROOM_TEST_EXTRA_DATA[] =
{
	TILE_EXTRA_DATA_WARP_NEW(2, 10, ROOM_G_0, 0),
	TILE_EXTRA_DATA_WARP_DESTINATION_NEW(9, 13, 1),
	TILE_EXTRA_DATA_WARP_NEW(9, 11, ROOM_TEST, 1),
	TILE_EXTRA_DATA_END_NEW,
};
const TILE_EXTRA_DATA ROOM_G_0_EXTRA_DATA[] =
{
	TILE_EXTRA_DATA_WARP_NEW(3, 6, ROOM_TEST, 0),
	TILE_EXTRA_DATA_WARP_NEW(6, 2, -1, -1),
	TILE_EXTRA_DATA_END_NEW,
};

const ROOM_INFO ROOM_INFOS[ROOM_COUNT] =
{
	{(const TILE *)ROOM_TEST_TILES, ROOM_TEST_EXTRA_DATA},
	{(const TILE *)ROOM_G_0_TILES, ROOM_G_0_EXTRA_DATA},
};