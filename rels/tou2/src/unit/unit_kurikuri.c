// unit_kurikuri: Goomba Bros. (`kurikuri`), the Goomba pair of a Glitz Pit match (with Koopa messages), battle unit.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "system.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_default.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_weapon_power.h"
#include "battle/battle_database_common.h"
#include "battle/battle_sub.h"
#include "evt/evt_msg.h"
#include "evt/evt_story.h"

// Unit work slots of the Glitz Pit Goomba (btlevtcmd_GetUnitWork).
enum {
    UW_KURIKURI_INTRO_LEADER = 0, // non-zero on the Goomba that plays the turn-1 intro (set by the battle setup)
};

static USER_FUNC(krb_get_dir);

BattleUnitKind unit_kurikuri;
static BattleDataEntry data_table[2];
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static StatusVulnerability regist;
static BattleUnitKindPart parts[1];
static BattleWeapon weapon_kuriboo_attack;
static EvtWord init_event[46];
static EvtWord damage_event[10];
static EvtWord phase_event[122];
static EvtWord attack_event[492];
static EvtWord wait_event[6];

/**
 * Unit data of the Goomba Bros.: hit points, level, size, sounds, parts, status vulnerability, init event
 * and event data table.
 */
BattleUnitKind unit_kurikuri = {
    36,
#if VERSION <= VERSION_DEMO_JP
    "btl_un_kurikuri",
#else
    "btl_un_kuriboo",
#endif
    2,
    0,
    1,
    1,
    7,
    0,
    0,
    70,
    0,
    50,
    9999,
    23,
    25,
    5,
    25,
    0.0f,
    12.0f,
    0.0f,
    0,
    0,
    0.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    -10.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    0.0f,
    11.5f,
    0.0f,
    0.0f,
    12.0f,
    18.0f,
    0.0f,
    0.0f,
    12.0f,
    0.0f,
    23.0f,
    25.0f,
    0,
    0,
    0,
    2,
    100,
    20,
    0.0f,
    0.0f,
    0.0f,
    "SFX_ENM_KURI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    UNIT_ATTR_REQUIRED_FOR_CLEAR,
    &regist,
    1,
    parts,
    init_event,
    data_table,
};

/**
 * Pose table of the Goomba Bros.: maps each battle pose (idle, hurt, attacking and so on) to its
 * animation, named KUR_*.
 */
static PoseTableEntry pose_table[] = {
    {1, "KUR_N_1"},
    {2, "KUR_Y_1"},
    {9, "KUR_Y_1"},
    {5, "KUR_K_1"},
    {4, "KUR_I_1"},
    {3, "KUR_I_1"},
    {BTL_POSE_NORMAL, "KUR_S_1"},
    {29, "KUR_Q_1"},
    {30, "KUR_Q_1"},
    {31, "KUR_S_1"},
    {BTL_POSE_DAMAGE, "KUR_D_1"},
    {50, "KUR_A_1"},
    {51, "KUR_A_2"},
    {BTL_POSE_RUN, "KUR_R_1"},
    {41, "KUR_R_2"},
    {BTL_POSE_WALK, "KUR_W_1"},
    {BTL_POSE_DANGER, "KUR_I_1"},
    {BTL_POSE_PERIL, "KUR_I_1"},
    {BTL_POSE_TALK, "KUR_T_1"},
    {BTL_POSE_STAY_DEFAULT, "KUR_S_1"},
};

/**
 * Event data table of the Goomba Bros.: no custom reactions, so the standard battle handlers run for every
 * event.
 */
static BattleDataEntry data_table[] = {
    {48, btldefaultevt_Dummy},
    {0, NULL},
};

/**
 * Defense of the Goomba Bros. against normal, fire, ice, explosion and electric attacks: none, so it takes
 * full damage from every element.
 */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Damage-type reactions of the Goomba Bros.: none, so every element hurts it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

#if VERSION <= VERSION_DEMO_JP
/**
 * Status vulnerability of the Goomba Bros. (both early demos), as the percent chance each status takes hold:
 * extra vulnerable to stop, Fright, Gale Force and instant KO.
 */
static StatusVulnerability regist = {100, 120, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 120, 120, 100, 100, 100, 100, 150};
#else
/**
 * Status vulnerability of the Goomba Bros. (the retail releases), as the percent chance each status takes
 * hold: extra vulnerable to stop, Fright and instant KO.
 */
static StatusVulnerability regist = {100, 110, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 100, 110, 100, 100, 100, 100, 100, 150};
#endif

/**
 * Parts of the Goomba Bros.: a single body part (part 1, model c_kuribo), each with its defense tables,
 * attributes and pose table.
 */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_kuriboo", "c_kuribo", 0.0f, 0.0f, 0.0f, 0.0f, 22.0f, 0.0f, 0.0f, 30.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, PART_ATTR_MAIN | PART_ATTR_GUARD_COVER, 0, pose_table},
};

/** Weapon record of the Goomba Bros.' leaping attack: 1 damage and counts as a jump-type hit. */
static BattleWeapon weapon_kuriboo_attack = {
    NULL, 0, // name..icon
    {0}, // pad_06
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, // baseFpCost..baseSpCost
    1, // superguardsAllowed
    1.0f, // reserved_14
    1, // stylishCommandMultiplier
    1, // reserved_19
    1, // bingoSlotChance
    1, // reserved_1B
    weaponGetPowerDefault, // hpDamageFn
    {1, 0, 0, 0, 0, 0, 0, 0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    TARGET_CLASS_NO_TREE_OR_SWITCH | TARGET_CLASS_NO_SYSTEM_UNIT | TARGET_CLASS_NO_OWN_ALLIANCE | TARGET_CLASS_NO_SELF | TARGET_CLASS_MAIN_PARTS | TARGET_CLASS_SINGLE, // targetClassFlags
    TARGET_PROP_JUMPLIKE | TARGET_PROP_START_OPPOSING_SIDE, // targetPropertyFlags
    ELEMENT_NORMAL, 0, // element..damagePattern
    3, // acLevel
    2, // reserved_6F
    NULL, // acHelpMsg
    SPECIAL_BADGE_BUFFABLE | SPECIAL_STATUS_BUFFABLE | SPECIAL_CHARGE_BUFFABLE | SPECIAL_SHATTERS_FREEZE | SPECIAL_FLIPS_SHELLED | SPECIAL_GROUNDS_WINGED, // special
    0, // counterResistFlags
    TARGET_WEIGHT_PREFER_FRONT | TARGET_WEIGHT_UNUSED_2000 | TARGET_WEIGHT_RANDOM, // targetWeightFlags
    0, 0, 0, 0, 0, 0, 0, 0, // sleepChance..poisonTime
    0, 0, 0, 0, 0, 0, 0, 0, // poisonStrength..burnChance
    0, 0, 0, 0, 0, 0, 0, 0, // burnTime..atkChangeTime
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeStrength..chargeStrength
    0, 0, 0, 0, 0, 0, 0, 0, // fastChance..holdFastTime
    0, 0, 0, 0, 0, 0, // invisibleChance..fpRegenStrength
    {0}, // pad_AE
    NULL, // attackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // stageEffectRates
};

/**
 * Init script of the Goomba: registers its wait, phase, attack, damage and confusion handlers,
 * sets the walk/run/jump sounds (SFX_ENM_KURI_*) and starts the idle event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventPhase, BTL_UNIT_SELF, PTR(phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetRunSound, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetWalkSound, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 6, 6)
    CALL(btlevtcmd_SetJumpSound, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_JUMP1"), STRING("SFX_ENM_KURI_LANDING1"))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage reaction: runs the default damage handling (btldefaultevt_Damage) with LW(10) = -2 (the unit itself)
 * and LW(11) = 1.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/**
 * Intro of the Goomba pair in the Glitz Pit (runs once, on turn 1, for the unit with work 0 set,
 * while GSWF_TOU_GOOMBA_BROS_FIRST_STRIKE_SEEN is clear):
 * pans the camera, has the partner complain about the attack before the bell (Goombella stg3_tou_83_kur,
 * Koops stg3_tou_83_nok, Flurrie stg3_tou_83_win, by unit kind 224, 225, 227) and the Goomba answer that it was
 * a welcome gift for the rookie (stg3_tou_84), then sets the flag.
 */
static EVT_BEGIN(phase_event)
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_KURIKURI_INTRO_LEADER, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        IF_INT_EQUAL(GSWF(GSWF_TOU_GOOMBA_BROS_FIRST_STRIKE_SEEN), 0)
            CALL(btlevtcmd_CheckPhase, LW(0), BATTLE_PHASE_BEFORE_PLAYER)
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_get_turn, LW(0))
                IF_INT_EQUAL(LW(0), 1)
                    CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_PARTNER)
                    CALL(btlevtcmd_PhaseEventStartDeclare, BTL_UNIT_SELF)
                    SET_VALUE(GSWF(GSWF_TOU_GOOMBA_BROS_FIRST_STRIKE_SEEN), 1)
                    CALL(evt_btl_camera_set_prilimit, 1)
                    CALL(evt_btl_camera_set_mode, 1, 3)
                    CALL(evt_btl_camera_set_moveto, 1, -104, 74, 334, -102, 52, 0, 30, 4)
                    WAIT_FRAMES(30)
                    CALL(btlevtcmd_GetUnitKind, BTL_UNIT_PARTNER, LW(0))
                    SWITCH(LW(0))
                        CASE_EQUAL(UNIT_GOOMBELLA)
                        CALL(evt_msg_print, 2, STRING("stg3_tou_83_kur"), 0, BTL_UNIT_PARTNER)
                        CASE_EQUAL(UNIT_KOOPS)
                        CALL(evt_msg_print, 2, STRING("stg3_tou_83_nok"), 0, BTL_UNIT_PARTNER)
                        CASE_EQUAL(UNIT_FLURRIE)
                        CALL(evt_msg_print, 2, STRING("stg3_tou_83_win"), 0, BTL_UNIT_PARTNER)
                    END_SWITCH
                    CALL(evt_btl_camera_set_moveto, 1, 91, 74, 334, 91, 52, 0, 30, 4)
                    WAIT_FRAMES(30)
                    CALL(evt_msg_print, 2, STRING("stg3_tou_84"), 0, BTL_UNIT_SELF)
                    CALL(evt_btl_camera_set_prilimit, 0)
                    CALL(evt_btl_camera_set_mode, 0, 0)
                    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_PARTNER)
                    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
                END_IF
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * The Goomba's headbonk (weapon_kuriboo_attack): picks a target (or uses an item), walks up to it and jumps onto
 * it with its body tilted along the arc (krb_get_dir).
 * A miss carries the jump on past the target and it lands with two hops; a hit plays SFX_ENM_KURI_ATTACK1,
 * applies the damage and bounces it back in three hops.
 * It then walks home.
 */
static EVT_BEGIN(attack_event)
    // In a first strike it waits, then uses the target of that strike; otherwise it chooses a target.
    CALL(btlevtcmd_check_battleflag, LW(0), 2)
    IF_INT_NOT_EQUAL(LW(0), 0)
        WAIT_MS(750)
        CALL(btlevtcmd_GetFirstAttackTarget, LW(3), LW(4))
    ELSE
        CALL(btlevtcmd_GetEnemyBelong, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_SamplingEnemy, BTL_UNIT_SELF, LW(0), PTR(&weapon_kuriboo_attack))
        CALL(btlevtcmd_ChoiceSamplingEnemy, PTR(&weapon_kuriboo_attack), LW(3), LW(4))
    END_IF
    IF_INT_EQUAL(LW(3), -1)
        CALL(btlevtcmd_CheckToken, BTL_UNIT_SELF, TOKEN_FLAG_CONFUSED_ACTION, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL_CHILD(subsetevt_confuse_flustered)
            RETURN
        END_IF
        GOTO(99)
    END_IF
    // A Goomba Bros. uses an enemy item if one fits.
    CALL(btlevtcmd_EnemyItemUseCheck, BTL_UNIT_SELF, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(LW(0))
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        RETURN
    END_IF
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.5996094f))
    CALL(evt_btl_camera_set_mode, 0, 8)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, LW(3))
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 250)
    CALL(btlevtcmd_WeaponAftereffect, PTR(&weapon_kuriboo_attack))
    // The attack is announced.
    CALL(btlevtcmd_AttackDeclare, BTL_UNIT_SELF, LW(3), LW(4))
    CALL(btlevtcmd_WaitGuardMove)
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, PTR(&weapon_kuriboo_attack))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_RUN)
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, LW(3), LW(0), 100)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(0), LW(2), 1, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(4.0f))
    // It walks around behind its target, then turns back to face it and pauses.
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), 0, LW(2), 0, -1, 1)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, BTL_POSE_STAY)
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, -1, LW(3), LW(4), 16, LW(15))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(15))
    WAIT_MS(170)
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_nomove_y_onoff, 0, 1)
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPosFloat, BTL_UNIT_SELF, LW(5), LW(6), LW(7))
        SET_VALUE(LW(8), 0)
        // It leaps at the target, spinning in the air as it goes.
        LOOP(32)
            CALL(btlevtcmd_GetPosFloat, BTL_UNIT_SELF, LW(9), LW(10), LW(11))
            CALL(krb_get_dir, LW(5), LW(6), LW(9), LW(10), LW(8))
            CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, LW(8))
            SET_FLOAT_VALUE(LW(5), LW(9))
            SET_FLOAT_VALUE(LW(6), LW(10))
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        LOOP(12)
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LW(15), 50)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, LW(15))
    END_INLINE_EVENT
    CALL(btlevtcmd_GetHitPos, LW(3), LW(4), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 32, -1)
    // Find out how the target reacts to the leap.
    CALL(btlevtcmd_PreCheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_kuriboo_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    SWITCH(LW(5))
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
        GOTO(91)
        CASE_END
    END_SWITCH
    // The leap missed: it lands past the target and hops on in two small steps.
    LABEL(90)
    CALL(btlevtcmd_JumpContinue, BTL_UNIT_SELF)
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(15), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MoveDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 20, -1)
    CALL(btlevtcmd_MoveDirectionAdd, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 10, -1)
    WAIT_MS(500)
    GOTO(95)
    // The leap connects: the damage is applied and it bounces back in three shrinking hops.
    LABEL(91)
    CALL(evt_btl_camera_shake_h, 0, 1, 1, 8, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(evt_btl_camera_add_zoom, 0, -50)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_ATTACK1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_ResultACDefence, LW(3), PTR(&weapon_kuriboo_attack))
    CALL(btlevtcmd_CheckDamage, BTL_UNIT_SELF, LW(3), LW(4), PTR(&weapon_kuriboo_attack), DAMAGE_FLAG_LAST_HIT, LW(5))
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    SET_VALUE(LW(15), BTL_POSE_STAY_DEFAULT)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, LW(15))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    SET_VALUE(LW(1), 0)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 40)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 30, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 20)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 12, -1)
    CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 10)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 6, -1)
    GOTO(95)
    // It walks back to its home position.
    LABEL(95)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(btlevtcmd_SetMoveSoundDataWork, BTL_UNIT_SELF, STRING("SFX_ENM_KURI_MOVE1"), STRING("SFX_ENM_KURI_MOVE2"), 0, 3, 3, 0, 0)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, 1, 41)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(5.0f))
    CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -2, 0)
    LABEL(99)
    CALL(btlevtcmd_ResetFaceDirection, BTL_UNIT_SELF)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Idle event: sets the unit's body part 1 to the pose given by its pose table for its current state. */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    RETURN
EVT_END()

/**
 * Script helper: arg0/arg1 = x/y of the previous position, arg2/arg3 = x/y of the current one;
 * arg4 receives the angle (degrees) of the step between them, or keeps its incoming value when the points
 * coincide.
 * The headbonk uses it each frame as the Goomba's z rotation, so it leans along its jump arc.
 */
static USER_FUNC(krb_get_dir) {
    EvtWord* args = event->args;
    f32 x1 = evtGetFloat(event, args[0]);
    f32 z1 = evtGetFloat(event, args[1]);
    f32 x2 = evtGetFloat(event, args[2]);
    f32 z2 = evtGetFloat(event, args[3]);
    s32 dir = evtGetValue(event, args[4]);
    f32 dx = x2 - x1;
    f32 dz = z2 - z1;

    if (dx == 0.0f && dz == 0.0f) {
        evtSetValue(event, args[4], dir);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[4], angleABf(dx, dz, 0.0f, 0.0f));
    return EVT_RETURN_DONE;
}
