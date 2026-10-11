// include: driver/effdrv.h
// include: mario/mario.h
// proto: USER_FUNC(map_bgmode);
USER_FUNC(map_bgmode) {
    s32* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    EffectEntry* eff = effNameToPtr(name1);

    ((s32*)eff->userdata)[14] = 5;
    ((f32*)eff->userdata)[5] = 4.3f;
    eff = effNameToPtr(name2);
    ((s32*)eff->userdata)[10] = 5;
    marioSetCamId(5);
    return EVT_RETURN_DONE;
}
