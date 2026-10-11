// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// decl: EffectEntry* effPuniBalloonEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// decl: EffectEntry* marioeff;
// proto: USER_FUNC(mario_shabon_eff);
USER_FUNC(mario_shabon_eff) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);

    marioeff = effPuniBalloonEntry(type, x, y, evtGetFloat(event, args[3]), 2.5f);
    return EVT_RETURN_DONE;
}
