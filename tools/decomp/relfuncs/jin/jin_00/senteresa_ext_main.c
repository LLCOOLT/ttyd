// include: dolphin/mtx.h
// include: mario/mario.h
// include: mario/mariost.h
// include: party.h
// include: evt/evt_bero.h
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
// decl: static inline f32 sinf(f32 x) { return sin(x); }
// decl: static f32 randf(f32 min, f32 max);
// decl: int rand(void);
// decl: f32 marioGetAngleKaitenHammer(void);
// decl: static void computePos(Teresa* ter, Vec* out);
// decl: s32 computeAlpha(Teresa* ter, MarioWork* mp, f32 angle);
// decl: void computeMtx(ExtPose* pose, f32 angle);
// decl: f32 computeAngle(ExtPose* pose, MarioWork* mp);
// proto: static void senteresa_ext_main(void);
static void senteresa_ext_main(void) {
    ExtPose* pose = extGetPosePtr();
    MarioWork* mp = marioGetPtr();
    s32 n = extGetPoseNum();
    s32 i;
    s32 hammer = 0;
    s32 bero;
    s32 party;
    s32 res;
    u8 alpha;
    f32 angle;
    f32 spd;
    Vec v;
    Vec d;

    if (marioGetAngleKaitenHammer() > 0.0f) {
        hammer = 1;
    }
    PSVECSubtract(&mp->position, &g_vecRotCenter, &d);
    if (mp->baseSpeed > 0.0f) {
        g_bMove = 1;
    }
    if (g_bMove) {
        g_nMarioMoveCnt++;
    }
    if (g_nMarioMoveCnt > 12) {
        g_fSpeed += 0.01f;
        if (g_fSpeed > 2.6f) {
            g_fSpeed = 2.6f;
        }
        if (d.x == 0.0f && d.y == 0.0f && d.z == 0.0f) {
            g_vecRotCenter = mp->position;
            if (mp->baseSpeed == 0.0f) {
                g_fSpeed = 0.0f;
                g_bMove = 0;
                g_nMarioMoveCnt = 0;
            }
        } else {
            f32 mag = PSVECMag(&d);
            if (mag > 50.0f) {
                spd = 2.6f;
            } else {
                spd = 2.6f * mag / 50.0f;
            }
            if (g_fSpeed > spd) {
                g_fSpeed = spd;
            }
            PSVECNormalize(&d, &d);
            PSVECScale(&d, &d, g_fSpeed);
            PSVECAdd(&g_vecRotCenter, &d, &g_vecRotCenter);
            PSVECSubtract(&g_vecRotCenter, &mp->position, &v);
            if (PSVECMag(&v) < 0.3f) {
                g_vecRotCenter = mp->position;
                if (mp->baseSpeed == 0.0f) {
                    g_fSpeed = 0.0f;
                    g_bMove = 0;
                    g_nMarioMoveCnt = 0;
                }
            }
        }
    }
    bero = (bero_get_BeroEXEC() & 3) != 0;
    party = 0;
    if (partyGetPtr(0) != NULL && (partyGetPtr(0)->flags & 0x100)) {
        party = 1;
    }
    for (i = 0; i < n; i++, pose++) {
        switch (pTeresa[i].seq) {
            case 0:
                pose->frame = 0;
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    if (i == 0) {
                        Vec pos = {0.0f, 200.0f, 0.0f};
                        psndSFXOn_3D((const char*)0x5D3, &pos);
                    }
                    pTeresa[i].seq++;
                }
                break;
            case 1:
                pose->frame = (gp->retraceCount / 5 + i * i) % 16;
                if (mp->position.x < pose->mtx[0][3]) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                computePos(&pTeresa[i], &v);
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                v.y = pose->mtx[1][3];
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                angle = computeAngle(pose, mp);
                pTeresa[i].alpha += 3;
                alpha = pTeresa[i].alpha;
                computeAlpha(&pTeresa[i], mp, angle);
                if (pTeresa[i].alpha < alpha) {
                    pTeresa[i].seq++;
                    g_nNumEndProc[0]++;
                    if (i == 0) {
                        Vec pos = {0.0f, 200.0f, 0.0f};
                        psndSFXOn_3D((const char*)0x5D3, &pos);
                    }
                } else {
                    pTeresa[i].alpha = alpha;
                    if (pTeresa[i].alpha >= 250) {
                        pTeresa[i].alpha = 255;
                        pTeresa[i].seq++;
                        g_nNumEndProc[0]++;
                        if (i == 0) {
                            Vec pos = {0.0f, 200.0f, 0.0f};
                            psndSFXOn_3D((const char*)0x5D3, &pos);
                        }
                    }
                }
                break;
            case 2:
                pose->frame = (gp->retraceCount / 5 + i * i) % 16;
                if (mp->position.x < pose->mtx[0][3]) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                computePos(&pTeresa[i], &v);
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                v.y = pose->mtx[1][3];
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                angle = computeAngle(pose, mp);
                computeAlpha(&pTeresa[i], mp, angle);
                if (g_nNumEndProc[0] == 200) {
                    pTeresa[i].wait = i + 1;
                    pTeresa[i].seq++;
                }
                break;
            case 3:
                pose->frame = (gp->retraceCount / 5 + i * i) % 16;
                if (mp->position.x < pose->mtx[0][3]) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                computePos(&pTeresa[i], &v);
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                v.y = pose->mtx[1][3];
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pTeresa[i].field_0x1C += 0.08f;
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    pose->flags &= ~2;
                    pTeresa[i].wait = i * 30 + rand() % 10 + 295;
                    pTeresa[i].seq++;
                }
                break;
            case 4:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                computePos(&pTeresa[i], &v);
                v.y = pose->mtx[1][3];
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[1][3] = v.y;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                pTeresa[i].field_0x20 += 0.01f;
                if (pTeresa[i].field_0x20 > 1.2f) {
                    pTeresa[i].field_0x20 = 1.2f;
                }
                pTeresa[i].angle += pTeresa[i].field_0x20;
                if (pTeresa[i].angle > 360.0f) {
                    pTeresa[i].angle -= 360.0f;
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                res = computeAlpha(&pTeresa[i], mp, angle);
                if (g_nNumHuttobasu[0] >= 20) {
                    break;
                }
                if (res && rand() % 1000 == 312) {
                    pTeresa[i].wait = 100;
                    pTeresa[i].seq = 9;
                }
                if (!party && g_nNumHuttobasu[0] < 20) {
                    pTeresa[i].wait--;
                    if (pTeresa[i].wait == 0) {
                        pTeresa[i].field_0x1C = 0.0f;
                        pTeresa[i].seq++;
                    }
                }
                break;
            case 5:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                v.x = pose->mtx[0][3];
                v.y = pose->mtx[1][3];
                v.z = pose->mtx[2][3];
                PSVECSubtract(&mp->position, &v, &d);
                PSVECNormalize(&d, &d);
                PSVECScale(&d, &d, 1.8f);
                PSVECAdd(&v, &d, &v);
                pose->mtx[0][3] = v.x;
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pose->mtx[2][3] = v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                if (!party) {
                    PSVECSubtract(&v, &mp->position, &v);
                    if (PSVECMag(&v) <= 25.0f) {
                        f32 dy = pose->mtx[1][3] - mp->position.y;
                        if (dy > -2.0f && dy < 10.0f) {
                            pTeresa[i].ofs.x = pose->mtx[0][3] - mp->position.x;
                            pTeresa[i].ofs.y = pose->mtx[1][3] - mp->position.y;
                            pTeresa[i].ofs.z = pose->mtx[2][3] - mp->position.z;
                            pTeresa[i].seq++;
                            if (!bero) {
                                g_nNumHarituku[0]++;
                            }
                        }
                    }
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                computeAlpha(&pTeresa[i], mp, angle);
                break;
            case 6:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                pose->mtx[0][3] = mp->position.x + pTeresa[i].ofs.x;
                pose->mtx[1][3] = mp->position.y + pTeresa[i].ofs.y;
                pose->mtx[2][3] = mp->position.z + pTeresa[i].ofs.z;
                angle = computeAngle(pose, mp);
                computeAlpha(&pTeresa[i], mp, angle);
                if (hammer) {
                    v.x = pose->mtx[0][3];
                    v.y = pose->mtx[1][3];
                    v.z = pose->mtx[2][3];
                    PSVECSubtract(&v, &mp->position, &d);
                    PSVECNormalize(&d, &d);
                    pTeresa[i].vel.x = 4.2f * d.x;
                    if (d.z > 0.0f) {
                        spd = d.z * randf(5.2f, 12.7f);
                    } else {
                        spd = d.z * randf(-5.0f, -2.0f);
                    }
                    pTeresa[i].vel.z = spd;
                    pTeresa[i].vel.y = randf(6.0f, 10.0f);
                    pTeresa[i].seq = 10;
                    computeMtx(pose, 0.0f);
                    g_nNumHarituku[0]--;
                    g_nNumHuttobasu[0]++;
                    {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        psndSFXOn_3D((const char*)0x5D7, &pos);
                    }
                }
                break;
            case 9:
                pose->frame = (s32)(12.0f * ((100.0f - pTeresa[i].wait) / 100.0f)) + 34;
                computePos(&pTeresa[i], &v);
                v.y = pose->mtx[1][3];
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                pTeresa[i].angle += 1.2f;
                if (pTeresa[i].angle > 360.0f) {
                    pTeresa[i].angle -= 360.0f;
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                res = computeAlpha(&pTeresa[i], mp, angle);
                pTeresa[i].wait--;
                if (!res || pTeresa[i].wait == 0) {
                    pTeresa[i].wait = rand() % 300 + 200;
                    pTeresa[i].seq = 4;
                }
                break;
            case 10:
                pose->frame = (gp->retraceCount + i * i) % 8 + 26;
                pose->mtx[0][3] += pTeresa[i].vel.x;
                pose->mtx[1][3] += pTeresa[i].vel.y;
                pose->mtx[2][3] += pTeresa[i].vel.z;
                pTeresa[i].vel.y -= 0.3f;
                if (pose->mtx[1][3] < -20.0f) {
                    pose->flags = 0;
                    pTeresa[i].seq = 99;
                }
                break;
            case 20:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                computePos(&pTeresa[i], &v);
                v.y = pose->mtx[1][3];
                pose->mtx[0][3] = g_vecRotCenter.x + v.x;
                pose->mtx[1][3] = 0.4f * sinf(1.2f * pTeresa[i].field_0x1C) + v.y;
                pose->mtx[2][3] = g_vecRotCenter.z + v.z;
                pTeresa[i].field_0x1C += 0.08f;
                if (pTeresa[i].field_0x1C > 3.1415927f) {
                    pTeresa[i].field_0x1C -= 3.1415927f;
                }
                pTeresa[i].angle += 1.2f;
                if (pTeresa[i].angle > 360.0f) {
                    pTeresa[i].angle -= 360.0f;
                }
                angle = computeAngle(pose, mp);
                computeMtx(pose, angle);
                computeAlpha(&pTeresa[i], mp, angle);
                pTeresa[i].wait--;
                if (pTeresa[i].wait == 0) {
                    pose->flags = 3;
                    pTeresa[i].from.x = pose->mtx[0][3];
                    pTeresa[i].from.y = pose->mtx[1][3];
                    pTeresa[i].from.z = pose->mtx[2][3];
                    pTeresa[i].field_0x1C = 0.0f;
                    pTeresa[i].seq++;
                }
                break;
            case 21: {
                f32 t;

                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                t = pTeresa[i].field_0x1C;
                if (t >= 1.0f) {
                    pTeresa[i].seq = 22;
                    {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        psndSFXOn_3D((const char*)0x5D4, &pos);
                    }
                    g_nNumEndProc[0]++;
                } else {
                    v.x = (1.0f - t) * pTeresa[i].from.x + t * pTeresa[i].to.x;
                    v.y = (1.0f - t) * pTeresa[i].from.y + t * pTeresa[i].to.y;
                    v.z = (1.0f - t) * pTeresa[i].from.z + t * pTeresa[i].to.z;
                    pose->mtx[0][3] = v.x;
                    pose->mtx[1][3] = 20.0f * (f32)sin(6.28f * pTeresa[i].field_0x1C) + v.y;
                    pose->mtx[2][3] = v.z;
                    pTeresa[i].field_0x1C += 0.01f;
                }
                break;
            }
            case 22:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                if ((pTeresa[i].wait & 7) == 0) {
                    pose->mtx[0][3] += 2.0f;
                } else if ((pTeresa[i].wait & 7) == 3) {
                    pose->mtx[0][3] -= 2.0f;
                }
                pTeresa[i].wait++;
                break;
            case 30:
                pose->frame = (gp->retraceCount + i * i) % 8 + 26;
                pose->mtx[0][3] += pTeresa[i].vel.x;
                pose->mtx[1][3] += pTeresa[i].vel.y;
                pose->mtx[2][3] += pTeresa[i].vel.z;
                pTeresa[i].vel.y -= 0.3f;
                if (pose->mtx[1][3] < -10.0f) {
                    pose->flags = 0;
                    pTeresa[i].seq = 99;
                    g_nNumEndProc[0]++;
                }
                break;
            case 80:
                pose->frame = (gp->retraceCount + i * i) % 10 + 16;
                pose->mtx[1][3] = mp->position.y + pTeresa[i].ofs.y;
                break;
            case 99:
                break;
        }
    }
}
