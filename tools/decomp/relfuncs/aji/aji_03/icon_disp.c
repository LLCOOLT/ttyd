// include: driver/camdrv.h
// include: driver/icondrv.h
// include: dolphin/mtx.h
// proto: void icon_disp(CameraId camera, void* param);
void icon_disp(CameraId camera, void* param) {
    EventEntry* event = param;
    Mtx trans;
    Mtx scale;
    Mtx rot;

    camGetPtr(camera);
    if (event->userdata[0] == 0) {
        PSMTXTrans(trans, event->userdata[1] - 70, event->userdata[2], 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXRotRad(rot, 'z', 0.0f);
        PSMTXConcat(trans, scale, trans);
        PSMTXConcat(trans, rot, trans);
        iconDispGx2(trans, 0x10, 0x163);
        PSMTXTrans(trans, event->userdata[1], event->userdata[2], 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXConcat(trans, scale, trans);
        iconDispGx2(trans, 0x10, 0x64);
    } else {
        PSMTXTrans(trans, event->userdata[1] - 30, event->userdata[2] + 100, 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXRotRad(rot, 'z', 4.712389f);
        PSMTXConcat(trans, scale, trans);
        PSMTXConcat(trans, rot, trans);
        iconDispGx2(trans, 0x10, 0x163);
        PSMTXTrans(trans, event->userdata[1], event->userdata[2], 0.0f);
        PSMTXScale(scale, 1.5f, 1.5f, 1.5f);
        PSMTXConcat(trans, scale, trans);
        iconDispGx2(trans, 0x10, 0x66);
    }
}
