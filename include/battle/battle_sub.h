// Declares the battle unit transition ids and movement and math helpers.
#pragma once

#include "battle/battle.h"
#include "manager/evtmgr.h"

// Unit ids with a special meaning in battle script arguments; BattleTransID turns
// them into the id of a real unit.
typedef enum BattleTransUnitId {
    BTL_UNIT_NONE = -1,    // no unit
    BTL_UNIT_SELF = -2,    // the unit that runs the script (EventEntry.unitId)
    BTL_UNIT_MARIO = -3,   // Mario
    BTL_UNIT_PARTNER = -4, // the active partner, or -1 when there is none
    BTL_UNIT_SYSTEM = -5,  // the battle's system unit
    BTL_UNIT_LECTURE = -6, // the unit set with _battle_set_lecture_unit_id (BattleWork.lectureUnitId)
} BattleTransUnitId;

void btlsubResetMoveColorLvAll(BattleWork* work);
s32 BattleTransID(EventEntry* event, s32 type);

void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);

f32 sinfd(f32 deg);
f32 cosfd(f32 deg);
f32 atan2f_safety(f32 y, f32 x);
f32 intpl_sub(s32 mode, s32 cur, s32 steps, f32 start, f32 end);
s32 BtlCompForwardLv(s32 dir, f32 x);
