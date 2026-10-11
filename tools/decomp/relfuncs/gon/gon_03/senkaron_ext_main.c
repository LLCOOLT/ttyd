// include: mario/mario.h
// include: mario/mariost.h
// include: pmario_sound.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Senkaron { s8 state; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: Senkaron* senkaron;
// decl: s32 senkaronAttackStartFlag;
// decl: s32 senkaronEscapeFlag;
// decl: s32 senkaronMesPushingFlag;
// decl: s32 marioPushedFlag;
// decl: s32 marioHammerFrame;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: double sqrt(double x);
// proto: static void senkaron_ext_main(void);
static void senkaron_ext_main(void) {
    MarioWork* mario;
    const char* sfxLand;
    const char* sfxFly;
    const char* sfxFly2;
    s32 n;
    s32 i;
    ExtPose* pose;
    s32 r;
    f32 range;
    f32 near;
    f32 scale;
    f32 dx;
    f32 dz;
    f32 dist;
    f32 speed;

    pose = extGetPosePtr();
    mario = marioGetPtr();
    scale = mario->wPlayerCollisionBox.x / 2;
    marioPushedFlag = 0;
    if (mario->currMotionId == 0x12) {
        if (++marioHammerFrame == 15) {
            marioHammerFrame = 0;
        }
    } else {
        marioHammerFrame = 0;
    }
    n = extGetPoseNum();
    sfxLand = (0, "SFX_STG1_HONE_LANDING1");
    range = 1.5f * (6.0f * scale);
    sfxFly = (0, "SFX_STG1_HONE_FLY1");
    near = 3.0f * scale;
    sfxFly2 = (0, "SFX_STG1_HONE_FLY1");
    for (i = n - 1; i >= 0; i--, pose++) {
        switch (senkaron[i].state) {
            case 0:
                pose->frame = (gp->retraceCount + i * i) % 24;
                if (senkaron[i].timer > 0) {
                    if (senkaronEscapeFlag == 1) {
                        senkaron[i].state = 0x62;
                    } else if (senkaronAttackStartFlag == 1) {
                        senkaron[i].timer--;
                    }
                    break;
                }
                pose->mtx[1][3] += senkaron[i].vy;
                senkaron[i].vy -= 0.3f;
                if (pose->mtx[1][3] < 0.0f) {
                    pose->mtx[1][3] = 0.0f;
                    senkaron[i].state = 1;
                    senkaron[i].timer = 0;
                    senkaron[i].flags &= 0xFFFE;
                    if (i % 8 == 0) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = pose->mtx[0][3];
                        pos.y = pose->mtx[1][3];
                        pos.z = pose->mtx[2][3];
                        psndSFXOn_3D(sfxLand, &pos);
                    }
                }
                break;
            case 1:
                pose->frame = (gp->retraceCount + i * i) % 24;
                if (senkaronEscapeFlag == 1) {
                    if (pose->mtx[0][3] == 0.0f && pose->mtx[2][3] == 0.0f) {
                        senkaron[i].vx = 1.0f;
                        senkaron[i].vz = 1.0f;
                    } else {
                        dist = sqrt(pose->mtx[0][3] * pose->mtx[0][3] + pose->mtx[2][3] * pose->mtx[2][3]);
                        senkaron[i].vx = 4.0f * pose->mtx[0][3] / dist;
                        senkaron[i].vz = 4.0f * pose->mtx[2][3] / dist;
                    }
                    if (senkaron[i].vx < 0.0f) {
                        pose->rot = 90.0f;
                    } else {
                        pose->rot = 270.0f;
                    }
                    senkaron[i].state = 0x62;
                    senkaron[i].timer = 300;
                    break;
                }
                if (senkaronMesPushingFlag == 1) {
                    break;
                }
                if (mario->currMotionId == 0x12 && marioHammerFrame == 10 &&
                    pose->mtx[2][3] > mario->position.z - 80.0f && pose->mtx[2][3] < 80.0f + mario->position.z) {
                    if (mario->directionView > 0.0f && mario->directionView < 180.0f) {
                        if (pose->mtx[0][3] > mario->position.x && pose->mtx[0][3] < mario->position.x + range) {
                            f32 dx;
                            f32 dz;

                            dz = pose->mtx[2][3] - mario->position.z;
                            dx = pose->mtx[0][3] - mario->position.x;
                            dist = sqrt(dx * dx + dz * dz);
                            senkaron[i].vx = 3.0f * dx / dist - 1.0f;
                            senkaron[i].vy = randf(5.0f, 10.0f);
                            senkaron[i].vz = randf(-5.0f, 10.0f);
                            senkaron[i].state = 0x61;
                            {
                                Vec pos = {0.0f, 0.0f, 0.0f};
                                pos.x = pose->mtx[0][3];
                                pos.y = pose->mtx[1][3];
                                pos.z = pose->mtx[2][3];
                                psndSFXOn_3D(sfxFly, &pos);
                            }
                        }
                    } else {
                        if (pose->mtx[0][3] < mario->position.x && pose->mtx[0][3] > mario->position.x - range) {
                            f32 dx;
                            f32 dz;

                            dz = pose->mtx[2][3] - mario->position.z;
                            dx = pose->mtx[0][3] - mario->position.x;
                            dist = sqrt(dx * dx + dz * dz);
                            senkaron[i].vx = 1.0f + 3.0f * dx / dist;
                            senkaron[i].vy = randf(5.0f, 10.0f);
                            senkaron[i].vz = randf(-5.0f, 10.0f);
                            senkaron[i].state = 0x61;
                            {
                                Vec pos = {0.0f, 0.0f, 0.0f};
                                pos.x = pose->mtx[0][3];
                                pos.y = pose->mtx[1][3];
                                pos.z = pose->mtx[2][3];
                                psndSFXOn_3D(sfxFly2, &pos);
                            }
                        }
                    }
                }
                if (pose->mtx[0][3] > mario->position.x + scale - 10.0f && pose->mtx[0][3] < mario->position.x + near &&
                    pose->mtx[2][3] > mario->position.z - 20.0f && pose->mtx[2][3] < 20.0f + mario->position.z) {
                    marioPushedFlag = 1;
                }
                if (pose->mtx[0][3] >= mario->position.x) {
                    if (senkaron[i].flags & 1) {
                        pose->rot = 270.0f;
                    } else {
                        pose->rot = 90.0f;
                    }
                } else {
                    if (senkaron[i].flags & 1) {
                        pose->rot = 90.0f;
                    } else {
                        pose->rot = 270.0f;
                    }
                }
                if (senkaron[i].timer == 0) {
                    f32 dx;
                    f32 dz;
                    f32 dist;

                    dx = pose->mtx[0][3] - mario->position.x;
                    dz = pose->mtx[2][3] - mario->position.z;
                    dist = 10.0f * (f32)sqrt(dx * dx + dz * dz);
                    r = randf(0.0f, 50.0f);
                    senkaron[i].vx = randf(-0.5f, 0.5f);
                    senkaron[i].vz = randf(-0.5f, 0.5f);
                    senkaron[i].vx -= dx / dist;
                    senkaron[i].vz -= dz / dist;
                    if (r == 1) {
                        senkaron[i].flags |= 1;
                    } else {
                        senkaron[i].flags &= 0xFFFE;
                    }
                    senkaron[i].timer = 60;
                }
                senkaron[i].timer--;
                pose->mtx[0][3] += senkaron[i].vx;
                pose->mtx[2][3] += senkaron[i].vz;
                if (pose->mtx[0][3] > 375.0f) {
                    pose->mtx[0][3] = 375.0f;
                }
                if (pose->mtx[0][3] < -385.0f) {
                    pose->mtx[0][3] = -385.0f;
                }
                if (pose->mtx[2][3] > 140.0f) {
                    pose->mtx[2][3] = 140.0f;
                }
                if (pose->mtx[2][3] < -125.0f) {
                    pose->mtx[2][3] = -125.0f;
                }
                break;
            case 0x61:
                pose->flags |= 4;
                if (pose->mtx[1][3] > -100.0f) {
                    pose->mtx[0][3] += senkaron[i].vx;
                    pose->mtx[1][3] += senkaron[i].vy;
                    pose->mtx[2][3] += senkaron[i].vz;
                    if (pose->mtx[2][3] <= -125.0f) {
                        pose->mtx[2][3] = -125.0f;
                    }
                    senkaron[i].vy -= 0.3f;
                    pose->frame = 24;
                } else {
                    marioGetPtr();
                    pose->mtx[0][3] = randf(-385.0f, 375.0f);
                    pose->mtx[1][3] = 200.0f;
                    pose->mtx[2][3] = randf(-125.0f, 140.0f);
                    pose->rot = randf(0.0f, 360.0f);
                    pose->flags &= ~4;
                    senkaron[i].state = 0;
                    senkaron[i].timer = randf(1.0f, 1000.0f);
                    senkaron[i].vy = 0.0f;
                }
                break;
            case 0x62:
                if (senkaron[i].timer > 0) {
                    pose->mtx[0][3] += senkaron[i].vx;
                    pose->mtx[2][3] += senkaron[i].vz;
                    senkaron[i].timer--;
                } else {
                    senkaron[i].state = 0x63;
                }
                pose->frame = (gp->retraceCount + i * i) % 24;
                break;
            case 0x63:
                break;
        }
    }
    if (marioPushedFlag == 1) {
        f32 dx;
        f32 dz;
        f32 dist;
        f32 speed;

        dx = -390.0f - mario->position.x;
        dz = -mario->position.z;
        dist = sqrt(dx * dx + dz * dz);
        switch (mario->currMotionId) {
            case 0x12:
                speed = 0.0f;
                break;
            case 1:
                speed = randf(2.0f, 2.5f);
                break;
            case 2:
                speed = randf(2.8f, 3.3f);
                break;
            case 3:
                speed = randf(2.3f, 2.8f);
                break;
            default:
                speed = randf(0.7f, 1.2f);
                break;
        }
        mario->position.x += speed * (dx / dist);
        mario->position.z += speed * (dz / dist);
    }
}
