// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(muj_ship_puka_func);
USER_FUNC(muj_ship_puka_func) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    f32 value = evtGetFloat(event, args[1]);

    evtSetFloat(event, args[2], value * ((f32*)muj_ship_puka_data)[index & 0xF]);
    return EVT_RETURN_DONE;
}
