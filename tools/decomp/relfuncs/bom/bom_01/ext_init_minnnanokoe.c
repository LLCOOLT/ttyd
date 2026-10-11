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
// decl: static inline void bom_set_anim(s32 i, const char* name) { BomWork* wp = lp->address; s32 j = 0; BomAnim* a; for (a = wp->anims; j < wp->animCount; j++, a++) { if (strcmp(a->name, name) == 0) { break; } } if (j < wp->animCount && wp->bom[i].anim != j) { wp->bom[i].anim = (s16)j; wp->bom[i].time = gp->renderTime + rand(); } }
// decl: static inline void bom_init_anim(void) { BomWork* wp; ExtAnimDef* def; char buf[32]; s32 i; s32 start; i = 0; wp = lp->address; def = EXT_DATA; strcpy(buf, ""); wp->animCount = -1; do { if (strcmp(def->name, buf) != 0) { strcpy(buf, def->name); wp->animCount++; start = i; } strcpy(wp->anims[wp->animCount].name, buf); wp->anims[wp->animCount].start = start; wp->anims[wp->animCount].count = i - start + 1; i++; wp->anims[wp->animCount].time = def->time; } while ((++def)->file != NULL); wp->animCount++; }
// proto: void ext_init_minnnanokoe(void);
void ext_init_minnnanokoe(void) {
    s32 i;
    BomWork* wp;
    ExtPose* pose;
    s32 x;
    s32 z;

    lp = smartAlloc(sizeof(BomWork), 1);
    wp = lp->address;
    memset(wp, 0, sizeof(BomWork));
    wp->count = extGetPoseNum();
    bom_init_anim();

    pose = extGetPosePtr();
    for (i = 0; i < wp->count; i++, pose++) {
        wp->bom[i].vy = 0.0f;
        wp->bom[i].gravity = 0.0f;
        wp->bom[i].state = 5;
        pose->flags |= 3;
        PSMTXIdentity(pose->mtx);
        x = (i % 14) * 30 - 205 + rand() % 10;
        z = 190 - (i / 14) * 20 + rand() % 20;
        pose->mtx[0][3] = x;
        pose->mtx[1][3] = 0.0f;
        pose->mtx[2][3] = z;
        pose->rot = 270.0f;
        bom_set_anim(i, "S_1");
    }
}
