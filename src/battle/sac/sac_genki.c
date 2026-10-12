#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "system.h"

extern BattleWork* _battleWorkPointer;

typedef struct GenkiWeapon {
    s32 flag;
    s32 state;
    u8 pad[0x54 - 8];
} GenkiWeapon;

typedef struct GenkiObject {
    s32 state;
    u8 pad[0x2C - 4];
} GenkiObject;

typedef struct GenkiStar {
    s32 a;
    s32 b;
    s32 c;
    u8 pad[0x64 - 12];
} GenkiStar;

typedef struct GenkiWork {
    s32 pad0;
    s32 state;
    u8 pad8[0x10 - 8];
    s32 score0;
    s32 score1;
    s32 score2;
    u8 pad1C[0x58 - 0x1C];
    s32 weaponNum;
    u8 pad5C[0x10C - 0x5C];
    GenkiWeapon weapon[7];
    GenkiObject object[10];
    GenkiStar star[7];
} GenkiWork;

s32 statusWinOpen();
void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);
USER_FUNC(recover_cmd_disable);
USER_FUNC(star_appear);
USER_FUNC(status_on);
USER_FUNC(get_score);
USER_FUNC(object_get_num);
USER_FUNC(object_entry);
USER_FUNC(weapon_entry);
USER_FUNC(main_genki);
USER_FUNC(end_genki);
static USER_FUNC(star_stone_appear);
static USER_FUNC(wait_game_end);
static USER_FUNC(start_game);
extern s32 btlevtcmd_AnimeChangePose[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_CheckStatus[];
extern s32 btlevtcmd_CommandPayWeaponCost[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetHomePos[];
extern s32 btlevtcmd_GetPos[];
extern s32 btlevtcmd_GetUnitId[];
extern s32 btlevtcmd_MovePosition[];
extern s32 btlevtcmd_OnOffStatus[];
extern s32 btlevtcmd_RecoverFp[];
extern s32 btlevtcmd_RecoverHp[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_StartWaitEvent[];
extern s32 btlevtcmd_reset_move_color_lv_all[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_btl_camera_set_homing_unit[];
extern s32 evt_btl_camera_set_mode[];
extern s32 evt_btl_camera_set_moveSpeedLv[];
extern s32 evt_btl_camera_set_zoom[];
extern s32 evt_btl_camera_set_zoomSpeedLv[];
extern s32 evt_eff[];
extern s32 evt_snd_sfxoff[];
extern s32 evt_snd_sfxon[];
extern s32 sac_ac_help_off[];
extern s32 sac_ac_help_on[];
extern s32 sac_enemy_slide_go[];
extern s32 sac_enemy_slide_return[];
extern s32 sac_mario_item_on_end_evt[];
extern s32 sac_mario_item_on_evt[];
extern s32 sac_start_camera_evt[];
extern s32 sac_start_stardust[];
extern s32 sac_wao[];


extern s32 genki_evt_common[];
extern s32 status_recover_evt[];
static GenkiWork* get_ptr(void);

s32 marioAttackEvent_Genki0[] = {
    131122, -29999985, 0, 65630, (s32)genki_evt_common, 2, 1,
};

s32 marioAttackEvent_Genki1[] = {
    131122, -29999985, 1, 65630, (s32)genki_evt_common, 2, 1,
};

s32 genki_evt_common[] = {
    196699, (s32)btlevtcmd_GetUnitId, -4, -29999987, 196699, (s32)btlevtcmd_GetBodyId, -29999987, -29999986,
    262235, (s32)btlevtcmd_CheckStatus, -29999987, 27, -30000000, 131097, -30000000, 0,
    131122, -29999987, -1, 33, 65627, (s32)btlevtcmd_reset_move_color_lv_all, 131163, (s32)btlevtcmd_CommandPayWeaponCost,
    -2, 110, 196699, (s32)main_genki, -29999987, -29999985, 112, 65630,
    (s32)sac_start_camera_evt, 65546, 500, 65627, (s32)sac_enemy_slide_go, 393307, (s32)btlevtcmd_snd_se, -2,
    (s32)"SFX_BTL_SAC_START1", -250000000, 0, -250000000, 65630, (s32)sac_mario_item_on_evt, 65546, 500,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BTL_SAC_START2", -250000000, 0, -29999989, 131096,
    -29999985, 0, 65627, (s32)star_appear, 32, 65627, (s32)star_stone_appear, 33,
    110, 65630, (s32)sac_start_stardust, 112, 65545, 100, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_BTL_SAC_HEART_SHOOT1", -250000000, 0, -29999990, 131163, (s32)evt_snd_sfxoff, -29999989,
    196699, (s32)evt_btl_camera_set_mode, 0, 0, 65545, 40, 65630, (s32)sac_mario_item_on_end_evt,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 196699, (s32)btlevtcmd_SetMoveSpeed, -2,
    -229996928, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 524379,
    (s32)btlevtcmd_MovePosition, -2, -75, -29999999, -29999998, 0, -1, 0,
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"M_I_Y", 65545, 40, 131163,
    (s32)evt_snd_sfxoff, -29999990, 65627, (s32)sac_ac_help_on, 65627, (s32)start_game, 65627, (s32)wait_game_end,
    65627, (s32)sac_ac_help_off, 262235, (s32)get_score, -29999990, -29999989, -29999988, 65545,
    70, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 42, 327771, (s32)btlevtcmd_GetHomePos,
    -2, -30000000, -29999999, -29999998, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229996928,
    524379, (s32)btlevtcmd_MovePosition, -2, -30000000, -29999999, -29999998, 0, -1,
    0, 262235, (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 40, 65627, (s32)status_on,
    196699, (s32)evt_btl_camera_set_mode, 0, 7, 262235, (s32)evt_btl_camera_set_homing_unit, 0, -2,
    -1, 196699, (s32)evt_btl_camera_set_zoom, 0, 200, 196699, (s32)evt_btl_camera_set_moveSpeedLv, 0,
    2, 196699, (s32)evt_btl_camera_set_zoomSpeedLv, 0, 2, 131122, -29999985, -29999990,
    131125, -29999985, -29999989, 131125, -29999985, -29999988, 131101, -29999985,
    1, 65627, (s32)sac_wao, 33, 131097, -29999987, -1, 196699,
    (s32)evt_snd_sfxon, (s32)"SFX_HP_RECOVER_SHINE2", 0, 131122, -29999991, -2, 65630, (s32)status_recover_evt,
    262235, (s32)btlevtcmd_RecoverHp, -2, 1, -29999990, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"stardust", 2,
    -30000000, -29999999, -29999998, 50, 50, 50, 100, 0,
    0, 0, 0, 131122, -29999991, -29999987, 65630, (s32)status_recover_evt,
    131163, (s32)btlevtcmd_StartWaitEvent, -29999987, 262235, (s32)btlevtcmd_RecoverHp, -29999987, -29999986, -29999989,
    327771, (s32)btlevtcmd_GetPos, -29999987, -30000000, -29999999, -29999998, 983131, (s32)evt_eff,
    (s32)"", (s32)"stardust", 2, -30000000, -29999999, -29999998, 50, 50,
    50, 100, 0, 0, 0, 0, 262235, (s32)btlevtcmd_RecoverFp,
    -2, 1, -29999988, 32, 196699, (s32)evt_snd_sfxon, (s32)"SFX_HP_RECOVER_SHINE2", 0,
    131122, -29999991, -2, 65630, (s32)status_recover_evt, 262235, (s32)btlevtcmd_RecoverHp, -2,
    1, -29999990, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    983131, (s32)evt_eff, (s32)"", (s32)"stardust", 2, -30000000, -29999999, -29999998,
    50, 50, 50, 100, 0, 0, 0, 0,
    262235, (s32)btlevtcmd_RecoverFp, -2, 1, -29999988, 33, 65546, 1000,
    65627, (s32)sac_enemy_slide_return, 65546, 1000, 196699, (s32)evt_btl_camera_set_mode, 0, 0,
    65546, 1000, 65627, (s32)end_genki, 131163, (s32)btlevtcmd_StartWaitEvent, -2, 2,
    1,
};

s32 status_recover_evt[] = {
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 1, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 1, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 2, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 2, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 3, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 3, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 4, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 4, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 5, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 5, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 8, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 8, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 9, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 9, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 13, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 13, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 11, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 11, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 15, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 15, 0, 0, 0, 33,
    262235, (s32)btlevtcmd_CheckStatus, -29999991, 20, -30000000, 131097, -30000000, 0,
    393307, (s32)btlevtcmd_OnOffStatus, -29999991, 20, 0, 0, 0, 33,
    65627, (s32)recover_cmd_disable, 2, 1,
};


#pragma dont_inline on
static GenkiWork* get_ptr(void) {
    return (GenkiWork*)((u8*)_battleWorkPointer + 0x1F4C);
}
#pragma dont_inline reset

USER_FUNC(weapon_entry) {
    BattleUnit* mario;
    BattleUnitPart* part;
    GenkiWork* w = get_ptr();
    s32 cnt = 0;
    s32 idx[7];
    s32 i;
    mario = BattleGetMarioPtr(_battleWorkPointer);
    part = BtlUnit_GetPartsPtr(mario, BtlUnit_GetBodyPartsId(mario));
    for (i = 0; i < w->weaponNum; i++) {
        if (w->weapon[i].flag == 0) {
            idx[cnt] = i;
            cnt++;
        }
    }
    if (cnt >= 1) {
        GenkiWeapon* wp = &w->weapon[idx[irand(cnt)]];
        wp->flag = 1;
        wp->state = 7;
        BtlUnit_SetAnim(part, "M_C_2C");
    }
}

USER_FUNC(object_entry) {
    GenkiWork* w = get_ptr();
    s32 i;
    for (i = 0; i < 10; i++) {
        s32* p = &w->object[i].state;
        if (*p == 0) {
            *p = 1;
            break;
        }
    }
}

USER_FUNC(object_get_num) {
    GenkiWork* w = get_ptr();
    s32 n = 0;
    s32 i;
    for (i = 0; i < 10; i++) {
        if (w->object[i].state == 2) {
            n++;
        }
    }
    return n;
}

static USER_FUNC(start_game) {
    GenkiWork* w = get_ptr();
    w->state = 1;
    return 2;
}

static USER_FUNC(wait_game_end) {
    return get_ptr()->state == 3 ? 2 : 0;
}

USER_FUNC(get_score) {
    GenkiWork* w = get_ptr();
    s32* args = event->args;
    evtSetValue(event, args[0], w->score0);
    evtSetValue(event, args[1], w->score1);
    evtSetValue(event, args[2], w->score2);
    return 2;
}

USER_FUNC(status_on) {
    statusWinOpen();
    return 2;
}

USER_FUNC(star_appear) {
    GenkiWork* w = get_ptr();
    s32 i;
    for (i = 0; i < 7; i++) {
        s32* p = (s32*)((u8*)w + 0x510 + i * 0x64);
        p[0] = 1;
        p[2] = 0;
    }
    return 2;
}

static USER_FUNC(star_stone_appear) {
    GenkiWork* w = get_ptr();
    w->star[0].a = 1;
    w->star[0].c = 1;
    return 2;
}

USER_FUNC(recover_cmd_disable) {
    BattleWork* w = _battleWorkPointer;
    w->commandDisabled[0] = 0;
    w->commandDisabled[1] = 0;
    w->commandDisabled[2] = 0;
    w->commandDisabled[3] = 0;
    w->commandDisabled[4] = 0;
    return 2;
}
