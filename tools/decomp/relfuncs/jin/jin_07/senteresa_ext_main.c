// include: driver/extdrv.h
// include: mario/mario.h
// include: mario/mariost.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Teresa { Vec pos; Vec dst; f32 t; f32 field_0x1C; f32 field_0x20; f32 field_0x24; s32 wait; u8 state; } Teresa;
// decl: static Teresa* pTeresa;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: s32 g_nNumOutBox[1];
// decl: static s32 g_nNumEndProc[1];
// decl: void computePosHermite(ExtPose* pose, Teresa* ter);
// proto: static void senteresa_ext_main(void);
static void senteresa_ext_main(void) {
    ExtPose* pose = extGetPosePtr();
    s32 n;
    s32 i;

    marioGetPtr();
    n = extGetPoseNum();
    for (i = 0; i < n; i++, pose++) {
        switch (pTeresa[i].state) {
            case 0:
                pose->frame = 0;
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    pose->flags |= 1;
                    g_nNumOutBox[0]++;
                    pTeresa[i].state++;
                }
                break;
            case 1:
                pose->frame = (gp->retraceCount + i * i) % 3 + 1;
                computePosHermite(pose, &pTeresa[i]);
                pTeresa[i].t += 0.015f;
                if (pTeresa[i].t >= 1.0f) {
                    pTeresa[i].pos.x = pose->mtx[0][3];
                    pTeresa[i].pos.y = pose->mtx[1][3];
                    pTeresa[i].pos.z = pose->mtx[2][3];
                    pTeresa[i].dst.x = 200.0f;
                    pTeresa[i].dst.y = pose->mtx[1][3];
                    pTeresa[i].dst.z = 50.0f;
                    pTeresa[i].t = 0.01f;
                    pTeresa[i].state = 99;
                    g_nNumEndProc[0]++;
                }
                break;
            case 99:
                break;
        }
    }
    if (g_nNumEndProc[0] == 200) {
        extReset();
    }
}
