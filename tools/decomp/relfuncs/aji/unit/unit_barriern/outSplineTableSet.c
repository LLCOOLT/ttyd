// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// proto: static USER_FUNC(outSplineTableSet);
static USER_FUNC(outSplineTableSet) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    BattleUnitPart* part;

    switch (evtGetValue(event, args[1])) {
        case 1:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4]), 1);
            part->work[2] = (s32)splineTableOut1_1;
            break;
        case 2:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4]), 1);
            part->work[2] = (s32)splineTableOut2_1;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[5]), 1);
            part->work[2] = (s32)splineTableOut2_2;
            break;
        case 3:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4]), 1);
            part->work[2] = (s32)splineTableOut3_1;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[5]), 1);
            part->work[2] = (s32)splineTableOut3_2;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[6]), 1);
            part->work[2] = (s32)splineTableOut3_3;
            break;
        case 4:
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4]), 1);
            part->work[2] = (s32)splineTableOut4_1;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[5]), 1);
            part->work[2] = (s32)splineTableOut4_2;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[6]), 1);
            part->work[2] = (s32)splineTableOut4_3;
            part = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[7]), 1);
            part->work[2] = (s32)splineTableOut4_4;
            break;
    }
    return EVT_RETURN_DONE;
}
