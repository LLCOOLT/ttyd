// include: battle/battle_stage_object.h
// proto: USER_FUNC(_set_offset);
USER_FUNC(_set_offset) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 outVar = args[1];
    s32 step = evtGetValue(event, outVar);
    s32 total = evtGetValue(event, args[2]);
    s32 base = evtGetValue(event, args[3]);
    s32 amp = evtGetValue(event, args[4]);
    BattleStageObject* obj = BattleSearchObjectPtr(name);

    obj->field_0x10.x = base + amp * step / total;
    step--;
    if (step < 0) {
        step = total;
    }
    evtSetValue(event, outVar, step);
    return EVT_RETURN_DONE;
}
