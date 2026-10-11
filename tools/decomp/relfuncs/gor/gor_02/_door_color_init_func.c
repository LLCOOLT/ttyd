// include: manager/evtmgr_cmd.h
// include: memory.h
// include: dolphin/gx.h
// decl: typedef struct DoorColorWork { GXColor color; GXColor color2; } DoorColorWork;
// decl: DoorColorWork* _door;
// proto: USER_FUNC(_door_color_init_func);
USER_FUNC(_door_color_init_func) {
    _door = _mapAlloc(sizeof(DoorColorWork));
    _door->color.r = 255;
    _door->color.g = 255;
    _door->color.b = 255;
    _door->color.a = 255;
    _door->color2.r = 255;
    _door->color2.g = 255;
    _door->color2.b = 255;
    _door->color2.a = 255;
    return EVT_RETURN_DONE;
}
