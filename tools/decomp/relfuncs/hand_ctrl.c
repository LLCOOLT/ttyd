// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// proto: static USER_FUNC(hand_ctrl);
static USER_FUNC(hand_ctrl) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    s8 turns;
    s8 strength;
    BattleUnitPart* part;
    f32* dest;
    Vec* scale;
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    s32 j;

    if (unit == NULL) {
        return EVT_RETURN_BLOCK;
    }
    BtlUnit_GetStatus(unit, 2, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    BtlUnit_GetStatus(unit, 9, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    BtlUnit_GetStatus(unit, 1, &turns, &strength);
    if (turns > 0) {
        return EVT_RETURN_DONE;
    }
    for (j = 0, i = 2; i <= 5; i++, j++) {
        part = BtlUnit_GetPartsPtr(unit, i);
        dest = (f32*)unit->work[j];
        scale = &part->mBaseScale;
        x = part->mPositionOffset.x * scale->x;
        y = part->mPositionOffset.y * scale->y;
        z = part->mPositionOffset.z * scale->z;
        x += (dest[0] - x) / 10.0f;
        y += (dest[1] - y) / 10.0f;
        z += (dest[2] - z) / 10.0f;
        part->mPositionOffset.x = x;
        part->mPositionOffset.y = y;
        part->mPositionOffset.z = z;
    }
    return EVT_RETURN_DONE;
}
