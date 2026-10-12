// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// include: driver/mapdrv.h
// include: manager/evtmgr.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; Vec field_0x30; s16 pose; u8 field_0x3e[2]; OSTime startTime; s16 group; s16 order; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; void* escapeEvt; s32 animPoseId; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; s16 chainNum[128]; s16 chainIdx[128][2]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extReset(void);
// decl: int rand(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: static void moamoa_pose_init(void);
// decl: static void moamoa_pose_main(void);
// decl: static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
// decl: #pragma inline_max_total_size(100000)
// decl: static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// include: mario/mario.h
// include: mario/mario_motion.h
// include: party.h
// include: driver/camdrv.h
// include: system.h
// decl: s32 nokonokoGetStatus(PartyEntry* party);
// proto: static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
#pragma opt_propagation off
#pragma opt_lifetimes off
static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa) {
    MarioWork* mario = marioGetPtr();
    CameraEntry* cam;
    f32 range;
    f32 dist;
    f32 angle;
    f32 rad;
    Vec a, b, c, d, e, f;

    if (mario->position.y > 20.0f + pose->mtx[1][3]) {
        return 0;
    }
    if (pose->mtx[1][3] > mario->position.y + mario->wPlayerCollisionBox.y) {
        return 0;
    }
    if (distABf(pose->mtx[0][3], pose->mtx[2][3], mario->position.x, mario->position.z) < (20.0f + mario->wPlayerCollisionBox.x) / 2
        && mario->position.y > 10.0f + pose->mtx[1][3] && (mario->flags & 0x20000) && !(mario->flags & 0x10000)
        && wp->field_0x558 < 2) {
        if (mario->currMotionId != 0x16 && mario->currMotionId != 0x1a) {
            marioChgMot(5);
        }
        wp->field_0x558++;
        return 1;
    }
    if (!(mario->flags & 0x30000)) {
        wp->field_0x558 = 0;
    }
    if (mario->currMotionId == 0x12 && wp->field_0x40 > 10) {
        cam = camGetPtr(CAMERA_3D);
        rad = 6.2831855f * reviseAngle(mario->unk1A8 - 90.0f + cam->viewYaw) / 360.0f;
        angle = 35.0f * moa_sin(rad) + mario->position.x;
        dist = mario->position.z - 35.0f * moa_cos(rad);
        if (distABf(pose->mtx[0][3], pose->mtx[2][3], angle, dist) < 35.0f) {
            return 2;
        }
    }
    if (mario->currMotionId == 0x13 && mario->currSubMotionId == 0x14) {
        a = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        if (PSVECDistance(&mario->position, &a) < 65.0f) {
            return 2;
        }
    }
    if (wp->breathDir >= 0.0f) {
        b = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        if (PSVECDistance(&wp->breathPos, &b) < 30.0f) {
            return 3;
        }
    }
    if (nokonokoGetStatus(partyGetPtr(0)) == 2) {
        c = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &c) < 30.0f) {
            return 2;
        }
    }
    if (partyGetPtr(0)->currentMemberId == 3 && partyGetPtr(0)->useMotionId == 0x46) {
        d = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        if (PSVECDistance(&partyGetPtr(0)->position, &d) < 50.0f) {
            return 4;
        }
    }
    e = (Vec){mario->position.x, pose->mtx[1][3], mario->position.z};
    f = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
    range = (20.0f + mario->wPlayerCollisionBox.x) / 2;
    if (PSVECDistance(&e, &f) < range) {
        pose->mtx[0][3] = moa->field_0x28;
        pose->mtx[2][3] = moa->field_0x2c;
        f = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        dist = PSVECDistance(&e, &f);
        if (dist < range) {
            angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
            if (__fabsf(compAngle(angle, mario->directionView)) < 40.0f) {
                mario->unk174.x = -((range - dist) * moa_sin(6.2831855f * mario->directionView / 360.0f));
                mario->unk174.z = (range - dist) * moa_cos(6.2831855f * mario->directionView / 360.0f);
            } else {
                rad = 6.2831855f * angle / 360.0f;
                mario->unk174.x = pose->mtx[0][3] - range * moa_sin(rad) - mario->position.x;
                mario->unk174.z = pose->mtx[2][3] + range * moa_cos(rad) - mario->position.z;
            }
        }
    }
    return 0;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
