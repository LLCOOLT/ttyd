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
// proto: USER_FUNC(moamoa_guruguru);
USER_FUNC(moamoa_guruguru) {
    ExtPose* pose;
    Moamoa* elem;
    s32 i;
    f32 cnt;
    f32 ang;
    Vec v;
    Mtx m;

    BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    wp->center = (Vec){0.0f, 0.0f, 0.0f};
    pose = extGetPosePtr();
    elem = wp->elems;
    cnt = 0.0f;
    for (i = 0; i < wp->count; i++, pose++, elem++) {
        if (*elem->owner != -1) {
            v.x = pose->mtx[0][3];
            v.y = pose->mtx[1][3];
            v.z = pose->mtx[2][3];
            if (v.y >= 0.0f) {
                elem->flags |= 1;
                cnt += 1.0f;
                PSVECAdd(&v, &wp->center, &wp->center);
            }
        }
    }
    PSVECScale(&wp->center, &wp->center, 1.0f / cnt);
    wp->angle = 0.0f;
    wp->radius = 2.0f;
    pose = extGetPosePtr();
    elem = wp->elems;
    ang = 0.0f;
    for (i = 0; i < wp->count; i++, pose++, elem++) {
        if (elem->flags & 1) {
            elem->vel.x = pose->mtx[0][3];
            elem->vel.y = pose->mtx[1][3];
            elem->vel.z = pose->mtx[2][3];
            elem->pos2 = (Vec){0.0f, 1.0f, 0.0f};
            PSMTXRotRad(m, 'Z', 0.017453292f * ang);
            PSMTXMultVec(m, &elem->pos2, &elem->pos2);
            ang += 22.4375f;
            if (ang >= 360.0f) {
                ang -= 360.0f;
            }
        }
    }
    return 2;
}
