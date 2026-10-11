// include: driver/effdrv.h
// proto: USER_FUNC(starstone_set_alpha);
USER_FUNC(starstone_set_alpha) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    u8 alpha = evtGetValue(event, args[1]);

    ((u8*)effNameToPtr(name)->userdata)[0x5F] = alpha;
    return EVT_RETURN_DONE;
}
