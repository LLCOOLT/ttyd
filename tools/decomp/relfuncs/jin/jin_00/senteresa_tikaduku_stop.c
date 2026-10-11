// include: manager/evtmgr_cmd.h
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
// proto: USER_FUNC(senteresa_tikaduku_stop);
USER_FUNC(senteresa_tikaduku_stop) {
    s32 n = extGetPoseNum();
    s32 i;

    for (i = 0; i < n; i++) {
        if (pTeresa[i].seq != 10) {
            pTeresa[i].seq = 4;
            pTeresa[i].wait = 99999;
        }
    }
    return EVT_RETURN_DONE;
}
