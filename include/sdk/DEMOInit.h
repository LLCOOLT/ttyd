// src/sdk/DEMOInit.c: the SDK demo-library init and frame begin/end (DEMOInit, DEMOBeforeRender, DEMODoneRender).
#pragma once

#include <dolphin/gx.h>

void DEMOInit(GXRenderModeObj* mode);
void DEMOBeforeRender(void);
void DEMODoneRender(void);
GXRenderModeObj* DEMOGetRenderModeObj(void);
void* L_DEMOGetCurrentBuffer(void);
#define DEMOGetCurrentBuffer L_DEMOGetCurrentBuffer
void DEMOEnableGPHangWorkaround(u32 timeoutFrames);
