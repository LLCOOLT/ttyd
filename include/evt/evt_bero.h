#pragma once

#include <dolphin/types.h>
#include "evt/evt_cmd.h"

typedef union BeroINFO {
	const char* name;
	s32 value;
} BeroINFO;

typedef struct BeroEntry {
	const char* hitName; //0x0
	u16 type; //0x4, BeroInfoType | 0x1000 background | 0x2000 no fade; low 12 bits: 0 road, 1 door, 2 pipe, 3 gate, 0xF00 none
	u16 sfxId; //0x6
	s32 directionId; //0x8, 45-degree steps from north, 8 up, 9 down
	s32 centerPosition; //0xC, x of centerPosition[3]
	s32 centerPositionY; //0x10
	s32 centerPositionZ; //0x14
	s32 length; //0x18, -1 = default for type
	s32* enterEvent; //0x1C;
	s32 caseType; //0x20, -1 = default for type
	s32* exitEvent; //0x24
	s32 nextMapName; //0x28, const char* held as s32
	const char* nextBeroName; //0x2C
	u16 enterAnimeType; //0x30
	u16 exitAnimeType; //0x32
	s32 enterAnimeArg; //0x34
	s32 exitAnimeArg; //0x38
} BeroEntry;

EVT_DEF(evt_bero_info_run);

USER_FUNC(evt_bero_set_reset_position);
USER_FUNC(evt_bero_set_reset_position_current);
s32 bero_get_BeroEXEC(void);
s32 bero_get_BeroNUM(void);
f32 bero_get_BeroSX(void);
f32 bero_get_BeroSY(void);
f32 bero_get_BeroSZ(void);
f32 bero_get_BeroEX(void);
f32 bero_get_BeroEY(void);
f32 bero_get_BeroEZ(void);
BeroEntry** bero_get_ptr(void);
void bero_clear_Offset(void);
s32 bero_id_filter(s32 id);
USER_FUNC(evt_bero_mapchange);
USER_FUNC(evt_bero_get_entername);
USER_FUNC(evt_bero_exec_onoff);
USER_FUNC(evt_bero_exec_get);
USER_FUNC(evt_bero_exec_wait);
USER_FUNC(evt_bero_get_start_position);
USER_FUNC(evt_bero_get_end_position);
USER_FUNC(evt_bero_get_info_anime);
USER_FUNC(evt_bero_get_info_length);
USER_FUNC(evt_bero_get_info_kinddir);
USER_FUNC(evt_bero_get_info_nextarea);
USER_FUNC(evt_bero_set_now_number);
USER_FUNC(evt_bero_get_now_number);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_bero_get_into_info);

extern s32 bero_case_entry[];
extern s32 bero_case_exec_pipe[];
extern s32 bero_case_switch_off[];
extern s32 bero_case_switch_on[];
extern s32 bero_close_door_play_se[];
extern s32 bero_open_door_play_se[];
extern s32 bero_play_enter_anime[];
extern s32 evt_bero_info_run[];

extern s32 BeroID[16];
extern BeroEntry* BeroINFOARR[16];
extern s32 BeroSW[16]; //switches
extern s32 bero_case_entry_sub[];
extern s32 bero_case_exec_door[];
extern s32 bero_case_exec_gate[];
extern s32 bero_case_exec_none[];
extern s32 bero_case_exec_pipe_sub[];
extern s32 bero_case_exec_road[];
extern s32 bero_case_init_check[];
void bero_get_position_pipe_sub(s32 id, s32 a, s32 name, s32 kind, Vec* start, Vec* end);
extern BeroEntry bero_null[];
extern s32 bero_play_out_anime[];
extern s32 default_entevt[];
extern s32 default_outevt[];
extern s32 evt_bero_info_run_door[];
extern s32 evt_bero_info_run_gate[];
extern s32 evt_bero_info_run_none[];
extern s32 evt_bero_info_run_pipe[];
extern s32 evt_bero_info_run_pipe_sub00[];
extern s32 evt_bero_info_run_road[];
extern s32 evt_bero_initial_pos[];
extern s32 evt_bero_mario_enter[];
extern s32 evt_bero_nonride_check[];
