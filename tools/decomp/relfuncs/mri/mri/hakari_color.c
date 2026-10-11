// include: mario/mariost.h
// include: dolphin/gx.h
// decl: void mapGrpSetColor(const char* name, GXColor color);
// decl: typedef struct HSV { u8 h; u8 s; u8 v; u8 a; } HSV;
// decl: GXColor HSV2RGB(HSV hsv);
// proto: USER_FUNC(hakari_color);
USER_FUNC(hakari_color) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 now = evtGetValue(event, args[1]);
    s32 max = evtGetValue(event, args[2]);

    if (now <= max) {
        mapGrpSetColor(name, HSV2RGB((HSV){gp->retraceCount, 0xFF, 0xFF, 0xFF}));
    } else {
        GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
        mapGrpSetColor(name, white);
    }
    return EVT_RETURN_DONE;
}
