// Default battle events: standard guard, escape, damage and badge-effect scripts shared by all units.
#include "eff/eff_fire.h"
#include "battle/battle_event_default.h"
#include "battle/battle.h"
#include "battle/battle_ac_help.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "driver/effdrv.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_seq_end.h"
#include "battle/battle_mario.h"
#include "battle/battle_event_subset.h"
#include "battle/battle_event_cmd.h"
#include "battle/battle_camera.h"
#include "evt/evt_batstage.h"
#include "evt/evt_sub.h"
#include "battle/battle_message.h"
#include "evt/evt_audience.h"
#include "evt/evt_eff.h"
#include "evt/evt_snd.h"

#include "battle/battle_damage.h"
#include "version.h"
// FAKE: battle_event_default.c calls BattlePartyAnimeLoad through this prototype (the types it was compiled with) instead of the one in battle/battle.h; same registers, behaviour-identical.
typedef BOOL (*BattlePartyAnimeLoadRetBoolFn)(s32);

static USER_FUNC(_anime_load);
static USER_FUNC(_anime_load_wait);
static USER_FUNC(_backfire);
static USER_FUNC(_btl_escape_reset_move_color_lv_player_unit_all);
static USER_FUNC(_check_pose_stay);
static USER_FUNC(_get_escape_rate);
static USER_FUNC(_get_flower_suitoru_point);
static USER_FUNC(_get_heart_suitoru_point);
static USER_FUNC(_set_escape_ac_hlp_msg);
// Audience reaction when Mario starts to run away (defined below).
USER_FUNC(btlevtcmd_audience_code_escape);
// Audience reaction to a failed escape (defined below).
USER_FUNC(btlevtcmd_audience_code_escape_fail);
// Audience reaction to a successful escape (defined below).
USER_FUNC(btlevtcmd_audience_code_escape_success);

extern EvtWord btldefaultevt_guard_move[];
extern EvtWord btldefaultevt_guard_return[];
extern EvtWord _Defence_core[];

/**
 * Standard damage reaction that unit damage scripts call with LW(10) = unit and LW(11) = part:
 * plays the reaction for the damage pattern and damage code (hurt pose, Gale Force and Fright blow-away, slaps,
 * counters, guards, lucky and dodged misses, using the unit's data-table events where it has them), then the KO,
 * the backfire (damage code bit 0x4000) or the guard return,
 * and finally walks or floats the unit back to its home position and restarts its wait event.
 */
EVT_BEGIN(btldefaultevt_Damage)
    // The unit is set upright; a frozen unit that shatters loses its freeze and bursts into ice
    // (the shatter chance is 0, so this never happens).
    CALL(btlevtcmd_SetRotate, LW(10), 0, 0, 0)
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_SHATTER, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_OnOffStatus, LW(10), STATUS_FREEZE, 0, 0, 0)
        CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
        CALL(evt_eff64, STRING(""), STRING("freeze_n64"), 0, LW(0), LW(1), LW(2), FLOAT(1.0f), 1, 0, 0, 0, 0, 0, 0)
    END_IF
    // Damage pattern 2 (Yoshi's Gulp, Flurrie's Lip Lock, the Quake Hammer moves):
    // the unit freezes in its hurt pose for good, and the attacker's script takes it from here.
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 2, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 39)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
        END_SIBLING_EVENT
        LABEL(0)
        WAIT_FRAMES(1)
        GOTO(0)
    END_IF
    // Damage pattern 3 (Flurrie's Gale Force on a unit it can blow away):
    // the unit trembles in its hurt pose until the attack ends.
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 3, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 39)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
        END_SIBLING_EVENT
        LABEL(1)
        CALL(btlevtcmd_SetDispOffset, LW(10), 2, 0, 0)
        WAIT_FRAMES(2)
        CALL(btlevtcmd_SetDispOffset, LW(10), 0, 0, 0)
        WAIT_FRAMES(2)
        CALL(btlevtcmd_WaitAttackEndCheck, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            GOTO(1)
        END_IF
    END_IF
    // Damage pattern 20 (Ms. Mowz's Kiss Thief): the unit holds pose 5 until the attack ends.
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 20, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 5)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
        END_SIBLING_EVENT
        CALL(btlevtcmd_WaitAttackEnd)
        GOTO(10)
    END_IF
    // Yoshi's Gulp hitting the unit's body (damage pattern 7) runs its data-table event 54 if it has one.
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 7, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 54)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 54)
        END_IF
    END_IF
    // The Ultra Hammer's acrobatic hit (damage pattern 18) plays its own spin reaction.
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 18, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL_CHILD(subset_ultra_hammer_acrobat_damage_event)
        GOTO(10)
    END_IF
    // A guarded hit: the unit holds its guard pose for half a second.
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_GUARDED, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 31)
        WAIT_FRAMES(30)
        GOTO(10)
    END_IF
    // Attacks stopped before they land: codes 31-37 (the attack bounced off this unit's spikes or flames)
    // run data-table events 37-43, and a Superguard (42) runs event 47.
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(31)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 37)
        GOTO(10)
        CASE_EQUAL(32)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 38)
        GOTO(10)
        CASE_EQUAL(33)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 39)
        GOTO(10)
        CASE_EQUAL(34)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 40)
        GOTO(10)
        CASE_EQUAL(35)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 41)
        GOTO(10)
        CASE_EQUAL(36)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 42)
        GOTO(10)
        CASE_EQUAL(37)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 43)
        GOTO(10)
        CASE_EQUAL(42)
        CALL(btlevtcmd_RunDataEventChild, LW(10), 47)
        GOTO(10)
        CASE_EQUAL(38)
        // Lucky (code 38): the unit's own lucky event, else the lucky jingle.
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 45)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 45)
        ELSE
            CALL(evt_snd_sfxon, STRING("SFX_SYSTEM_LUCKY1"), 0)
        END_IF
        GOTO(10)
        CASE_EQUAL(39)
        // Miss (code 39): the unit's own miss event, else a miss sound and the paper-dodge animation.
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 44)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 44)
        ELSE
            CALL(btlevtcmd_CheckCommandUnit, LW(10), LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(evt_snd_sfxon, STRING("SFX_MARIO_AVOID1"), 0)
            ELSE
                CALL(evt_snd_sfxon, STRING("SFX_BTL_ATTACK_MISS1"), 0)
            END_IF
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 48)
            CALL(btlevtcmd_AnimeChangePaperGroup, LW(10), LW(11), STRING("p_b_st"), 1)
            CALL(btlevtcmd_CheckStatus, LW(10), STATUS_DEFENSE_DOWN, LW(2))
            IF_INT_NOT_EQUAL(LW(2), 0)
                CALL(btlevtcmd_AnimeChangePaperAnime, LW(10), LW(11), STRING("PM_F_3A"))
                CALL(btlevtcmd_ftomsec, 37, LW(0))
                WAIT_MS(LW(0))
                CALL(btlevtcmd_AnimeChangePaperAnime, LW(10), LW(11), STRING("PM_F_3B"))
                CALL(btlevtcmd_ftomsec, 22, LW(0))
                WAIT_MS(LW(0))
            ELSE
                CALL(btlevtcmd_CheckStatus, LW(10), STATUS_DEFENSE_UP, LW(2))
                IF_INT_NOT_EQUAL(LW(2), 0)
                    CALL(btlevtcmd_AnimeChangePaperAnime, LW(10), LW(11), STRING("PM_Y_2A"))
                    CALL(btlevtcmd_ftomsec, 40, LW(0))
                    WAIT_MS(LW(0))
                    CALL(btlevtcmd_AnimeChangePaperAnime, LW(10), LW(11), STRING("PM_Y_2B"))
                    CALL(btlevtcmd_ftomsec, 65, LW(0))
                    WAIT_MS(LW(0))
                ELSE
                    CALL(btlevtcmd_AnimeChangePaperAnime, LW(10), LW(11), STRING("PM_Y_2A"))
                    CALL(btlevtcmd_ftomsec, 40, LW(0))
                    WAIT_MS(LW(0))
                    CALL(btlevtcmd_AnimeChangePaperAnime, LW(10), LW(11), STRING("PM_Y_2B"))
                    CALL(btlevtcmd_ftomsec, 65, LW(0))
                    WAIT_MS(LW(0))
                END_IF
            END_IF
        END_IF
        GOTO(10)
        CASE_EQUAL(40)
        // Dodge (code 40): the unit's data-table dodge event 46.
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 46)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 46)
        ELSE
        END_IF
    END_SWITCH
    // Ms. Mowz's Love Slap (damage patterns 21 and 22) plays the slap from the left or the right.
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 21, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 39)
        CALL_CHILD(subsetevt_binta_damage_left)
        CALL(btlevtcmd_WaitAttackEnd)
        RETURN
    END_IF
    CALL(btlevtcmd_CheckDamagePattern, LW(10), 22, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        SET_VALUE(LW(14), 39)
        CALL_CHILD(subsetevt_binta_damage_right)
        CALL(btlevtcmd_WaitAttackEnd)
        RETURN
    END_IF
    // The main reaction, chosen by the hit type.
    CALL(btlevtcmd_GetDamageCode, LW(10), LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(57)
        // The battle opened with Mario's or the partner's First Strike on this unit: data-table event 48.
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 48)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 48)
        END_IF
        CALL(btlevtcmd_StartWaitEvent, LW(10))
        RETURN
        CASE_OR_EQUAL(30)
        CASE_OR_EQUAL(27)
        CASE_OR_EQUAL(26)
        CASE_OR_EQUAL(23)
        // Normal, ice, electric and no-damage hits: the HP gauge shows and the hurt reaction plays
        // (hurt pose 38 for damage pattern 1).
        CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_SHOW_HP_GAUGE)
        SET_VALUE(LW(14), 39)
        SET_VALUE(LW(15), -1)
        CALL(btlevtcmd_CheckDamagePattern, LW(10), 1, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(14), 38)
        END_IF
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
        END_SIBLING_EVENT
        CALL_CHILD(subsetevt_damage)
        CASE_END
        CASE_EQUAL(22)
        // A hit that only inflicted a status: the unit shows pose 35 for 45 frames if it has one.
        CALL(btlevtcmd_CheckDefinePosetype, LW(10), LW(11), 35, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            SET_VALUE(LW(14), 35)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            BEGIN_SIBLING_EVENT
                CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
            END_SIBLING_EVENT
            WAIT_FRAMES(45)
        ELSE
            WAIT_FRAMES(45)
        END_IF
        CASE_EQUAL(24)
        // Fire and explosion hits: the unit's data-table events 11 and 12,
        // else the normal hurt reaction with pose 29.
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 11)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 11)
        ELSE
            CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_SHOW_HP_GAUGE)
            SET_VALUE(LW(14), 29)
            SET_VALUE(LW(15), -1)
            BEGIN_SIBLING_EVENT
                CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
            END_SIBLING_EVENT
            CALL_CHILD(subsetevt_damage)
        END_IF
        CASE_EQUAL(25)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 12)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 12)
        ELSE
            CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_SHOW_HP_GAUGE)
            SET_VALUE(LW(14), 29)
            SET_VALUE(LW(15), -1)
            BEGIN_SIBLING_EVENT
                CALL(btlevtcmd_RunDataEventChild, LW(10), 10)
            END_SIBLING_EVENT
            CALL_CHILD(subsetevt_damage)
        END_IF
        CASE_EQUAL(43)
        // This unit is an attacker hurt by its target's counter (codes 43-55: spikes, fire, ice, electricity,
        // explosions, poison, Payback, Hold Fast): data-table events 24-36, else the standard counter reaction.
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 24)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 24)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(44)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 25)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 25)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(45)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 26)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 26)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(46)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 27)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 27)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(47)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 28)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 28)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(48)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 29)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 29)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(49)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 30)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 30)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(50)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 31)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 31)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(51)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 32)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 32)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(52)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 33)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 33)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(53)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 34)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 34)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(54)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 35)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 35)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(55)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 36)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 36)
        ELSE
            CALL_CHILD(subsetevt_counter_damage)
        END_IF
        CASE_EQUAL(41)
        // The unit steps back from the attack (code 41).
        CALL_CHILD(btldefaultevt_avoid_guard)
        RETURN
        CASE_EQUAL(56)
        // The unit moves in front of the one it protects (code 56), then goes on to the KO checks below.
        CALL_CHILD(btldefaultevt_guard_move)
        CASE_EQUAL(28)
        // Fright (code 28) scares the unit off; Gale Force (code 29) blows it away
        // with its data-table event 58 or the standard one.
        CALL_CHILD(subsetevt_terror)
        RETURN
        CASE_EQUAL(29)
        CALL(btlevtcmd_CheckDataOfDataTable, LW(10), LW(2), 58)
        IF_INT_NOT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 58)
        ELSE
            CALL_CHILD(subsetevt_blow_dead)
        END_IF
        RETURN
        CASE_DEFAULT
    END_SWITCH
    LABEL(10)
    // After the reaction: a defeated unit plays its KO;
    // a unit at 0 HP that is not out (like a Dull Bones pile) runs its own event 15.
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_DEFEATED, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        WAIT_FRAMES(30)
        CALL_CHILD(subsetevt_dead)
        RETURN
    ELSE
        CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_KO, LW(1))
        IF_INT_NOT_EQUAL(LW(1), 0)
            CALL(btlevtcmd_RunDataEventChild, LW(10), 15)
            RETURN
        END_IF
    END_IF
    // A backfiring move, or a unit that used Defend, finishes with its own event.
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_BACKFIRE, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL(_backfire, LW(10))
        RETURN
    END_IF
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_GUARDING, LW(1))
    IF_INT_NOT_EQUAL(LW(1), 0)
        CALL_CHILD(btldefaultevt_guard_return)
        RETURN
    END_IF
    // Unless this was the move's last hit, the unit waits for the whole attack to end.
    CALL(btlevtcmd_CheckDamageCode, LW(10), DAMAGE_FLAG_LAST_HIT, LW(1))
    IF_INT_EQUAL(LW(1), 0)
        CALL(btlevtcmd_WaitAttackEnd)
    END_IF
    LABEL(99)
    // A floating unit flies back to its home position if the hit moved it.
    CALL(btlevtcmd_CheckAttribute, LW(10), UNIT_ATTR_FLOATING, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_GetPos, LW(10), LW(5), LW(6), LW(7))
        CALL(btlevtcmd_GetHomePos, LW(10), LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(2), LW(5))
            IF_INT_EQUAL(LW(3), LW(6))
                IF_INT_EQUAL(LW(4), LW(7))
                    GOTO(101)
                END_IF
            END_IF
        END_IF
        SET_VALUE(LW(14), 42)
        CALL(btlevtcmd_SetMoveSpeed, LW(10), FLOAT(4.0f))
        CALL(btlevtcmd_GetHomePos, LW(10), LW(2), LW(3), LW(4))
        CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, LW(7))
        IF_INT_GREATER(LW(7), 0)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            CALL(btlevtcmd_DivePosition, LW(10), LW(2), LW(3), LW(4), 0, 0, 0, 0, -1)
        END_IF
        LABEL(101)
    ELSE
        // A ground unit walks back to its home position if the hit moved it.
        CALL(btlevtcmd_GetPos, LW(10), LW(5), LW(6), LW(7))
        CALL(btlevtcmd_GetHomePos, LW(10), LW(2), LW(3), LW(4))
        IF_INT_EQUAL(LW(2), LW(5))
            IF_INT_EQUAL(LW(3), LW(6))
                IF_INT_EQUAL(LW(4), LW(7))
                    GOTO(102)
                END_IF
            END_IF
        END_IF
        SET_VALUE(LW(14), 40)
        CALL(btlevtcmd_SetMoveSpeed, LW(10), FLOAT(4.0f))
        CALL(btlevtcmd_GetHomePos, LW(10), LW(2), LW(3), LW(4))
        CALL(btlevtcmd_GetMoveFrame, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, LW(7))
        IF_INT_GREATER(LW(7), 0)
            CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), LW(14))
            CALL(btlevtcmd_MovePosition, LW(10), LW(2), LW(3), LW(4), 0, -1, 0)
        END_IF
        LABEL(102)
    END_IF
    // The unit faces its usual way and its idle animation restarts.
    CALL(btlevtcmd_ResetFaceDirection, LW(10))
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    RETURN
EVT_END()

/**
 * Partner switch from the command menu: loads the new partner's animations,
 * shrinks the old partner as it jumps to Mario, swaps in the new one with a cheer from the audience,
 * grows it as it jumps to its home position and removes the old unit.
 * The switch ends Mario's turn unless Quick Change is equipped (and he is not confused).
 */
EVT_BEGIN(btldefaultevt_ChangeParty)
    CALL(_anime_load)
    CALL(btlevtcmd_GetPartyId, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_GetBodyId, LW(3), LW(4))
    CALL(btlevtcmd_SetFallAccel, LW(3), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, LW(3), LW(0), LW(1), LW(2))
    CALL(btlevtcmd_GetMarioId, BTL_UNIT_SELF, LW(8))
    CALL(btlevtcmd_GetPos, LW(8), LW(5), LW(6), LW(7))
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetScale, LW(3), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
        LOOP(18)
            CALL(btlevtcmd_AddScale, LW(3), FLOAT(-0.049804688f), FLOAT(-0.049804688f), FLOAT(-0.049804688f))
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(evt_snd_sfxon, STRING("SFX_BTL_PARTY_IN1"), 0)
    CALL(btlevtcmd_JumpPosition, LW(3), LW(5), LW(6), LW(7), 20, 0)
    CALL(_anime_load_wait)
    CALL(btlevtcmd_ChangeParty, LW(9))
    CALL(btlevtcmd_OffUnitFlag, LW(9), UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_GetBodyId, LW(9), LW(0))
    CALL(btlevtcmd_AnimeChangePoseFromTable, LW(9), LW(0))
    CALL(btlevtcmd_SetPos, LW(9), LW(5), LW(6), LW(7))
    CALL(btlevtcmd_SetFallAccel, LW(9), FLOAT(0.69921875f))
    CALL(btlevtcmd_CheckDataOfDataTable, LW(9), LW(0), 4)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_RunDataEventChild, LW(9), 4)
    END_IF
    CALL(evt_snd_sfxon, STRING("SFX_BTL_PARTY_CHANGE1"), 0)
    CALL(evt_audience_sound_cheer, 45, 25)
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_SetScale, LW(9), FLOAT(0.099609375f), FLOAT(0.099609375f), FLOAT(0.099609375f))
        LOOP(18)
            CALL(btlevtcmd_AddScale, LW(9), FLOAT(0.049804688f), FLOAT(0.049804688f), FLOAT(0.049804688f))
            WAIT_FRAMES(1)
        END_LOOP
        CALL(btlevtcmd_SetScale, LW(9), FLOAT(1.0f), FLOAT(1.0f), FLOAT(1.0f))
    END_SIBLING_EVENT
    CALL(btlevtcmd_GetHomePos, LW(9), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon, STRING("SFX_PARTY_OUT1"), 0)
    CALL(btlevtcmd_JumpPosition, LW(9), LW(0), LW(1), LW(2), 20, 0)
    CALL(btlevtcmd_OnUnitFlag, LW(9), UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_KillUnit, LW(3), 0)
    CALL(btlevtcmd_SortPhaseMoveTable)
    CALL(_check_pose_stay, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    END_IF
    RETURN
EVT_END()

/** The short scripts sit where the demo's .data places them (retail keeps them in .sdata). */
EVT_BEGIN(btldefaultevt_ProtectPartner)
    CALL(btlevtcmd_GetPartnerId, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_SetGuard, BTL_UNIT_SELF, LW(3))
    RETURN
EVT_END()

/** Empty script used as a data-table event that should do nothing (the partners use it for event 48). */
EVT_BEGIN(btldefaultevt_Dummy)
    RETURN
EVT_END()

/**
 * Jitters the unit sideways for electric-shock paralysis ("biribiri"), then restarts its wait event.
 * battle_seq would run it for Electric units, but its chance there is irand(100) < 0, so it never plays.
 */
EVT_BEGIN(btldefaultevt_BiribiriMove)
    CALL(evt_sub_intpl_init, 8, 0, 5, 16)
    LABEL(0)
    CALL(evt_sub_intpl_get_value)
    CALL(btlevtcmd_SetDispOffset, BTL_UNIT_SELF, LW(0), 0, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LW(1), 1)
        GOTO(0)
    END_IF
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    RETURN
EVT_END()

/**
 * Moves a unit (LW(10), part LW(11)) in front of the unit it protects, running or diving if it floats,
 * and ends in the guard pose; run for damage code 56.
 */
EVT_BEGIN(btldefaultevt_guard_move)
    CALL(btlevtcmd_AnimeCmpPoseType, LW(10), LW(11), 42, 40, LW(2))
    IF_INT_EQUAL(LW(2), 0)
        CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(2.0f))
    END_IF
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_RUN)
    CALL(btlevtcmd_CheckAttribute, LW(10), UNIT_ATTR_FLOATING, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_GetProtectId, LW(10), LW(6))
        CALL(btlevtcmd_GetHomePos, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePosition, LW(10), LW(0), LW(1), LW(2), 20, 0, 0, 0, -1)
    ELSE
        CALL(btlevtcmd_GetProtectId, LW(10), LW(6))
        CALL(btlevtcmd_GetHomePos, LW(6), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 20, -1, 0)
    END_IF
    CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(1.0f))
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 46)
    CALL(btlevtcmd_GuardMoveEnd)
    RETURN
EVT_END()

/**
 * After a protecting unit has taken the hit, moves it back to its home position,
 * ends the guard and restarts its wait event.
 */
EVT_BEGIN(btldefaultevt_guard_return)
    CALL(btlevtcmd_WaitAttackEnd)
    CALL(btlevtcmd_CheckGuardMotionEnable, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeCmpPoseType, LW(10), LW(11), 42, 40, LW(2))
        IF_INT_EQUAL(LW(2), 0)
            CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(2.0f))
        END_IF
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_RUN)
    END_IF
    CALL(btlevtcmd_CheckAttribute, LW(10), UNIT_ATTR_FLOATING, LW(6))
    IF_INT_NOT_EQUAL(LW(6), 0)
        CALL(btlevtcmd_GetHomePos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_DivePosition, LW(10), LW(0), LW(1), LW(2), 20, 0, 0, 0, -1)
    ELSE
        CALL(btlevtcmd_GetHomePos, LW(10), LW(0), LW(1), LW(2))
        CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 20, -1, 0)
    END_IF
    CALL(btlevtcmd_CheckGuardMotionEnable, LW(10), LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_AnimeSetMotionSpeed, LW(10), LW(11), FLOAT(1.0f))
        CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_DEFEND)
    END_IF
    CALL(btlevtcmd_GuardMoveEnd)
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    RETURN
EVT_END()

/** Action for a unit that does nothing this turn: restarts its wait event. */
EVT_BEGIN(btldefaultevt_Wait)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Action that ends a tutorial battle turn: runs the lecture unit's data-table event 70 (69 in the demos). */
EVT_BEGIN(btldefaultevt_LectureEnd)
#if VERSION <= VERSION_DEMO_US
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_LECTURE, 69)
#else
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_LECTURE, 70)
#endif
    RETURN
EVT_END()

/**
 * The Appeal command: the camera zooms in on the unit (further out in retail when it is huge),
 * it strikes the appeal pose with a sound and the audience reacts,
 * unless its data table has its own appeal event.
 */
EVT_BEGIN(btldefaultevt_Appeal)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), BTL_POSE_STAY)
#if VERSION >= VERSION_JP
    CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_HUGE, LW(0))
    IF_INT_EQUAL(LW(0), 0)
#endif
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(1))
        ADD(LW(1), 53)
        ADD(LW(3), 35)
        SET_VALUE(LW(4), LW(2))
        ADD(LW(2), 250)
#if VERSION >= VERSION_JP
    ELSE
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        SET_VALUE(LW(3), LW(1))
        ADD(LW(1), 150)
        ADD(LW(3), 80)
        SET_VALUE(LW(4), LW(2))
        ADD(LW(2), 400)
    END_IF
#endif
    CALL(evt_btl_camera_set_mode, 0, 3)
    CALL(evt_btl_camera_set_moveto, 0, LW(0), LW(1), LW(2), LW(0), LW(3), LW(4), 30, 11)
    CALL(evt_batstage_light_set_player_on, 0)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_CheckDataOfDataTable, BTL_UNIT_SELF, LW(0), 5)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 5)
        CALL(evt_btl_camera_set_mode, 0, 0)
        CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
        CALL(evt_batstage_light_set_player_off)
        WAIT_FRAMES(60)
        RETURN
    END_IF
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), BTL_POSE_APPEAL)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_MARIO_APPEAL1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    WAIT_FRAMES(60)
    CALL(evt_btl_camera_set_mode, 0, 0)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 2)
    CALL(btlevtcmd_AudienceAppeal, BTL_UNIT_SELF)
    CALL(evt_batstage_light_set_player_off)
    WAIT_FRAMES(60)
    CALL(btlevtcmd_StartWaitEvent, LW(10))
    RETURN
EVT_END()

/**
 * Shared Defend action (LW(12) = the defend weapon):
 * pays the cost, spins the unit twice, marks it as defending, shows the "defend" message and returns to waiting.
 */
EVT_BEGIN(_Defence_core)
    CALL(btlevtcmd_GetUnitId, BTL_UNIT_SELF, LW(3))
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(4))
    IF_INT_EQUAL(LW(3), -1)
        GOTO(99)
    END_IF
    CALL(btlevtcmd_PayWeaponCost, BTL_UNIT_SELF, LW(12))
    CALL(btlevtcmd_RunDataEventChild, BTL_UNIT_SELF, 7)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_MARIO_DEFENCE1"), EVT_NULLPTR, 0, EVT_NULLPTR)
    LOOP(20)
        CALL(btlevtcmd_AddRotate, BTL_UNIT_SELF, 0, 36, 0)
        WAIT_FRAMES(1)
    END_LOOP
    CALL(btlevtcmd_SetRotate, BTL_UNIT_SELF, 0, 0, 0)
    CALL(btlevtcmd_WeaponAftereffect, LW(12))
    CALL(btlevtcmd_OnStatusFlag, BTL_UNIT_SELF, STATUS_FLAG_DEFENDING)
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(4), BTL_POSE_DEFEND)
    CALL(btlevtcmd_snd_se, BTL_UNIT_SELF, STRING("SFX_BTL_MARIO_DEFENCE2"), EVT_NULLPTR, 0, EVT_NULLPTR)
    CALL(btlevtcmd_ftof, 60, LW(0))
    CALL(btlevtcmd_AnnounceMessage, 0, 0, 0, STRING("btl_msg_defend_command_exec"), LW(0))
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Mario's Defend command. */
EVT_BEGIN(btldefaultevt_Defend)
    SET_VALUE(LW(12), PTR(&badgeWeapon_DefenceCommand))
    CALL_CHILD(_Defence_core)
    RETURN
EVT_END()

/** The partner's Defend command. */
EVT_BEGIN(btldefaultevt_DefendParty)
    SET_VALUE(LW(12), PTR(&badgeWeapon_DefenceCommandP))
    CALL_CHILD(_Defence_core)
    RETURN
EVT_END()

/**
 * The Run Away command: Mario and the partner turn and run in place
 * while the escape action command plays (the gauge uses the enemy group's run rate).
 * On a miss both stumble and walk home; on a success they run off screen,
 * the audience reacts and the battle ends (after _event_MajinaiEnd when Merlee's spells ran out).
 */
EVT_BEGIN(btldefaultevt_Escape)
    // The camera frames the party and the Run Away Action Command is set up,
    // its gauge set by the enemy group's escape rate.
    CALL(evt_btl_camera_set_mode, 0, 20)
    CALL(_btl_escape_reset_move_color_lv_player_unit_all)
    CALL(btlevtcmd_AcSetDifficulty, BTL_UNIT_SELF, 3)
    CALL(evt_sub_random, 99, LW(0))
    CALL(evt_sub_random, 6, LW(1))
    ADD(LW(1), 30)
    CALL(_get_escape_rate, LW(2))
    CALL(btlevtcmd_AcSetParamAll, 1, 180, LW(0), LW(1), 0, 4, 6, LW(2))
    CALL(btlevtcmd_AcSetFlag, 3)
    CALL(btlevtcmd_SetupAC, BTL_UNIT_SELF, 5, 1, 0)
    CALL(_set_escape_ac_hlp_msg)
    // The partner, then Mario, turns away from the enemies and hops twice.
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPartnerId, BTL_UNIT_SELF, LW(10))
        IF_INT_NOT_EQUAL(LW(10), -1)
            CALL(btlevtcmd_CheckActStatus, LW(10), LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetBodyId, LW(10), LW(11))
                CALL(btlevtcmd_CalculateFaceDirection, LW(10), LW(11), -1, -1, 260, LW(0))
                CALL(btlevtcmd_ChangeFaceDirection, LW(10), LW(0))
                CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_RUN)
                CALL(btlevtcmd_JumpSetting, LW(10), 20, FLOAT(0.0f), FLOAT(0.69921875f))
                CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 16, -1)
                CALL(btlevtcmd_JumpPosition, LW(10), LW(0), LW(1), LW(2), 16, -1)
            END_IF
        END_IF
    END_INLINE_EVENT
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(11))
    CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, LW(11), -1, -1, 260, LW(0))
    CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(11), BTL_POSE_RUN)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    // The audience reacts and both run in place, slowly edging back, while the player fills the gauge.
    CALL(btlevtcmd_audience_code_escape)
    CALL(evt_snd_sfxon, STRING("SFX_MARIO_BATTLE_STAMP1"), LW(15))
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionSub, BTL_UNIT_SELF, LW(0), 15)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 180, -1, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(btlevtcmd_GetPartnerId, BTL_UNIT_SELF, LW(10))
        IF_INT_NOT_EQUAL(LW(10), -1)
            CALL(btlevtcmd_CheckActStatus, LW(10), LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_FaceDirectionSub, LW(10), LW(0), 15)
                CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 180, -1, 0)
            END_IF
        END_IF
    END_INLINE_EVENT
    // The Action Command runs; Mario hops when it ends.
    CALL(btlevtcmd_StartAC, 1)
    CALL(btlevtcmd_ResultAC)
    CALL(btlevtcmd_StopAC)
    CALL(btlevtcmd_JumpSetting, BTL_UNIT_SELF, 20, FLOAT(0.0f), FLOAT(0.69921875f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_JumpPosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 16, -1)
    CALL(btlevtcmd_GetResultAC, LW(6))
    // The escape failed: the partner and Mario dash a few steps, trip and fall, and the audience reacts.
    IF_BITS_CLEAR(LW(6), 2)
        CALL(evt_snd_sfxoff, LW(15))
        CALL(evt_snd_sfxon, STRING("SFX_MARIO_RUN_AWAY_MISS1"), 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL(btlevtcmd_GetPartnerId, BTL_UNIT_SELF, LW(10))
            IF_INT_NOT_EQUAL(LW(10), -1)
                CALL(btlevtcmd_CheckActStatus, LW(10), LW(0))
                IF_INT_NOT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_OffUnitFlag, LW(10), UNIT_FLAG_FLOAT_ACTIVE)
                    CALL(btlevtcmd_GetBodyId, LW(10), LW(11))
                    CALL(btlevtcmd_SetMoveSpeed, LW(10), FLOAT(10.0f))
                    CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_FaceDirectionAdd, LW(10), LW(0), 30)
                    CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 0, -1, 0)
                    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_ESCAPE_FAIL)
                    CALL(btlevtcmd_FaceDirectionAdd, LW(10), LW(0), 5)
                    CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 5, -1, 0)
                    CALL(btlevtcmd_FaceDirectionAdd, LW(10), LW(0), 10)
                    CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 60, -1, 0)
                    WAIT_FRAMES(25)
                    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_ESCAPE_FAIL_END)
                    WAIT_FRAMES(40)
                    CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_FLOAT_ACTIVE)
                END_IF
            END_IF
        END_SIBLING_EVENT
        CALL(btlevtcmd_OffUnitFlag, LW(10), UNIT_FLAG_FLOAT_ACTIVE)
        CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(11))
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
        CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 30)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(11), BTL_POSE_ESCAPE_FAIL)
        CALL(btlevtcmd_audience_code_escape_fail)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 5)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 5, -1, 0)
        CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 10)
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 60, -1, 0)
        WAIT_FRAMES(25)
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(11), BTL_POSE_ESCAPE_FAIL_END)
        CALL(evt_btl_camera_set_mode, 0, 0)
        WAIT_FRAMES(40)
        CALL(btlevtcmd_OnUnitFlag, LW(10), UNIT_FLAG_FLOAT_ACTIVE)
        // Both get up and walk back to their home positions; the turn goes on.
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL(btlevtcmd_GetPartnerId, BTL_UNIT_SELF, LW(10))
            IF_INT_NOT_EQUAL(LW(10), -1)
                CALL(btlevtcmd_CheckActStatus, LW(10), LW(0))
                IF_INT_NOT_EQUAL(LW(0), 0)
                    CALL(btlevtcmd_GetBodyId, LW(10), LW(11))
                    CALL(btlevtcmd_CalculateFaceDirection, LW(10), LW(11), 0, 0, 4, LW(0))
                    CALL(btlevtcmd_ChangeFaceDirection, LW(10), LW(0))
                    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), BTL_POSE_RUN)
                    CALL(btlevtcmd_SetMoveSpeed, LW(10), FLOAT(3.0f))
                    CALL(btlevtcmd_GetHomePos, LW(10), LW(0), LW(1), LW(2))
                    CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 0, -1, 0)
                    CALL(btlevtcmd_StartWaitEvent, LW(10))
                END_IF
            END_IF
        END_SIBLING_EVENT
        CALL(btlevtcmd_CalculateFaceDirection, BTL_UNIT_SELF, LW(11), 0, 0, 4, LW(0))
        CALL(btlevtcmd_ChangeFaceDirection, BTL_UNIT_SELF, LW(0))
        CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(11), BTL_POSE_RUN)
        CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(3.0f))
        CALL(btlevtcmd_GetHomePos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
        CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, -1, 0)
        CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
        RETURN
    END_IF
    // The escape worked: the partner and Mario dash off the side of the stage while the audience reacts.
    BEGIN_SIBLING_EVENT
        CALL(btlevtcmd_GetPartnerId, BTL_UNIT_SELF, LW(10))
        IF_INT_NOT_EQUAL(LW(10), -1)
            CALL(btlevtcmd_CheckActStatus, LW(10), LW(0))
            IF_INT_NOT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_SetMoveSpeed, LW(10), FLOAT(10.0f))
                CALL(btlevtcmd_GetPos, LW(10), LW(0), LW(1), LW(2))
                CALL(btlevtcmd_FaceDirectionAdd, LW(10), LW(0), 200)
                CALL(btlevtcmd_MovePosition, LW(10), LW(0), LW(1), LW(2), 0, -1, 0)
            END_IF
        END_IF
    END_SIBLING_EVENT
    CALL(evt_snd_sfxoff, LW(15))
    CALL(btlevtcmd_audience_code_escape_success)
    CALL(evt_snd_sfxon, STRING("SFX_MARIO_RUN_AWAY1"), 0)
    CALL(btlevtcmd_SetMoveSpeed, BTL_UNIT_SELF, FLOAT(10.0f))
    CALL(btlevtcmd_GetPos, BTL_UNIT_SELF, LW(0), LW(1), LW(2))
    CALL(btlevtcmd_FaceDirectionAdd, BTL_UNIT_SELF, LW(0), 200)
    CALL(btlevtcmd_MovePosition, BTL_UNIT_SELF, LW(0), LW(1), LW(2), 0, 0, 0)
    // When Merlee's spells ran out during this battle, her farewell plays first; then the battle ends.
    SET_VALUE(LW(15), 0)
    CALL(btlevtcmd_check_battleflag, LW(0), 4194304)
    IF_INT_NOT_EQUAL(LW(0), 0)
        BEGIN_SIBLING_EVENT_GET_ID(LW(15))
            CALL_CHILD(_event_MajinaiEnd)
        END_SIBLING_EVENT
    END_IF
    IF_INT_NOT_EQUAL(LW(15), 0)
        CALL(btlevtcmd_WaitEventEnd, LW(15))
    END_IF
    CALL(btlevtcmd_InterruptStop, 0)
    RETURN
EVT_END()

/** Confused unit's action: the confused pose for 30 frames, then the unit's confusion action script. */
EVT_BEGIN(btldefaultevt_Confuse)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), 5)
    WAIT_FRAMES(30)
    CALL(btlevtcmd_GetConfuseActEvent, BTL_UNIT_SELF, LW(0))
    CALL_CHILD(LW(0))
    RETURN
EVT_END()

/**
 * Run instead of a unit's action in zero gravity when it cannot act there:
 * zooms on it and shows the "can't move in zero gravity" message.
 */
EVT_BEGIN(btldefaultevt_CantMoveZeroGravity)
    CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(0))
    CALL(btlevtcmd_AnimeChangePoseType, BTL_UNIT_SELF, LW(0), BTL_POSE_ZERO_GRAVITY)
    CALL(evt_btl_camera_set_mode, 0, 7)
    CALL(evt_btl_camera_set_homing_unit, 0, BTL_UNIT_SELF, BTL_UNIT_NONE)
    CALL(evt_btl_camera_set_moveSpeedLv, 0, 1)
    CALL(evt_btl_camera_set_zoom, 0, 200)
    CALL(btlevtcmd_AnnounceMessage, 0, 0, 0, STRING("btl_msg_cant_move_zero_gravity"), 120)
    CALL(evt_btl_camera_set_mode, 0, 0)
    WAIT_FRAMES(20)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * HP Drain and FP Drain badge effect after an attack:
 * heals the attacker by its equipped HP Drain and then FP Drain power, capped at the damage it dealt this turn,
 * with the recovery effect over its head.
 */
EVT_BEGIN(btldefaultevt_SuitoruBadgeEffect)
    CALL(_get_heart_suitoru_point, BTL_UNIT_SELF, LW(5))
    IF_INT_GREATER_OR_EQUAL(LW(5), 1)
        BEGIN_SIBLING_EVENT
            CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(4))
#if VERSION <= VERSION_DEMO_US
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(4), LW(0), LW(1), LW(2))
            ADD(LW(1), 50)
            CALL(evt_eff, STRING(""), STRING("recovery"), 0, LW(0), LW(1), LW(2), LW(5), 0, 0, 0, 0, 0, 0, 0)
#else
            CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
            CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(7))
            MULTIPLY_FLOAT(LW(7), LW(6))
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(4), LW(0), LW(1), LW(2))
            ADD(LW(1), LW(7))
            CALL(evt_eff, 0, STRING("recovery"), 0, LW(0), LW(1), LW(2), LW(5), 0, 0, 0, 0, 0, 0, 0)
#endif
            WAIT_FRAMES(120)
            CALL(btlevtcmd_RecoverHp, BTL_UNIT_SELF, LW(4), LW(5))
        END_SIBLING_EVENT
        WAIT_FRAMES(125)
    END_IF
    CALL(_get_flower_suitoru_point, BTL_UNIT_SELF, LW(5))
    IF_INT_GREATER_OR_EQUAL(LW(5), 1)
        BEGIN_SIBLING_EVENT
#if VERSION <= VERSION_DEMO_US
            CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(4))
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(4), LW(0), LW(1), LW(2))
            ADD(LW(1), 50)
            CALL(evt_eff, STRING(""), STRING("recovery"), 1, LW(0), LW(1), LW(2), LW(5), 0, 0, 0, 0, 0, 0, 0)
#else
            CALL(btlevtcmd_GetStatusMg, BTL_UNIT_SELF, LW(6))
            CALL(btlevtcmd_GetHeight, BTL_UNIT_SELF, LW(7))
            MULTIPLY_FLOAT(LW(7), LW(6))
            CALL(btlevtcmd_GetBodyId, BTL_UNIT_SELF, LW(4))
            CALL(btlevtcmd_GetPartsPos, BTL_UNIT_SELF, LW(4), LW(0), LW(1), LW(2))
            ADD(LW(1), LW(7))
            CALL(evt_eff, 0, STRING("recovery"), 1, LW(0), LW(1), LW(2), LW(5), 0, 0, 0, 0, 0, 0, 0)
#endif
            WAIT_FRAMES(120)
            CALL(btlevtcmd_RecoverFp, BTL_UNIT_SELF, LW(4), LW(5))
        END_SIBLING_EVENT
        WAIT_FRAMES(125)
    END_IF
    RETURN
EVT_END()

/** Data-table event for avoiding a counter: the unit spins round five times (1800 degrees) over 40 frames. */
EVT_BEGIN(btldefaultevt_avoid_counter_event)
    CALL(btlevtcmd_AnimeChangePoseType, LW(10), LW(11), 49)
    BEGIN_SIBLING_EVENT_GET_ID(LW(0))
        CALL(evt_sub_intpl_init, 5, 0, 1800, 40)
        LOOP(40)
            CALL(evt_sub_intpl_get_value_para, LW(1), LW(2))
            CALL(btlevtcmd_SetRotate, LW(10), EVT_NULLPTR, LW(1), EVT_NULLPTR)
            WAIT_FRAMES(1)
        END_LOOP
    END_SIBLING_EVENT
    CALL(btlevtcmd_WaitEventEnd, LW(0))
    RETURN
EVT_END()

/**
 * Script: backfire for the unit args[0]: shows a pulsing fire for 60 frames, then deals 5 damage to it.
 * Finishes the whole calling script when the unit is the one running it.
 */
static USER_FUNC(_backfire) {
    s32 id;
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    f32 x, y, z;
    s32 self;
    EffectEntry* eff;
    EffFireWork* fire;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (!unit) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        BtlUnit_GetPos(unit, &x, &y, &z);
        event->userdatap[0] = effFireEntry(0, 0, x, y, z, 1.0f);
        event->userdata[1] = 0;
    }
    eff = event->userdatap[0];
    fire = (EffFireWork*)eff->userdata;
    event->userdata[1]++;
    if (event->userdata[1] >= 60) {
        effDelete(event->userdatap[0]);
        BattleDamageDirect(-5, unit, NULL, 1, 0, 0x118, 0, 1);
        self = BattleTransID(event, event->unitId);
        if (self != id) {
            return EVT_RETURN_DONE;
        }
        return EVT_RETURN_FINISH;
    }
    fire->scale = 1.6f * sinfd(event->userdata[1] * 3) + 0.4f;
    return EVT_RETURN_BLOCK;
}

/** Script: starts loading the animations of the partner chosen in the command menu. */
static USER_FUNC(_anime_load) {
    ((BattlePartyAnimeLoadRetBoolFn)BattlePartyAnimeLoad)(_battleWorkPointer->commandMenu.partyKind);
    return EVT_RETURN_DONE;
}

/** Script: blocks until the chosen partner's animations are loaded. */
static USER_FUNC(_anime_load_wait) {
    return ((BattlePartyAnimeLoadRetBoolFn)BattlePartyAnimeLoad)(_battleWorkPointer->commandMenu.partyKind) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/**
 * Script: sets args[0] to 1 when the active unit is Mario
 * and the partner switch costs his turn (no Quick Change, or he is confused).
 */
static USER_FUNC(_check_pose_stay) {
    BattleWork* wp = _battleWorkPointer;
    s32 out = event->args[0];
    BattleUnit* unit;
    s32 stay;
    s32 id;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    stay = FALSE;
    if (unit->currentKind == UNIT_MARIO) {
        stay = TRUE;
        if (wp->badgeEquippedFlags & BADGE_FLAG_QUICK_CHANGE) {
            if (!(unit->tokenFlags & TOKEN_FLAG_CONFUSED_ACTION)) {
                stay = FALSE;
            }
        }
    }
    evtSetValue(event, out, stay);
    return EVT_RETURN_DONE;
}

/** Script: tells the audience that Mario is running away. */
USER_FUNC(btlevtcmd_audience_code_escape) {
    BattleAudience_Case_Escape();
    return EVT_RETURN_DONE;
}

/** Script: audience reaction to a successful escape. */
USER_FUNC(btlevtcmd_audience_code_escape_success) {
    BattleAudience_Case_Escape_Good();
    return EVT_RETURN_DONE;
}

/** Script: audience reaction to a failed escape. */
USER_FUNC(btlevtcmd_audience_code_escape_fail) {
    BattleAudience_Case_Escape_Bad();
    return EVT_RETURN_DONE;
}

/** Script: resets the moveColorLv shading of Mario and the partner to full brightness before the escape. */
static USER_FUNC(_btl_escape_reset_move_color_lv_player_unit_all) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    unit = BattleGetMarioPtr(wp);
    unit->moveColorLv = 0xFF;
    unit = BattleGetPartyPtr(wp);
    if (unit) {
        unit->moveColorLv = 0xFF;
    }
    return EVT_RETURN_DONE;
}

/** Script: shows the escape action command's help text. */
static USER_FUNC(_set_escape_ac_hlp_msg) {
    BattleAcHelpSetHelp("msg_ac_escape");
    BattleAcHelpSetDispType(2);
    return EVT_RETURN_DONE;
}

/** Script: returns in args[0] the enemy group's run rate, which sets the escape gauge. */
static USER_FUNC(_get_escape_rate) {
    BattleWork* wp = _battleWorkPointer;
    evtSetValue(event, event->args[0],
                wp->fbatInfo->setup->groupSetup->enemyData->unitKindParams->runRate);
    return EVT_RETURN_DONE;
}

/**
 * Script: returns in args[1] the HP the unit args[0] regains from HP Drain:
 * its equipped power, capped at its damage dealt.
 */
static USER_FUNC(_get_heart_suitoru_point) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = *args++;
    s32 out = *args++;

    BattleUnit* unit;
    s32 point;

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    point = 0;
    if (unit) {
        point = unit->badgesEquipped.HpDrain;
        if (point > unit->totalDamageDealt) {
            point = unit->totalDamageDealt;
        }
    }
    evtSetValue(event, out, point);
    return EVT_RETURN_DONE;
}

/**
 * Script: returns in args[1] the FP the unit args[0] regains from FP Drain:
 * its equipped power, capped at its damage dealt.
 */
static USER_FUNC(_get_flower_suitoru_point) {
    BattleWork* wp = _battleWorkPointer;
    EvtWord* args = event->args;
    s32 id = *args++;
    s32 out = *args++;

    BattleUnit* unit;
    s32 point;

    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    point = 0;
    if (unit) {
        point = unit->badgesEquipped.FpDrain;
        if (point > unit->totalDamageDealt) {
            point = unit->totalDamageDealt;
        }
    }
    evtSetValue(event, out, point);
    return EVT_RETURN_DONE;
}
