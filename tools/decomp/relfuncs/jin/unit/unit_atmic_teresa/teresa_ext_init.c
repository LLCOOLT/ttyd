// include: battle/battle.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
// decl: AtmTeresa* teresa;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: void teresa_ext_init(void);
void teresa_ext_init(void) {
    s32 i;
    ExtPose* pose = extGetPosePtr();

    teresa = BattleAlloc(sizeof(AtmTeresa) * 30);
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        pose->flags = 1;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = 0.0f;
        pose->mtx[1][3] = -1000.0f;
        pose->mtx[2][3] = 0.0f;
        pose->rot = 90.0f;
        teresa[i].state = 0;
        teresa[i].flag = 0;
        teresa[i].anim = 0;
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            teresa[i].vel = zero;
        }
    }
}
