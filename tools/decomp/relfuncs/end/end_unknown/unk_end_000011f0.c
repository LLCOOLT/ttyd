// include: driver/animdrv.h
// include: driver/npcdrv.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// include: driver/mapdrv.h
// include: driver/msgdrv.h
// include: driver/windowdrv.h
// include: driver/swdrv.h
// include: manager/evtmgr.h
// include: manager/evtmgr_cmd.h
// include: manager/filemgr.h
// include: manager/fontmgr.h
// include: mario/mariost.h
// include: memory.h
// include: string.h
// include: stdio.h
// include: pmario_sound.h
// include: system.h
// include: sdk/texPalette.h
// include: data/mapdata.h
// include: dolphin/gx.h
// include: dolphin/mtx.h
// decl: #define ARRAY_SIZE(a) (sizeof(a) / sizeof((a)[0]))
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct EndMoa { Vec pos; s32 chain; s32 idx; } EndMoa;
// decl: typedef struct EndExtData { const char* anim; const char* pose; f32 speed; } EndExtData;
// decl: typedef struct EndWork { FileEntry* tpl; s32 mode; s32 alpha; s32 alpha2; s32 tevAlpha; s32 win1[3]; s32 win2[3]; s32 field_0x2c; s32 pos; EventEntry* evt; } EndWork;
// decl: typedef struct CreditMsg { s32 field_0x0; s32 pos; s32 type; const char* msg1[3]; const char* msg2[3]; } CreditMsg;
// decl: typedef struct CreditNpc { const char* agb; const char* anim; s32* evt; } CreditNpc;
// decl: typedef struct CreditActor { s32 state; s32 poseId; f32 angle; f32 limit; s32 pos; Mtx mtx; } CreditActor;
// decl: EndWork unk_end_bss00000010;
// decl: s32 (*unk_end_bss0000000c)[2];
// decl: s32* unk_end_bss00000008;
// decl: EndExtData* unk_end_bss00000004;
// decl: EndMoa* unk_end_bss00000000;
// decl: extern EndWork* dat_ptr_end_00003218;
// decl: extern CreditMsg unk_end_0000321c[50];
// decl: extern CreditNpc R_credits_npc_info[152];
// decl: extern const char* dat_ptr_end_00005034;
// decl: extern const char* dat_ptr_end_00005038;
// decl: extern const char* g_moamoa_chain_tbl[][2];
// decl: extern const s32 dat_80419a28;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extReset(void);
// decl: void extLoadRenderMode(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extLoadTev(void);
// decl: void extDraw(void);
// decl: void extLoadTextureExit(void);
// decl: int rand(void);
// decl: double tan(double x);
// decl: static inline f32 tanf(f32 x) { return tan(x); }
// decl: s32 EXIGetType(s32 chan, u32 dev, u32* type);
// decl: void L_animPoseWorldPositionEvalOff(s32 poseId);
// decl: void animPoseVivianMain(s32 poseId, Vec* pos);
// decl: s32 msgWindow_Entry(const char* msg, s32 a, s32 b);
// decl: void msgWindow_Continue(s32 id);
// decl: void JUTFont_Free(void);
// decl: void JUTFontSetup(s32 mode);
// proto: USER_FUNC(unk_end_000011f0);
USER_FUNC(unk_end_000011f0) {
    dat_ptr_end_00003218->tevAlpha = evtGetValue(event, event->args[0]);
    return 2;
}
