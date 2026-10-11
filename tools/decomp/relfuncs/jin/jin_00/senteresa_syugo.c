// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
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
// decl: double sin(double x);
// decl: double cos(double x);
// decl: static inline f32 sinf(f32 x) { return sin(x); }
// decl: static inline f32 cosf(f32 x) { return cos(x); }
// decl: static f32 randf(f32 min, f32 max);
// decl: int rand(void);
// proto: USER_FUNC(senteresa_syugo);
USER_FUNC(senteresa_syugo) {
    ExtPose* pose = extGetPosePtr();
    NpcEntry* npc = npcNameToPtr("\222\206\211\233\203e\203\214\203T");
    s32 n = extGetPoseNum();
    s32 i;
    f32 a;
    f32 r;

    g_nNumEndProc[0] = 0;
    for (i = 0; i < n; i++, pose++) {
        pTeresa[i].from.x = pose->mtx[0][3];
        pTeresa[i].from.y = pose->mtx[1][3];
        pTeresa[i].from.z = pose->mtx[2][3];
        a = randf(0.0f, 6.2831f);
        r = randf(0.0f, 25.0f);
        pTeresa[i].to.x = r * cosf(a) + npc->position.x;
        pTeresa[i].to.y = r * sinf(a) + npc->position.y;
        pTeresa[i].to.z = npc->position.z;
        pTeresa[i].field_0x1C = 0.0f;
        pTeresa[i].wait = (i & 15) + rand() % 10 * 30 + 1;
        pTeresa[i].alpha = 255;
        pTeresa[i].seq = 20;
        if (pTeresa[i].from.x < pTeresa[i].to.x) {
            pose->rot = 270.0f;
        } else {
            pose->rot = 90.0f;
        }
    }
    return EVT_RETURN_DONE;
}
