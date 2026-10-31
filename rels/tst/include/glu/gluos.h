#pragma once

/* Platform glue for libtess. The tessellator was built with its assertions on (the game's NDEBUG build turns MSL's
 * assert off), each failing one calling the game's __assert (system.c, PAL only) with the bare file name. */

#include "dolphin/types.h"

BOOL __assert(const char* filename, s32 line, const char* assertion);

#undef assert
#define assert(expr) ((void)((expr) || __assert(__FILE__, __LINE__, #expr)))
