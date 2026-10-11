// include: battle/battle_stage_object.h
// proto: USER_FUNC(_space_rotate);
USER_FUNC(_space_rotate) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 outVar = args[1];
    s32 step = evtGetValue(event, outVar);
    s32 total = evtGetValue(event, args[2]);
    BattleStageObject* obj = BattleSearchObjectPtr(name);

    obj->mRotation.z = 360.0f * step / total;
    step++;
    if (step >= total) {
        step = 0;
    }
    evtSetValue(event, outVar, step);
    return EVT_RETURN_DONE;
}
