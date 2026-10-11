// include: eff/eff_kemu_test.h
// include: manager/evtmgr_cmd.h
// decl: void effKemuTestDrawCam(EffectEntry* effect, s32 camera);
// proto: USER_FUNC(bakuhatu_kemuri);
USER_FUNC(bakuhatu_kemuri) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);

    effKemuTestDrawCam(effKemuTestEntry(8, x, y, 0.0f, 2.5f), 8);
    return EVT_RETURN_DONE;
}
