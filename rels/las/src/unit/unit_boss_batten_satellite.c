#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "party/party_motion.h"

s32 bts_x_flag_data;
f32 intplGetValue(s32 mode, s32 currStep, f32 start, f32 end, s32 steps);

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable);
USER_FUNC(btlevtcmd_OnUnitFlag);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetHpGaugeOffset);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(bts_x_flag_wait);
USER_FUNC(bts_x_flag_get);
USER_FUNC(bts_x_flag_add);
USER_FUNC(bts_x_flag_set);
static USER_FUNC(bts_wariai_enzan_0f);
static USER_FUNC(bts_wariai_enzan_0);
USER_FUNC(bts_wariai_enzan_1f_intpl_w);
static USER_FUNC(bts_wariai_enzan_1f_intpl);
static USER_FUNC(bts_wariai_enzan_1f);
static USER_FUNC(bts_wariai_enzan_1);

__declspec(section ".data") u64 fd_boss_batten_satellite_negone_one_374;
__declspec(section ".data") s32 fd_boss_batten_satellite_neg_one_382[1];
__declspec(section ".data") s32 fd_boss_batten_satellite___local_PI_383[1];
__declspec(section ".data") s32 fd_boss_batten_satellite___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_boss_batten_satellite_one_negone_373;
__declspec(section ".data") s32 fd_boss_batten_satellite___local_PIO2_384[1];
__declspec(section ".data") s32 fd_boss_batten_satellite_one_381[1];
__declspec(section ".data") u64 fd_boss_batten_satellite_negone_one_360;
__declspec(section ".data") s32 fd_boss_batten_satellite_neg_one_365[1];
__declspec(section ".data") s32 fd_boss_batten_satellite___local_PI_366[1];
__declspec(section ".data") s32 fd_boss_batten_satellite___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_boss_batten_satellite_one_negone_359;
__declspec(section ".data") s32 fd_boss_batten_satellite___local_PIO2_367[1];
__declspec(section ".data") s32 fd_boss_batten_satellite_one_364[1];
s32 weapon_batten_satellite_attack[48];
BattleUnitKind unit_boss_batten_satellite;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static BattleDataEntry data_table[15];
s32 dmg_counter_event[149];
static BattleUnitKindPart parts[1];
static s32 init_event[30];
static __declspec(section ".data") s32 entry_event[2];
static __declspec(section ".data") s32 damage_event[10];
static __declspec(section ".data") s32 phase_event[2];
static __declspec(section ".data") s32 dead_event[2];
static __declspec(section ".data") s32 attack_event[10];
s32 batten_satellite_attack_attack_event[304];
static __declspec(section ".data") s32 wait_event[6];

__declspec(section ".data") u64 fd_boss_batten_satellite_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_batten_satellite_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_batten_satellite___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_batten_satellite___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_batten_satellite_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_batten_satellite___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_batten_satellite_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_boss_batten_satellite_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_boss_batten_satellite_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_boss_batten_satellite___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_boss_batten_satellite___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_boss_batten_satellite_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_boss_batten_satellite___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_boss_batten_satellite_one_364[] = {
    1065353216,
};

s32 weapon_batten_satellite_attack[] = {
    0, 0, 0, 0, 1677721601, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    4, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2, -2147475452,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

BattleUnitKind unit_boss_batten_satellite = {
    147,
    "btl_un_batten_satellite",
    3,
    0,
    1,
    1,
    0,
    0,
    1,
    100,
    0,
    50,
    9,
    16,
    16,
    0,
    8,
    0.0f,
    0.0f,
    0.0f,
    -3,
    -6,
    0.0f,
    0.0f,
    0.0f,
    8.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    8.0f,
    0.0f,
    0.0f,
    6.0f,
    7.0f,
    0.0f,
    -1.0f,
    0.0f,
    0.0f,
    16.0f,
    16.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_BOSS_SATELLITE_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {0, 75, 90, 0, 10, 100, 100, 75, 100, 75, 100, 75, 100, 95, 75, 0, 90, 100, 75, 100, 100, 90};

static PoseTableEntry pose_table[] = {
    {1, "N_1"},
    {2, "Y_1"},
    {9, "Y_1"},
    {5, "K_1"},
    {4, "X_1"},
    {3, "K_1"},
    {28, "S_1"},
    {29, "Q_1"},
    {30, "Q_1"},
    {31, "D_1"},
    {39, "D_1"},
    {50, "A_1"},
    {42, "S_1"},
    {40, "S_1"},
    {56, "X_1"},
    {57, "X_1"},
    {65, "A_1"},
    {69, "S_1"},
};

static BattleDataEntry data_table[] = {
    {24, dmg_counter_event},
    {25, dmg_counter_event},
    {26, dmg_counter_event},
    {27, dmg_counter_event},
    {28, dmg_counter_event},
    {29, dmg_counter_event},
    {30, dmg_counter_event},
    {31, dmg_counter_event},
    {32, dmg_counter_event},
    {33, dmg_counter_event},
    {34, dmg_counter_event},
    {35, dmg_counter_event},
    {36, dmg_counter_event},
    {50, dead_event},
    {0, NULL},
};

s32 dmg_counter_event[] = {
    196699, (s32)btlevtcmd_OnUnitFlag, -29999990, 1, 65570, -30000000, 65572, 43,
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_ATTACK_MISS3", 0, 131122, -29999986, 36, 65579,
    46, 65579, 49, 65579, 50, 65579, 54, 131122,
    -29999986, 29, 46, 42, 131122, -29999986, 39, 49,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -29999990, -29999989, -29999986, 110, 196699, (s32)btlevtcmd_RunDataEventChild,
    -29999990, 10, 112, 196699, (s32)btlevtcmd_SetFallAccel, -29999990, -229998976, 327771,
    (s32)btlevtcmd_GetPos, -29999990, -29999998, -29999997, -29999996, 262235, (s32)btlevtcmd_FaceDirectionSub, -29999990,
    -29999998, 25, 131125, -29999997, 25, 655451, (s32)btlevtcmd_DivePosition, -29999990,
    -29999998, -29999997, -29999996, 10, 0, 0, 0, -1,
    65546, 500, 196699, (s32)evt_btl_camera_set_mode, 0, 0, 262235, (s32)btlevtcmd_CheckDamageCode,
    -29999990, 512, -30000000, 131097, -30000000, 0, 262235, (s32)btlevtcmd_CheckDamageCode,
    -29999990, 2048, -30000000, 131096, -30000000, 0, 2, 33,
    33, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SATELLITE_ATTACK2", -250000000, 0, -250000000,
    327771, (s32)btlevtcmd_GetHomePos, -29999990, -29999995, -29999994, -29999993, 65546, 80,
    131122, -29999992, 42, 65541, -29999992, 393307, (s32)bts_wariai_enzan_1, -29999992,
    42, -29999998, -29999995, -29999988, 393307, (s32)bts_wariai_enzan_1, -29999992, 42,
    -29999997, -29999994, -29999987, 393307, (s32)bts_wariai_enzan_1, -29999992, 42, -29999996,
    -29999993, -29999986, 327771, (s32)btlevtcmd_SetPos, -2, -29999988, -29999987, -29999986,
    65545, 1, 6, 2, 1,
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_batten_satellite", "c_shuryo_p", 0.0f, 0.0f, 0.0f, -4.0f, -2.0f, 0.0f, -6.0f, 1.0f, 0.0f, 14, 14, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetHpGaugeOffset, -2, -5, -13)
    CALL(btlevtcmd_OnUnitFlag, -2, 3145728)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(entry_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(phase_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(dead_event)
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(attack_event)
    SET_VALUE(LW(9), PTR(weapon_batten_satellite_attack))
    CALL_CHILD(PTR(batten_satellite_attack_attack_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

s32 batten_satellite_attack_attack_event[] = {
    262235, (s32)btlevtcmd_AnimeChangePose, -2, 1, (s32)"F_1", 65546, 400, 262235,
    (s32)btlevtcmd_AnimeChangePoseType, -2, 1, 69, 196699, (s32)btlevtcmd_GetEnemyBelong, -2, -30000000,
    262235, (s32)btlevtcmd_SamplingEnemy, -2, -30000000, -29999991, 262235, (s32)btlevtcmd_ChoiceSamplingEnemy, -29999991,
    -29999997, -29999996, 131096, -29999997, -1, 262235, (s32)btlevtcmd_CheckToken, -2,
    16, -30000000, 131097, -30000000, 0, 65630, (s32)subsetevt_confuse_flustered, 33,
    2, 33, 131163, (s32)btlevtcmd_WeaponAftereffect, -29999991, 262235, (s32)btlevtcmd_AttackDeclare, -2,
    -29999997, -29999996, 65627, (s32)btlevtcmd_WaitGuardMove, 196699, (s32)btlevtcmd_PayWeaponCost, -2, -29999991,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SATELLITE_ATTACK1", -250000000, 0, -250000000, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 393307, (s32)btlevtcmd_GetHitPos, -29999997,
    -29999996, -29999987, -29999994, -29999993, 131122, -29999992, 9, 65541,
    -29999992, 393307, (s32)bts_wariai_enzan_1, -29999992, 9, -30000000, -29999987, -29999990,
    393307, (s32)bts_wariai_enzan_1, -29999992, 9, -29999999, -29999994, -29999989, 393307,
    (s32)bts_wariai_enzan_1, -29999992, 9, -29999998, -29999993, -29999988, 327771, (s32)btlevtcmd_SetPos,
    -2, -29999990, -29999989, -29999988, 65545, 1, 6, 131126,
    -29999987, -30000000, 131128, -29999987, 2, 131126, -29999994, -29999999,
    131128, -29999994, 2, 131126, -29999993, -29999998, 131128, -29999993,
    2, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996, -30000000, -29999999, -29999998,
    131125, -29999987, -30000000, 131125, -29999994, -29999999, 131125, -29999993,
    -29999998, 110, 131122, -29999992, 4, 65541, -29999992, 393307,
    (s32)bts_wariai_enzan_1, -29999992, 4, -30000000, -29999987, -29999990, 393307, (s32)bts_wariai_enzan_1,
    -29999992, 4, -29999999, -29999994, -29999989, 393307, (s32)bts_wariai_enzan_1, -29999992,
    4, -29999998, -29999993, -29999988, 327771, (s32)btlevtcmd_SetPos, -2, -29999990,
    -29999989, -29999988, 65545, 1, 6, 112, 458843, (s32)btlevtcmd_PreCheckDamage,
    -2, -29999997, -29999996, -29999991, 256, -29999995, 65570, -29999995,
    65579, 4, 65540, 90, 46, 65572, 3, 196699,
    (s32)btlevtcmd_StartAvoid, -29999997, 38, 65540, 90, 46, 65572, 6,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 39, 65540, 90, 65572, 2,
    196699, (s32)btlevtcmd_StartAvoid, -29999997, 40, 65540, 90, 65572, 1,
    65540, 91, 46, 42, 65540, 98, 46, 49,
    65539, 90, 65540, 98, 65539, 91, 196699, (s32)btlevtcmd_ResultACDefence,
    -29999997, -29999991, 458843, (s32)btlevtcmd_CheckDamage, -2, -29999997, -29999996, -29999991,
    256, -29999995, 65539, 98, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_BOSS_SATELLITE_ATTACK2",
    -250000000, 0, -250000000, 327771, (s32)btlevtcmd_GetHomePos, -2, -30000000, -29999999,
    -29999998, 65546, 80, 131122, -29999992, 42, 65541, -29999992,
    393307, (s32)bts_wariai_enzan_1, -29999992, 42, -29999987, -30000000, -29999990, 393307,
    (s32)bts_wariai_enzan_1, -29999992, 42, -29999994, -29999999, -29999989, 393307, (s32)bts_wariai_enzan_1,
    -29999992, 42, -29999993, -29999998, -29999988, 327771, (s32)btlevtcmd_SetPos, -2,
    -29999990, -29999989, -29999988, 65545, 1, 6, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, -2, 1)
    RETURN
EVT_END()

USER_FUNC(bts_x_flag_wait) {
    s32 v = evtGetValue(event, event->args[0]);

    if (v == bts_x_flag_data) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(bts_x_flag_get) {
    evtSetValue(event, event->args[0], bts_x_flag_data);
    return EVT_RETURN_DONE;
}

USER_FUNC(bts_x_flag_add) {
    bts_x_flag_data += evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

USER_FUNC(bts_x_flag_set) {
    bts_x_flag_data = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

static USER_FUNC(bts_wariai_enzan_0f) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]) - 1.0f;
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetFloat(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}

static USER_FUNC(bts_wariai_enzan_0) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]) - 1.0f;
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetValue(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}

USER_FUNC(bts_wariai_enzan_1f_intpl_w) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);
    s32 out = args[4];
    f32 t1 = evtGetFloat(event, args[5]);
    f32 t2 = evtGetFloat(event, args[6]);
    f32 r1;
    f32 r2;
    f32 w;

    if (t1 >= 14.0f) {
        t1 -= 14.0f;
        if (t1 >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r1 = 1.0f - intplGetValue(t1, b - a, 1.0f, 0.0f, b);
    } else {
        r1 = intplGetValue(t1, b - a, 0.0f, 1.0f, b);
    }
    if (t2 >= 14.0f) {
        t2 = t1 - 14.0f;
        if (t2 >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r2 = 1.0f - intplGetValue(t2, b - a, 1.0f, 0.0f, b);
    } else {
        r2 = intplGetValue(t2, b - a, 0.0f, 1.0f, b);
    }
    w = r1 * r2;
    evtSetFloat(event, out, c * (1.0f - w) + d * w);
    return EVT_RETURN_DONE;
}

static USER_FUNC(bts_wariai_enzan_1f_intpl) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);
    s32 out = args[4];
    f32 t = evtGetFloat(event, args[5]);
    f32 r;

    if (t >= 14.0f) {
        t -= 14.0f;
        if (t >= 14.0f) {
            evtSetFloat(event, out, c);
            return EVT_RETURN_DONE;
        }
        r = 1.0f - intplGetValue(t, b - a, 1.0f, 0.0f, b);
    } else {
        r = intplGetValue(t, b - a, 0.0f, 1.0f, b);
    }
    evtSetFloat(event, out, (1.0f - r) * c + r * d);
    return EVT_RETURN_DONE;
}

static USER_FUNC(bts_wariai_enzan_1f) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetFloat(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}

static USER_FUNC(bts_wariai_enzan_1) {
    s32* args = event->args;
    f32 a = evtGetFloat(event, args[0]) - 1.0f;
    f32 b = evtGetFloat(event, args[1]);
    f32 c = evtGetFloat(event, args[2]);
    f32 d = evtGetFloat(event, args[3]);

    evtSetValue(event, args[4], (a * c + d * (b - a)) / b);
    return EVT_RETURN_DONE;
}
