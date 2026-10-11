// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// decl: static void outSplineTableSet_Sub(BattleUnit* unit, s32 n, s32* table);
// proto: static USER_FUNC(outSplineTableSet);
static USER_FUNC(outSplineTableSet) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);

    switch (evtGetValue(event, args[1])) {
        case 1:
            outSplineTableSet_Sub(unit, 0, splineTableOut1_1);
            break;
        case 2:
            outSplineTableSet_Sub(unit, 0, splineTableOut2_1);
            outSplineTableSet_Sub(unit, 1, splineTableOut2_2);
            break;
        case 3:
            outSplineTableSet_Sub(unit, 0, splineTableOut3_1);
            outSplineTableSet_Sub(unit, 1, splineTableOut3_2);
            outSplineTableSet_Sub(unit, 2, splineTableOut3_3);
            break;
        case 4:
            outSplineTableSet_Sub(unit, 0, splineTableOut4_1);
            outSplineTableSet_Sub(unit, 1, splineTableOut4_2);
            outSplineTableSet_Sub(unit, 2, splineTableOut4_3);
            outSplineTableSet_Sub(unit, 3, splineTableOut4_4);
            break;
    }
    return EVT_RETURN_DONE;
}
