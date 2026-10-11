// include: battle/battle.h
// include: battle/battle_unit.h
// include: battle/battle_stage_object.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct ZakoGun { s8 field_0x0; s8 state; s32 timer; s32 timerMax; Vec pos; Vec home; s32 poseBase; s32 poseNum; s32 poseDiv; s32 poseCount; Vec start; Vec target; Vec vel; Vec ofs; Vec rot; } ZakoGun;
// decl: typedef struct ZakoGunWork { s32 flag; s32 targetId; s32 state; s32 timer; Vec pos; u8 field_0x1c[0x34 - 0x1c]; f32 radius; f32 angle; f32 speed; u8 field_0x40[0x48 - 0x40]; Vec start; Vec end; s32 timer2; s32 steps; s32 count; s32 sfx; } ZakoGunWork;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: extern ZakoGun* zakogun;
// decl: extern ZakoGunWork* work_20_bss_6C;
// decl: ExtPose* extGetPosePtr(void);
// decl: BattleUnit* zakogun_get_ptr(void);
// decl: s32 zakogun_get_kanbu_id(void);
// decl: void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div);
// decl: void zakogun_ext_init123_common(ExtPose* pose, s32 i);
// decl: void psndSFXOff(s32 id);
// decl: int rand(void);
// decl: double sqrt(double x);
// proto: void zakogun_ext_main3(void);
void zakogun_ext_main3(void) {
    s32 i;
    BattleUnit* unit = zakogun_get_ptr();
    ExtPose* pose = extGetPosePtr();
    ZakoGun* zako;
    f32 left;
    f32 top;
    f32 dx;
    f32 dy;
    Mtx m;
    Mtx m2;

    for (i = 0; i < 500; i++, pose++) {
        zako = &zakogun[i];
        pose->frame = zako->poseBase + zako->poseCount / zako->poseDiv;
        zako->poseCount++;
        if (zako->poseCount >= zako->poseNum * zako->poseDiv) {
            zako->poseCount = 0;
        }
        switch (zako->state) {
            case 0:
                zako->state = 3;
                zako->timer = 0;
                zako->rot.x = zako->rot.y = zako->rot.z = 0.0f;
                zakogun_set_pose(zako, 0, 20, 2);
                break;
            case 3:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 5;
                    zako->timer = 0;
                }
                break;
            case 5:
                zako->start.x = 300.0f;
                zako->start.y = 0.0f;
                zako->start.z = -75.0f + 150.0f * rand() / 32767.0f;
                zako->timerMax = zako->timer = irand(30) + 60;
                zako->state = 10;
                zakogun_set_pose(zako, 0x16, 10, 1);
            case 10:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->home.x);
                zako->pos.y = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.y, zako->home.y);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->home.z);
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 15;
                    zakogun_set_pose(zako, 0, 20, 2);
                }
                break;
            case 15:
                zako->pos.x = zako->home.x + (unit->mPosition.x - unit->mHomePosition.x);
                zako->pos.y = zako->home.y;
                if (zako->pos.y < unit->mPosition.y) {
                    zako->pos.y = unit->mPosition.y;
                }
                zako->pos.z = zako->home.z;
                break;
            case 20:
                if (i >= 0 && i < 484) {
                    left = work_20_bss_6C->pos.x - work_20_bss_6C->radius;
                    top = work_20_bss_6C->pos.y + work_20_bss_6C->radius;
                    zako->target.x = left + (i % 22) * (2.0f * work_20_bss_6C->radius / 22.0f);
                    zako->target.y = top - (i / 22) * (2.0f * work_20_bss_6C->radius / 22.0f);
                    zako->target.z = work_20_bss_6C->pos.z + rand() / 32767.0f - 0.5f;
                    dx = work_20_bss_6C->pos.x - zako->target.x;
                    dy = work_20_bss_6C->pos.y - zako->target.y;
                    if ((f32)sqrt(dx * dx + dy * dy) > work_20_bss_6C->radius) {
                        zako->target.x = work_20_bss_6C->pos.x;
                        zako->target.y = work_20_bss_6C->pos.y;
                        zako->target.z = work_20_bss_6C->pos.z - 10.0f;
                    }
                } else {
                    zako->target.x = work_20_bss_6C->pos.x;
                    zako->target.y = work_20_bss_6C->pos.y;
                    zako->target.z = work_20_bss_6C->pos.z - 10.0f;
                }
                zako->start.x = zako->pos.x;
                zako->start.y = zako->pos.y;
                zako->start.z = zako->pos.z;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -200.0f) / 40.0f;
                zako->state = 25;
                zako->timer = zako->target.y;
            case 25:
                zako->timer--;
                if (zako->timer <= 0) {
                    zako->state = 30;
                    zako->timerMax = zako->timer = 30;
                    zakogun_set_pose(zako, 0x22, 1, 1);
                }
                break;
            case 30:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 35;
                    zako->pos.y = zako->target.y;
                    zako->rot.z = 360.0f * rand() / 32767.0f;
                    zako->ofs.x = zako->pos.x - work_20_bss_6C->pos.x;
                    zako->ofs.y = zako->pos.y - work_20_bss_6C->pos.y;
                    zakogun_set_pose(zako, 0, 20, 2);
                    work_20_bss_6C->count++;
                }
                break;
            case 35:
                if (work_20_bss_6C->count == 500) {
                    zako->state = 40;
                }
                break;
            case 50:
                zako->start.x = zako->pos.x;
                zako->start.y = zako->pos.y;
                zako->start.z = zako->pos.z;
                zako->target.x = 200.0f * rand() / 32767.0f - 100.0f;
                zako->target.y = 0.0f;
                zako->target.z = 150.0f * rand() / 32767.0f - 75.0f;
                zako->vel.y = (2.0f * (zako->target.y - zako->start.y) - -200.0f) / 40.0f;
                zako->rot.z = 0.0f;
                zako->state = 55;
                zako->timer = zako->timerMax = 20;
                zakogun_set_pose(zako, 0x22, 1, 1);
            case 55:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->target.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->target.z);
                zako->pos.y += zako->vel.y;
                zako->vel.y += -0.5f;
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 60;
                    zako->pos.y = zako->target.y;
                    zakogun_set_pose(zako, 0, 20, 2);
                }
                break;
            case 60:
                zako->start.x = zako->pos.x;
                zako->start.z = zako->pos.z;
                zako->timerMax = zako->timer = irand(30) + 30;
                zako->state = 65;
                zakogun_set_pose(zako, 0x16, 10, 1);
            case 65:
                zako->pos.x = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.x, zako->home.x);
                zako->pos.z = intplGetValue(0, zako->timerMax - zako->timer, zako->timerMax, zako->start.z, zako->home.z);
                zako->timer--;
                if (zako->timer < 0) {
                    zako->state = 15;
                    zako->pos.y = zako->home.y;
                    zakogun_set_pose(zako, 0, 20, 2);
                }
                break;
            case 80:
                zako->rot.y = 0.0f;
                zako->timer = irand(5) + 48;
                zako->state = 82;
            case 82:
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
                    {
                        Vec hide = {0.0f, -1000.0f, 0.0f};
                        zako->pos = hide;
                    }
                }
                break;
            case 90:
                zako->rot.y = 180.0f;
                zako->pos.x += 5.0f;
                if (zako->pos.x >= 300.0f) {
                    zako->state = -1;
                    zako->rot.y = 0.0f;
                }
                break;
        }
        if (zako->state >= 35 && zako->state <= 40) {
            PSMTXIdentity(pose->mtx);
            PSMTXRotRad(m, 'z', 0.017453292f * zako->rot.z);
            PSMTXConcat(pose->mtx, m, pose->mtx);
            pose->mtx[0][3] = zako->ofs.x;
            pose->mtx[1][3] = zako->ofs.y;
            pose->mtx[2][3] = work_20_bss_6C->pos.z + 0.05f * i;
            PSMTXRotRad(m, 'z', 0.017453292f * work_20_bss_6C->angle);
            PSMTXConcat(m, pose->mtx, pose->mtx);
            pose->mtx[0][3] += work_20_bss_6C->pos.x;
            pose->mtx[1][3] += work_20_bss_6C->pos.y;
            pose->mtx[2][3] += work_20_bss_6C->pos.z;
            zako->pos.x = pose->mtx[0][3];
            zako->pos.y = pose->mtx[1][3];
            zako->pos.z = pose->mtx[2][3];
        } else {
            PSMTXIdentity(pose->mtx);
            PSMTXRotRad(m2, 'x', 0.017453292f * zako->rot.x);
            PSMTXConcat(pose->mtx, m2, pose->mtx);
            PSMTXRotRad(m2, 'y', 0.017453292f * zako->rot.y);
            PSMTXConcat(pose->mtx, m2, pose->mtx);
            PSMTXRotRad(m2, 'z', 0.017453292f * zako->rot.z);
            PSMTXConcat(pose->mtx, m2, pose->mtx);
            pose->mtx[0][3] = zako->pos.x;
            pose->mtx[1][3] = zako->pos.y;
            pose->mtx[2][3] = zako->pos.z + 0.03f * i;
        }
    }
}
