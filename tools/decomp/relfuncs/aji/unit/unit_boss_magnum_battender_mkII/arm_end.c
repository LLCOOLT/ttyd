// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// decl: typedef struct ArmWork { Vec prevPos; Vec pos; f32 rot; f32 targetRot; EffectEntry* eff; } ArmWork;
// decl: static ArmWork* work[2];
// proto: static USER_FUNC(arm_end);
static USER_FUNC(arm_end) {
    s32 idx = evtGetValue(event, event->args[0]);
    ArmWork* arm = work[idx];

    if (arm->eff != NULL) {
        effDelete(arm->eff);
        arm->eff = NULL;
    }
    return EVT_RETURN_DONE;
}
