// include: dolphin/os.h
// include: mario/mariost.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; Vec pos; f32 angle; s16 pose; u64 startTime; } Moamoa;
// decl: typedef struct MoamoaWork { s32 field_0x0; s32 count; Moamoa* moa; s32 numDefs; MoamoaPoseDef defs[32]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: static void moamoa_pose_main(void);
static void moamoa_pose_main(void) {
    f32 t;
    u64 now;
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    MoamoaPoseDef* def;

    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++, pose++) {
        now = gp->renderTime;
        def = &wp->defs[moa->pose];
        t = 60.0f * OSTicksToMilliseconds(now - moa->startTime) / 1000.0f / def->speed;

        if (t >= 1.0f) {
            if (def->loop) {
                moa->startTime = now;
                t = 0.0f;
            } else {
                t = 1.0f;
            }
        }
        pose->frame = def->start + (s32)((def->count - 1) * t);
    }
}
