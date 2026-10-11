// include: memory.h
// include: string.h
// include: stdlib.h
// include: system.h
// include: mario/mariost.h
// include: pmario_sound.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct ExtAnimDef { const char* file; const char* name; f32 time; } ExtAnimDef;
// decl: typedef struct BomAnim { char name[8]; f32 time; s32 start; s32 count; } BomAnim;
// decl: typedef struct Bom { u8 state; u8 next; u8 pad_2[2]; Vec target; f32 field_0x10; f32 gravity; s16 timer; u8 pad_1a[2]; f32 vy; s32 anim; u8 pad_24[4]; OSTime time; } Bom;
// decl: typedef struct BomWork { u16 flags; u8 pad_2[2]; s32 count; BomAnim anims[8]; s32 animCount; u8 pad_ac[4]; Bom bom[1000]; } BomWork;
// decl: smartEntry* lp;
// decl: #define EXT_DATA ((ExtAnimDef*)ext_data)
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static void pose_change(s32 i, const char* name);
// proto: USER_FUNC(bom_fall);
USER_FUNC(bom_fall) {
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr();
    s32 i;

    for (i = 0; i < wp->count; i++, pose++) {
        wp->bom[i].state = 127;
        pose->mtx[0][3] = 600.0f * rand() / 32767.0f;
        pose->mtx[1][3] = 300.0f + 3700.0f * rand() / 32767.0f;
        pose->mtx[2][3] = -650.0f + -450.0f * rand() / 32767.0f;
        pose_change(i, "S_2");
    }
    return EVT_RETURN_DONE;
}
