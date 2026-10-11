// include: memory.h
// include: dolphin/mtx.h
// include: mario/mario.h
// decl: typedef struct Teresa { Vec vel; f32 angle; Vec ofs; f32 field_0x1C; f32 field_0x20; Vec from; Vec to; s32 wait; u8 alpha; u8 seq; } Teresa;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
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
// decl: static f32 randf(f32 min, f32 max);
// proto: static void senteresa_ext_init(void);
static void senteresa_ext_init(void) {
    ExtPose* pose = extGetPosePtr();
    MarioWork* mp = marioGetPtr();
    s32 n = extGetPoseNum();
    s32 i;

    pTeresa = _mapAlloc(sizeof(Teresa) * 200);
    for (i = 0; i < n; i++, pose++) {
        pose->flags = 3;
        PSMTXIdentity(pose->mtx);
        pTeresa[i].angle = 0.0f;
        pTeresa[i].wait = (i % 100 + 1) * 3;
        pTeresa[i].alpha = 0;
        pTeresa[i].seq = 0;
        pTeresa[i].field_0x20 = randf(0.0f, 0.1f);
        pTeresa[i].ofs.x = randf(-300.0f, 300.0f);
        pTeresa[i].ofs.y = 0.0f;
        pTeresa[i].ofs.z = randf(-235.0f, 235.0f);
        pose->mtx[0][3] = mp->position.x + pTeresa[i].ofs.x;
        pose->mtx[1][3] = randf(10.0f, 400.0f);
        pose->mtx[2][3] = mp->position.z + pTeresa[i].ofs.z;
        if (mp->position.x < pose->mtx[0][3]) {
            pose->rot = 90.0f;
        } else {
            pose->rot = 270.0f;
        }
    }
    g_nNumEndProc[0] = 0;
    g_nNumHarituku[0] = 0;
    g_nNumHuttobasu[0] = 0;
    g_nMarioMoveCnt = 0;
    g_fSpeed = 0.0f;
    g_bMove = 0;
    g_vecRotCenter.x = mp->position.x;
    g_vecRotCenter.y = 0.0f;
    g_vecRotCenter.z = mp->position.z;
}
