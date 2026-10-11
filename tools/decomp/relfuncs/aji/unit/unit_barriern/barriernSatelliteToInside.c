// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// decl: static u8 barriernSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
// decl: static u8 barriernSatelliteTo_Main(BattleUnit* unit, s32 n);
// proto: static USER_FUNC(barriernSatelliteToInside);
static USER_FUNC(barriernSatelliteToInside) {
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
            if (unit->work[4 + i] != -1) {
                s32 table = BtlUnit_GetPartsPtr(BattleGetUnitPtr(_battleWorkPointer, unit->work[4 + i]), 1)->work[2];

                if (table == (s32)splineTableOut1_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn1_1);
                }
                if (table == (s32)splineTableOut2_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn2_1);
                }
                if (table == (s32)splineTableOut2_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn2_2);
                }
                if (table == (s32)splineTableOut3_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_1);
                }
                if (table == (s32)splineTableOut3_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_2);
                }
                if (table == (s32)splineTableOut3_3) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn3_3);
                }
                if (table == (s32)splineTableOut4_1) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_1);
                }
                if (table == (s32)splineTableOut4_2) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_2);
                }
                if (table == (s32)splineTableOut4_3) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_3);
                }
                if (table == (s32)splineTableOut4_4) {
                    barriernSatelliteTo_Init(unit, i, splineTableIn4_4);
                }
            }
        }
    }
    moving = FALSE;
    for (i = 0; i < 4; i++) {
        if (barriernSatelliteTo_Main(unit, i) == TRUE) {
            moving = TRUE;
        }
    }
    return moving == FALSE ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
