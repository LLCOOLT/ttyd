// include: memory.h
// include: string.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; Vec pos; f32 angle; s16 pose; u64 startTime; } Moamoa;
// decl: typedef struct MoamoaWork { s32 field_0x0; s32 count; Moamoa* moa; s32 numDefs; MoamoaPoseDef defs[32]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: int rand(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: static void moamoa_pose_init(void);
// decl: static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
// proto: void moamoa_init(void);
void moamoa_init(void) {
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    f32 x, y, z;

    wp = _mapAlloc(sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->count = extGetPoseNum();
    wp->moa = _mapAlloc(wp->count * sizeof(Moamoa));
    memset(wp->moa, 0, wp->count * sizeof(Moamoa));
    moamoa_pose_init();
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        PSMTXIdentity(pose->mtx);
        pose->flags |= 5;
        moa->flags = 0;
        moa->state = 0;
        moamoa_pose_change(moa, "c_n_moa_a", "S_1");
        if (!strncmp(gp->currentMapName, "rsh_00", 6)) {
            x = randf(-200.0f, 400.0f);
            if (x > 257.0f) {
                x = randf(257.0f, 262.0f);
            }
            y = randf(20.0f, 100.0f);
            if (x < 185.0f) {
                z = randf(-160.0f, -165.0f);
            } else if (x < 257.0f) {
                z = 0.8f * (x - 185.0f) + -160.0f;
            } else {
                z = randf(-90.0f, -20.0f);
            }
            {
                Vec pos = {0.0f, 0.0f, 0.0f};

                pos.x = x;
                pos.y = y;
                pos.z = z - 100.0f;
                moa->pos = pos;
            }
            pose->mtx[0][3] = 0.0f;
            pose->mtx[1][3] = -1000.0f;
            pose->mtx[2][3] = 0.0f;
            if (!(x < 185.0f)) {
                if (x < 257.0f) {
                    Mtx m;

                    PSMTXRotRad(m, 'y', -0.7853982f);
                    PSMTXConcat(pose->mtx, m, pose->mtx);
                    moa->flags |= 1;
                } else {
                    Mtx m;

                    PSMTXRotRad(m, 'y', 1.5707964f);
                    PSMTXConcat(pose->mtx, m, pose->mtx);
                    moa->flags |= 1;
                }
            }
        } else {
            if (!strncmp(gp->currentMapName, "rsh_03", 6)) {
                x = randf(-500.0f, 500.0f);
                y = randf(20.0f, 100.0f) - 10.0f;
                z = randf(-170.0f, -180.0f);
                z -= 100.0f;
            } else {
                x = randf(-350.0f, 350.0f);
                y = randf(20.0f, 100.0f);
                z = randf(-290.0f, -300.0f);
            }
            {
                Vec pos = {0.0f, 0.0f, 0.0f};

                pos.x = x;
                pos.y = y;
                pos.z = z;
                moa->pos = pos;
            }
            pose->mtx[0][3] = 0.0f;
            pose->mtx[1][3] = -1000.0f;
            pose->mtx[2][3] = 0.0f;
        }
    }
}
