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
// proto: USER_FUNC(senteresa_get_seq);
USER_FUNC(senteresa_get_seq) {
    s32* args = event->args;
    s32 i = evtGetValue(event, args[0]);

    evtSetValue(event, args[1], pTeresa[i].seq);
    return EVT_RETURN_DONE;
}
