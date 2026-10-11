// include: manager/evtmgr_cmd.h
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
// proto: USER_FUNC(senteresa_turiageru);
USER_FUNC(senteresa_turiageru) {
    s32 n = extGetPoseNum();
    s32 i;

    g_nNumEndProc[0] = 0;
    for (i = 0; i < n; i++) {
        if (pTeresa[i].seq == 6) {
            pTeresa[i].seq = 80;
        } else if (pTeresa[i].seq != 9) {
            pTeresa[i].wait = 99999;
        }
    }
    return EVT_RETURN_DONE;
}
