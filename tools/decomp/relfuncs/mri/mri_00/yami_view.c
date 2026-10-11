// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// decl: void envSetYamiView(Mtx mtx);
// proto: static USER_FUNC(yami_view);
static USER_FUNC(yami_view) {
    f32 x = evtGetFloat(event, event->args[0]);
    Mtx mtx;

    C_MTXLookAt(mtx, &(Vec){-100.0f + x, 100.0f, 0.0f}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){x, 0.0f, 0.0f});
    envSetYamiView(mtx);
    return EVT_RETURN_DONE;
}
