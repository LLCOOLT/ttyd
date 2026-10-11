#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#pragma force_active on
#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "memory.h"
#include "dolphin/gx.h"
#include "driver/camdrv.h"
#include "driver/dispdrv.h"
#include "system.h"

typedef struct PidersYarn { f32 x0; f32 y0; f32 z0; f32 x1; f32 y1; f32 z1; u8 alpha; } PidersYarn;
void GXEnd_(void);
void GXPosition3f32_(f32 x, f32 y, f32 z);
static void piders_draw_yarn_sub(CameraId camera, void* param);
BOOL BtlUnit_CanActStatus(BattleUnit* unit);

USER_FUNC(btlevtcmd_AddRotate);
USER_FUNC(btlevtcmd_AnimeChangePose);
USER_FUNC(btlevtcmd_AttackDeclare);
USER_FUNC(btlevtcmd_CalculateFaceDirection);
USER_FUNC(btlevtcmd_ChangeFaceDirection);
USER_FUNC(btlevtcmd_CheckActStatus);
USER_FUNC(btlevtcmd_CheckDamage);
USER_FUNC(btlevtcmd_CheckPhase);
USER_FUNC(btlevtcmd_CheckStatus);
USER_FUNC(btlevtcmd_CheckToken);
USER_FUNC(btlevtcmd_ChoiceSamplingEnemy);
USER_FUNC(btlevtcmd_EnemyItemUseCheck);
USER_FUNC(btlevtcmd_GetEnemyBelong);
USER_FUNC(btlevtcmd_GetPos);
USER_FUNC(btlevtcmd_GetUnitId);
USER_FUNC(btlevtcmd_GetUnitWork);
USER_FUNC(btlevtcmd_JumpPartsContinue);
USER_FUNC(btlevtcmd_OnPartsAttribute);
USER_FUNC(btlevtcmd_PayWeaponCost);
USER_FUNC(btlevtcmd_PreCheckDamage);
USER_FUNC(btlevtcmd_ResetFaceDirection);
USER_FUNC(btlevtcmd_ResultACDefence);
USER_FUNC(btlevtcmd_SamplingEnemy);
USER_FUNC(btlevtcmd_SetEventAttack);
USER_FUNC(btlevtcmd_SetEventConfusion);
USER_FUNC(btlevtcmd_SetEventDamage);
USER_FUNC(btlevtcmd_SetEventEntry);
USER_FUNC(btlevtcmd_SetEventUnisonPhase);
USER_FUNC(btlevtcmd_SetEventWait);
USER_FUNC(btlevtcmd_SetPartsRotate);
USER_FUNC(btlevtcmd_SetPos);
USER_FUNC(btlevtcmd_SetRotate);
USER_FUNC(btlevtcmd_SetUnitWork);
USER_FUNC(btlevtcmd_StartAvoid);
USER_FUNC(btlevtcmd_StartWaitEvent);
USER_FUNC(btlevtcmd_WaitAttackEnd);
USER_FUNC(btlevtcmd_WaitGuardMove);
USER_FUNC(btlevtcmd_WeaponAftereffect);
USER_FUNC(btlevtcmd_check_battleflag);
USER_FUNC(evt_btl_camera_set_mode);
USER_FUNC(evt_sub_intpl_get_value);
USER_FUNC(evt_sub_intpl_init);
USER_FUNC(evt_sub_random);
static USER_FUNC(piders_draw_yarn);
static USER_FUNC(piders_get_first_pos_attr);
static USER_FUNC(piders_get_num);
static USER_FUNC(piders_get_zyun);
static USER_FUNC(piders_renzoku_attack_set_target);
static USER_FUNC(piders_yarn_init);
static void piders_get_next_target(s32* unitIdx, s32* partIdx);
static void piders_get_target(s32* unitIdx, s32* partIdx);
static void piders_draw_yarn_sub(CameraId camera, void* param);
void GXEnd_(void);
void GXPosition3f32_(f32 x, f32 y, f32 z);
extern s32 _add_star_point_disp_offset[];
extern s32 btldefaultevt_Damage[];
extern s32 btlevtcmd_AnimeChangePoseFromTable[];
extern s32 btlevtcmd_AnimeChangePoseType[];
extern s32 btlevtcmd_DivePosition[];
extern s32 btlevtcmd_GetBodyId[];
extern s32 btlevtcmd_GetCoin[];
extern s32 btlevtcmd_GetExp[];
extern s32 btlevtcmd_GetHitPos[];
extern s32 btlevtcmd_GetStageSize[];
extern s32 btlevtcmd_GetStatusMg[];
extern s32 btlevtcmd_JumpPartsPosition[];
extern s32 btlevtcmd_JumpPartsSetting[];
extern s32 btlevtcmd_KillUnit[];
extern s32 btlevtcmd_OffPartsAttribute[];
extern s32 btlevtcmd_OnAttribute[];
extern s32 btlevtcmd_SetHomePos[];
extern s32 btlevtcmd_SetMaxMoveCount[];
extern s32 btlevtcmd_SetMoveSpeed[];
extern s32 btlevtcmd_SetPartsPos[];
extern s32 btlevtcmd_SetPartsRotateOffset[];
extern s32 btlevtcmd_SetPartsScale[];
extern s32 btlevtcmd_SetRotateOffset[];
extern s32 btlevtcmd_StoreCoin[];
extern s32 btlevtcmd_StoreExp[];
extern s32 btlevtcmd_snd_se[];
extern s32 evt_eff[];
extern s32 evt_eff64[];
extern s32 evt_snd_sfxon[];
extern s32 subsetevt_confuse_flustered[];
extern s32 weaponGetPowerDefault[];

__declspec(section ".data") u64 fd_piders_negone_one_374;
__declspec(section ".data") s32 fd_piders_neg_one_382[1];
__declspec(section ".data") s32 fd_piders___local_PI_383[1];
__declspec(section ".data") s32 fd_piders___local_3PIO2_385[1];
__declspec(section ".data") u64 fd_piders_one_negone_373;
__declspec(section ".data") s32 fd_piders___local_PIO2_384[1];
__declspec(section ".data") s32 fd_piders_one_381[1];
__declspec(section ".data") u64 fd_piders_negone_one_360;
__declspec(section ".data") s32 fd_piders_neg_one_365[1];
__declspec(section ".data") s32 fd_piders___local_PI_366[1];
__declspec(section ".data") s32 fd_piders___local_3PIO2_368[1];
__declspec(section ".data") u64 fd_piders_one_negone_359;
__declspec(section ".data") s32 fd_piders___local_PIO2_367[1];
__declspec(section ".data") s32 fd_piders_one_364[1];
BattleUnitKind unit_piders_28_data_2E140;
static __declspec(section ".data") BattleUnitDefense defence;
static __declspec(section ".data") BattleUnitDefenseAttr defence_attr;
static __declspec(section ".data") StatusVulnerability regist;
static PoseTableEntry pose_table[18];
static __declspec(section ".data") BattleDataEntry data_table[5];
static BattleUnitKindPart parts[5];
static s32 weapon_piders_attack[48];
static s32 weapon_piders_renzoku_attack[48];
static s32 init_event[53];
static s32 dmg_first_attack_pos[19];
static s32 yarn_event[44];
static s32 entry_event[48];
static __declspec(section ".data") s32 damage_event[10];
static s32 dead_event[189];
static s32 blow_dead_event[104];
static __declspec(section ".data") s32 battle_end_event[7];
static s32 yure_event[76];
static s32 move_kuutei_event[83];
static s32 move_kuuchu_event[54];
static s32 unison_phase_event[120];
static s32 attack_event[72];
static s32 damage_check_event_sub[157];
static s32 piders_attack_common_event1[163];
static s32 piders_attack_common_event1_2[109];
static s32 piders_attack_common_event2[47];
static s32 piders_attack_common_event3[70];
static s32 normal_attack_event[87];
static s32 renzoku_attack_event[149];
static s32 renzoku_attack_event_sub[55];
static __declspec(section ".data") s32 renzoku_attack_event_sub_no_last[10];
static s32 renzoku_attack_event_sub_last[79];
static __declspec(section ".data") s32 wait_event[7];

static USER_FUNC(piders_yarn_init) {
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    *(PidersYarn**)&unit->countersetWeapon = __memAlloc(HEAP_BATTLE, sizeof(PidersYarn));
    return EVT_RETURN_DONE;
}

#pragma dont_inline on
void GXPosition3f32_(f32 x, f32 y, f32 z) {
    GXWGFifo.f32 = x;
    GXWGFifo.f32 = y;
    GXWGFifo.f32 = z;
}
#pragma dont_inline reset

// GXEnd and GXPosition3f32 are ordinary functions in this file instead of the SDK inlines (names don't matter)
#pragma dont_inline on
void GXEnd_(void) {
}
#pragma dont_inline reset

__declspec(section ".data") u64 fd_piders_negone_one_374 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_piders_neg_one_382[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_piders___local_PI_383[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_piders___local_3PIO2_385[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_piders_one_negone_373 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_piders___local_PIO2_384[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_piders_one_381[] = {
    1065353216,
};

__declspec(section ".data") u64 fd_piders_negone_one_360 = 0xBF8000003F800000;

__declspec(section ".data") s32 fd_piders_neg_one_365[] = {
    -1082130432,
};

__declspec(section ".data") s32 fd_piders___local_PI_366[] = {
    1078530011,
};

__declspec(section ".data") s32 fd_piders___local_3PIO2_368[] = {
    1083624420,
};

__declspec(section ".data") u64 fd_piders_one_negone_359 = 0x3F800000BF800000;

__declspec(section ".data") s32 fd_piders___local_PIO2_367[] = {
    1070141403,
};

__declspec(section ".data") s32 fd_piders_one_364[] = {
    1065353216,
};

BattleUnitKind unit_piders_28_data_2E140 = {
    27,
    "btl_un_piders",
    5,
    0,
    1,
    1,
    12,
    0,
    2,
    70,
    0,
    70,
    9999,
    46,
    56,
    0,
    56,
    0.0f,
    28.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    23.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    18.0f,
    0.0f,
    0.0f,
    13.0f,
    32.0f,
    0.0f,
    0.0f,
    28.0f,
    0.0f,
    46.0f,
    56.0f,
    0,
    0,
    0,
    2,
    100,
    0,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_PAIDA_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    5,
    parts,
    init_event,
    data_table,
};

static __declspec(section ".data") BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static __declspec(section ".data") StatusVulnerability regist = {90, 90, 50, 100, 90, 100, 100, 90, 100, 90, 100, 90, 100, 95, 90, 100, 70, 100, 90, 100, 100, 95};

static PoseTableEntry pose_table[] = {
    {1, "PAI_N_1"},
    {2, "PAI_Y_1"},
    {9, "PAI_Y_1"},
    {5, "PAI_K_1"},
    {4, "PAI_X_1"},
    {3, "PAI_X_1"},
    {28, "PAI_S_1"},
    {29, "PAI_D_1"},
    {30, "PAI_D_1"},
    {31, "PAI_S_1"},
    {39, "PAI_D_1"},
    {50, "PAI_A_1"},
    {40, "PAI_W_1"},
    {42, "PAI_W_1"},
    {56, "PAI_X_1"},
    {57, "PAI_X_1"},
    {65, "PAI_S_1"},
    {69, "PAI_S_1"},
};

static __declspec(section ".data") BattleDataEntry data_table[] = {
    {49, dead_event},
    {58, blow_dead_event},
    {63, battle_end_event},
    {48, dmg_first_attack_pos},
    {0, NULL},
};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_piders", "c_paid", 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 0.0f, 0.0f, 50.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
    {2, "btl_un_piders", "c_paid", 0.0f, 0.0f, 5.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_piders", "c_paid", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_piders", "c_paid", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {5, "btl_un_piders", "c_paid", 0.0f, 0.0f, 0.0f, 15.0f, 25.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

static void piders_draw_yarn_sub(CameraId camera, void* param) {
    PidersYarn* yarn = param;
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    GXSetChanMatColor(GX_COLOR0A0, (GXColor){0xFF, 0xFF, 0xFF, yarn->alpha});
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_RASC);
    GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
    GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
    GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    GXLoadPosMtxImm(cam->view, GX_PNMTX0);
    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32_(yarn->x0 - 1.0f, yarn->y0, yarn->z0 - 5.0f);
    GXPosition3f32_(1.0f + yarn->x0, yarn->y0, yarn->z0 - 5.0f);
    GXPosition3f32_(1.0f + yarn->x1, yarn->y1, yarn->z1 - 5.0f);
    GXPosition3f32_(yarn->x1 - 1.0f, yarn->y1, yarn->z1 - 5.0f);
    GXEnd_();
}

static USER_FUNC(piders_draw_yarn) {
    u8 alpha = evtGetValue(event, event->args[0]);
    s32 id = BattleTransID(event, -2);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    PidersYarn* yarn = *(PidersYarn**)&unit->countersetWeapon;

    // from the pider down to its hanging height, and up to the ceiling
    BtlUnit_GetHomePos(unit, &yarn->x1, &yarn->y1, &yarn->z1);
    yarn->y1 = unit->work[2];
    BtlUnit_GetHomePos(unit, &yarn->x0, &yarn->y0, &yarn->z0);
    yarn->y0 = 400.0f;
    yarn->alpha = alpha;
    dispEntry(CAMERA_3D, 0.0f, 2, piders_draw_yarn_sub, yarn);
    return EVT_RETURN_DONE;
}

static USER_FUNC(piders_get_num) {
    BattleUnit* unit;
    s32 i;
    s32* args = event->args;
    s32 num = 0;
    BattleWork* wp = _battleWorkPointer;

    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x1B || unit->currentKind == 0xA4) && !BtlUnit_CheckStatus(unit, 0x1B)) {
            num++;
        }
    }
    evtSetValue(event, args[0], num);
    return EVT_RETURN_DONE;
}

static USER_FUNC(piders_get_zyun) {
    s32 id;
    s32 i;
    s32* args = event->args;
    s32 order = 0;
    BattleWork* wp;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    wp = _battleWorkPointer;
    id = BattleTransID(event, id);
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x1B || unit->currentKind == 0xA4)) {
            if (!BtlUnit_CheckStatus(unit, 0x1B)) {
                order++;
            }
            if (unit->unitId == id) {
                break;
            }
        }
    }
    evtSetValue(event, args[1], order);
    return EVT_RETURN_DONE;
}

static USER_FUNC(piders_get_first_pos_attr) {
    s32 i;
    s32* args = event->args;
    s32 attr;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    // find the first living pider
    for (i = 0; i < 64; i++) {
        unit = wp->units[i];
        if (unit != NULL && (unit->currentKind == 0x1B || unit->currentKind == 0xA4) && !BtlUnit_CheckStatus(unit, 0x1B)) {
            break;
        }
    }
    attr = unit->work[0];
    if (BtlUnit_CanActStatus(unit)) {
        if (attr == 0) {
            attr = 1;
        } else {
            attr = 0;
        }
    }
    evtSetValue(event, args[0], attr);
    return EVT_RETURN_DONE;
}

static USER_FUNC(piders_renzoku_attack_set_target) {
    s32* args = event->args;
    s32 unitIdx[20];
    s32 partIdx[20];
    s32 i;
    s32 num;

    i = 0;
    _battleWorkPointer->weaponTargets.currentTarget = 0;
    piders_get_target(&unitIdx[0], &partIdx[0]);
    while (TRUE) {
        if (unitIdx[i] == -1) {
            num = i;
            break;
        }
        i++;
        piders_get_next_target(&unitIdx[i], &partIdx[i]);
    }
    for (i = 0; i < 3; i++) {
        s32 r = irand(num);
        evtSetValue(event, *args++, unitIdx[r]);
        evtSetValue(event, *args++, partIdx[r]);
    }
    return EVT_RETURN_DONE;
}

#pragma dont_inline on
static void piders_get_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;
    BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];

    *unitIdx = target->unitIdx;
    *partIdx = target->partIdx;
}
#pragma dont_inline reset

#pragma dont_inline on
static void piders_get_next_target(s32* unitIdx, s32* partIdx) {
    BattleWorkWeaponTargets* wt = &_battleWorkPointer->weaponTargets;

    wt->currentTarget++;
    if (wt->currentTarget < wt->numTargets) {
        BattleWorkTarget* target = &wt->targets[wt->targetIndices[wt->currentTarget]];
        *unitIdx = target->unitIdx;
        *partIdx = target->partIdx;
    } else {
        *unitIdx = -1;
        *partIdx = 0;
    }
}
#pragma dont_inline reset

static s32 weapon_piders_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    2, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static s32 weapon_piders_renzoku_attack[] = {
    0, 0, 0, 0, 1677721602, 1065353216, 16843009, (s32)weaponGetPowerDefault,
    1, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 17830496, 536870912, 770, 0, 135, 2047, -2147475456,
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 100, 0, 0,
};

static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, -2, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, -2, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, -2, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, -2, PTR(attack_event))
    CALL(btlevtcmd_SetEventEntry, -2, PTR(entry_event))
    CALL(btlevtcmd_SetUnitWork, -2, 0, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 2, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 3, 1)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 255)
    CALL(piders_yarn_init)
    SPAWN_EVENT(PTR(yarn_event))
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(dmg_first_attack_pos)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 10)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_WaitAttackEnd)
    RETURN
EVT_END()

static EVT_BEGIN(yarn_event)
    LABEL(0)
    CALL(btlevtcmd_GetUnitId, -2, LW(0))
    IF_INT_EQUAL(LW(0), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_GetUnitWork, -2, 1, LW(0))
    IF_INT_LESS(LW(0), 255)
        IF_INT_GREATER(LW(0), 2)
            SUBTRACT(LW(0), 2)
            CALL(btlevtcmd_SetUnitWork, -2, 1, LW(0))
        END_IF
    END_IF
    CALL(piders_draw_yarn, LW(0))
    WAIT_FRAMES(1)
    GOTO(0)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(entry_event)
    CALL(btlevtcmd_GetPos, -2, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 180)
    CALL(btlevtcmd_SetPos, -2, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, -2, 2, 400)
    DIVIDE(LW(0), 10)
    ADD(LW(0), 80)
    WAIT_FRAMES(LW(0))
    CALL(evt_sub_intpl_init, 4, 400, 0, 40)
    LOOP(40)
        CALL(evt_sub_intpl_get_value)
        CALL(btlevtcmd_SetUnitWork, -2, 2, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

static s32 dead_event[] = {
    131122, -30000000, 48, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_1", -250000000,
    0, -250000000, 65539, 10, 65545, 1, 327771, (s32)btlevtcmd_AddRotate,
    -29999990, 0, -15, 0, 131126, -30000000, 1, 131099,
    -30000000, 0, 65540, 10, 33, 327771, (s32)btlevtcmd_SetRotate, -29999990,
    0, 0, 0, 393307, (s32)btlevtcmd_snd_se, -29999990, (s32)"SFX_BTL_ENEMY_DIE1_2", -250000000,
    0, -250000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -30000000, -29999999, -29999998,
    131125, -29999998, 10, 983131, (s32)evt_eff64, (s32)"", (s32)"expbom_n64", -30000000,
    -29999999, -29999998, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163,
    (s32)btlevtcmd_StoreCoin, -30000000, 196699, (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp,
    -30000000, 327771, (s32)btlevtcmd_GetPos, -29999990, -29999997, -29999999, -29999998, 131125,
    -29999998, 10, 131125, -29999999, 30, 327771, (s32)_add_star_point_disp_offset, -29999990,
    -29999997, -29999999, -29999998, 983131, (s32)evt_eff, (s32)"", (s32)"star_point", 0,
    -29999997, -29999999, -29999998, -30000000, 0, 0, 0, 0,
    0, 0, 0, 131101, -30000000, 1, 65541, -30000000,
    6, 33, 327771, (s32)btlevtcmd_SetRotateOffset, -29999990, 0, 0, 0,
    131122, -30000000, 30, 65539, 20, 65545, 1, 327771,
    (s32)btlevtcmd_AddRotate, -29999990, 3, 0, 0, 131126, -30000000, 1,
    131099, -30000000, 0, 65540, 20, 33, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -29999990, 1, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, 1, 33554432,
    262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, 1, 65536, 196699, (s32)btlevtcmd_OnAttribute, -29999990,
    268435456, 196699, (s32)btlevtcmd_SetMaxMoveCount, -29999990, 0, 196699, (s32)btlevtcmd_OnAttribute, -29999990,
    33554432, 327771, (s32)btlevtcmd_SetPos, -29999990, 0, -1000, 0, 196699,
    (s32)btlevtcmd_KillUnit, -29999990, 1, 2, 1,
};

static s32 blow_dead_event[] = {
    196699, (s32)evt_snd_sfxon, (s32)"SFX_BTL_CLAUD_BREATH3", 0, 196699, (s32)btlevtcmd_GetBodyId, -2, -30000000,
    262235, (s32)btlevtcmd_AnimeChangePoseType, -2, -30000000, 39, 110, 65539, 0,
    327771, (s32)btlevtcmd_AddRotate, -2, 0, 20, 0, 65545, 1,
    65540, 0, 112, 196699, (s32)btlevtcmd_SetMoveSpeed, -2, -229997952, 327771,
    (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_GetStageSize, -30000000,
    -250000000, -250000000, 131125, -29999999, 40, 655451, (s32)btlevtcmd_DivePosition, -2,
    -30000000, -29999999, -29999998, 0, -10, 2, 0, -1,
    196699, (s32)btlevtcmd_GetCoin, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreCoin, -30000000, 196699,
    (s32)btlevtcmd_GetExp, -29999990, -30000000, 131163, (s32)btlevtcmd_StoreExp, -30000000, 262235, (s32)btlevtcmd_OnPartsAttribute,
    -29999990, 1, 16777216, 262235, (s32)btlevtcmd_OnPartsAttribute, -29999990, 1, 65536,
    196699, (s32)btlevtcmd_OnAttribute, -29999990, 268435456, 196699, (s32)btlevtcmd_SetMaxMoveCount, -29999990, 0,
    196699, (s32)btlevtcmd_OnAttribute, -29999990, 33554432, 327771, (s32)btlevtcmd_SetPos, -29999990, 0,
    -1000, 0, 196699, (s32)btlevtcmd_KillUnit, -29999990, 1, 2, 1,
};

static __declspec(section ".data") EVT_BEGIN(battle_end_event)
    CALL(btlevtcmd_SetUnitWork, -2, 1, 254)
    RETURN
EVT_END()

static EVT_BEGIN(yure_event)
    BEGIN_INLINE_EVENT
        LOOP(10)
            CALL(btlevtcmd_AddRotate, -2, 0, 6, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(22)
            CALL(btlevtcmd_AddRotate, -2, 0, -5, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(20)
            CALL(btlevtcmd_AddRotate, -2, 0, 4, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(16)
            CALL(btlevtcmd_AddRotate, -2, 0, -3, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(14)
            CALL(btlevtcmd_AddRotate, -2, 0, 2, 0)
            WAIT_FRAMES(1)
        END_LOOP
        LOOP(10)
            CALL(btlevtcmd_AddRotate, -2, 0, -1, 0)
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetRotate, -2, 0, 0, 0)
    END_INLINE_EVENT
    RETURN
EVT_END()

static s32 move_kuutei_event[] = {
    262235, (s32)btlevtcmd_GetUnitWork, -2, 3, -30000000, 131096, -30000000, 1,
    262235, (s32)btlevtcmd_SetUnitWork, -2, 3, 0, 110, 65541, 4,
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAIDA_MOVE1", -250000000, 0, -250000000, 65545,
    7, 6, 112, 32, 110, 65541, 4, 393307,
    (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAIDA_MOVE2", -250000000, 0, -250000000, 65545, 7,
    6, 112, 33, 65630, (s32)yure_event, 327771, (s32)btlevtcmd_GetPos, -2,
    -30000000, -29999999, -29999998, 131122, -29999999, 10, 655451, (s32)btlevtcmd_DivePosition,
    -2, -30000000, -29999999, -29999998, 30, -10, 4, 0,
    -1, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000, -29999999, -29999998, 262235,
    (s32)btlevtcmd_OffPartsAttribute, -2, 1, 6291456, 262235, (s32)btlevtcmd_SetUnitWork, -2, 0,
    1, 2, 1,
};

static s32 move_kuuchu_event[] = {
    65628, (s32)yure_event, 327771, (s32)btlevtcmd_GetPos, -2, -30000000, -29999999, -29999998,
    131122, -29999999, 70, 110, 65541, 4, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_PAIDA_MOVE2", -250000000, 0, -250000000, 65545, 7, 6,
    112, 655451, (s32)btlevtcmd_DivePosition, -2, -30000000, -29999999, -29999998, 30,
    10, 4, 0, -1, 327771, (s32)btlevtcmd_SetHomePos, -2, -30000000,
    -29999999, -29999998, 262235, (s32)btlevtcmd_OnPartsAttribute, -2, 1, 6291456, 262235,
    (s32)btlevtcmd_SetUnitWork, -2, 0, 0, 2, 1,
};

static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_CheckPhase, LW(0), 67108865)
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckStatus, -2, 27, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CheckActStatus, -2, LW(0))
    IF_INT_EQUAL(LW(0), 0)
        GOTO(99)
    END_IF
    CALL(piders_get_zyun, -2, LW(14))
    IF_INT_EQUAL(LW(14), 1)
        CALL(btlevtcmd_GetUnitWork, -2, 0, LW(0))
        IF_INT_EQUAL(LW(0), 1)
            CALL_CHILD(PTR(move_kuuchu_event))
            ELSE
            CALL_CHILD(PTR(move_kuutei_event))
        END_IF
        GOTO(99)
    END_IF
    CALL(piders_get_first_pos_attr, LW(13))
    CALL(piders_get_num, LW(15))
    MODULO(LW(15), 2)
    IF_INT_EQUAL(LW(15), 1)
        IF_INT_EQUAL(LW(13), 0)
            CALL_CHILD(PTR(move_kuuchu_event))
            GOTO(99)
            ELSE
            CALL_CHILD(PTR(move_kuutei_event))
            GOTO(99)
        END_IF
        ELSE
        MODULO(LW(14), 2)
        IF_INT_EQUAL(LW(14), 1)
            IF_INT_EQUAL(LW(13), 0)
                CALL_CHILD(PTR(move_kuuchu_event))
                GOTO(99)
                ELSE
                CALL_CHILD(PTR(move_kuutei_event))
                GOTO(99)
            END_IF
            ELSE
            IF_INT_EQUAL(LW(13), 0)
                CALL_CHILD(PTR(move_kuutei_event))
                GOTO(99)
                ELSE
                CALL_CHILD(PTR(move_kuuchu_event))
                GOTO(99)
            END_IF
        END_IF
    END_IF
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_SetUnitWork, -2, 11, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 12, 0)
    CALL(btlevtcmd_SetUnitWork, -2, 13, 0)
    CALL(btlevtcmd_EnemyItemUseCheck, -2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, -2)
        RETURN
    END_IF
    LABEL(0)
    SET_VALUE(LW(0), 50)
    ADD(LW(0), 50)
    SUBTRACT(LW(0), 1)
    CALL(evt_sub_random, LW(0), LW(1))
    IF_INT_LESS(LW(1), 50)
        SET_VALUE(LW(9), PTR(weapon_piders_attack))
        CALL_CHILD(PTR(normal_attack_event))
        GOTO(99)
    END_IF
    SET_VALUE(LW(9), PTR(weapon_piders_renzoku_attack))
    CALL_CHILD(PTR(renzoku_attack_event))
    GOTO(99)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, -2)
    CALL(btlevtcmd_StartWaitEvent, -2)
    RETURN
EVT_END()

static EVT_BEGIN(damage_check_event_sub)
    CALL(btlevtcmd_PreCheckDamage, -2, LW(3), LW(4), LW(9), 0, LW(0))
    SWITCH(LW(0))
        CASE_OR_EQUAL(4)
        GOTO(90)
        CASE_END
        CASE_EQUAL(3)
        CALL(btlevtcmd_StartAvoid, LW(3), 38)
        GOTO(90)
        CASE_END
        CASE_EQUAL(6)
        CALL(btlevtcmd_StartAvoid, LW(3), 39)
        GOTO(90)
        CASE_EQUAL(2)
        CALL(btlevtcmd_StartAvoid, LW(3), 40)
        GOTO(90)
        CASE_EQUAL(1)
        GOTO(91)
        CASE_END
        CASE_DEFAULT
        GOTO(99)
        CASE_END
    END_SWITCH
    LABEL(90)
    CALL(btlevtcmd_JumpPartsContinue, -2, LW(7))
    CALL(btlevtcmd_OnPartsAttribute, -2, LW(7), 16777216)
    CALL(btlevtcmd_OnPartsAttribute, -2, LW(7), 33554432)
    GOTO(99)
    LABEL(91)
    CALL(btlevtcmd_OnPartsAttribute, -2, LW(7), 16777216)
    CALL(btlevtcmd_OnPartsAttribute, -2, LW(7), 33554432)
    IF_INT_EQUAL(LW(10), 1)
        SET_VALUE(LW(0), 5)
        SET_VALUE(LW(1), 8)
        LOOP(0)
            CALL(btlevtcmd_GetUnitWork, -2, LW(0), LW(2))
            IF_INT_EQUAL(LW(3), LW(2))
                CALL(btlevtcmd_GetUnitWork, -2, LW(1), LW(2))
                IF_INT_EQUAL(LW(4), LW(2))
                    ADD(LW(0), 6)
                    CALL(btlevtcmd_SetUnitWork, -2, LW(0), 1)
                    BREAK_LOOP
                END_IF
            END_IF
            ADD(LW(0), 1)
            ADD(LW(1), 1)
        END_LOOP
    END_IF
    CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
    IF_INT_EQUAL(LW(8), 1)
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(0))
        ELSE
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 0, LW(0))
    END_IF
    GOTO(99)
    LABEL(99)
    RETURN
EVT_END()

static s32 piders_attack_common_event1[] = {
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999992,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999992, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -29999998, -229996928, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PAI_A_1", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"PAI_A_2a", 393307,
    (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_OffPartsAttribute,
    -2, 2, 16777216, 196699, (s32)btlevtcmd_GetStatusMg, -2, -29999999, 131124,
    -30000000, -229969280, 131132, -30000000, -29999999, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2,
    2, 0, -30000000, 0, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAIDA_ATTACK1",
    -250000000, 0, -250000000, 327771, (s32)evt_sub_intpl_init, 4, 0, 110,
    5, 65541, 5, 65627, (s32)evt_sub_intpl_get_value, 131127, -30000000, -29999992,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0, 0, -30000000, 65545,
    1, 6, 65545, 20, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAIDA_ATTACK1",
    -250000000, 0, -250000000, 327771, (s32)evt_sub_intpl_init, 4, 110, 70,
    5, 65541, 5, 65627, (s32)evt_sub_intpl_get_value, 131127, -30000000, -29999992,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0, 0, -30000000, 65545,
    1, 6, 65545, 15, 393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAIDA_ATTACK1",
    -250000000, 0, -250000000, 327771, (s32)evt_sub_intpl_init, 4, 70, 100,
    5, 65541, 5, 65627, (s32)evt_sub_intpl_get_value, 131127, -30000000, -29999992,
    393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0, 0, -30000000, 65545,
    1, 6, 65545, 10, 262235, (s32)btlevtcmd_SetUnitWork, -2, 4,
    -30000000, 2, 1,
};

static s32 piders_attack_common_event1_2[] = {
    458843, (s32)btlevtcmd_CalculateFaceDirection, -2, -1, -29999997, -29999996, 16, -29999992,
    196699, (s32)btlevtcmd_ChangeFaceDirection, -2, -29999992, 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -29999998, -229996928, 262235, (s32)btlevtcmd_AnimeChangePose, -2,
    1, (s32)"PAI_A_1", 262235, (s32)btlevtcmd_AnimeChangePose, -2, 2, (s32)"PAI_A_2a", 393307,
    (s32)btlevtcmd_SetPartsPos, -2, 2, -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_OffPartsAttribute,
    -2, 2, 16777216, 262235, (s32)btlevtcmd_CheckStatus, -2, 11, -30000000,
    196699, (s32)btlevtcmd_GetStatusMg, -2, -29999999, 131124, -30000000, -229969280, 131132,
    -30000000, -29999999, 393307, (s32)btlevtcmd_SetPartsRotateOffset, -2, 2, 0, -30000000,
    0, 262235, (s32)btlevtcmd_GetUnitWork, -2, 4, -30000000, 393307, (s32)btlevtcmd_snd_se,
    -2, (s32)"SFX_ENM_PAIDA_ATTACK1", -250000000, 0, -250000000, 327771, (s32)evt_sub_intpl_init, 4,
    -30000000, 100, 5, 65541, 5, 65627, (s32)evt_sub_intpl_get_value, 131127,
    -30000000, -29999992, 393307, (s32)btlevtcmd_SetPartsRotate, -2, 2, 0, 0,
    -30000000, 65545, 1, 6, 65545, 5, 262235, (s32)btlevtcmd_SetUnitWork,
    -2, 4, -30000000, 2, 1,
};

static EVT_BEGIN(piders_attack_common_event2)
    CALL(btlevtcmd_CalculateFaceDirection, -2, -1, LW(3), LW(4), 16, LW(8))
    CALL(btlevtcmd_ChangeFaceDirection, -2, LW(8))
    CALL(evt_sub_intpl_init, 4, 100, 0, 15)
    LOOP(15)
        CALL(evt_sub_intpl_get_value)
        MULTIPLY(LW(0), LW(8))
        CALL(btlevtcmd_SetPartsRotate, -2, 2, 0, 0, LW(0))
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_AnimeChangePose, -2, 1, STRING("PAI_S_1"))
    CALL(btlevtcmd_OnPartsAttribute, -2, 2, 16777216)
    RETURN
EVT_END()

static s32 piders_attack_common_event3[] = {
    393307, (s32)btlevtcmd_snd_se, -2, (s32)"SFX_ENM_PAIDA_ATTACK2", -250000000, 0, -250000000, 262235,
    (s32)btlevtcmd_AnimeChangePose, -2, -29999993, (s32)"PAI_A_3a", 327771, (s32)btlevtcmd_GetPos, -2, -30000000,
    -29999999, -29999998, 131125, -29999999, 20, 393307, (s32)btlevtcmd_JumpPartsSetting, -2,
    -29999993, 0, -229993856, -229999744, 393307, (s32)btlevtcmd_SetPartsPos, -2, -29999993,
    -30000000, -29999999, -29999998, 262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999993, 16777216,
    262235, (s32)btlevtcmd_OffPartsAttribute, -2, -29999993, 33554432, 393307, (s32)btlevtcmd_SetPartsScale, -2,
    -29999993, -229997952, -229997952, -229997952, 393307, (s32)btlevtcmd_GetHitPos, -29999997, -29999996,
    -30000000, -29999999, -29999998, 524379, (s32)btlevtcmd_JumpPartsPosition, -2, -29999993, -30000000,
    -29999999, -29999998, 0, -1, 2, 1,
};

static EVT_BEGIN(normal_attack_event)
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        GOTO(99)
        ELSE
        CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
        CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
        CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    SET_VALUE(LW(7), 3)
    CALL_CHILD(PTR(piders_attack_common_event1))
    SPAWN_EVENT(PTR(piders_attack_common_event2))
    SET_VALUE(LW(8), 1)
    SET_VALUE(LW(5), 5)
    CALL_CHILD(PTR(piders_attack_common_event3))
    SET_VALUE(LW(10), 0)
    CALL_CHILD(PTR(damage_check_event_sub))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(500)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(renzoku_attack_event)
    CALL(btlevtcmd_GetEnemyBelong, -2, LW(0))
    CALL(btlevtcmd_SamplingEnemy, -2, LW(0), LW(9))
    CALL(btlevtcmd_ChoiceSamplingEnemy, LW(9), LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, -2, 16, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(PTR(subsetevt_confuse_flustered))
            RETURN
        END_IF
        GOTO(99)
    END_IF
    CALL(piders_renzoku_attack_set_target, LW(0), LW(1), LW(2), LW(3), LW(4), LW(5))
    CALL(btlevtcmd_SetUnitWork, -2, 5, LW(0))
    CALL(btlevtcmd_SetUnitWork, -2, 6, LW(2))
    CALL(btlevtcmd_SetUnitWork, -2, 7, LW(4))
    CALL(btlevtcmd_SetUnitWork, -2, 8, LW(1))
    CALL(btlevtcmd_SetUnitWork, -2, 9, LW(3))
    CALL(btlevtcmd_SetUnitWork, -2, 10, LW(5))
    CALL(btlevtcmd_GetUnitWork, -2, 5, LW(3))
    CALL(btlevtcmd_GetUnitWork, -2, 8, LW(4))
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, LW(9))
    CALL(btlevtcmd_AttackDeclare, -2, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, -2, LW(9))
    SET_VALUE(LW(5), 5)
    SET_VALUE(LW(6), 8)
    SET_VALUE(LW(7), 3)
    CALL_CHILD(PTR(piders_attack_common_event1))
    LOOP(3)
        CALL(btlevtcmd_GetUnitWork, -2, LW(5), LW(3))
        CALL(btlevtcmd_GetUnitWork, -2, LW(6), LW(4))
        CALL_CHILD(PTR(piders_attack_common_event3))
        SPAWN_EVENT(PTR(renzoku_attack_event_sub))
        ADD(LW(5), 1)
        ADD(LW(6), 1)
        ADD(LW(7), 1)
        WAIT_FRAMES(30)
    END_LOOP
    SPAWN_EVENT(PTR(piders_attack_common_event2))
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_MS(250)
    LABEL(99)
    RETURN
EVT_END()

static EVT_BEGIN(renzoku_attack_event_sub)
    SET_VALUE(LW(0), LW(5))
    SET_VALUE(LW(1), LW(6))
    CALL(btlevtcmd_GetUnitWork, -2, LW(0), LW(3))
    CALL(btlevtcmd_GetUnitWork, -2, LW(1), LW(4))
    LOOP(0)
        IF_INT_GREATER_OR_EQUAL(LW(0), 7)
            CALL_CHILD(PTR(renzoku_attack_event_sub_last))
            BREAK_LOOP
        END_IF
        ADD(LW(0), 1)
        ADD(LW(1), 1)
        CALL(btlevtcmd_GetUnitWork, -2, LW(0), LW(8))
        CALL(btlevtcmd_GetUnitWork, -2, LW(1), LW(10))
        IF_INT_EQUAL(LW(3), LW(8))
            IF_INT_EQUAL(LW(4), LW(10))
                CALL_CHILD(PTR(renzoku_attack_event_sub_no_last))
                BREAK_LOOP
            END_IF
        END_IF
    END_LOOP
    RETURN
EVT_END()

static __declspec(section ".data") EVT_BEGIN(renzoku_attack_event_sub_no_last)
    SET_VALUE(LW(8), 0)
    SET_VALUE(LW(10), 1)
    CALL_CHILD(PTR(damage_check_event_sub))
    RETURN
EVT_END()

static EVT_BEGIN(renzoku_attack_event_sub_last)
    SET_VALUE(LW(0), 5)
    SET_VALUE(LW(1), 8)
    LOOP(0)
        CALL(btlevtcmd_GetUnitWork, -2, LW(0), LW(2))
        IF_INT_EQUAL(LW(3), LW(2))
            CALL(btlevtcmd_GetUnitWork, -2, LW(1), LW(2))
            IF_INT_EQUAL(LW(4), LW(2))
                ADD(LW(0), 6)
                CALL(btlevtcmd_GetUnitWork, -2, LW(0), LW(2))
                BREAK_LOOP
            END_IF
        END_IF
        ADD(LW(0), 1)
        ADD(LW(1), 1)
    END_LOOP
    IF_INT_EQUAL(LW(2), 1)
        CALL(btlevtcmd_OnPartsAttribute, -2, LW(7), 16777216)
        CALL(btlevtcmd_OnPartsAttribute, -2, LW(7), 33554432)
        CALL(btlevtcmd_ResultACDefence, LW(3), LW(9))
        CALL(btlevtcmd_CheckDamage, -2, LW(3), LW(4), LW(9), 256, LW(0))
        ELSE
        SET_VALUE(LW(8), 1)
        SET_VALUE(LW(10), 0)
        CALL_CHILD(PTR(damage_check_event_sub))
    END_IF
    RETURN
EVT_END()

static __declspec(section ".data") s32 wait_event[] = {
    196699, (s32)btlevtcmd_AnimeChangePoseFromTable, -2, 1, 2, 1, 0,
};

