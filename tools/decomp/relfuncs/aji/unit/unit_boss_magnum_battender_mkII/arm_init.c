// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: driver/effdrv.h
// decl: typedef struct ArmWork { Vec prevPos; Vec pos; f32 rot; f32 targetRot; EffectEntry* eff; } ArmWork;
// decl: static ArmWork* work[2];
// proto: static USER_FUNC(arm_init);
static USER_FUNC(arm_init) {
    s32 i;

    for (i = 0; i < 2; i++) {
        work[i] = BattleAlloc(sizeof(ArmWork));
        work[i]->prevPos = work[i]->pos = (Vec){0.0f, 0.0f, 0.0f};
    }
    return EVT_RETURN_DONE;
}
