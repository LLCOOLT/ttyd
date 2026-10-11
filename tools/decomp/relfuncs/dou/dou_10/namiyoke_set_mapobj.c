// include: manager/evtmgr_cmd.h
// decl: void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
// proto: USER_FUNC(namiyoke_set_mapobj);
USER_FUNC(namiyoke_set_mapobj) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);

    mapObjTranslate((const char*)namiyoke_mapobj[idx], x, y, z);
    return EVT_RETURN_DONE;
}
