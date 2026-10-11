// include: driver/camdrv.h
// include: mario/mariost.h
// include: manager/evtmgr_cmd.h
// decl: double sin(double x);
// proto: USER_FUNC(cam_r);
USER_FUNC(cam_r) {
    f32 roll = evtGetFloat(event, event->args[0]);
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 s;

    if (!roll) {
        cam->rollAngle = 0.0f;
        cam->viewOffset.z = 0.0f;
    } else {
        cam->rollAngle = roll;
        s = sin(gp->retraceCount / 10.0f);
        cam->viewOffset.z = -__fabsf(15.0f * s);
        cam->cameraPos.y = 97.0f;
        cam->cameraAt.y = 45.0f;
    }
    return EVT_RETURN_DONE;
}
