// include: memory.h
// include: string.h
// include: dolphin/mtx.h
// decl: typedef struct Senkaron { s8 state; u16 area; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: typedef struct SenkaronWork { s32 attackStart; s32 escape; s32 mesPushing; u32 frameCount; s32 marioPushed; s32 hammerFrame; Senkaron* sk; } SenkaronWork;
// decl: SenkaronWork* skwp;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static f32 randf(f32 min, f32 max);
// proto: static void senkaron_ext_init(void);
static void senkaron_ext_init(void) {
    s32 i;
    ExtPose* pose = extGetPosePtr();
    Senkaron* sk;

    skwp = _mapAlloc(0x18);
    memset(skwp, 0, 0x18);
    skwp->sk = _mapAlloc(sizeof(Senkaron) * 1000);
    sk = skwp->sk;
    for (i = extGetPoseNum() - 1; i >= 0; i--, pose++) {
        pose->flags = 3;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(-570.0f, 570.0f);
        pose->mtx[1][3] = 250.0f;
        pose->mtx[2][3] = randf(-270.0f, 270.0f);
        pose->rot = 90.0f;
        sk[i].state = 0;
        sk[i].timer = randf(1.0f, 200.0f);
        sk[i].vy = -3.0f;
    }
}
