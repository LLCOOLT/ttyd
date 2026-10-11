// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// include: manager/evtmgr.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; u8 field_0x30[0x3c - 0x30]; s16 pose; u8 field_0x3e[2]; OSTime startTime; u8 field_0x48[4]; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; u8 field_0xc[8]; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; EventEntry* escapeEvt; u8 field_0x48[4]; s32 numDefs; MoamoaPoseDef defs[32]; f32 angleToMario; f32 distToMario; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; u8 field_0x570[0x870 - 0x570]; } MoamoaWork;
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
// proto: USER_FUNC(evt_moamoa_fusion);
USER_FUNC(evt_moamoa_fusion) {
    s32 i;
    ExtPose* pose;
    Moamoa* moa;

    if (isFirstCall) {
        pose = extGetPosePtr();
        moa = wp->moa;
        for (i = 0; i < wp->count; i++, pose++, moa++) {
            pose->mtx[2][2] = 1.0f;
            pose->mtx[1][1] = 1.0f;
            pose->mtx[0][0] = 1.0f;
            moa->next = 14;
            moa->state = 14;
            moa->timer = i < 100 ? i % 100 : i % 60 + 100;
            moa->flags |= 0x100;
        }
    }
    extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, moa++) {
        if (!(moa->flags & 0x200)) {
            return EVT_RETURN_BLOCK;
        }
    }
    pose = extGetPosePtr();
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        pose->flags |= 4;
        moa->flags |= 0x400;
        moa->state = 61;
        moamoa_pose_change(moa, "c_n_moa_a", "S_1");
    }
    return EVT_RETURN_DONE;
}
