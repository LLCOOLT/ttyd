// jin_03 (ダイム寺院, Creepy Steeple): staircase room joining jin_00, jin_01 and jin_02,
// with a spinning (kururin) floor tile.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_bero.h"
#include "evt/evt_hit.h"
#include "evt/evt_map.h"
#include "evt/evt_mobj.h"
#include "evt/evt_snd.h"
#include "jin.h"
#include "evt/evt_story.h"
#include "driver/mapdrv.h"

extern EvtWord w3_close[];
extern EvtWord w3_open[];
static BeroEntry bero_entry_data[6];
extern EvtWord jin_03_kaidan_temae_kesu[];
extern EvtWord jin_03_kaidan_naka_kesu[];
extern EvtWord jin_03_kaidan_oku_kesu[];

static EVT_BEGIN(n_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door01"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(n_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door01"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(s_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door02"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w1_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00A"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w1_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00A"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w2_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00B"), 0, LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(w2_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00B"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(w3_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00C"), 0, LW(0), 0)
    RETURN
EVT_END()

EVT_BEGIN(w3_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
    CALL(evt_mapobj_rotate, 0, STRING("door00C"), 0, LW(0), 0)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "n_bero", // hitName
        1, // type
        2, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "jin_01", // nextMapName
        "s_bero_2", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        n_close, // enterAnimeArg
        n_open, // exitAnimeArg
    },
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
        "jin_02", // nextMapName
        "n_bero_2", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        s_close, // enterAnimeArg
        s_open, // exitAnimeArg
    },
    {
        "w_bero3", // hitName
        1, // type
        2, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "jin_00", // nextMapName
        "e_bero_3", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w1_close, // enterAnimeArg
        w1_open, // exitAnimeArg
    },
    {
        "w_bero1", // hitName
        1, // type
        2, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "jin_00", // nextMapName
        "e_bero_1", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w3_close, // enterAnimeArg
        w3_open, // exitAnimeArg
    },
    {
        "w_bero2", // hitName
        1, // type
        2, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        NULL, // exitEvent
        "jin_00", // nextMapName
        "e_bero_2", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w2_close, // enterAnimeArg
        w2_open, // exitAnimeArg
    },
    {0},
};

EVT_BEGIN(jin_03_kaidan_temae_kesu)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kaidan01"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("a_kaidan01"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_03_kaidan_naka_kesu)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kaidan02"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("a_kaidan02"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_03_kaidan_oku_kesu)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("kaidan03"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("a_kaidan03"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(jin_03_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG4_JIN1"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG4_JIN1"))
    CALL(evt_snd_set_rev_mode, 2)
    CALL(evt_kagemario_init)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(evt_usu_kagemario_party_kill)
    IF_INT_EQUAL(LSW(1), 0)
        SPAWN_EVENT(jin_03_kaidan_temae_kesu)
        SPAWN_EVENT(jin_03_kaidan_oku_kesu)
    ELSE
        IF_INT_EQUAL(LSW(1), 1)
            SPAWN_EVENT(jin_03_kaidan_naka_kesu)
            SPAWN_EVENT(jin_03_kaidan_oku_kesu)
        ELSE
            SPAWN_EVENT(jin_03_kaidan_temae_kesu)
            SPAWN_EVENT(jin_03_kaidan_naka_kesu)
        END_IF
    END_IF
    CALL(evt_mobj_kururing_floor, STRING("kururin1"), 125, 0, 0, STRING("S_yuka"), 125, GSWF(GSWF_JIN03_STAR_PIECE_PANEL))
    RETURN
EVT_END()
