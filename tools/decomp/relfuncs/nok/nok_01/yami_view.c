// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: USER_FUNC(yami_view);
void envSetYamiView(Mtx mtx);

USER_FUNC(yami_view) {
    f32 z = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){-100.0f + z, 100.0f, 0.0f}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){z, 0.0f, 0.0f});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}
