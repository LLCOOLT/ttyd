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
// decl: void moamoa_draw(CameraId cameraId, void* param);
// proto: static void ext_moamoa_main(void);
static void ext_moamoa_main(void) {
    s32 i;
    Moamoa* elem;
    ExtPose* pose;
    MoamoaGroup* grp;
    BattleUnit* unit;
    AnimationPose* ap;
    Vec* a;
    Vec* b;
    s32 j;
    s32 n;
    f32 t;
    f32 s;
    Vec joint[5];
    Vec ofs[5];
    Mtx m;
    Vec w;
    Vec v;
    Vec r;

    pose = extGetPosePtr();
    for (i = 0; i < wp->count; i++, pose++) {
    }
    wp->scale += 0.1f * (wp->targetScale - wp->scale);

    pose = extGetPosePtr();
    elem = wp->elems;
    for (i = 0; i < wp->count; i++, elem++, pose++) {
        grp = &wp->groups[elem->group];
        t = gp->framerate * (f32)OSTicksToMilliseconds((u64)(gp->renderTime - elem->time)) / 1000.0f / grp->speed;
        if (t >= 1.0f) {
            elem->time = gp->renderTime;
            t = 0.0f;
        }
        n = grp->num * t;
        if (n >= grp->num) {
            n = grp->num - 1;
        }
        pose->frame = grp->start + n;
    }

    if (wp->unitId != -1) {
        unit = BattleGetUnitPtr(_battleWorkPointer, wp->unitId);
        for (j = 0; j < 5; j++) {
            if (j == 0 || unit->work[j + 2] != -1) {
                ap = animPoseGetAnimPosePtr(wp->poseId[j]);
                joint[j] = (*ap->worldPositions)[animPoseGetGroupIdx(wp->poseId[j], "joint_core")];
                PSVECSubtract(&joint[0], &joint[j], &ofs[j]);
            }
        }
        pose = extGetPosePtr();
        elem = wp->elems;
        for (i = 0; i < wp->count; i++, pose++, elem++) {
            if (*elem->owner == -1) {
                pose->mtx[0][3] = 0.0f;
                pose->mtx[1][3] = -1000.0f;
                pose->mtx[2][3] = 0.0f;
                continue;
            }
            ap = animPoseGetAnimPosePtr(elem->poseId);
            a = &(*ap->worldPositions)[wp->chainIdx[elem->chain][0]];
            b = &(*ap->worldPositions)[wp->chainIdx[elem->chain][1]];
            t = elem->t;
            s = 1.0f - t;
            if (a->y == -1000.0f || b->y == -1000.0f) {
                v = (Vec){0.0f, -1000.0f, 0.0f};
                pose->flags &= ~1;
            } else {
                PSVECScale(a, &v, t);
                PSVECScale(b, &w, s);
                PSVECAdd(&v, &w, &v);
                PSVECAdd(&v, &elem->pos, &v);
                pose->flags |= 1;
            }
            if (elem->owner != &wp->unitId) {
                for (j = 1; j < 5; j++) {
                    if (&unit->work[j + 2] == elem->owner) {
                        PSVECAdd(&v, &ofs[j], &v);
                        break;
                    }
                }
            }
            if (elem->chain >= 46) {
                pose->mtx[0][0] = pose->mtx[1][1] = wp->scale;
            }
            pose->mtx[0][3] += (v.x - pose->mtx[0][3]) / 2;
            pose->mtx[1][3] += (v.y - pose->mtx[1][3]) / 2;
            pose->mtx[2][3] += (v.z - pose->mtx[2][3]) / 2;
        }
    } else {
        wp->angle += 8.571428f;
        wp->radius -= 0.0044444446f;
        if (wp->radius < 0.8f) {
            wp->radius = 0.8f;
        }
        if (wp->angle >= 360.0f) {
            wp->angle -= 360.0f;
        }
        pose = extGetPosePtr();
        elem = wp->elems;
        for (i = 0; i < wp->count; i++, pose++, elem++) {
            if (elem->flags & 1) {
                PSVECSubtract(&elem->vel, &wp->center, &r);
                PSMTXRotAxisRad(m, &elem->pos2, 0.017453292f * wp->angle);
                PSMTXMultVec(m, &r, &r);
                PSVECScale(&r, &r, wp->radius);
                PSVECAdd(&r, &wp->center, &r);
                pose->mtx[0][3] += (r.x - pose->mtx[0][3]) / 2;
                pose->mtx[1][3] += (r.y - pose->mtx[1][3]) / 2;
                pose->mtx[2][3] += (r.z - pose->mtx[2][3]) / 2;
            }
        }
    }
    dispEntry(CAMERA_3D, 0.0f, 1, moamoa_draw, NULL);
}
