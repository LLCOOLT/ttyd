// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// proto: USER_FUNC(pcharge_set_pos);
USER_FUNC(pcharge_set_pos) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    EffectEntry* eff = effNameToPtr(name);

    ((f32*)eff->userdata)[1] = x;
    ((f32*)eff->userdata)[2] = y;
    ((f32*)eff->userdata)[3] = z;
    return EVT_RETURN_DONE;
}
