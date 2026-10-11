// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// decl: u8 battenSatelliteTo_Init(BattleUnit* unit, s32 n, s32* table);
// decl: u8 battenSatelliteTo_Main(BattleUnit* unit, s32 n);
// proto: USER_FUNC(battenSatelliteToOutside);
USER_FUNC(battenSatelliteToOutside) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num = evtGetValue(event, args[1]);
    BattleUnit* unit;
    u8 moving;
    s32 i;

    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (isFirstCall) {
        switch (num) {
        case 1:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut1_1) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 2:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut2_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut2_2) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 3:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut3_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut3_2) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut3_3) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        case 4:
            i = 0;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_1) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_2) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_3) == TRUE) {
                    break;
                }
                i++;
            }
            i++;
            while (TRUE) {
                if (battenSatelliteTo_Init(unit, i, splineTableOut4_4) == TRUE) {
                    break;
                }
                i++;
            }
            break;
        default:
            return EVT_RETURN_DONE;
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
