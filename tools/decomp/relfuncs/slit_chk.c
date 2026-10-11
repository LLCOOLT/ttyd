// include: mario/mario.h
// include: driver/camdrv.h
// proto: USER_FUNC(slit_chk);
USER_FUNC(slit_chk) {
    MarioWork* mario = marioGetPtr();

    if (mario->flags & 0x100000) {
        if ((mario->position.x < -200.0f || mario->position.x > 300.0f) && mario->position.y < 169.0f &&
            mario->position.y > 160.0f) {
            camCtrlOff(CAMERA_3D);
            evtStopID(event->lwData[0]);
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_BLOCK;
}
