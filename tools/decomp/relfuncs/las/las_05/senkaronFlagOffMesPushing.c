// include: manager/evtmgr_cmd.h
// decl: typedef struct Senkaron { s8 state; u16 area; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: typedef struct SenkaronWork { s32 attackStart; s32 escape; s32 mesPushing; s32 field_C; s32 marioPushed; s32 field_14; Senkaron* sk; } SenkaronWork;
// decl: SenkaronWork* skwp;
// proto: USER_FUNC(senkaronFlagOffMesPushing);
USER_FUNC(senkaronFlagOffMesPushing) {
    skwp->mesPushing = 0;
    return EVT_RETURN_DONE;
}
