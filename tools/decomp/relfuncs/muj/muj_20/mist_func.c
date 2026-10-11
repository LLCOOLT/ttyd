// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: mario/mariost.h
// include: dolphin/os.h
// include: system.h
// decl: EffectEntry* effMistEntry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5);
// proto: USER_FUNC(mist_func);
USER_FUNC(mist_func) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    EffectEntry* eff;
    BOOL done = FALSE;

    if (isFirstCall) {
        x += irand(150) - 75;
        y += irand(150) - 75;
        z += irand(150) - 75;
        event->userdatap[1] = effMistEntry(0, 0, x, y, z, 0.0f);
        event->userdata[0] = 0;
    }
    eff = event->userdatap[1];
    switch (event->userdata[0]) {
        case 0:
            event->savedTime = gp->renderTime;
            event->userdata[2] = irand(1000) + 3000;
            event->userdata[0] = 1;
            break;
        case 1:
            if ((s32)OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime) > event->userdata[2]) {
                event->userdata[0] = 2;
            }
            break;
        case 2:
            done = TRUE;
            break;
    }
    if (!done) {
        return EVT_RETURN_BLOCK;
    }
    effSoftDelete(eff);
    return EVT_RETURN_DONE;
}
