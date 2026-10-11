// include: mario/mario.h
// include: driver/camdrv.h
// decl: void camFollowYOn(void);
// proto: USER_FUNC(bg_cam_chk);
USER_FUNC(bg_cam_chk) {
    CameraEntry* camera = camGetPtr(4);

    if (marioBgmodeChk() && (camera->flags & 0x10) && marioGetPtr()->airTimer == 0) {
        camFollowYOn();
    }
    return EVT_RETURN_BLOCK;
}
