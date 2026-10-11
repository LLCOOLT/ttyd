// include: manager/evtmgr_cmd.h
// include: string.h
// decl: typedef struct CamRoadWork { u8 field_0x0[0xD8]; s32 field_0xD8; u8 field_0xDC[0xFC - 0xDC]; char* curveName; } CamRoadWork;
// decl: CamRoadWork* camRoadGetWorkPtr(void);
// decl: char* camstring;
// proto: USER_FUNC(get_camcurve);
USER_FUNC(get_camcurve) {
    s32* args = event->args;
    CamRoadWork* road = camRoadGetWorkPtr();
    s32 ret = 0;

    if (road->field_0xD8 != 0 && road->curveName != NULL) {
        if (!strcmp(road->curveName, "|MarioSt_CameraRoad|C_ground_ok") && !strcmp(camstring, "|MarioSt_CameraRoad|C_ue")) {
            ret = 1;
        }
        strcpy(camstring, road->curveName);
    }
    evtSetValue(event, args[0], ret);
    return EVT_RETURN_DONE;
}
