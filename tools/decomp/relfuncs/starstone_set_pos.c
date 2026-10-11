// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(starstone_set_pos);
USER_FUNC(starstone_set_pos) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    EffectEntry* eff = effNameToPtr(name);

    ((f32*)eff->userdata)[2] = x;
    ((f32*)eff->userdata)[3] = y;
    ((f32*)eff->userdata)[4] = z;
    return EVT_RETURN_DONE;
}
