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
// include: dolphin/os.h
// proto: static void pose_main(void);
static void pose_main(void) {
    OSTime now;
    BomWork* wp = lp->address;
    s32 i;
    ExtPose* pose = extGetPosePtr();
    f32 t;

    for (i = 0; i < wp->count; i++, pose++) {
        BomAnim* a = &wp->anims[wp->bom[i].anim];
        now = gp->renderTime;

        t = 60.0f * OSTicksToMilliseconds((u64)(now - wp->bom[i].time)) / 1000.0f / a->time;
        if (t >= 1.0f) {
            wp->bom[i].time = now;
            t = 0.0f;
        }
        pose->frame = a->start + (s32)((a->count - 1) * t);
    }
}
