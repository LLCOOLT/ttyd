#pragma once

#include <dolphin/types.h>

extern f32 queen_uv[];

#ifdef VERSION_G8ME01_DEMO
#include <dolphin/gx.h>

// demo only: the 2D textured-quad helpers seq_demo draws its movie overlay with
BOOL gxsubChgMode(s32 mode);
void gxsubDrawQuad(s32 x, s32 y, s32 w, s32 h, GXColor* color);
void gxsubSetTexObj(GXTexObj* obj);
#endif
