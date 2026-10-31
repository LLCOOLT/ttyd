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

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"
#include "evt/evt_audience.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"
#include "icon_ids.h"
#include "unit/party/unit_party_vivian.h"
#include "libc_decls.h"

static USER_FUNC(_vivian_make_extra_work_area);
static USER_FUNC(_disp_heart_entry_stop_check);
static USER_FUNC(_disp_heart_entry_stop);
static void _disp_heart(CameraId camera, void* param);
static USER_FUNC(_disp_heart_entry);
static USER_FUNC(_make_kagenuke_weapon);
// Forward declaration: the Shade Fist positioning helper, defined further down; the US demo has neither.
#if VERSION >= VERSION_JP
USER_FUNC(_get_vivian_attack_position);
#endif
static USER_FUNC(_get_move_frame);
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

/** Vivian's defence: 0 against every element. */
static VivDef defence = {{{0, 0, 0, 0, 0}}, {0, 0, 0}};

/** Vivian's defence attributes: normal (0) against every element, no weakness or immunity. */
static VivDefAttr defence_attr = {{{0, 0, 0, 0, 0}}, {0, 0, 0}};

/** Vivian's status chances: 100 for every status (badges lower them in battle). */
static VivRegist regist = {{100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100}, {0, 0}};

/**
 * Vivian's pose table: animations for each status (stop, dizzy, poison, confusion, sleep, freeze, instant KO),
 * the hurt poses, gliding and fast gliding, low HP, the failed Run Away tumble, talking, item use,
 * the command menu wait, zero gravity, the Defend stance and plain floating.
 */
PoseTableEntry pose_table_vivian_stay[] = {
    {9, "PTR_D_4"},
    {2, "PTR_D_4"},
    {3, "PTR_X_1"},
    {4, "PTR_D_2"},
    {5, "PTR_X_1"},
    {1, "PTR_N_1"},
    {27, "PTR_D_3"},
    {BTL_POSE_NORMAL, "PTR_S_1"},
    {37, "PTR_G_2"},
    {31, "PTR_G_1"},
    {BTL_POSE_DAMAGE, "PTR_D_1"},
    {BTL_POSE_WALK, "PTR_W_1"},
    {BTL_POSE_RUN, "PTR_R_1"},
    {BTL_POSE_PERIL, "PTR_D_2"},
    {BTL_POSE_DANGER, "PTR_D_2"},
    {BTL_POSE_ESCAPE_FAIL, "PTR_D_4"},
    {BTL_POSE_ESCAPE_FAIL_END, "PTR_D_2"},
    {BTL_POSE_TALK, "PTR_T_1"},
    {BTL_POSE_ITEM_USE, "PTR_I_1"},
    {BTL_POSE_COMMAND_WAIT, "PTR_C_1"},
    {BTL_POSE_ZERO_GRAVITY, "PTR_X_1"},
    {49, "PTR_D_1"},
    {BTL_POSE_DEFEND, "PTR_G_1"},
    {BTL_POSE_STAY_DEFAULT, "PTR_S_1"},
};

/**
 * Vivian's data events: the Veil countdown each phase (tag 3), Appeal, the audience attack reaction, her move
 * list (tag 1, __makeTechMenuFunc), the counter-hit reaction for tags 25-35, First Strike (nothing), the
 * victory pose, an empty step run after a move's cost is paid (7) and the spin when she
 * superguards an attack (47).
 */
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

/** Vivian's single battle part: her targetable body (model c_vivian) with her pose table. */
BattleUnitKindPart unitpartsdata_Party_Vivian[] = {
    {1, "btl_un_vivian", "c_vivian", 0.0f, 0.0f, 0.0f, 16.0f, 24.0f, 5.0f, 0.0f, 24.0f, 0.0f, 20, 24, 255, &defence.d, &defence_attr.d, 0x9, 0, pose_table_vivian_stay},
};

/**
 * Vivian's battle unit (UNIT_VIVIAN), listed in battle_party.c's partner table:
 * a floating unit with one part, the partner hit sounds and no enemy HP gauge.
 */
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

/** Empty: partner moves come from the player's menu choices, not a unit attack script. */
static EVT_BEGIN(attack_event)
    RETURN
EVT_END()

/**
 * Vivian-style emergence from a shadow for part args[1] of unit args[0]:
 * grows the shadow, places the unit at (args[2], args[3], args[4]) and plays the p_bibi rise animation,
 * then shrinks the shadow back. args[5] non-zero also clears the shared-shadow flag. Blocks until done.
 */
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

/**
 * Vivian's battle entry: starts 250 units behind her home spot and, after 40 frames,
 * floats in to it at speed 4 with her hovering sound, then takes her stay pose.
 */
static EVT_BEGIN(battle_entry_event)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 250)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(40)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_SUBHANG1"), STRING("SFX_PARTY_BATTLE_SUBHANG1"), 0, 6, 6, 0, 0)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Init for Vivian: allocates her spare weapon, registers her wait, attack, damage, confusion and entry scripts,
 * clears the Veil turns (UW_VIVIAN_VEIL_TURNS) and UW_VIVIAN_AWAY,
 * spawns vivian_shadow_tail_event and sets her walk, run, dive and jump sounds.
 */
static EVT_BEGIN(init_event)
    CALL(_vivian_make_extra_work_area)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_VEIL_TURNS, 0)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_AWAY, 0)
    SPAWN_EVENT(vivian_shadow_tail_event)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 20, 20)
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_MOVE1L"), STRING("SFX_PARTY_BATTLE_MOVE1R"), 0, 11, 11)
    CALL(btlevtcmd_SetDiveSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_HANG1"), STRING("SFX_PARTY_BATTLE_HANG1"), 0, 11, 11)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_PARTY_BATTLE_JUMP1"), STRING("SFX_PARTY_BATTLE_LANDING1"))
    CALL(btlevtcmd_SetEventEntry, BTL_UNIT_SELF, PTR(battle_entry_event))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Hit reaction: straightens her rotation (left over from her moves), then runs the default damage script. */
static EVT_BEGIN(damage_event)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Veil's per-phase countdown (data tag 3): decrements the turns left in UW_VIVIAN_VEIL_TURNS and, when they run out,
 * Mario and Vivian rise out of the shadow (battle_evt_majo_disp_on) and walk back home,
 * with an optional stylish.
 */
EVT_BEGIN(vivian_hide_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_VEIL_TURNS, LW(0))
    IF_INT_GREATER_OR_EQUAL(LW(0), 1)
        SUBTRACT(LW(0), 1)
    END_IF
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_VEIL_TURNS, LW(0))
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

/** Idle: plays the stay pose from the current pose table. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Shade Fist (0 FP): a punch from the shadows on any single enemy; damage by rank 3, 4 or 5
 * (the same whether or not the action command succeeds); only a successful command burns it for 2 turns.
 * Cannot be guarded; usable while confused.
 */
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
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/**
 * Veil (1 FP): Vivian targets Mario and pulls him into the shadows with her so neither can be attacked
 * until they come out. No damage (the damage values here are unused).
 */
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
    ELEMENT_NORMAL, 0, // element..damagePattern
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

/**
 * Fiery Jinx (6 FP): fire on every enemy that pierces defence and burns for 3 turns (100% chance);
 * the damage is the action command result (weaponGetACOutputParam on output 0). Cannot be guarded.
 */
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
    ELEMENT_FIRE, // element
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

/**
 * Infatuate (4 FP): a kiss blown at every enemy that confuses for 3 turns (90% chance in the US demo,
 * 100% later), only where the action command succeeds. No damage; cannot be guarded.
 */
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
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    "msg_ac_meromero_kiss", // acHelpMsg
    SPECIAL_UNGUARDABLE, // special
    COUNTER_RESIST_ALL, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, // poisonStrength
#if VERSION <= VERSION_DEMO_US
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

/**
 * Vivian's Shade Fist: she sinks into the shadows,
 * reappears beside the enemy (_get_vivian_attack_position) and punches it with the action command,
 * the hit able to burn it for 2 turns (_make_kagenuke_weapon), then returns.
 */
EVT_BEGIN(partyVivianAttack_NormalAttack)
    // Pick the target, set up the burn and pay the cost; the camera follows Vivian and the enemy.
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
    // Action command (press the button shown on screen) starts as she sinks into her shadow.
    CALL(btlevtcmd_CommandGetWeaponActionLv, LW(0))
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AcSetParamAll, 1, 1, 40, 1, 2, 0, 3, 0)
    CALL(btlevtcmd_AcSetFlag, 23)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 18, 1, 0)
    CALL(evt_snd_sfxon, STRING("SFX_BTL_VIVIAN_ATTACK1"), 0)
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_StartAC, 1)
    // She glides under the stage to a spot beside the enemy and rises out of the floor there.
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
#if VERSION >= VERSION_JP
    CALL(_get_vivian_attack_position, LW(3), LW(0), LW(1), LW(2))
#else
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_TransStageFloorPosition, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SUBTRACT(LW(1), 20)
    IF_INT_LESS(LW(1), LW(7))
        SET_VALUE(LW(1), LW(7))
    END_IF
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
#endif
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 50, 0, 5, 0, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_AWAY, 1)
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_VIVIAN_ATTACK2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(battle_evt_majo_disp_on, BTL_UNIT_SELF, 1, LW(0), LW(1), LW(2), 0)
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    // She turns to face the enemy and glides in close if she is not there yet.
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(6), LW(7), LW(8))
#if VERSION >= VERSION_JP
    CALL(_get_vivian_attack_position, LW(3), LW(0), LW(1), LW(2))
    CALL(_get_vivian_attack_position, LW(3), LW(6), LW(7), LW(8))
    CALL(btlevtcmd_TransStageFloorPosition, LW(6), LW(7), LW(8))
#else
    CALL(btlevtcmd_TransStageFloorPosition, LW(6), LW(7), LW(8))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 30)
    SUBTRACT(LW(1), 20)
    IF_INT_LESS(LW(1), LW(7))
        SET_VALUE(LW(1), LW(7))
    END_IF
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
    // A pre-emptive spiky enemy hurts her first.
    LABEL(9)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
    IF_INT_EQUAL(LW(5), 5)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
    END_IF
    // Wait for the command result, then check whether the punch connects; a miss plays the enemy's dodge reaction.
    CALL(btlevtcmd_ResultAC)
    SET_VALUE(LW(10), 0)
    LABEL(10)
    IF_INT_GREATER_OR_EQUAL(LW(10), 1)
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_ALWAYS_HIT, LW(5))
    ELSE
        CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // The punch lands; a successful command also burns the enemy and adds the rating effect (Nice, Good...).
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_2"))
    CALL(btlevtcmd_ftomsec, 4, LW(0))
    WAIT_MS(LW(0))
    CALL(evt_snd_sfxon, STRING("SFX_BTL_VIVIAN_ATTACK4"), 0)
    CALL(btlevtcmd_GetResultAC, LW(0))
    IF_BITS_SET(LW(0), 2)
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
    ELSE
        CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), LW(12), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_NO_STATUS, LW(5))
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
    // She sinks back into the floor, glides home under the stage and rises again; pressing A as she rises is the
    // stylish.
    LABEL(90)
    CALL(btlevtcmd_StopAC)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_A1_1"))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, 0, 5, 0, -1)
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_AWAY, 0)
    CALL(battle_evt_majo_disp_off, BTL_UNIT_SELF, 1, 0, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, EVT_NULLPTR, LW(1), EVT_NULLPTR)
    CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 40, 0, 5, 0, -1)
    BEGIN_SIBLING_EVENT
#if VERSION >= VERSION_US
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 14, 29, 29, 0)
#else
        CALL(btlevtcmd_ACRStart, BTL_UNIT_SELF, 20, 29, 29, 0)
#endif
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
    // The audience refills Star Power and her turn ends.
    LABEL(99)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL_CHILD(btldefaultevt_SuitoruBadgeEffect)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Vivian's Veil: she pulls Mario down into the shadows with her, so both are veiled and cannot be targeted;
 * UW_VIVIAN_VEIL_TURNS is set to 1 so vivian_hide_event brings them back out next turn.
 */
EVT_BEGIN(partyVivianAttack_ShadowGuard)
    // Target Mario, pay the cost and focus the camera on Vivian as she floats over to him.
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
    // Action command (press the buttons in order as they appear); on a failure she floats back home and nothing
    // happens.
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
    // Success: the rating effect, then she opens her shadow and Mario sinks into it, veiled and untargetable.
#if VERSION <= VERSION_DEMO_US
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
#if VERSION >= VERSION_JP
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
    // Vivian follows him under with a ripple on the floor; she stays untargetable until vivian_hide_event brings
    // them back out.
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
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_VEIL_TURNS, 1)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    WAIT_FRAMES(1)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, -1, -1, 4, LW(0))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(0))
    WAIT_MS(500)
    // The audience refills Star Power and the camera returns.
    LABEL(90)
    CALL(evt_audience_ap_recovery)
    CALL(btlevtcmd_InviteApInfoReport)
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
#if VERSION >= VERSION_JP
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
#endif
    LABEL(99)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Vivian's Fiery Jinx: she casts fire over all the enemies,
 * with the action command deciding the damage and whether they are burned.
 */
EVT_BEGIN(partyVivianAttack_MagicalPowder)
    // Target every enemy and pay the cost.
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
    // Action command (press the buttons in order as they appear): less time at higher difficulty; the camera pulls
    // back on Vivian.
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
    // She casts the spell in a burst of stardust; pressing A at the right moment is the stylish.
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
    // The camera returns to the stage view.
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
#if VERSION >= VERSION_US
    CALL(evt_btl_camera_set_posoffset, 0, 0, 0, 0)
#endif
    WAIT_FRAMES(40)
    // Each enemy in turn: a puff of fire, then the enemy's dodge reaction on a miss, or the fire hit and burn with
    // its rating effect.
    SET_VALUE(LW(10), 0)
    LABEL(10)
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(evt_eff, 0, STRING("kemuri_test"), 6, LW(0), LW(1), LW(2), FLOAT(1.0f), 0, 0, 0, 0, 0, 0, 0)
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(6))
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
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(5))
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
    // Next enemy until all are done, then the Star Power refill and she returns to her stance.
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

/**
 * Vivian's Infatuate: she blows a kiss at all the enemies,
 * confusing those it takes hold on for 3 turns (90% chance in the US demo, 100% later);
 * a heart shows over the target during the action command (_disp_heart_entry).
 */
EVT_BEGIN(partyVivianAttack_CharmKissAttack)
    // Target every enemy and pay the cost.
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
    // For each enemy: she fidgets shyly while the action command waits a random time for the heart cue;
    // the press window shrinks at higher difficulty.
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
    // A heart appears over the enemy when the cue comes.
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
    // She blows the kiss; a miss plays the enemy's dodge reaction.
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
    CALL(btlevtcmd_CommandPreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT, LW(6))
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
    // The kiss lands: a successful press confuses the enemy, with a heart burst and the rating effect.
    IF_BITS_SET(LW(7), 2)
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_AC_SUCCESS, LW(5))
    ELSE
        CALL(btlevtcmd_CommandCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), DAMAGE_FLAG_LAST_HIT | DAMAGE_FLAG_NO_STATUS, LW(5))
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
    // Stylish: pressing A during her pose.
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
    // Next enemy until all are done, then the Star Power refill and she returns to her stance.
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

/**
 * Spawned by init_event, runs for the unit's lifetime:
 * each frame, while she is not away (UW_VIVIAN_AWAY is 0),
 * stores Vivian's floor position in UW_VIVIAN_SHADOW_X-Z so a counter-hit can return her there.
 */
EVT_BEGIN(vivian_shadow_tail_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_X, LW(0))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_Y, LW(1))
    CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_Z, LW(2))
    LABEL(0)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(5))
    IF_INT_EQUAL(LW(5), -1)
        RETURN
    END_IF
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_AWAY, LW(5))
    IF_INT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_X, LW(0))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_Y, LW(1))
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_Z, LW(2))
    END_IF
    WAIT_FRAMES(1)
    GOTO(0)
    RETURN
EVT_END()

/**
 * Counter-damage reaction (data tags 25-35): Vivian is knocked up and back;
 * if she was out of her shadow (UW_VIVIAN_AWAY set) she dives back to the saved floor spot,
 * sinks into the shadow and resurfaces at home.
 */
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
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_AWAY, LW(5))
    IF_INT_NOT_EQUAL(LW(5), 0)
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_X, LW(0))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_Y, LW(1))
        CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_SHADOW_Z, LW(2))
        CALL(btlevtcmd_TransStageFloorPosition, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, 0, 5, 0, -1)
        CALL(btlevtcmd_SetUnitWork, BTL_UNIT_SELF, UW_VIVIAN_AWAY, 0)
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

/** Vivian's Appeal (data tag 5): appeal pose and sound, then the audience is fired up. */
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

/** Victory reaction (data tag 64): plays Vivian's PTR_Y_1 pose to the end, holds half a second, then her stay pose. */
static EVT_BEGIN(party_win_reaction)
    CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("PTR_Y_1"))
    CALL(btlevtcmd_AnimeWaitPlayComplete, BTL_UNIT_SELF, 1)
    WAIT_MS(500)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    RETURN
EVT_END()

/**
 * Audience-attack reaction (data tag 6): Vivian runs offstage, reappears in the audience,
 * hits the chosen audience member with her Shade Fist pose (PTR_A1_2) and runs home.
 */
static EVT_BEGIN(attack_audience_event)
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetStageSize, LW(3), EVT_NULLPTR, EVT_NULLPTR)
    CALL(btlevtcmd_GetFaceDirection, BTL_UNIT_SELF, LW(4))
    SET_VALUE(LW(8), LW(3))
    MULTIPLY(LW(8), LW(4))
    MULTIPLY(LW(8), -1)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(6.0f))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
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
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(6), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_SetPos, BTL_UNIT_SELF, LW(8), LW(1), LW(2))
    CALL(btlevtcmd_WaitEventEnd, LW(15))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Sinks part args[1] of unit args[0] into its shadow:
 * grows the shadow, plays the p_bibi sink animation and sound,
 * then shrinks the shadow away and drops the unit 500 units below the stage.
 * args[2] non-zero sets the shared-shadow flag; args[3] non-zero hides the part. Blocks until done.
 */
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

/**
 * Allocates a spare BattleWeapon in the running unit's countersetWeapon slot,
 * which Shade Fist fills per use (_make_kagenuke_weapon). Run from init_event.
 */
static USER_FUNC(_vivian_make_extra_work_area) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    unit->countersetWeapon = BattleAlloc(sizeof(BattleWeapon));
    return EVT_RETURN_DONE;
}

/**
 * Builds Vivian's battle move list (data tag 1):
 * Shade Fist and Veil always, Fiery Jinx from Super rank and Infatuate from Ultra rank,
 * appending each to command->weapon and advancing *count.
 */
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

/**
 * Returns in args[7] how many frames moving from point args[0..2] to args[3..5] takes at speed args[6],
 * capped at 15.
 */
static USER_FUNC(_get_move_frame) {
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

#if VERSION >= VERSION_JP

/**
 * Takes target unit args[0] and a position in args[1]-args[3]
 * and adjusts it in place to where Vivian should surface for Shade Fist:
 * 30 units behind her facing, plus the target's vivianOffsetX/Z, 20 units lower but not below the floor.
 * Not in the US demo.
 */
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

/**
 * Copies the weapon pointed to by args[0] into the unit's spare weapon,
 * sets its burn duration (burnTime) to args[1] turns, and writes the copy's address back into args[0].
 * Shade Fist always passes 2.
 */
static USER_FUNC(_make_kagenuke_weapon) {
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

/**
 * Shows Infatuate's heart over part args[4] of unit args[3] for args[2] frames,
 * popping in by frame args[0] and settling by frame args[1] (state kept in event->heart).
 * Ends early once _disp_heart_entry_stop is called.
 */
static USER_FUNC(_disp_heart_entry) {
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

/**
 * Display callback for _disp_heart_entry: draws the heart icons at the target's hit position,
 * scaled through the pop-in animation.
 */
static void _disp_heart(CameraId camera, void* param) {
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

/** Stops the heart display of the event whose id is args[0] (sets its heart.stop). */
static USER_FUNC(_disp_heart_entry_stop) {
    EventEntry* e = evtGetPtrID(evtGetValue(event, *event->args));
    e->heart.stop = 1;
    return EVT_RETURN_DONE;
}

/** Returns in args[0] whether the running event's heart display has been stopped. */
static USER_FUNC(_disp_heart_entry_stop_check) {
    evtSetValue(event, *event->args, event->heart.stop);
    return EVT_RETURN_DONE;
}
