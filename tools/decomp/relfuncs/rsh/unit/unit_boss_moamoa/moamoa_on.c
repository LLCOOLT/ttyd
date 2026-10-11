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
// decl: extern const char* g_moamoa_chain_tbl[][2];
// decl: extern const s32 dat_80419a28;
// decl: static f32 randf(f32 min, f32 max);
// decl: USER_FUNC(moamoa1_on);
// proto: USER_FUNC(moamoa_on);
USER_FUNC(moamoa_on) {
    s32 i;
    s32 j;
    Moamoa* elem;
    MoamoaExtData* d;
    AnimationPose* ap;
    Vec* p;
    s32 start;
    Vec v;
    char anim[32];
    char pose[32];

    wp = __memAlloc(HEAP_BATTLE, sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->count = 750;
    wp->elems = __memAlloc(HEAP_BATTLE, wp->count * sizeof(Moamoa));
    memset(wp->elems, 0, wp->count * sizeof(Moamoa));
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        elem->flags = 0;
        v = (Vec){0.0f, 0.0f, 0.0f};
        v.x = randf(-10.0f, 10.0f);
        v.y = randf(-10.0f, 10.0f);
        v.z = randf(-10.0f, 10.0f);
        elem->pos = v;
    }
    wp->unitId = BattleTransID(event, -2);
    BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
    wp->poseId[0] = BattleGetUnitPartsPtr(wp->unitId, 1)->poseId;
    animPoseWorldPositionEvalOn(wp->poseId[0]);
    ap = animPoseGetAnimPosePtr(wp->poseId[0]);
    p = *ap->worldPositions;
    for (i = 0; i < ap->numWorldPositions; i++, p++) {
        *p = (Vec){0.0f, -1000.0f, 0.0f};
    }
    for (i = 0; i < dat_80419a28; i++) {
        wp->chainIdx[i][0] = animPoseGetGroupIdx(wp->poseId[0], g_moamoa_chain_tbl[i][0]);
        wp->chainIdx[i][1] = animPoseGetGroupIdx(wp->poseId[0], g_moamoa_chain_tbl[i][1]);
    }
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        elem->chain = i % dat_80419a28;
        elem->order = wp->chainNum[elem->chain]++;
    }
    moamoa1_on(event, isFirstCall);
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        elem->t = (f32)elem->order / (f32)wp->chainNum[elem->chain];
    }
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++) {
        if (elem->chain == 0 || elem->chain == 5 || elem->chain == 10 || elem->chain == 15 || elem->chain == 46) {
            elem->type = 1;
        }
        if (elem->order == 0) {
            if (elem->chain == 3) {
                elem->type = 2;
            }
            if (elem->chain == 4) {
                elem->type = 3;
            }
            if (elem->chain == 7) {
                elem->type = 4;
            }
            if (elem->chain == 8) {
                elem->type = 5;
            }
            if (elem->chain == 9) {
                elem->type = 6;
            }
            if (elem->chain == 12) {
                elem->type = 7;
            }
            if (elem->chain == 13) {
                elem->type = 8;
            }
            if (elem->chain == 14) {
                elem->type = 9;
            }
        }
    }
    d = (MoamoaExtData*)ext_moamoa_data;
    j = 0;
    strcpy(anim, "");
    strcpy(pose, "");
    wp->numGroups = -1;
    do {
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            strcpy(pose, "");
        }
        if (strcmp(d->pose, pose) != 0) {
            strcpy(pose, d->pose);
            start = j;
            wp->numGroups++;
        }
        strcpy(wp->groups[wp->numGroups].anim, anim);
        strcpy(wp->groups[wp->numGroups].pose, pose);
        wp->groups[wp->numGroups].start = start;
        wp->groups[wp->numGroups].num = j - start + 1;
        if (elem->type >= 2 && elem->type != 10) {
            wp->groups[wp->numGroups].speed = 12.0f;
        } else {
            wp->groups[wp->numGroups].speed = d->speed;
        }
        j++;
    } while ((++d)->anim != NULL);
    wp->numGroups++;
    for (i = 0; i < wp->numGroups; i++) {
    }
    return 2;
}
