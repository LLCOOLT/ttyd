// include: driver/effdrv.h
// proto: USER_FUNC(eff_starstone_sound_off);
USER_FUNC(eff_starstone_sound_off) {
    *(u16*)((u8*)effNameToPtr((const char*)evtGetValue(event, event->args[0]))->userdata + 4) &= ~4;
    return EVT_RETURN_DONE;
}
