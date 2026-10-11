// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: pmario_sound.h
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
// decl: static f32 randf(f32 min, f32 max);
// proto: USER_FUNC(senteresa_huttobu);
USER_FUNC(senteresa_huttobu) {
    ExtPose* pose = extGetPosePtr();
    NpcEntry* npc = npcNameToPtr("\203A\203g\203~\203b\203N\203e\203\214\203T");
    s32 n = extGetPoseNum();
    s32 i;
    f32 scale;

    g_nNumEndProc[0] = 0;
    for (i = 0; i < n; i++, pose++) {
        pose->flags = 3;
        pose->mtx[0][3] = npc->position.x;
        pose->mtx[1][3] = npc->position.y;
        pose->mtx[2][3] = npc->position.z;
        pTeresa[i].vel.x = 4.0f * (f32)sin(pTeresa[i].angle);
        pTeresa[i].vel.y = randf(6.0f, 12.0f);
        pTeresa[i].vel.z = cos(pTeresa[i].angle);
        if (pTeresa[i].vel.z > 0.0f) {
            scale = randf(5.0f, 12.5f);
        } else {
            scale = randf(-5.0f, -2.0f);
        }
        pTeresa[i].vel.z *= scale;
        pTeresa[i].alpha = 255;
        pTeresa[i].seq = 30;
        if (i & 1) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = pose->mtx[0][3];
            pos.y = pose->mtx[1][3];
            pos.z = pose->mtx[2][3];
            psndSFXOn_3D((const char*)0x5D7, &pos);
        }
    }
    return EVT_RETURN_DONE;
}
