// include: manager/evtmgr_cmd.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: USER_FUNC(senteresa_dispoff);
USER_FUNC(senteresa_dispoff) {
    ExtPose* pose = extGetPosePtr();
    s32 n = extGetPoseNum();
    s32 i;

    for (i = 0; i < n; i++, pose++) {
        pose->flags = 0;
    }
    return EVT_RETURN_DONE;
}
