// include: driver/camdrv.h
// include: dolphin/gx.h
// decl: typedef struct Teresa { Vec vel; f32 angle; Vec ofs; f32 field_0x1C; f32 field_0x20; Vec from; Vec to; s32 wait; u8 alpha; u8 seq; } Teresa;
// decl: f32 g_fSpeed;
// decl: static s32 g_nNumEndProc[1];
// decl: s32 g_nNumHarituku[1];
// decl: s32 g_nNumHuttobasu[1];
// decl: s32 g_nMarioMoveCnt;
// decl: s32 g_bMove;
// decl: Vec g_vecRotCenter;
// decl: static Teresa* pTeresa;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extPoseDraw(s32 i);
// decl: void extLoadTextureExit(void);
// decl: void senteresa_loadTev(void);
// decl: void senteresa_loadRenderMode(void);
// proto: static void senteresa_ext_disp(CameraId camera, void* param);
static void senteresa_ext_disp(CameraId camera, void* param) {
    GXColor color = {0xFF, 0xFF, 0xFF, 0xFF};
    s32 n = extGetPoseNum();
    s32 i;

    senteresa_loadRenderMode();
    extLoadVertex();
    extLoadTexture();
    senteresa_loadTev();
    for (i = 0; i < n; i++) {
        color.a = pTeresa[i].alpha;
        GXSetTevColor(GX_TEVREG0, color);
        extPoseDraw(i);
    }
    extLoadTextureExit();
}
