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
    BattleUnit* unit;
    PouchData* pouch;
    BattleUnit* target;
    s32 itemVar;
    s32 iconVar;
    s32* args = event->args;
    s32 numVar;
    s32 item;
    s32 coins;
    s32 num;
    s32 count;
    s32 id;
    s32 i;
    s32 r;

    pouch = pouchGetPtr();
    id = evtGetValue(event, args[0]);
    id = BattleTransID(event, id);
    unit = BattleGetUnitPtr(_battleWorkPointer, id);
    if (unit == NULL) {
        return EVT_RETURN_DONE;
    }
    id = evtGetValue(event, args[1]);
    id = BattleTransID(event, id);
    target = BattleGetUnitPtr(_battleWorkPointer, id);
    if (target == NULL) {
        return EVT_RETURN_DONE;
    }
    itemVar = args[2];
    iconVar = args[3];
    numVar = args[4];
    evtSetValue(event, itemVar, 0);
    evtSetValue(event, iconVar, 0);
    evtSetValue(event, numVar, 0);
    if (irand(100) < 100) {
        coins = pouchGetCoin();
        num = 5;
        if (coins < 5) {
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
    item = 0;
    count = 0;
    for (i = 0; i < 20; i++) {
        if (pouch->heldItems[i] != 0) {
            count++;
        }
    }
    if (count <= 0) {
        return EVT_RETURN_DONE;
    }
    r = irand(count);
    if (r >= count) {
        r -= count;
        for (i = 0; i < 200; i++) {
            if (pouch->badges[i] != 0) {
                if (--r < 0) {
                    item = pouch->badges[i];
                    break;
                }
            }
        }
    } else {
        for (i = 0; i < 20; i++) {
            if (pouch->heldItems[i] != 0) {
                if (--r < 0) {
                    item = pouch->heldItems[i];
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
        evtSetValue(event, iconVar, *(u16*)&itemDataTable[item].icon_id);
    }
    return EVT_RETURN_DONE;
}
