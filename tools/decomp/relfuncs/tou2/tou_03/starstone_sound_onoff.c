// include: driver/itemdrv.h
// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: typedef struct StoneEffWork3 { s32 field_0x0; u16 flags; } StoneEffWork3;
// proto: USER_FUNC(starstone_sound_onoff);
USER_FUNC(starstone_sound_onoff) {
    s32 flag = evtGetValue(event, event->args[0]);
    EffectEntry* eff = itemNameToPtr("stone")->effect;

    if (eff) {
        if (flag == 0) {
            ((StoneEffWork3*)eff->userdata)->flags &= ~4;
        }
        if (flag == 1) {
            ((StoneEffWork3*)eff->userdata)->flags |= 4;
        }
    }
    return EVT_RETURN_DONE;
}
