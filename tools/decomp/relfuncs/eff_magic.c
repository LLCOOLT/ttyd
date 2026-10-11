// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: EffectEntry* effMagic1N64Entry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6, f32 arg7);
// proto: USER_FUNC(eff_magic);
USER_FUNC(eff_magic) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    f32 a = evtGetFloat(event, args[1]);
    f32 b = evtGetFloat(event, args[2]);
    f32 c = evtGetFloat(event, args[3]);
    s32 type = evtGetValue(event, args[4]);
    f32 x;
    f32 y;
    f32 z;
    EffectEntry* eff;

    BtlUnit_GetPos(unit, &x, &y, &z);
    // from the tip of the wand
    x += 25.0f * unit->mSizeMultiplier * unit->faceDirection;
    y += 20.0f * unit->mSizeMultiplier;
    z += 5.0f;
    eff = effMagic1N64Entry(0, type, x, y, z, a, b, c);
    unit->work[5] = (s32)eff;
    ((f32*)eff->userdata)[10] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}
