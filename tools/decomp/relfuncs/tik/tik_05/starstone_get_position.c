// include: driver/effdrv.h
// proto: USER_FUNC(starstone_get_position);
USER_FUNC(starstone_get_position) {
    s32* args = event->args;
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, args[0]));
    f32 x = ((f32*)eff->userdata)[2];
    f32 y = ((f32*)eff->userdata)[3];
    f32 z = ((f32*)eff->userdata)[4];

    evtSetFloat(event, args[1], x);
    evtSetFloat(event, args[2], y);
    evtSetFloat(event, args[3], z);
    return EVT_RETURN_DONE;
}
