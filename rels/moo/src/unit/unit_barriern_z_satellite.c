// Battle unit the Mini-Z-Yux that orbit a Z-Yux (バリアーンＺ): moo.rel's copy.

#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_cmd.h"
#include "evt/evt_sub.h"

// Unit work slots of a Mini-Yux (btlevtcmd_SetUnitWork / GetUnitWork).
enum {
    UW_BARRIERN_Z_SATELLITE_PARENT = 0, // unit id of the Yux it orbits (set by the Yux when it spawns it)
    UW_BARRIERN_Z_SATELLITE_IDLE = 1    // non-zero once the Yux lets it play its idle pose
};

BattleUnitKind unit_barriern_z_satellite;
static BattleUnitDefense defence;
static BattleUnitDefenseAttr defence_attr;
static BattleUnitKindPart parts[6];
static StatusVulnerability regist;
static PoseTableEntry pose_table[17];
static BattleDataEntry data_table[1];
static EvtWord init_event[29];
static EvtWord damage_event[10];
static EvtWord unison_phase_event[5];
static EvtWord attack_event[5];
static EvtWord wait_event[56];

/**
 * Unit data of the Mini-Z-Yux: 2 HP, 16x16 units in size; ties together its sounds, parts,
 * status vulnerability, init event and event table.
 */
BattleUnitKind unit_barriern_z_satellite = {
    116,
    "btl_un_barriern_satellite_z",
    2,
    0,
    1,
    1,
    0,
    0,
    0,
    70,
    0,
    50,
    9999,
    16,
    16,
    0,
    8,
    0.0f,
    0.0f,
    0.0f,
#if VERSION <= VERSION_DEMO_JP
    0,
    -16,
#else
    -3,
    -6,
#endif
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
    5.0f,
    6.0f,
    0.0f,
    0.0f,
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
    "SFX_ENM_BARRI_DAMAGED1",
    "SFX_BTL_DAMAGE_FIRE1",
    "SFX_BTL_DAMAGE_ICE1",
    "SFX_BTL_DAMAGE_BIRIBIRI1",
    0x4,
    &regist,
    6,
    parts,
    init_event,
    data_table,
};

/** Defence of the Mini-Z-Yux: 0 against every kind of hit. */
static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

/** Defence attributes of the Mini-Z-Yux: none, every element hits it normally. */
static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

/** Parts of the Mini-Z-Yux: 6 parts (model c_baria_z). */
static BattleUnitKindPart parts[] = {
    {1, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
    {2, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {5, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {6, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

#if VERSION <= VERSION_DEMO_JP
/**
 * Demo builds: Status vulnerability of the Mini-Z-Yux (percent chance each status takes hold):
 * immune to poison, freeze, fright; resists sleep (70%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {70, 90, 90, 0, 80, 100, 100, 0, 100, 80, 100, 80, 100, 80, 80, 0, 90, 100, 80, 100, 100, 100};
#else
/**
 * Retail builds: Status vulnerability of the Mini-Z-Yux (percent chance each status takes hold):
 * immune to poison, freeze, fright; resists sleep (70%); the rest take hold at 80% or better.
 */
static StatusVulnerability regist = {70, 90, 95, 0, 80, 100, 100, 0, 100, 85, 100, 85, 100, 90, 80, 0, 95, 100, 80, 100, 100, 100};
#endif

/** Pose table of the Mini-Z-Yux: maps its battle poses to its animations. */
static PoseTableEntry pose_table[] = {
    {1, "N_2"},
    {2, "Y_2"},
    {9, "Y_2"},
    {5, "K_2"},
    {4, "X_2"},
    {3, "X_2"},
    {28, "S_2"},
    {29, "Q_2"},
    {30, "Q_2"},
    {31, "S_2"},
    {39, "D_2"},
    {42, "R_2"},
    {41, "R_2"},
    {40, "W_2"},
    {56, "X_2"},
    {57, "X_2"},
    {BTL_POSE_STAY_DEFAULT, "S_2"},
};

/** Event table of the Mini-Z-Yux: it has no special event scripts. */
static BattleDataEntry data_table[] = {
    {0, NULL},
};

/**
 * Init event of the Mini Z-Yux: installs its wait, unison phase, attack,
 * damage and confusion events and sets unit flags 0x100000 and 0x200000 (UNIT_FLAG_FLOAT and FLOAT_ACTIVE:
 * it hovers with the bobbing motion).
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, UNIT_FLAG_FLOAT | UNIT_FLAG_FLOAT_ACTIVE)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/** Damage event of the Mini Z-Yux: default damage handling on its body part. */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Phase event of the Mini Z-Yux: does nothing (an empty script). */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Unison phase event of the Mini Z-Yux: only restarts its wait event; the Z-Yux that owns it does the work. */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack event of the Mini Z-Yux: never attacks by itself;
 * it only restarts its wait event (the Z-Yux uses it in its own attacks).
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Wait event of the Mini Z-Yux: plays its idle pose and,
 * from time to time (every 30 to 150 frames) while its unit work 1 flag is set and it can act and is not asleep,
 * glows (S_4) for 180 frames.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    LABEL(0)
    CALL(evt_sub_random, 120, LW(0))
    ADD(LW(0), 30)
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, UW_BARRIERN_Z_SATELLITE_IDLE, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, STATUS_CONFUSE, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL(btlevtcmd_AnimeChangePose, BTL_UNIT_SELF, 1, STRING("S_4"))
                WAIT_FRAMES(180)
                CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
            END_IF
        END_IF
    END_IF
    GOTO(0)
    RETURN
EVT_END()

/**
 * Script helper: returns where a Mini Z-Yux sits around its Z-Yux.
 * args[0] is the Z-Yux, args[1] the number of satellites, args[2] the index of this one (0-based);
 * the offset is returned in args[3], args[4] and args[5] (X mirrored by the Z-Yux's facing):
 * 1 beside it, 2 on both sides, 3 above and two below, 4 on four corners, 25 units each way.
 */
static USER_FUNC(battleGetBarriernSatelliteInitPos) {
    EvtWord* args = event->args;
    BattleUnit* unit;
    s32 max;
    s32 index;
    s32 id;
    s32 x;
    s32 y;
    s32 z;
    s32 i;
    s32 j;
    static const Vec VecData[] = {
        // 1 satellite
        {25.0f, 0.0f, 0.0f},
        // 2 satellites
        {25.0f, 0.0f, 0.0f},
        {-25.0f, 0.0f, 0.0f},
        // 3 satellites
        {0.0f, 25.0f, 0.0f},
        {25.0f, -25.0f, 0.0f},
        {-25.0f, -25.0f, 0.0f},
        // 4 satellites
        {25.0f, 25.0f, 0.0f},
        {-25.0f, 25.0f, 0.0f},
        {25.0f, -25.0f, 0.0f},
        {-25.0f, -25.0f, 0.0f},
    };
    const Vec* p;
    BattleWork* wp = _battleWorkPointer;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    max = evtGetValue(event, args[1]);
    index = evtGetValue(event, args[2]);
    x = args[3];
    y = args[4];
    z = args[5];
    p = VecData;
    for (i = 0; i < max; i++) {
        for (j = 0; j < i; j++) {
            p++;
        }
    }
    for (j = 0; j < index; j++) {
        p++;
    }
    evtSetValue(event, x, (s32)(p->x * unit->faceDirection));
    evtSetValue(event, y, (s32)p->y);
    evtSetValue(event, z, (s32)p->z);
    return EVT_RETURN_DONE;
}
