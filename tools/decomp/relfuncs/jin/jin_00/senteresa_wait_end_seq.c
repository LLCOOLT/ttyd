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
// proto: USER_FUNC(senteresa_wait_end_seq);
USER_FUNC(senteresa_wait_end_seq) {
    return g_nNumEndProc[0] == 200 ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
