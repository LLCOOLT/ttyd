// decl: typedef struct Senkaron { s8 state; u16 area; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: typedef struct SenkaronWork { s32 attackStart; s32 escape; s32 mesPushing; u32 frameCount; s32 marioPushed; s32 hammerFrame; Senkaron* sk; } SenkaronWork;
// decl: SenkaronWork* skwp;
// proto: void calc_area(s32 i, f32 x, f32 z);
void calc_area(s32 i, f32 x, f32 z) {
    f32 fx = x - -570.0f;
    f32 fz = z - -270.0f;
    u16 iz;
    u16 ix;

    fx /= 40.0f;
    fz /= 40.0f;
    iz = fz;
    ix = fx;
    skwp->sk[i].area = ix + iz * 29.5f;
}
