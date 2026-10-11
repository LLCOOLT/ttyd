// include: driver/effdrv.h
// proto: USER_FUNC(hokori_color_func);
USER_FUNC(hokori_color_func) {
    EffectEntry* effect = effNameToPtr((const char*)evtGetValue(event, event->args[0]));

    ((s32*)effect->userdata)[12] = 0x70;
    ((s32*)effect->userdata)[13] = 0x58;
    ((s32*)effect->userdata)[14] = 0x58;
    return EVT_RETURN_DONE;
}
