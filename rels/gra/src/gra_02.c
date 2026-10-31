// gra_02 (ウスグラの道, Twilight Trail): the shed on the trail with the shopkeeper turned into a pig; between gra_01 and
// gra_03.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "evt/evt_bero.h"
#include "gra.h"
#include "evt/evt_npc.h"
#include "evt/evt_cloud.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_msg.h"
#include "evt/evt_snd.h"
#include "evt/evt_urouro.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"

static USER_FUNC(booboo_main);

static NpcSetupInfo npcEnt[2];
static BeroEntry bero_entry_data[5];
static const char* booboo_name[1];

EVT_BEGIN(shopmaster_pig_init)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG4_10_DOOPLISS_BATTLE)
        CASE_DEFAULT
        CALL(evt_npc_set_position, STRING("ブタお店の主人"), 0, -2000, 0)
    END_SWITCH
    RETURN
EVT_END()

EVT_BEGIN(shopmaster_talk)
    SWITCH(GSW(GSW_STORY_PROGRESS))
        CASE_LESS(STORY_STG4_10_DOOPLISS_BATTLE)
        CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG4_VOICE_PIG1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_msg_print, 0, STRING("stg4_gra_17"), 0, STRING("me"))
        CASE_DEFAULT
        CALL(evt_msg_print, 0, STRING("stg4_gra_18"), 0, STRING("me"))
    END_SWITCH
    RETURN
EVT_END()

static EVT_BEGIN(urouro_move)
    CALL(evt_npc_flag_onoff, 0, STRING("me"), NPC_FLAG_NO_WALL_HIT)
    CALL(evt_npc_get_position, STRING("me"), LW(0), LW(1), LW(2))
    CALL(urouro_init_func, STRING("me"), LW(0), LW(2), FLOAT(50.0f), FLOAT(30.0f), 0)
    CALL(urouro_main_func, STRING("me"))
    RETURN
EVT_END()

static NpcSetupInfo npcEnt[] = {
    {
        "ブタお店の主人", // name
        NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM, // flags
        0, // reactionFlags
        shopmaster_pig_init, // initEvent
        urouro_move, // regularEvent
        shopmaster_talk, // talkEvent
        NULL, NULL, NULL, NULL, NULL, 0, // deadEvent..territoryType
        {0}, // territoryBase
        {0}, // territoryLoiter
        0.0f, 0.0f, 0.0f, 0.0f, 0, // searchRange..battleInfoId
    },
    {0},
};

EVT_BEGIN(w_bero_2_in)
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero_1", // hitName
        0, 0, // type..sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "gra_01", // nextMapName
        "e_bero1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "w_bero_2", // hitName
        4096, // type
        0, // sfxId
        BERO_DIR_W, // directionId
        242, // centerPosition
        21, // centerPositionY
        -450, // centerPositionZ
        -1, // length
        (s32*)w_bero_2_in, // enterEvent
        0, NULL, // caseType..exitEvent
        "gra_03", // nextMapName
        "e_bero", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_1", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_2", // hitName
        4098, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

EVT_BEGIN(gra02_get_key)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG4_03_SHOP_KEY)
    RETURN
EVT_END()

EVT_BEGIN(gra02_straw_blow_evt)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SUCCESS1"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG4_05_STRAW_TEPEE)
    RETURN
EVT_END()

static const char* booboo_name[] = {
    "ブタお店の主人",
};

EVT_BEGIN(gra_02_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG4_GRA1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG4_USU1"))
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL(evt_item_entry, STRING("item00"), ITEM_STAR_PIECE, -125, 0, -110, ITEM_ENTRY_FIXED, GSWF(GSWF_GRA02_STAR_PIECE_1), 0)
    CALL(evt_item_entry, STRING("item01"), ITEM_STAR_PIECE, 305, 0, -35, ITEM_ENTRY_FIXED, GSWF(GSWF_GRA02_STAR_PIECE_2), 0)
    CALL_CHILD(evt_usu_kagemario_party_kill)
    CALL(evt_npc_setup, PTR(npcEnt))
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG4_03_SHOP_KEY)
        CALL(evt_item_entry, STRING("key00"), ITEM_SHOP_KEY, -30, 0, 0, ITEM_ENTRY_STAY, -1, PTR(gra02_get_key))
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG4_05_STRAW_TEPEE)
        CALL(evt_cloud_init)
        CALL(evt_cloud_ent, 0, STRING("S_wara"), STRING("polySurface981_q023"), PTR(gra02_straw_blow_evt))
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_wara"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("polySurface981_q023"), 0, 0)
    END_IF
    BEGIN_INLINE_EVENT
        CALL(booboo_main)
    END_INLINE_EVENT
    RETURN
EVT_END()

static USER_FUNC(booboo_main) {
    animPoseSetMaterialLightFlagOn(npcNameToPtr((const char*)booboo_name[0])->poseId, ANIM_MATERIAL_LIGHT_PAPER_NO_AMB);
    return EVT_RETURN_DONE;
}
