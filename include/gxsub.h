// gxsub.c: queen_uv and, in the demo only, the 2D textured-quad helpers that seq_demo draws with.
#pragma once

#include <dolphin/types.h>
#include "version.h"

extern f32 queen_uv[];

#if VERSION <= VERSION_DEMO_US
#include <dolphin/gx.h>

// demo only: the 2D textured-quad helpers seq_demo draws its movie overlay with
BOOL gxsubMiscSetGX(s32 mode);
void gxsubFillGX(s32 x, s32 y, s32 w, s32 h, GXColor* color);
void gxsubFillSetTexObj(GXTexObj* obj);
#endif
