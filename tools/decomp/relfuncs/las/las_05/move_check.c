// include: mario/mario.h
// decl: typedef struct Senkaron { s8 state; u16 area; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: typedef struct SenkaronWork { s32 attackStart; s32 escape; s32 mesPushing; s32 field_C; s32 marioPushed; s32 field_14; Senkaron* sk; } SenkaronWork;
// decl: SenkaronWork* skwp;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: void move_check(ExtPose* pose, s32 idx);
void move_check(ExtPose* pose, s32 idx) {
    MarioWork* mario;
    Senkaron* sk;
    ExtPose* pose2;
    s32 cnt;
    s32 j;

    extGetPosePtr();
    mario = marioGetPtr();
    sk = skwp->sk;
    cnt = extGetPoseNum() - (idx + 1);
    if (sk[idx].state == 1) {
        pose2 = pose + 1;
        for (j = idx + 1; cnt != 0; cnt--, j++, pose2++) {
            if (sk[j].state == 1 && sk[j].area == sk[idx].area) {
                f32 dx1 = __fabsf(pose->mtx[0][3] - mario->position.x);
                f32 dz1 = __fabsf(pose->mtx[2][3] - mario->position.z);
                f32 dx2 = __fabsf(pose2->mtx[0][3] - mario->position.x);
                f32 dz2 = __fabsf(pose2->mtx[2][3] - mario->position.z);

                if (dx1 * dx1 + dz1 * dz1 > dx2 * dx2 + dz2 * dz2) {
                    if (__fabsf(__fabsf(pose->mtx[0][3] - pose2->mtx[0][3]) - __fabsf(pose->mtx[2][3] - pose2->mtx[2][3])) < 20.0f) {
                        sk[idx].flags |= 2;
                    }
                } else {
                    sk[j].flags |= 2;
                }
            }
        }
    }
}
