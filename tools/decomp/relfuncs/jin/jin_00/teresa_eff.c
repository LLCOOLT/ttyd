// include: manager/evtmgr_cmd.h
// include: eff/eff_teresa.h
// proto: USER_FUNC(teresa_eff);
USER_FUNC(teresa_eff) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    effTeresaEntry(0, x, y + 20.0f, z + 20.0f);
    return EVT_RETURN_DONE;
}
