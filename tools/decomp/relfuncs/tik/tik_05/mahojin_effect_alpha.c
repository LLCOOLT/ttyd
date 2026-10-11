// include: driver/effdrv.h
// proto: USER_FUNC(mahojin_effect_alpha);
USER_FUNC(mahojin_effect_alpha) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    u8 alpha = evtGetValue(event, args[1]);

    ((s32*)effNameToPtr(name)->userdata)[8] = alpha;
    return EVT_RETURN_DONE;
}
