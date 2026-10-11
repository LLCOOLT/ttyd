// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// decl: EffectEntry* effKumokumoN64Entry(s32 type, s32 time, f32 x, f32 y, f32 z, f32 arg5, f32 arg6, f32 scale);
// proto: USER_FUNC(_clauda_breath_effect_ready);
USER_FUNC(_clauda_breath_effect_ready) {
    BattleWork* wp = _battleWorkPointer;
    s32 id;
    BattleUnit* unit;
    Vec pos;
    EffectEntry* eff;

    id = BattleTransID(event, -2);
    unit = BattleGetUnitPtr(wp, id);
    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x += unit->mSizeMultiplier * (unit->faceDirection * 20);
    pos.y += 25.0f * unit->mSizeMultiplier;
    eff = effKumokumoN64Entry(0, 60, pos.x, pos.y, pos.z, 0.0f, 2.0f, 1.0f);
    ((s32*)eff->userdata)[6] = 76;
    ((s32*)eff->userdata)[7] = 167;
    ((s32*)eff->userdata)[8] = 202;
    ((s32*)eff->userdata)[10] = 125;
    ((s32*)eff->userdata)[11] = 27;
    ((s32*)eff->userdata)[12] = 245;
    return EVT_RETURN_DONE;
}
