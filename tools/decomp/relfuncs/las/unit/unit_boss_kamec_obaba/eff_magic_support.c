// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// decl: EffectEntry* effStardustEntry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 width, f32 height, s32 time);
// proto: USER_FUNC(eff_magic_support);
USER_FUNC(eff_magic_support) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    s32 type = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 x;
    f32 y;
    f32 z;

    BtlUnit_GetPos(unit, &x, &y, &z);
    switch (type) {
        case 0:
            x += 30.0f * unit->mSizeMultiplier * unit->faceDirection;
            y += 10.0f * unit->mSizeMultiplier;
            z += 5.0f;
            effStardustEntry(6, 5, x, y, z, 40.0f, 40.0f, 30);
            break;
        case 1:
            x += 30.0f * unit->mSizeMultiplier * unit->faceDirection;
            y += 50.0f * unit->mSizeMultiplier;
            z += 5.0f;
            effStardustEntry(6, 5, x, y, z, 40.0f, 40.0f, 30);
            break;
    }
    return EVT_RETURN_DONE;
}
