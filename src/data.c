#include "main.h"

const TILE_INFO TILE_INFOS[TILE_COUNT] =
{
	{0,                                       0,                                       0              }, // Null
	{TEXTURE_TEST,                            TEXTURE_TEST,                            0              }, // Test
	{TEXTURE_STONE_BRICKS,                    TEXTURE_STONE_BRICKS,                    TILE_FLAGS_WALL}, // Stone bricks
	{TEXTURE_WOOD_PLANKS,                     TEXTURE_WOOD_PLANKS,                     0              }, // Wood planks
	{TEXTURE_STONE_BRICKS_LANDSCAPE_PAINTING, TEXTURE_STONE_BRICKS_LANDSCAPE_PAINTING, TILE_FLAGS_WALL}, // Stone bricks with landscape painting
	{TEXTURE_STONE_BRICKS_WOOD_DOOR,          TEXTURE_STONE_BRICKS_WOOD_DOOR,          TILE_FLAGS_WALL}, // Stone bricks with wood door
};

const ROOM_INFO ROOM_INFOS[ROOM_COUNT] =
{
	{(const TILE *)ROOM_TEST_TILES},
	{(const TILE *)ROOM_G_0_TILES},
};