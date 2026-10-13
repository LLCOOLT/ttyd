/* TODO: whoever's unfucking this file, every function before btlevtcmd_GetHp
 * needs to be refactored to have BattleWork* wp = _battleWorkPointer; right
 * below args (line 2 in each function), along with having to explicitly store
 * btlId (can't condense to one line), should fix most problems
*/
#include "battle/battle_event_cmd.h"
#pragma optimize_for_size on
#include "battle/battle_acrobat.h"
#include "battle/battle_disp.h"
#include "battle/battle_sub.h"
#include "battle/battle_unit.h"
#include "battle/battle_unit_event.h"
#include "eff/eff_nice.h"
#include "manager/evtmgr_cmd.h"
#include "system.h"
#include <stdlib.h>

extern BattleWork* _battleWorkPointer;

//s32* eventId
USER_FUNC(btlevtcmd_WaitEventEnd) {
    s32 id;

    id = evtGetValue(event, *event->args);
    return evtCheckID(id) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE; //TODO: fix
}

//s32 retIndex, s32 battleFlags
USER_FUNC(btlevtcmd_check_battleflag) { //TODO: regalloc
    s32* args = event->args;
    s32 index;
    s32 flags = args[1];
    index = args[0];
    if (flags & _battleWorkPointer->flags) {
        evtSetValue(event, index, TRUE);
    }
    else {
        evtSetValue(event, index, FALSE);
    }
    return EVT_RETURN_DONE;
}

//BOOL* onoff, s32 flags
USER_FUNC(btlevtcmd_onoff_battleflag) {
    s32* args = event->args;
    BOOL val = evtGetValue(event, args[0]);
    u32 flags = args[1];
    BattleWork* wp = _battleWorkPointer;
    if (val == TRUE) {
        wp->flags |= flags;
    }
    else {
        wp->flags &= ~flags;
    }
    return EVT_RETURN_DONE;
}

//s32 retIndex
USER_FUNC(btlevtcmd_get_turn) {
    evtSetValue(event, *event->args, _battleWorkPointer->turnCount);
    return EVT_RETURN_DONE;
}

//no params
USER_FUNC(btlevtcmd_reset_turn) {
    _battleWorkPointer->flags |= 0x2000;
    return EVT_RETURN_DONE;
}

//no params
USER_FUNC(btlevtcmd_reset_move_color_lv_all) {
    btlsubResetMoveColorLvAll(_battleWorkPointer);
    return EVT_RETURN_DONE;
}

//s32 retIndex, s32 phaseSeqId
USER_FUNC(btlevtcmd_CheckPhase) {
    s32* args = event->args;
    s32 index = args[0];
    u32 seq = args[1];
    if (seq != BattleGetSeq(_battleWorkPointer, SEQ_PHASE)) {
        evtSetValue(event, index, FALSE);
    }
    else {
        evtSetValue(event, index, TRUE);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 indexX, s32 indexY, s32 indexZ
USER_FUNC(btlevtcmd_GetPos) {
    s32* args = event->args;
    s32 btlId;
    s32 indexX, indexY, indexZ;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    indexX = args[1];
    indexY = args[2];
    indexZ = args[3];
    BtlUnit_GetPos(unit, &x, &y, &z);
    if (indexX != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexX, (s32)x);
    }
    if (indexY != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexY, (s32)y);
    }
    if (indexZ != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexZ, (s32)z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 indexX, s32 indexY, s32 indexZ
USER_FUNC(btlevtcmd_GetPosFloat) {
    s32* args = event->args;
    s32 btlId;
    s32 indexX, indexY, indexZ;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;


    id = evtGetValue(event, args[0]);


    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    indexX = args[1];
    indexY = args[2];
    indexZ = args[3];
    BtlUnit_GetPos(unit, &x, &y, &z);
    if (indexX != EVTDAT_POINTER_MAX) {
        evtSetFloat(event, indexX, x);
    }
    if (indexY != EVTDAT_POINTER_MAX) {
        evtSetFloat(event, indexY, y);
    }
    if (indexZ != EVTDAT_POINTER_MAX) {
        evtSetFloat(event, indexZ, z);
    }
    return EVT_RETURN_DONE;
}

//s32* maxValue, s32 retIndex
USER_FUNC(btlevtcmd_GetRandomValue) {
    s32* args = event->args;
    s32 max, index;

    max = evtGetValue(event, args[0]);
    index = args[1];
    evtSetValue(event, index, irand(max));
    return EVT_RETURN_DONE;
}

//s32 retIndex, s32 countIndex, s32 sizeIndex[]
USER_FUNC(btlevtcmd_DrawLots) {
    s32* args = event->args;
    s32 index = args[0];
    s32 *alloc;
    s32 i, count, max;
    s32 ceiling, ceilcount, retcount;

    index = args[0];
    args += 2;
    count = evtGetValue(event, args[-1]);
    alloc = BattleAlloc(sizeof(s32) * count);
    max = 0;
    for (i = 0; i < count; i++) {
        alloc[i] = evtGetValue(event, *args++);
        max += alloc[i];
    }
    ceiling = irand(max);
    retcount = 0;
    for (i = 0, ceilcount = retcount; i < count; i++) {
        ceilcount += alloc[i];
        if (ceiling < ceilcount) {
            break;
        }
        retcount++;
    }
    evtSetValue(event, index, retcount);
    BattleFree(alloc);
    return EVT_RETURN_DONE;
}

//s32 retIndex for unitId, BattleUnitSetup** setup, s32 spawnFlags
USER_FUNC(btlevtcmd_SpawnUnit) {
    s32* args = event->args;
    BattleUnitSetup* setup;
    BattleUnit* unit;
    s32 index;
    
    index = args[0];
    setup = (BattleUnitSetup*)evtGetValue(event, args[1]);
    unit = BtlUnit_Spawn(setup, args[2]);
    if (!unit) {
        evtSetValue(event, index, -1);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, index, unit->unitId);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 flags
USER_FUNC(btlevtcmd_KillUnit) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    s32 id, flags;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    flags = args[1];
    if (!unit) {
        return EVT_RETURN_DONE;
    }
    unit->currentHp = 0;
    BtlUnit_ClearStatus(unit);
    if (flags & 2) {
        unit->mAttributeFlags |= 0x20000;
        return EVT_RETURN_DONE;
    }
    else {
        BtlUnit_SetStatus(unit, STATUS_INSTANT_KILL, 1, 1);
        if (!(flags & 1)) {
            unit->flags |= 0x80000000;
        }
        return EVT_RETURN_DONE;
    }
}

//s32* battleId, s32* copyToPartId, BattleUnitKindPart* kind, s32* copyFromPartId
USER_FUNC(btlevtcmd_ReplaceParts) {
    s32* args = event->args;
    BattleUnitPart* part;
    BattleUnit* unit;
    BattleUnitKindPart* kind;
    s32 id, transId, lookupPart, partNum;

    id = evtGetValue(event, args[0]);
    transId = BattleTransID(event, id);
    lookupPart = evtGetValue(event, args[1]);
    kind = (BattleUnitKindPart*)args[2];
    partNum = evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, transId);
    part = BattleGetUnitPartsPtr(transId, lookupPart);
    if (kind) {
        while (kind->partNum != partNum) {
            ;
        }
        part->mKindPartParams = kind;
        part->partName = part->mKindPartParams->partName;
        part->attributes = part->mKindPartParams->attributes;
        part->counterAttributes = part->mKindPartParams->counterAttributes;
        part->defense = part->mKindPartParams->defense;
        part->defenseAttr = part->mKindPartParams->defenseAttr;
        part->mPositionOffset.x = part->mKindPartParams->positionOffset.x;
        part->mPositionOffset.y = part->mKindPartParams->positionOffset.y;
        part->mPositionOffset.z = part->mKindPartParams->positionOffset.z;
        BtlUnit_SetPartsRotate(part, 0.0f, 0.0f, 0.0f);
        BtlUnit_SetPartsRotateOffset(part, 0.0f, 0.0f, 0.0f);
        part->mHitBaseOffset.x = part->mKindPartParams->hitBaseOffset.x;
        part->mHitBaseOffset.y = part->mKindPartParams->hitBaseOffset.y;
        part->mHitOffset.x = 0.0f;
        part->mHitOffset.y = 0.0f;
        part->field_0x1A0 = 0;
    }
    btlDispEntAnime(unit);
    return EVT_RETURN_DONE;
}

//s32 retIndex
USER_FUNC(btlevtcmd_ChangeParty) {
    BattleUnit* unit;
    s32 index, value;

    value = -1;
    index = *event->args;
    unit = BattleChangeParty(_battleWorkPointer);
    if (unit) {
        value = unit->unitId;
    }
    evtSetValue(event, index, value);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z (can be EVTDAT_POINTER_MAX to set current)
USER_FUNC(btlevtcmd_SetPos) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId;
    f32 x, y, z, currX, currY, currZ;
    s32 id, indexZ, indexY, indexX;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    indexX = args[1];
    x = (f32)evtGetValue(event, indexX);
    indexY = args[2];
    y = (f32)evtGetValue(event, indexY);
    indexZ = args[3];
    z = (f32)evtGetValue(event, indexZ);

    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_GetPos(unit, &currX, &currY, &currZ);
    if (indexX == EVTDAT_POINTER_MAX) {
        x = currX;
    }
    if (indexY == EVTDAT_POINTER_MAX) {
        y = currY;
    }
    if (indexZ == EVTDAT_POINTER_MAX) {
        z = currZ;
    }
    BtlUnit_SetPos(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddPos) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_AddPos(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, s32 indexX, s32 indexY, s32 indexZ (can be EVTDAT_POINTER_MAX for noret)
USER_FUNC(btlevtcmd_GetPartsPos) {
    s32* args = event->args;
    s32 btlId;
    s32 id, partId;
    s32 indexX, indexY, indexZ;
    f32 currX, currY, currZ;
    BattleUnitPart* part;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    BattleGetUnitPtr(_battleWorkPointer, id);
    part = BattleGetUnitPartsPtr(id, partId);
    indexX = args[2];
    indexY = args[3];
    indexZ = args[4];
    BtlUnit_GetPartsWorldPos(part, &currX, &currY, &currZ);
    if (indexX != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexX, (s32)currX);
    }
    if (indexY != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexY, (s32)currY);
    }
    if (indexZ != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexZ, (s32)currZ);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetPartsPos) {
    s32* args = event->args;
    s32 btlId;
    f32 x, y, z, currX, currY, currZ;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, partId;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    x = (f32)evtGetValue(event, args[2]);
    y = (f32)evtGetValue(event, args[3]);
    z = (f32)evtGetValue(event, args[4]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BattleGetUnitPartsPtr(id, partId);
    if (part->attributes & 0x10000000) {
        BtlUnit_SetPartsPos(part, x, y, z);
    }
    else {
        BtlUnit_GetPos(unit, &currX, &currY, &currZ);
        x -= currX; y -= currY; z -= currZ;
        BtlUnit_SetPartsOffsetPos(part, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddPartsPos) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    x = (f32)evtGetValue(event, args[2]);
    y = (f32)evtGetValue(event, args[3]);
    z = (f32)evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    if (part->attributes & 0x10000000) {
        BtlUnit_AddPartsPos(part, x, y, z);
    }
    else {
        BtlUnit_AddPartsOffsetPos(part, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetDispOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_SetDispOffset(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetPartsDispOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    BattleUnit* unit;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    x = (f32)evtGetValue(event, args[2]);
    y = (f32)evtGetValue(event, args[3]);
    z = (f32)evtGetValue(event, args[4]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id); //unused variable
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_SetPartsDispOffset(part, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddPartsDispOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    BattleUnit* unit;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    x = (f32)evtGetValue(event, args[2]);
    y = (f32)evtGetValue(event, args[3]);
    z = (f32)evtGetValue(event, args[4]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id); //unused variable
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_AddPartsDispOffset(part, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetTogeOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    if (x != (f32)EVTDAT_POINTER_MAX) {
        unit->togeOffset.x = x;
    }
    if (y != (f32)EVTDAT_POINTER_MAX) {
        unit->togeOffset.y = y;
    }
    if (z != (f32)EVTDAT_POINTER_MAX) {
        unit->togeOffset.z = z;
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 indexX, s32 indexY, s32 indexZ
USER_FUNC(btlevtcmd_GetHomePos) {
    s32* args = event->args;
    s32 btlId;
    s32 indexX, indexY, indexZ;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    indexX = args[1];
    indexY = args[2];
    indexZ = args[3];
    BtlUnit_GetHomePos(unit, &x, &y, &z);
    evtSetValue(event, indexX, (s32)x);
    evtSetValue(event, indexY, (s32)y);
    evtSetValue(event, indexZ, (s32)z);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetHomePos) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_SetHomePos(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddHomePos) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_AddHomePos(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetPartsHomePos) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    x = (f32)evtGetValue(event, args[2]);
    y = (f32)evtGetValue(event, args[3]);
    z = (f32)evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_SetPartsHomePos(part, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, s32 indexX, s32 indexY, s32 indexZ
USER_FUNC(btlevtcmd_GetHitPos) {
    s32* args = event->args;
    f32 x, y, z;
    s32 id, partId;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 indexX, indexY, indexZ;
    s32 btlId;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BattleGetUnitPartsPtr(id, partId);
    indexX = args[2];
    indexY = args[3];
    indexZ = args[4];
    BtlUnit_GetHitPos(unit, part, &x, &y, &z);
    if (indexX != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexX, (s32)x);
    }
    if (indexY != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexY, (s32)y);
    }
    if (indexZ != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexZ, (s32)z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetHitOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    BattleUnit* unit;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    partId = evtGetValue(event, args[1]);
    x = (f32)evtGetValue(event, args[2]);
    y = (f32)evtGetValue(event, args[3]);
    z = (f32)evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_SetHitOffset(unit, part, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetHitCursorOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    BattleUnit* unit;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    partId = evtGetValue(event, args[1]);
    x = (f32)evtGetValue(event, args[2]);
    y = (f32)evtGetValue(event, args[3]);
    z = (f32)evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_SetHitCursorOffset(unit, part, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 retIndex
USER_FUNC(btlevtcmd_GetWidth) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, index, width;

    id = evtGetValue(event, args[0]);
    index = args[1];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    width = BtlUnit_GetWidth(unit);
    evtSetValue(event, index, width);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 retIndex
USER_FUNC(btlevtcmd_GetHeight) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, index, height;

    id = evtGetValue(event, args[0]);
    index = args[1];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    height = BtlUnit_GetHeight(unit);
    evtSetValue(event, index, height);
    return EVT_RETURN_DONE;
}

//s32* battleId, s16* height
USER_FUNC(btlevtcmd_SetHeight) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s16 height;
    s32 btlId, id;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    height = (s16)evtGetValue(event, args[1]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_SetHeight(unit, height); //TODO: make sure extsh
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 retIndex
USER_FUNC(btlevtcmd_GetStatusMg) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, index;

    id = evtGetValue(event, args[0]);
    index = args[1];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    evtSetFloat(event, index, unit->mSizeMultiplier);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* xpos, s32* ypos (can be EVTDAT_POINTER_MAX to not store)
USER_FUNC(btlevtcmd_SetStatusIconOffset) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, btlId, xpos, ypos;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    xpos = evtGetValue(event, args[1]);
    ypos = evtGetValue(event, args[2]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (xpos != EVTDAT_POINTER_MAX) {
        unit->mStatusIconOffset[0] = (s16)xpos;
    }
    if (ypos != EVTDAT_POINTER_MAX) {
        unit->mStatusIconOffset[1] = (s16)ypos;
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* xpos, s32* ypos (can be EVTDAT_POINTER_MAX to not store)
USER_FUNC(btlevtcmd_SetHpGaugeOffset) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, btlId, xpos, ypos;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    xpos = evtGetValue(event, args[1]);
    ypos = evtGetValue(event, args[2]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (xpos != EVTDAT_POINTER_MAX) {
        unit->mHpGaugeOffset[0] = (s16)xpos;
    }
    if (ypos != EVTDAT_POINTER_MAX) {
        unit->mHpGaugeOffset[1] = (s16)ypos;
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32 retX, s32 retY
USER_FUNC(btlevtcmd_GetHpGaugeOffset) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId, indexX, indexY;
    BattleUnit* unit;
    s32 x, y;

    btlId = evtGetValue(event, args[0]);
    indexX = args[1];
    indexY = args[2];
    unit = BattleGetUnitPtr(wp, BattleTransID(event, btlId));
    x = unit->mHpGaugeOffset[0];
    y = unit->mHpGaugeOffset[1];
    if (x != -250000000) {
        evtSetValue(event, indexX, x);
    }
    if (y != -250000000) {
        evtSetValue(event, indexY, y);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, u8* alpha
USER_FUNC(btlevtcmd_SetAlpha) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, btlId, partId;
    s32 alpha;

    btlId = evtGetValue(event, args[0]);
    partId = evtGetValue(event, args[1]);
    alpha = evtGetValue(event, args[2]);
    id = BattleTransID(event, btlId);
    part = BattleGetUnitPartsPtr(id, partId);
    part->color.a = alpha;
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, u8* redIndex, u8* greenIndex, u8* blueIndex
USER_FUNC(btlevtcmd_GetRGB) {
    s32* args = event->args;
    s32 id, partId;
    BattleUnitPart* part;
    s32 indexR, indexG, indexB;

    id = evtGetValue(event, args[0]);
    partId = evtGetValue(event, args[1]);
    id = BattleTransID(event, id);
    part = BattleGetUnitPartsPtr(id, partId);
    indexR = args[2];
    indexG = args[3];
    args = (s32*)args[4];
    evtSetValue(event, indexR, part->color.r);
    evtSetValue(event, indexG, part->color.g);
    evtSetValue(event, (s32)args, part->color.b);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, u8* red, u8* green, u8* blue
USER_FUNC(btlevtcmd_SetRGB) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, btlId, partId;
    s32 r, g, b;

    btlId = evtGetValue(event, args[0]);
    partId = evtGetValue(event, args[1]);
    r = evtGetValue(event, args[2]);
    g = evtGetValue(event, args[3]);
    b = evtGetValue(event, args[4]);
    id = BattleTransID(event, btlId);
    part = BattleGetUnitPartsPtr(id, partId);
    part->color.r = r;
    part->color.g = g;
    part->color.b = b;
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z (can be EVTDAT_POINTER_MAX to skip)
USER_FUNC(btlevtcmd_GetRotate) {
    s32* args = event->args;
    s32 btlId;
    f32 rotateX, rotateY, rotateZ;
    s32 indexX, indexY, indexZ;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    indexX = args[1];
    indexY = args[2];
    indexZ = args[3];
    BtlUnit_GetRotate(unit, &rotateX, &rotateY, &rotateZ);
    if (indexX != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexX, (s32)rotateX);
    }
    if (indexY != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexY, (s32)rotateY);
    }
    if (indexZ != EVTDAT_POINTER_MAX) {
        evtSetValue(event, indexZ, (s32)rotateZ);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z (can be EVTDAT_POINTER_MAX to skip)
USER_FUNC(btlevtcmd_SetRotate) {
    s32* args = event->args;
    BattleUnit* unit;
    f32 x, y, z, currX, currY, currZ;
    s32 id, indexX, indexY, indexZ;
    s32 btlId;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    indexX = args[1];
    x = (f32)evtGetValue(event, indexX);
    indexY = args[2];
    y = (f32)evtGetValue(event, indexY);
    indexZ = args[3];
    z = (f32)evtGetValue(event, indexZ);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_GetRotate(unit, &currX, &currY, &currZ);
    if (indexX == EVTDAT_POINTER_MAX) {
        x = currX;
    }
    if (indexY == EVTDAT_POINTER_MAX) {
        y = currY;
    }
    if (indexZ == EVTDAT_POINTER_MAX) {
        z = currZ;
    }
    BtlUnit_SetRotate(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddRotate) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_AddRotate(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_GetPartsRotate) {
    s32* args = event->args;
    s32 btlId;
    s32 id, partId, indexX, indexY, indexZ;
    BattleUnitPart* part;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, partId);
    indexX = args[2];
    indexY = args[3];
    indexZ = args[4];
    BtlUnit_GetPartsRotate(part, &x, &y, &z);
    evtSetValue(event, indexX, (s32)x);
    evtSetValue(event, indexY, (s32)y);
    evtSetValue(event, indexZ, (s32)z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetPartsRotate) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId, x, y, z;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    x = evtGetValue(event, args[2]);
    y = evtGetValue(event, args[3]);
    z = evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_SetPartsRotate(part, (f32)x, (f32)y, (f32)z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddPartsRotate) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId, x, y, z;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    x = evtGetValue(event, args[2]);
    y = evtGetValue(event, args[3]);
    z = evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_AddPartsRotate(part, (f32)x, (f32)y, (f32)z);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z (can be EVTDAT_POINTER_MAX to skip)
USER_FUNC(btlevtcmd_SetBaseRotate) {
    s32* args = event->args;
    BattleUnit* unit;
    f32 x, y, z, currX, currY, currZ;
    s32 id, indexX, indexY, indexZ;
    s32 btlId;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    indexX = args[1];
    x = (f32)evtGetValue(event, indexX);
    indexY = args[2];
    y = (f32)evtGetValue(event, indexY);
    indexZ = args[3];
    z = (f32)evtGetValue(event, indexZ);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_GetBaseRotate(unit, &currX, &currY, &currZ);
    if (indexX == EVTDAT_POINTER_MAX) {
        x = currX;
    }
    if (indexY == EVTDAT_POINTER_MAX) {
        y = currY;
    }
    if (indexZ == EVTDAT_POINTER_MAX) {
        z = currZ;
    }
    BtlUnit_SetBaseRotate(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z (can be EVTDAT_POINTER_MAX to skip)
USER_FUNC(btlevtcmd_SetPartsBaseRotate) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    f32 currX, currY, currZ;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_GetPartsBaseRotate(part, &currX, &currY, &currZ);
    if (x != (f32)EVTDAT_POINTER_MAX) {
        currX = x;
    }
    if (y != (f32)EVTDAT_POINTER_MAX) {
        currY = y;
    }
    if (z != (f32)EVTDAT_POINTER_MAX) {
        currZ = z;
    }
    BtlUnit_SetPartsBaseRotate(part, currX, currY, currZ);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetRotateOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_SetRotateOffset(unit, x, y, z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetPartsRotateOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId, x, y, z;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    x = evtGetValue(event, args[2]);
    y = evtGetValue(event, args[3]);
    z = evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_SetPartsRotateOffset(part, (f32)x, (f32)y, (f32)z);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddPartsRotateOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId, x, y, z;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    x = evtGetValue(event, args[2]);
    y = evtGetValue(event, args[3]);
    z = evtGetValue(event, args[4]);
    part = BattleGetUnitPartsPtr(id, partId);
    BtlUnit_AddPartsRotateOffset(part, (f32)x, (f32)y, (f32)z);
    return EVT_RETURN_DONE;
}

//s32* battleId
USER_FUNC(btlevtcmd_SetRotateOffsetFromCenterOffset) {
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, *event->args);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_SetRotateOffset(unit, unit->offsetCenter.x, unit->offsetCenter.y, unit->offsetCenter.z);
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetCutBaseOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->cutBaseOffset.x = x;
    unit->cutBaseOffset.y = y;
    unit->cutBaseOffset.z = z;
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetBintaHitOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->bintaHitOffset.x = x;
    unit->bintaHitOffset.y = y;
    unit->bintaHitOffset.z = z;
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetKissHitOffset) {
    s32* args = event->args;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    x = (f32)evtGetValue(event, args[1]);
    y = (f32)evtGetValue(event, args[2]);
    z = (f32)evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->kissHitOffset.x = x;
    unit->kissHitOffset.y = y;
    unit->kissHitOffset.z = z;
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* value
USER_FUNC(btlevtcmd_SetCutWidth) {
    s32 btlId;
    s32 value;
    s32 id;
    BattleUnit* unit;
    s32* args = event->args;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    value = evtGetValue(event, args[1]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->cutWidth = value;
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* value
USER_FUNC(btlevtcmd_SetCutHeight) {
    s32 btlId;
    s32 value;
    s32 id;
    BattleUnit* unit;
    s32* args = event->args;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    value = evtGetValue(event, args[1]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->cutHeight = value;
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z (can be EVTDAT_POINTER_MAX to skip)
USER_FUNC(btlevtcmd_SetPossessionItemOffset) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId;
    s32 id, x, y, z, indexX, indexY, indexZ;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    indexX = args[1];
    x = evtGetValue(event, indexX);
    indexY = args[2];
    y = evtGetValue(event, indexY);
    indexZ = args[3];
    z = evtGetValue(event, indexZ);
    if (indexX != EVTDAT_POINTER_MAX) {
        unit->heldItemOffset.x = (f32)x;
    }
    if (indexY != EVTDAT_POINTER_MAX) {
        unit->heldItemOffset.y = (f32)y;
    }
    if (indexZ != EVTDAT_POINTER_MAX) {
        unit->heldItemOffset.z = (f32)z;
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetBaseScale) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    x = evtGetFloat(event, args[1]);
    y = evtGetFloat(event, args[2]);
    z = evtGetFloat(event, args[3]);
    if (unit) {
        BtlUnit_SetBaseScale(unit, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetPartsBaseScale) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    f32 x, y, z;
    s32 id;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    if (id == -1) return EVT_RETURN_DONE;
    {
        btlId = evtGetValue(event, args[1]);
        part = BattleGetUnitPartsPtr(id, btlId);
        x = evtGetFloat(event, args[2]);
        y = evtGetFloat(event, args[3]);
        z = evtGetFloat(event, args[4]);
        BtlUnit_SetPartsBaseScale(part, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z (can be EVTDAT_POINTER_MAX to skip)
USER_FUNC(btlevtcmd_GetScale) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId;
    s32 id, indexX, indexY, indexZ;
    BattleUnit* unit;
    f32 x, y, z;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    if (id == -1) {
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    indexX = args[1];
    indexY = args[2];
    indexZ = args[3];
    BtlUnit_GetScale(unit, &x, &y, &z);
    if (indexX != EVTDAT_POINTER_MAX) {
        evtSetFloat(event, indexX, x);
    }
    if (indexY != EVTDAT_POINTER_MAX) {
        evtSetFloat(event, indexY, y);
    }
    if (indexZ != EVTDAT_POINTER_MAX) {
        evtSetFloat(event, indexZ, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetScale) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    if (id == -1) return EVT_RETURN_DONE;
    {
        unit = BattleGetUnitPtr(wp, id);
        x = evtGetFloat(event, args[1]);
        y = evtGetFloat(event, args[2]);
        z = evtGetFloat(event, args[3]);
        BtlUnit_SetScale(unit, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddScale) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId;
    BattleUnit* unit;
    f32 x, y, z;
    s32 id;

    btlId = evtGetValue(event, args[0]);

    id = BattleTransID(event, btlId);
    if (id == -1) return EVT_RETURN_DONE;
    {
        unit = BattleGetUnitPtr(wp, id);
        x = evtGetFloat(event, args[1]);
        y = evtGetFloat(event, args[2]);
        z = evtGetFloat(event, args[3]);
        BtlUnit_AddScale(unit, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_SetPartsScale) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    if (id == -1) {
        return EVT_RETURN_DONE;
    }
    { //TODO: un-hardcode?
        partId = evtGetValue(event, args[1]);
        part = BattleGetUnitPartsPtr(id, partId);
        x = evtGetFloat(event, args[2]);
        y = evtGetFloat(event, args[3]);
        z = evtGetFloat(event, args[4]);
        BtlUnit_SetPartsScale(part, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* partId, f32* x, f32* y, f32* z
USER_FUNC(btlevtcmd_AddPartsScale) {
    s32* args = event->args;
    s32 btlId;
    BattleUnitPart* part;
    s32 id, partId;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);

    id = BattleTransID(event, id);
    if (id == -1) {
        return EVT_RETURN_DONE;
    }
    { //TODO: un-hardcode?
        partId = evtGetValue(event, args[1]);
        part = BattleGetUnitPartsPtr(id, partId);
        x = evtGetFloat(event, args[2]);
        y = evtGetFloat(event, args[3]);
        z = evtGetFloat(event, args[4]);
        BtlUnit_AddPartsScale(part, x, y, z);
    }
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* retIndex
USER_FUNC(btlevtcmd_GetHp) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, args[1], unit->currentHp);
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* retIndex
USER_FUNC(btlevtcmd_GetFp) { //1:1
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, index;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    index = args[1];
    evtSetValue(event, index, BtlUnit_GetFp(unit));
    return EVT_RETURN_DONE;
}

//s32* battleId, s32* retIndex
USER_FUNC(btlevtcmd_GetMaxHp) { //1:1
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, args[1], unit->maxHp);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetMaxFp) { //1:1
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, index;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    index = args[1];
    evtSetValue(event, index, BtlUnit_GetMaxFp(unit));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetHp) { //1:1
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    f32 value; //TODO: rename
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    unit->currentHp = (s16)evtGetValue(event, args[1]);
    unit->hpGauge.field_0xC = unit->currentHp;
    unit->hpGauge.field_0x10 = unit->currentHp;
    value = (f32)unit->currentHp / (f32)unit->maxHp;
    unit->hpGauge.field_0x18 = value;
    unit->hpGauge.field_0x14 = value;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetFp) { //1:1
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, value;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    value = evtGetValue(event, args[1]);
    BtlUnit_SetFp(unit, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetMaxFp) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, value;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    value = evtGetValue(event, args[1]);
    BtlUnit_SetMaxFp(unit, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetSwallowParam) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;
    s32 value;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    value = evtGetValue(event, args[1]);
    if (unit) {
        unit->swallowRate = value;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetSwallowAttribute) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;
    s32 value;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    value = (u8)evtGetValue(event, args[1]);
    if (unit) {
        unit->swallowAttribute = value;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetMaxMoveCount) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;
    s8 max;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    unit->maxMoveCount = (u8)evtGetValue(event, args[1]);
    if (unit->movesRemaining > (s8)unit->maxMoveCount) {
        unit->movesRemaining = unit->maxMoveCount;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetDamagePartsId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, args[1], unit->currentTarget->mKindPartParams->partNum);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetHpDamage) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, args[1], unit->hpDamageTaken);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetFpDamage) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, args[1], unit->fpDamageTaken);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetHpDamageCount) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) { //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtSetValue(event, args[1], unit->hpDamageCount);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_RecoverHp) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, hp;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) {  //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtGetValue(event, args[1]); //unused, debug?
    hp = evtGetValue(event, args[2]);
    if (!(unit->mAttributeFlags & kUnk_ImmageToOHKO)) {
        unit->hpGauge.field_0xC = unit->currentHp;
        BtlUnit_RecoverHp(unit, hp);
        unit->hpGauge.field_0x10 = unit->currentHp;
        unit->hpGauge.field_0x4 = unit->hpGauge.field_0x6;
        unit->hpGauge.field_0x8 = unit->hpGauge.field_0xA;
        unit->hpGauge.field_0x2 |= 1;
    }
    else {
        BtlUnit_RecoverHp(unit, hp);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_RecoverFp) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, value;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    if (id == -1) {  //TODO: un-hardcode?
        return EVT_RETURN_DONE;
    }
    unit = BattleGetUnitPtr(wp, id);
    evtGetValue(event, args[1]); //unused, debug?
    value = evtGetValue(event, args[2]);
    BtlUnit_RecoverFp(unit, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetOverTurnCount) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId, id, index;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, unit->flippedTurns);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetOverTurnCount) {
    s32 id;
    s32* args = event->args;
    s32 btlId;
    s32 value;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    value = evtGetValue(event, args[1]);
    { BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id); unit->flippedTurns = value; }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetUnitWork) {
    s32* args = event->args;
    s32 btlId, id, i, index;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    i = evtGetValue(event, args[1]);
    index = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, unit->work[i]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetUnitWork) {
    s32* args = event->args;
    s32 btlId, id, value, index;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = evtGetValue(event, args[1]);
    value = evtGetValue(event, args[2]);
    {
        s32* p = (s32*)BattleGetUnitPtr(_battleWorkPointer, id) + index;
        p[0x214/4] = value;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AddUnitWork) {
    s32* args = event->args;
    s32 btlId, id, value, index;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = evtGetValue(event, args[1]);
    value = evtGetValue(event, args[2]);
    {
        s32* p = (s32*)BattleGetUnitPtr(_battleWorkPointer, id) + index;
        p[0x214/4] += value;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetUnitWorkFloat) {
    s32* args = event->args;
    s32 btlId, id, i, index;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    i = evtGetValue(event, args[1]);
    index = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetFloat(event, index, *(f32*)&unit->work[i]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetUnitWorkFloat) {
    s32* args = event->args;
    s32 btlId, id, index;
    f32 value;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = evtGetValue(event, args[1]);
    value = evtGetFloat(event, args[2]);
    *(f32*)&BattleGetUnitPtr(_battleWorkPointer, id)->work[index] = value;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetPartsWork) {
    s32* args = event->args;
    s32 btlId, id, partId, i, index;
    BattleUnitPart* part;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    i = evtGetValue(event, args[2]);
    index = args[3];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BtlUnit_GetPartsPtr(unit, partId);
    evtSetValue(event, index, part->work[i]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsWork) {
    s32* args = event->args;
    s32 btlId, id, partId, index, value;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    index = evtGetValue(event, args[2]);
    value = evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    {
        u8* p = (u8*)BtlUnit_GetPartsPtr(unit, partId) + index * 4;
        *(s32*)(p + 0x130) = value;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetDamage) {
    s32* args = event->args;
    s32 btlId, id, index, value;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    index = args[1];
    if (unit) {
        evtSetValue(event, index, BtlUnit_GetHitDamage(unit));
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetTotalDamage) {
    s32* args = event->args;
    s32 btlId, id, index, value;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    index = args[1];
    if (unit) {
        evtSetValue(event, index, BtlUnit_GetTotalHitDamage(unit));
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetDamageCode) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId, id, index;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, (s32)(u8)unit->damageCode); //TODO: double check this cast
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckDamageCode) {
    s32* args = event->args;
    s32 btlId, id, mask, index; BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    mask = args[1];
    index = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id); if (unit->damageCode & mask) {
        evtSetValue(event, index, 1);
    }
    else {
        evtSetValue(event, index, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StartAvoid) {
    s32* args = event->args;
    s32 btlId, id, damageCode;
    EffectEntry* entry;
    BattleUnit* unit;
    Vec pos;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    damageCode = args[1] | 0x100;
    if ((u8)damageCode == 0x26) {
        BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
        if (pos.y < 85.0f) {
            pos.y += 50.0f;
        }
        else {
            pos.y += -50.0f;
        }
        pos.x -= 45.0f;
        entry = effNiceEntry(6, pos.x, pos.y, pos.z);
        ((NiceEffectWork*)entry->userdata)->field_0x1C = 0.75f;
    }
    unit->damagePattern = 0;
    BattleRunHitEvent(unit, damageCode);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_RunHitEventDirect) {
    s32* args = event->args;
    void* code;
    BattleUnit* unit;
    s32 btlId, id, damageCode;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    damageCode = args[1];
    code = (void*)evtGetValue(event, args[2]);
    unit->damagePattern = evtGetValue(event, args[3]);
    BattleRunHitEventDirect(unit, damageCode | 0x100, code);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckDamagePattern) {
    s32* args = event->args;
    s32 btlId, id, index;
    u32 pattern, dp;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    pattern = args[1];
    index = args[2];
    dp = BattleGetUnitPtr(_battleWorkPointer, id)->damagePattern;
    if (dp == pattern) {
        evtSetValue(event, index, 1);
    }
    else {
        evtSetValue(event, index, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckSpace) { //TODO: probably wrong
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 boundX, boundY, boundZ;
    s32 baseX, baseY, baseZ;
    BattleUnit* unit;
    s32 index, i;
    f32 x, y, z;
    s32 ix, iy, iz;
    BOOL found;

    index = args[0];
    baseX = evtGetValue(event, args[1]);
    baseY = evtGetValue(event, args[2]);
    baseZ = evtGetValue(event, args[3]);
    boundX = evtGetValue(event, args[4]);
    boundY = evtGetValue(event, args[5]);
    boundZ = evtGetValue(event, args[6]);
    for (i = 0; i < 64; ++i) {
        found = FALSE;
        unit = BattleGetUnitPtr(wp, i);
        if (unit && UNIT_ALLIANCE_PARTY) {
            BtlUnit_GetHomePos(unit, &x, &y, &z);
            ix = x; iy = y; iz = z;
            if (boundX) {
                if (abs(ix - baseX) < boundX) {
                    found = TRUE;
                }
            }
            if (boundY) {
                if (abs(iy - baseY) < boundY) {
                    found = TRUE;
                }
            }
            if (boundZ) {
                if (abs(iz - baseZ) < boundZ) {
                    found = TRUE;
                }
            }
            if (found) {
                evtSetValue(event, index, i);
                return EVT_RETURN_DONE;
            }
        }
    }
    evtSetValue(event, index, -1);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetEnemyBelong) {
    s32* args = event->args;
    s32 btlId, id, index, value;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    value = BtlUnit_GetEnemyBelong(unit);
    evtSetValue(event, index, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetFriendBelong) {
    s32* args = event->args;
    s32 btlId, id, index;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, unit->mAlliance);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetProtectId) {
    s32* args = event->args;
    s32 btlId, id, index;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, unit->protectId);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetUnitKind) {
    s32* args = event->args;
    s32 btlId, id, index;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, unit->currentKind);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetPartnerId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit, * partner;
    s32 btlId, id, index;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(wp, id);
    partner = BattleGetPartnerPtr(wp, unit);
    if (partner) {
        evtSetValue(event, index, partner->unitId);
    }
    else {
        evtSetValue(event, index, -1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetMarioId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId, id, index, alliance;
    BattleUnit* unit;
    int i;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    alliance = BattleGetUnitPtr(wp, id)->mAlliance;
    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit && unit->mAlliance == alliance && unit->currentKind == UNIT_MARIO) {
            break;
        }
    }
    if (i >= 64) {
        evtSetValue(event, index, -1);
    }
    else {
        evtSetValue(event, index, unit->unitId);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetPartyId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId, id, index, alliance, kind;
    BattleUnit* unit;
    int i;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    alliance = BattleGetUnitPtr(wp, id)->mAlliance;
    for (i = 0; i < 64; i++) {
        unit = BattleGetUnitPtr(wp, i);
        if (unit && unit->mAlliance == alliance) {
            kind = unit->currentKind;
            if (kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
                break;
            }
        }
    }
    if (i >= 64) {
        evtSetValue(event, index, -1);
    }
    else {
        evtSetValue(event, index, unit->unitId);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetBodyId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId, id, index, value;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(wp, id);
    value = BtlUnit_GetBodyPartsId(unit);
    evtSetValue(event, index, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetUnitId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId, id, index;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(wp, id);
    if (unit && (unit->flags & 0x80000000)) {
        unit = NULL;
    }
    if (unit) {
        evtSetValue(event, index, id);
    }
    else {
        evtSetValue(event, index, -1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetPartyTechLv) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 btlId, id, index, value, i;
    BattleUnitType kind;
    PouchPartyData* party;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    kind = BattleGetUnitPtr(wp, id)->currentKind;
    value = 0;
    if (kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
        i = BattleTransPartyId(kind);
        party = &pouchGetPtr()->partyData[i];
        value = party->techLevel;
    }
    evtSetValue(event, index, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CalculateFaceDirection) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    f32 thisX, thisY, thisZ;
    f32 targetX, targetY, targetZ;
    f32 offsetX, offsetY, offsetZ;
    f32 localX, localY, localZ;
    f32 thisOffsetX, thisOffsetY, thisOffsetZ;
    f32 calculate;
    BattleUnit *thisUnit, *targetUnit;
    s32 thisId, thisPartId;
    s32 targetId, targetPartId;
    s32 btlId, flags, index, value, tid;
    BattleUnitPart* thisPart = NULL;
    BattleUnitPart* targetPart = NULL;

    btlId = evtGetValue(event, args[0]);
    thisId = BattleTransID(event, btlId);
    thisPartId = evtGetValue(event, args[1]);
    targetId = evtGetValue(event, args[2]);
    tid = targetId;
    targetPartId = evtGetValue(event, args[3]);
    flags = args[4];
    index = args[5];

    if (!(flags & 9)) {
        tid = BattleTransID(event, targetId);
    }

    thisUnit = BattleGetUnitPtr(_battleWorkPointer, thisId);
    if (thisPartId != -1) {
        thisPart = BtlUnit_GetPartsPtr(thisUnit, thisPartId);
    }

    if (flags & 0x10) {
        targetUnit = BattleGetUnitPtr(_battleWorkPointer, tid);
        if (targetPartId != -1) {
            targetPart = BtlUnit_GetPartsPtr(targetUnit, targetPartId);
        }
    }

    value = thisUnit->faceDirection;
    if (thisPart) {
        value = thisPart->faceDirection;
    }

    if (flags & 4) {
        value = wp->alliances[thisUnit->mAlliance].attackDirection;
    }

    if (flags & 8) {
        value = thisUnit->moveDirection;
        if (thisPart) {
            value = thisPart->moveDirection;
        }
    }

    if (flags & 0x10) {
        BtlUnit_GetPos(thisUnit, &thisX, &thisY, &thisZ);
        if (thisPart) {
            if (thisPart->attributes & 0x10000000) {
                BtlUnit_GetPartsPos(thisPart, &thisX, &thisY, &thisZ);
            }
            else {
                BtlUnit_GetPartsOffsetPos(thisPart, &offsetX, &offsetY, &offsetZ);
                thisX += offsetX;
            }
        }

        BtlUnit_GetPos(targetUnit, &targetX, &targetY, &targetZ);
        if (targetPart) {
            if (targetPart->attributes & 0x10000000) {
                BtlUnit_GetPartsPos(targetPart, &targetX, &targetY, &targetZ);
            }
            else {
                BtlUnit_GetPartsOffsetPos(targetPart, &offsetX, &offsetY, &offsetZ);
                targetX += offsetX;
            }
        }

        calculate = targetX - thisX;
        if (calculate > 0.0f) {
            value = 1;
        }
        else if (calculate < 0.0f) {
            value = -1;
        }
    }

    if (flags & 1) {
        BtlUnit_GetPos(thisUnit, &localX, &localY, &localZ);
        if (thisPart) {
            if (thisPart->attributes & 0x10000000) {
                BtlUnit_GetPartsPos(thisPart, &localX, &localY, &localZ);
            }
            else {
                BtlUnit_GetPartsOffsetPos(thisPart, &thisOffsetX, &thisOffsetY, &thisOffsetZ);
                localX += thisOffsetX;
            }
        }
        calculate = (f32)targetId - localX;
        if (calculate > 0.0f) {
            value = 1;
        }
        else if (calculate < 0.0f) {
            value = -1;
        }
    }
    if (flags & 0x100) {
        value *= -1;
    }
    evtSetValue(event, index, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetFaceDirection) {
    s32* args = event->args;
    s32 btlId, id, index;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    evtSetValue(event, index, unit->faceDirection);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ChangeFaceDirection) {
    s32 id;
    s32* args = event->args;
    s32 btlId;
    s32 value;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    value = evtGetValue(event, args[1]);
    { BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id); unit->faceDirection = value; }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ChangePartsFaceDirection) {
    s32* args = event->args;
    s32 btlId, id, partId;
    s32 value;
    BattleUnitPart* part;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    value = evtGetValue(event, args[2]);
    part = BattleGetUnitPartsPtr(id, partId);
    part->faceDirection = value;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ResetFaceDirection) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id;

    btlId = evtGetValue(event, *event->args);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, btlId));
    unit->faceDirection = wp->alliances[unit->mAlliance].attackDirection;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckAttribute) {
    s32* args = event->args;
    s32 btlId, id, mask, index; BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    mask = args[1];
    index = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id); if (unit->mAttributeFlags & mask) {
        evtSetValue(event, index, 1);
    }
    else {
        evtSetValue(event, index, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OnAttribute) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId, id, mask;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    mask = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->mAttributeFlags |= mask;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OffAttribute) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId, id, mask;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    mask = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->mAttributeFlags = unit->mAttributeFlags & ~mask;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckPartsAttribute) {
    s32* args = event->args;
    s32 btlId, id, partId, index, mask;
    BattleUnit* unit;
    BattleUnitPart* part;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    mask = args[2];
    index = args[3];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BtlUnit_GetPartsPtr(unit, partId);
    if (part->attributes & mask) {
        evtSetValue(event, index, 1);
    }
    else {
        evtSetValue(event, index, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OnPartsAttribute) {
    s32* args = event->args;
    s32 btlId, id, partId, mask;
    BattleUnitPart* part;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    mask = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BtlUnit_GetPartsPtr(unit, partId);
    part->attributes |= mask;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OffPartsAttribute) {
    s32* args = event->args;
    s32 btlId, id, partId, mask;
    BattleUnitPart* part;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    mask = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BtlUnit_GetPartsPtr(unit, partId);
    part->attributes = ~mask & part->attributes;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckPartsCounterAttribute) {
    s32* args = event->args;
    s32 btlId, id, partId, index, mask;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    mask = args[2];
    index = args[3];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (mask & BtlUnit_GetPartsPtr(unit, partId)->counterAttributes) {
        evtSetValue(event, index, 1);
    }
    else {
        evtSetValue(event, index, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OnPartsCounterAttribute) {
    s32* args = event->args;
    s32 btlId, id, partId, mask;
    BattleUnitPart* part;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    mask = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BtlUnit_GetPartsPtr(unit, partId);
    part->counterAttributes |= mask;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OffPartsCounterAttribute) {
    s32* args = event->args;
    s32 btlId, id, partId, mask;
    BattleUnitPart* part;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    mask = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BtlUnit_GetPartsPtr(unit, partId);
    part->counterAttributes = part->counterAttributes & ~mask;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsBlur) {
    s32* args = event->args;
    s32 btlId, id, partId;
    u8 color0, color1, color2, color3, color4, color5, color6, color7;
    BattleUnit* unit;
    BattleUnitPart* part;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    color0 = (u8)evtGetValue(event, args[2]);
    color1 = (u8)evtGetValue(event, args[3]);
    color2 = (u8)evtGetValue(event, args[4]);
    color3 = (u8)evtGetValue(event, args[5]);
    color4 = (u8)evtGetValue(event, args[6]);
    color5 = (u8)evtGetValue(event, args[7]);
    color6 = (u8)evtGetValue(event, args[8]);
    color7 = (u8)evtGetValue(event, args[9]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    part = BtlUnit_GetPartsPtr(unit, partId);
    part->blurWork.color[0] = color0;
    part->blurWork.color[1] = color1;
    part->blurWork.color[2] = color2;
    part->blurWork.color[3] = color3;
    part->blurWork.color[4] = color4;
    part->blurWork.color[5] = color5;
    part->blurWork.color[6] = color6;
    part->blurWork.color[7] = color7;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OnToken) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId, id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->mTokenFlags = args[1] | unit->mTokenFlags;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OffToken) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId, id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    unit->mTokenFlags &= ~args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckToken) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 btlId, id, index;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    index = args[2];
    if (args[1] & unit->mTokenFlags) {
        evtSetValue(event, index, 1);
    }
    else {
        evtSetValue(event, index, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetRegistStatus) {
    s32* args = event->args;
    BattleVulnerableStatus* status;
    s32 btlId, id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    status = (BattleVulnerableStatus*)evtGetValue(event, args[1]);
    BattleGetUnitPtr(_battleWorkPointer, id)->vulnStatus = status;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckCommandUnit) {
    s32* args = event->args;
    s32 btlId, id, index;
    BattleUnitType kind;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    kind = BattleGetUnitPtr(_battleWorkPointer, id)->currentKind;
    index = args[1];
    if (kind == UNIT_MARIO || kind >= TYPE_PARTNER_MIN && kind < TYPE_PARTNER_MAX) {
        evtSetValue(event, index, 1);
    }
    else {
        evtSetValue(event, index, 0);
    }
    return EVT_RETURN_DONE;
}

void BattleStoreExp(BattleWork* wp, s32 exp);
void BattleStoreCoin(BattleWork* wp, s32 coin);
s32 BtlUnit_GetExp(BattleUnit* unit);
s32 BtlUnit_GetCoin(BattleUnit* unit);

USER_FUNC(btlevtcmd_ChangeKind) {
    s32 btlId, id, kind;
    s32* args = event->args;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    BattleGetUnitPtr(_battleWorkPointer, id)->currentKind = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsDefenceTable) {
    s32* args = event->args;
    s32 btlId, id, partId, table;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    table = evtGetValue(event, args[2]);
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, id), partId)->defense = (BattleUnitDefense*)table;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsDefenceAttrTable) {
    s32* args = event->args;
    s32 btlId, id, partId, table;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    partId = evtGetValue(event, args[1]);
    table = evtGetValue(event, args[2]);
    BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, id), partId)->defenseAttr = (BattleUnitDefenseAttr*)table;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ChangeDataTable) {
    s32* args = event->args;
    s32 btlId, id;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    args = (s32*)args[1];
    BattleGetUnitPtr(_battleWorkPointer, id)->dataTable = (BattleDataEntry*)args;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetBackItem) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    NpcBattleInfo* info;
    ItemType item;
    s32 btlId, i;

    btlId = evtGetValue(event, args[0]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, btlId));
    if ((unit->flags & 0x40000000) && (item = unit->heldItem) != 0) {
        info = wp->fbatInfo->setup;
        for (i = 0; i < 8; i++) {
            if (info->recoveredItems[i] == 0) {
                break;
            }
        }
        info->recoveredItems[i] = item;
        unit->heldItem = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetExp) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, index, val;

    id = evtGetValue(event, args[0]);
    index = args[1];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    val = BtlUnit_GetExp(unit);
    evtSetValue(event, index, val);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StoreExp) {
    s32 val = evtGetValue(event, event->args[0]);
    BattleStoreExp(_battleWorkPointer, val);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetCoin) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, index, val;

    id = evtGetValue(event, args[0]);
    index = args[1];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    val = BtlUnit_GetCoin(unit);
    evtSetValue(event, index, val);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StoreCoin) {
    s32 val = evtGetValue(event, event->args[0]);
    BattleStoreCoin(_battleWorkPointer, val);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetMoveSpeed) {
    s32* args = event->args;
    s32 btlId, id;
    f32 speed;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    speed = evtGetFloat(event, args[1]);
    BtlUnit_SetMoveSpeed(BattleGetUnitPtr(_battleWorkPointer, id), speed);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetJumpSpeed) {
    s32* args = event->args;
    s32 btlId, id;
    f32 speed;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    speed = evtGetFloat(event, args[1]);
    BtlUnit_SetJumpSpeed(BattleGetUnitPtr(_battleWorkPointer, id), speed);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetFallAccel) {
    s32* args = event->args;
    s32 btlId, id;
    f32 accel;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    accel = evtGetFloat(event, args[1]);
    BtlUnit_SetFallAccel(BattleGetUnitPtr(_battleWorkPointer, id), accel);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_JumpSetting) {
    s32 btlId, id, frames;
    s32* args = event->args;
    f32 speed, accel;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    frames = evtGetValue(event, args[1]);
    speed = evtGetFloat(event, args[2]);
    accel = evtGetFloat(event, args[3]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    *(s32*)unit->field_0x168 = frames;
    unit->mMoveSpeedXZ = speed;
    unit->mFallAccel = accel;
    return EVT_RETURN_DONE;
}

/* movers begin (half_B) */
void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);
f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z);
void BtlUnit_LoadSeMode(s32 mode, s32 kind, void* table, void* work);
void _UnitMoveSoundControl(BattleUnit* unit);
void _UnitMoveSoundControlEnd(BattleUnit* unit);
#define BEC_MVFRAME(u) (*(s32*)(u)->field_0x168)
#define BEC_MVDIST(u) (*(f32*)(u)->field_0x17C)
#define BEC_SNDNAME(u, off) (*(s32*)&(u)->field_0x186[(off) - 0x186])

static inline Vec becMvVecA(f32 x, f32 y, f32 z) {
    Vec v = {0.0f, 0.0f, 0.0f};
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static inline Vec becMvVecB(f32 x, f32 y, f32 z) {
    Vec v = {0.0f, 0.0f, 0.0f};
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

USER_FUNC(btlevtcmd_JumpPosition) {
    s32 id;
    s32* args = event->args;
    BattleUnit* unit;
    s32 kind, frames;
    f32 tx, ty, tz;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = (f32)evtGetValue(event, args[1]);
    ty = (f32)evtGetValue(event, args[2]);
    tz = (f32)evtGetValue(event, args[3]);
    frames = evtGetValue(event, args[4]);
    kind = evtGetValue(event, args[5]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        event->blocked = 1;
        if (frames) {
            BEC_MVFRAME(unit) = frames;
        }
        BtlUnit_SetMoveTargetPos(unit, tx, ty, tz);
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetMoveCurrentPos(unit, x, y, z);
        unit->mMoveDirection = angleABf(x, z, tx, tz);
        BEC_MVDIST(unit) = distABf(x, z, tx, tz);
        if (tx - x > 0.0f) {
            unit->moveDirection = 1;
        }
        else if (tx - x < 0.0f) {
            unit->moveDirection = -1;
        }
        y = ty - y;
        if (BEC_MVFRAME(unit) == 0) {
            BEC_MVFRAME(unit) = BEC_MVDIST(unit) / unit->mMoveSpeedXZ;
            BEC_MVDIST(unit) = BEC_MVDIST(unit) - BEC_MVFRAME(unit) * unit->mMoveSpeedXZ;
        }
        else {
            unit->mMoveSpeedXZ = BEC_MVDIST(unit) / BEC_MVFRAME(unit);
            BEC_MVDIST(unit) = BEC_MVDIST(unit) - BEC_MVFRAME(unit) * unit->mMoveSpeedXZ;
        }
        if (BEC_MVFRAME(unit) == 0) {
            return EVT_RETURN_DONE;
        }
        unit->mMoveSpeedY = y / BEC_MVFRAME(unit) + (unit->mFallAccel * BEC_MVFRAME(unit)) / 2.0f;
        unit->mMoveSpeedXZ = unit->mMoveSpeedXZ + BEC_MVDIST(unit) / BEC_MVFRAME(unit);
        BtlUnit_LoadSeMode(2, kind, (u8*)unit + 0x1C0, (u8*)unit + 0x188);
        if (BEC_SNDNAME(unit, 0x188)) {
            Vec pos = becMvVecA(unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
            psndSFXOn_3D((const char*)BEC_SNDNAME(unit, 0x188), &pos);
        }
    }
    unit->mMoveCurrentPos.y += unit->mMoveSpeedY;
    unit->mMoveSpeedY -= unit->mFallAccel;
    if (unit->mMoveSpeedY < 0.0f && unit->mMoveCurrentPos.y < unit->mMoveTargetPos.y) {
        unit->mMoveCurrentPos.y = unit->mMoveTargetPos.y;
    }
    btlMovePos(unit->mMoveSpeedXZ, unit->mMoveDirection, &unit->mMoveCurrentPos.x, &unit->mMoveCurrentPos.z);
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    BEC_MVFRAME(unit)--;
    if (BEC_MVFRAME(unit) <= 0) {
        BtlUnit_SetPos(unit, unit->mMoveTargetPos.x, unit->mMoveTargetPos.y, unit->mMoveTargetPos.z);
        if (BEC_SNDNAME(unit, 0x18C)) {
            Vec pos = becMvVecB(unit->mMoveTargetPos.x, unit->mMoveTargetPos.y, unit->mMoveTargetPos.z);
            psndSFXOn_3D((const char*)BEC_SNDNAME(unit, 0x18C), &pos);
        }
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(btlevtcmd_JumpContinue) {
    BattleUnit* unit;
    s32 id;
    f32 x, y, z;
    f32 h;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        event->blocked = 1;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetMoveCurrentPos(unit, x, y, z);
    }
    unit->mMoveCurrentPos.y += unit->mMoveSpeedY;
    unit->mMoveSpeedY -= unit->mFallAccel;
    btlMovePos(unit->mMoveSpeedXZ, unit->mMoveDirection, &unit->mMoveCurrentPos.x, &unit->mMoveCurrentPos.z);
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    h = BattleGetFloorHeight(_battleWorkPointer, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    if (unit->mMoveCurrentPos.y < h) {
        unit->mMoveCurrentPos.y = h;
        BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(btlevtcmd_FallPosition) {
    s32 id, frames;
    s32* args = event->args;
    BattleUnit* unit;
    f32 tx, ty, tz;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = (f32)evtGetValue(event, args[1]);
    ty = (f32)evtGetValue(event, args[2]);
    tz = (f32)evtGetValue(event, args[3]);
    frames = evtGetValue(event, args[4]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        event->blocked = 1;
        BEC_MVFRAME(unit) = frames;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetMoveCurrentPos(unit, x, y, z);
        BtlUnit_SetMoveTargetPos(unit, tx, ty, tz);
        unit->mMoveDirection = angleABf(x, z, tx, tz);
        BEC_MVDIST(unit) = distABf(x, z, tx, tz);
        if (tx - x > 0.0f) {
            unit->moveDirection = 1;
        }
        else if (tx - x < 0.0f) {
            unit->moveDirection = -1;
        }
        y = ty - y;
        if (BEC_MVFRAME(unit) == 0) {
            if (unit->mMoveSpeedXZ == 0.0f) {
                unit->mMoveSpeedXZ = 1.0f;
            }
            BEC_MVFRAME(unit) = BEC_MVDIST(unit) / unit->mMoveSpeedXZ;
            if (BEC_MVFRAME(unit) == 0) {
                BEC_MVFRAME(unit) = 1;
            }
        }
        else {
            unit->mMoveSpeedXZ = BEC_MVDIST(unit) / BEC_MVFRAME(unit);
        }
        unit->mMoveSpeedY = 0.0f;
        unit->mFallAccel = (y / BEC_MVFRAME(unit) - unit->mMoveSpeedY) / (-BEC_MVFRAME(unit) / 2.0f);
    }
    unit->mMoveCurrentPos.y += unit->mMoveSpeedY;
    unit->mMoveSpeedY -= unit->mFallAccel;
    btlMovePos(unit->mMoveSpeedXZ, unit->mMoveDirection, &unit->mMoveCurrentPos.x, &unit->mMoveCurrentPos.z);
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    BEC_MVFRAME(unit)--;
    if (BEC_MVFRAME(unit) <= 0) {
        BtlUnit_SetPos(unit, unit->mMoveTargetPos.x, unit->mMoveTargetPos.y, unit->mMoveTargetPos.z);
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(btlevtcmd_MovePosition) {
    s32 id;
    s32* args = event->args;
    BattleUnit* unit;
    s32 kind, mode, frames;
    f32 tx, ty, tz;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = (f32)evtGetValue(event, args[1]);
    ty = (f32)evtGetValue(event, args[2]);
    tz = (f32)evtGetValue(event, args[3]);
    frames = evtGetValue(event, args[4]);
    kind = evtGetValue(event, args[5]);
    mode = evtGetValue(event, args[6]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        event->blocked = 1;
        BEC_MVFRAME(unit) = frames;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetMoveCurrentPos(unit, x, y, z);
        BtlUnit_SetMoveTargetPos(unit, tx, ty, tz);
        unit->mMoveDirection = angleABf(x, z, tx, tz);
        BEC_MVDIST(unit) = distABf(x, z, tx, tz);
        if (tx - x > 0.0f) {
            unit->moveDirection = 1;
        }
        else if (tx - x < 0.0f) {
            unit->moveDirection = -1;
        }
        if (BEC_MVFRAME(unit) == 0) {
            BEC_MVFRAME(unit) = BEC_MVDIST(unit) / unit->mMoveSpeedXZ;
            if (BEC_MVFRAME(unit) == 0) {
                BEC_MVFRAME(unit) = 1;
            }
            unit->mMoveSpeedXZ = unit->mMoveSpeedXZ + (BEC_MVDIST(unit) - BEC_MVFRAME(unit) * unit->mMoveSpeedXZ) / BEC_MVFRAME(unit);
        }
        else {
            unit->mMoveSpeedXZ = BEC_MVDIST(unit) / BEC_MVFRAME(unit);
        }
        BtlUnit_LoadSeMode(mode, kind, (u8*)unit + 0x1C0, (u8*)unit + 0x188);
    }
    btlMovePos(unit->mMoveSpeedXZ, unit->mMoveDirection, &unit->mMoveCurrentPos.x, &unit->mMoveCurrentPos.z);
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    BEC_MVFRAME(unit)--;
    if (BEC_MVFRAME(unit) <= 0) {
        BtlUnit_SetPos(unit, unit->mMoveTargetPos.x, unit->mMoveTargetPos.y, unit->mMoveTargetPos.z);
        _UnitMoveSoundControlEnd(unit);
        return EVT_RETURN_YIELD;
    }
    _UnitMoveSoundControl(unit);
    return EVT_RETURN_BLOCK;
}

USER_FUNC(btlevtcmd_GetMoveFrame) {
    s32 id;
    s32* args = event->args;
    BattleUnit* unit;
    s32 frame, index;
    f32 tx, tz, speed, dist;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = (f32)evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    tz = (f32)evtGetValue(event, args[3]);
    speed = evtGetFloat(event, args[4]);
    index = args[5];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    dist = distABf(x, z, tx, tz);
    if (!speed) {
        speed = unit->mMoveSpeedXZ;
        if (!speed) {
            speed = 1.0f;
        }
    }
    frame = dist / speed;
    if (dist - frame * speed > 0.0f) {
        frame++;
    }
    if (frame == 0) {
        frame = 1;
    }
    if (index != -250000000) {
        evtSetValue(event, index, frame);
    }
    return EVT_RETURN_DONE;
}
extern int __float_nan[];

static inline s32 bec_fpclassifyf(f32 x) {
    switch (*(s32*)&x & 0x7F800000) {
    case 0x7F800000:
        if (*(s32*)&x & 0x007FFFFF) {
            return 1;
        }
        else {
            return 2;
        }
        break;
    case 0:
        if (*(s32*)&x & 0x007FFFFF) {
            return 5;
        }
        else {
            return 3;
        }
        break;
    default:
        return 4;
    }
}

static inline f32 bec_sqrtf(f32 x) {
    if (x > 0.0f) {
        f64 guess = __frsqrte(x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        guess = 0.5 * guess * (3.0 - guess * guess * x);
        return x * guess;
    }
    else if (x < 0.0) {
        return *(f32*)__float_nan;
    }
    else if (bec_fpclassifyf(x) == 1) {
        return *(f32*)__float_nan;
    }
    return x;
}

f32 intpl_sub(s32 type, f32 start, f32 end, s32 cur, s32 max);
f32 sinfd(f32 degrees);
f32 cosfd(f32 degrees);
#define BEC_MVCNT(u) (*(f32*)((u)->field_0x17C + 4))

USER_FUNC(btlevtcmd_EllipseMovePosition) {
    s32 width, mode;
    s32* args = event->args;
    BattleUnit* unit;
    s32 frames, id;
    f32 tx, ty, tz;
    f32 cx, cz, w, r, ang, t;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = (f32)evtGetValue(event, args[1]);
    ty = (f32)evtGetValue(event, args[2]);
    tz = (f32)evtGetValue(event, args[3]);
    frames = evtGetValue(event, args[4]);
    width = evtGetValue(event, args[5]);
    mode = evtGetValue(event, args[6]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        event->blocked = 1;
        BEC_MVFRAME(unit) = frames;
        BtlUnit_GetPos(unit, &x, &y, &z);
        BtlUnit_SetMoveStartPos(unit, x, y, z);
        BtlUnit_SetMoveCurrentPos(unit, x, y, z);
        BtlUnit_SetMoveTargetPos(unit, tx, ty, tz);
        {
            f32 dx = x - tx, dy = y - ty, dz = z - tz;
            dx = dx * dx;
            dy = dy * dy;
            dz = dz * dz;
            BEC_MVDIST(unit) = bec_sqrtf(dx + dy + dz);
        }
        if (BEC_MVFRAME(unit) == 0) {
            BEC_MVFRAME(unit) = BEC_MVDIST(unit) / unit->mMoveSpeedXZ;
        }
        else {
            unit->mMoveSpeedXZ = BEC_MVDIST(unit) / BEC_MVFRAME(unit);
        }
        if (BEC_MVFRAME(unit) == 0) {
            return EVT_RETURN_DONE;
        }
        BEC_MVCNT(unit) = 0.0f;
        unit->mMoveDirection = 0.0f;
        if (tx - x > 0.0f) {
            unit->moveDirection = 1;
        }
        else if (tx - x < 0.0f) {
            unit->moveDirection = -1;
        }
    }
    cx = (unit->mMoveStartPos.x + unit->mMoveTargetPos.x) * 0.5f;
    cz = (unit->mMoveStartPos.z + unit->mMoveTargetPos.z) * 0.5f;
    {
        f32 dx = unit->mMoveTargetPos.x - unit->mMoveStartPos.x, dz = unit->mMoveTargetPos.z - unit->mMoveStartPos.z;
        dx = dx * dx;
        dz = dz * dz;
        r = 0.5f * bec_sqrtf(dx + dz);
    }
    w = (f32)width;
    ang = angleABf(cx, cz, unit->mMoveStartPos.x, unit->mMoveStartPos.z);
    t = intpl_sub(mode, 180.0f, 0.0f, (s32)BEC_MVCNT(unit), BEC_MVFRAME(unit));
    unit->mMoveCurrentPos.x = cx - (w * cosfd(ang) * sinfd(t) + r * sinfd(ang) * cosfd(t));
    unit->mMoveCurrentPos.z = cz + r * cosfd(ang) * cosfd(t) - w * sinfd(ang) * sinfd(t);
    BtlUnit_SetPos(unit, unit->mMoveCurrentPos.x, unit->mMoveCurrentPos.y, unit->mMoveCurrentPos.z);
    BEC_MVCNT(unit) += 1.0f;
    if (BEC_MVCNT(unit) > BEC_MVFRAME(unit)) {
        BtlUnit_SetPos(unit, unit->mMoveTargetPos.x, unit->mMoveTargetPos.y, unit->mMoveTargetPos.z);
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
/* movers end (half_B) */

USER_FUNC(btlevtcmd_MoveDirectionAdd) {
    s32 btlId, id, index, value, dir;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    value = evtGetValue(event, args[2]);
    unit = BattleGetUnitPtr(wp, id);
    if (unit->moveDirection) {
        dir = value * unit->moveDirection;
    } else {
        dir = unit->faceDirection * value;
    }
    evtSetValue(event, index, evtGetValue(event, index) + dir);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_FaceDirectionAdd) {
    s32 btlId, id, value;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 index, dir;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    value = evtGetValue(event, args[2]);
    unit = BattleGetUnitPtr(wp, id);
    dir = value * unit->faceDirection;
    value = evtGetValue(event, index);
    value += dir;
    evtSetValue(event, index, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_FaceDirectionSub) {
    s32 btlId, id, index, value, dir;
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;

    btlId = evtGetValue(event, args[0]);
    id = BattleTransID(event, btlId);
    index = args[1];
    value = evtGetValue(event, args[2]);
    unit = BattleGetUnitPtr(wp, id);
    dir = value * unit->faceDirection;
    evtSetValue(event, index, evtGetValue(event, index) - dir);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_PartsFaceDirectionSub) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 btlId, id, partId, index, value, dir;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    partId = evtGetValue(event, args[1]);
    index = args[2];
    value = evtGetValue(event, args[3]);
    unit = BattleGetUnitPtr(wp, id);
    dir = value * BtlUnit_GetPartsPtr(unit, partId)->faceDirection;
    evtSetValue(event, index, evtGetValue(event, index) - dir);
    return EVT_RETURN_DONE;
}





















































/* half_A begin PRE */
/* first-half (target order 1..153) functions, generated block */
#include <string.h>
#include "data/item_data.h"
void BattleStatusWindowCheck(void);
s32 BattleEnemyUseItemCheck(BattleUnit* unit);
void BattleAudience_ApRecoveryBuild(StarPowerInfo* info);
BattleStage* BattleStageGetPtr(void);
f32 BattleGetFloorHeight(BattleWork* wp, f32 x, f32 y, f32 z);
void battleSortPhaseMoveTable(BattleWork* wp, s32 a);
void BtlUnit_PayWeaponCost(BattleUnit* unit, BattleWeapon* weapon);
void BattleAfterReactionEntry(s32 id, s32 value);
BOOL BtlUnit_GetACPossibility(BattleUnit* unit);
BOOL BtlUnit_CanActStatus(BattleUnit* unit);
BattleWeapon* BattleGetSelectWeapon(BattleWork* wp);
extern ItemData itemDataTable[];
#include "driver/animdrv.h"
void btlDispChangePeraAnime(BattleUnitPart* part, s32 anim);
void BtlUnit_PoseSoundInit(BattleUnitPart* part);
void btlDispPoseAnime(BattleUnitPart* part);
void BtlUnit_SetAnimType(BattleUnitPart* part, s32 type);
void BtlUnit_SetAnim(BattleUnitPart* part, const char* name);
void BattleAudience_Case_Appeal(BattleUnit* unit);
s32 battleAcTimingA_GetSuccessFrame(BattleWork* wp);
s32 BattleActionCommandGetPrizeLv(BattleWork* wp, BattleUnit* unit, s32 value);
void BattleActionCommandCheckDefence(BattleUnit* unit, BattleWeapon* weapon);
void BattleActionCommandSetup(BattleWork* wp, s32 a, BattleUnit* unit, s32 b, s32 c);
void BattleActionCommandSetDifficulty(BattleWork* wp, BattleUnit* unit, s32 diff);
void BattleAttackDeclareAll(BattleWork* wp);
void BattleGetFirstAttackUnit(BattleWork* wp, s32* a, BattleUnit** unit);
void BattleChoiceSamplingEnemy(BattleWorkWeaponTargets* targets, s32 a, s32* b, s32* c);
#define BEC_FIELD(wp, off, type) (*(type*)((u8*)(wp) + (off)))
typedef struct BecSndWork {
    const char* name0; // 0x0
    const char* name1; // 0x4
    u8 field_0x8[0xE - 0x8];
    s16 period0;       // 0xE
    s16 period1;       // 0x10
    s16 timer;         // 0x12
    s16 count;         // 0x14
    s32 sfxId;         // 0x18
} BecSndWork;
s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* sfxName, s32 volume, s32 pitch, Vec* pos);
void BtlUnit_SetSeMode(void* work, const char* name0, const char* name1, s16 c, s16 e, s16 unused, s16 a, s16 b);
void psndSFX_pos(s32 id, Vec* pos);
void _MoveSoundControlEndCore(BattleUnit* unit, BecSndWork* work);
void _MoveSoundControlCore(BattleUnit* unit, BecSndWork* work, BattleUnitPart* part, f32 x, f32 y, f32 z);
const char* _mario_acrobat_voice_table[5] = {
    "SFX_VOICE_MARIO_AC3_1", "SFX_VOICE_MARIO_AC3_2", "SFX_VOICE_MARIO_AC3_3",
    "SFX_VOICE_MARIO_AC3_4", "SFX_VOICE_MARIO_AC3_5",
};
const char* _mario_attack_voice_table[10] = {
    "SFX_VOICE_MARIO_AC1_1", "SFX_VOICE_MARIO_AC1_2", "SFX_VOICE_MARIO_AC1_3",
    "SFX_VOICE_MARIO_AC1_4", "SFX_VOICE_MARIO_AC1_5", "SFX_VOICE_MARIO_AC2_1",
    "SFX_VOICE_MARIO_AC2_2", "SFX_VOICE_MARIO_AC2_3", "SFX_VOICE_MARIO_AC2_4",
    "SFX_VOICE_MARIO_AC2_5",
};
void* BattleSetConfuseAct(BattleWork* wp, BattleUnit* unit);
extern s32 subsetevt_confuse_flustered[];
void BattleSamplingEnemy(BattleWorkWeaponTargets* targets, BattleWeapon* weapon, s32 unitId, s8 belong, u32 classFlags, u32 propFlags, s8 direction);
void BattleAttackDeclare(s32* unitIdx, s32* partIdx);
void BattleActionCommandDeclareACResult(BattleWork* work, BattleWeapon* weapon, s32 result);
void BattleDamageDirect(s32 unitId, BattleUnit* target, BattleUnitPart* part, s32 damage, s32 fpDamage, u32 result, u32 pattern, s32 flag);
void BattleInitCounterPreCheckWork(s32* work);
s32 BattleCheckCounter(s32* work, BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32* flags);
s32 BattlePreCheckDamage(BattleUnit* attacker, BattleUnit* target, BattleUnitPart* part, BattleWeapon* weapon, u32 flags);
void* itemEntry(const char* name, s32 itemId, s32 type, s32 evtId, s32 a5, f32 x, f32 y, f32 z);
void itemDelete(const char* name);
void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);
BOOL pouchRemoveItemIndex(s32 id, s32 index);
typedef struct BecCmdItem {
    s32 index;           // 0x0
    s32 id;              // 0x4
    u8 pad[0x1C - 0x8];  // 0x8
} BecCmdItem;
typedef struct BecCmd {
    u8 pad[0x90];        // 0x0
    BecCmdItem items[1]; // 0x90
} BecCmd;
#include "eff/n64/eff_coin_n64.h"
s16 pouchAddCoin(s16 coins);
static inline void bec_coin(BattleUnit* unit, s32 item) {
    s32 coins;
    Vec pos;
    if (BEC_FIELD(unit, 0x2F7, u8)) {
        coins = (s32)((f32)(BEC_FIELD(unit, 0x2F7, u8) * 5 + 70) * (f32)itemDataTable[item].sell_price / 100.0f);
        if (coins > 0) {
            ((void (*)(s32))pouchAddCoin)(coins);
            BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
            ((void (*)(s32, s32, f32, f32, f32, f32))effCoinN64Entry)(0, 0, pos.x, pos.y, pos.z, 1.0f);
        }
    }
}
typedef struct { u8 pad[0x94]; struct { s32 v; u8 p[0x18]; } e[1]; } BecCmdMenuX;

USER_FUNC(btlevtcmd_SamplingEnemy) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleWorkWeaponTargets* targets = &wp->weaponTargets;
    s32 id;
    s8 belong;
    BattleWeapon* weapon;
    s8 dir;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    belong = evtGetValue(event, args[1]);
    weapon = (BattleWeapon*)evtGetValue(event, args[2]);
    dir = -wp->alliances[belong].attackDirection;
    if (weapon->targetPropertyFlags & 0x10000000) {
        dir *= -1;
    }
    BattleSamplingEnemy(targets, weapon, id, belong, weapon->targetClassFlags, weapon->targetPropertyFlags, dir);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ChoiceSamplingEnemy) {
    s32* args = event->args;
    BattleWorkWeaponTargets* targets = &_battleWorkPointer->weaponTargets;
    u8* weapon;
    s32 a, b, ra, rb;

    weapon = (u8*)evtGetValue(event, args[0]);
    a = args[1];
    b = args[2];
    BattleChoiceSamplingEnemy(targets, BEC_FIELD(weapon, 0x7C, s32), &ra, &rb);
    evtSetValue(event, a, ra);
    evtSetValue(event, b, rb);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetSelectEnemy) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleWorkWeaponTargets* targets = &wp->weaponTargets;
    s32 a = args[0];
    s32 b = args[1];
    BattleWorkTarget* t;

    if (wp->weaponTargets.numTargets <= 0) {
        evtSetValue(event, a, -1);
        evtSetValue(event, b, -1);
        return EVT_RETURN_DONE;
    }
    t = &targets->targets[targets->targetIndices[targets->currentTarget]];
    evtSetValue(event, a, t->unitIdx);
    evtSetValue(event, b, t->partIdx);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetSelectNextEnemy) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleWorkWeaponTargets* targets = &wp->weaponTargets;
    s32 a = args[0];
    s32 b = args[1];
    BattleWorkTarget* t;

    targets->currentTarget = wp->weaponTargets.currentTarget + 1;
    if (targets->currentTarget < targets->numTargets) {
        t = &targets->targets[targets->targetIndices[targets->currentTarget]];
        evtSetValue(event, a, t->unitIdx);
        evtSetValue(event, b, t->partIdx);
    } else {
        evtSetValue(event, a, -1);
        evtSetValue(event, b, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetFirstAttackTarget) {
    s32* args = event->args;
    s32 part;
    BattleUnit* unit;
    s32 a = args[0];
    s32 b = args[1];
    s32 body;

    BattleGetFirstAttackUnit(_battleWorkPointer, &part, &unit);
    body = BtlUnit_GetBodyPartsId(unit);
    evtSetValue(event, a, *(s32*)unit);
    evtSetValue(event, b, body);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetConsumeItem) {
    BattleWork* wp = _battleWorkPointer;
    BattleCommandWeapon* w = (BattleCommandWeapon*)&wp->commandMenu;
    w = &w[wp->commandMenu.cursor[11].field_0];
    evtSetValue(event, event->args[0], ((BattleCommand*)w)->weapon[0].itemId);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_DispItemIcon) {
    s32* args = event->args;
    s32 x, y, z;
    s32 item;
    s32 time;

    x = evtGetValue(event, args[0]);
    y = evtGetValue(event, args[1]);
    z = evtGetValue(event, args[2]);
    item = evtGetValue(event, args[3]);
    time = evtGetValue(event, args[4]);
    if (isFirstCall) {
        event->userdata[0] = time;
        event->userdatap[1] = itemEntry(NULL, item, 0x11, -1, 0, x, y, z);
        return EVT_RETURN_BLOCK;
    }
    if (--event->userdata[0] > 0) {
        return EVT_RETURN_BLOCK;
    }
    itemDelete((char*)event->userdatap[1] + 0xC);
    return EVT_RETURN_DONE;
}

void effItemGetEntry(s32 type, f32 x, f32 y, f32 z);

USER_FUNC(btlevtcmd_CommandFlyItem) {
    s32* args = event->args;
    s32 id, time;
    BecCmd* cmd;
    BattleUnit* unit;
    s32 kind;
    s32 item;
    BattleWork* wp;
    Vec pos;

    id = evtGetValue(event, args[0]);
    time = evtGetValue(event, args[1]);
    id = BattleTransID(event, id);
    if (isFirstCall) {
        wp = _battleWorkPointer;
        cmd = (BecCmd*)&wp->commandMenu;
        unit = BattleGetUnitPtr(wp, id);
        kind = unit->currentKind;
        if (kind == 0xDE || (kind >= 0xE0 && kind < 0xE7)) {
            item = cmd->items[BEC_FIELD(cmd, 0x1C38 - 0x171C, s32)].id;
        } else {
            item = unit->heldItem;
        }
        event->userdata[0] = time;
        BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
        pos.y += 10.0f;
        if (!(unit->mAttributeFlags & 0x10)) {
            if (unit->mAttributeFlags & 2) {
                pos.y -= 5.0f;
            } else {
                pos.y += unit->mSizeMultiplier * BtlUnit_GetHeight(unit);
            }
        }
        event->userdatap[1] = itemEntry(NULL, item, 0x11, -1, 0, pos.x, pos.y, pos.z);
        effItemGetEntry(10, pos.x, 12.0f + pos.y, pos.z - 5.0f);
        if (kind == 0xDE) {
            psndSFXOn_3D("SFX_ITEM_MARIO_USE1", &pos);
        } else if (kind >= 0xE0 && kind < 0xE7) {
            psndSFXOn_3D("SFX_ITEM_PARTY_USE1", &pos);
        } else {
            psndSFXOn_3D("SFX_ENM_ITEM_USE1", &pos);
        }
        return EVT_RETURN_BLOCK;
    }
    if (--event->userdata[0] > 0) {
        return EVT_RETURN_BLOCK;
    }
    itemDelete((char*)event->userdatap[1] + 0xC);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ConsumeItem) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    BecCmdItem* ci;
    s32 id;
    s32 item;
    s32 idx;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit->currentKind == 0xDE || (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7)) {
        BecCmd* cmd = (BecCmd*)&wp->commandMenu;
        item = cmd->items[BEC_FIELD(cmd, 0x1C38 - 0x171C, s32)].id;
        idx = cmd->items[BEC_FIELD(cmd, 0x1C38 - 0x171C, s32)].index;
        if (BEC_FIELD(&itemDataTable[item], 0x10, u16) & 1) {
            pouchRemoveItemIndex(item, idx);
        }
        bec_coin(unit, item);
    } else {
        unit->heldItem = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ConsumeItemReserve) {
    s32 id;
    BattleUnit* unit;
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 item;
    s32 i;
    s32 coins;
    Vec pos;

    id = evtGetValue(event, args[0]);
    item = evtGetValue(event, args[1]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit->currentKind == 0xDE || (unit->currentKind >= 0xE0 && unit->currentKind < 0xE7)) {
        if (BEC_FIELD(&itemDataTable[item], 0x10, u16) & 1) {
            for (i = 0; i < 4; i++) {
                if ((s32)wp->reserveItems[i] == item) {
                    break;
                }
                if ((s32)wp->reserveItems[i] == 0) {
                    wp->reserveItems[i] = item;
                    break;
                }
            }
        }
        if (BEC_FIELD(unit, 0x2F7, u8)) {
            coins = (s32)((f32)(BEC_FIELD(unit, 0x2F7, u8) * 5 + 70) * (f32)itemDataTable[item].sell_price / 100.0f);
            if (coins > 0) {
                ((void (*)(s32))pouchAddCoin)(coins);
                BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
                ((void (*)(s32, s32, f32, f32, f32, f32))effCoinN64Entry)(0, 0, pos.x, pos.y, pos.z, 1.0f);
            }
        }
    } else if (unit->heldItem == 0x97) {
        unit->heldItem = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AttackDeclare) {
    s32* args = event->args;
    s32 id;
    s32 a, b;
    s32 unitIdx, partIdx;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    a = args[1];
    b = args[2];
    unitIdx = evtGetValue(event, a);
    unitIdx = BattleTransID(event, unitIdx);
    partIdx = evtGetValue(event, b);
    BattleAttackDeclare(&unitIdx, &partIdx);
    evtSetValue(event, a, unitIdx);
    evtSetValue(event, b, partIdx);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AttackDeclareAll) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    BattleAttackDeclareAll(wp);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_PreCheckDamage) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* attacker;
    BattleUnit* target;
    BattleUnitPart* part;
    BattleWeapon* weapon;
    s32 id;
    s32 id2;
    s32 pno;
    s32 flags;
    s32 out;
    s32 res;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    attacker = BattleGetUnitPtr(wp, id);
    id2 = evtGetValue(event, args[1]);
    id2 = BattleTransID(event, id2);
    target = BattleGetUnitPtr(wp, id2);
    pno = evtGetValue(event, args[2]);
    part = BtlUnit_GetPartsPtr(target, pno);
    weapon = (BattleWeapon*)evtGetValue(event, args[3]);
    out = args[5];
    res = BattlePreCheckDamage(attacker, target, part, weapon, args[4]);
    if (res < 0) {
        return EVT_RETURN_FINISH;
    }
    evtSetValue(event, out, res);
    if (!evtCheckID(event->eventId)) {
        return EVT_RETURN_FINISH;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CommandPreCheckDamage) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* attacker;
    BattleUnit* target;
    BattleUnitPart* part;
    BattleWeapon* weapon;
    s32 id;
    s32 id2;
    s32 pno;
    s32 out;
    s32 flags;
    s32 res;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    attacker = BattleGetUnitPtr(wp, id);
    id2 = evtGetValue(event, args[1]);
    id2 = BattleTransID(event, id2);
    target = BattleGetUnitPtr(wp, id2);
    pno = evtGetValue(event, args[2]);
    part = BtlUnit_GetPartsPtr(target, pno);
    flags = args[3];
    out = args[4];
    weapon = BattleGetSelectWeapon(wp);
    res = BattlePreCheckDamage(attacker, target, part, weapon, flags);
    if (res < 0) {
        return EVT_RETURN_FINISH;
    }
    evtSetValue(event, out, res);
    if (!evtCheckID(event->eventId)) {
        return EVT_RETURN_FINISH;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_PreCheckCounter) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* attacker;
    BattleUnit* target;
    BattleUnitPart* part;
    BattleWeapon* weapon;
    s32 id;
    s32 id2;
    s32 pno;
    s32 out;
    s32 res;
    s32 work[12];
    u32 flags = 0;

    BattleInitCounterPreCheckWork(work);
    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    attacker = BattleGetUnitPtr(wp, id);
    id2 = evtGetValue(event, args[1]);
    id2 = BattleTransID(event, id2);
    target = BattleGetUnitPtr(wp, id2);
    pno = evtGetValue(event, args[2]);
    part = BtlUnit_GetPartsPtr(target, pno);
    weapon = (BattleWeapon*)evtGetValue(event, args[3]);
    out = args[5];
    res = BattleCheckCounter(work, attacker, target, part, weapon, &flags);
    evtSetValue(event, out, res);
    if (!evtCheckID(event->eventId)) {
        return EVT_RETURN_FINISH;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CommandPreCheckCounter) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* attacker;
    BattleUnit* target;
    BattleUnitPart* part;
    BattleWeapon* weapon;
    s32 id;
    s32 id2;
    s32 pno;
    s32 out;
    s32 res;
    s32 work[12];
    u32 flags = 0;

    BattleInitCounterPreCheckWork(work);
    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    attacker = BattleGetUnitPtr(wp, id);
    id2 = evtGetValue(event, args[1]);
    id2 = BattleTransID(event, id2);
    target = BattleGetUnitPtr(wp, id2);
    pno = evtGetValue(event, args[2]);
    part = BtlUnit_GetPartsPtr(target, pno);
    out = args[4];
    weapon = BattleGetSelectWeapon(wp);
    res = BattleCheckCounter(work, attacker, target, part, weapon, &flags);
    evtSetValue(event, out, res);
    if (!evtCheckID(event->eventId)) {
        return EVT_RETURN_FINISH;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckDamage) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* attacker;
    BattleUnit* target;
    BattleUnitPart* part;
    BattleWeapon* weapon;
    s32 id;
    s32 id2;
    s32 pno;
    s32 flags;
    s32 res;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    attacker = BattleGetUnitPtr(wp, id);
    id2 = evtGetValue(event, args[1]);
    id2 = BattleTransID(event, id2);
    target = BattleGetUnitPtr(wp, id2);
    pno = evtGetValue(event, args[2]);
    part = BtlUnit_GetPartsPtr(target, pno);
    weapon = (BattleWeapon*)evtGetValue(event, args[3]);
    flags = args[4];
    args = (s32*)args[5];
    res = BattleCheckDamage(attacker, target, part, weapon, flags);
    if (res < 0) {
        return EVT_RETURN_FINISH;
    }
    evtSetValue(event, (s32)args, res);
    if (!evtCheckID(event->eventId)) {
        return EVT_RETURN_FINISH;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CommandCheckDamage) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* attacker;
    BattleUnit* target;
    BattleUnitPart* part;
    BattleWeapon* weapon;
    s32 id;
    s32 id2;
    s32 pno;
    s32 out;
    s32 flags;
    s32 res;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    attacker = BattleGetUnitPtr(wp, id);
    id2 = evtGetValue(event, args[1]);
    id2 = BattleTransID(event, id2);
    target = BattleGetUnitPtr(wp, id2);
    pno = evtGetValue(event, args[2]);
    part = BtlUnit_GetPartsPtr(target, pno);
    flags = args[3];
    out = args[4];
    weapon = BattleGetSelectWeapon(wp);
    res = BattleCheckDamage(attacker, target, part, weapon, flags);
    if (res < 0) {
        return EVT_RETURN_FINISH;
    }
    evtSetValue(event, out, res);
    if (!evtCheckID(event->eventId)) {
        return EVT_RETURN_FINISH;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_DamageDirect) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id;
    s32 damage;
    s32 result;
    s32 pattern;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    pattern = evtGetValue(event, args[1]);
    part = BtlUnit_GetPartsPtr(unit, pattern);
    damage = evtGetValue(event, args[2]);
    result = args[3];
    pattern = evtGetValue(event, args[4]);
    BattleDamageDirect(-5, unit, part, damage, 0, result, pattern, evtGetValue(event, args[5]));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventDamage) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x2AC, s32) = args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventWait) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x288, s32) = args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventEntry) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x2B4, s32) = args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventPhase) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x294, s32) = args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventUnisonPhase) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x290, s32) = args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventAttack) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x29C, s32) = args[1];
    BEC_FIELD(unit, 0x2A8, s32) = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventConfusion) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x2A0, s32) = args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetEventCeilFall) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BEC_FIELD(unit, 0x2BC, s32) = args[1];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StartWaitEvent) {
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (BEC_FIELD(unit, 0x288, void*)) {
        BattleRunWaitEvent(unit);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StopWaitEvent) {
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (BEC_FIELD(unit, 0x28C, s32)) {
        evtDeleteID(BEC_FIELD(unit, 0x28C, s32));
        BEC_FIELD(unit, 0x28C, s32) = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GuardMoveEnd) {
    _battleWorkPointer->flags &= ~1;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_WaitGuardMove) {
    return (_battleWorkPointer->flags & 1) ? EVT_RETURN_BLOCK : EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_WaitAttackEnd) {
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, _battleWorkPointer->activeUnitId);
    if (!unit) {
        return EVT_RETURN_DONE;
    }
    if (!BEC_FIELD(unit, 0x2A4, s32)) {
        return EVT_RETURN_DONE;
    }
    if (evtCheckID(BEC_FIELD(unit, 0x2A4, s32))) {
        return EVT_RETURN_BLOCK;
    }
    BEC_FIELD(unit, 0x2A4, s32) = 0;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_WaitAttackEndCheck) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit = BattleGetUnitPtr(wp, wp->activeUnitId);
    s32 out = args[0];

    evtSetValue(event, out, 1);
    if (!unit) {
        return EVT_RETURN_DONE;
    }
    if (!BEC_FIELD(unit, 0x2A4, s32)) {
        return EVT_RETURN_DONE;
    }
    if (evtCheckID(BEC_FIELD(unit, 0x2A4, s32))) {
        evtSetValue(event, out, 0);
    } else {
        BEC_FIELD(unit, 0x2A4, s32) = 0;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_RunDataEventChild) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, type;
    void* evt;
    EventEntry* child;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    type = evtGetValue(event, args[1]);
    evt = BtlUnit_GetData(unit, type);
    if (!evt) {
        return EVT_RETURN_DONE;
    }
    child = evtChildEntry(event, evt, 0);
    BEC_FIELD(event, 0xA, u8) = 0;
    BEC_FIELD(child, 0x160, s32) = id;
    return 0xFF;
}

USER_FUNC(btlevtcmd_CheckDataOfDataTable) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;
    s32 index, type;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    index = args[1];
    type = evtGetValue(event, args[2]);
    evtSetValue(event, index, BtlUnit_CheckData(unit, type));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetDataFromDataTable) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id;
    s32 index, type;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    index = args[1];
    type = evtGetValue(event, args[2]);
    evtSetValue(event, index, (s32)BtlUnit_GetData(unit, type));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_PhaseEventStartDeclare) {
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    BattlePhaseEventStartDeclare(BattleGetUnitPtr(_battleWorkPointer, id));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetConfuseActEvent) {
    s32* args = event->args;
    s32 id;
    s32 out;
    BattleUnit* unit;
    s32 i = 0;
    void* evt;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    out = args[1];
    evt = NULL;
    while (!evt) {
        evt = BattleSetConfuseAct(_battleWorkPointer, unit);
        i++;
        if (i > 20) {
            evt = subsetevt_confuse_flustered;
        }
    }
    evtSetValue(event, out, (s32)evt);
    return EVT_RETURN_DONE;
}

void BattleChoiceSamplingEnemy(BattleWorkWeaponTargets* targets, s32 n, s32* id, s32* pno);

USER_FUNC(btlevtcmd_GetTakeoffPosition) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, id2, pno, ox, oy, oz;
    BattleUnit* unit;
    BattleUnit* target;
    BattleUnitPart* part;
    BattleUnit* u2;
    BattleUnitPart* p2;
    s32 belong, back;
    BattleAlliance* al;
    BattleWorkWeaponTargets targets;
    f32 hx, hy, hz, y, x, tx;
    s32 cid, cpno;

    id = evtGetValue(event, args[0]);
    id2 = evtGetValue(event, args[1]);
    pno = evtGetValue(event, args[2]);
    ox = args[3];
    oy = args[4];
    oz = args[5];
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &x, &y, &y);
    target = BattleGetUnitPtr(wp, BattleTransID(event, id2));
    part = BtlUnit_GetPartsPtr(target, pno);
    BtlUnit_GetHomePos(unit, &hx, &hy, &hz);
    BtlUnit_GetHitPos(target, part, &hx, &y, &hz);
    belong = (s8)BtlUnit_GetEnemyBelong(unit);
    al = (BattleAlliance*)((u8*)wp + belong * 8 + 8);
    back = ((s32 (*)(BattleWorkWeaponTargets*, BattleWeapon*, s32, s8, u32, u32, s8))BattleSamplingEnemy)(
        &targets, NULL, id, belong, 0x1001240, 0x1000000, -al->attackDirection);
    BattleChoiceSamplingEnemy(&targets, 4, &cid, &cpno);
    if (targets.numTargets > 0) {
        cid = BattleTransID(event, cid);
        u2 = BattleGetUnitPtr(wp, cid);
        p2 = BtlUnit_GetPartsPtr(u2, cpno);
        BtlUnit_GetHitPos(u2, p2, &tx, &y, &y);
        if (__fabs(x - hx) > __fabs(x - tx)) {
            hx = tx;
        }
        if (part == p2) {
            if (back) hx += al->attackDirection * -60;
            else hx += al->attackDirection * 60;
        }
        else {
            if (back) hx += al->attackDirection * -30;
            else hx += al->attackDirection * 30;
        }
    }
    else {
        hx += al->attackDirection * 60;
    }
    evtSetValue(event, ox, (s32)hx);
    evtSetValue(event, oy, (s32)hy);
    evtSetValue(event, oz, (s32)hz);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsMoveSpeed) {
    s32* args = event->args;
    s32 id, pno;
    f32 speed;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    speed = evtGetFloat(event, args[2]);
    BtlUnit_SetPartsMoveSpeed(BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, id), pno), speed);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsFallAccel) {
    s32* args = event->args;
    s32 id, pno;
    f32 accel;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    accel = evtGetFloat(event, args[2]);
    BtlUnit_SetPartsFallAccel(BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, id), pno), accel);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_JumpPartsSetting) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 a;
    s32 id;
    s32 pno;
    f32 f0, f1;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    a = evtGetValue(event, args[2]);
    f0 = evtGetFloat(event, args[3]);
    f1 = evtGetFloat(event, args[4]);
    part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, id), pno);
    BEC_FIELD(part, 0xA0, s32) = a;
    BEC_FIELD(part, 0xA4, f32) = f0;
    BEC_FIELD(part, 0xA8, f32) = f1;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_FallPartsPosition) {
    s32 id, pno, frames;
    s32* args = event->args;
    BattleUnitPart* part;
    f32 tx, ty, tz;
    f32 x, y, z;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    tx = (f32)evtGetValue(event, args[2]);
    ty = (f32)evtGetValue(event, args[3]);
    tz = (f32)evtGetValue(event, args[4]);
    frames = evtGetValue(event, args[5]);
    part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, id), pno);
    if (isFirstCall) {
        event->blocked = 1;
        BEC_FIELD(part, 0xA0, s32) = frames;
        BtlUnit_GetPartsPos(part, &x, &y, &z);
        BtlUnit_SetPartsMoveCurrentPos(part, x, y, z);
        BtlUnit_SetPartsMoveTargetPos(part, tx, ty, tz);
        BEC_FIELD(part, 0xB0, f32) = angleABf(x, z, tx, tz);
        BEC_FIELD(part, 0xB4, f32) = distABf(x, z, tx, tz);
        if (tx - x > 0.0f) {
            BEC_FIELD(part, 0xBC, s8) = 1;
        }
        else if (tx - x < 0.0f) {
            BEC_FIELD(part, 0xBC, s8) = -1;
        }
        y = ty - y;
        if (BEC_FIELD(part, 0xA0, s32) == 0) {
            if (BEC_FIELD(part, 0xA4, f32) == 0.0f) {
                BEC_FIELD(part, 0xA4, f32) = 1.0f;
            }
            BEC_FIELD(part, 0xA0, s32) = BEC_FIELD(part, 0xB4, f32) / BEC_FIELD(part, 0xA4, f32);
            if (BEC_FIELD(part, 0xA0, s32) == 0) {
                BEC_FIELD(part, 0xA0, s32) = 1;
            }
        }
        else {
            BEC_FIELD(part, 0xA4, f32) = BEC_FIELD(part, 0xB4, f32) / BEC_FIELD(part, 0xA0, s32);
        }
        BEC_FIELD(part, 0xAC, f32) = 0.0f;
        BEC_FIELD(part, 0xA8, f32) = (y / BEC_FIELD(part, 0xA0, s32) - BEC_FIELD(part, 0xAC, f32)) / (-BEC_FIELD(part, 0xA0, s32) / 2.0f);
    }
    part->mMoveCurrentPos.y += BEC_FIELD(part, 0xAC, f32);
    BEC_FIELD(part, 0xAC, f32) -= BEC_FIELD(part, 0xA8, f32);
    btlMovePos(BEC_FIELD(part, 0xA4, f32), BEC_FIELD(part, 0xB0, f32), &part->mMoveCurrentPos.x, &part->mMoveCurrentPos.z);
    BtlUnit_SetPartsPos(part, part->mMoveCurrentPos.x, part->mMoveCurrentPos.y, part->mMoveCurrentPos.z);
    BEC_FIELD(part, 0xA0, s32)--;
    if (BEC_FIELD(part, 0xA0, s32) <= 0) {
        BtlUnit_SetPartsPos(part, part->mMoveTargetPos.x, part->mMoveTargetPos.y, part->mMoveTargetPos.z);
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(btlevtcmd_JumpPartsContinue) {
    s32* args = event->args;
    s32 id, pno;
    BattleUnitPart* part;
    f32 h;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, id), pno);
    if (isFirstCall) {
        f32 x, y, z;
        event->blocked = 1;
        BtlUnit_GetPartsPos(part, &x, &y, &z);
        BtlUnit_SetPartsMoveCurrentPos(part, x, y, z);
    }
    part->mMoveCurrentPos.y += BEC_FIELD(part, 0xAC, f32);
    BEC_FIELD(part, 0xAC, f32) -= part->mFallAccel;
    btlMovePos(part->mMoveSpeedXZ, BEC_FIELD(part, 0xB0, f32), &part->mMoveCurrentPos.x, &part->mMoveCurrentPos.z);
    BtlUnit_SetPartsPos(part, part->mMoveCurrentPos.x, part->mMoveCurrentPos.y, part->mMoveCurrentPos.z);
    h = BattleGetFloorHeight(_battleWorkPointer, part->mMoveCurrentPos.x, part->mMoveCurrentPos.y, part->mMoveCurrentPos.z);
    if (part->mMoveCurrentPos.y < h) {
        part->mMoveCurrentPos.y = h;
        BtlUnit_SetPartsPos(part, part->mMoveCurrentPos.x, part->mMoveCurrentPos.y, part->mMoveCurrentPos.z);
        return EVT_RETURN_YIELD;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(btlevtcmd_AcSetDifficulty) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, diff;

    id = evtGetValue(event, args[0]);
    diff = evtGetValue(event, args[1]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    BattleActionCommandSetDifficulty(wp, unit, diff);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcGetDifficulty) {
    s32 index = event->args[0];
    evtSetValue(event, index, ((s32(*)(BattleWork*))BattleActionCommandGetDifficulty)(_battleWorkPointer));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcSetFlag) {
    BEC_FIELD(_battleWorkPointer, 0x1CC4, s32) = event->args[0];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcSetParamAll) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 i, value;

    for (i = 0; i < 8; i++) {
        value = evtGetValue(event, *args++);
        if (value != EVTDAT_POINTER_MAX) {
            ((s32*)wp)[i + 0x1CC8 / 4] = value;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcSetParam) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 i = evtGetValue(event, args[0]);
    ((s32*)((u8*)wp + 0x1CC8))[i] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcGetParam) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 i = evtGetValue(event, args[0]);
    s32 index = args[1];
    s32 value = ((s32*)((u8*)wp + 0x1CC8))[i];
    if (index != EVTDAT_POINTER_MAX) {
        evtSetValue(event, index, value);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcSetGaugeParam) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BEC_FIELD(wp, 0x1D08, s32) = evtGetValue(event, args[0]);
    BEC_FIELD(wp, 0x1D0C, s32) = evtGetValue(event, args[1]);
    BEC_FIELD(wp, 0x1D10, s32) = evtGetValue(event, args[2]);
    BEC_FIELD(wp, 0x1D14, s32) = evtGetValue(event, args[3]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcGetOutputParam) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    s32 i = evtGetValue(event, args[0]);
    s32 index = args[1];
    s32 value = ((s32*)((u8*)wp + 0x1CE8))[i];
    if (index != EVTDAT_POINTER_MAX) {
        evtSetValue(event, index, value);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AcSetOutputParam) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 i = evtGetValue(event, args[0]);
    ((s32*)((u8*)wp + 0x1CE8))[i] = evtGetValue(event, args[1]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetupAC) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, a, b, c;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    a = evtGetValue(event, args[1]);
    b = args[2];
    c = evtGetValue(event, args[3]);
    BattleActionCommandSetup(wp, a, unit, b, c);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StartAC) {
    BattleWork* wp = _battleWorkPointer;
    s32 help = evtGetValue(event, event->args[0]);
    BattleActionCommandStart(wp);
    if (help && !(BEC_FIELD(BEC_FIELD(wp, 0x1C90, u8*), 0x278, u32) & 0x10)) {
        BattleAcHelpSetDispType(2);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StopAC) {
    BattleActionCommandStop(_battleWorkPointer);
    BattleAcHelpSetDispType(0);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ResultAC) {
    BattleWork* wp = _battleWorkPointer;
    BattleActionCommandResult(wp);
    if (BEC_FIELD(wp, 0x1CB8, s32) & 1) {
        return EVT_RETURN_BLOCK;
    }
    BattleAcHelpSetDispType(0);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ResultACDefence) {
    s32* args = event->args;
    BattleUnit* unit;
    BattleWeapon* weapon;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    weapon = (BattleWeapon*)evtGetValue(event, args[1]);
    BattleActionCommandCheckDefence(unit, weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetResultAC) {
    evtSetValue(event, event->args[0], BEC_FIELD(_battleWorkPointer, 0x1CB8, s32));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetResultPrizeLv) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit = NULL;
    s32 id, value, index;

    id = evtGetValue(event, args[0]);
    if (id != -1 && id != -5) {
        unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id));
    }
    value = evtGetValue(event, args[1]);
    index = args[2];
    evtSetValue(event, index, BattleActionCommandGetPrizeLv(wp, unit, value));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetResultACDefence) {
    s32 index = event->args[0];
    evtSetValue(event, index, BattleActionCommandGetDefenceResult());
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_MarioJumpParam) {
    s32* args = event->args;
    s32 id, frames, n, out;
    f32 tx, tz, dist;
    f32 x, y, z;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    tx = evtGetValue(event, args[1]);
    evtGetValue(event, args[2]);
    tz = evtGetValue(event, args[3]);
    out = args[4];
    frames = evtGetValue(event, out);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BtlUnit_GetPos(unit, &x, &y, &z);
    dist = distABf(x, z, tx, tz);
    if (frames != 0) {
        n = frames;
    } else {
        n = dist / unit->mMoveSpeedXZ;
    }
    if (dist > 60.0f) {
        n += (s32)(0.15f * (dist - 60.0f));
    }
    if (frames == 0 || n > frames) {
        frames = n;
    }
    if (frames != -250000000) {
        evtSetValue(event, out, frames);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetResultCountAC) {
    evtSetValue(event, event->args[0], BEC_FIELD(_battleWorkPointer, 0x1CB4, s32));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AudienceDeclareACResult) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleWeapon* weapon;
    s32 result;
    u8* ac;
    weapon = (BattleWeapon*)evtGetValue(event, args[0]);
    result = evtGetValue(event, args[1]);
    ac = &wp->marioAcSuccess;
    if (result != -1) {
        if (ac[0] < 200) {
            ac[0]++;
        }
        wp->field_19064[0] = 1;
    } else {
        if (ac[1] < 200) {
            ac[1]++;
        }
        wp->field_19064[0] = 0;
    }
    BattleActionCommandDeclareACResult(wp, weapon, result);
    return EVT_RETURN_DONE;
}

void BattleAudience_Case_AcrobatGood(void);
void BattleAudience_Case_AcrobatBad(void);

USER_FUNC(btlevtcmd_AudienceDeclareAcrobatResult) {
    s32* args = event->args;
    u8* res;
    s32 good;
    u8* aud;
    BattleWork* wp;
    BattleUnit* unit;
    f32 x, y, z;
    Vec pos;

    res = (u8*)evtGetValue(event, args[0]);
    good = evtGetValue(event, args[1]);
    wp = _battleWorkPointer;
    unit = BattleGetUnitPtr(wp, BEC_FIELD(event, 0x160, s32));
    aud = (u8*)wp + 0x18FEC;
    x = evtGetFloat(event, args[2]);
    y = evtGetFloat(event, args[3]);
    z = evtGetFloat(event, args[4]);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    if (good) {
        EffectEntry* eff;
        aud[0] = res[0x18];
        aud[3] = res[0x1B];
        BattleAudience_Case_AcrobatGood();
        pos.y += BtlUnit_GetHeight(unit);
        pos.x += BtlUnit_GetWidth(unit) / 2;
        if (pos.x > 150.0f) {
            pos.x = 150.0f;
        }
        eff = effNiceEntry(7, pos.x + x, pos.y + y, pos.z + z);
        BEC_FIELD(eff->userdata, 0x1C, f32) = 0.75f;
    } else {
        BattleAudience_Case_AcrobatBad();
        psndSFXOn_3D("SFX_BTL_ACROBAT_MISS1", &pos);
    }
    return EVT_RETURN_DONE;
}

extern void psndSFX_pit(s32 id, s32 pitch);

USER_FUNC(btlevtcmd_ACSuccessEffect) {
    s32* args = event->args;
    s32 type;
    f32 scale = 0.75f;
    f32 w, h;
    Vec pos;
    const char* name;
    s32 eff;
    EffectEntry* entry;

    type = evtGetValue(event, args[0]);
    pos.x = (f32)evtGetValue(event, args[1]);
    pos.y = (f32)evtGetValue(event, args[2]);
    pos.z = (f32)evtGetValue(event, args[3]);
    switch (type) {
        case 0: scale *= 0.3f; name = "SFX_SYSTEM_NICE_25PERCENT1"; w = 90.0f; eff = 0; break;
        case 1: scale *= 0.6f; name = "SFX_SYSTEM_NICE_50PERCENT1"; w = 90.0f; eff = 0; break;
        case 2: scale *= 1.2f; name = "SFX_SYSTEM_NICE1"; w = 90.0f; eff = 0; break;
        case 3: scale *= 1.2f; name = "SFX_SYSTEM_GOOD1"; w = 90.0f; eff = 1; break;
        case 4: scale *= 1.2f; name = "SFX_SYSTEM_GREAT1"; w = 120.0f; eff = 2; break;
        case 5: name = "SFX_SYSTEM_WONDERFUL1"; w = 150.0f; eff = 3; break;
        case 6: name = "SFX_SYSTEM_EXCELLENT1"; w = 180.0f; eff = 4; break;
        default: return EVT_RETURN_DONE;
    }
    h = w * scale * 0.5f;
    if (pos.x + h > 160.0f) {
        pos.x = 160.0f - h;
    }
    if (pos.y < 80.0f) {
        entry = effNiceEntry(eff, pos.x - h, 50.0f + pos.y, pos.z);
    }
    else {
        entry = effNiceEntry(eff, pos.x - h, pos.y - 50.0f, pos.z);
    }
    ((NiceEffectWork*)entry->userdata)->field_0x1C = scale;
    psndSFX_pit(psndSFXOn_3D(name, &pos), 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ac_timing_flag_onoff) {
    s32* args = event->args;
    s32 on = evtGetValue(event, args[0]);
    BattleWork* wp;
    u32 flags = args[1];
    wp = _battleWorkPointer;
    if (on) {
        BEC_FIELD(wp, 0x1F50, u32) |= flags;
    }
    else {
        BEC_FIELD(wp, 0x1F50, u32) &= ~flags;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ac_timing_get_success_frame) {
    s32 index = event->args[0];
    s32 frame = battleAcTimingA_GetSuccessFrame(_battleWorkPointer);
    evtSetValue(event, index, frame);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ACHelpSet) {
    u8* weapon = (u8*)evtGetValue(event, event->args[0]);
    BattleAcHelpSetHelp(BEC_FIELD(weapon, 0x70, const char*));
    BattleAcHelpSetDispType(2);
    return EVT_RETURN_DONE;
}
/* half_A end PRE */

//s32* battleId, s32* windowStartFrame, s32* windowEndFrame, s32* endFrame, s32* earlyFrames
USER_FUNC(btlevtcmd_ACRStart) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, windowStartFrame, windowEndFrame, endFrame, earlyFrames;

    if (isFirstCall) {
        id = evtGetValue(event, args[0]);
        id = BattleTransID(event, id);
        windowStartFrame = evtGetValue(event, args[1]);
        windowEndFrame = evtGetValue(event, args[2]);
        endFrame = evtGetValue(event, args[3]);
        earlyFrames = evtGetValue(event, args[4]);
        BattleAcrobatStart(wp, id, windowStartFrame, windowEndFrame, endFrame, earlyFrames);
    }
    return BattleAcrobatMain(wp);
}

//s32 resultRetIndex, s32 frameRetIndex (can be EVTDAT_POINTER_MAX to skip)
USER_FUNC(btlevtcmd_ACRGetResult) {
    s32* args = event->args;
    s32 index1, index2, result, frame;

    index1 = args[0];
    index2 = args[1];
    BattleAcrobatGetResult(_battleWorkPointer, &result, &frame);
    if (index1 != EVTDAT_POINTER_MAX) {
        evtSetValue(event, index1, result);
    }
    if (index2 != EVTDAT_POINTER_MAX) {
        evtSetValue(event, index2, frame);
    }
    return EVT_RETURN_DONE;
}

/* half_A begin MID */
USER_FUNC(btlevtcmd_AudienceAppeal) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    if (unit) {
        BattleAudience_Case_Appeal(unit);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeChangeGroup) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;
    const char* name;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    name = (const char*)evtGetValue(event, args[2]);
    if (isFirstCall) {
        if (BEC_FIELD(part, 0x1C0, s32) != -1) {
            animPoseRelease(BEC_FIELD(part, 0x1C0, s32));
            BEC_FIELD(part, 0x1C0, s32) = -1;
        }
        animEffectAsync(name, 1);
    }
    if (!animEffectAsync(name, 1)) {
        return EVT_RETURN_BLOCK;
    }
    BEC_FIELD(part, 0x1C0, s32) = animPoseEntry(name, 1);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeChangePose) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;
    const char* name;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    name = (const char*)evtGetValue(event, args[2]);
    BtlUnit_SetAnim(part, name);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeChangePoseType) {
    s32* args = event->args;
    s32 type;
    BattleUnitPart* part;
    s32 id, pno;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    type = evtGetValue(event, args[2]);
    BtlUnit_GetPoseNameFromType(part, type);
    BtlUnit_SetAnimType(part, type);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeChangePoseDirect) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, pno;
    const char* name;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    name = (const char*)evtGetValue(event, args[2]);
    strcpy((char*)part + 0x1C4, name);
    BEC_FIELD(part, 0x204, u32) &= ~0x80;
    BEC_FIELD(part, 0x204, u32) &= ~0x10;
    animPoseSetAnim(BEC_FIELD(part, 0x1C0, s32), name, TRUE);
    BEC_FIELD(part, 0x215, u8) = 1;
    if (BtlUnit_CheckStatus(unit, 18)) {
        BEC_FIELD(part, 0x215, u8) = 7;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeWaitPlayComplete) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    if (isFirstCall) {
        event->userdata[0] = 1;
    }
    if (event->userdata[0] > 0) {
        event->userdata[0]--;
        return EVT_RETURN_BLOCK;
    }
    if (animPoseGetLoopTimes(BEC_FIELD(part, 0x1C0, s32)) < 1.0f) {
        return EVT_RETURN_BLOCK;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeWaitPlayLoopTiming) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;
    f32 loop;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    if (isFirstCall) {
        event->userdata[0] = 1;
        event->userdata[1] = 0;
        event->userdata[2] = 0;
    }
    if (__fabs(BEC_FIELD(animPoseGetAnimPosePtr(BEC_FIELD(part, 0x1C0, s32)), 0x44, f32)) < 0.01) {
        return EVT_RETURN_DONE;
    }
    loop = animPoseGetLoopTimes(BEC_FIELD(part, 0x1C0, s32));
    if (event->userdata[0] > 0) {
        event->userdata[0]--;
        return EVT_RETURN_BLOCK;
    }
    switch (event->userdata[1]) {
    case 0:
        event->userdata[2] = (s32)loop;
        event->userdata[1]++;
        return EVT_RETURN_BLOCK;
    }
    if ((s32)loop != event->userdata[2]) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}

USER_FUNC(btlevtcmd_SetTalkBodyId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, body;

    id = evtGetValue(event, args[0]);
    body = evtGetValue(event, args[1]);
    BEC_FIELD(BattleGetUnitPtr(wp, BattleTransID(event, id)), 0x2D0, s32) = body;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetTalkPose) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 name = args[1];
    BEC_FIELD(BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id)), 0x2D4, s32) = name;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetStayPose) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 name = args[1];
    BEC_FIELD(BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id)), 0x2D8, s32) = name;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetTalkPoseType) {
    s32* args = event->args;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, type, body;

    id = evtGetValue(event, args[0]);
    type = evtGetValue(event, args[1]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    body = BtlUnit_GetBodyPartsId(unit);
    part = BattleGetUnitPartsPtr(id, body);
    BEC_FIELD(unit, 0x2D4, char*) = BtlUnit_GetPoseNameFromType(part, type);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetStayPoseType) {
    s32* args = event->args;
    BattleUnit* unit;
    BattleUnitPart* part;
    s32 id, type, body;

    id = evtGetValue(event, args[0]);
    type = evtGetValue(event, args[1]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    body = BtlUnit_GetBodyPartsId(unit);
    part = BattleGetUnitPartsPtr(id, body);
    BEC_FIELD(unit, 0x2D8, char*) = BtlUnit_GetPoseNameFromType(part, type);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeCmpPoseType) {
    s32* args = event->args;
    s32 id, pno;
    s32 t1, t2;
    BattleUnitPart* part;
    s32 index;
    char* n1;
    char* n2;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    t1 = evtGetValue(event, args[2]);
    t2 = evtGetValue(event, args[3]);
    index = args[4];
    n1 = BtlUnit_GetPoseNameFromType(part, t1);
    n2 = BtlUnit_GetPoseNameFromType(part, t2);
    evtSetValue(event, index, strcmp(n1, n2) != 0);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeChangePoseFromTable) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    btlDispPoseAnime(part);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeSetPoseTable) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    BEC_FIELD(part, 0x1BC, s32) = args[2];
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeSetPoseSoundTable) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    BEC_FIELD(part, 0x4D0, s32) = args[2];
    BtlUnit_PoseSoundInit(part);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckDefinePosetype) {
    s32* args = event->args;
    s32 type;
    BattleUnitPart* part;
    s32 id, pno;
    s32 out;
    s32* table;
    s32 res;
    s32 end;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    type = evtGetValue(event, args[2]);
    out = args[3];
    table = (s32*)BEC_FIELD(part, 0x1BC, void*);
    res = 0;
    if (type <= 28) {
        end = 28;
    } else if (type < 40) {
        end = 39;
    } else if (type < 70) {
        end = 69;
    } else {
        evtSetValue(event, out, 0);
        return EVT_RETURN_DONE;
    }
    for (; table; table += 2) {
        if (table[0] >= 70) {
            res = 0;
            break;
        }
        if (table[0] == type) {
            res = 1;
            break;
        }
        if (table[0] == end) {
            res = 0;
            break;
        }
    }
    evtSetValue(event, out, res);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeSetMotionSpeed) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    BEC_FIELD(part, 0x20C, f32) = evtGetFloat(event, args[2]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeChangePaperGroup) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;
    const char* name;
    s32 value;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    name = (const char*)evtGetValue(event, args[2]);
    value = evtGetValue(event, args[3]);
    animPoseSetEffect(BEC_FIELD(part, 0x1C0, s32), name, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeChangePaperAnime) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;
    s32 value;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    value = evtGetValue(event, args[2]);
    btlDispChangePeraAnime(part, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AnimeFlagOnOff) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno;
    u32 flags, on;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    flags = args[2];
    on = evtGetValue(event, args[3]);
    if (on) {
        BEC_FIELD(part, 0x204, u32) |= flags;
    }
    else {
        BEC_FIELD(part, 0x204, u32) &= ~flags;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckGuardMotionEnable) {
    s32* args = event->args;
    s32 id, index;
    BOOL enable;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    enable = TRUE;
    if (BtlUnit_CheckStatus(unit, 1) || BtlUnit_CheckStatus(unit, 2) || BtlUnit_CheckStatus(unit, 9) ||
        BtlUnit_CheckStatus(unit, 11) || BtlUnit_CheckStatus(unit, 27) || BtlUnit_CheckStatus(unit, 18)) {
        enable = FALSE;
    }
    if (BtlUnit_CheckStatusFlag(unit, 1)) {
        enable = FALSE;
    }
    evtSetValue(event, index, enable);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckStatus) {
    s32* args = event->args;
    s32 id, index;
    s8 type;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    type = args[1];
    index = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (BtlUnit_CheckStatus(unit, type)) {
        evtSetValue(event, index, TRUE);
    }
    else {
        evtSetValue(event, index, FALSE);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OnOffStatus) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, turns, strength, onoff;
    s8 type;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    type = args[1];
    turns = evtGetValue(event, args[2]);
    strength = evtGetValue(event, args[3]);
    onoff = evtGetValue(event, args[4]);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (onoff) {
        BtlUnit_SetStatus(unit, type, (s8)turns, (s8)strength);
    }
    else {
        BtlUnit_SetStatus(unit, type, 0, 0);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ClearAllStatus) {
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    BtlUnit_ClearStatus(BattleGetUnitPtr(_battleWorkPointer, id));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OnStatusFlag) {
    s32* args = event->args;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    args = (s32*)args[1];
    BtlUnit_OnStatusFlag(BattleGetUnitPtr(_battleWorkPointer, id), (u32)args);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OffStatusFlag) {
    s32* args = event->args;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    args = (s32*)args[1];
    BtlUnit_OffStatusFlag(BattleGetUnitPtr(_battleWorkPointer, id), (u32)args);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckActStatus) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 index = args[1];
    if (BtlUnit_CanActStatus(BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id)))) {
        evtSetValue(event, index, TRUE);
    }
    else {
        evtSetValue(event, index, FALSE);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetACPossibility) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 index = args[1];
    if (BtlUnit_GetACPossibility(BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id)))) {
        evtSetValue(event, index, TRUE);
    }
    else {
        evtSetValue(event, index, FALSE);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckUnitFlag) {
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, index;
    s32 flags;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    flags = args[1];
    index = args[2];
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (BtlUnit_CheckUnitFlag(unit, flags)) {
        evtSetValue(event, index, TRUE);
    }
    else {
        evtSetValue(event, index, FALSE);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OnUnitFlag) {
    s32* args = event->args;
    s32 id;
    s32 flags;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    args = (s32*)args[1];
    BtlUnit_OnUnitFlag(BattleGetUnitPtr(_battleWorkPointer, id), (u32)args);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_OffUnitFlag) {
    s32* args = event->args;
    s32 id;
    s32 flags;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    args = (s32*)args[1];
    BtlUnit_OffUnitFlag(BattleGetUnitPtr(_battleWorkPointer, id), (u32)args);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_AfterReactionEntry) {
    s32* args = event->args;
    s32 id, value;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    value = evtGetValue(event, args[1]);
    BattleAfterReactionEntry(id, value);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CheckWeaponPluralTarget) {
    s32* args = event->args;
    u8* weapon = (u8*)evtGetValue(event, args[0]);
    s32 out;
    out = args[1];
    if (BEC_FIELD(weapon, 0x64, u32) & 0x1000000) {
        evtSetValue(event, out, 0);
    }
    else {
        evtSetValue(event, out, 1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_PayWeaponCost) {
    s32* args = event->args;
    BattleWeapon* weapon;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    weapon = (BattleWeapon*)evtGetValue(event, args[1]);
    BtlUnit_PayWeaponCost(BattleGetUnitPtr(_battleWorkPointer, id), weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CommandPayWeaponCost) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    void* weapon;
    s32 id;

    id = evtGetValue(event, event->args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    weapon = BattleGetSelectWeapon(wp);
    BtlUnit_PayWeaponCost(unit, weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetWeaponActionLv) {
    s32* args = event->args;
    u8* weapon = (u8*)evtGetValue(event, args[0]);
    evtSetValue(event, args[1], weapon[0x6E]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CommandGetWeaponActionLv) {
    s32 index = event->args[0];
    u8* weapon = (u8*)BattleGetSelectWeapon(_battleWorkPointer);
    evtSetValue(event, index, weapon[0x6E]);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CommandGetWeaponAddress) {
    BattleWork* wp = _battleWorkPointer;
    s32* args = event->args;
    BattleUnit* unit;
    s32 id, index, kind;
    void* weapon;

    id = evtGetValue(event, args[0]);
    index = args[1];
    unit = BattleGetUnitPtr(_battleWorkPointer, BattleTransID(event, id));
    kind = BEC_FIELD(unit, 0x8, s32);
    if (kind == 0xDE || (kind >= 0xE0 && kind < 0xE7)) {
        weapon = BattleGetSelectWeapon(wp);
    }
    else {
        weapon = itemDataTable[BEC_FIELD(unit, 0x304, s32)].battle_params;
    }
    evtSetValue(event, index, (s32)weapon);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_CommandGetWeaponItemId) {
    s32* args = event->args;
    s32 index = args[0];
    u8* weapon = (u8*)evtGetValue(event, args[1]);
    evtSetValue(event, index, BEC_FIELD(weapon, 0x8, s32));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetItemRecoverParam) {
    s32* args = event->args;
    s32 id, a, b, c;
    u8* item;

    id = evtGetValue(event, args[0]);
    a = args[1];
    b = args[2];
    c = args[3];
    item = (u8*)&itemDataTable[id];
    if (a != EVTDAT_POINTER_MAX) {
        evtSetValue(event, a, item[0x1D]);
    }
    if (b != EVTDAT_POINTER_MAX) {
        evtSetValue(event, b, item[0x1E]);
    }
    if (c != EVTDAT_POINTER_MAX) {
        evtSetValue(event, c, item[0x1F]);
    }
    return EVT_RETURN_DONE;
}

void BattleStage_DestroyA1(void);
void BattleStage_DestroyA2(void);
void BattleStage_DestroyB(void);
void BattleStage_NozzleDirChangeCheck(void);
void BattleStage_NozzleWorkCheck(s32);
void BattleStage_IronFrameFallCheck(void);
void BattleStage_ObjectFallCheck(void);

USER_FUNC(btlevtcmd_WeaponAftereffect) {
    BattleWork* wp = _battleWorkPointer;
    u8* w = (u8*)evtGetValue(event, event->args[0]);
    s32 a1, a2, b;
    s32 r;
    u32 flags;
    u8 st;

    b = 0;
    a2 = 0;
    a1 = 0;
    r = irand(w[0xB4] + w[0xB5] + w[0xB6] + w[0xB7]);
    flags = BEC_FIELD(wp, 0x19068, u32);
    if (flags & 0x10) a1 = 1;
    if (flags & 0x20) a2 = 1;
    if ((r -= w[0xB4]) < 0) {
        a2 = 1;
        a1 = 1;
    }
    else if ((r -= w[0xB5]) < 0) {
        a1 = 1;
    }
    else if ((r -= w[0xB6]) < 0) {
        a2 = 1;
    }
    st = wp->field_180DC;
    if (st & 4) a2 = 0;
    if (st & 2) a1 = 0;
    if ((st & 2) && !(st & 8)) {
        if (irand(100) < w[0xB8] || (BEC_FIELD(wp, 0x19068, u32) & 0x40)) {
            b = 1;
            if (!(wp->field_180DC & 4)) a2 = 1;
        }
    }
    if (a1) BattleStage_DestroyA1();
    if (a2) BattleStage_DestroyA2();
    if (b) BattleStage_DestroyB();
    if (irand(100) < w[0xB9] || (BEC_FIELD(wp, 0x19068, u32) & 0x200)) BattleStage_NozzleDirChangeCheck();
    if (irand(100) < w[0xBA] || (BEC_FIELD(wp, 0x19068, u32) & 0x100)) BattleStage_NozzleWorkCheck(1);
    if (irand(100) < w[0xBB] || (BEC_FIELD(wp, 0x19068, u32) & 0x80)) BattleStage_IronFrameFallCheck();
    if (wp->field_180DC & 0x20) {
        if (BEC_FIELD(wp, 0x19068, u32) & 1) {
            BattleStage_ObjectFallCheck();
        }
        else if (irand(100) < w[0xBC]) {
            BattleStage_ObjectFallCheck();
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetGuard) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id, btlId;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    btlId = evtGetValue(event, args[1]);
    BEC_FIELD(unit, 0x13C, s32) = BattleTransID(event, btlId);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetGuardKouraId) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32* koura;
    s32 id, index;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    index = args[1];
    unit = BattleGetUnitPtr(wp, id);
    koura = (s32*)BtlUnit_GetGuardKouraPtr(unit);
    if (koura) {
        evtSetValue(event, index, *koura);
    }
    else {
        evtSetValue(event, index, -1);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_InterruptStop) {
    s32 type = evtGetValue(event, event->args[0]);
    BattleWork* wp = _battleWorkPointer;

    if (isFirstCall) {
        switch (type) {
            case 0:
                wp->flags |= 0x10;
                break;
            case 1:
                wp->flags |= 0x20;
                break;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SortPhaseMoveTable) {
    battleSortPhaseMoveTable(_battleWorkPointer, -1);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetStageSize) {
    s32* args = event->args;
    BattleStage* stage = BattleStageGetPtr();
    s32 x = args[0];
    s32 y = args[1];
    s32 z = args[2];

    if (x != EVTDAT_POINTER_MAX) {
        evtSetValue(event, x, BEC_FIELD(stage, 0xB24, f32));
    }
    if (y != EVTDAT_POINTER_MAX) {
        evtSetValue(event, y, BEC_FIELD(stage, 0xB28, f32));
    }
    if (z != EVTDAT_POINTER_MAX) {
        evtSetValue(event, z, BEC_FIELD(stage, 0xB2C, f32));
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_GetStageAudienceAreaSize) {
    s32* args = event->args;
    BattleStage* stage = BattleStageGetPtr();
    s32 x = args[0];
    s32 y = args[1];
    s32 z = args[2];

    if (x != EVTDAT_POINTER_MAX) {
        evtSetValue(event, x, BEC_FIELD(stage, 0xB30, f32));
    }
    if (y != EVTDAT_POINTER_MAX) {
        evtSetValue(event, y, BEC_FIELD(stage, 0xB34, f32));
    }
    if (z != EVTDAT_POINTER_MAX) {
        evtSetValue(event, z, BEC_FIELD(stage, 0xB38, f32));
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_TransStageFloorPosition) {
    s32* args = event->args;
    s32 index;
    f32 x, z;

    x = evtGetValue(event, args[0]);
    index = args[1];
    z = evtGetValue(event, args[2]);
    evtSetValue(event, index, BattleGetFloorHeight(_battleWorkPointer, x, 0.0f, z));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetMoveSoundDataWork) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;
    const char* name0;
    const char* name1;
    s32 c, d, e;
    s16 f, g;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    name0 = (const char*)evtGetValue(event, args[1]);
    name1 = (const char*)evtGetValue(event, args[2]);
    c = evtGetValue(event, args[3]);
    d = evtGetValue(event, args[4]);
    e = evtGetValue(event, args[5]);
    f = evtGetValue(event, args[6]);
    g = evtGetValue(event, args[7]);
    BtlUnit_SetSeMode((u8*)unit + 0x188, name0, name1, c, d, e, f, g);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetRunSound) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;
    s32 a, b, c, d, e;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    a = evtGetValue(event, args[1]);
    b = evtGetValue(event, args[2]);
    c = evtGetValue(event, args[3]);
    d = evtGetValue(event, args[4]);
    e = evtGetValue(event, args[5]);
    BEC_FIELD(unit, 0x1C8, s32) = a;
    BEC_FIELD(unit, 0x1C8 + 4, s32) = b;
    BEC_FIELD(unit, 0x1C8 + 8, s16) = c;
    BEC_FIELD(unit, 0x1C8 + 0xA, s16) = d;
    BEC_FIELD(unit, 0x1C8 + 0xC, s16) = e;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsRunSound) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno, a, b, c, d, e;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    a = evtGetValue(event, args[2]);
    b = evtGetValue(event, args[3]);
    c = evtGetValue(event, args[4]);
    d = evtGetValue(event, args[5]);
    e = evtGetValue(event, args[6]);
    BEC_FIELD(part, 0x100, s32) = a;
    BEC_FIELD(part, 0x100 + 4, s32) = b;
    BEC_FIELD(part, 0x100 + 8, s16) = c;
    BEC_FIELD(part, 0x100 + 0xA, s16) = d;
    BEC_FIELD(part, 0x100 + 0xC, s16) = e;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetWalkSound) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;
    s32 a, b, c, d, e;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    a = evtGetValue(event, args[1]);
    b = evtGetValue(event, args[2]);
    c = evtGetValue(event, args[3]);
    d = evtGetValue(event, args[4]);
    e = evtGetValue(event, args[5]);
    BEC_FIELD(unit, 0x1D8, s32) = a;
    BEC_FIELD(unit, 0x1D8 + 4, s32) = b;
    BEC_FIELD(unit, 0x1D8 + 8, s16) = c;
    BEC_FIELD(unit, 0x1D8 + 0xA, s16) = d;
    BEC_FIELD(unit, 0x1D8 + 0xC, s16) = e;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsWalkSound) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno, a, b, c, d, e;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    a = evtGetValue(event, args[2]);
    b = evtGetValue(event, args[3]);
    c = evtGetValue(event, args[4]);
    d = evtGetValue(event, args[5]);
    e = evtGetValue(event, args[6]);
    BEC_FIELD(part, 0x110, s32) = a;
    BEC_FIELD(part, 0x110 + 4, s32) = b;
    BEC_FIELD(part, 0x110 + 8, s16) = c;
    BEC_FIELD(part, 0x110 + 0xA, s16) = d;
    BEC_FIELD(part, 0x110 + 0xC, s16) = e;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetDiveSound) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;
    s32 a, b, c, d, e;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    a = evtGetValue(event, args[1]);
    b = evtGetValue(event, args[2]);
    c = evtGetValue(event, args[3]);
    d = evtGetValue(event, args[4]);
    e = evtGetValue(event, args[5]);
    BEC_FIELD(unit, 0x1E8, s32) = a;
    BEC_FIELD(unit, 0x1E8 + 4, s32) = b;
    BEC_FIELD(unit, 0x1E8 + 8, s16) = c;
    BEC_FIELD(unit, 0x1E8 + 0xA, s16) = d;
    BEC_FIELD(unit, 0x1E8 + 0xC, s16) = e;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsDiveSound) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno, a, b, c, d, e;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    a = evtGetValue(event, args[2]);
    b = evtGetValue(event, args[3]);
    c = evtGetValue(event, args[4]);
    d = evtGetValue(event, args[5]);
    e = evtGetValue(event, args[6]);
    BEC_FIELD(part, 0x120, s32) = a;
    BEC_FIELD(part, 0x120 + 4, s32) = b;
    BEC_FIELD(part, 0x120 + 8, s16) = c;
    BEC_FIELD(part, 0x120 + 0xA, s16) = d;
    BEC_FIELD(part, 0x120 + 0xC, s16) = e;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetJumpSound) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id;
    s32 a, b;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    a = evtGetValue(event, args[1]);
    b = evtGetValue(event, args[2]);
    BEC_FIELD(unit, 0x1C0, s32) = a;
    BEC_FIELD(unit, 0x1C4, s32) = b;
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SetPartsJumpSound) {
    s32* args = event->args;
    BattleUnitPart* part;
    s32 id, pno, a, b;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    pno = evtGetValue(event, args[1]);
    part = BattleGetUnitPartsPtr(id, pno);
    a = evtGetValue(event, args[2]);
    b = evtGetValue(event, args[3]);
    BEC_FIELD(part, 0xF8, s32) = a;
    BEC_FIELD(part, 0xFC, s32) = b;
    return EVT_RETURN_DONE;
}

#pragma dont_inline on
void _UnitMoveSoundControl(BattleUnit* unit) {
    f32 x, y, z;
    BtlUnit_GetPos(unit, &x, &y, &z);
    _MoveSoundControlCore(unit, (BecSndWork*)((u8*)unit + 0x188), NULL, x, y, z);
}

void _PartsMoveSoundControl(BattleUnitPart* part) {
    f32 x, y, z;
    BtlUnit_GetPartsPos(part, &x, &y, &z);
    _MoveSoundControlCore(part->mOwner, (BecSndWork*)((u8*)part + 0xC0), part, x, y, z);
}

void _MoveSoundControlCore(BattleUnit* unit, BecSndWork* work, BattleUnitPart* part, f32 x, f32 y, f32 z) {
    Vec pos;
    Vec cur;
    Vec tmp = {0.0f, 0.0f, 0.0f};
    const char* name;

    tmp.x = x;
    tmp.y = y;
    tmp.z = z;
    pos = tmp;
    if ((s32)work->name0 || (s32)work->name1) {
        if ((s32)work->name0 && !(s32)work->name1) {
            if (work->sfxId == 0xFFFFFFFF) {
                work->sfxId = BtlUnit_snd_se_pos(unit, work->name0, EVTDAT_POINTER_MAX, 0, &pos);
            }
            if (part) {
                BtlUnit_GetPartsWorldPos(part, &cur.x, &cur.y, &cur.z);
            }
            else {
                BtlUnit_GetPos(unit, &cur.x, &cur.y, &cur.z);
            }
            psndSFX_pos(work->sfxId, &cur);
        }
        else if (work->timer >= 0) {
            work->timer--;
            if (work->timer < 0) {
                work->count++;
                if (work->count & 1) {
                    name = work->name0;
                    work->timer = work->period0;
                }
                else {
                    name = work->name1;
                    work->timer = work->period1;
                }
                if ((s32)name) {
                    BtlUnit_snd_se_pos(unit, name, EVTDAT_POINTER_MAX, 0, &pos);
                }
            }
        }
    }
}

void _UnitMoveSoundControlEnd(BattleUnit* unit) {
    _MoveSoundControlEndCore(unit, (BecSndWork*)((u8*)unit + 0x188));
}

void _PartsMoveSoundControlEnd(BattleUnitPart* part) {
    _MoveSoundControlEndCore(part->mOwner, (BecSndWork*)((u8*)part + 0xC0));
}

void _MoveSoundControlEndCore(BattleUnit* unit, BecSndWork* work) {
    if ((u32)work->sfxId != 0xFFFFFFFF) {
        psndSFXOff(work->sfxId);
        work->sfxId = -1;
    }
}
#pragma dont_inline reset

USER_FUNC(btlevtcmd_snd_se) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    const char* name;
    s32 volume;
    BattleUnit* unit;
    s32 index, ret;
    s16 pitch;
    s32 id;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    name = (const char*)evtGetValue(event, args[1]);
    volume = evtGetValue(event, args[2]);
    pitch = evtGetValue(event, args[3]);
    index = args[4];
    ret = BtlUnit_snd_se(unit, name, volume, pitch);
    if ((index) != EVTDAT_POINTER_MAX) {
        evtSetValue(event, index, ret);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_snd_se_offset) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    s32 index;
    const char* name;
    s32 volume, ret;
    BattleUnit* unit;
    s16 pitch;
    Vec pos;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    name = (const char*)evtGetValue(event, args[1]);
    volume = evtGetValue(event, args[2]);
    pitch = evtGetValue(event, args[3]);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += evtGetFloat(event, args[4]);
    pos.y += evtGetFloat(event, args[5]);
    pos.z += evtGetFloat(event, args[6]);
    index = args[7];
    ret = BtlUnit_snd_se_pos(unit, name, volume, pitch, &pos);
    if (index != EVTDAT_POINTER_MAX) {
        evtSetValue(event, index, ret);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_snd_voice) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id, type;
    BattleUnit* unit;

    id = evtGetValue(event, args[0]);
    type = evtGetValue(event, args[1]);
    unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    switch (type) {
        case 1:
            BtlUnit_snd_se(unit, _mario_acrobat_voice_table[irand(5)], EVTDAT_POINTER_MAX, 0);
            break;
        case 2:
            BtlUnit_snd_se(unit, _mario_attack_voice_table[irand(10)], EVTDAT_POINTER_MAX, 0);
            break;
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_EnemyItemUseCheck) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit;
    s32 id, index;
    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(wp, id);
    index = args[1];
    evtSetValue(event, index, BattleEnemyUseItemCheck(unit));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_PadCheckTrigger) {
    s32* args = event->args;
    s32 chan = evtGetValue(event, args[0]);
    s32 mask = args[1];
    args = (s32*)args[2];
    if (BattlePadMultiCheckTrigger(chan, mask)) {
        evtSetValue(event, (s32)args, TRUE);
    }
    else {
        evtSetValue(event, (s32)args, FALSE);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_PadCheckNow) {
    s32* args = event->args;
    s32 chan = evtGetValue(event, args[0]);
    s32 mask = args[1];
    args = (s32*)args[2];
    if (BattlePadMultiCheckNow(chan, mask)) {
        evtSetValue(event, (s32)args, TRUE);
    }
    else {
        evtSetValue(event, (s32)args, FALSE);
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_InviteApInfoReport) {
    StarPowerInfo* info = &_battleWorkPointer->impendingBonuses;
    BattleAudience_ApRecoveryBuild(info);
    memset(info, 0, sizeof(StarPowerInfo));
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_SacBgsetMove) {
    BattleWork* wp = _battleWorkPointer;
    s32 on, i;
    BattleStageObject* obj;
    s32 mode;
    f32 val;
    s32 cnt;

    on = evtGetValue(event, event->args[0]);
    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    cnt = event->userdata[0] + 1;
    event->userdata[0] = cnt;
    mode = on ? 5 : 2;
    for (i = 0; i < 32; i++) {
        obj = &wp->stageObjects[i];
        if (obj->id > 0) {
            switch (obj->data->mLayer) {
                case 0:
                case 1:
                    if (on) {
                        if (obj->mPosition.x >= 0.0f) {
                            val = intplGetValue(mode, cnt, 45, 450.0f, 0.0f);
                        }
                        else {
                            val = -intplGetValue(mode, cnt, 45, 450.0f, 0.0f);
                        }
                    }
                    else {
                        if (obj->mPosition.x >= 0.0f) {
                            val = intplGetValue(mode, cnt, 45, 0.0f, 450.0f);
                        }
                        else {
                            val = -intplGetValue(mode, cnt, 45, 0.0f, 450.0f);
                        }
                    }
                    obj->field_0x28.x = val;
                    break;
                case 2:
                    if (on) {
                        val = intplGetValue(mode, cnt, 45, 260.0f, 0.0f);
                    }
                    else {
                        val = intplGetValue(mode, cnt, 45, 0.0f, 260.0f);
                    }
                    obj->field_0x28.y = val;
                    break;
            }
        }
    }
    return event->userdata[0] >= 45;
}

USER_FUNC(btlevtcmd_BtlStageObjFlagOnOff) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 i;
    BattleStageObject* obj;
    s32 onoff;
    const char* name;
    s32 flags;

    name = (const char*)evtGetValue(event, args[0]);
    flags = args[1];
    onoff = evtGetValue(event, args[2]);
    for (i = 0; i < 32; i++) {
        obj = &wp->stageObjects[i];
        if (obj->id > 0 && !strcmp(obj->data->name, name)) {
            if (onoff) {
                obj->mFlags |= flags;
            }
            else {
                obj->mFlags &= ~flags;
            }
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_BtlStageObjSetRotate) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 i;
    BattleStageObject* obj;
    const char* name;
    s32 xa, y, z, x, ya, za;

    name = (const char*)evtGetValue(event, args[0]);
    xa = args[1];
    x = evtGetValue(event, xa);
    ya = args[2];
    y = evtGetValue(event, ya);
    za = args[3];
    z = evtGetValue(event, za);
    for (i = 0; i < 32; i++) {
        obj = &wp->stageObjects[i];
        if (obj->id > 0 && !strcmp(obj->data->name, name)) {
            if (xa != EVTDAT_POINTER_MAX) {
                obj->mRotation.x = x;
            }
            if (ya != EVTDAT_POINTER_MAX) {
                obj->mRotation.y = y;
            }
            if (za != EVTDAT_POINTER_MAX) {
                obj->mRotation.z = z;
            }
            break;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_BtlStageObjGetRotate) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 i;
    BattleStageObject* obj;
    const char* name;
    s32 x, y, z;

    name = (const char*)evtGetValue(event, args[0]);
    x = args[1];
    y = args[2];
    z = args[3];
    for (i = 0; i < 32; i++) {
        obj = &wp->stageObjects[i];
        if (obj->id > 0 && !strcmp(obj->data->name, name)) {
            if (x != EVTDAT_POINTER_MAX) {
                evtSetFloat(event, x, obj->mRotation.x);
            }
            if (y != EVTDAT_POINTER_MAX) {
                evtSetFloat(event, y, obj->mRotation.y);
            }
            if (z != EVTDAT_POINTER_MAX) {
                evtSetFloat(event, z, obj->mRotation.z);
            }
            break;
        }
    }
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_StatusWindowOnOff) {
    BattleWork* wp = _battleWorkPointer;
    switch (evtGetValue(event, event->args[0])) {
        case 2:
            BEC_FIELD(wp, 0x2744, s32) = 1;
            break;
        case 1:
            BEC_FIELD(wp, 0x2748, s32) = 1;
            break;
        case 0:
            BEC_FIELD(wp, 0x2748, s32) = 0;
            break;
    }
    BattleStatusWindowCheck();
    return EVT_RETURN_DONE;
}
/* half_A end MID */

BOOL BattleFogForceStop(void);

USER_FUNC(btlevtcmd_StageDispellFog) {
    BattleFogForceStop();
    return EVT_RETURN_DONE;
}

/* half_A begin POST */
USER_FUNC(btlevtcmd_ftomsec) {
    s32* args = event->args;
    s32 value = evtGetValue(event, args[0]);
    evtSetValue(event, args[1], value * 1000 / 60);
    return EVT_RETURN_DONE;
}

USER_FUNC(btlevtcmd_ftof) {
    s32* args = event->args;
    s32 index, value, frames;
    value = evtGetValue(event, args[0]);
    index = args[1];
    frames = sysMsec2Frame(value * 1000 / 60);
    evtSetValue(event, index, frames);
    return EVT_RETURN_DONE;
}
/* half_A end POST */
