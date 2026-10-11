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
// proto: USER_FUNC(bom1000_msg);
USER_FUNC(bom1000_msg) {
    s32* args = event->args;
    s32 type = evtGetValue(event, args[0]);
    s32 idx = evtGetValue(event, args[1]);
    ExtPose* pose = extGetPosePtr();
    ExtPose* p;
    s32 row;
    s32 flag;
    s32 n;

    if (type == 0) {
        row = 3;
        flag = 1;
    } else {
        row = 10;
        flag = 0;
    }
    n = idx + row * 14;
    idx += (rand() % 2 + 1) * 4;
    idx %= 14;
    p = &pose[n];
    evtSetValue(event, args[0], flag);
    evtSetValue(event, args[1], idx);
    evtSetFloat(event, args[2], p->mtx[0][3]);
    evtSetFloat(event, args[3], p->mtx[2][3]);
    return EVT_RETURN_DONE;
}
