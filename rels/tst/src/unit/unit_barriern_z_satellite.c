// Battle unit Mini-Z-Yux (`barriern_z_satellite`): tst.rel's copy of rels/aji/src/unit/unit_barriern_z_satellite.c.
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "battle/battle.h"
#include "battle/battle_unit.h"
#include "battle/battle_sub.h"
#include "battle/battle_event_default.h"
#include "manager/evtmgr_cmd.h"
#include "battle/battle_event_cmd.h"
#include "evt/evt_sub.h"
#include "tst.h"
#include "version.h"

static USER_FUNC(battleGetBarriernSatelliteInitPos);

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
#if VERSION <= VERSION_DEMO_US
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

static BattleUnitDefense defence = {{0, 0, 0, 0, 0}};

static BattleUnitDefenseAttr defence_attr = {{0, 0, 0, 0, 0}};

static BattleUnitKindPart parts[] = {
    {1, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x600009, 0, pose_table},
    {2, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {3, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {4, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {5, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
    {6, "btl_un_barriern_satellite_z", "c_baria_z", 0.0f, 0.0f, 0.0f, 0.0f, 5.0f, 0.0f, 0.0f, 10.0f, 0.0f, 20, 30, 255, &defence, &defence_attr, 0x13010000, 0, pose_table},
};

#if VERSION <= VERSION_DEMO_US
static StatusVulnerability regist = {70, 90, 90, 0, 80, 100, 100, 0, 100, 80, 100, 80, 100, 80, 80, 0, 90, 100, 80, 100, 100, 100};
#else
static StatusVulnerability regist = {70, 90, 95, 0, 80, 100, 100, 0, 100, 85, 100, 85, 100, 90, 80, 0, 95, 100, 80, 100, 100, 100};
#endif

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

static BattleDataEntry data_table[] = {
    {0, NULL},
};

/**
 * Init script of a Mini-Yux satellite: registers its wait, unison-phase,
 * attack and damage handlers (confusion uses the default handler),
 * sets the unit flags 0x300000 and starts the idle event.
 */
static EVT_BEGIN(init_event)
    CALL(btlevtcmd_SetEventWait, BTL_UNIT_SELF, PTR(wait_event))
    CALL(btlevtcmd_SetEventUnisonPhase, BTL_UNIT_SELF, PTR(unison_phase_event))
    CALL(btlevtcmd_SetEventAttack, BTL_UNIT_SELF, PTR(attack_event))
    CALL(btlevtcmd_SetEventDamage, BTL_UNIT_SELF, PTR(damage_event))
    CALL(btlevtcmd_SetEventConfusion, BTL_UNIT_SELF, PTR(btldefaultevt_Confuse))
    CALL(btlevtcmd_OnUnitFlag, BTL_UNIT_SELF, 3145728)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Damage reaction of a Mini-Yux: runs the default damage handling with LW(10) = -2 (the unit itself)
 * and LW(11) = 1.
 */
static EVT_BEGIN(damage_event)
    SET_VALUE(LW(10), -2)
    SET_VALUE(LW(11), 1)
    CALL_CHILD(btldefaultevt_Damage)
    RETURN
EVT_END()

/** Phase event: empty, it does nothing. */
static EVT_BEGIN(phase_event)
    RETURN
EVT_END()

/** Start-of-turn event of a Mini-Yux: empty, it only restarts its idle event. The parent Yux does the moving. */
static EVT_BEGIN(unison_phase_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Attack event of a Mini-Yux: empty, it only restarts its idle event.
 * The parent Yux makes the satellites attack through its own scripts.
 */
static EVT_BEGIN(attack_event)
    CALL(btlevtcmd_StartWaitEvent, BTL_UNIT_SELF)
    RETURN
EVT_END()

/**
 * Idle event of a Mini-Yux: shows its pose from the pose table, then at random intervals of 30 to 150 frames,
 * if its unit work 1 is set (the parent told it to idle) and it can act and is not asleep,
 * holds the S_4 pose for 180 frames before returning to the table pose.
 */
static EVT_BEGIN(wait_event)
    CALL(btlevtcmd_AnimeChangePoseFromTable, BTL_UNIT_SELF, 1)
    LABEL(0)
    CALL(evt_sub_random, 120, LW(0))
    ADD(LW(0), 30)
    WAIT_FRAMES(LW(0))
    CALL(btlevtcmd_GetUnitWork, BTL_UNIT_SELF, 1, LW(0))
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(btlevtcmd_CheckActStatus, BTL_UNIT_SELF, LW(0))
        IF_INT_NOT_EQUAL(LW(0), 0)
            CALL(btlevtcmd_CheckStatus, BTL_UNIT_SELF, 5, LW(0))
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
 * Script helper: args[0] is the Yux, args[1] the number of satellites (1-4),
 * args[2] the index of this satellite; args[3]-args[5] receive its starting offset from the Yux (a fixed
 * formation of +-25 units, x mirrored by facing direction).
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
#if VERSION >= VERSION_JP
    TST_ASSERTMSG("unit_barriern_common_main.c", 44, max<5, "衛星の数が多すぎ\n");
#endif
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
