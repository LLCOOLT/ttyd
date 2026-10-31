// Pianta Parlor (yuu, yugijo "amusement hall"): types and data of its minigames (Monte, MonteTable, SlitWork).
#pragma once

#include "dolphin/types.h"
#include "dolphin/mtx.h"
#include "manager/evtmgr.h"
#include "driver/camdrv.h"
#include "evt/evt_cmd.h"
#include "evt/evt_yuuminigame.h"
#include "driver/icondrv.h"

// A Pianta token lying in a minigame room (yuu_00 .. yuu_03), drawn as an icon.
typedef struct Monte {
    u8 hidden;        // 0x00
    u8 pad_1;         // 0x01
    s16 num;          // 0x02
    u8 state;         // 0x04
    u8 pad_5[3];      // 0x05
    IconEntry icon;   // 0x08, only position and scale are used
    MiniGameWork* wp; // 0x40
} Monte;

// Area of a room where tokens are scattered (yuu_00, yuu_01); a zero num ends the table.
typedef struct MonteTable {
    f32 x0, x1; // 0x00, x range
    f32 y0, y1; // 0x08, second range (y in the 2D rooms, z in yuu_01)
    s32 num;    // 0x10, tokens placed in this area
} MonteTable;
// minigame 4 (yuu_03) work
typedef struct SlitWork {
    u32 flags;
    s32 phase;
    s32 coins;
    s32 result;
    s32 state;
    s32 timer;
    f32 rot1;
    f32 rot2;
    s32 monteCount;
    EventEntry* viewEvent;
} SlitWork;

extern EvtWord evt_yuunpc_minigame1[];
extern EvtWord evt_yuunpc_minigame2[];
extern EvtWord evt_yuunpc_minigame3[];
extern EvtWord evt_yuunpc_minigame4[];
extern EvtWord yuu_00_init_evt[];
extern EvtWord yuu_01_init_evt[];
extern EvtWord yuu_02_init_evt[];
extern EvtWord yuu_03_init_evt[];
extern MiniGameWork* yuunpc_yuuminigame4_ptr;
extern f32 yuusintbl[];

extern const char* a_nametbl[];
extern Vec fukkipoint[];
extern signed char hitdata[];
extern s32 hoko_tbl[];
extern EvtWord minigame01_end[];
extern EvtWord minigame01_start[];
extern EvtWord minigame02_end[];
extern EvtWord minigame02_start[];
extern EvtWord minigame03_end[];
extern EvtWord minigame03_start[];
extern EvtWord minigame04_end[];
extern EvtWord minigame04_start[];
extern EvtWord ryushi_event[];
extern const char* s_nametbl[];
extern s32 turn_tbl[];
extern EvtWord yuu_02_icon_monte_entry_evt[];
extern EvtWord yuu_02_jumpret[];
extern EvtWord yuu_03_icon_monte_entry_evt[];

extern EvtWord minigame01_floor_delete[];

USER_FUNC(evt_yuucounter_free);
USER_FUNC(evt_yuucounter_alloc);
USER_FUNC(yuu_atai_init);
USER_FUNC(yuu_atai_pop);
USER_FUNC(yuu_atai_push);
USER_FUNC(eff_call_minigame);
USER_FUNC(yuuminigame_set_dataadr);
USER_FUNC(yuuminigame_get_dataadr);
USER_FUNC(evt_yuuminigame_alloc);
USER_FUNC(yuuranking_get_monte);
USER_FUNC(evt_yuutitle_alloc);
USER_FUNC(evt_yuutitle_free);
s32 yuucounter_get_data(void);
void ext_yuunpc_minigame4_init_sub(void);
s32 yuunpc_juni(Vec* pos);
void yuuminigame_disp_1hikoki(CameraId camera, void* param);
void yuuminigame_disp_2fune(CameraId camera, void* param);
void yuuminigame_disp_3roll(CameraId camera, void* param);
void yuuminigame_disp_4slit(CameraId camera, void* param);
void yuucounter_flag_on(u32 mask);
void yuunpc_wp_flag_off(u16 flag);
