#pragma once

#include "dolphin/types.h"
#include "dolphin/mtx.h"
#include "manager/evtmgr.h"
#include "driver/camdrv.h"

// minigame driver work (evt_yuuminigame); data points at the per-game work (HikokiWork, SlitWork, ...)
typedef struct MiniGameWork { EventEntry* event; EventEntry* subEvent; u16 flags; s32 type; s32 (*init)(EventEntry* event, BOOL isFirstCall); s32 (*main)(EventEntry* event, BOOL isFirstCall); void (*disp)(CameraId camera, void* param); void* data; } MiniGameWork;
// minigame 4 (yuu_03) work
typedef struct SlitWork { u32 flags; s32 phase; s32 coins; s32 result; s32 state; s32 timer; f32 rot1; f32 rot2; s32 monteCount; EventEntry* viewEvent; } SlitWork;

extern s32 evt_yuunpc_minigame1[];
extern s32 evt_yuunpc_minigame2[];
extern s32 evt_yuunpc_minigame3[];
extern s32 evt_yuunpc_minigame4[];
extern s32 yuu_00_init_evt[];
extern s32 yuu_01_init_evt[];
extern s32 yuu_02_init_evt[];
extern s32 yuu_03_init_evt[];
extern MiniGameWork* yuunpc_yuuminigame4_ptr;
extern f32 yuusintbl[];

extern const char* a_nametbl[];
extern Vec fukkipoint[];
extern signed char hitdata[];
extern s32 hoko_tbl[];
extern s32 minigame01_end[];
extern s32 minigame01_start[];
extern s32 minigame02_end[];
extern s32 minigame02_start[];
extern s32 minigame03_end[];
extern s32 minigame03_start[];
extern s32 minigame04_end[];
extern s32 minigame04_start[];
extern s32 minigame_view_monte[];
extern s32 ryushi_event[];
extern const char* s_nametbl[];
extern s32 turn_tbl[];
extern s32 yuu_02_icon_monte_entry_evt[];
extern s32 yuu_02_jumpret[];
extern s32 yuu_03_icon_monte_entry_evt[];

extern s32 minigame01_floor_delete[];
