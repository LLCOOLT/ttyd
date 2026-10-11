// include: driver/mapdrv.h
// include: evt/evt_cmd.h
// decl: void envGlareFilter(s32 on, s16 x0, s16 y0, s16 x1, s16 y1);
// decl: void envGlareFilterZ(f32 z);
// proto: USER_FUNC(test_glare);
USER_FUNC(test_glare) {
    MapObject* sun = mapGetMapObj("sun");
    u16* rect;

    if (isFirstCall) {
        sun->flags |= 0x20000000;
        return EVT_RETURN_BLOCK;
    }
    rect = sun->screenRect;
    if (rect[0] == 0x3FF || rect[1] == 0x3FF || rect[2] == 0x3FF || rect[3] == 0x3FF) {
        envGlareFilter(0, 0, 0, 0, 0);
    } else if (rect[0] == 0 && rect[1] == 0 && rect[2] == 0 && rect[3] == 0) {
        envGlareFilter(0, 0, 0, 0, 0);
    } else if (evtGetValue(event, GF(15))) {
        envGlareFilter(0, 0, 0, 0, 0);
    } else {
        envGlareFilter(1, rect[1] - 50, rect[0] - 50, rect[3] + 50, rect[2] + 50);
    }
    return EVT_RETURN_BLOCK;
}
