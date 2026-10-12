// include: driver/npcdrv.h
// include: driver/extdrv.h
// include: driver/camdrv.h
// include: mario/mariost.h
// include: pmario_sound.h
// include: stdlib.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct YuuNpcPose { char name[16]; char anim[8]; u16 field_0x18; f32 frames; f32 jump; s32 start; s32 count; u16 flags; f32 field_0x30; } YuuNpcPose;
// decl: typedef struct YuuNpc { u16 id; u16 flags; s16 state; f32 field_0x8; Vec goal; Vec dest; Vec pos; Vec dir; f32 speed; f32 vy; f32 field_0x44; f32 zofs; s32 field_0x4c; s32 field_0x50; s16 poseId; s16 poses[4]; u8 field_0x5e[2]; NpcEntry* npc; f32 animSpeed; u64 time; } YuuNpc;
// decl: typedef struct YuuNpcWork { u16 flags; s32 numNpc; s32 slot[3]; YuuNpc* npcs; s32 basePoseNum; s32 numPoses; s32 chusanPose; s16 hit[6 * 72]; s16 hitY[72]; YuuNpcPose pose[32]; } YuuNpcWork;
// decl: static YuuNpcWork* yuunpc_wp;
// decl: void* yuunpc_yuuminigame4_ptr;
// decl: ExtPose* extGetPosePtr(void);
// decl: f32 yuunpc_pose_sub(ExtPose* ext, YuuNpc* npc);
// decl: void yuunpc_pose_change(YuuNpc* npc, s16 id, f32 speed, f32 frame);
// decl: s32 goalincheck(YuuNpc* npc);
// decl: void errper_set_rtn(YuuNpc* npc);
// decl: s32 hitcheck(YuuNpc* npc);
// decl: s32 fallcheck(YuuNpc* npc);
// proto: void yuunpc_pose_minigame4_main(void);
typedef struct YuuMg4Sub { u8 field_0x0[0x10]; s32 mode; s32 limit; } YuuMg4Sub;
typedef struct YuuMg4 { u8 field_0x0[0x1c]; YuuMg4Sub* sub; } YuuMg4;

static inline s32 yuunpc_hitY_get(f32 x) {
    s32 out = 0;

    if (x < -1800.0f || x >= 1800.0f) {
        out = 1;
    }
    if (out) {
        return 0;
    }
    return yuunpc_wp->hitY[(s32)((x - -1800.0f) / 50.0f)];
}

static inline s32 yuunpc_hit_ofs(YuuNpc* npc, Vec* ofs) {
    f32 x = npc->pos.x + ofs->x;
    s32 out = 0;

    if (x < -1800.0f || x >= 1800.0f || npc->pos.z + ofs->z < -150.0f || npc->pos.z + ofs->z >= 150.0f) {
        out = 1;
    }
    if (out) {
        return -500;
    }
    return yuunpc_wp->hit[(s32)((npc->pos.z + ofs->z - -150.0f) / 50.0f) * 72 + (s32)((x - -1800.0f) / 50.0f)];
}

static inline f32 yuunpc_rnd10(YuuNpc* npc) {
    return 10.0f * ((npc->id % 101 - 50) / 50.0f);
}

#define YUU_STOP(npc)                                                              \
    do {                                                                           \
        (npc)->field_0x4c = 0;                                                     \
        yuunpc_pose_change((npc), (npc)->poses[0], 1.0f, rand() / 32767.0f);       \
        (npc)->speed = 0.0f;                                                       \
    } while (0)

#define YUU_JUMP(npc)                                                                                                    \
    do {                                                                                                                 \
        (npc)->field_0x4c = 4;                                                                                           \
        yuunpc_pose_change((npc), (npc)->poses[3], 0.0f, yuunpc_wp->pose[(npc)->poses[3]].jump / yuunpc_wp->pose[(npc)->poses[3]].frames); \
        (npc)->vy = 6.5f;                                                                                                \
        (npc)->dir.x = 1.0f;                                                                                             \
        (npc)->dir.z = 0.0f;                                                                                             \
        if (!(c26 & 0x1f)) {                                                                                             \
            psndSFXOn_3D((const char*)0x8e0, &(npc)->pos);                                                               \
        }                                                                                                                \
        c26++;                                                                                                           \
    } while (0)

#define YUU_RUN(npc)                                                               \
    do {                                                                           \
        (npc)->field_0x4c = 2;                                                     \
        yuunpc_pose_change((npc), (npc)->poses[2], 1.0f, rand() / 32767.0f);       \
        if ((npc)->flags & 0x18) {                                                 \
            (npc)->speed = 1.0f;                                                   \
        } else {                                                                   \
            (npc)->speed = 2.25f;                                                  \
        }                                                                          \
    } while (0)

#define YUU_WALK(npc)                                                                                         \
    do {                                                                                                      \
        (npc)->field_0x4c = 1;                                                                                \
        yuunpc_pose_change((npc), (npc)->poses[1], yuunpc_wp->pose[(npc)->poses[1]].field_0x30, rand() / 32767.0f); \
        if ((npc)->flags & 0x18) {                                                                            \
            (npc)->speed = 0.5f;                                                                              \
        } else {                                                                                              \
            (npc)->speed = 1.0f;                                                                              \
        }                                                                                                     \
    } while (0)

void yuunpc_pose_minigame4_main(void) {
    s32 i;
    ExtPose* ext;
    f32 right;
    f32 camX = camGetPtr(4)->cameraAt.x;
    YuuNpc* npc;
    f32 x, y, z;
    s32 c28 = 0;
    s32 c27 = 0;
    s32 c26 = 0;
    YuuMg4Sub* mg;
    s32 kind;
    s16 h;
    s16 k;
    f32 px;
    f32 off;
    f32 w;
    f32 d;
    f32 dz;
    f32 ha;
    f32 hb;
    f32 hc;
    s32 mode;
    s32 cnt;
    s32 n;
    u32 t;

    ext = extGetPosePtr();
    npc = yuunpc_wp->npcs;
    right = 500.0f + camX;

    for (i = 0; i < yuunpc_wp->numNpc; i++, ext++, npc++) {
        if (npc->flags & 1) {
            x = ext->mtx[0][3];
            if (x > camX) {
                while (TRUE) {
                    if (!(x > right)) break;
                    x -= 1000.0f;
                    ext->mtx[0][3] = x;
                }
            } else {
                while (TRUE) {
                    if (!(x < camX - 500.0f)) break;
                    x += 1000.0f;
                    ext->mtx[0][3] = x;
                }
            }
            z = ext->mtx[2][3];
            if (z < -570.0f) {
                y = ext->mtx[1][3];
                if ((x >= -1700.0f && x <= -1600.0f) || (x >= -50.0f && x <= 50.0f) || (x >= 1600.0f && x <= 1700.0f)) {
                    if (y > -500.0f) {
                        y += -1000.0f;
                        ext->mtx[1][3] = y;
                    }
                } else {
                    if (y < -500.0f) {
                        y -= -1000.0f;
                        ext->mtx[1][3] = y;
                    }
                }
            }
            if (irand(100) == 0) {
                if (irand(101) <= 80) {
                    ext->rot = angleABf(camX, 0.0f, x, z);
                } else {
                    ext->rot = angleABf(camX, 0.0f, x - 2.0f * (x - camX), z);
                }
            }
        }
        if (npc->flags & 2) {
            if (yuunpc_yuuminigame4_ptr == NULL || (npc->flags & 0x80)) {
                continue;
            }
            mg = ((YuuMg4*)yuunpc_yuuminigame4_ptr)->sub;
            switch (npc->flags & 0x18) {
            case 0:
                break;
            case 8:
                if (npc->field_0x50 == 0) {
                    npc->flags |= 0x18;
                }
                break;
            case 0x10:
                if (npc->field_0x50 == 0) {
                    npc->flags &= ~0x18;
                    npc->field_0x44 = 0.0f;
                    npc->field_0x4c = 0;
                    yuunpc_pose_change(npc, npc->poses[0], 1.0f, rand() / 32767.0f);
                    npc->speed = 0.0f;
                }
                break;
            case 0x18:
                break;
            }
            switch (npc->field_0x4c) {
            case 0:
            case 1:
            case 2:
                if (!(npc->flags & 0x20)) {
                    npc->field_0x4c = 3;
                    yuunpc_pose_change(npc, npc->poses[3], 0.0f, yuunpc_wp->pose[npc->poses[3]].jump / yuunpc_wp->pose[npc->poses[3]].frames);
                    npc->vy = 0.0f;
                }
                break;
            case 3:
            case 4:
                if (npc->flags & 0x20) {
                    npc->field_0x4c = 0;
                    yuunpc_pose_change(npc, npc->poses[0], 1.0f, rand() / 32767.0f);
                    npc->speed = 0.0f;
                }
                break;
            }
            if (npc->field_0x4c != 3 && npc->field_0x4c != 4) {
                px = npc->pos.x;
                kind = 1;
                h = yuunpc_hitY_get(px);
                k = h;
                switch (h) {
                case 0:
                case 1:
                    npc->dest = npc->goal;
                    if (npc->pos.x < 1500.0f) {
                        d = npc->pos.z - npc->dest.z;
                        if (d < 0.0f) {
                            d = -d;
                        }
                        if (d > 16.666666f) {
                            npc->dest.x = npc->pos.x + 300.0f * (1.0f - d / 300.0f) * 0.5f;
                        }
                    }
                    break;
                case 24:
                case 25:
                case 26:
                case 27:
                case 28:
                    kind = 2;
                    k -= 22;
                case 2:
                case 3:
                case 4:
                case 5:
                case 6:
                    if (k == 6) {
                        off = 0.0f;
                    } else {
                        off = 50.0f * (3 - (k - 2));
                    }
                    npc->dest.x = ((s32)((3600.0f + (px + off)) / 50.0f) + 1) * 50.0f - 3600.0f;
                    {
                        f32 sp = ((npc->id % 101 - 50) / 50.0f) * (50.0f * (kind - 1) * 0.5f + 10.0f);
                        npc->dest.z = npc->pos.z >= 0.0f ? 150.0f - 50.0f * kind * 0.5f + sp : -150.0f + 50.0f * kind * 0.5f + sp;
                    }
                    npc->dest.y = npc->pos.y;
                    break;
                case 7:
                case 8:
                case 9:
                case 10:
                    off = 50.0f * (3 - (h - 7));
                    npc->dest.x = ((s32)((3600.0f + (px + off)) / 50.0f) + 1) * 50.0f - 3600.0f;
                    npc->dest.z = 0.65f * npc->goal.z;
                    npc->dest.y = npc->pos.y;
                    break;
                case 11:
                    npc->dest.x = ((s32)((3600.0f + (50.0f + px)) / 50.0f) + 1) * 50.0f - 3600.0f;
                    npc->dest.z = npc->pos.z;
                    npc->dest.y = npc->pos.y;
                    break;
                case 12:
                case 13:
                case 14:
                case 15:
                    if ((u16)npc->id & 3) {
                        off = 50.0f * (3 - (h - 12));
                        npc->dest.x = ((s32)((3600.0f + (px + off)) / 50.0f) + 1) * 50.0f - 3600.0f;
                        npc->dest.z = -(75.0f + yuunpc_rnd10(npc));
                        npc->dest.y = npc->pos.y;
                    } else {
                        npc->dest.x = ((s32)((3600.0f + (50.0f + px)) / 50.0f) + 1) * 50.0f - 3600.0f;
                        npc->dest.z = npc->pos.z;
                        npc->dest.y = npc->pos.y;
                    }
                    break;
                case 16:
                case 17:
                case 18:
                case 19:
                    if ((u16)npc->id & 3) {
                        off = 50.0f * (3 - (h - 16));
                        npc->dest.x = ((s32)((3600.0f + (px + off)) / 50.0f) + 1) * 50.0f - 3600.0f;
                        npc->dest.z = -25.0f + yuunpc_rnd10(npc);
                        npc->dest.y = npc->pos.y;
                    } else {
                        npc->dest.x = ((s32)((3600.0f + (50.0f + px)) / 50.0f) + 1) * 50.0f - 3600.0f;
                        npc->dest.z = npc->pos.z;
                        npc->dest.y = npc->pos.y;
                    }
                    break;
                case 20:
                case 21:
                case 22:
                case 23:
                    if ((u16)npc->id & 3) {
                        off = 50.0f * (3 - (h - 20));
                        npc->dest.x = ((s32)((3600.0f + (px + off)) / 50.0f) + 1) * 50.0f - 3600.0f;
                        npc->dest.z = 75.0f + yuunpc_rnd10(npc);
                        npc->dest.y = npc->pos.y;
                    } else {
                        npc->dest.x = ((s32)((3600.0f + (50.0f + px)) / 50.0f) + 1) * 50.0f - 3600.0f;
                        npc->dest.z = npc->pos.z;
                        npc->dest.y = npc->pos.y;
                    }
                    break;
                }
                PSVECSubtract(&npc->dest, &npc->pos, &npc->dir);
                npc->dir.y = 0.0f;
                PSVECNormalize(&npc->dir, &npc->dir);
                w = 150.0f * npc->field_0x8;
                mode = mg->mode;
                switch (mode) {
                default:
                    d = 0.0f;
                    break;
                case 1:
                case 2:
                case 3:
                case 4:
                    switch (h) {
                    case 0:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 12:
                    case 13:
                    case 14:
                    case 16:
                    case 17:
                    case 18:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 25:
                    case 26:
                        if (npc->pos.z >= -150.0f && npc->pos.z < 150.0f + w) {
                            d = 150.0f + w - npc->pos.z;
                        } else {
                            d = 0.0f;
                        }
                        break;
                    case 1:
                    case 10:
                        d = 0.0f;
                        break;
                    case 5:
                    case 6:
                    case 27:
                    case 28:
                        z = npc->pos.z;
                        if (z >= -150.0f && z < 150.0f) {
                            f32 tt = 50.0f * kind;
                            f32 a = -150.0f + tt + w;
                            if (z >= a && z < 150.0f - tt) {
                                d = 0.0f;
                            } else if (z > 0.0f) {
                                d = 150.0f + w - z;
                            } else {
                                d = a - z;
                            }
                        } else {
                            d = 0.0f;
                        }
                        break;
                    }
                    break;
                case 5:
                case 6:
                case 7:
                case 8:
                    switch (h) {
                    case 0:
                    case 2:
                    case 3:
                    case 4:
                    case 7:
                    case 8:
                    case 9:
                    case 12:
                    case 13:
                    case 14:
                    case 16:
                    case 17:
                    case 18:
                    case 20:
                    case 21:
                    case 22:
                    case 24:
                    case 25:
                    case 26:
                        if (npc->pos.z >= -150.0f + w && npc->pos.z < 150.0f) {
                            d = -(-150.0f + w) + npc->pos.z;
                        } else {
                            d = 0.0f;
                        }
                        break;
                    case 1:
                    case 10:
                        d = 0.0f;
                        break;
                    case 5:
                    case 6:
                    case 27:
                    case 28:
                        z = npc->pos.z;
                        if (z >= -150.0f + w && z < 150.0f) {
                            f32 tt = 50.0f * kind;
                            if (z >= -150.0f + tt && z < 150.0f - tt + w) {
                                d = 0.0f;
                            } else if (z > 0.0f) {
                                d = z - (150.0f - tt + w);
                            } else {
                                d = -(-150.0f + w) + z;
                            }
                        } else {
                            d = 0.0f;
                        }
                        break;
                    }
                    break;
                }
                d -= 17.0f;
                if (d < 0.0f) {
                    d = 0.0f;
                }
                cnt = d / 0.0f;
                switch (npc->flags & 0x18) {
                case 0:
                    if (mg->mode == 0) {
                        n = 1;
                    } else {
                        switch (mode) {
                        case 1:
                        case 5:
                            if (cnt >= 60) {
                                cnt += 60;
                            } else {
                                cnt += cnt;
                            }
                            break;
                        case 2:
                        case 6:
                            if (cnt >= mg->limit) {
                                cnt += mg->limit;
                            } else {
                                cnt += cnt;
                            }
                            break;
                        }
                        if (cnt < 30) {
                            n = 0;
                        } else {
                            n = d / 2.9166667f;
                        }
                    }
                    if (!(yuunpc_wp->flags & 1) && npc->goal.x > npc->pos.x && n <= 0) {
                        npc->flags |= 8;
                        npc->field_0x50 = 30;
                        npc->field_0x44 = ext->rot;
                        npc->field_0x4c = 0;
                        yuunpc_pose_change(npc, npc->poses[0], 1.0f, rand() / 32767.0f);
                        npc->speed = 0.0f;
                        errper_set_rtn(npc);
                    }
                    break;
                case 8:
                case 0x10:
                    break;
                case 0x18:
                    if (cnt < 30) {
                        n = 0;
                    } else {
                        cnt = 30;
                        n = d / 2.9166667f;
                    }
                    if (npc->goal.x == npc->pos.x || mg->mode == 0 || ((mg->mode == 4 || mg->mode == 8) && cnt + n >= mg->limit)) {
                        npc->flags &= ~8;
                        npc->field_0x50 = 30;
                        errper_set_rtn(npc);
                    }
                    break;
                }
            }
            switch (npc->flags & 0x18) {
            case 0:
                break;
            case 8:
                npc->field_0x50--;
                ext->rot = npc->field_0x44 + -450.0f * (1.0f - npc->field_0x50 / 30.0f);
                ext->rot = (3600.0f + ext->rot) - (s32)((3600.0f + ext->rot) / 360.0f) * 360;
                break;
            case 0x18:
                t = gp->retraceCount + (u16)npc->id;
                if (t & 0x20) {
                    n = 15 - (t & 0x1f);
                } else {
                    n = (t & 0x1f) - 15;
                }
                ext->rot = -450.0f + npc->field_0x44 + 2.0f * n;
                ext->rot = (3600.0f + ext->rot) - (s32)((3600.0f + ext->rot) / 360.0f) * 360;
                break;
            case 0x10:
                npc->field_0x50--;
                ext->rot = -180.0f + (-450.0f + npc->field_0x44) + -450.0f * (1.0f - npc->field_0x50 / 30.0f);
                ext->rot = (3600.0f + ext->rot) - (s32)((3600.0f + ext->rot) / 360.0f) * 360;
                break;
            }
            npc->zofs = 0.0f;
            if (npc->pos.x < 1500.0f) {
                dz = 0.0f;
                mode = mg->mode;
                switch (mode) {
                case 2:
                case 3:
                case 4:
                    switch (npc->flags & 0x18) {
                    case 0x18:
                        dz = 0.0f;
                        break;
                    case 8:
                    case 0x10:
                        dz = 0.0f;
                        break;
                    case 0:
                        dz = 2.9166667f;
                        break;
                    }
                    break;
                case 6:
                case 7:
                case 8:
                    switch (npc->flags & 0x18) {
                    case 0x18:
                        dz = -0.0f;
                        break;
                    case 8:
                    case 0x10:
                        dz = -0.0f;
                        break;
                    case 0:
                        dz = -2.9166667f;
                        break;
                    }
                    break;
                }
                switch (mode) {
                case 2:
                case 6:
                    dz = dz * (60 - mg->limit) / 60.0f;
                    break;
                }
                npc->zofs += dz;
            }
            do {
                kind = 0;
                switch (npc->field_0x4c) {
                case 0:
                    if (goalincheck(npc) == -1) {
                        break;
                    }
                    if (yuunpc_wp->flags & 1) {
                        break;
                    }
                    if (npc->state >= 2 || (npc->state <= 1 && irand(36) == 0)) {
                        px = npc->pos.x;
                        ha = yuunpc_hit_get(25.0f + px, &npc->pos.z);
                        hb = yuunpc_hit_get(75.0f + px, &npc->pos.z);
                        if (npc->state <= 3 && irand(2)) {
                            if (ha >= npc->pos.y) {
                                YUU_WALK(npc);
                                kind = 1;
                            }
                        } else if (!(npc->flags & 0x18) || ((npc->flags & 0x18) && (ha >= npc->pos.y || (ha < npc->pos.y && hb < npc->pos.y)))) {
                            YUU_RUN(npc);
                            kind = 1;
                        }
                    }
                    break;
                case 1:
                    if (goalincheck(npc) == -1) {
                        YUU_STOP(npc);
                        break;
                    }
                    if (npc->flags & 0x18) {
                        Vec v1, s1;

                        PSVECSubtract(&npc->dest, &npc->pos, &v1);
                        PSVECNormalize(&v1, &v1);
                        PSVECScale(&v1, &s1, 10.0f);
                        ha = yuunpc_hit_ofs(npc, &s1);
                        PSVECScale(&v1, &s1, 25.0f);
                        hb = yuunpc_hit_ofs(npc, &s1);
                        PSVECScale(&v1, &s1, 75.0f);
                        hc = yuunpc_hit_ofs(npc, &s1);
                        if (ha > npc->pos.y) {
                            YUU_JUMP(npc);
                        } else if (hb < npc->pos.y && hc == npc->pos.y) {
                            YUU_STOP(npc);
                        } else if (irand(60) == 0) {
                            if (npc->state <= 1 && irand(3) == 0) {
                                YUU_STOP(npc);
                            } else if (hb >= npc->pos.y) {
                                YUU_RUN(npc);
                            }
                        }
                    } else {
                        Vec v2, s2;

                        PSVECSubtract(&npc->dest, &npc->pos, &v2);
                        PSVECNormalize(&v2, &v2);
                        PSVECScale(&v2, &s2, 20.0f);
                        ha = yuunpc_hit_ofs(npc, &s2);
                        PSVECScale(&v2, &s2, 25.0f);
                        hb = yuunpc_hit_ofs(npc, &s2);
                        PSVECScale(&v2, &s2, 75.0f);
                        hc = yuunpc_hit_ofs(npc, &s2);
                        if (ha > npc->pos.y) {
                            if (mg->mode == 0) {
                                YUU_JUMP(npc);
                            } else {
                                YUU_STOP(npc);
                            }
                        } else if ((hb < npc->pos.y && hc == npc->pos.y) || (npc->state <= 3 && irand(60) == 0)) {
                            if (npc->state <= 1 && irand(3) == 0) {
                                YUU_STOP(npc);
                            } else {
                                YUU_RUN(npc);
                            }
                        }
                    }
                    if (!(c28 & 0x3f)) {
                        t = gp->retraceCount + i;
                        if (!(t & 0xf)) {
                            if (t & 0x10) {
                                psndSFXOn_3D((const char*)0x8de, &npc->pos);
                            } else {
                                psndSFXOn_3D((const char*)0x8df, &npc->pos);
                            }
                        }
                    }
                    c28++;
                    break;
                case 2:
                    if (goalincheck(npc) == -1) {
                        YUU_STOP(npc);
                        break;
                    }
                    if (npc->flags & 0x18) {
                        Vec v3, s3;

                        PSVECSubtract(&npc->dest, &npc->pos, &v3);
                        PSVECNormalize(&v3, &v3);
                        PSVECScale(&v3, &s3, 20.0f);
                        ha = yuunpc_hit_ofs(npc, &s3);
                        PSVECScale(&v3, &s3, 25.0f);
                        hb = yuunpc_hit_ofs(npc, &s3);
                        PSVECScale(&v3, &s3, 75.0f);
                        hc = yuunpc_hit_ofs(npc, &s3);
                        if (ha > npc->pos.y) {
                            YUU_JUMP(npc);
                        } else if (hb < npc->pos.y && hc == npc->pos.y) {
                            YUU_STOP(npc);
                        } else if (npc->state <= 3 && irand(60) == 0) {
                            if (npc->state <= 1 && irand(3) == 0) {
                                YUU_STOP(npc);
                            } else if (hb >= npc->pos.y) {
                                YUU_WALK(npc);
                            }
                        }
                    } else {
                        Vec v4, s4;

                        PSVECSubtract(&npc->dest, &npc->pos, &v4);
                        PSVECNormalize(&v4, &v4);
                        PSVECScale(&v4, &s4, 5.0f);
                        ha = yuunpc_hit_ofs(npc, &s4);
                        PSVECScale(&v4, &s4, 45.0f);
                        hb = yuunpc_hit_ofs(npc, &s4);
                        PSVECScale(&v4, &s4, 55.0f);
                        hc = yuunpc_hit_ofs(npc, &s4);
                        if ((ha < npc->pos.y && hc == npc->pos.y) || hb > npc->pos.y) {
                            if (mg->mode == 0) {
                                YUU_JUMP(npc);
                            } else {
                                YUU_STOP(npc);
                            }
                        } else if (npc->state <= 3 && irand(60) == 0) {
                            if (npc->state <= 1 && irand(3) == 0) {
                                YUU_STOP(npc);
                            } else if ((f32)yuunpc_hit_get(25.0f + npc->pos.x, &npc->pos.z) >= npc->pos.y) {
                                YUU_WALK(npc);
                            }
                        }
                    }
                    if (!(c27 & 0x3f)) {
                        t = gp->retraceCount + i;
                        if (!(t & 7)) {
                            if (t & 8) {
                                psndSFXOn_3D((const char*)0x8de, &npc->pos);
                            } else {
                                psndSFXOn_3D((const char*)0x8df, &npc->pos);
                            }
                        }
                    }
                    c27++;
                    break;
                case 3:
                case 4:
                    break;
                }
            } while (kind);
            switch (npc->field_0x4c) {
            case 0:
            case 1:
            case 2:
                if (hitcheck(npc) == -1) {
                    npc->flags &= ~0x20;
                } else {
                    npc->flags |= 0x20;
                }
                break;
            case 3:
            case 4:
                hitcheck(npc);
                if (fallcheck(npc) == -1) {
                    npc->flags |= 0x20;
                } else {
                    npc->flags &= ~0x20;
                }
                if (npc->pos.y <= -100.0f) {
                    npc->flags |= 0x40;
                }
                if (npc->pos.y <= -500.0f) {
                    npc->flags |= 0x80;
                    ext->flags &= ~1;
                }
                break;
            }
            ext->mtx[0][3] = npc->pos.x;
            ext->mtx[1][3] = npc->pos.y;
            ext->mtx[2][3] = npc->pos.z;
        }
        yuunpc_pose_sub(ext, npc);
    }
}
