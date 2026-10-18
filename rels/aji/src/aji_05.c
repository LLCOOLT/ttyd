#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "stdio.h"
#include "mario/mario.h"
#include "party.h"
#include "driver/hitdrv.h"
#include "string.h"
#include "pmario_sound.h"
#include "eff/n64/eff_akari_charge_n64.h"

void mapGrpFlagOn(const char* name, u32 flags);
void mapGrpFlagOff(const char* name, u32 flags);

USER_FUNC(_hikaru_off);
USER_FUNC(_hikaru_on);
USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hitobj_attr_onoff);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
static USER_FUNC(ride_chk);
static USER_FUNC(thunder_main);
static USER_FUNC(loop_onoff);
extern s32 evt_bero_info_run[];
extern s32 evt_emergency[];
extern s32 evt_hit_damage_return_set[];
extern s32 evt_map_playanim[];
extern s32 evt_mobj_itembox[];

__declspec(section ".data") u64 fd_aji_05_negone_one_374;
__declspec(section ".data") s32 fd_aji_05_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_05___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_05___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_05_one_negone_373;
__declspec(section ".data") s32 fd_aji_05___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_05_one_381[1];
__declspec(section ".data") u64 fd_aji_05_negone_one_360;
__declspec(section ".data") s32 fd_aji_05_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_05___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_05___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_05_one_negone_359;
__declspec(section ".data") s32 fd_aji_05___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_05_one_364[1];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[30];
static s32 evt_box[95];
static __declspec(section ".data") s32 hikaru_on[4];
static __declspec(section ".data") s32 hikaru_off[4];
static __declspec(section ".data") s32 dmgReturnPt[8];
static s32 hikaru_yuka_init[48];
s32 aji_05_init_evt[77];

__declspec(section ".data") u64 fd_aji_05_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_05_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_05___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_05___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_05_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_05___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_05_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_05_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_05_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_05___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_05___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_05_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_05___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_05_one_364[] = {
    1065353216,
};

static EVT_BEGIN(e_door_close)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static EVT_BEGIN(e_door_open)
    MULTIPLY_FLOAT(LW(0), FLOAT(-0.25f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_1"), 0, 0, LW(0))
    MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
    CALL(evt_mapobj_trans, 0, STRING("S_door1_2"), 0, 0, LW(0))
    RETURN
EVT_END()

static s32 bero_entry_data[] = {
    (s32)"e_bero", 65546, 20000, 100000, 0, 0, -1, 0,
    -1, 0, (s32)"aji_01", (s32)"w_bero_3", 327685, (s32)e_door_close, (s32)e_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(evt_box)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("dummy"), 29, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("dummy"))
    CALL(evt_hitobj_attr_onoff, 1, 0, STRING("A_no1"), 2048)
    SET_VALUE(GSWF(4182), 1)
    WAIT_FRAMES(1)
    CALL_CHILD(PTR(hikaru_off))
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    LOOP(5)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("yukayu1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("yukayu2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ato"), 1)
        WAIT_MS(150)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("yukayu1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("yukayu2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ato"), 1)
        WAIT_MS(150)
    END_LOOP
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(hikaru_on)
    CALL(_hikaru_on)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(hikaru_off)
    CALL(_hikaru_off)
    RETURN
EVT_END()

static __declspec(section ".data") s32 dmgReturnPt[] = {
    (s32)"mod_01", 0, -998637568, 0, 0, 0, 0, 0,
};

static s32 hikaru_yuka_init[] = {
    65630, (s32)hikaru_off, 327771, (s32)evt_hitobj_attr_onoff, 1, 1, (s32)"A_no1", 2048,
    589915, (s32)evt_mobj_itembox, (s32)"box", -255, 10, -10, 2, 0,
    (s32)evt_box, -129995822, 131163, (s32)evt_hit_damage_return_set, (s32)dmgReturnPt, 107, 65627, (s32)ride_chk,
    109, 107, 65627, (s32)thunder_main, 109, 327771, (s32)evt_mapobj_flag_onoff, 1,
    0, (s32)"yukayu1", 1, 327771, (s32)evt_mapobj_flag_onoff, 1, 1, (s32)"yukayu2",
    1, 262235, (s32)evt_map_playanim, (s32)"denyuka", 1, 0, 1, 2,
};

EVT_BEGIN(aji_05_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI1"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("no1"), 1)
    IF_INT_EQUAL(GSWF(4182), 0)
        CALL_CHILD(PTR(hikaru_yuka_init))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ato"), 1)
        ELSE
        CALL_CHILD(PTR(hikaru_off))
        CALL(evt_hitobj_attr_onoff, 1, 0, STRING("A_no1"), 2048)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("yukayu1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("yukayu2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ato"), 1)
    END_IF
    CALL(evt_mobj_badgeblk, STRING("mobj00"), -75, 60, -125, 138, 0, GSWF(4212), 0)
    SPAWN_EVENT(PTR(evt_emergency))
    RETURN
EVT_END()

static USER_FUNC(ride_chk) {
    static s32 onoff[24];
    char hitName[64];
    char name[64];
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    HitEntry* hit;
    s32 i;

    if (isFirstCall) {
        memset(onoff, 0, sizeof(onoff));
    }
    if (party != NULL && party->currentMemberId == 4 && (party->flags & 0x100)) {
        hit = mario->hitobjStandOn;
        if (hit == NULL) {
            hit = mario->hitobjJumpFrom;
        }
    } else {
        hit = (HitEntry*)mario->hitobjUnder;
    }
    // panels stay lit for 30 frames after being touched
    for (i = 0; i < 24; i++) {
        if (hit != NULL) {
            sprintf(hitName, "A_hikaru_%02d", i + 1);
            if (strcmp(hit->joint->name, hitName) == 0) {
                onoff[i] = 30;
            }
        }
    }
    for (i = 0; i < 24; i++) {
        if (onoff[i] > 0) {
            onoff[i]--;
        }
        if (onoff[i] != 0) {
            sprintf(name, "hikaru_%02d", i + 1);
            mapGrpFlagOff(name, 1);
            sprintf(name, "nashi_%02d", i + 1);
            mapGrpFlagOn(name, 1);
        } else {
            sprintf(name, "hikaru_%02d", i + 1);
            mapGrpFlagOn(name, 1);
            sprintf(name, "nashi_%02d", i + 1);
            mapGrpFlagOff(name, 1);
        }
    }
    if (evtGetValue(event, GSWF(4182))) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(thunder_main) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    if (event->userdata[0] == 0) {
        if (mario->currMotionId == 0x20) {
            EffectEntry* eff;

            event->userdata[0] = 1;
            psndSFXOn_3D("SFX_STG7_ELECTRIC_SHOCK1", &mario->position);
            eff = effAkariChargeN64Entry(0, 100, mario->position.x, 30.0f + mario->position.y, mario->position.z, 1.0f);
            ((s32*)eff->userdata)[6] = 30;
            ((s32*)eff->userdata)[7] = 231;
            ((s32*)eff->userdata)[8] = 219;
            ((s32*)eff->userdata)[10] = 0;
            ((s32*)eff->userdata)[11] = 0;
            ((s32*)eff->userdata)[12] = 0;
        }
    } else if (mario->currMotionId != 0x20) {
        event->userdata[0] = 0;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_hikaru_off) {
    char name[64];
    s32 i;

    for (i = 1; i < 25; i++) {
        sprintf(name, "hikaru_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "nashi_%02d", i);
        mapGrpFlagOn(name, 1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(_hikaru_on) {
    char name[64];
    s32 i;

    for (i = 1; i < 25; i++) {
        sprintf(name, "hikaru_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "nashi_%02d", i);
        mapGrpFlagOff(name, 1);
    }
    return EVT_RETURN_DONE;
}

static USER_FUNC(loop_onoff) {
    char name[64];
    s32 i;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        event->userdata[2] = 0;
    }
    // light the panels up one after another, twice
    event->userdata[0]++;
    if (event->userdata[0] > 2) {
        event->userdata[0] = 0;
        event->userdata[1]++;
        if (event->userdata[1] >= 25) {
            event->userdata[1] = 0;
            event->userdata[2]++;
            if (event->userdata[2] > 1) {
                return EVT_RETURN_DONE;
            }
        }
    }
    for (i = 1; i < 25; i++) {
        if (i == event->userdata[1]) {
            sprintf(name, "hikaru_%02d", i);
            mapGrpFlagOff(name, 1);
            sprintf(name, "nashi_%02d", i);
            mapGrpFlagOn(name, 1);
        } else {
            sprintf(name, "hikaru_%02d", i);
            mapGrpFlagOn(name, 1);
            sprintf(name, "nashi_%02d", i);
            mapGrpFlagOff(name, 1);
        }
    }
    return EVT_RETURN_BLOCK;
}

