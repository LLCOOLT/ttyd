// include: manager/evtmgr_cmd.h
// include: stdio.h
// include: pmario_sound.h
// decl: void mapObjGetPos(const char* name, Vec* pos);
// proto: USER_FUNC(hikari_se);
USER_FUNC(hikari_se) {
    char name[8];
    Vec pos;
    s32* args = event->args;
    s32 n = evtGetValue(event, args[0]);
    s32 off = evtGetValue(event, args[1]);
    s32 dark = evtGetValue(event, args[2]);

    sprintf(name, "hi%d", n);
    mapObjGetPos(name, &pos);
    if (!off) {
        if (!dark) {
            psndSFXOn_3D("SFX_STG8_CANDLE_ON1", &pos);
        } else {
            psndSFXOn_3D("SFX_STG8_CANDLE_DARK_ON1", &pos);
        }
    } else {
        if (!dark) {
            psndSFXOn_3D("SFX_STG8_CANDLE_OFF1", &pos);
        } else {
            psndSFXOn_3D("SFX_STG8_CANDLE_DARK_OFF1", &pos);
        }
    }
    return EVT_RETURN_DONE;
}
