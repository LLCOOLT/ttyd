// include: battle/battle.h
// include: battle/battle_unit.h
// include: driver/dispdrv.h
// include: mario/mariost.h
// include: system.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Chorogun { u8 flags; u8 state; u8 pad_2[2]; Vec vel; f32 speed; Vec pos; s32 timer; Vec target; } Chorogun;
// decl: Chorogun* chorogun;
// decl: s32 chorogun_targetId;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: s32 BtlUnit_snd_se_pos(BattleUnit* unit, const char* name, s32 vol, s32 pan, Vec* pos);
// decl: int rand(void);
// decl: double sqrt(double x);
// proto: void chorogun_ext_main(void);
void chorogun_ext_main(void) {
    BattleWork* wp;
    BattleUnit* unit;
    s32 i;
    s32 n;
    ExtPose* pose;
    Chorogun* c;
    f32 d;
    f32 dz;
    f32 dx;
    f32 tx;
    f32 tz;
    f32 dz2;
    f32 dx2;
    f32 x, y, z;

    wp = _battleWorkPointer;
    unit = chorogun_get_ptr();
    pose = extGetPosePtr();
    n = 0;
    for (i = 0; i < extGetPoseNum(); i++) {
        if (chorogun[i].flags & 1) {
            n++;
        }
    }
    n = 1000 - n;
    for (i = 0; i < extGetPoseNum(); i++, pose++) {
        pose->frame = (gp->retraceCount + i * i) % 20;
        c = &chorogun[i];
        pose->mtx[0][3] += c->vel.x;
        pose->mtx[1][3] += c->vel.y;
        pose->mtx[2][3] += c->vel.z;
        switch (c->state) {
        case 0:
            break;
        case 1:
            c->timer--;
            if (c->timer > 0) {
                break;
            }
            pose->mtx[0][3] = 500.0f * rand() / 32767.0f - 250.0f;
            pose->mtx[1][3] = 250.0f + 100.0f * rand() / 32767.0f;
            pose->mtx[2][3] = 800.0f * rand() / 32767.0f - 100.0f;
            c->vel.x = 0.0f;
            c->vel.y = 0.0f;
            c->vel.z = 0.0f;
            c->speed = 3.0f;
            c->state = 2;
            c->timer = 0;
            if (i == 0) {
                BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_CHORO_FALL2", 0x7F, 0, &(Vec){0.0f, 200.0f, 200.0f});
            }
            break;
        case 2:
            if (pose->mtx[1][3] <= 0.0f) {
                if (i % 100 == 0) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_CHORO_FALL1", 0x7F, 0, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                }
                c->state = 10;
            } else {
                c->vel.y += -0.25f;
            }
            break;
        case 10:
            if (pose->mtx[1][3] <= 0.0f) {
                dx = c->pos.x - pose->mtx[0][3];
                dz = c->pos.z - pose->mtx[2][3];
                d = sqrt(dx * dx + dz * dz);
                if (i % 100 == 0) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_CHORO_TOGETHER1", 0x7F, 0, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                }
                if (d <= 5.0f) {
                    c->state = 20;
                } else {
                    if (d <= 20.0f) {
                        c->speed *= 0.9f;
                    }
                    c->vel.x = c->speed * (dx / d);
                    c->vel.y = c->speed;
                    c->vel.z = c->speed * (dz / d);
                    pose->mtx[1][3] = 0.0f;
                }
            } else {
                c->vel.y += -0.5f;
            }
            break;
        case 20:
            pose->mtx[1][3] = 0.0f;
            c->vel.x = 0.0f;
            c->vel.y = c->speed;
            c->vel.z = 0.0f;
            c->state = 21;
            break;
        case 21:
            tx = unit->mPosition.x - unit->mHomePosition.x + intplGetValue(0, n, 1000, c->pos.x, unit->mHomePosition.x);
            tz = unit->mPosition.z - unit->mHomePosition.z + intplGetValue(0, n, 1000, c->pos.z, unit->mHomePosition.z);
            if (pose->mtx[1][3] <= unit->mPosition.y) {
                dx2 = tx - pose->mtx[0][3];
                dz2 = tz - pose->mtx[2][3];
                d = sqrt(dx2 * dx2 + dz2 * dz2);
                if (i % 100 == 0) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_CHORO_WAIT1", 0x60, 0, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                }
                c->speed = 3.0f + 0.5f * rand() / 32767.0f;
                c->vel.x = c->speed * (dx2 / d);
                c->vel.y = c->speed;
                c->vel.z = c->speed * (dz2 / d);
                pose->mtx[1][3] = unit->mPosition.y;
            } else {
                c->vel.y += -0.5f;
            }
            break;
        case 30:
            c->state = 31;
            c->timer = 0;
            BtlUnit_GetPos(BattleGetUnitPtr(wp, chorogun_targetId), &x, &y, &z);
            x += 50.0f * rand() / 32767.0f - 25.0f;
            c->target.x = x;
            z += 50.0f * rand() / 32767.0f - 25.0f;
            c->target.z = z;
        case 31:
            if (pose->mtx[1][3] <= 0.0f) {
                dx2 = c->target.x - pose->mtx[0][3];
                dz2 = c->target.z - pose->mtx[2][3];
                d = sqrt(dx2 * dx2 + dz2 * dz2);
                if (i % 100 == 0) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_CHORO_MOVE1", 0x60, 0, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                }
                if (d <= 30.0f || c->timer >= 240) {
                    c->state = 40;
                } else {
                    c->vel.x = c->speed * (dx2 / d);
                    c->vel.y = c->speed;
                    c->vel.z = c->speed * (dz2 / d);
                    pose->mtx[1][3] = 0.0f;
                    c->timer++;
                }
            } else {
                c->vel.y += -0.5f;
            }
            break;
        case 40:
            if (pose->mtx[1][3] <= 0.0f) {
                pose->mtx[1][3] = 0.0f;
                c->vel.x = 0.0f;
                c->vel.y = c->speed;
                c->vel.z = 0.0f;
            } else {
                c->vel.y += -0.5f;
            }
            break;
        case 45:
            c->timer--;
            if (c->timer <= 0) {
                c->timer = 0;
                c->vel.y = 0.0f;
            } else {
                c->vel.y += -0.5f;
            }
            break;
        case 46:
            c->state = 47;
            c->timer = 0;
            c->vel.y = 6.0f;
            if (pose->mtx[1][3] <= 0.0f) {
                pose->mtx[1][3] = 0.1f;
            }
        case 47:
            if (pose->mtx[1][3] <= 0.0f) {
                c->state = 40;
                pose->mtx[1][3] = 0.0f;
                c->vel.x = 0.0f;
                c->vel.y = c->speed;
                c->vel.z = 0.0f;
            } else {
                c->vel.y += -0.5f;
            }
            break;
        case 48:
            c->state = 49;
            c->timer = 0;
            c->vel.x = -4.0f;
            c->vel.y = 10.0f;
            if (pose->mtx[1][3] <= 0.0f) {
                pose->mtx[1][3] = 0.1f;
            }
        case 49:
            if (pose->mtx[1][3] <= 0.0f) {
                c->state = 40;
                pose->mtx[1][3] = 0.0f;
                c->vel.x = 0.0f;
                c->vel.y = c->speed;
                c->vel.z = 0.0f;
            } else {
                c->vel.y += -0.5f;
            }
            break;
        case 50:
            c->state = 20;
            break;
        case 60:
            c->state = 61;
            break;
        case 61:
            if (pose->mtx[1][3] <= 0.0f) {
                if (i % 100 == 0) {
                    BtlUnit_snd_se_pos(unit, "SFX_BOSS_TEAM_CHORO_MOVE1", 0x60, 0, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                }
                pose->mtx[1][3] = 0.0f;
                c->vel.x = 5.0f;
                c->vel.y = c->speed + irand(5);
                c->vel.z = 0.0f;
            } else {
                c->vel.y += -0.5f;
            }
            if (pose->mtx[0][3] >= 250.0f) {
                c->state = 99;
            }
            break;
        case 99:
            pose->mtx[0][3] = 0.0f;
            pose->mtx[1][3] = -1000.0f;
            pose->mtx[2][3] = 0.0f;
            break;
        }
    }
    dispEntry(CAMERA_3D, 0.0f, 1, chorogun_ext_disp, NULL);
}
