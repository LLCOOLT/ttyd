// include: mario/mario.h
// include: driver/mapdrv.h
// include: driver/animdrv.h
// decl: static s32 color_change_evt(s32 on);
// proto: USER_FUNC(evt_kagemario_change);
USER_FUNC(evt_kagemario_change) {
    color_change_evt(event->args[0]);
    return EVT_RETURN_DONE;
}
