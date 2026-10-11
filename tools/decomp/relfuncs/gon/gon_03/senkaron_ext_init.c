// include: memory.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Senkaron { s8 state; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: Senkaron* senkaron;
// decl: s32 senkaronAttackStartFlag;
// decl: s32 senkaronEscapeFlag;
// decl: s32 senkaronMesPushingFlag;
// decl: s32 marioPushedFlag;
// decl: s32 marioHammerFrame;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static f32 randf(f32 min, f32 max);
// proto: static void senkaron_ext_init(void);
static void senkaron_ext_init(void) {
    s32 i;
    ExtPose* pose = extGetPosePtr();

    senkaron = _mapAlloc(sizeof(Senkaron) * 1000);
    for (i = extGetPoseNum() - 1; i >= 0; i--, pose++) {
        pose->flags = 3;
        pose->rot = randf(0.0f, 360.0f);
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(-385.0f, 375.0f);
        pose->mtx[1][3] = 200.0f;
        pose->mtx[2][3] = randf(-125.0f, 140.0f);
        pose->rot = 90.0f;
        senkaron[i].state = 0;
        senkaron[i].timer = randf(1.0f, 50.0f);
        senkaron[i].vy = -5.0f;
    }
    senkaronAttackStartFlag = 0;
    senkaronEscapeFlag = 0;
    marioHammerFrame = 0;
}
