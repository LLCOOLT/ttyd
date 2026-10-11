// include: driver/effdrv.h
// proto: static USER_FUNC(starstone_set_ry);
static USER_FUNC(starstone_set_ry) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 ry = evtGetFloat(event, args[1]);
    EffectEntry* eff = effNameToPtr(name);

    ((f32*)eff->userdata)[7] = ry - 360.0f * ((s32)ry / 360);
    return EVT_RETURN_DONE;
}
