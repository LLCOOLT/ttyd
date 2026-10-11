// include: manager/evtmgr_cmd.h
// include: dolphin/gx.h
// decl: void mapGrpSetColor(const char* name, GXColor color);
// proto: USER_FUNC(house03_f1_fade_func);
USER_FUNC(house03_f1_fade_func) {
    s32 v = evtGetValue(event, event->args[0]);

    mapGrpSetColor("S_i03_f1_naka", (GXColor){v, v, v, 0xFF});
    return EVT_RETURN_DONE;
}
