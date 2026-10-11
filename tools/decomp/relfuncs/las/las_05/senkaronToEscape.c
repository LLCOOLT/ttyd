// include: manager/evtmgr_cmd.h
// decl: typedef struct Senkaron { s8 state; u16 area; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: typedef struct SenkaronWork { s32 attackStart; s32 escape; s32 mesPushing; u32 frameCount; s32 marioPushed; s32 hammerFrame; Senkaron* sk; } SenkaronWork;
// decl: SenkaronWork* skwp;
// proto: USER_FUNC(senkaronToEscape);
USER_FUNC(senkaronToEscape) {
    skwp->escape = 1;
    return EVT_RETURN_DONE;
}
