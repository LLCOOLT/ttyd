// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// proto: void computeMtx(ExtPose* pose, f32 angle);
void computeMtx(ExtPose* pose, f32 angle) {
    Mtx m;

    PSMTXRotRad(m, 'Y', 0.017453292f * angle);
    pose->mtx[0][0] = m[0][0];
    pose->mtx[0][1] = m[0][1];
    pose->mtx[0][2] = m[0][2];
    pose->mtx[1][0] = m[1][0];
    pose->mtx[1][1] = m[1][1];
    pose->mtx[1][2] = m[1][2];
    pose->mtx[2][0] = m[2][0];
    pose->mtx[2][1] = m[2][1];
    pose->mtx[2][2] = m[2][2];
}
