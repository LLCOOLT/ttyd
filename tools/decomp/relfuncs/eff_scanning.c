// include: battle/battle.h
// include: battle/battle_sub.h
// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// proto: USER_FUNC(eff_scanning);
EffectEntry* effScanningEntry(s32 type, f32 x, f32 y, f32 z);

USER_FUNC(eff_scanning) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, args[0]));
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff = effScanningEntry(0, x, y, z);

    ((f32*)eff->userdata)[4] = unit->mSizeMultiplier;
    return EVT_RETURN_DONE;
}
