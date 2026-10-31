// Rogueport (gor, ゴロツキタウン): declarations shared by the area's maps (gor_00 to gor_04, gor_10 to gor_12).
#pragma once

#include "dolphin/types.h"
#include "dolphin/mtx.h"
#include "driver/npcdrv.h"
#include "evt/evt_word.h"
#include "driver/camdrv.h"
#include "evt/evt_cmd.h"

extern EvtWord all_juyoitem_lecture_rel[];
extern EvtWord all_party_lecture[];
extern NpcTerritoryInfo btl_gor_setup_no_tbl[];
extern NpcSetupBattleInfo btlsetup_gor_tbl[];
extern const char* door_data_05_npc[];
extern const char* door_data_05_npc_01[];
extern EvtWord gor_00_init_evt[];
extern EvtWord gor_01_init_evt[];
extern EvtWord gor_02_init_evt[];
extern EvtWord gor_03_init_evt[];
extern EvtWord gor_04_init_evt[];
extern EvtWord gor_10_init_evt[];
extern EvtWord gor_11_init_evt[];
extern EvtWord gor_12_init_evt[];
extern EvtWord gor_irai_init[];
extern EvtWord gor_villager_urouro[];
extern EvtWord luigi_gor_first_talk[];
extern BattleUnitKind unit_lecture_frankli_sac;
extern BattleUnitKind unit_monban;

typedef struct CookRecipe {
    const char* a;
    const char* b;
    const char* out;
} CookRecipe;
extern CookRecipe R_cookbook_recipe_table[];
extern s32 naniga_okorukana_list[];
typedef struct SimpleRecipe {
    const char* ingredient;
    const char* result;
    const char* result2;
} SimpleRecipe; /* naniga_okorukana lookup: results go to args[1]/args[2] */
extern SimpleRecipe R_simple_recipe_table[];
extern f32 gor_ship_puka_data[];
extern s32* irai_item_table[];
extern const char* irai_msg_client[];
extern const char* irai_msg_contents[];
extern const char* irai_msg_kakunin[];
extern s32 special_cook_list[];
extern Vec suifu100kaidanDOWN[];
extern Vec suifu100kaidanUP[];

USER_FUNC(evt_goryuugijo_alloc);
USER_FUNC(keijiban_joho_makelabel);
USER_FUNC(keijiban_joho_check);
USER_FUNC(keijiban_data_free);
USER_FUNC(keijiban_data_alloc);
USER_FUNC(evt_gor_villager_urouro_check_func);
USER_FUNC(evt_goki_sub_intpl_init);
USER_FUNC(evt_goki_sub_intpl_get_value);
void goryuugijo_disp_slot(CameraId camera, void* param);
void goryuugijo_main_slot(EventEntry* event, BOOL isFirstCall);
void goryuugijo_init_slot(EventEntry* event, BOOL isFirstCall);
void goryuugijo_disp_montemedal(CameraId camera, void* param);
void goryuugijo_main_montemedal(EventEntry* event, BOOL isFirstCall);
void goryuugijo_init_montemedal(EventEntry* event, BOOL isFirstCall);
void tegami_delete(void);
extern BattleUnitKind unit_boss_kanbu1;
extern BattleUnitKind unit_lecture_christine;
extern BattleUnitKind unit_lecture_frankli;
extern BattleUnitKind unit_npc_christine;
