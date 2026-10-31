// jin_11 (ダイム寺院, Creepy Steeple): room with a save block, a power-up block and a breaking floor;
// doors to jin_07 and jin_10.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_map.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "party/party_motion.h"
#include "jin.h"
#include "evt/evt_story.h"

extern EvtWord jin_11_ana[];
static BeroEntry bero_entry_data[3];
extern EvtWord evt_yuka[];

EVT_BEGIN(jin_11_ana)
    SET_VALUE(GSWF(GSWF_STG4_DROP_IN_ENTRANCE), 1)
    CALL(evt_bero_mapchange, STRING("jin_07"), 0)
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door10"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door10"), 0, LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "s_bero", // hitName
        1, // type
        2, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "jin_10", // nextMapName
        "n_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_close, // enterAnimeArg
        s_open, // exitAnimeArg
    },
    {
        "ana", // hitName
        0, 0, // type..sfxId
        BERO_DIR_S, // directionId
        845, // centerPosition
        115, // centerPositionY
        77, // centerPositionZ
        -1, // length
        NULL, 0, // enterEvent..caseType
        (s32*)jin_11_ana, // exitEvent
        "jin_07", // nextMapName
        NULL, // nextBeroName
        4, // enterAnimeType
        4, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

EVT_BEGIN(evt_yuka)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG4_13_03_BREAKING_THE_FLOOR)
    RETURN
EVT_END()

EVT_BEGIN(jin_11_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL_CHILD(PTR(evt_usu_kagemario_party_kill))
    CALL(evt_mobj_save_blk, STRING("mobj_save"), -50, 60, -40, 0, 0)
    CALL(evt_mobj_powerupblk, STRING("pblk00"), 40, 60, -40, 0, GSWF(GSWF_JIN11_SHINE_SPRITE), 0)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG4_13_03_BREAKING_THE_FLOOR)
        CALL(evt_mobj_breaking_floor, STRING("mobj_bf00"), 845, 115, 5, 0, PTR(evt_yuka), GSWF(GSWF_JIN11_FLOOR_BROKEN))
    END_IF
    RETURN
EVT_END()
