// include: memory.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Teresa { Vec pos; Vec dst; f32 t; f32 field_0x1C; f32 field_0x20; f32 field_0x24; s32 wait; u8 state; } Teresa;
// decl: static Teresa* pTeresa;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: f32 randf(f32 min, f32 max);
// decl: double cos(double x);
// decl: static inline f32 cosf(f32 x) { return cos(x); }
// decl: s32 g_nNumOutBox[1];
// decl: static s32 g_nNumEndProc[1];
// proto: static void senteresa_ext_init(void);
static void senteresa_ext_init(void) {
    ExtPose* pose = extGetPosePtr();
    s32 n = extGetPoseNum();
    s32 i;
    f32 a;
    f32 r;

    pTeresa = _mapAlloc(sizeof(Teresa) * 200);
    for (i = 0; i < n; i++, pose++) {
        pose->flags = 2;
        pose->rot = 270.0f;
        PSMTXIdentity(pose->mtx);
        pTeresa[i].pos.x = 0.0f;
        pose->mtx[0][3] = 0.0f;
        pTeresa[i].pos.y = 6.0f;
        pose->mtx[1][3] = 6.0f;
        pTeresa[i].pos.z = 80.0f;
        pose->mtx[2][3] = 80.0f;
        a = randf(0.0f, 360.0f);
        r = randf(10.0f, 30.0f);
        pTeresa[i].dst.x = 200.0f;
        pTeresa[i].dst.y = pTeresa[i].pos.y + randf(27.0f, 170.0f);
        pTeresa[i].dst.z = pTeresa[i].pos.z + r * cosf(a);
        pTeresa[i].field_0x1C = 0.0f;
        pTeresa[i].field_0x20 = randf(-0.1f, 0.1f);
        pTeresa[i].t = 0.0f;
        pTeresa[i].wait = 1.7f * (i + 1);
        pTeresa[i].state = 0;
        pTeresa[i].field_0x24 = randf(0.0f, 350.0f);
    }
    g_nNumOutBox[0] = 0;
    g_nNumEndProc[0] = 0;
}
