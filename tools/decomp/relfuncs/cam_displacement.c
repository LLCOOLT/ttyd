// proto: USER_FUNC(cam_displacement);
void* camRoadGetWorkPtr(void);

USER_FUNC(cam_displacement) {
    u8* work = camRoadGetWorkPtr();

    *(f32*)(work + 0x1C4) = 1.7f;
    return EVT_RETURN_DONE;
}
