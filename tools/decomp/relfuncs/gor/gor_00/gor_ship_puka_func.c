// decl: extern f32 gor_ship_puka_data[];
// proto: USER_FUNC(gor_ship_puka_func);
USER_FUNC(gor_ship_puka_func) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    f32 f = evtGetFloat(event, args[1]);
    evtSetFloat(event, args[2], f * gor_ship_puka_data[idx & 0xF]);
    return EVT_RETURN_DONE;
}
