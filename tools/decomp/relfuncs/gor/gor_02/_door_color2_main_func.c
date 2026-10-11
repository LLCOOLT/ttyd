// include: manager/evtmgr_cmd.h
// include: dolphin/gx.h
// decl: typedef struct DoorColorWork { GXColor color; GXColor color2; } DoorColorWork;
// decl: DoorColorWork* _door;
// proto: USER_FUNC(_door_color2_main_func);
USER_FUNC(_door_color2_main_func) {
    s32* args = event->args;
    DoorColorWork* door = _door;

    door->color2.r = evtGetValue(event, args[0]);
    door->color2.g = evtGetValue(event, args[1]);
    door->color2.b = evtGetValue(event, args[2]);
    door->color2.a = evtGetValue(event, args[3]);
    return EVT_RETURN_DONE;
}
