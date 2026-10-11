// include: manager/evtmgr.h
// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
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
// include: driver/hitdrv.h
// include: driver/mapdrv.h
// decl: void evalOn(void);
// decl: static void ext_moamoa_main(void);
// proto: static void ext_moamoa_init(void);
static void ext_moamoa_init(void) {
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    Vec v;
    f32 hitX, hitY, hitZ, dist, nx, ny, nz;

    wp = _mapAlloc(sizeof(MoamoaWork));
    memset(wp, 0, sizeof(MoamoaWork));
    wp->target[0] = (Vec){10.0f, 215.0f, 0.0f};
    wp->target[1] = (Vec){10.0f, 215.0f, 0.0f};
    wp->target[2] = (Vec){10.0f, 215.0f, 0.0f};
    wp->count = extGetPoseNum();
    wp->moa = _mapAlloc(wp->count * sizeof(Moamoa));
    memset(wp->moa, 0, wp->count * sizeof(Moamoa));
    moamoa_pose_init();
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        moa->flags = 0;
        moa->state = 0;
        moa->timer = 0;
        moamoa_pose_change(moa, "c_n_moa_a", "S_1");
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(-500.0f, 500.0f);
        pose->mtx[1][3] = 215.0f;
        pose->mtx[2][3] = randf(-45.0f, 45.0f);
        hitX = hitY = hitZ = 0.0f;
        dist = 1000000.0f;
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, pose->mtx[0][3], 100.0f + pose->mtx[1][3], pose->mtx[2][3], 0.0f, -1.0f, 0.0f)) {
            pose->mtx[1][3] = hitY;
        } else {
            pose->flags |= 4;
            pose->mtx[0][3] = randf(-500.0f, 500.0f);
            pose->mtx[1][3] = randf(100.0f, 215.0f);
            pose->mtx[2][3] = randf(70.0f, 75.0f);
            moa->flags |= 0x40;
            moamoa_pose_change(moa, "c_n_moa_a", "S_1");
        }
        v = (Vec){0.0f, 0.0f, 0.0f};
        v.x = randf(-10.0f, 10.0f);
        v.y = randf(-10.0f, 10.0f);
        v.z = randf(-10.0f, 10.0f);
        moa->field_0x30 = v;
    }
    evalOn();
    for (i = 0; i < 600; i++) {
        ext_moamoa_main();
    }
}
