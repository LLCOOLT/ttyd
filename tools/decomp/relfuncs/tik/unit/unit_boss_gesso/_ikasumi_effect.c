// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// decl: EffectEntry* effOpukuJetwN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);
// proto: USER_FUNC(_ikasumi_effect);
USER_FUNC(_ikasumi_effect) {
    s32* args = event->args;
    BattleWork* wp = _battleWorkPointer;
    s32 id = evtGetValue(event, args[0]);
    s32 count = evtGetValue(event, args[1]);
    BattleUnit* unit = BattleGetUnitPtr(wp, BattleTransID(event, id));
    Vec pos;
    EffectEntry* eff;

    BtlUnit_GetPos(unit, &pos.x, &pos.y, &pos.z);
    pos.x -= 95.0f;
    pos.y += 75.0f;
    eff = effOpukuJetwN64Entry(0, count, pos.x, pos.y, pos.z, 2.0f);
    ((f32*)eff->userdata)[14] = 135.0f;
    ((s32*)eff->userdata)[6] = 0;
    ((s32*)eff->userdata)[7] = 0;
    ((s32*)eff->userdata)[8] = 0;
    ((s32*)eff->userdata)[10] = 0;
    ((s32*)eff->userdata)[11] = 0;
    ((s32*)eff->userdata)[12] = 0;
    return EVT_RETURN_DONE;
}
