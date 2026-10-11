// include: manager/evtmgr_cmd.h
// decl: typedef struct MapAnimRate { f32 fune; f32 funeTarget; f32 nami; f32 namiTarget; } MapAnimRate;
// decl: MapAnimRate mapAnimRate;
// proto: USER_FUNC(evt_set_nami_anim_rate);
USER_FUNC(evt_set_nami_anim_rate) {
    mapAnimRate.namiTarget = evtGetFloat(event, event->args[0]);
    return EVT_RETURN_DONE;
}
