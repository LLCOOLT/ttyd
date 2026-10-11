// include: driver/effdrv.h
// include: system.h
// proto: USER_FUNC(kemuri_set_color);
USER_FUNC(kemuri_set_color) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    u8 r = evtGetValue(event, args[1]);
    u8 g = evtGetValue(event, args[2]);
    u8 b = evtGetValue(event, args[3]);
    EffectEntry* eff = effNameToPtr(name);

    ((u8*)eff->userdata)[0x38] = r;
    ((u8*)eff->userdata)[0x39] = g;
    ((u8*)eff->userdata)[0x3A] = b;
    ((f32*)eff->userdata)[6] = 1.0f + irand(30) / 10.0f;
    return EVT_RETURN_DONE;
}
