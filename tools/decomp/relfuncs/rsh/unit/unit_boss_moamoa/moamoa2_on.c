// include: battle/battle.h
// include: battle/battle_sub.h
// include: battle/battle_unit.h
// include: driver/animdrv.h
// include: driver/dispdrv.h
// include: mario/mariost.h
// include: memory.h
// include: string.h
// include: dolphin/mtx.h
// include: dolphin/os.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct MoamoaGroup { char anim[16]; char pose[8]; f32 speed; s32 start; s32 num; } MoamoaGroup;
// decl: typedef struct Moamoa { u16 flags; u8 field_0x2[2]; Vec pos; s16 group; u8 field_0x12[6]; OSTime time; s16 chain; s16 order; f32 t; s32 poseId; s32 type; s32* owner; Vec vel; Vec pos2; u8 field_0x4c[4]; } Moamoa;
// decl: typedef struct MoamoaWork { s32 field_0x0; s32 count; Moamoa* elems; s32 numGroups; MoamoaGroup groups[32]; s16 chainNum[128]; s16 chainIdx[128][2]; s32 poseId[5]; s32 unitId; Vec center; f32 angle; f32 radius; f32 targetScale; f32 scale; } MoamoaWork;
// decl: typedef struct MoamoaExtData { const char* anim; const char* pose; f32 speed; } MoamoaExtData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: void extReset(void);
// decl: int rand(void);
// proto: USER_FUNC(moamoa2_on);
USER_FUNC(moamoa2_on) {
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    Moamoa* elem;
    AnimationPose* ap;
    Vec* p;
    s32 i;

    wp->poseId[4] = BattleGetUnitPartsPtr(unit->work[6], 1)->poseId;
    animPoseWorldPositionEvalOn(wp->poseId[4]);
    ap = animPoseGetAnimPosePtr(wp->poseId[4]);
    p = *ap->worldPositions;
    for (i = 0; i < ap->numWorldPositions; i++, p++) {
        *p = (Vec){0.0f, -1000.0f, 0.0f};
    }
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        if (elem->chain < 5) {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        } else if (elem->chain < 10) {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        } else if (elem->chain < 15) {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        } else if (elem->chain < 30) {
            elem->poseId = wp->poseId[4];
            elem->owner = &unit->work[6];
        } else {
            elem->poseId = wp->poseId[0];
            elem->owner = &wp->unitId;
        }
    }
    return 2;
}
