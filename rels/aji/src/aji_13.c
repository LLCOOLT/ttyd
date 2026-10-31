// aji_13 (敵のアジト, X-Naut Fortress): the conveyor-belt room (move_left_right, move_up_down) with clockwork
// switches and the card key (evt_key_get).
#include "version.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"

#include "driver/hitdrv.h"
#include "string.h"
#include "mario/mario.h"
#include "party.h"
#include "driver/mapdrv.h"
#include "system.h"
#include "dolphin/mtx.h"
#include "driver/camdrv.h"
#include "evt/evt_bero.h"
#include "aji.h"
#include "mario/mario_pouch.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_hit.h"
#include "evt/evt_img.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_mobj.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_offscreen.h"
#include "evt/evt_paper.h"
#include "evt/evt_pouch.h"
#include "evt/evt_snd.h"
#include "evt/evt_sub.h"
#include "evt/evt_window.h"
#include "mario/mario_cam.h"
#include "memory.h"
#include "libc_decls.h"
#include "evt/evt_story.h"
#include "driver/casedrv.h"
#if VERSION == VERSION_EU
#include "mario/mariost.h"
#endif

static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);
typedef struct {
    Vec pos;
    Vec delta;
} BeltWork;

static USER_FUNC(bg_cam_chk);
static USER_FUNC(mario_chk);
#if VERSION >= VERSION_JP
USER_FUNC(hit_group_chk);
#endif
static BOOL hitIsGroup(HitEntry* target, HitEntry* group);
static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling);

extern EvtWord evt_snd_stop[];
static BeroEntry bero_entry_data[15];
static const char* name_tbl[13];
const char* name_tbl2[6];
extern EvtWord move_left_right[];
extern EvtWord move_up_down[];
extern EvtWord move_r[];
/* moving-floor gimmick read by shikake_init: hit, mapobj, two motion params, time; a NULL mapobj ends the table */
typedef struct ShikakeMove {
    const char* hit;
    const char* mapobj;
    s32 param0;
    s32 param1;
    s32 time;
} ShikakeMove;
typedef struct ShikakeMoveTbl7 {
    ShikakeMove rows[7];
    const char* end[2];
} ShikakeMoveTbl7;
ShikakeMoveTbl7 left_right_tbl;
typedef struct ShikakeMoveTbl6 {
    ShikakeMove rows[6];
    const char* end[2];
} ShikakeMoveTbl6;
ShikakeMoveTbl6 up_down_tbl;
typedef struct ShikakeMoveTbl15 {
    ShikakeMove rows[15];
    const char* end[2];
} ShikakeMoveTbl15;
ShikakeMoveTbl15 r_tbl;
extern EvtWord shikake_init[];
extern EvtWord evt_bcv_sw[];
extern EvtWord evt_key_get[];
static s32 key_tbl[2];

static BOOL _hitIsGroupSub(HitEntry* target, HitEntry* node, BOOL checkSibling) {
    if (strcmp(target->joint->name, node->joint->name) == 0) {
        return TRUE;
    }
    if (node->child != NULL) {
        return _hitIsGroupSub(target, node->child, TRUE);
    }
    if (checkSibling && node->sibling != NULL) {
        return _hitIsGroupSub(target, node->sibling, TRUE);
    }
    return FALSE;
}

static BOOL hitIsGroup(HitEntry* target, HitEntry* group) {
    // whether target is group or one of its descendants
    return _hitIsGroupSub(target, group, FALSE);
}

static EVT_BEGIN(w_door_close)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
#endif
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(w_door_open)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(0.25f))
#endif
    CALL(evt_mapobj_trans, 0, STRING("S_door2_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door2_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_close)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
#endif
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
#if VERSION <= VERSION_DEMO_US
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.22167969f))
#else
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
#endif
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

EVT_BEGIN(evt_snd_stop)
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_17_CONVEYOR_BELT)
        CALL(evt_snd_sfxoff, GW(11))
    END_IF
    SET_VALUE(LW(0), 0)
    RETURN
EVT_END()

static EVT_BEGIN(evt_haikei_in)
    BEGIN_INLINE_EVENT
        CALL(evt_bero_exec_wait, 65536)
        WAIT_FRAMES(10)
        CALL(evt_mario_cam_keep_off)
        CALL(evt_mario_cam_y_on)
    END_INLINE_EVENT
    SET_VALUE(LW(0), 1)
    RETURN
EVT_END()

static BeroEntry bero_entry_data[] = {
    {
        "w_bero", // hitName
        1, // type
        10, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        (s32*)evt_snd_stop, // exitEvent
        "aji_18", // nextMapName
        "e_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        w_door_close, // enterAnimeArg
        w_door_open, // exitAnimeArg
    },
    {
        "e_bero", // hitName
        1, // type
        10, // sfxId
        BERO_DIR_AUTO, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        -1, // caseType
        (s32*)evt_snd_stop, // exitEvent
        "aji_14", // nextMapName
        "w_bero", // nextBeroName
        5, // enterAnimeType
        5, // exitAnimeType
        e_door_close, // enterAnimeArg
        e_door_open, // exitAnimeArg
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
        "dokan_6", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_2", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_7", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_3", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_8", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_4", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_9", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_5", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_10", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_6", // hitName
        4098, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)evt_haikei_in, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_1", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_7", // hitName
        4098, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)evt_haikei_in, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_2", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_8", // hitName
        4098, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)evt_haikei_in, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_3", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_9", // hitName
        4098, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)evt_haikei_in, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_4", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_10", // hitName
        4098, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        (s32*)evt_haikei_in, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_5", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_c", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_d", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {
        "dokan_d", // hitName
        2, // type
        0, // sfxId
        BERO_DIR_DOWN, // directionId
        BERO_POS_AUTO, // centerPosition
        0, 0, // centerPositionY..centerPositionZ
        -1, // length
        NULL, // enterEvent
        6, // caseType
        NULL, 0, // exitEvent..nextMapName
        "dokan_c", // nextBeroName
        1, // enterAnimeType
        1, // exitAnimeType
        0, 0, // enterAnimeArg..exitAnimeArg
    },
    {0},
};

static const char* name_tbl[] = {
    "A_ugoku_1",
    "A_ugoku_2",
    "A_ugoku_3",
    "A_ugoku_4",
    "A_ugoku_h_1",
    "A_ugoku_h_2",
    "A_ugoku_h_3",
    "A_ugoku_h_4",
    "A_ugoku_h_5",
    "A_ugoku_h_6",
    "A_ugoku_h_7",
    "A_ugoku_h_8",
    "A_ugoku_h_9",
};

const char* name_tbl2[] = {
    "A_zenmai1",
    "A_zenmai2",
    "A_zenmai3",
    "A__zenmai4",
    "A_zenmai5",
    "A_zenmai6",
};

static USER_FUNC(mario_chk) {
    BeltWork* work;
    s32 i;
    f32 angle;
    f32 delta;
    f32 dist;
    f32 rot;

    if (isFirstCall) {
        work = _mapAlloc(sizeof(BeltWork) * 13);
        for (i = 0; i < 13; i++) {
            work[i].pos = (Vec){0.0f, 0.0f, 0.0f};
            work[i].delta = (Vec){0.0f, 0.0f, 0.0f};
        }
        event->userdata[0] = (EvtWord)work;
        event->userdataf[1] = 0.0f;
        event->userdata[2] = 0;
    }
    work = (BeltWork*)event->userdata[0];
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        if (hit != NULL && hit->mapObj != NULL) {
            Vec pos = (Vec){hit->mapObj->transformMtx[0][3], hit->mapObj->transformMtx[1][3], hit->mapObj->transformMtx[2][3]};
            PSVECSubtract(&pos, &work[i].pos, &work[i].delta);
            work[i].pos = pos;
        }
    }
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        MarioWork* mario = marioGetPtr();
        if (hit != NULL && mario != NULL && mario->hitobjStandOn != NULL && hitIsGroup(mario->hitobjStandOn, hit)) {
            mario->floorMove.x = 10.0f * work[i].delta.x;
            mario->floorMove.z = 10.0f * work[i].delta.z;
            break;
        }
    }
    for (i = 0; i < 13; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl[i]);
        PartyEntry* party = partyGetPtr(0);
        if (hit != NULL && party != NULL && party->hitobjStandOn != NULL && hitIsGroup(party->hitobjStandOn, hit)) {
            party->floorMoveX = 10.0f * work[i].delta.x;
            party->floorMoveZ = 10.0f * work[i].delta.z;
            break;
        }
    }
    if (evtGetValue(event, GSW(GSW_STORY_PROGRESS)) >= STORY_STG7_17_CONVEYOR_BELT) {
        MarioWork* mario = marioGetPtr();
        PartyEntry* party = partyGetPtr(0);
        if (mario != NULL && mario->hitobjStandOn != NULL && hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_bel"))) {
            mario->floorMove.x = 0.6f;
#if VERSION == VERSION_EU
            mario->floorMove.x *= 60.0f / gp->framerate; // PAL: the push per frame is scaled to the frame rate
#endif
        }
        if (party != NULL && party->hitobjUnder != NULL && hitIsGroup(party->hitobjStandOn, hitNameToPtr("A_bel"))) {
            party->floorMoveX = 0.6f;
#if VERSION == VERSION_EU
            party->floorMoveX *= 60.0f / gp->framerate;
#endif
        }
    }
    for (i = 0; i < 6; i++) {
        HitEntry* hit = hitNameToPtr((const char*)name_tbl2[i]);
        MarioWork* mario = marioGetPtr();
        if (hit == NULL) {
            continue;
        }
        if (mario->hitobjStandOn == NULL) {
            event->userdataf[1] = 0.0f;
            event->userdata[2] = 0;
            continue;
        }
        if (hitIsGroup(mario->hitobjStandOn, hit)) {
            Vec v = (Vec){0.0f, 1.0f, 0.0f};
            Mtx m;
            mtxGetRotationElement(hit->mapObj->transformMtx, m, 'x', 'y');
            PSMTXMultVec(m, &v, &v);
            angle = angleABf(0.0f, 0.0f, v.x, v.y);
            delta = angle - event->userdataf[1];
            hitObjGetPos((const char*)name_tbl2[i], &v);
            dist = distABf(mario->position.x, mario->position.y, v.x, v.y);
            rot = angleABf(v.x, v.y, mario->position.x, mario->position.y);
            if ((HitEntry*)event->userdata[2] != NULL && strcmp(hit->joint->name, ((HitEntry*)event->userdata[2])->joint->name) == 0) {
                rot = 6.2831855f * (rot + delta) / 360.0f;
                mario->floorMove.x = (v.x + dist * (f32)sin(rot)) - mario->position.x;
                mario->floorMove.y = (v.y - dist * (f32)cos(rot)) - mario->position.y;
            }
            event->userdataf[1] = angle;
            event->userdata[2] = (EvtWord)hit;
            break;
        }
    }
    return EVT_RETURN_BLOCK;
}

EVT_BEGIN(move_left_right)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    SET_VALUE(LW(8), LW(3))
    SET_VALUE(LW(9), LW(4))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(evt_hit_bind_mapobj, LW(5), LW(6))
    END_IF
    MULTIPLY(LW(7), 100)
    MULTIPLY(LW(8), 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 11, LW(7), LW(8), LW(9))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), LW(0), 0, 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        WAIT_MS(300)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(7), LW(9))
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), LW(0), 0, 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
        WAIT_MS(300)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(move_up_down)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    SET_VALUE(LW(8), LW(3))
    SET_VALUE(LW(9), LW(4))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(evt_hit_bind_mapobj, LW(5), LW(6))
    END_IF
    MULTIPLY(LW(7), 100)
    MULTIPLY(LW(8), 100)
#if VERSION >= VERSION_JP
    SET_VALUE(LW(4), LW(8))
    IF_STR_EQUAL(LW(5), STRING("A_ugoku_2"))
        SET_VALUE(LW(3), 1)
        SET_VALUE(GF(1), 0)
        BEGIN_SIBLING_EVENT
            LOOP(0)
                CALL(evt_mario_get_name_hitobj_head, LW(10))
                CALL(hit_group_chk, LW(10), LW(5), LW(10))
                IF_INT_NOT_EQUAL(LW(10), 0)
                    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                    IF_FLOAT_GREATER(LW(1), FLOAT(0.099609375f))
                        SET_VALUE(GF(1), 1)
                    END_IF
                END_IF
                WAIT_FRAMES(1)
            END_LOOP
        END_SIBLING_EVENT
    ELSE
        SET_VALUE(LW(3), 0)
    END_IF
#endif
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 11, LW(7), LW(8), LW(9))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), 0, LW(0), 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
#if VERSION >= VERSION_JP
        IF_INT_NOT_EQUAL(LW(3), 0)
            IF_INT_NOT_EQUAL(GF(1), 0)
#if VERSION == VERSION_JP
                MULTIPLY_FLOAT(LW(0), FLOAT(100.0f))
#endif
                GOTO(5)
            END_IF
        END_IF
#endif
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
#if VERSION <= VERSION_DEMO_US
        WAIT_MS(300)
#else
        LABEL(5)
        IF_INT_NOT_EQUAL(LW(3), 0)
            IF_INT_EQUAL(GF(1), 0)
                SET_VALUE(LW(8), LW(4))
            ELSE
#if VERSION >= VERSION_US
                MULTIPLY_FLOAT(LW(0), FLOAT(100.0f))
#endif
                SET_VALUE(LW(8), LW(0))
            END_IF
            WAIT_MS(300)
            LOOP(0)
                IF_INT_EQUAL(GF(1), 0)
                    BREAK_LOOP
                END_IF
                SET_VALUE(GF(1), 0)
                WAIT_MS(1000)
            END_LOOP
        ELSE
            WAIT_MS(300)
        END_IF
#endif
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        CALL(evt_sub_intpl_msec_init, 11, LW(8), LW(7), LW(9))
        LABEL(1)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        CALL(evt_mapobj_trans, 1, LW(6), 0, LW(0), 0)
        IF_INT_NOT_EQUAL(LW(5), 0)
            CALL(evt_hit_bind_update, LW(5))
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(1)
        END_IF
#if VERSION >= VERSION_JP
        SET_VALUE(LW(8), LW(4))
#endif
        WAIT_MS(300)
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

EVT_BEGIN(move_r)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    SET_VALUE(LW(8), LW(3))
    SET_VALUE(LW(9), LW(4))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(evt_hit_bind_mapobj, LW(5), LW(6))
    END_IF
    MULTIPLY(LW(7), 100)
    MULTIPLY(LW(8), 100)
    LOOP(0)
        CALL(evt_sub_intpl_msec_init, 0, LW(7), LW(8), LW(9))
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
            CALL(evt_mapobj_rotate, 1, LW(6), 0, 0, LW(0))
            IF_INT_NOT_EQUAL(LW(5), 0)
                CALL(evt_hit_bind_update, LW(5))
            END_IF
            IF_INT_EQUAL(GF(0), 1)
                BREAK_LOOP
            END_IF
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(0)
            IF_INT_EQUAL(GF(0), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_LOOP
    RETURN
EVT_END()

ShikakeMoveTbl7 left_right_tbl = {
    {
        {"A_ugoku_1", "S_ugoku_1", 0, -150, 3000},
        {"A_ugoku_3", "S_ugoku_3", 0, 100, 1500},
        {"A_ugoku_4", "S_ugoku_4", 0, -100, 1500},
        {"A_ugoku_h_1", "S_ugoku_h_1", -30, 200, 3000},
        {"A_ugoku_h_2", "S_ugoku_h_2", -50, 50, 3000},
        {"A_ugoku_h_3", "S_ugoku_h_3", 50, -50, 3000},
        {"A_ugoku_h_7", "S_ugoku_h_7", -50, 80, 4500},
    },
    {NULL, NULL},
};

ShikakeMoveTbl6 up_down_tbl = {
    {
        {"A_ugoku_2", "S_ugoku_2", 0, -150, 2800},
        {"A_ugoku_h_4", "S_ugoku_h_4", 0, 100, 3000},
        {"A_ugoku_h_5", "S_ugoku_h_5", 0, -200, 4000},
#if VERSION <= VERSION_DEMO_US
        {"A_ugoku_h_6", "S_ugoku_h_6", 0, -150, 3000},
#else
        {"A_ugoku_h_6", "S_ugoku_h_6", 40, -150, 3000},
#endif
        {"A_ugoku_h_8", "S_ugoku_h_8", 20, -100, 2000},
        {"A_ugoku_h_9", "S_ugoku_h_9", -100, 20, 2000},
    },
    {NULL, NULL},
};

ShikakeMoveTbl15 r_tbl = {
    {
        {"A_zenmai1", "S_zenmai1", 0, 360, 6000},
        {"A_zenmai2", "S_zenmai2", 0, -360, 6000},
        {"A_zenmai3", "S_zenmai3", 0, 360, 3000},
        {"A__zenmai4", "S_zenmai4", 0, 360, 9000},
        {"A_zenmai5", "S_zenmai5", 0, -360, 6000},
        {"A_zenmai6", "S_zenmai6", 0, -360, 3000},
        {NULL, "S_zen1", 0, 360, 6000},
        {NULL, "S_zen2", 0, -360, 3000},
        {NULL, "S_zen3", 0, -360, 6000},
        {NULL, "S_zen4", 0, 360, 6000},
        {NULL, "S_zen5", 0, 360, 6000},
        {NULL, "S_zen6", 0, -360, 3000},
        {NULL, "S_zen7", 0, 360, 6000},
        {NULL, "S_zen8", 0, -360, 6000},
        {NULL, "S_zen9", 0, 360, 3000},
    },
    {NULL, NULL},
};

EVT_BEGIN(shikake_init)
    SET_VALUE(GF(0), 0)
    SET_INT_READ_ADDR(PTR(&left_right_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        READ_INT3(LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(move_left_right)
    END_LOOP
    SET_INT_READ_ADDR(PTR(&up_down_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        READ_INT3(LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(move_up_down)
    END_LOOP
    SET_INT_READ_ADDR(PTR(&r_tbl))
    LOOP(0)
        READ_INT2(LW(0), LW(1))
        READ_INT3(LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        SPAWN_EVENT(move_r)
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(mario_chk)
    END_INLINE_EVENT
    RETURN
EVT_END()

static EVT_BEGIN(evt_sw)
    CALL(evt_mario_key_onoff, 0)
    SET_VALUE(GF(0), 1)
    CALL(evt_cam3d_evt_set, 475, 425, 743, 475, 325, 0, 1000, 11)
    WAIT_MS(2500)
    CALL(evt_paper_entry, STRING("OFF_hei_07"))
    CALL(evt_img_entry, STRING("img"))
    CALL(evt_img_set_paper, STRING("img"), STRING("OFF_hei_07"))
    CALL(evt_offscreen_entry, STRING("ofs"))
    CALL(evt_img_onoff, STRING("img"), 0)
    CALL(evt_mapobj_set_offscreen, 1, STRING("S_kaidan"), STRING("ofs"))
    CALL(evt_offscreen_get_boundingbox, STRING("ofs"), LW(10), LW(11), LW(12), LW(13))
    CALL(evt_img_alloc_capture, STRING("img"), 0, 0, 1, LW(10), LW(11), LW(12), LW(13))
    WAIT_FRAMES(1)
    CALL(evt_img_clear_virtual_point, STRING("img"))
    CALL(evt_img_set_paper_anim, STRING("img"), STRING("A_1"))
    CALL(evt_img_onoff, STRING("img"), 1)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_OFF7_KAIDAN_APPEAR1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kaidan"), MAPOBJ_FLAG_HIDE)
    CALL(evt_hitobj_onoff, STRING("A_kaidan"), 1, 1)
    WAIT_MS(1800)
    CALL(evt_img_wait_animend, STRING("img"))
    CALL(evt_img_onoff, STRING("img"), 0)
    CALL(evt_img_release, STRING("img"))
    CALL(evt_mapobj_clear_offscreen, 1, STRING("S_kaidan"))
    CALL(evt_offscreen_delete, STRING("ofs"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_18_OFF_SCREEN_STAIRS)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_off, 1000, 11)
    WAIT_MS(500)
    SET_VALUE(GF(0), 0)
    WAIT_MS(500)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static EVT_BEGIN(evt_hari)
    SET_VALUE(LW(8), LW(0))
    SET_VALUE(LW(2), 0)
    SET_VALUE(LF(0), 0)
    LOOP(0)
        CALL(evt_sub_random, 900, LW(3))
        IF_INT_EQUAL(LF(0), 0)
            MULTIPLY(LW(3), -1)
            SET_VALUE(LF(0), 1)
        ELSE
            SET_VALUE(LF(0), 0)
        END_IF
        CALL(evt_sub_random, 1500, LW(9))
        ADD(LW(9), 1500)
        CALL(evt_sub_intpl_msec_init, 11, LW(2), LW(3), LW(9))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(10.0f))
        CALL(evt_mapobj_rotate, 1, LW(8), 0, 0, LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
        SET_VALUE(LW(2), LW(3))
    END_LOOP
    RETURN
EVT_END()

static EVT_BEGIN(evt_ramp)
    CALL(evt_mapobj_get_position, STRING("S_bel"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CONVEYER_MOVE1"), LW(0), LW(1), LW(2), GW(11))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_pato1"), MAPOBJ_FLAG_HIDE)
    BEGIN_INLINE_EVENT
        SET_FLOAT_VALUE(LW(0), FLOAT(0.0f))
        LOOP(0)
            CALL(evt_mapobj_rotate, 1, STRING("S_pato1"), 0, LW(0), 0)
            ADD_FLOAT(LW(0), FLOAT(10.0f))
            IF_FLOAT_GREATER(LW(0), FLOAT(360.0f))
                SUBTRACT_FLOAT(LW(0), FLOAT(360.0f))
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    SET_VALUE(LW(0), STRING("S_hari01"))
    SPAWN_EVENT(evt_hari)
    SET_VALUE(LW(0), STRING("S_hari02"))
    SPAWN_EVENT(evt_hari)
    SET_VALUE(LW(0), STRING("S_hari03"))
    SPAWN_EVENT(evt_hari)
    SET_VALUE(LW(0), STRING("S_hari04"))
    SPAWN_EVENT(evt_hari)
    RETURN
EVT_END()

EVT_BEGIN(evt_bcv_sw)
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_17_CONVEYOR_BELT)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_cam3d_evt_set, -575, 152, 578, -575, 57, 37, 1000, 11)
    WAIT_MS(1000)
    WAIT_MS(1000)
    CALL(evt_mapobj_get_position, STRING("S_bel"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_CONVEYER_ACTIVE1"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_1_1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_2_1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_3_1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_4_1"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_1_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_2_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_3_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_4_2"), MAPOBJ_FLAG_HIDE)
    CALL(evt_map_playanim, STRING("kon"), 1, 0)
    SPAWN_EVENT(evt_ramp)
    WAIT_MS(3000)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(evt_key_get)
    SET_VALUE(GSWF(GSWF_AJI13_CARD_KEY_TAKEN), 1)
    RETURN
EVT_END()

static s32 key_tbl[] = {
    ITEM_CARD_KEY_0x20, -1,
};

static EVT_BEGIN(evt_door_msg)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_pouch_check_item, ITEM_CARD_KEY_0x20, LW(0))
    IF_INT_LESS(LW(0), 1)
        CALL(evt_msg_print, 0, STRING("stg7_aji_67"), 0, 0)
        CALL(evt_mario_key_onoff, 1)
        RETURN
    END_IF
#if VERSION <= VERSION_DEMO_US
    CALL(evt_win_item_select, PTR(key_tbl), LW(0))
#else
    CALL(evt_win_item_select, 0, PTR(key_tbl), LW(0), 0)
#endif
    IF_INT_NOT_EQUAL(LW(0), -1)
        CALL(evt_pouch_remove_item, LW(0), LW(1))
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(bero_case_switch_on)
        SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG7_19_THE_DOOR_TO_LORD_CRUMP)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_kagi1_mid"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi1_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_lights1_m"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_lights1_r"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG7_DOOR_UNLOCK1"), LW(0), LW(1), LW(2), 0)
        CALL(evt_exit_case_evt)
    END_IF
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

EVT_BEGIN(aji_13_init_evt)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG7_AJI7"))
#if VERSION >= VERSION_JP
    CALL(evt_snd_set_rev_mode, 1)
#endif
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(evt_bero_info_run)
    CALL_CHILD(shikake_init)
    CALL(evt_map_entry_airport_harbor, 0, STRING("hikou1"), STRING("A_hikou1"))
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_ami2"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_dai5"), MAPOBJ_FLAG_BBOX_CULL)
    CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("S_dai3"), MAPOBJ_FLAG_BBOX_CULL)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_17_CONVEYOR_BELT)
        CALL(evt_mobj_switch_blue, 0, STRING("bcv_sw"), -150, 0, 100, PTR(evt_bcv_sw), GSWF(GSWF_AJI13_CONVEYOR_SWITCH_PRESSED))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_pato1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_1_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_2_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_3_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_4_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_1_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_2_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_3_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_4_2"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_map_playanim, STRING("kon"), 1, 0)
        CALL_CHILD(evt_ramp)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_1_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_2_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_3_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("meta_4_1"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_1_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_2_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_3_2"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("meta_4_2"), MAPOBJ_FLAG_HIDE)
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_AJI13_CARD_KEY_TAKEN), 0)
        CALL(evt_item_entry, STRING("key"), ITEM_CARD_KEY_0x20, -50, 100, 100, ITEM_ENTRY_FIXED, -1, PTR(evt_key_get))
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_18_OFF_SCREEN_STAIRS)
        CALL(evt_mobj_switch_blue, 0, STRING("sw"), 650, 200, 100, PTR(evt_sw), GSWF(GSWF_AJI13_STAIRS_SWITCH_PRESSED))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kaidan"), MAPOBJ_FLAG_HIDE)
        CALL(evt_hitobj_onoff, STRING("A_kaidan"), 1, 0)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG7_19_THE_DOOR_TO_LORD_CRUMP)
        SET_VALUE(LW(0), STRING("e_bero"))
        CALL_CHILD(bero_case_switch_off)
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("A_kagi1"), 0, PTR(evt_door_msg), 0)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi1_mid"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_lights1_m"), MAPOBJ_FLAG_HIDE)
    ELSE
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_kagi1_aka"), MAPOBJ_FLAG_HIDE)
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("S_lights1_r"), MAPOBJ_FLAG_HIDE)
    END_IF
    CALL(evt_mobj_save_blk, STRING("mobj_save"), 200, 60, 100, 0, 0)
    CALL(evt_mobj_recovery_blk, STRING("mobj_recover"), 10, 300, 60, 100, 0, 0)
    CALL(evt_item_entry, STRING("item00"), ITEM_ULTRA_SHROOM, -670, 320, -450, ITEM_ENTRY_FIXED, GSWF(GSWF_AJI13_ULTRA_SHROOM), 0)
#if VERSION >= VERSION_JP
    CALL(evt_item_set_scale, STRING("item00"), FLOAT(0.5996094f))
#endif
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG7_20_LORD_CRUMP_DEFEATED)
        CALL(evt_npc_check_delete, STRING("軍団ザコ魔法使い"))
        CALL(evt_npc_check_delete, STRING("バリアーンＺ"))
    END_IF
    SPAWN_EVENT(evt_emergency)
    BEGIN_INLINE_EVENT
        CALL(bg_cam_chk)
    END_INLINE_EVENT
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
USER_FUNC(hit_group_chk) {
    EvtWord* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    HitEntry* hit1 = name1 != NULL ? hitNameToPtr(name1) : NULL;
    HitEntry* hit2 = name2 != NULL ? hitNameToPtr(name2) : NULL;

    if (hit1 != NULL && hit2 != NULL && hitIsGroup(hit1, hit2)) {
        evtSetValue(event, args[2], TRUE);
    } else {
        evtSetValue(event, args[2], FALSE);
    }
    return EVT_RETURN_DONE;
}
#endif

static USER_FUNC(bg_cam_chk) {
    CameraEntry* camera = camGetPtr(CAMERA_3D);

#if VERSION <= VERSION_DEMO_US
    if (marioBgmodeChk() && (camera->flags & CAM_FLAG_FOLLOW_Y_OFF)) {
#else
    if (marioBgmodeChk() && (camera->flags & CAM_FLAG_FOLLOW_Y_OFF) && marioGetPtr()->airTimer == 0) {
#endif
        camFollowYOn();
    }
    return EVT_RETURN_BLOCK;
}
