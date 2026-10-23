#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "mario/mario.h"
#include "pmario_sound.h"
#include "eff/n64/eff_akari_charge_n64.h"
#include "party.h"
#include "driver/hitdrv.h"
#include "stdio.h"
#include "string.h"

void mapGrpFlagOn(const char* name, u32 flags);
void mapGrpFlagOff(const char* name, u32 flags);
void hitGrpAttrOn(const char* name, u32 flags);
void hitGrpAttrOff(const char* name, u32 flags);
int sscanf(const char* s, const char* format, ...);

USER_FUNC(evt_bero_get_info);
USER_FUNC(evt_hit_damage_return_set);
USER_FUNC(evt_item_entry);
USER_FUNC(evt_item_get_item);
USER_FUNC(evt_map_playanim);
USER_FUNC(evt_mapobj_flag_onoff);
USER_FUNC(evt_mapobj_trans);
USER_FUNC(evt_mario_key_onoff);
USER_FUNC(evt_mario_set_dir);
USER_FUNC(evt_mobj_badgeblk);
USER_FUNC(evt_mobj_get_position);
USER_FUNC(evt_mobj_itembox);
USER_FUNC(evt_mobj_wait_animation_end);
USER_FUNC(evt_snd_bgmon);
USER_FUNC(evt_snd_envon);
USER_FUNC(evt_snd_set_rev_mode);
static USER_FUNC(hikaru_off);
static USER_FUNC(mario_chk);
static USER_FUNC(thunder_main);
extern s32 evt_bero_info_run[];
extern s32 evt_emergency[];

__declspec(section ".data") u64 fd_aji_12_negone_one_374;
__declspec(section ".data") s32 fd_aji_12_neg_one_382[1];
__declspec(section ".data") s32 fd_aji_12___local_PI_383[1];
__declspec(section ".data") s32 fd_aji_12___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_aji_12_one_negone_373;
__declspec(section ".data") s32 fd_aji_12___local_PIO2_384[1];
__declspec(section ".data") s32 fd_aji_12_one_381[1];
__declspec(section ".data") u64 fd_aji_12_negone_one_360;
__declspec(section ".data") s32 fd_aji_12_neg_one_365[1];
__declspec(section ".data") s32 fd_aji_12___local_PI_366[1];
__declspec(section ".data") s32 fd_aji_12___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_aji_12_one_negone_359;
__declspec(section ".data") s32 fd_aji_12___local_PIO2_367[1];
__declspec(section ".data") s32 fd_aji_12_one_364[1];
static s32 e_door_close[22];
static s32 e_door_open[22];
static s32 bero_entry_data[30];
s32 hit_list[50];
static s32 evt_box[89];
static __declspec(section ".data") s32 dmgReturnPt[8];
static s32 hikaru_yuka_init[40];
s32 aji_12_init_evt[71];

__declspec(section ".data") u64 fd_aji_12_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_12_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_12___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_12___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_12_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_12___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_12_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_aji_12_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_aji_12_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_aji_12___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_aji_12___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_aji_12_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_aji_12___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_aji_12_one_364[] = {
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
    -1, 0, (s32)"aji_01", (s32)"w_bero_4", 327685, (s32)e_door_close, (s32)e_door_open, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,
};

s32 hit_list[] = {
    (s32)"A_hikaru_01", (s32)"A_hikaru_02", (s32)"A_hikaru_03", (s32)"A_hikaru_04", (s32)"A_hikaru_05", (s32)"A_hikaru_06", (s32)"A_hikaru_07", (s32)"A_hikaru_08",
    (s32)"A_hikaru_09", (s32)"A_hikaru_10", (s32)"A_hikaru_11", (s32)"A_hikaru_12", (s32)"A_hikaru_13", (s32)"A_hikaru_14", (s32)"A_hikaru_15", (s32)"A_hikaru_16",
    (s32)"A_hikaru_17", (s32)"A_hikaru_18", (s32)"A_hikaru_19", (s32)"A_hikaru_20", (s32)"A_hikaru_21", (s32)"A_hikaru_22", (s32)"A_hikaru_23", (s32)"A_hikaru_24",
    (s32)"A_hikaru_25", (s32)"A_hikaru_26", (s32)"A_hikaru_27", (s32)"A_hikaru_08", (s32)"A_hikaru_28", (s32)"A_hikaru_29", (s32)"A_hikaru_30", (s32)"A_hikaru_31",
    (s32)"A_hikaru_32", (s32)"A_hikaru_12", (s32)"A_hikaru_13", (s32)"A_hikaru_33", (s32)"A_hikaru_15", (s32)"A_hikaru_34", (s32)"A_hikaru_35", (s32)"A_hikaru_36",
    (s32)"A_hikaru_37", (s32)"A_hikaru_38", (s32)"A_hikaru_39", (s32)"A_hikaru_40", (s32)"A_hikaru_41", (s32)"A_hikaru_42", (s32)"A_hikaru_41", (s32)"A_hikaru_40",
    (s32)"A_hikaru_43", (s32)"A_hikaru_44",
};

static EVT_BEGIN(evt_box)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mobj_get_position, STRING("box"), LW(0), LW(1), LW(2))
    CALL(evt_item_entry, STRING("dummy"), 30, LW(0), LW(1), LW(2), 17, -1, 0)
    CALL(evt_mobj_wait_animation_end, STRING("box"))
    CALL(evt_item_get_item, STRING("dummy"))
    SET_VALUE(GSWF(4183), 1)
    WAIT_FRAMES(2)
    CALL(hikaru_off)
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

static __declspec(section ".data") s32 dmgReturnPt[] = {
    (s32)"mod_01", 0, -998637568, 0, 0, 0, 0, 0,
};

static EVT_BEGIN(hikaru_yuka_init)
    CALL(evt_mobj_itembox, STRING("box"), -350, 10, -10, 2, 0, PTR(evt_box), GSWF(4179))
    CALL(evt_hit_damage_return_set, PTR(dmgReturnPt))
    BEGIN_INLINE_EVENT
        CALL(thunder_main)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(mario_chk)
    END_INLINE_EVENT
    CALL(evt_mapobj_flag_onoff, 1, 0, STRING("yukayu1"), 1)
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("yukayu2"), 1)
    CALL(evt_map_playanim, STRING("denyuka"), 1, 0)
    RETURN
EVT_END()

EVT_BEGIN(aji_12_init_evt)
    CALL(evt_snd_bgmon, 512, STRING("BGM_STG7_DUN2"))
    CALL(evt_snd_envon, 272, STRING("ENV_STG7_AJI1"))
    CALL(evt_snd_set_rev_mode, 1)
    SET_VALUE(LW(0), PTR(bero_entry_data))
    CALL(evt_bero_get_info)
    CALL_CHILD(PTR(evt_bero_info_run))
    CALL(evt_mapobj_flag_onoff, 1, 1, STRING("no1"), 1)
    IF_INT_EQUAL(GSWF(4183), 0)
        CALL_CHILD(PTR(hikaru_yuka_init))
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("ato"), 1)
        ELSE
        CALL(hikaru_off)
        CALL(evt_mapobj_flag_onoff, 1, 1, STRING("yukayu1"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("yukayu2"), 1)
        CALL(evt_mapobj_flag_onoff, 1, 0, STRING("ato"), 1)
    END_IF
    CALL(evt_mobj_badgeblk, STRING("mobj00"), 170, 60, 120, 144, 0, GSWF(4214), 0)
    SPAWN_EVENT(PTR(evt_emergency))
    RETURN
EVT_END()

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

static USER_FUNC(mario_chk) {
    s32 n;
    char name[256];
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;
    HitEntry* hit;
    s32 i;
    s32 j;

    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    if (evtGetValue(NULL, GSWF(4183))) {
        return EVT_RETURN_DONE;
    }
    for (i = 1; i <= 44; i++) {
        sprintf(name, "hikaru_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "nashi_%02d", i);
        mapGrpFlagOff(name, 1);
    }
    for (i = 0; i < 50; i++) {
        hitGrpAttrOn((const char*)hit_list[i], 0x800);
    }
    party = partyGetPtr(0);
    if (party != NULL && party->currentMemberId == 4 && (party->flags & 0x100)) {
        hit = mario->hitobjStandOn;
        if (hit == NULL) {
            hit = mario->hitobjJumpFrom;
        }
    } else {
        hit = (HitEntry*)mario->hitobjUnder;
    }
    if (hit == NULL) {
        mapGrpFlagOff("hikaru_01", 1);
        mapGrpFlagOn("nashi_01", 1);
        hitGrpAttrOff("A_hikaru_01", 0x800);
        event->userdata[2] = 0;
    } else if (strncmp(hitGetName(hit), "A_hikaru_", strlen("A_hikaru_")) != 0) {
        mapGrpFlagOff("hikaru_01", 1);
        mapGrpFlagOn("nashi_01", 1);
        hitGrpAttrOff("A_hikaru_01", 0x800);
        event->userdata[2] = 0;
    } else if (strcmp(hitGetName(hit), "A_hikaru_01") == 0 && event->userdata[2] == 0) {
        event->userdata[2] = 1;
        event->userdata[0] = 0;
        event->userdata[1] = 0;
    }
    n = 0;
    j = event->userdata[0];
    if (j >= 50) {
        j = 49;
    }
    sscanf((const char*)hit_list[j], "A_hikaru_%02d", &n);
    sprintf(name, "hikaru_%02d", n);
    mapGrpFlagOff(name, 1);
    sprintf(name, "nashi_%02d", n);
    mapGrpFlagOn(name, 1);
    sprintf(name, "A_hikaru_%02d", n);
    hitGrpAttrOff(name, 0x800);
    j++;
    if (j >= 50) {
        j = 49;
    }
    sscanf((const char*)hit_list[j], "A_hikaru_%02d", &n);
    sprintf(name, "hikaru_%02d", n);
    mapGrpFlagOff(name, 1);
    sprintf(name, "nashi_%02d", n);
    mapGrpFlagOn(name, 1);
    sprintf(name, "A_hikaru_%02d", n);
    hitGrpAttrOff(name, 0x800);
#ifdef VERSION_G8ME01
    j++;
    if (j >= 50) {
        j = 49;
    }
    sscanf((const char*)hit_list[j], "A_hikaru_%02d", &n);
    sprintf(name, "hikaru_%02d", n);
    mapGrpFlagOff(name, 1);
    sprintf(name, "nashi_%02d", n);
    mapGrpFlagOn(name, 1);
    sprintf(name, "A_hikaru_%02d", n);
    hitGrpAttrOff(name, 0x800);
#endif
    event->userdata[1]++;
    if (event->userdata[1] > (event->userdata[2] == 0 ? 20 : 60)) {
        event->userdata[1] = 0;
        event->userdata[0]++;
        if (event->userdata[0] > 50) {
            event->userdata[0] = 0;
        }
    }
    return EVT_RETURN_BLOCK;
}

static USER_FUNC(hikaru_off) {
    char name[256];
    s32 i;

    for (i = 1; i <= 44; i++) {
        sprintf(name, "hikaru_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "nashi_%02d", i);
        mapGrpFlagOn(name, 1);
        sprintf(name, "A_hikaru_%02d", i);
        hitGrpAttrOff(name, 0x800);
    }
    hitGrpAttrOff("A_no1\0\0", 0x800);
    return EVT_RETURN_DONE;
}

