// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// include: driver/mapdrv.h
// include: manager/evtmgr.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; u8 field_0x30[0x3c - 0x30]; s16 pose; u8 field_0x3e[2]; OSTime startTime; u8 field_0x48[4]; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; EventEntry* escapeEvt; u8 field_0x48[0x4c - 0x48]; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; u8 field_0x570[0x870 - 0x570]; } MoamoaWork;
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
// include: system.h
// include: math.h
// proto: static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    f32 hitX, hitY, hitZ, dist, nx, ny, nz;
    f32 dy;
    f32 angle;

    if (checkGround) {
        hitX = hitY = hitZ = 0.0f;
        dist = 1000000.0f;
        if (hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &dist, &nx, &ny, &nz, x, 100.0f + y, z, 0.0f, -1.0f, 0.0f)) {
            if (fabs(y - hitY) > 30.0) {
                speed -= 0.1f;
                gravity += 0.1f;
            }
            y = hitY;
        }
    }
    moa->target = (Vec){x, y, z};
    moa->speed = speed;
    moa->gravity = gravity;
    dy = moa->target.y - pose->mtx[1][3];
    dist = distABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z);
    angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z);
    moa->jumpTimer = dist / moa->speed;
    moa->vy = dy / moa->jumpTimer + moa->gravity * moa->jumpTimer / 2;
    moa->state = 3;
    moa->next = next;
    pose->rot = 180.0f + angle;
    moa->flags |= 2;
    pose->flags |= 0x10;
    pose->flags &= ~4;
}
