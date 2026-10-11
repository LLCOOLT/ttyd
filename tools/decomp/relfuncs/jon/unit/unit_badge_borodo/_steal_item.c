// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: mario/mario_pouch.h
// include: data/item_data.h
// include: system.h
// decl: extern ItemData itemDataTable[];
// decl: void BtlUnit_EquipItem(BattleUnit* unit, s32 flags, ItemType type);
// proto: USER_FUNC(_steal_item);
USER_FUNC(_steal_item) {
    s32* args = event->args;
    PouchData* pouch = pouchGetPtr();
    BattleUnit* unit;
    BattleUnit* target;
    s32 itemVar;
    s32 iconVar;
    s32 numVar;
    s32 id;
    s32 tid;

    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    tid = evtGetValue(event, args[1]);
    tid = BattleTransID(event, tid);
    target = BattleGetUnitPtr(_battleWorkPointer, tid);
    if (target == NULL) {
        return EVT_RETURN_DONE;
    }
    itemVar = args[2];
    iconVar = args[3];
    numVar = args[4];
    evtSetValue(event, itemVar, 0);
    evtSetValue(event, iconVar, 0);
    evtSetValue(event, numVar, 0);
    if (irand(100) < 40) {
        s32 coins = pouchGetCoin();
        s32 num = 10;

        if (coins < 10) {
            num = coins;
        }
        if (num > 0) {
            evtSetValue(event, itemVar, ITEM_COIN);
            evtSetValue(event, iconVar, 395);
            evtSetValue(event, numVar, num);
            unit->heldItem = ITEM_COIN;
            unit->field_0x30C[0] = num;
            pouchSetCoin(coins - num);
        }
        return EVT_RETURN_DONE;
    }
    {
        s32 item = 0;
        s32 count = 0;
        s32 held = 0;
        s32 r;
        s32 i;

        for (i = 0; i < 200; i++) {
            if (pouch->badges[i] != 0) {
                count++;
            }
        }
        if (count <= 0) {
            return EVT_RETURN_DONE;
        }
        r = irand(count);
        if (r >= held) {
            s32 j;

            r -= held;
            for (j = 0; j < 200; j++) {
                if (pouch->badges[j] != 0) {
                    if (--r < 0) {
                        item = pouch->badges[j];
                        break;
                    }
                }
            }
        } else {
            s32 k;

            for (k = 0; k < 20; k++) {
                if (pouch->heldItems[k] != 0) {
                    if (--r < 0) {
                        item = pouch->heldItems[k];
                        break;
                    }
                }
            }
        }
        if (item != 0) {
            if (!pouchRemoveItem(item)) {
                return EVT_RETURN_DONE;
            }
            unit->heldItem = item;
            if (item >= 240 && item < 339) {
                if (target->currentKind == 222) {
                    BtlUnit_EquipItem(target, 3, 0);
                } else if (target->currentKind >= 224 && target->currentKind < 231) {
                    BtlUnit_EquipItem(target, 5, 0);
                }
                pouchReviseMarioParam();
                pouchRevisePartyParam();
            }
            evtSetValue(event, itemVar, item);
            evtSetValue(event, iconVar, itemDataTable[item].icon_id);
        }
    }
    return EVT_RETURN_DONE;
}
