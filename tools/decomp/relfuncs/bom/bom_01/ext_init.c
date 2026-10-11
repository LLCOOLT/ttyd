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
// decl: static inline f32 chb_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 chb_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// decl: static void pose_init(void);
// decl: static void pose_change(s32 i, const char* name);
// proto: static void ext_init(void);
#pragma opt_propagation off
#pragma opt_lifetimes off
static void ext_init(void) {
    s32 i;
    BomWork* wp;
    ExtPose* pose;
    f32 angle;

    lp = smartAlloc(sizeof(BomWork), 1);
    wp = lp->address;
    memset(wp, 0, sizeof(BomWork));
    wp->count = extGetPoseNum();
    pose_init();

    pose = extGetPosePtr();
    for (i = 0; i < wp->count; i++, pose++) {
        f32 dist;

        wp->bom[i].vy = 0.0f;
        wp->bom[i].gravity = 0.0f;
        wp->bom[i].state = 0;
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        angle = 6.2831855f * rand() / 32767.0f;
        dist = 500.0f + 400.0f * rand() / 32767.0f;
        pose->mtx[0][3] = dist * chb_sin(angle);
        pose->mtx[1][3] = 0.0f;
        pose->mtx[2][3] = dist * chb_cos(angle);
        pose_change(i, "R_1");
    }
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
