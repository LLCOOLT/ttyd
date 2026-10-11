// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: memory.h
// decl: void BtlUnit_SetAnim(BattleUnitPart* part, const char* anim);
// proto: static USER_FUNC(hand_init);
static USER_FUNC(hand_init) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, *args++);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    f32 x;
    f32 y;
    f32 z;
    f32* dest;
    s32 i;
    s32 j;

    BtlUnit_GetPos(unit, &x, &y, &z);
    for (j = 0, i = 2; i <= 5; i++, j++) {
        BtlUnit_SetAnim(BtlUnit_GetPartsPtr(unit, i), "MAH_Z_2");
        dest = __memAlloc((HEAP_TYPE)4, 12);
        unit->work[j] = (s32)dest;
        dest[0] = 0.0f;
        dest[1] = 0.0f;
        dest[2] = 0.0f;
    }
    return EVT_RETURN_DONE;
}
