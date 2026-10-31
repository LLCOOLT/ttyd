// Battle unit data and scripts for Vivian as a partner.
#include "version.h"
#include "battle/battle.h"
#include "battle/battle_database_common.h"
#include "battle/battle_stage.h"
#include "battle/battle_sub.h"
#include "driver/effdrv.h"
#include "driver/msgdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario_party.h"
#include "system.h"
#include "driver/animdrv.h"
#include "pmario_sound.h"
#include <string.h>
#include "battle/battle_attack_audience.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "evt/evt_sub.h"
#include "party/party_motion.h"

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_audience.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "icon_ids.h"
#include "unit/party/unit_party_vivian.h"
#include "libc_decls.h"

USER_FUNC(_vivian_make_extra_work_area);
USER_FUNC(_disp_heart_entry_stop_check);
USER_FUNC(_disp_heart_entry_stop);
void _disp_heart(CameraId camera, void* param);
USER_FUNC(_disp_heart_entry);
USER_FUNC(_make_kagenuke_weapon);
#if VERSION != VERSION_DEMO
USER_FUNC(_get_vivian_attack_position);
#endif
USER_FUNC(_get_move_frame);
static void __makeTechMenuFunc(BattleCommand* command, s32* count);

PoseTableEntry pose_table_vivian_stay[24];
static BattleDataEntry data_table[20];
BattleUnitKindPart unitpartsdata_Party_Vivian[1];
BattleUnitKind unitdata_Party_Vivian;
typedef struct {
    BattleUnitDefense d;
    u8 zeroFill[3];
} VivDef; // zeroFill: the table is 8 bytes in the original data
typedef struct {
    BattleUnitDefenseAttr d;
    u8 zeroFill[3];
} VivDefAttr; // zeroFill: 8 bytes in the original data
typedef struct {
    StatusVulnerability d;
    u8 zeroFill[2];
} VivRegist; // zeroFill: 0x18 bytes in the original data
static VivDef defence;
static VivDefAttr defence_attr;
static VivRegist regist;
static EvtWord init_event[68];
static EvtWord damage_event[16];
static EvtWord wait_event[6];
extern EvtWord vivian_hide_event[];
BattleWeapon partyWeapon_VivianNormalAttack;
BattleWeapon partyWeapon_VivianShadowGuard;
BattleWeapon partyWeapon_VivianMagicalPowder;
BattleWeapon partyWeapon_VivianCharmKissAttack;
extern EvtWord partyVivianAttack_NormalAttack[];
extern EvtWord partyVivianAttack_ShadowGuard[];
extern EvtWord partyVivianAttack_MagicalPowder[];
extern EvtWord partyVivianAttack_CharmKissAttack[];
extern EvtWord vivian_counter_damage_event[];
extern EvtWord vivian_appeal_event[];
static EvtWord party_win_reaction[18];
static EvtWord attack_audience_event[189];

static VivDef defence = {{{0, 0, 0, 0, 0}}, {0, 0, 0}};

static VivDefAttr defence_attr = {{{0, 0, 0, 0, 0}}, {0, 0, 0}};

static VivRegist regist = {{100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, {0, 0}};

PoseTableEntry pose_table_vivian_stay[] = {
#if VERSION == VERSION_DEMO
    {9, "PTR_D_4"},
    {2, "PTR_D_4"},
    {3, "PTR_X_1"},
    {4, "PTR_D_2"},
    {5, "PTR_X_1"},
    {1, "PTR_N_1"},
    {27, "PTR_D_3"},
    {28, "PTR_S_1"},
    {37, "PTR_G_2"},
    {31, "PTR_G_1"},
    {39, "PTR_D_1"},
    {40, "PTR_W_1"},
    {42, "PTR_R_1"},
    {57, "PTR_D_2"},
    {56, "PTR_D_2"},
    {58, "PTR_D_4"},
    {59, "PTR_D_2"},
    {63, "PTR_T_1"},
    {52, "PTR_I_1"},
    {65, "PTR_C_1"},
    {62, "PTR_X_1"},
    {49, "PTR_D_1"},
    {45, "PTR_G_1"},
    {67, "PTR_S_1"},
#else
    {9, "PTR_D_4"},
    {2, "PTR_D_4"},
    {3, "PTR_X_1"},
    {4, "PTR_D_2"},
    {5, "PTR_X_1"},
    {1, "PTR_N_1"},
    {27, "PTR_D_3"},
    {28, "PTR_S_1"},
    {37, "PTR_G_2"},
    {31, "PTR_G_1"},
    {39, "PTR_D_1"},
    {40, "PTR_W_1"},
    {42, "PTR_R_1"},
    {57, "PTR_D_2"},
    {56, "PTR_D_2"},
    {60, "PTR_D_4"},
    {61, "PTR_D_2"},
    {65, "PTR_T_1"},
    {52, "PTR_I_1"},
    {67, "PTR_C_1"},
    {64, "PTR_X_1"},
    {49, "PTR_D_1"},
    {45, "PTR_G_1"},
    {69, "PTR_S_1"},
#endif
};

static BattleDataEntry data_table[] = {
    {3, vivian_hide_event},
    {5, vivian_appeal_event},
    {6, attack_audience_event},
    {1, __makeTechMenuFunc},
    {25, vivian_counter_damage_event},
    {26, vivian_counter_damage_event},
    {27, vivian_counter_damage_event},
    {28, vivian_counter_damage_event},
    {29, vivian_counter_damage_event},
    {30, vivian_counter_damage_event},
    {31, vivian_counter_damage_event},
    {32, vivian_counter_damage_event},
    {33, vivian_counter_damage_event},
    {34, vivian_counter_damage_event},
    {35, vivian_counter_damage_event},
    {48, btldefaultevt_Dummy},
    {64, party_win_reaction},
    {7, subset_attack_ready_jump_event},
    {47, btldefaultevt_avoid_counter_event},
    {0, NULL},
};

BattleUnitKindPart unitpartsdata_Party_Vivian[] = {
    {1, "btl_un_vivian", "c_vivian", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence.d, &defence_attr.d, 0x9, 0, pose_table_vivian_stay},
};

BattleUnitKind unitdata_Party_Vivian = {
    228,
    "btl_un_vivian",
    10,
    5,
    5,
    1,
    1,
    0,
    0,
    0,
    0,
    100,
    9,
    20,
    33,
    14,
    36,
    0.0f,
    12.0f,
    0.0f,
    0,
    0,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    40.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    10.0f,
    0.0f,
    0.0f,
    10.0f,
    21.45f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0,
    0,
    -1,
    0,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_PARTY_DAMAGE1",
    "SFX_MARIO_DAMAGE_FIRE1",
    "SFX_MARIO_DAMAGE_ICE1",
    "SFX_MARIO_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_FLOATING | UNIT_ATTR_NO_HP_GAUGE,
    &regist.d,
    1,
    unitpartsdata_Party_Vivian,
    init_event,
    data_table,
};

static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

USER_FUNC(battle_evt_majo_disp_on) {
    EvtWord* args = event->args;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, partNo, flag;
    f32 px, py, pz;
    s32 pose;

    id = BattleTransID(event, evtGetValue(event, args[0]));
    partNo = evtGetValue(event, args[1]);
    px = evtGetFloat(event, args[2]);
    py = evtGetFloat(event, args[3]);
    pz = evtGetFloat(event, args[4]);
    flag = evtGetValue(event, args[5]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BattleGetUnitPartsPtr(id, partNo);
    pose = part->poseId;
    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        {
            Vec v = {0.0f, 0.0f, 0.0f};
            v.x = px;
            v.y = py - 200.0f;
            v.z = pz;
            unit->position = v;
        }
        animEffectAsync("p_bibi", 1);
    }
    switch (event->userdata[0]) {
        case 0:
            part->shadowScale = intplGetValue(0, 0.0f, 2.0f, event->userdata[1], 30);
            if (event->userdata[1] == 0) {
                psndSFXOn_3D("SFX_BTL_VIVIAN_SHADOW1_1", &unit->position);
            }
            event->userdata[1]++;
            if (event->userdata[1] > 15) {
                event->userdata[0]++;
            }
            break;
        case 1:
            if (event->userdata[1] <= 30) {
                part->shadowScale = intplGetValue(0, 0.0f, 2.0f, event->userdata[1], 30);
                event->userdata[1]++;
            }
            if (!animEffectAsync("p_bibi", 1)) {
                return EVT_RETURN_BLOCK;
            }
            {
                Vec v = {0.0f, 0.0f, 0.0f};
                v.x = px;
                v.y = py;
                v.z = pz;
                unit->position = v;
            }
            animPoseSetEffect(pose, "p_bibi", 1);
            animPoseSetEffectAnim(pose, "PM_B_2", 1);
            event->userdata[0]++;
            break;
        case 2:
            if (event->userdata[1] <= 30) {
                part->shadowScale = intplGetValue(0, 0.0f, 2.0f, event->userdata[1], 30);
                event->userdata[1]++;
            }
            if (animPoseGetLoopTimes(animPoseGetAnimPosePtr(pose)->paperId) >= 0.6666667f) {
                animPoseSetPaperAnimGroup(pose, NULL, 1);
                event->userdata[0]++;
                event->userdata[1] = 0;
            }
            break;
        case 3:
            part->shadowScale = intplGetValue(0, 2.0f, 1.0f, event->userdata[1], 15);
            event->userdata[1]++;
            if (event->userdata[1] > 15) {
                part->shadowScale = 1.0f;
                animPoseSetEffect(pose, NULL, 1);
                if (flag != 0) {
                    unit->flags &= ~UNIT_FLAG_SHARED_SHADOW;
                }
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}

static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 250)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_SUBHANG1"), STRING("SFX_PARTY_BATTLE_SUBHANG1"), 0, 6, 6, 0, 0)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

static EVT_BEGIN(init_event)
    CALL(_vivian_make_extra_work_area)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    SPAWN_EVENT(PTR(vivian_shadow_tail_event))
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 11, 11)
    CALL(btlevtcmd_SetDiveSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 11, 11)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(PTR(btldefaultevt_Damage))
    RETURN
EVT_END()

EVT_BEGIN(vivian_hide_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        SUBTRACT(LW(0), 1)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 0)
        SET_VALUE(LW(3), -3)
        CALL(btlevtcmd_PhaseEventStartDeclare, LW(3))
        CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 15)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        BEGIN_INLINE_EVENT
            CALL(btlevtcmd_OffAttribute, LW(3), UNIT_ATTR_VEILED)
            CALL(btlevtcmd_OffPartsAttribute, LW(3), 1, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
            CALL(battle_evt_majo_disp_on, LW(3), 1, LW(0), LW(1), LW(2), 1)
            CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetMoveSpeed, LW(3), FLOAT(2.0f))
            CALL(btlevtcmd_MovePosition, LW(3), LW(0), LW(1), LW(2), 0, -1, 0)
        END_INLINE_EVENT
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NOT_TARGETABLE)
        CALL(btlevtcmd_OffPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_HIDDEN)
        CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 1)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), FLOAT(2.0f), LW(15))
        BEGIN_SIBLING_EVENT_GET_ID(LW(14))
            CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), LW(15), -1, 0)
        END_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, LW(15), LW(15), 15)
        CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
        SWITCH(LW(6))
            CASE_GREATER_OR_EQUAL(2)
            DELETE_EVENT(LW(14))
            CALL(btlevtcmd_AudienceDeclareAcrobatResult, PTR(&partyWeapon_VivianShadowGuard), 1, 0, 0, 0)
            CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
            CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
            CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
            CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
            CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
            CASE_DEFAULT
            CALL(evt_audience_acrobat_notry)
            CALL(btlevtcmd_WaitEventEnd, LW(14))
        END_SWITCH
        CALL(evt_audience_ap_recovery)
        CALL(btlevtcmd_InviteApInfoReport)
        CALL(btlevtcmd_StartWaitEvent, LW(3))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    END_IF
    RETURN
EVT_END()

static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

BattleWeapon partyWeapon_VivianNormalAttack = {
    "btl_wn_ptr_normal", // name
#if VERSION >= VERSION_US
    344, // icon
#else
    336, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_ptr_kagenuke", // description
    100, // baseAccuracy
    0, 0, 0, // baseFpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetPowerFromPartyAttackLv, // hpDamageFn
    {3, 3, 4, 4, 5, 5, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_kagenuke", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_USABLE_IF_CONFUSED | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_TOP_SPIKY, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, // poisonStrength..dodgyTime
    100, // burnChance
    2, // burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    partyVivianAttack_NormalAttack, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 4, 2, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 2, 2, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

BattleWeapon partyWeapon_VivianShadowGuard = {
    "btl_wn_ptr_lv1", // name
#if VERSION >= VERSION_US
    345, // icon
#else
    337, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_ptr_kagegakure", // description
    100, // baseAccuracy
    1, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
#if VERSION >= VERSION_US
    1, // stylishCommandMultiplier
#else
    2, // stylishCommandMultiplier
#endif
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    NULL, // hpDamageFn
    {0, 2, 2, 3, 3, 4, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OPPOSING_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_NO_FLOATING | TARGET_PROP_START_OWN_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_kagegakure", // acHelpMsg
    SPECIAL_ALWAYS_HITS | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    partyVivianAttack_ShadowGuard, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

BattleWeapon partyWeapon_VivianMagicalPowder = {
    "btl_wn_ptr_lv2", // name
#if VERSION >= VERSION_US
    346, // icon
#else
    338, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_ptr_mahou_no_kona", // description
    100, // baseAccuracy
    6, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    weaponGetACOutputParam, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    1, // element
    0, // damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_mahou_no_kona", // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_PIERCES_DEFENSE | SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, // poisonStrength..dodgyTime
    100, // burnChance
    3, // burnTime
    0, 0, 0, 0, 0, 0, 0, 0, // freezeChance..atkChangeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeChance..fastChance
    0, 0, 0, 0, 0, 0, 0, 0, // fastTime..invisibleChance
    0, 0, 0, 0, 0, // invisibleTime..fpRegenStrength
    {0}, // pad_AE
    partyVivianAttack_MagicalPowder, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 10, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 5, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

BattleWeapon partyWeapon_VivianCharmKissAttack = {
    "btl_wn_ptr_lv3", // name
#if VERSION >= VERSION_US
    347, // icon
#else
    339, // icon
#endif
    {0}, // pad_06
    0, // itemId
    "msg_ptr_meromero_kiss", // description
    100, // baseAccuracy
    4, // baseFpCost
    0, 0, // baseSpCost..superguardsAllowed
    1.0f, // reserved_14
#if VERSION >= VERSION_US
    1, // stylishCommandMultiplier
#else
    2, // stylishCommandMultiplier
#endif
    5, // reserved_19
    100, // bingoSlotChance
    50, // reserved_1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_MULTIPLE, // targetClassFlags
    TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_meromero_kiss", // acHelpMsg
    SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, // poisonStrength
#if VERSION == VERSION_DEMO
    90, // confuseChance
#else
    100, // confuseChance
#endif
    3, // confuseTime
    0, 0, 0, 0, 0, 0, 0, 0, // electricChance..freezeTime
    0, 0, 0, 0, 0, 0, 0, 0, // sizeChangeChance..defChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // defChangeStrength..slowChance
    0, 0, 0, 0, 0, 0, 0, 0, // slowTime..hpRegenTime
    0, 0, 0, // hpRegenStrength..fpRegenStrength
    {0}, // pad_AE
    partyVivianAttack_CharmKissAttack, // attackEvtScript
#if VERSION >= VERSION_US
    {0, 0, 0, 100, 0, 10, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#else
    {0, 0, 0, 100, 0, 5, 5, 0, 0, 0, 0, 0}, // stageEffectRates
#endif
};

#if VERSION >= VERSION_US
EVT_BEGIN(partyVivianAttack_NormalAttack)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetPartyTechLv, BTL_UNIT_SELF, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(2)
        CALL(_make_kagenuke_weapon, LW(12), 2)
        CASE_EQUAL(1)
        CALL(_make_kagenuke_weapon, LW(12), 2)
        CASE_DEFAULT
        CALL(_make_kagenuke_weapon, LW(12), 2)
    END_SWITCH
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcSetParamAll, 1, 1, 40, 1, 2, 0, 3, 0)
    CALL(btlevtcmd_AcSetFlag, 23)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 18, 1, 0)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_VIVIAN_ATTACK1"), 0)
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(_get_vivian_attack_position, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 50, 0, 5, 0, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 1)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(_get_vivian_attack_position, LW(3), LW(0), LW(1), LW(2))
    CALL(_get_vivian_attack_position, LW(3), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_TransStageFloorPosition, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_GetFaceDirection, LW(3), LW(15))
    MULTIPLY(LW(15), -1)
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(6), LW(7), LW(8))
    CALL(_get_move_frame, LW(0), LW(1), LW(2), LW(6), LW(7), LW(8), FLOAT(4.0f), LW(6))
    IF_INT_GREATER_OR_EQUAL(LW(6), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, 0, 5, 0, -1)
    END_IF
    LABEL(9)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    CALL(btlevtcmd_ResultAC)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    IF_INT_GREATER_OR_EQUAL(LW(10), 1)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 1048832, LW(5))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
    END_SWITCH
    IF_INT_NOT_EQUAL(LW(5), 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_2"))
        WAIT_MS(166)
        IF_INT_EQUAL(LW(5), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(5), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(5), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        WAIT_MS(500)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_2"))
    CALL(btlevtcmd_ftomsec, 4, LW(0))
    WAIT_MS(LW(0))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_VIVIAN_ATTACK4"), 0)
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 131328, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 536871168, LW(5))
    END_IF
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    ELSE
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    WAIT_MS(500)
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, 0, 5, 0, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 5, 0, -1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 14, 29, 29, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
        WAIT_FRAMES(52)
    END_IF
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()
#else
EVT_BEGIN(partyVivianAttack_NormalAttack)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_GetPartyTechLv, BTL_UNIT_SELF, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(2)
        CALL(_make_kagenuke_weapon, LW(12), 2)
        CASE_EQUAL(1)
        CALL(_make_kagenuke_weapon, LW(12), 2)
        CASE_DEFAULT
        CALL(_make_kagenuke_weapon, LW(12), 2)
    END_SWITCH
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(evt_btl_camera_set_mode, 0, 11)
    CALL(evt_btl_camera_set_homing_unitparts, 0, BTL_UNIT_SELF, 1, LW(3), LW(4))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcSetParamAll, 1, 1, 40, 1, 2, 0, 3, 0)
    CALL(btlevtcmd_AcSetFlag, 23)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 18, 1, 0)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_VIVIAN_ATTACK1"), 0)
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
#if VERSION == VERSION_DEMO
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_TransStageFloorPosition, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SUBTRACT(LW(1), 20)
    IF_INT_LESS(LW(1), LW(7))
        SET_VALUE(LW(1), LW(7))
    END_IF
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
#else
    CALL(_get_vivian_attack_position, LW(3), LW(0), LW(1), LW(2))
#endif
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 50, 0, 5, 0, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 1)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
#if VERSION == VERSION_DEMO
    CALL(btlevtcmd_TransStageFloorPosition, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SUBTRACT(LW(1), 20)
    IF_INT_LESS(LW(1), LW(7))
        SET_VALUE(LW(1), LW(7))
    END_IF
#else
    CALL(_get_vivian_attack_position, LW(3), LW(0), LW(1), LW(2))
    CALL(_get_vivian_attack_position, LW(3), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_TransStageFloorPosition, LW(6), LW(7), LW(8))
#endif
    CALL(btlevtcmd_GetFaceDirection, LW(3), LW(15))
    MULTIPLY(LW(15), -1)
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(6), LW(7), LW(8))
    CALL(_get_move_frame, LW(0), LW(1), LW(2), LW(6), LW(7), LW(8), FLOAT(4.0f), LW(6))
    IF_INT_GREATER_OR_EQUAL(LW(6), 1)
        CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_ATTACK3"), EVT_NULLPTR, 0, EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, 0, 5, 0, -1)
    END_IF
    LABEL(9)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    CALL(btlevtcmd_ResultAC)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    IF_INT_GREATER_OR_EQUAL(LW(10), 1)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 1048832, LW(5))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 256, LW(5))
    END_IF
    SWITCH(LW(5))
        CASE_OR_EQUAL(2)
        CASE_OR_EQUAL(3)
        CASE_OR_EQUAL(6)
        CASE_OR_EQUAL(4)
        CASE_END
        CASE_EQUAL(1)
        CASE_DEFAULT
    END_SWITCH
    IF_INT_NOT_EQUAL(LW(5), 1)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_2"))
        WAIT_MS(166)
        IF_INT_EQUAL(LW(5), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(5), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(5), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        WAIT_MS(500)
        GOTO(90)
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_2"))
    CALL(btlevtcmd_ftomsec, 4, LW(0))
    WAIT_MS(LW(0))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_VIVIAN_ATTACK4"), 0)
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 131328, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), 536871168, LW(5))
    END_IF
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
        CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    ELSE
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
    END_IF
    WAIT_MS(500)
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, 0, 5, 0, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 5, 0, -1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 20, 29, 29, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
        WAIT_FRAMES(52)
    END_IF
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()
#endif

EVT_BEGIN(partyVivianAttack_ShadowGuard)
    SET_VALUE(LW(3), -3)
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(evt_btl_camera_set_posoffset, 0, 20, 0, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), -1, 16, LW(0))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A2_1"))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, LW(3), LW(0), 15)
    ADD(LW(2), 5)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), -1, 16, LW(0))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 420)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 330)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 270)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 240)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 200)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 160)
        CASE_DEFAULT
        SET_VALUE(LW(0), 120)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, LW(0), 1, 5, -2, 5, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 0)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 10, 1, 0)
    WAIT_FRAMES(22)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_CLEAR(LW(0), 2)
        CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        CALL(btlevtcmd_StopAC)
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(2.0f))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        GOTO(90)
    END_IF
#if VERSION == VERSION_DEMO
    CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
#else
    CALL(btlevtcmd_GetResultPrizeLv, BTL_UNIT_NONE, 0, LW(6))
#endif
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
    CALL(btlevtcmd_StopAC)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 350)
#if VERSION != VERSION_DEMO
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
#endif
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A2_2"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A2_3"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_AnimeChangePose, LW(3), 1, STRING("M_B_3"))
        CALL(battle_evt_majo_disp_off, LW(3), 1, 1, 0)
        CALL(btlevtcmd_OnAttribute, LW(3), UNIT_ATTR_VEILED)
        CALL(btlevtcmd_OnPartsAttribute, LW(3), 1, PART_ATTR_HIDDEN | PART_ATTR_NO_SHADOW)
        WAIT_FRAMES(1)
        CALL(btlevtcmd_GetHomePos, LW(3), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetPos, LW(3), LW(0), LW(1), LW(2))
    END_SIBLING_EVENT
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 1, 1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, LW(3), LW(5), LW(1), LW(2))
    ADD(LW(0), LW(5))
    DIVIDE(LW(0), 2)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    ADD(LW(1), 1)
    CALL(evt_eff, 0, STRING("ripple"), 1, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(333)
    CALL(btlevtcmd_OnPartsAttribute, BTL_UNIT_SELF, 1, PART_ATTR_NOT_TARGETABLE | PART_ATTR_HIDDEN)
    WAIT_FRAMES(1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 4, 1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, -1, -1, 4, LW(0))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(0))
    WAIT_MS(500)
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
#if VERSION != VERSION_DEMO
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
#endif
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

#if VERSION >= VERSION_US
EVT_BEGIN(partyVivianAttack_MagicalPowder)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 360)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 270)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 210)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 180)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 160)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 140)
        CASE_DEFAULT
        SET_VALUE(LW(0), 120)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, LW(0), 1, 5, -3, 1, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 7)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 10, 1, 0)
    WAIT_FRAMES(22)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 4)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    CALL(evt_btl_camera_set_posoffset, 0, 20, 0, 0)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_StopAC)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetWidth, BTL_UNIT_SELF, LW(5))
        CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(6))
        CALL(evt_eff, 0, STRING("stardust"), 4, LW(0), LW(1), LW(2), LW(5), LW(6), 30, 60, 0, 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A3_1"))
    CALL(btlevtcmd_ftof, 20, LW(0))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_ftof, 26, LW(0))
    CALL(btlevtcmd_ftof, 46, LW(1))
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, LW(0), LW(1), LW(1), 0)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    SWITCH(LW(6))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
        CASE_DEFAULT
        CALL(evt_audience_acrobat_notry)
    END_SWITCH
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
    WAIT_FRAMES(40)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 6, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(50)
    END_IF
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 3)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    END_IF
    IF_INT_EQUAL(LW(5), 18)
        CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
        SWITCH(LW(0))
            CASE_LESS_OR_EQUAL(0)
            SET_VALUE(LW(0), -1)
            CASE_OR_EQUAL(1)
            CASE_OR_EQUAL(2)
            SET_VALUE(LW(0), 0)
            CASE_END
            CASE_OR_EQUAL(3)
            CASE_OR_EQUAL(4)
            SET_VALUE(LW(0), 1)
            CASE_END
            CASE_DEFAULT
            SET_VALUE(LW(0), 2)
        END_SWITCH
        IF_INT_GREATER_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
        ELSE
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        END_IF
    END_IF
    LABEL(50)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(80)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_1"))
    WAIT_MS(800)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()
#else
EVT_BEGIN(partyVivianAttack_MagicalPowder)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(0), 360)
        CASE_EQUAL(-2)
        SET_VALUE(LW(0), 270)
        CASE_EQUAL(-1)
        SET_VALUE(LW(0), 210)
        CASE_EQUAL(0)
        SET_VALUE(LW(0), 180)
        CASE_EQUAL(1)
        SET_VALUE(LW(0), 160)
        CASE_EQUAL(2)
        SET_VALUE(LW(0), 140)
        CASE_DEFAULT
        SET_VALUE(LW(0), 120)
    END_SWITCH
    CALL(btlevtcmd_AcSetParamAll, LW(0), 1, 5, -3, 1, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_AcSetFlag, 7)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 10, 1, 0)
    WAIT_FRAMES(22)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, 1)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 4)
    CALL(evt_btl_camera_set_zoom, 0, 400)
    CALL(evt_btl_camera_set_posoffset, 0, 20, 0, 0)
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_StopAC)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetWidth, BTL_UNIT_SELF, LW(5))
        CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(6))
        CALL(evt_eff, 0, STRING("stardust"), 4, LW(0), LW(1), LW(2), LW(5), LW(6), 30, 60, 0, 0, 0, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_MAGIC1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A3_1"))
    CALL(btlevtcmd_ftof, 20, LW(0))
    WAIT_FRAMES(20)
    CALL(btlevtcmd_ftof, 26, LW(0))
    CALL(btlevtcmd_ftof, 46, LW(1))
    CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, LW(0), LW(1), LW(1), 0)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    SWITCH(LW(6))
        CASE_GREATER_OR_EQUAL(2)
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(12), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
        CASE_DEFAULT
        CALL(evt_audience_acrobat_notry)
    END_SWITCH
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    WAIT_FRAMES(40)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 6, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(50)
    END_IF
    CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
    IF_INT_LESS_OR_EQUAL(LW(0), 3)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(5))
    END_IF
    IF_INT_EQUAL(LW(5), 18)
        CALL(btlevtcmd_AcGetOutputParam, 0, LW(0))
        SWITCH(LW(0))
            CASE_LESS_OR_EQUAL(0)
            SET_VALUE(LW(0), -1)
            CASE_OR_EQUAL(1)
            CASE_OR_EQUAL(2)
            SET_VALUE(LW(0), 0)
            CASE_END
            CASE_OR_EQUAL(3)
            CASE_OR_EQUAL(4)
            SET_VALUE(LW(0), 1)
            CASE_END
            CASE_DEFAULT
            SET_VALUE(LW(0), 2)
        END_SWITCH
        IF_INT_GREATER_OR_EQUAL(LW(0), 0)
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), LW(0), LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
        ELSE
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        END_IF
    END_IF
    LABEL(50)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(80)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_1"))
    WAIT_MS(800)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()
#endif

EVT_BEGIN(partyVivianAttack_CharmKissAttack)
    CALL(btlevtcmd_GetSelectEnemy, LW(3), LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_AttackDeclareAll, BTL_UNIT_SELF)
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_CommandPayWeaponCost, BTL_UNIT_SELF)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    WAIT_FRAMES(20)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A4_1"))
    CALL(evt_snd_sfxon, STRING("SFX_PARTY_MOJIMOJI1"), 0)
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcGetDifficulty, LW(0))
    SUBTRACT(LW(0), 3)
    SWITCH(LW(0))
        CASE_LESS_OR_EQUAL(-3)
        SET_VALUE(LW(5), 60)
        CASE_EQUAL(-2)
        SET_VALUE(LW(5), 45)
        CASE_EQUAL(-1)
        SET_VALUE(LW(5), 30)
        CASE_EQUAL(0)
        SET_VALUE(LW(5), 25)
        CASE_EQUAL(1)
        SET_VALUE(LW(5), 20)
        CASE_EQUAL(2)
        SET_VALUE(LW(5), 12)
        CASE_DEFAULT
        SET_VALUE(LW(5), 6)
    END_SWITCH
    CALL(evt_sub_random, LW(1), 89)
    ADD(LW(1), 30)
    SET_VALUE(LW(2), LW(1))
    SUBTRACT(LW(2), LW(5))
    CALL(btlevtcmd_AcSetParamAll, 5, LW(1), LW(2), LW(1), EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR, EVT_NULLPTR)
    IF_INT_GREATER(LW(10), 0)
        CALL(btlevtcmd_AcSetFlag, 9)
    ELSE
        CALL(btlevtcmd_AcSetFlag, 8)
    END_IF
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 11, 1, 0)
    WAIT_FRAMES(22)
    IF_INT_GREATER(LW(10), 0)
        CALL(btlevtcmd_StartAC, 0)
    ELSE
        CALL(btlevtcmd_StartAC, 1)
    END_IF
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        SET_VALUE(LW(0), 5)
        LOOP(LW(0))
            CALL(btlevtcmd_AcGetOutputParam, 2, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                CALL(_disp_heart_entry, 10, 20, 25, LW(3), LW(4))
                WAIT_FRAMES(1)
                BREAK_LOOP
            END_IF
            CALL(_disp_heart_entry_stop_check, LW(1))
            IF_INT_NOT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            SET_VALUE(LW(0), 5)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_GetResultAC, LW(7))
    IS_EVENT_RUNNING(LW(15), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(_disp_heart_entry_stop, LW(15))
    END_IF
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A4_2"))
    WAIT_MS(200)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_MEROMERO1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 30)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(6))
    MULTIPLY(LW(6), 45)
    CALL(evt_eff, 0, STRING("kiss"), 4, LW(0), LW(1), LW(2), LW(6), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 256, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 1)
        IF_INT_EQUAL(LW(6), 3)
            CALL(btlevtcmd_StartAvoid, LW(3), 38)
        END_IF
        IF_INT_EQUAL(LW(6), 6)
            CALL(btlevtcmd_StartAvoid, LW(3), 39)
        END_IF
        IF_INT_EQUAL(LW(6), 2)
            CALL(btlevtcmd_StartAvoid, LW(3), 40)
        END_IF
        GOTO(50)
    END_IF
    IF_BITS_SET(LW(7), 2)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 131328, LW(5))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), 536871168, LW(5))
    END_IF
    IF_INT_EQUAL(LW(5), 18)
        IF_BITS_SET(LW(7), 2)
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            ADD(LW(2), 10)
            CALL(evt_eff, 0, STRING("kiss"), 5, LW(0), LW(1), LW(2), 0, 0, 0, 0, 0, 0, 0, 0)
            CALL(btlevtcmd_GetResultPrizeLv, LW(3), 0, LW(6))
            CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_ACSuccessEffect, LW(6), LW(0), LW(1), LW(2))
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), LW(6))
        ELSE
            CALL(btlevtcmd_AudienceDeclareACResult, LW(12), -1)
        END_IF
    END_IF
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 0, 30, 30, 0)
    END_SIBLING_EVENT
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    CALL(btlevtcmd_ACRGetResult, LW(6), LW(7))
    IF_INT_EQUAL(LW(6), 2)
        CALL(btlevtcmd_CommandGetWeaponAddress, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AudienceDeclareAcrobatResult, LW(0), 1, 0, 0, 0)
        CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
        WAIT_FRAMES(32)
    END_IF
    WAIT_FRAMES(5)
    LABEL(50)
    CALL(btlevtcmd_GetSelectNextEnemy, LW(3), LW(4))
    IF_INT_NOT_EQUAL(LW(3), -1)
        ADD(LW(10), 1)
        GOTO(10)
    END_IF
    LABEL(80)
    CALL(btlevtcmd_StopAC)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(90)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_1"))
    WAIT_FRAMES(48)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

EVT_BEGIN(vivian_shadow_tail_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(1))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(2))
    LABEL(0)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(5))
    IF_INT_EQUAL(LW(5), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 1, LW(1))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 2, LW(2))
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

EVT_BEGIN(vivian_counter_damage_event)
    CALL(btlevtcmd_SetScale, BTL_UNIT_SELF, FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_SHOW_HP_GAUGE)
    IF_INT_EQUAL(LW(0), 43)
        SET_VALUE(LW(14), 36)
    ELSE
        SET_VALUE(LW(14), 39)
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(11), LW(14))
    CALL(btlevtcmd_SetFallAccel, BTL_UNIT_SELF, FLOAT(1.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(2), LW(3), LW(4))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(2), 25)
    ADD(LW(3), 25)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(2), LW(3), LW(4), 5, 0, 0, 0, -1)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 3, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 0, LW(0))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(1))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 2, LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, 0, 5, 0, -1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, 3, 0)
        CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 80, 0, 5, 0, -1)
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
        CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    ELSE
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(2), LW(3), LW(4))
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(2), LW(3), LW(4), 5, 0, 0, 0, -1)
    END_IF
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

EVT_BEGIN(vivian_appeal_event)
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_O_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MARIO_APPEAL1"), LW(0), LW(1), LW(2), 0)
    WAIT_FRAMES(10)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_O_2"))
    WAIT_MS(333)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 15)
    ADD(LW(1), 30)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(14))
    MULTIPLY(LW(14), 45)
    CALL(evt_eff, STRING(""), STRING("kiss"), 0, LW(0), LW(1), LW(2), LW(14), 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(333)
    CALL(btlevtcmd_AudienceAppeal, BTL_UNIT_SELF)
    WAIT_MS(500)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 43)
    RETURN
EVT_END()

static EVT_BEGIN(attack_audience_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(3), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(4))
    SET_VALUE(LW(8), LW(3))
    MULTIPLY(LW(8), LW(4))
    MULTIPLY(LW(8), -1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(8), LW(1), LW(2), 0, -1, 0)
    WAIT_FRAMES(20)
    CALL(_get_attack_aud_no, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageAudienceAreaSize, LW(4), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(5))
    SET_VALUE(LW(6), LW(4))
    MULTIPLY(LW(6), LW(5))
    MULTIPLY(LW(6), -1)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(6), LW(1), LW(2))
    CALL(evt_btl_camera_set_mode, 0, 13)
    CALL(evt_btl_camera_set_homing_unit_audience, 0, BTL_UNIT_SELF, 1, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_set_zoom, 0, 100)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_2"))
    CALL(btlevtcmd_ftomsec, 4, LW(0))
    WAIT_MS(LW(0))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_VIVIAN_ATTACK4"), 0)
    CALL(_attack_aud, LW(3), 0)
    BEGIN_SIBLING_EVENT_GET_ID(LW(15))
        WAIT_MS(1500)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_MS(1000)
    END_SIBLING_EVENT
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 42)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(6), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(8), LW(1), LW(2))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

USER_FUNC(battle_evt_majo_disp_off) {
    EvtWord* args = event->args;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, partNo, flag, flag2;
    s32 pose;

    id = BattleTransID(event, evtGetValue(event, args[0]));
    partNo = evtGetValue(event, args[1]);
    flag = evtGetValue(event, args[2]);
    flag2 = evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BattleGetUnitPartsPtr(id, partNo);
    pose = part->poseId;
    if (isFirstCall) {
        event->userdata[0] = 0;
        event->userdata[1] = 0;
        animEffectAsync("p_bibi", 1);
    }
    switch (event->userdata[0]) {
        case 0:
            part->shadowScale = intplGetValue(0, 1.0f, 2.0f, event->userdata[1], 30);
            if (flag != 0) {
                unit->flags |= UNIT_FLAG_SHARED_SHADOW;
            }
            event->userdata[1]++;
            if (event->userdata[1] > 15) {
                event->userdata[0]++;
            }
            break;
        case 1:
            if (event->userdata[1] <= 30) {
                part->shadowScale = intplGetValue(0, 1.0f, 2.0f, event->userdata[1], 30);
                event->userdata[1]++;
            }
            if (!animEffectAsync("p_bibi", 1)) {
                return EVT_RETURN_BLOCK;
            }
            animPoseSetEffect(pose, "p_bibi", 1);
            animPoseSetEffectAnim(pose, "PM_B_1", 1);
            animPoseSetLocalTime(animPoseGetAnimPosePtr(pose)->paperId, 8.0f);
            event->userdata[0]++;
            break;
        case 2:
            if (event->userdata[1] <= 30) {
                part->shadowScale = intplGetValue(0, 1.0f, 2.0f, event->userdata[1], 30);
                event->userdata[1]++;
            }
            if (animPoseGetLoopTimes(animPoseGetAnimPosePtr(pose)->paperId) >= 1.0f) {
                event->userdata[0]++;
                event->userdata[1] = 0;
                psndSFXOn_3D("SFX_BTL_VIVIAN_SHADOW1_2", &unit->position);
                if (flag2 != 0) {
                    part->attributes |= PART_ATTR_HIDDEN;
                }
            }
            break;
        case 3:
            part->shadowScale = intplGetValue(0, 2.0f, 0.0f, event->userdata[1], 20);
            event->userdata[1]++;
            if (event->userdata[1] > 20) {
                part->shadowScale = 0.0f;
                unit->position.y -= 500.0f;
                animPoseSetEffect(pose, NULL, 1);
                animPoseSetPaperAnimGroup(pose, NULL, 1);
                return EVT_RETURN_DONE;
            }
            break;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(_vivian_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

static void __makeTechMenuFunc(BattleCommand* command, s32* count) {
    s32 techLv;

    techLv = partyGetTechLv(BattleTransPartyId(BattleGetPartyPtr(_battleWorkPointer)->currentKind));

#define ADD_W(w)                                                                    \
    command->weapon[*count].index = -1;                                             \
    command->weapon[*count].itemId = 0;                                             \
    command->weapon[*count].weapon = (BattleWeapon*)(w);                            \
    command->weapon[*count].enabled = 0;                                            \
    command->weapon[*count].icon = command->weapon[*count].weapon->icon;            \
    command->weapon[*count].name = msgSearch(command->weapon[*count].weapon->name); \
    (*count)++;
    ADD_W(&partyWeapon_VivianNormalAttack)
    if (techLv >= 0) {
        ADD_W(&partyWeapon_VivianShadowGuard)
    }
    if (techLv >= 1) {
        ADD_W(&partyWeapon_VivianMagicalPowder)
    }
    if (techLv >= 2) {
        ADD_W(&partyWeapon_VivianCharmKissAttack)
    }
}

USER_FUNC(_get_move_frame) {
    EvtWord* args = event->args;
    Vec a, b, d;
    f32 speed;
    s32 frames, out;

    a.x = evtGetFloat(event, args[0]);
    a.y = evtGetFloat(event, args[1]);
    a.z = evtGetFloat(event, args[2]);
    b.x = evtGetFloat(event, args[3]);
    b.y = evtGetFloat(event, args[4]);
    b.z = evtGetFloat(event, args[5]);
    speed = evtGetFloat(event, args[6]);
    out = args[7];
    PSVECSubtract(&a, &b, &d);
    frames = (s32)((f32)sqrt(d.x * d.x + d.y * d.y + d.z * d.z) / speed);
    if (frames > 15) {
        frames = 15;
    }
    evtSetValue(event, out, frames);
    return EVT_RETURN_DONE;
}

#if VERSION != VERSION_DEMO

USER_FUNC(_get_vivian_attack_position) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* self;
    BattleUnit* target;
    s32 targetId, x, y, z;
    s32 i1, i2, i3;
    s32 ix, iy;
    f32 floor;
    f32 sx, sy, sz;

    targetId = evtGetValue(event, args[0]);
    i1 = args[1];
    x = evtGetValue(event, i1);
    i2 = args[2];
    y = evtGetValue(event, i2);
    i3 = args[3];
    z = evtGetValue(event, i3);
    self = BattleGetUnitPtr(wp, BattleTransID(event, -2));
    target = BattleGetUnitPtr(wp, BattleTransID(event, targetId));
    BtlUnit_GetScale(target, &sx, &sy, &sz);
    ix = (s32)((f32)target->faceDirection * (target->kindParams->vivianOffsetX * sx));
    iy = (s32)(target->kindParams->vivianOffsetZ * sz);
    {
        x += -30.0f * self->sizeMultiplier * (f32)self->faceDirection + ix;
        z = z + iy;
        y -= 20.0f * self->sizeMultiplier;
    }
    floor = BattleGetFloorHeight(wp, x, y, z);
    if (floor > y) {
        y = (s32)floor;
    }
    evtSetValue(event, i1, x);
    evtSetValue(event, i2, y);
    evtSetValue(event, i3, z);
    return EVT_RETURN_DONE;
}
#endif

USER_FUNC(_make_kagenuke_weapon) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 index;
    BattleWeapon* weapon;
    void* src;
    s32 id, value;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    index = args[0];
    weapon = unit->countersetWeapon;
    src = (void*)evtGetValue(event, index);
    value = evtGetValue(event, args[1]);
    memcpy(weapon, src, sizeof(BattleWeapon));
    weapon->burnTime = value;
    evtSetValue(event, index, (EvtWord)weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(_disp_heart_entry) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    if (isFirstCall) {
        event->heart.unit = unit;
        event->heart.cur = 0;
        event->heart.start = evtGetValue(event, args[0]);
        event->heart.end = evtGetValue(event, args[1]);
        event->heart.total = evtGetValue(event, args[2]);
        event->heart.stop = 0;
        event->heart.unitId = evtGetValue(event, args[3]);
        event->heart.partId = evtGetValue(event, args[4]);
    }
    if (event->heart.stop != 0) {
        return EVT_RETURN_DONE;
    }
    event->heart.cur++;
    dispEntry(CAMERA_3D, 0.0f, 1, (DispCallback)_disp_heart, event);
    return event->heart.cur < event->heart.total ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

void _disp_heart(CameraId camera, void* param) {
    EventEntry* w;
    f32 scale;
    Vec p, b, a, c;
    BattleUnit* unit;

    if (param == NULL) {
        return;
    }
    w = param;
    if (w->heart.unit != NULL) {
        {
            if (w->heart.cur <= w->heart.start) {
                scale = intplGetValue(5, 0.0f, 1.2f, w->heart.cur, w->heart.start);
            } else if (w->heart.cur <= w->heart.end) {
                scale = intplGetValue(0xb, 1.2f, 1.0f, w->heart.cur - w->heart.start, w->heart.end - w->heart.start);
            } else {
                scale = 1.0f;
            }
            unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(w, w->heart.unitId));
            BtlUnit_GetHitPos(unit, BtlUnit_GetPartsPtr(unit, w->heart.partId), &p.x, &p.y, &p.z);
            p.z += 10.0f;
            a = p;
            b = p;
            c = p;
            b.y = 16.0f * scale + a.y;
            b.z = 5.0f + a.z;
            iconDispGx(&a, 0, ICON_1F2, scale);
            iconDispGx(&b, 0, ICON_189, scale);
        }
    }
}

USER_FUNC(_disp_heart_entry_stop) {
    EventEntry* e = evtGetPtrID(evtGetValue(event, *event->args));
    e->heart.stop = 1;
    return EVT_RETURN_DONE;
}

USER_FUNC(_disp_heart_entry_stop_check) {
    evtSetValue(event, *event->args, event->heart.stop);
    return EVT_RETURN_DONE;
}
