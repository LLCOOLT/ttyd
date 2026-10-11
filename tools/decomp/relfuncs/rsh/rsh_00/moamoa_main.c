// include: system.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; Vec pos; f32 angle; s16 pose; u64 startTime; } Moamoa;
// decl: typedef struct MoamoaWork { s32 field_0x0; s32 count; Moamoa* moa; s32 numDefs; MoamoaPoseDef defs[32]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: double sin(double x);
// decl: double cos(double x);
// decl: int rand(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: static void moamoa_pose_main(void);
// proto: void moamoa_main(void);
void moamoa_main(void) {
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    f32 r;

    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        switch (moa->state) {
            case 0:
                break;
            case 1:
                moa->timer = rand() % 60;
                moa->state++;
                break;
            case 2:
                if (--moa->timer > 0) {
                    break;
                }
                moa->state++;
                moa->angle = randf(0.0f, 6.283184f);
                break;
            case 3:
                if (moa->timer < 20) {
                    if (!(moa->flags & 1)) {
                        r = intplGetValue(2, ++moa->timer, 20, 50.0f, 0.0f);
                        pose->mtx[0][3] = moa->pos.x + r * (f32)sin(moa->angle);
                        pose->mtx[1][3] = moa->pos.y - r * (f32)cos(moa->angle);
                        pose->mtx[2][3] = moa->pos.z;
                    } else {
                        r = intplGetValue(2, ++moa->timer, 20, 50.0f, 0.0f);
                        pose->mtx[0][3] = moa->pos.x;
                        pose->mtx[1][3] = moa->pos.y - r * (f32)cos(moa->angle);
                        pose->mtx[2][3] = moa->pos.z;
                    }
                } else {
                    moa->state++;
                }
                break;
            case 4:
                pose->mtx[0][3] = moa->pos.x;
                pose->mtx[1][3] = moa->pos.y;
                pose->mtx[2][3] = moa->pos.z;
                break;
        }
        if (pose->mtx[2][3] > 45.0f) {
            pose->mtx[2][3] = 45.0f;
        }
    }
    moamoa_pose_main();
}
