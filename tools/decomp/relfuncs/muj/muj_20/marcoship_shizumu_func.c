// include: manager/evtmgr_cmd.h
// decl: void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
// proto: USER_FUNC(marcoship_shizumu_func);
USER_FUNC(marcoship_shizumu_func) {
    f32 y = evtGetFloat(event, event->args[0]);

    mapObjTranslate("S_a1", 0.0f, y, 0.0f);
    return EVT_RETURN_DONE;
}
