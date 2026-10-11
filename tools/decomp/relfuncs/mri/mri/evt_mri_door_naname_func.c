// include: manager/evtmgr_cmd.h
// include: mario/mariost.h
// include: dolphin/os.h
// include: system.h
// decl: void mapObjTranslate(const char* name, f32 x, f32 y, f32 z);
// proto: USER_FUNC(evt_mri_door_naname_func);
USER_FUNC(evt_mri_door_naname_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x0 = evtGetFloat(event, args[1]);
    f32 z0 = evtGetFloat(event, args[2]);
    f32 x1 = evtGetFloat(event, args[3]);
    f32 z1 = evtGetFloat(event, args[4]);
    s32 frames = evtGetValue(event, args[5]);
    s32 mode = evtGetValue(event, args[6]);
    s32 elapsed;

    if (isFirstCall) {
        event->savedTime = gp->renderTime;
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    if (elapsed < frames) {
        f32 x;
        f32 z;
        isFirstCall = elapsed;
        x = intplGetValue(mode, isFirstCall, frames, x0, x1);
        z = intplGetValue(mode, isFirstCall, frames, z0, z1);
        mapObjTranslate(name, x, 0.0f, z);
        return EVT_RETURN_BLOCK;
    }
    mapObjTranslate(name, x1, 0.0f, z1);
    return EVT_RETURN_DONE;
}
