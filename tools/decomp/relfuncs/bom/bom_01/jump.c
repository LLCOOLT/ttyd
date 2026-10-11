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
// proto: void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity) {
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr() + i;
    f32 dy;
    f32 dist;

    wp->bom[i].target = (Vec){x, y, z};
    wp->bom[i].field_0x10 = speed;
    wp->bom[i].gravity = gravity;
    dy = y - pose->mtx[1][3];
    dist = distABf(pose->mtx[0][3], pose->mtx[2][3], x, z);
    angleABf(pose->mtx[0][3], pose->mtx[2][3], x, z);
    wp->bom[i].timer = dist / wp->bom[i].field_0x10;
    wp->bom[i].vy = dy / wp->bom[i].timer + wp->bom[i].gravity * wp->bom[i].timer / 2;
    wp->bom[i].next = next;
    wp->bom[i].state = 100;
    pose->rot = angleABf(x, z, pose->mtx[0][3], pose->mtx[2][3]);
    if (i % 20 == 0 && !(wp->flags & 1)) {
        Vec pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        psndSFXOn_3D("SFX_STG7_BOMB_TOGETHER2", &pos);
    }
}
