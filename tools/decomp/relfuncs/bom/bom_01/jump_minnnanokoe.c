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
// proto: void jump_minnnanokoe(s32 i, f32 h);
void jump_minnnanokoe(s32 i, f32 h) {
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr() + i;

    wp->bom[i].target = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
    wp->bom[i].field_0x10 = 0.0f;
    wp->bom[i].gravity = 0.1f;
    wp->bom[i].timer = 20;
    wp->bom[i].vy = wp->bom[i].gravity * wp->bom[i].timer / 2 + h / wp->bom[i].timer;
    wp->bom[i].next = 5;
    wp->bom[i].state = 100;
    if (evtGetValue(NULL, GSW(0)) != 401 && i % 5 == 0) {
        Vec pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        psndSFXOn_3D("SFX_STG7_BOMB_TOGETHER2", &pos);
    }
}
