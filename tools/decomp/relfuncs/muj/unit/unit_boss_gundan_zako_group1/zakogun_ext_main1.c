// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_stage_object.h
// include: system.h
// include: dolphin/mtx.h
// include: driver/dispdrv.h
// decl: typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; Vec ofs; Vec rot; } ZakoGun;
// decl: typedef struct ZakoGunWork { s32 flag; s32 targetId; s32 state; s32 timer; Vec pos; u8 field_0x1c[0x34 - 0x1c]; f32 radius; f32 angle; f32 speed; u8 field_0x40[0x48 - 0x40]; Vec start; Vec end; s32 timer2; s32 steps; s32 count; s32 sfx; ZakoGun* zako; } ZakoGunWork;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: extern ZakoGun* zakogun;
// decl: extern ZakoGunWork* work_20_bss_6C;
// decl: ExtPose* extGetPosePtr(void);
// decl: void extLoadRenderMode(void);
// decl: void extLoadVertex(void);
// decl: void extLoadTexture(void);
// decl: void extLoadTev(void);
// decl: void extDraw(void);
// decl: void extLoadTextureExit(void);
// decl: void zakogun_ext_main1(void);
// decl: void zakogun_ext_main2(void);
// decl: void zakogun_ext_main3(void);
// decl: void zakogun_ext_disp(CameraId camera, void* param);
// include: mario/mariost.h
// decl: s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* name, s32 vol, s32 pan, Vec* pos);
// decl: void btl_camera_set_mode(s32 a, s32 b);
// proto: void zakogun_ext_main1(void);
void zakogun_ext_main1(void) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = zakogun_get_ptr();
    ExtPose* pose = extGetPosePtr();
    ZakoGun* zako;
    s32 i;
    s32 n;
    s32 j;
    f32 x, y, z;
    f32 d;
    Mtx m;

    for (i = 0; i < 6; i++, pose++) {
        zako = &zakogun[i];
        pose->frame = zako->poseBase + zako->poseCount / zako->poseDiv;
        zako->poseCount++;
        if (zako->poseCount >= zako->poseNum * zako->poseDiv) {
            zako->poseCount = 0;
        }
        if (i == 1 && zako->state >= 35 && zako->state < 80) {
            unit->mPosition.x = zako->pos.x;
        }
        switch (zako->state) {
            case 0:
                zako->state = 5;
                zako->timer = 0;
                zako->rot.x = zako->rot.y = zako->rot.z = 0.0f;
                zakogun_set_pose(zako, 0, 20, 2);
                break;
            case 5:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->timer = 0;
                    zako->state = 10;
                }
                break;
            case 10:
                zako->pos.x = zako->start.x = 300.0f + irand(100);
                zako->pos.y = zako->start.y = 0.0f;
                zako->pos.z = zako->start.z = irand(100) - 50.0f;
                zako->state = 12;
                zako->rot.y = 0.0f;
            case 12:
                x = unit->mHomePosition.x;
                y = unit->mHomePosition.y;
                z = unit->mHomePosition.z;
                switch (i) {
                    case 0:
                        zako->target.x = x - 10.0f;
                        zako->target.y = y;
                        zako->target.z = z - 10.0f;
                        break;
                    case 1:
                        zako->target.x = x;
                        zako->target.y = y;
                        zako->target.z = z;
                        break;
                    case 2:
                        zako->target.x = x + 10.0f;
                        zako->target.y = y;
                        zako->target.z = z + 10.0f;
                        break;
                    case 3:
                        zako->target.x = x + 45.0f;
                        zako->target.y = y;
                        zako->target.z = z - 5.0f;
                        break;
                    case 4:
                        zako->target.x = x + 55.0f;
                        zako->target.y = y;
                        zako->target.z = z + 5.0f;
                        break;
                    case 5:
                        zako->target.x = x + 75.0f;
                        zako->target.y = y;
                        zako->target.z = z;
                        break;
                }
                zako->state = 15;
                zako->timer = zako->timerMax = irand(40) + 40;
                zakogun_set_pose(zako, 0x16, 10, 1);
                break;
            case 15:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.y = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.y, zako->target.y);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                if (i == 5) {
                    if (zako->timer % 12 == 0) {
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1L", 0x7f, 0, &zako->pos);
                    }
                    if (zako->timer % 12 == 6) {
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1R", 0x7f, 0, &zako->pos);
                    }
                }
                zako->timer--;
                if (zako->timer < 0) {
                    zako->timer = -1;
                    zako->rot.y = 0.0f;
                    if (i >= 3 && i <= 5) {
                        switch (i) {
                            case 3:
                            case 4:
                                for (j = 0, n = 0; j < 3; j++) {
                                    if (zakogun[j].state == 20) {
                                        n++;
                                    }
                                }
                                if (n == 3) {
                                    zako->state = 16;
                                }
                                break;
                            case 5:
                                for (j = 3, n = 0; j < 5; j++) {
                                    if (zakogun[j].state == 20) {
                                        n++;
                                    }
                                }
                                if (n == 2) {
                                    zako->state = 16;
                                }
                                break;
                        }
                    } else {
                        zako->state = 20;
                        zako->timer = 0;
                        zakogun_set_pose(zako, 0x15, 1, 1);
                    }
                }
                break;
            case 16:
                x = unit->mHomePosition.x;
                y = unit->mHomePosition.y;
                z = unit->mHomePosition.z;
                zako->start.x = zako->pos.x;
                zako->start.y = zako->pos.y;
                zako->start.z = zako->pos.z;
                switch (i) {
                    case 3:
                        zako->target.x = x - 5.0f;
                        zako->target.y = y + 10.0f;
                        zako->target.z = z - 5.0f;
                        break;
                    case 4:
                        zako->target.x = x + 5.0f;
                        zako->target.y = y + 10.0f;
                        zako->target.z = z + 5.0f;
                        break;
                    case 5:
                        zako->target.x = x;
                        zako->target.y = y + 20.0f;
                        zako->target.z = z;
                        break;
                }
                zako->state = 17;
                zako->timer = zako->timerMax = 20;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -200.0f) / 40.0f;
                zakogun_set_pose(zako, 0x22, 1, 1);
                break;
            case 17:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 20;
                    zako->timer = 0;
                    zako->pos.y = zako->target.y;
                    zakogun_set_pose(zako, 0x15, 1, 1);
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_WAKE1", 0x7f, 0, &zako->pos);
                }
                break;
            case 20:
                if (unit == NULL) {
                    break;
                }
                BtlUnit_GetPos(unit, &x, &y, &z);
                zako->timer++;
                zako->timer = zakogun[0].timer;
                if (zako->timer >= 30) {
                    zako->timer -= 30;
                }
                switch (i) {
                    case 0:
                        zako->pos.x = zako->home.x = x - 10.0f;
                        zako->pos.y = zako->home.y = y;
                        zako->pos.z = zako->home.z = z - 10.0f;
                        break;
                    case 1:
                        zako->pos.x = zako->home.x = x;
                        zako->pos.y = zako->home.y = y;
                        zako->pos.z = zako->home.z = z;
                        break;
                    case 2:
                        zako->pos.x = zako->home.x = x + 10.0f;
                        zako->pos.y = zako->home.y = y;
                        zako->pos.z = zako->home.z = z + 10.0f;
                        break;
                    case 3:
                        zako->pos.x = zako->home.x = x - 5.0f;
                        if (zako->timer < 10) {
                            zako->pos.y = zako->home.y = y + 10.0f - 0.1f * zako->timer;
                        } else if (zako->timer < 20) {
                            zako->pos.y = zako->home.y = y + 10.0f - 1.0f;
                        } else {
                            zako->pos.y = zako->home.y = y + 10.0f - 1.0f + 0.1f * (zako->timer - 20.0f);
                        }
                        zako->pos.z = zako->home.z = z - 5.0f;
                        break;
                    case 4:
                        zako->pos.x = zako->home.x = x + 5.0f;
                        if (zako->timer < 10) {
                            zako->pos.y = zako->home.y = y + 10.0f - 0.1f * zako->timer;
                        } else if (zako->timer < 20) {
                            zako->pos.y = zako->home.y = y + 10.0f - 1.0f;
                        } else {
                            zako->pos.y = zako->home.y = y + 10.0f - 1.0f + 0.1f * (zako->timer - 20.0f);
                        }
                        zako->pos.z = zako->home.z = z + 5.0f;
                        break;
                    case 5:
                        zako->pos.x = zako->home.x = x;
                        if (zako->timer < 15) {
                            zako->pos.y = zako->home.y = y + 20.0f - 0.15f * zako->timer;
                        } else {
                            zako->pos.y = zako->home.y = y + 20.0f - 2.25f + 0.15f * (zako->timer - 15.0f);
                        }
                        zako->pos.z = zako->home.z = z;
                        break;
                }
                break;
            case 30:
                if (i >= 0 && i <= 2) {
                    zakogun_set_pose(zako, 0x14, 1, 1);
                }
                zako->state = 35;
                zako->timer = 5;
            case 35:
                if (i >= 3 && i <= 5) {
                    zako->pos.y += 3.0f;
                }
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 36;
                    zako->timer = 30;
                }
                break;
            case 36:
                zako->timer--;
                if (i >= 0 && i <= 2) {
                    if (zako->timer == 15) {
                        zakogun_set_pose(zako, 0x16, 10, 1);
                    }
                    if (zako->timer <= 15) {
                        if (zako->timer % 12 == 0) {
                            BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1L", 0x7f, 0, &zako->pos);
                        }
                        if (zako->timer % 12 == 6) {
                            BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1R", 0x7f, 0, &zako->pos);
                        }
                    }
                }
                if (zako->timer <= 0) {
                    zako->state = 40;
                }
                break;
            case 40:
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work_20_bss_6C->targetId), &x, &y, &z);
                x += 100.0f;
                zako->start.x = zako->pos.x;
                zako->start.y = zako->pos.y;
                zako->start.z = zako->pos.z;
                zako->target.x = x;
                zako->target.y = zako->pos.y;
                zako->target.z = zako->pos.z;
                zako->state = 45;
                zako->timer = zako->timerMax = 40;
            case 45:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                if (zako->timer % 12 == 0) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1L", 0x7f, 0, &zako->pos);
                }
                if (zako->timer % 12 == 6) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1R", 0x7f, 0, &zako->pos);
                }
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 50;
                    zako->timer = 0;
                }
                break;
            case 50: {
                f32 ofs[6] = {-20.0f, -10.0f, 0.0f, 10.0f, 20.0f, 30.0f};

                BtlUnit_GetPos(BattleGetUnitPtr(wp, work_20_bss_6C->targetId), &x, &y, &z);
                zako->start.x = zako->pos.x;
                zako->start.y = zako->pos.y;
                zako->start.z = zako->pos.z;
                zako->target.x = x - ofs[i];
                zako->target.y = 0.0f;
                zako->target.z = zako->start.z;
                zako->state = 55;
                zako->timer = zako->timerMax = 40;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -320.0f) / 80.0f;
                zakogun_set_pose(zako, 0x20, 1, 1);
                if (i == 0) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_ATTACK1", 0x7f, 0, &zako->pos);
                }
                break;
            }
            case 55:
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work_20_bss_6C->targetId), &x, &y, &z);
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.2f;
                zako->timer--;
                if (zako->timer <= 10) {
                    zako->state = 58;
                    if (i == 0) {
                        unit->work[0]++;
                        zakogun_set_pose(zako, 0, 20, 2);
                    }
                }
                break;
            case 58:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.2f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 60;
                    zako->timer = 30;
                    zako->pos.y = zako->target.y;
                    zakogun_set_pose(zako, 0x15, 1, 1);
                    if (i == 0) {
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_ATTACK1_2", 0x7f, 0, &zako->pos);
                    }
                }
                break;
            case 60:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 62;
                    zakogun_set_pose(zako, 0x16, 10, 1);
                }
                break;
            case 62:
                zako->state = 12;
                zako->rot.y = 180.0f;
                zako->start = zako->pos;
                unit->mPosition = unit->mHomePosition;
                btl_camera_set_mode(0, 0);
                break;
            case 80:
                zako->rot.z = 0.0f;
                zako->state = 81;
                zako->timer = 6;
            case 81:
                if (i >= 0 && i <= 2) {
                    zako->rot.z += 15.0f;
                    if (zako->rot.z >= 45.0f) {
                        zako->rot.z = 45.0f;
                    }
                }
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 82;
                    zako->timer = 10;
                    zako->vel.y = 0.0f;
                    if (i >= 0 && i <= 2) {
                        zako->rot.z = 45.0f;
                    }
                }
                break;
            case 82:
                if (i >= 3 && i <= 4) {
                    zako->rot.z += 15.0f;
                    if (zako->rot.z >= 45.0f) {
                        zako->rot.z = 45.0f;
                    }
                    zako->pos.y += zako->vel.y;
                    zako->vel.y += -0.5f;
                    if (zako->pos.y < 0.0f) {
                        zako->pos.y = 0.0f;
                    }
                }
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 83;
                    zako->timer = 20;
                    zako->vel.y = 0.0f;
                    if (i >= 3 && i <= 4) {
                        zako->rot.z = 45.0f;
                        zako->pos.y = 0.0f;
                    }
                }
                break;
            case 83:
                if (i == 5) {
                    zako->rot.z += 15.0f;
                    if (zako->rot.z >= 45.0f) {
                        zako->rot.z = 45.0f;
                    }
                    zako->pos.y += zako->vel.y;
                    zako->vel.y += -0.5f;
                    if (zako->pos.y < 0.0f) {
                        zako->pos.y = 0.0f;
                    }
                }
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->rot.y = 0.0f;
                    zako->state = 84;
                    zako->timer = 48;
                    if (i == 5) {
                        zako->rot.z = 45.0f;
                        zako->pos.y = 0.0f;
                    }
                }
                break;
            case 84:
                if (zako->timer <= 48) {
                    zako->rot.y -= 15.0f;
                }
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->rot.y = 0.0f;
                    zako->state = 85;
                }
                break;
            case 85:
                zako->rot.x += 3.0f;
                if (zako->rot.x >= 90.0f) {
                    zako->state = -1;
                    zako->pos = (Vec){0.0f, -1000.0f, 0.0f};
                }
                break;
            case 90:
                zako->pos.x += 5.0f;
                if (i == 0) {
                    if (gp->retraceCount % 12 == 0) {
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1L", 0x7f, 0, &zako->pos);
                    }
                    if (gp->retraceCount % 12 == 6) {
                        BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_3RD_MOVE1R", 0x7f, 0, &zako->pos);
                    }
                }
                if (zako->pos.x >= 300.0f) {
                    zako->state = -1;
                }
                break;
            case 95:
            case 96:
                d = 0.0f;
                BtlUnit_GetPos(unit, &x, &y, &z);
                if (zako->state == 96) {
                    zako->timer++;
                    zako->timer = zakogun[0].timer;
                    if ((zako->timer & 3) == 0 || (zako->timer & 3) == 1) {
                        d = 1.0f;
                    } else {
                        d = -1.0f;
                    }
                }
                switch (i) {
                    case 0:
                        zako->pos.x = zako->home.x = x - 10.0f + d;
                        zako->pos.y = zako->home.y = y;
                        zako->pos.z = zako->home.z = z - 10.0f;
                        break;
                    case 1:
                        zako->pos.x = zako->home.x = x + d;
                        zako->pos.y = zako->home.y = y;
                        zako->pos.z = zako->home.z = z;
                        break;
                    case 2:
                        zako->pos.x = zako->home.x = x + 10.0f + d;
                        zako->pos.y = zako->home.y = y;
                        zako->pos.z = zako->home.z = z + 10.0f;
                        break;
                    case 3:
                        zako->pos.x = zako->home.x = x - 5.0f + d;
                        zako->pos.y = zako->home.y = y + 20.0f;
                        zako->pos.z = zako->home.z = z - 5.0f;
                        break;
                    case 4:
                        zako->pos.x = zako->home.x = x + 5.0f + d;
                        zako->pos.y = zako->home.y = y + 20.0f;
                        zako->pos.z = zako->home.z = z + 5.0f;
                        break;
                    case 5:
                        zako->pos.x = zako->home.x = x + d;
                        zako->pos.y = zako->home.y = y + 40.0f;
                        zako->pos.z = zako->home.z = z;
                        break;
                }
                break;
        }
        PSMTXIdentity(pose->mtx);
        PSMTXRotRad(m, 'x', 0.017453292f * zako->rot.x);
        PSMTXConcat(pose->mtx, m, pose->mtx);
        PSMTXRotRad(m, 'y', 0.017453292f * zako->rot.y);
        PSMTXConcat(pose->mtx, m, pose->mtx);
        PSMTXRotRad(m, 'z', 0.017453292f * zako->rot.z);
        PSMTXConcat(pose->mtx, m, pose->mtx);
        pose->mtx[0][3] = zako->pos.x;
        pose->mtx[1][3] = zako->pos.y;
        pose->mtx[2][3] = zako->pos.z + i * 0.25f;
    }
}
