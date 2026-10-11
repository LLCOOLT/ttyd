// include: driver/itemdrv.h
// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: typedef struct StoneEffWork2 { u8 field_0x0[0x1C]; f32 rot; } StoneEffWork2;
// proto: USER_FUNC(evt_boss_stone_r);
USER_FUNC(evt_boss_stone_r) {
    s32* args = event->args;
    EffectEntry* eff = itemNameToPtr("stone")->effect;

    ((StoneEffWork2*)eff->userdata)->rot = evtGetFloat(event, args[0]);
    return EVT_RETURN_DONE;
}
