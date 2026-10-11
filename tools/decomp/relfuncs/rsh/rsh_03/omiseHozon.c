// include: driver/camdrv.h
// proto: USER_FUNC(omiseHozon);
USER_FUNC(omiseHozon) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);

    camPt = cam->cameraPos;
    camAt = cam->cameraAt;
    return EVT_RETURN_DONE;
}
