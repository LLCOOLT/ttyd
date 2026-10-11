// include: battle/battle.h
// include: battle/battle_unit.h
// include: driver/dispdrv.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct AtmTeresa { u8 state; u8 flag; s32 anim; s32 wait; s32 timer; Vec vel; Vec start; Vec target; u8 mode; } AtmTeresa;
// decl: AtmTeresa* teresa;
// decl: s32 teresa_count;
// decl: #define ATMIC_TERESA_SCALE (*(f32*)atmic_teresa_scale)
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* name, u32 flags, s32 arg3, Vec* pos);
// decl: s32 irand(s32 scalar);
// decl: f32 intplGetValue(s32 mode, f32 start, f32 end, s32 cur, s32 steps);
// decl: s32 irand(s32 scalar);
// decl: f32 intplGetValue(s32 mode, f32 start, f32 end, s32 cur, s32 steps);
// decl: double cos(double x);
// decl: double sin(double x);
// decl: void teresa_ext_disp(CameraId camera, void* param);
// proto: void teresa_ext_main(void);
void teresa_ext_main(void) {
    s32 i;
    s32 j;
    ExtPose* pose = extGetPosePtr();
    AtmTeresa* t;
    BattleUnit* unit = BattleGetUnitPtr(_battleWorkPointer, atmic_teresa_id[0]);
    BattleUnit* target = BattleGetUnitPtr(_battleWorkPointer, target_unit_id[0]);
    s32 n;
    f32 angle;
    s32 waits[8] = {0, 2, 5, 7, 10, 12, 15, 17};
    f32 ofs[30][2] = {
        {-30.0f, 8.0f}, {-28.0f, 10.0f}, {-26.0f, 6.0f}, {-24.0f, 30.0f}, {-22.0f, 16.0f},
        {-20.0f, 50.0f}, {-18.0f, 14.0f}, {-16.0f, 18.0f}, {-14.0f, 60.0f}, {-12.0f, 34.0f},
        {-10.0f, 66.0f}, {-8.0f, 8.0f}, {-6.0f, 28.0f}, {-4.0f, 40.0f}, {-2.0f, 46.0f},
        {0.0f, 20.0f}, {2.0f, 26.0f}, {4.0f, 52.0f}, {6.0f, 74.0f}, {8.0f, 68.0f},
        {10.0f, 0.0f}, {12.0f, 28.0f}, {14.0f, 44.0f}, {16.0f, 72.0f}, {18.0f, 42.0f},
        {20.0f, 76.0f}, {22.0f, 56.0f}, {24.0f, 32.0f}, {26.0f, 4.0f}, {28.0f, 2.0f},
    };
    u8 modes[7] = {0, 1, 2, 3, 4, 5, 6};
    f32 x, y, z;
    f32 hx, hy, hz;
    f32 sx, sy, sz;

    if (++teresa_count >= 360) {
        teresa_count -= 360;
    }
    if (unit != NULL) {
        BtlUnit_GetPos(unit, &x, &y, &z);
        y += 40.0f;
        BtlUnit_GetScale(unit, &sx, &sy, &sz);
        if (sx > ATMIC_TERESA_SCALE) {
            sx -= 0.005f;
            if (sx <= ATMIC_TERESA_SCALE) {
                sx = ATMIC_TERESA_SCALE;
            }
            BtlUnit_SetScale(unit, sx, sx, sz);
        }
        if (sx < ATMIC_TERESA_SCALE) {
            sx += 0.005f;
            if (sx >= ATMIC_TERESA_SCALE) {
                sx = ATMIC_TERESA_SCALE;
            }
            BtlUnit_SetScale(unit, sx, sx, sz);
        }
    }
    if (target != NULL) {
        BattleUnitPart* part = BtlUnit_GetPartsPtr(target, target_parts_id[0]);
        BtlUnit_GetHitPos(target, part, &hx, &hy, &hz);
    }

    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        t = &teresa[i];
        switch (t->flag) {
            case 1:
                t->anim++;
                if (t->anim <= 30) {
                    pose->frame = 8;
                } else if (t->anim < 44) {
                    pose->frame = (t->anim - 30) / 2 + 9;
                } else {
                    pose->frame = 15;
                }
                break;
            default:
                t->anim++;
                if (t->anim >= 24) {
                    t->anim -= 24;
                }
                pose->frame = t->anim / 3;
                break;
        }
        if (t->wait >= 1) {
            t->wait--;
            continue;
        }
        pose->mtx[0][3] += t->vel.x;
        pose->mtx[1][3] += t->vel.y;
        pose->mtx[2][3] += t->vel.z;
        if (pose->mtx[1][3] < 0.0f) {
            pose->mtx[1][3] = 0.0f;
        }

        switch (t->state) {
            case 0:
                pose->mtx[0][3] = 0.0f;
                pose->mtx[1][3] = -1000.0f;
                pose->mtx[2][3] = 0.0f;
                pose->rot = 90.0f;
                pose->mtx[1][1] = 1.0f;
                pose->mtx[0][0] = 1.0f;
                break;
            case 1:
                pose->flags &= ~2;
                pose->mtx[0][3] = x;
                pose->mtx[1][3] = y;
                pose->mtx[2][3] = z - 5.0f;
                pose->mtx[0][0] = 0.0f;
                pose->mtx[1][1] = 0.0f;
                angle = 0.785398f * i;
                t->vel.x = 2.0f * (f32)cos(angle);
                t->vel.y = 2.0f * (f32)sin(angle);
                t->vel.z = 0.0f;
                t->wait = waits[i];
                t->timer = 50;
                t->state = 5;
                break;
            case 5:
                t->timer--;
                if (t->timer == 25) {
                    ATMIC_TERESA_SCALE -= 0.05f;
                    if (i % 2 == 0) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_DIVIDE1", 0xF1194D80, 0, &pos);
                    }
                }
                pose->mtx[0][0] += 0.02f;
                pose->mtx[1][1] += 0.02f;
                if (t->timer <= 0) {
                    pose->flags |= 2;
                    t->state = 10;
                    t->timer = 150;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                    if (i % 2 == 0) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_S_MOVE1", 0xF1194D80, 0, &pos);
                    }
                }
                break;
            case 10:
                angle = 6.283184f * (0.125f * i + 2.0f * teresa_count / 360.0f);
                t->target.x = 90.0f * (f32)cos(angle) - 100.0f;
                t->target.y = 10.0f;
                t->target.z = 90.0f * (f32)sin(angle);
                if (pose->mtx[0][3] >= -100.0f) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 20.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 20.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 20.0f;
                if (t->timer <= 0) {
                    t->state = 15;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                }
                t->timer--;
                break;
            case 15:
                angle = 6.283184f * (0.125f * i + 2.0f * teresa_count / 360.0f);
                t->target.x = 90.0f * (f32)cos(angle) - 100.0f;
                t->target.y = 10.0f;
                t->target.z = 90.0f * (f32)sin(angle);
                if (pose->mtx[0][3] >= -100.0f) {
                    pose->rot = 90.0f;
                } else {
                    pose->rot = 270.0f;
                }
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 20.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 20.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 20.0f;
                n = 0;
                for (j = 0; j < 8; j++) {
                    if (teresa[j].state != 15) {
                        break;
                    }
                    n++;
                }
                if (n == 8) {
                    for (j = 0; j < 8; j++) {
                        AtmTeresa* p = &teresa[j];
                        p->state = 20;
                        p->flag = 1;
                        p->anim = 0;
                        p->vel.x = 0.0f;
                        p->vel.y = 0.0f;
                        p->vel.z = 0.0f;
                    }
                }
                break;
            case 20:
                if (t->anim >= 180) {
                    t->state = 23;
                    t->flag = 0;
                    t->anim = 0;
                    t->timer = 60;
                    t->wait = waits[i];
                    pose->rot = 90.0f;
                }
                break;
            case 23:
                t->target.x = (x - 35.0f) + irand(90);
                t->target.y = (y - 35.0f) + irand(90);
                t->target.z = (z - 30.0f) - 0.05f * i;
                t->timer = 60;
                t->state = 25;
                if (i % 2 == 0) {
                    Vec pos = {0.0f, 0.0f, 0.0f};
                    pos.x = pose->mtx[0][3];
                    pos.y = pose->mtx[1][3];
                    pos.z = pose->mtx[2][3];
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_S_MOVE1", 0xF1194D80, 0, &pos);
                }
                break;
            case 25:
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 20.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 20.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 20.0f;
                if (t->timer <= 0) {
                    t->state = 30;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                    pose->flags &= ~2;
                }
                t->timer--;
                break;
            case 31:
                pose->mtx[0][0] -= 0.0125f;
                pose->mtx[1][1] = pose->mtx[0][0];
                if (pose->mtx[0][0] <= 0.0f) {
                    t->state = 0;
                }
                break;
            case 51:
            case 52:
                pose->flags &= ~2;
                pose->mtx[0][3] = x - 15.0f;
                pose->mtx[1][3] = y - 5.0f;
                pose->mtx[2][3] = 5.0f + z;
                pose->mtx[1][1] = 0.0f;
                pose->mtx[0][0] = 0.0f;
                t->vel.x = 0.0f;
                t->vel.y = 0.0f;
                t->vel.z = 0.0f;
                t->start.x = pose->mtx[0][3];
                t->start.y = pose->mtx[1][3];
                t->start.z = pose->mtx[2][3];
                if (t->state == 51) {
                    t->target.x = (hx + ofs[i][0]) - 200.0f;
                } else {
                    t->target.x = (hx + ofs[i][0]) - 200.0f;
                }
                if (t->state == 51) {
                    t->target.y = (hy + ofs[i][1]) - 50.0f;
                } else {
                    t->target.y = (hy + ofs[i][1]) - 50.0f;
                }
                t->target.z = (hz - 10.0f) - 0.05f * i;
                t->wait = i * 3;
                t->timer = 0;
                t->state = 53;
                t->mode = modes[irand(7)];
                break;
            case 53:
                ATMIC_TERESA_SCALE -= 0.015f;
                t->state = 55;
                break;
            case 55:
                pose->mtx[0][0] += 0.04f;
                if (pose->mtx[0][0] >= 1.0f) {
                    pose->mtx[0][0] = 1.0f;
                }
                pose->mtx[1][1] = pose->mtx[0][0];
                pose->mtx[0][3] = intplGetValue(t->mode, t->start.x, t->target.x, t->timer, 30);
                pose->mtx[1][3] = intplGetValue(t->mode, t->start.y, t->target.y, t->timer, 30);
                pose->mtx[2][3] = intplGetValue(t->mode, t->start.z, t->target.z, t->timer, 30);
                if (t->timer >= 30) {
                    t->state = 60;
                }
                t->timer++;
                break;
            case 63:
                t->target.x = (x - 35.0f) + irand(90);
                t->target.y = (y - 35.0f) + irand(90);
                t->target.z = (z - 30.0f) - 0.05f * i;
                t->timer = 60;
                t->state = 65;
                if (i % 2 == 0) {
                    Vec pos = {0.0f, 0.0f, 0.0f};
                    pos.x = pose->mtx[0][3];
                    pos.y = pose->mtx[1][3];
                    pos.z = pose->mtx[2][3];
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_ATMTLSA_S_MOVE1", 0xF1194D80, 0, &pos);
                }
                break;
            case 65:
                t->vel.x = (t->target.x - pose->mtx[0][3]) / 15.0f;
                t->vel.y = (t->target.y - pose->mtx[1][3]) / 15.0f;
                t->vel.z = (t->target.z - pose->mtx[2][3]) / 15.0f;
                if (t->timer <= 0) {
                    t->state = 70;
                    t->vel.x = 0.0f;
                    t->vel.y = 0.0f;
                    t->vel.z = 0.0f;
                }
                t->timer--;
                break;
            case 71:
                pose->mtx[0][0] -= 0.0125f;
                pose->mtx[1][1] = pose->mtx[0][0];
                if (pose->mtx[0][0] <= 0.0f) {
                    t->state = 0;
                }
                break;
        }
    }
    dispEntry(4, 0.0f, 1, teresa_ext_disp, NULL);
}
