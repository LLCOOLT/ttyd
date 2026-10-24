#pragma once

#include "evt/evt_cmd.h"

/* Koopa Koot-style stage object streams read by kpa_read_mobj / kpa_read_item (kpa.c).
   Positions are evt floats; each macro expands to the tag word followed by its operands. */
#define KPA_OBJ_END -1
#define KPA_OBJ_OJAMA_BLK(x, z) 0, FLOAT(x), FLOAT(z)
#define KPA_OBJ_STONE_BLK(x, z) 1, FLOAT(x), FLOAT(z)
#define KPA_OBJ_BRICK_0(x, z) 2, FLOAT(x), FLOAT(z)
#define KPA_OBJ_BRICK_1(x, z) 3, FLOAT(x), FLOAT(z)
#define KPA_OBJ_BRICK_2(x, z) 4, FLOAT(x), FLOAT(z)
#define KPA_OBJ_BRICK_3(x, z) 5, FLOAT(x), FLOAT(z)
#define KPA_OBJ_BADGE_BLK(x, z, item) 6, FLOAT(x), FLOAT(z), item
#define KPA_OBJ_HIDDEN_BLK(x, z, item) 7, FLOAT(x), FLOAT(z), item
#define KPA_OBJ_KOOPA_BLK(x, z) 8, FLOAT(x), FLOAT(z)
#define KPA_OBJ_DOKAN_0(x, z) 9, FLOAT(x), FLOAT(z)
#define KPA_OBJ_DOKAN_1(x, z) 10, FLOAT(x), FLOAT(z)
#define KPA_OBJ_DOKAN_2(x, z) 11, FLOAT(x), FLOAT(z)
#define KPA_OBJ_SANGO(x, z) 12, FLOAT(x), FLOAT(z)
#define KPA_OBJ_FIREBAR_DODAI_0(x, z, a, b) 13, FLOAT(x), FLOAT(z), a, b
#define KPA_OBJ_FIREBAR_DODAI_1(x, z, a, b) 14, FLOAT(x), FLOAT(z), a, b
#define KPA_OBJ_POLE(x, z, clear_evt) 15, FLOAT(x), FLOAT(z), (EvtWord)(clear_evt)
#define KPA_OBJ_JUMPSTAND_RED(x, z, a) 16, FLOAT(x), FLOAT(z), a
#define KPA_OBJ_JUMPSTAND_BLUE(x, z, a) 17, FLOAT(x), FLOAT(z), a

#define KPA_ITEM_END -1
#define KPA_ITEM(x, z) 0, FLOAT(x), FLOAT(z)
