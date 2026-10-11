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
// include: driver/camdrv.h
// include: dolphin/gx.h
// decl: typedef struct YamiParam { s32 field_0x0; f32 (*mtx)[4]; s32 field_0x8; s32 numTevStages; s32 field_0x10; s32 numTexGens; s32 numIndStages; } YamiParam;
// decl: void envSetYami(YamiParam* param);
// decl: void extLoadRenderMode(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extLoadTev(void);
// decl: void extPoseDraw(s32 i);
// decl: void extLoadTextureExit(void);
// proto: void ext_disp_minnnanokoe(CameraId camera, void* param);
void ext_disp_minnnanokoe(CameraId camera, void* param) {
    YamiParam yp;
    ExtPose* pose = extGetPosePtr();
    s32 i;

    extLoadRenderMode();
    extLoadVertex();
    extLoadTexture();
    extLoadTev();
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        yp.numTevStages = 1;
        yp.field_0x10 = 1;
        yp.numTexGens = 1;
        yp.numIndStages = 0;
        yp.mtx = pose->mtx;
        envSetYami(&yp);
        GXSetNumTexGens(yp.numTexGens);
        GXSetNumTevStages(yp.numTevStages);
        GXSetNumIndStages(yp.numIndStages);
        extPoseDraw(i);
    }
    extLoadTextureExit();
}
