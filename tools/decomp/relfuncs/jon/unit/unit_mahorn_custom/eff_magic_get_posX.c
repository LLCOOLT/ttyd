// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_sub.h
// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: static USER_FUNC(eff_magic_get_posX);
static USER_FUNC(eff_magic_get_posX) {
    s32* args = event->args;
    s32 id = BattleTransID(event, evtGetValue(event, *args++));
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, id);
    EffectEntry* eff = (EffectEntry*)unit->work[7];
    f32* work = eff->userdata;
    s32 i;

    for (i = 0; i < eff->count; i++, work += 15) {
        if (((s32*)work)[11] == 3) {
            evtSetFloat(event, *args++, work[1]);
            break;
        }
    }
    if (i == eff->count) {
        evtSetFloat(event, *args++, 0.0f);
    }
    return EVT_RETURN_DONE;
}
