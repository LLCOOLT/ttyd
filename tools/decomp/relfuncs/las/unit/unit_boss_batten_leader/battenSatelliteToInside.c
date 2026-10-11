// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// decl: u8 battenSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
// decl: u8 battenSatelliteTo_Main(BattleUnit* unit, s32 n);
// proto: USER_FUNC(battenSatelliteToInside);
USER_FUNC(battenSatelliteToInside) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        for (i = 0; i < 4; i++) {
            if (unit->work[9 + i] != -1) {
                s32 table = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[9 + i]), 1)->work[1];

                if (table == (s32)splineTableOut1_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn1_1);
                }
                if (table == (s32)splineTableOut2_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn2_1);
                }
                if (table == (s32)splineTableOut2_2) {
                    battenSatelliteTo_Init(unit, i, splineTableIn2_2);
                }
                if (table == (s32)splineTableOut3_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn3_1);
                }
                if (table == (s32)splineTableOut3_2) {
                    battenSatelliteTo_Init(unit, i, splineTableIn3_2);
                }
                if (table == (s32)splineTableOut3_3) {
                    battenSatelliteTo_Init(unit, i, splineTableIn3_3);
                }
                if (table == (s32)splineTableOut4_1) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_1);
                }
                if (table == (s32)splineTableOut4_2) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_2);
                }
                if (table == (s32)splineTableOut4_3) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_3);
                }
                if (table == (s32)splineTableOut4_4) {
                    battenSatelliteTo_Init(unit, i, splineTableIn4_4);
                }
            }
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (battenSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
