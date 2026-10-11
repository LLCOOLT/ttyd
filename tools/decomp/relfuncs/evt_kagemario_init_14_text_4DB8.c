// include: mario/mario.h
// include: driver/mapdrv.h
// include: driver/animdrv.h
// decl: static s32 color_change_evt(s32 on);
// include: driver/swdrv.h
// proto: USER_FUNC(evt_kagemario_init_14_text_4DB8);
USER_FUNC(evt_kagemario_init_14_text_4DB8) {
    s32 sequence = swByteGet(0);

    if (sequence >= 201 && sequence < 212) {
        color_change_evt(1);
        evtEntry(evt_check, 0, 0);
    } else {
        color_change_evt(0);
    }
    return EVT_RETURN_DONE;
}
