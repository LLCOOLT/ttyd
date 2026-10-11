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
// decl: static s32 ext_data[93];
// decl: #define EXT_DATA ((ExtAnimDef*)ext_data)
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: static void pose_init(void);
static void pose_init(void) {
    BomWork* wp; ExtAnimDef* def; char buf[32]; s32 i; s32 start; i = 0; wp = lp->address; def = EXT_DATA; strcpy(buf, ""); wp->animCount = -1; do { if (strcmp(def->name, buf) != 0) { strcpy(buf, def->name); wp->animCount++; start = i; } strcpy(wp->anims[wp->animCount].name, buf); wp->anims[wp->animCount].start = start; wp->anims[wp->animCount].count = i - start + 1; i++; wp->anims[wp->animCount].time = def->time; } while ((++def)->file != NULL); wp->animCount++;
}
