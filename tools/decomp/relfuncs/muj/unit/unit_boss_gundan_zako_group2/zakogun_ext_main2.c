// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_stage_object.h
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: s32 irand(s32 scalar);
// decl: typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; u8 field_0x58[0x64 - 0x58]; Vec rot; } ZakoGun;
// decl: typedef struct ZakoGunWork { s32 flag; s32 targetId; u8 field_0x8[0x48 - 0x8]; Vec start; Vec end; s32 timer; s32 steps; s32 count; s32 sfx; } ZakoGunWork;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: extern ZakoGun* zakogun;
// decl: extern ZakoGunWork* work_20_bss_6C;
// include: dolphin/mtx.h
// decl: ExtPose* extGetPosePtr(void);
// decl: BattleUnit* zakogun_get_ptr(void);
// decl: void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div);
// decl: s32 psndSFXOn(const char* name);
// decl: int rand(void);
// decl: void btl_camera_set_mode(s32 a, s32 b);
// proto: void zakogun_ext_main2(void);
void zakogun_ext_main2(void) {
    BattleWork* wp = _battleWorkPointer;
    BattleUnit* unit = zakogun_get_ptr();
    ExtPose* pose = extGetPosePtr();
    BattleStageObject* body;
    s32 i;
    ZakoGun* zako;
    f32 x, y, z;
    Mtx m;
    const char* se1;
    const char* se2;
    const char* se3;

    if (unit == NULL) {
        return;
    }
    body = BattleSearchObjectPtr("if_body");
    se1 = (0, "SFX_BOSS_TEAM_3RD_ATTACK2");
    se2 = (0, "SFX_BOSS_TEAM_3RD_MOVE_CAILING2");
    se3 = "SFX_BOSS_TEAM_3RD_ATTACK2";
    for (i = 0; i < 25; i++, pose++) {
        zako = &zakogun[i];
        pose->frame = zako->poseBase + zako->poseCount / zako->poseDiv;
        zako->poseCount++;
        if (zako->poseCount >= zako->poseNum * zako->poseDiv) {
            zako->poseCount = 0;
        }
        switch (zako->state) {
            case 0:
                zako->state = 5;
                zako->rot.x = zako->rot.y = zako->rot.z = 0.0f;
                zakogun_set_pose(zako, 0x25, 4, 6);
                break;
            case 5:
                zako->pos.x = zako->home.x = body->mPosition.x - 250.0f + i * 20.0f;
                zako->pos.y = zako->home.y = body->mPosition.y - 35.0f;
                zako->pos.z = zako->home.z = 0.0f;
                zako->state = 10;
                break;
            case 10:
                zako->pos.x = zako->home.x = body->mPosition.x + unit->mPosition.x - 250.0f + i * 20.0f;
                zako->pos.y = zako->home.y = body->mPosition.y - 35.0f;
                if (zako->pos.y < unit->mPosition.y) {
                    zako->pos.y = unit->mPosition.y;
                }
                zako->pos.z = zako->home.z = -10.0f;
                break;
            case 20:
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work_20_bss_6C->targetId), &x, &y, &z);
                zako->start = zako->pos;
                if (zako->pos.x >= x) {
                    zako->target.x = zako->pos.x - 30.0f;
                    zako->rot.y = 0.0f;
                } else {
                    zako->target.x = 15.0f + zako->pos.x;
                    zako->rot.y = 180.0f;
                }
                zako->target.y = zako->start.y - 2.0f;
                zako->state = 25;
                zako->timer = zako->timerMax = 8;
            case 25:
                zako->pos.x = intplGetValue(zako->start.x, zako->target.x, 4, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y = intplGetValue(zako->start.y, zako->target.y, 4, (zako->timerMax - zako->timer) * 2, zako->timerMax);
                zako->timer--;
                if (zako->timer < 0) {
                    BtlUnit_GetPos(BattleGetUnitPtr(wp, work_20_bss_6C->targetId), &x, &y, &z);
                    if (__fabs(zako->pos.x - x) <= 20.0) {
                        zako->state = 30;
                    } else {
                        zako->state = 20;
                    }
                }
                break;
            case 30:
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work_20_bss_6C->targetId), &x, &y, &z);
                zako->vel.x = rand() / 32767.0f - 0.5f;
                zako->vel.y = 0.0f;
                zako->vel.z = 1.5f;
                zako->target.y = y + work_20_bss_6C->count * 2.0f;
                zako->state = 35;
                zakogun_set_pose(zako, 0x2C, 1, 1);
                psndSFXOn(se1);
            case 35:
                zako->pos.x += zako->vel.x;
                zako->pos.y += zako->vel.y;
                zako->pos.z += zako->vel.z;
                zako->vel.y += -0.5f;
                if (zako->pos.y < zako->target.y) {
                    zako->pos.y = zako->target.y;
                    zako->state = 40;
                    work_20_bss_6C->count++;
                    if (work_20_bss_6C->count == 25) {
                        unit->work[0] = 1;
                    }
                }
                break;
            case 40:
                if (work_20_bss_6C->count == 25) {
                    zako->state = 45;
                    zako->timer = irand(60);
                }
                break;
            case 45:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->vel.x = -5.0f;
                    zako->vel.y = 3.0f;
                    zako->state = 48;
                    zakogun_set_pose(zako, 0x22, 1, 1);
                    zako->rot.y = 0.0f;
                }
                break;
            case 48:
                zako->pos.x += zako->vel.x;
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                if (zako->pos.y < 0.0f) {
                    zako->pos.y = 0.0f;
                    zakogun_set_pose(zako, 0x16, 10, 1);
                    zako->state = 49;
                }
                break;
            case 49:
                zako->pos.x += zako->vel.x;
                if (zako->pos.x <= -300.0f) {
                    zako->state = 50;
                    zako->pos.x = 300.0f;
                    zako->pos.y = zako->home.y;
                    zako->pos.z = zako->home.z;
                    zakogun_set_pose(zako, 0x25, 4, 6);
                    if (i == 0) {
                        psndSFXOn(se2);
                    }
                }
                break;
            case 50:
                BtlUnit_GetPos(BattleGetUnitPtr(wp, work_20_bss_6C->targetId), &x, &y, &z);
                zako->rot.y = 0.0f;
                zako->start = zako->pos;
                zako->target.x = zako->pos.x - 30.0f;
                if (zako->target.x < zako->home.x) {
                    zako->target.x = zako->home.x;
                }
                zako->target.y = zako->start.y - 2.0f;
                zako->state = 55;
                zako->timer = zako->timerMax = 8;
                btl_camera_set_mode(0, 0);
            case 55:
                zako->pos.x = intplGetValue(zako->start.x, zako->target.x, 4, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y = intplGetValue(zako->start.y, zako->target.y, 4, (zako->timerMax - zako->timer) * 2, zako->timerMax);
                zako->timer--;
                if (zako->timer < 0) {
                    if (zako->pos.x <= zako->home.x) {
                        zako->pos.x = zako->home.x;
                        zako->state = 10;
                    } else {
                        zako->state = 50;
                    }
                }
                break;
            case 60:
                zakogun_set_pose(zako, 0x29, 3, 6);
                zako->state = 65;
                zako->timer = 120;
            case 65:
                zako->pos.x = body->mPosition.x - 250.0f + i * 20.0f;
                zako->pos.y = body->mPosition.y - 35.0f;
                zako->pos.z = 0.0f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 10;
                    zakogun_set_pose(zako, 0x25, 4, 6);
                }
                break;
            case 80:
                zako->timer = irand(10);
                zako->state = 82;
            case 82:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 83;
                    zako->vel.y = 0.0f;
                    psndSFXOn(se3);
                }
                break;
            case 83:
                zako->vel.y += -0.5f;
                zako->pos.y += zako->vel.y;
                if (zako->pos.y <= 0.0f) {
                    zako->pos.y = 0.0f;
                    zako->state = 84;
                    zakogun_set_pose(zako, 0x21, 3, 3);
                }
                break;
            case 84:
                zako->start = zako->pos;
                zako->target.x = zako->start.x + irand(100) - 50.0f;
                zako->target.y = 0.0f;
                zako->target.z = zako->start.z + irand(20) - 10.0f;
                zako->state = 85;
                zako->timer = zako->timerMax = 20;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -200.0f) / 40.0f;
            case 85:
                zako->pos.x = intplGetValue(zako->start.x, zako->target.x, 0, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.z = intplGetValue(zako->start.z, zako->target.z, 0, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 86;
                }
                break;
            case 86:
                zako->start = zako->pos;
                zako->target.x = zako->start.x + irand(50) - 25.0f;
                zako->target.y = 0.0f;
                zako->target.z = zako->start.z + irand(10) - 5.0f;
                zako->state = 87;
                zako->timer = zako->timerMax = 10;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -50.0f) / 20.0f;
            case 87:
                zako->pos.x = intplGetValue(zako->start.x, zako->target.x, 0, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.z = intplGetValue(zako->start.z, zako->target.z, 0, zako->timerMax - zako->timer, zako->timerMax);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 88;
                    zako->rot.y = 0.0f;
                    zako->timer = 48;
                }
                break;
            case 88:
                zako->rot.y -= 15.0f;
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->rot.y = 0.0f;
                    zako->state = 89;
                }
                break;
            case 89:
                zako->rot.x += 3.0f;
                if (zako->rot.x >= 90.0f) {
                    zako->state = -1;
                    zako->pos = (Vec){0.0f, -1000.0f, 0.0f};
                }
                break;
            case 90:
                zako->pos.x = 0.0f;
                zako->pos.y = -1000.0f;
                zako->pos.z = 0.0f;
                zako->state = -1;
                break;
        }
        PSMTXIdentity(pose->mtx);
        PSMTXRotRad(m, 'x', zako->rot.x * 0.017453292f);
        PSMTXConcat(pose->mtx, m, pose->mtx);
        PSMTXRotRad(m, 'y', zako->rot.y * 0.017453292f);
        PSMTXConcat(pose->mtx, m, pose->mtx);
        pose->mtx[0][3] = zako->pos.x;
        pose->mtx[1][3] = zako->pos.y;
        pose->mtx[2][3] = zako->pos.z + i * 0.25f;
    }
}
