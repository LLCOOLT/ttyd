// include: driver/effdrv.h
// include: mario/mario.h
// proto: USER_FUNC(map_bgmode_end);
USER_FUNC(map_bgmode_end) {
    s32* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    EffectEntry* eff;

    eff = effNameToPtr(name1);
    ((s32*)eff->userdata)[14] = 4;
    eff = effNameToPtr(name2);
    ((s32*)eff->userdata)[10] = 4;
    marioSetCamId(4);
    return EVT_RETURN_DONE;
}
