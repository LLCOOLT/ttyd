// include: driver/camdrv.h
// include: manager/evtmgr_cmd.h
// decl: double sin(double x);
// decl: double cos(double x);
// proto: USER_FUNC(yami_oowareru_check);
USER_FUNC(yami_oowareru_check) {
    s32* args = event->args;
    f32 limit = evtGetFloat(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    CameraEntry* camera = camGetPtr(4);
    f32 s;
    f32 c;
    f32 angle = 6.2831855f * (90.0f + camera->viewYaw) / 360.0f;

    s = sin(angle);
    c = cos(angle);

    if (s * x + -c * z < limit) {
        evtSetValue(event, args[3], TRUE);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[3], FALSE);
    return EVT_RETURN_BLOCK;
}
