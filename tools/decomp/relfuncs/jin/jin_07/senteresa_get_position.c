// include: manager/evtmgr_cmd.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: USER_FUNC(senteresa_get_position);
USER_FUNC(senteresa_get_position) {
    s32* args = event->args;
    ExtPose* pose = extGetPosePtr();

    pose += evtGetValue(event, args[0]);
    evtSetFloat(event, args[1], pose->mtx[0][3]);
    evtSetFloat(event, args[2], pose->mtx[1][3]);
    evtSetFloat(event, args[3], pose->mtx[2][3]);
    return EVT_RETURN_DONE;
}
