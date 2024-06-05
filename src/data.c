#include "main.h"

const TILE_INFO TILE_INFOS[TILE_COUNT] =
{
	{0,                                       0,                                       0              }, // Null
	{TEXTURE_TEST,                            TEXTURE_TEST,                            0              }, // Test
	{TEXTURE_STONE_BRICKS,                    TEXTURE_STONE_BRICKS,                    TILE_FLAGS_WALL}, // Stone bricks
	{TEXTURE_WOOD_PLANKS,                     TEXTURE_WOOD_PLANKS,                     0              }, // Wood planks
	{TEXTURE_STONE_BRICKS_LANDSCAPE_PAINTING, TEXTURE_STONE_BRICKS_LANDSCAPE_PAINTING, TILE_FLAGS_WALL}, // Stone bricks with landscape painting
};

const ROOM_INFO ROOM_INFOS[ROOM_COUNT] =
{
	{(const TILE *)ROOM_MAIN_TILES},
};

//#define TILE_LETTER_0 TILE_NULL
//#define ROOM_ROW(a, b, c, d, e, f, g, h, i, j, k, l, m, n, o, p) \
//	{ \
//		TILE_LETTER(a), TILE_LETTER(b), TILE_LETTER(c), TILE_LETTER(d), TILE_LETTER(e), TILE_LETTER(f), TILE_LETTER(g), TILE_LETTER(h), \
//		TILE_LETTER(i), TILE_LETTER(j), TILE_LETTER(k), TILE_LETTER(l), TILE_LETTER(m), TILE_LETTER(n), TILE_LETTER(o), TILE_LETTER(p), \
//	},
//#define TILE_LETTER(letter) TILE_LETTER_ ## letter
//
//#define TILE_LETTER_t TILE_TEST
//#define TILE_LETTER_B TILE_STONE_BRICK_WALL
//#define TILE_LETTER_w TILE_WOOD_PLANKS
//#define TILE_LETTER_P TILE_STONE_BRICKS_LANDSCAPE_PAINTING
//
//const TILE ROOM[16][16] = {
//	ROOM_ROW(t,B,0,B,B,B,0,B,B,B,B,B,B,0,0,0)
//	ROOM_ROW(B,w,B,w,w,w,B,w,w,w,w,w,w,B,0,0)
//	ROOM_ROW(B,w,B,B,B,w,B,w,B,w,B,B,w,B,B,0)
//	ROOM_ROW(B,w,B,B,B,w,w,w,B,w,B,B,w,w,w,B)
//	ROOM_ROW(B,w,w,w,B,B,B,B,B,w,B,B,B,B,B,0)
//	ROOM_ROW(P,w,t,w,w,w,w,w,w,w,w,w,w,w,w,B)
//	ROOM_ROW(B,w,w,w,B,B,B,B,B,B,B,B,w,B,B,0)
//	ROOM_ROW(0,B,w,B,0,0,0,B,0,0,0,B,w,B,0,0)
//	ROOM_ROW(0,0,B,0,0,0,B,w,B,0,0,B,w,B,0,0)
//	ROOM_ROW(0,0,0,0,0,B,B,w,B,B,0,B,w,B,0,0)
//	ROOM_ROW(0,B,B,B,B,w,w,w,w,w,B,B,w,B,0,0)
//	ROOM_ROW(B,w,w,w,w,w,w,w,w,w,B,B,w,B,0,0)
//	ROOM_ROW(0,B,B,B,B,w,w,w,w,w,w,w,w,B,0,0)
//	ROOM_ROW(B,w,w,w,w,w,w,w,w,w,B,B,B,0,0,0)
//	ROOM_ROW(0,B,B,B,B,w,w,w,w,w,B,0,0,0,0,0)
//	ROOM_ROW(0,0,0,0,0,B,B,B,B,B,0,0,0,0,0,0)
//};