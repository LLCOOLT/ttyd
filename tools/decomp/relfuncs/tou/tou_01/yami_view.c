// include: driver/camdrv.h
// include: dolphin/mtx.h
// decl: double sin(double x);
// decl: double cos(double x);
// decl: void envSetYamiView(Mtx mtx);
// proto: static USER_FUNC(yami_view);
static USER_FUNC(yami_view) {
    f32 s;
    f32 c;
    f32 dist = evtGetValue(event, event->args[0]);
    CameraEntry* camera = camGetPtr(4);
    f32 angle = 6.2831855f * (90.0f + camera->viewYaw) / 360.0f;
    f32 x;
    f32 z;
    f32 ox;
    f32 oz;
    Mtx view;

    s = sin(angle);
    c = cos(angle);
    x = dist * (f32)sin(angle);
    z = dist * -(f32)cos(angle);
    ox = -100.0f * s;
    oz = -100.0f * -c;

    C_MTXLookAt(view, &(Vec){ox + x, 100.0f, oz + z}, &(Vec){0.0f, 1.0f, 0.0f}, &(Vec){x, 0.0f, z});
    envSetYamiView(view);
    return EVT_RETURN_DONE;
}
