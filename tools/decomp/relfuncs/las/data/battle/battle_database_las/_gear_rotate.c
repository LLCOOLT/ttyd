// include: battle/battle_stage_object.h
// proto: USER_FUNC(_gear_rotate);
USER_FUNC(_gear_rotate) {
    s32* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    s32 frameVar = args[2];
    s32 frame = evtGetValue(event, frameVar);
    s32 total = evtGetValue(event, args[3]);
    s32 step = evtGetValue(event, args[4]);
    BattleStageObject* obj1 = BattleSearchObjectPtr(name1);
    BattleStageObject* obj2 = BattleSearchObjectPtr(name2);

    obj2->mRotation.z = obj1->mRotation.z = 360.0f * frame / total;
    frame += step;
    if (frame >= total) {
        frame = 0;
    }
    if (frame < 0) {
        frame = total - 1;
    }
    evtSetValue(event, frameVar, frame);
    return EVT_RETURN_DONE;
}
