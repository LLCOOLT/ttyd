#pragma optimize_for_size on
#include <dolphin/mtx.h>
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"

double cos(double);
double sin(double);
void btlDispTexPlane2(Mtx, u32, GXColor);
void btlDispTexPlane3(Mtx, u32, GXColor, GXColor, GXColor, GXColor);
void* memcpy(void*, const void*, unsigned long);

USER_FUNC(btlevtcmd_ACSuccessEffect);
USER_FUNC(star_stone_appear);
USER_FUNC(wait_game_end);
USER_FUNC(start_game);
USER_FUNC(set_weapon);
USER_FUNC(end_muki);
USER_FUNC(main_muki);
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AttackDeclare[];
extern s32 btlevtcmd_CheckDamage[];
extern s32 btlevtcmd_CheckStatus[];
extern s32 btlevtcmd_CommandGetWeaponAddress[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetSelectEnemy[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_StartWaitEvent[];
extern s32 btlevtcmd_WaitGuardMove[];
extern s32 btlevtcmd_WeaponAftereffect[];
extern s32 btlevtcmd_reset_move_color_lv_all[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_set_zoomSpeedLv[];
extern s32 evt_snd_sfxoff[];
extern s32 sac_ac_help_off[];
extern s32 sac_ac_help_on[];
extern s32 sac_enemy_slide_go[];
extern s32 sac_enemy_slide_return[];
extern s32 sac_handbeat[];
extern s32 sac_handbeat_end[];
extern s32 sac_mario_back_home[];
extern s32 sac_mario_item_on_end_evt[];
extern s32 sac_mario_item_on_evt[];
extern s32 sac_start_camera_evt[];
extern s32 sac_start_stardust[];
extern s32 sac_wao[];

typedef struct MukiObj { // 0x38
    s32 kind;       // 0x0
    s32 pad4;
    s32 type;       // 0x8
    f32 x, y, z;    // 0xc
    f32 sx, sy, sz; // 0x18
    s32 pad24;
    f32 rot;        // 0x28
    u8 pad2c[0x34 - 0x2c];
    u8 alpha;       // 0x34
    u8 pad35[3];
} MukiObj;

typedef struct Muki3D { // 0x24
    s32 kind;
    s32 pad4;
    f32 x, y, z;    // 0x8
    f32 sx, sy, sz; // 0x14
    u8 pad20[4];
} Muki3D;

typedef struct MukiWork {
    s32 pad0;
    s32 state;             // 0x4
    u8 pad8[0xc];
    f32 f14;               // 0x14
    u8 pad18[4];
    f32 f1c;               // 0x1c
    u8 pad20[0x38 - 0x20];
    s32 kind38;            // 0x38
    u8 pad3c[0x44 - 0x3c];
    f32 x44, y44, z44;     // 0x44
    u8 pad50[0x68 - 0x50];
    f32 sx68, sy68, sz68;  // 0x68
    GXColor col74;         // 0x74
    Muki3D o3d[9];         // 0x78
    MukiObj obj[9];        // 0x1bc
    s32 star;              // 0x3b4
    u8 pad3b8[0x408 - 0x3b8];
    u8 weapon[0xc0];       // 0x408
} MukiWork;

static s32 weapon[48];
s32 nice_event_pow[8];
s32 marioAttackEvent_Muki[254];

static s32 weapon[] = {
    (s32)"btl_wn_sac_mukimuki_body", 26869760, 0, (s32)"msg_mukimuki_body", 1677722368, 1065353216, 17130546, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 34603120, 268435456, 770, (s32)"msg_sac_4", 131080, 2047, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, (s32)marioAttackEvent_Muki, 100, 0, 0,
};

EVT_BEGIN(nice_event_pow)
    CALL(btlevtcmd_ACSuccessEffect, LW(0), -100, 175, 0)
    RETURN
EVT_END()

s32 marioAttackEvent_Muki[] = {
    196699, (s32)btlevtcmd_GetUnitId, -4, -29999986, 196699, (s32)btlevtcmd_GetBodyId, -29999986, -29999985,
    262235, (s32)btlevtcmd_CheckStatus, -29999986, 27, -30000000, 131097, -30000000, 0,
    131122, -29999986, -1, 33, 196699, (s32)btlevtcmd_GetSelectEnemy, -29999997, -29999996,
    131096, -29999997, -1, 65540, 99, 33, 262235, (s32)btlevtcmd_AttackDeclare,
    -2, -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 131163, (s32)btlevtcmd_CommandPayWeaponCost, -2,
    196699, (s32)btlevtcmd_CommandGetWeaponAddress, -2, -30000000, 131163, (s32)btlevtcmd_WeaponAftereffect, -30000000, 65627,
    (s32)btlevtcmd_reset_move_color_lv_all, 110, 131163, (s32)main_muki, -29999986, 112, 65630, (s32)sac_start_camera_evt,
    65546, 500, 65627, (s32)sac_enemy_slide_go, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_SAC_START1",
    -250000000, 0, -250000000, 65630, (s32)sac_mario_item_on_evt, 65546, 500, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_SAC_START2", -250000000, 0, -29999989, 65627, (s32)star_stone_appear,
    110, 65630, (s32)sac_start_stardust, 112, 65545, 100, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_SAC_START3", -250000000, 0, -250000000, 131163, (s32)evt_snd_sfxoff, -29999989,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65545, 40, 65630, (s32)sac_mario_item_on_end_evt,
    65630, (s32)sac_mario_back_home, 262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_I_Y", 65546,
    1000, 110, 65627, (s32)sac_handbeat, 112, 65627, (s32)sac_ac_help_on, 65627,
    (s32)start_game, 196699, (s32)wait_game_end, -30000000, -29999999, 65627, (s32)sac_ac_help_off, 65627,
    (s32)sac_handbeat_end, 65546, 500, 131122, -29999998, -30000000, 131125, -29999998,
    -29999999, 131097, -29999998, 0, 196699, (s32)evt_btl_camera_set_mode, 0, 7,
    262235, (s32)evt_btl_camera_set_homing_unit, 0, -2, -1, 196699, (s32)evt_btl_camera_set_zoom, 0,
    200, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0, 2, 196699, (s32)evt_btl_camera_set_zoomSpeedLv, 0,
    2, 65546, 1000, 65627, (s32)sac_wao, 107, 65546, 1000,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65627, (s32)sac_enemy_slide_return, 65627, (s32)end_muki,
    109, 107, 65546, 400, 131097, -29999999, 0, 262235,
    (s32)set_weapon, 1, -29999999, -29999991, 131097, -29999986, -1, 458843,
    (s32)btlevtcmd_CheckDamage, -2, -29999986, -29999985, -29999991, 256, -29999995, 33,
    458843, (s32)btlevtcmd_CheckDamage, -2, -2, 1, -29999991, 256, -29999995,
    33, 109, 131097, -30000000, 0, 262235, (s32)set_weapon, 0,
    -30000000, -29999991, 131097, -29999986, -1, 458843, (s32)btlevtcmd_CheckDamage, -2,
    -29999986, -29999985, -29999991, 256, -29999995, 33, 458843, (s32)btlevtcmd_CheckDamage,
    -2, -2, 1, -29999991, 256, -29999995, 2, 33,
    33, 65627, (s32)sac_enemy_slide_return, 65546, 1000, 65627, (s32)end_muki, 65546,
    1000, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2, 1,
};


#pragma dont_inline on
static MukiWork* get_ptr(void) {
    return (MukiWork*)((u8*)_battleWorkPointer + 0x1f4c);
}

#pragma dont_inline reset
static void disp_3D_alpha(void) {
    MukiWork* w = get_ptr();
    s32 i;
    MukiObj* o;
    Mtx m;
    for (i = 0; i < 9; i++) {
        o = &w->obj[i];
        if (o->kind >= 1 && o->kind <= 9) {
            f32 a;
            f32 c;
            GXColor ca;
            GXColor cb;
            switch (o->type) {
            case 0:
                PSMTXRotRad(m, 'y', 0.017453292f * o->rot);
                PSMTXScaleApply(m, m, 2.0f * o->sx, 2.0f * o->sy, o->sz);
                PSMTXTransApply(m, m, o->x, o->y, o->z);
                a = 2.0f * o->rot * 3.141592f / 360.0f;
                c = (f32)cos(a);
                PSMTXTransApply(m, m, 15.0f * (f32)sin(a), 0.0f, 15.0f * c);
                ca = (GXColor){0xE9, 0x4A, 0x3F, 0};
                cb = (GXColor){0xFE, 0xE6, 0x3E, 0};
                ca.a = o->alpha;
                cb.a = o->alpha;
                btlDispTexPlane3(m, 0x45, ca, ca, cb, cb);
                break;
            case 1:
                PSMTXRotRad(m, 'y', 0.017453292f * o->rot);
                PSMTXScaleApply(m, m, 2.0f * o->sx, 2.0f * o->sy, o->sz);
                PSMTXTransApply(m, m, o->x, o->y, o->z);
                a = 2.0f * o->rot * 3.141592f / 360.0f;
                c = (f32)cos(a);
                PSMTXTransApply(m, m, 15.0f * (f32)sin(a), 0.0f, 15.0f * c);
                ca = (GXColor){0x3F, 0x3F, 0xE9, 0};
                cb = (GXColor){0x74, 0xC9, 0xFF, 0};
                ca.a = o->alpha;
                cb.a = o->alpha;
                btlDispTexPlane3(m, 0x45, ca, ca, cb, cb);
                break;
            case 2:
                PSMTXRotRad(m, 'y', 0.017453292f * o->rot);
                PSMTXScaleApply(m, m, o->sx, o->sy, o->sz);
                PSMTXTransApply(m, m, o->x, o->y, o->z);
                a = 2.0f * o->rot * 3.141592f / 360.0f;
                c = (f32)cos(a);
                PSMTXTransApply(m, m, 15.0f * (f32)sin(a), 0.0f, 15.0f * c);
                ca = (GXColor){0xFF, 0xFF, 0xFF, 0};
                ca.a = o->alpha;
                btlDispTexPlane2(m, 0x31, ca);
                break;
            }
        }
    }
}

static void disp_3D(void) {
    MukiWork* w = get_ptr();
    s32 a[8] = {-8, 8, 8, 8, 8, -8, -8, -8};
    s32 b[8] = {-24, 24, 24, 24, 24, -24, -24, -24};
    s32 c[8] = {1, 1, -1, 1, -1, -1, 1, -1};
    Muki3D* o;
    s32 i, j;
    Mtx m;
    GXColor col;
    for (i = 0; i < 9; i++) {
        o = &w->o3d[i];
        if (o->kind >= 2 && o->kind < 8) {
            for (j = 0; j < 4; j++) {
                PSMTXScale(m, o->sx * (f32)c[j * 2], o->sy * (f32)c[j * 2 + 1], o->sz);
                PSMTXTransApply(m, m, o->x, o->y, o->z);
                PSMTXTransApply(m, m, o->sx * (f32)a[j * 2], o->sy * (f32)a[j * 2 + 1], 0.0f);
                col = (GXColor){0xDE, 0xDE, 0xDE, 0xFF};
                ((void (*)(Mtx, u32, GXColor*, s32))btlDispTexPlane2)(m, 0x42, &col, 0);
            }
        }
    }
    if (w->kind38 >= 2 && w->kind38 < 7) {
        for (j = 0; j < 4; j++) {
            PSMTXScale(m, w->sx68 * (f32)c[j * 2], w->sy68 * (f32)c[j * 2 + 1], w->sz68);
            PSMTXTransApply(m, m, w->x44, w->y44, w->z44);
            PSMTXTransApply(m, m, w->sx68 * (f32)b[j * 2], w->sy68 * (f32)b[j * 2 + 1], 0.0f);
            col = w->col74;
            ((void (*)(Mtx, u32, GXColor*, s32))btlDispTexPlane2)(m, 0x41, &col, 0);
        }
    }
}

static s32 set_weapon(EventEntry* evt, BOOL isFirstCall) {
    s32* args = evt->args;
    s32 type = evtGetValue(evt, args[0]);
    s32 power = evtGetValue(evt, args[1]);
    MukiWork* w = get_ptr();
    memcpy(w->weapon, weapon, 0xc0);
    switch (type) {
    case 0:
        w->weapon[0x96] = 100;
        w->weapon[0x97] = 3;
        w->weapon[0x98] = power;
        break;
    case 1:
        w->weapon[0x99] = 100;
        w->weapon[0x9a] = 3;
        w->weapon[0x9b] = power;
        break;
    }
    evtSetValue(evt, args[2], (s32)w->weapon);
    return 2;
}

static s32 start_game(EventEntry* evt, BOOL isFirstCall) {
    MukiWork* w = get_ptr();
    w->state = 1;
    return 2;
}

static s32 wait_game_end(EventEntry* evt, BOOL isFirstCall) {
    MukiWork* w = get_ptr();
    s32* args = evt->args;
    if (w->state == 7) {
        evtSetValue(evt, args[0], (s32)w->f14);
        evtSetValue(evt, args[1], (s32)w->f1c);
        return 2;
    }
    return 0;
}

static s32 star_stone_appear(EventEntry* evt, BOOL isFirstCall) {
    MukiWork* w = get_ptr();
    w->star = 1;
    return 2;
}
