#include "../src/main.h"
// head
#define RTC_ROOM_TILES ROOM_TEST_TILES
// key
#define RTC_TILE_LETTER_46 TILE_NULL
#define RTC_TILE_LETTER_116 TILE_TEST
#define RTC_TILE_LETTER_66 TILE_STONE_BRICK_WALL
#define RTC_TILE_LETTER_119 TILE_WOOD_PLANKS
#define RTC_TILE_LETTER_80 TILE_STONE_BRICKS_LANDSCAPE_PAINTING
#define RTC_TILE_LETTER_68 TILE_STONE_BRICKS_WOOD_DOOR
#define RTC_TILE_LETTER_102 TILE_WOOD_PLANKS_FLOOR_HOLE
#define RTC_TILE_LETTER_99 TILE_WOOD_PLANKS_CEILING_HOLE
// tiles
const TILE RTC_ROOM_TILES[16][16] =
{
	{
		RTC_TILE_LETTER_116,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_80,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_116,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_68,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_102,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_99,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
};
// head
#define RTC_ROOM_TILES ROOM_G_0_TILES
// key
#define RTC_TILE_LETTER_46 TILE_NULL
#define RTC_TILE_LETTER_116 TILE_TEST
#define RTC_TILE_LETTER_66 TILE_STONE_BRICK_WALL
#define RTC_TILE_LETTER_119 TILE_WOOD_PLANKS
#define RTC_TILE_LETTER_80 TILE_STONE_BRICKS_LANDSCAPE_PAINTING
#define RTC_TILE_LETTER_68 TILE_STONE_BRICKS_WOOD_DOOR
#define RTC_TILE_LETTER_83 TILE_STONE_BRICKS_WOOD_DOOR_SKY
#define RTC_TILE_LETTER_102 TILE_WOOD_PLANKS_FLOOR_HOLE
// tiles
const TILE RTC_ROOM_TILES[16][16] =
{
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_83,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_102,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_68,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_68,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_68,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_68,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_68,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_119,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_66,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
	{
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
		RTC_TILE_LETTER_46,
	},
};
