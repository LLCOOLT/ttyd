// include: driver/effdrv.h
// proto: USER_FUNC(disp_treasure_map_func);
USER_FUNC(disp_treasure_map_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 ry = evtGetFloat(event, args[4]);
    u8 alpha = evtGetValue(event, args[5]);
    EffectEntry* eff = effNameToPtr(name);

    ((f32*)eff->userdata)[1] = x;
    ((f32*)eff->userdata)[2] = y;
    ((f32*)eff->userdata)[3] = z;
    ((f32*)eff->userdata)[8] = 180.0f + ry;
    ((s32*)eff->userdata)[5] = alpha;
    return EVT_RETURN_DONE;
}
