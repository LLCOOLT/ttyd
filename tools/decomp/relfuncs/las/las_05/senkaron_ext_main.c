// include: mario/mario.h
// include: mario/mariost.h
// include: pmario_sound.h
// include: party/party_vivian.h
// include: dolphin/mtx.h
// decl: typedef struct Senkaron { s8 state; u16 area; s32 timer; f32 vx; f32 vy; f32 vz; u32 flags; } Senkaron;
// decl: typedef struct SenkaronWork { s32 attackStart; s32 escape; s32 mesPushing; u32 frameCount; s32 marioPushed; s32 hammerFrame; Senkaron* sk; } SenkaronWork;
// decl: SenkaronWork* skwp;
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: double sqrt(double x);
// decl: int rand(void);
// decl: f32 marioGetAngleKaitenHammer(void);
// decl: extern int __float_nan[];
// decl: s32 psndSFXOn_3D(const char* name, Vec* position);
// decl: extern s32 move_check_list[];
// decl: static inline s32 k_fpclassifyf(f32 x) { switch (*(s32*)&x & 0x7F800000) { case 0x7F800000: if (*(s32*)&x & 0x007FFFFF) { return 1; } else { return 2; } break; case 0: if (*(s32*)&x & 0x007FFFFF) { return 5; } else { return 3; } break; default: return 4; } }
// decl: static inline f32 k_sqrtf(f32 x) { const f64 _half = .5; const f64 _three = 3.0; if (x > 0.0f) { f64 guess = __frsqrte(x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); guess = _half * guess * (_three - guess * guess * x); return x * guess; } else if (x < 0.0) { return *(f32*)__float_nan; } else if (k_fpclassifyf(x) == 1) { return *(f32*)__float_nan; } return x; }
// decl: s32 party_hit_check(f32* dir, f32 x, f32 z);
// decl: void calc_area(s32 i, f32 x, f32 z);
// decl: void move_check(ExtPose* pose, s32 idx);
// proto: static void senkaron_ext_main(void);
static void senkaron_ext_main(void) {
    MarioWork* mario;
    ExtPose* pose;
    s32 hit;
    f32 range;
    ExtPose* p;
    ExtPose* ep;
    Senkaron* sk;
    Senkaron* s;
    f32 near;
    const char* sfxLand;
    const char* sfxFly;
    s32 hammerDir;
    s32 group;
    s32 start;
    s32 end;
    s32 i;
    f32 scale;
    f32 push;
    f32 dx;
    f32 adx;
    f32 adz;
    f32 dist;
    f32 angle;
    f32 speed;

    pose = extGetPosePtr();
    mario = marioGetPtr();
    hammerDir = 0;
    sk = skwp->sk;
    scale = mario->wPlayerCollisionBox.x / 2.0f;
    skwp->marioPushed = 0;
    if (mario->currMotionId == 0x12) {
        skwp->hammerFrame++;
        skwp->hammerFrame %= 15;
    } else {
        skwp->hammerFrame = 0;
    }
    if (mario->currMotionId == 0x12 && skwp->hammerFrame == 10) {
        if (0.0f == mario->unk1AC) {
            hammerDir = 1;
        } else if (180.0f == mario->unk1AC) {
            hammerDir = 2;
        } else if (mario->unk1A8 < 90.0f || 270.0f < mario->unk1A8) {
            hammerDir = 1;
        } else {
            hammerDir = 2;
        }
    }
    group = skwp->frameCount % 20;
    if (group != 0) {
        start = move_check_list[group - 1] + 1;
    } else {
        start = 0;
    }
    end = move_check_list[group];
    p = &pose[start];
    for (i = start; i < end; i++, p++) {
        sk[i].flags &= ~2;
        calc_area(i, p->mtx[0][3], p->mtx[2][3]);
    }
    p = &extGetPosePtr()[start];
    for (i = start; i < end; i++, p++) {
        move_check(p, i);
    }
    skwp->frameCount++;
    ep = extGetPosePtr();
    sfxLand = "SFX_STG8_KARON_LANDING1";
    range = 1.5f * (6.0f * scale);
    sfxFly = "SFX_STG8_KARON_FLY1";
    near = 3.0f * scale;
    for (i = 0; i < 1000; i++, ep++) {
        s = &sk[i];
        switch (s->state) {
            case 0:
                ep->frame = (gp->retraceCount + i * i) % 24;
                if (s->timer > 0) {
                    if (skwp->escape) {
                        ep->flags &= ~1;
                        s->state = 0x63;
                    } else if (skwp->attackStart) {
                        s->timer--;
                    }
                    break;
                }
                ep->mtx[1][3] += s->vy;
                s->vy -= 0.3f;
                if (ep->mtx[1][3] < 0.0f) {
                    ep->mtx[1][3] = 0.0f;
                    s->state = 1;
                    s->timer = 0;
                    s->flags &= 0xFFFE;
                    if (i % 8 == 0) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = ep->mtx[0][3];
                        pos.y = ep->mtx[1][3];
                        pos.z = ep->mtx[2][3];
                        psndSFXOn_3D(sfxLand, &pos);
                    }
                }
                break;
            case 1:
                ep->frame = (gp->retraceCount + i * i) % 24;
                if (skwp->escape) {
                    if (0.0f == ep->mtx[0][3] && 0.0f == ep->mtx[2][3]) {
                        s->vx = 1.0f;
                        s->vz = 1.0f;
                    } else {
                        dist = sqrt(ep->mtx[0][3] * ep->mtx[0][3] + ep->mtx[2][3] * ep->mtx[2][3]);
                        s->vx = 4.0f * ep->mtx[0][3] / dist;
                        s->vz = 4.0f * ep->mtx[2][3] / dist;
                    }
                    if (s->vx < 0.0f) {
                        ep->rot = 90.0f;
                    } else {
                        ep->rot = 270.0f;
                    }
                    s->state = 0x62;
                    s->timer = 300;
                    break;
                }
                hit = 0;
                dx = ep->mtx[0][3] - mario->position.x;
                push = 0.0f;
                adx = __fabsf(dx);
                adz = __fabsf(ep->mtx[2][3] - mario->position.z);
                if (ep->mtx[0][3] >= mario->position.x) {
                    if (s->flags & 1) {
                        ep->rot = 270.0f;
                    } else {
                        ep->rot = 90.0f;
                    }
                } else {
                    if (s->flags & 1) {
                        ep->rot = 90.0f;
                    } else {
                        ep->rot = 270.0f;
                    }
                }
                if (skwp->mesPushing) {
                    break;
                }
                if (hammerDir != 0 && adz < 80.0f) {
                    if (hammerDir == 2) {
                        if (ep->mtx[0][3] > mario->position.x && adx < range) {
                            hit = 1;
                            push = 1.0f;
                        }
                    } else {
                        if (ep->mtx[0][3] < mario->position.x && adx < range) {
                            hit = 1;
                            push = -1.0f;
                        }
                    }
                }
                angle = marioGetAngleKaitenHammer();
                if (angle >= 0.0f && adx < 80.0f && adz < 80.0f) {
                    if (angle >= 0.0f && angle < 90.0f) {
                        if (ep->mtx[2][3] > mario->position.z && ep->mtx[0][3] > mario->position.x) {
                            hit = 1;
                            push = 1.0f;
                        }
                    } else if (angle >= 90.0f && angle < 180.0f) {
                        if (ep->mtx[2][3] > mario->position.z && ep->mtx[0][3] < mario->position.x) {
                            hit = 1;
                            push = -1.0f;
                        }
                    } else if (angle >= 180.0f && angle < 270.0f) {
                        if (ep->mtx[2][3] < mario->position.z && ep->mtx[0][3] < mario->position.x) {
                            hit = 1;
                            push = -1.0f;
                        }
                    } else {
                        if (ep->mtx[2][3] < mario->position.z && ep->mtx[0][3] > mario->position.x) {
                            hit = 1;
                            push = -1.0f;
                        }
                    }
                }
                {
                    f32 dir = 0.0f;

                    if (party_hit_check(&dir, ep->mtx[0][3], ep->mtx[2][3])) {
                        hit = 2;
                        push = dir;
                    }
                }
                if (hit != 0) {
                    dist = k_sqrtf(adx * adx + adz * adz);
                    s->vx = push + 3.0f * dx / dist;
                    s->vy = randf(5.0f, 10.0f);
                    s->vz = randf(-5.0f, 10.0f);
                    s->state = 0x61;
                    if (hit == 1) {
                        Vec pos = {0.0f, 0.0f, 0.0f};
                        pos.x = ep->mtx[0][3];
                        pos.y = ep->mtx[1][3];
                        pos.z = ep->mtx[2][3];
                        psndSFXOn_3D(sfxFly, &pos);
                    }
                    break;
                }
                if (adz < 40.0f && vivianGetStatus() != 1 && vivianGetStatus() != 2 && vivianGetStatus() != 3) {
                    if (ep->mtx[0][3] > 0.0f) {
                        if (ep->mtx[0][3] > mario->position.x + scale - 10.0f && ep->mtx[0][3] < mario->position.x + near) {
                            skwp->marioPushed |= 1;
                        }
                    } else {
                        if (ep->mtx[0][3] > mario->position.x - near && ep->mtx[0][3] < 10.0f + (mario->position.x - scale)) {
                            skwp->marioPushed |= 2;
                        }
                    }
                }
                if (s->timer == 0) {
                    f32 tz = ep->mtx[2][3] - mario->position.z;
                    f32 tx = ep->mtx[0][3] - mario->position.x;
                    f32 td = 10.0f * (f32)sqrt(tx * tx + tz * tz);
                    s32 r = rand() % 50;

                    s->vx = randf(-0.5f, 0.5f);
                    s->vz = randf(-0.5f, 0.5f);
                    s->vx -= tx / td;
                    s->vz -= tz / td;
                    if (r == 1) {
                        s->flags |= 1;
                    } else {
                        s->flags &= 0xFFFE;
                    }
                    s->timer = 60;
                }
                s->timer--;
                if (s->flags & 2) {
                    ep->mtx[0][3] -= s->vx;
                    ep->mtx[2][3] -= s->vz;
                } else {
                    ep->mtx[0][3] += s->vx;
                    ep->mtx[2][3] += s->vz;
                }
                if (ep->mtx[0][3] > 570.0f) {
                    ep->mtx[0][3] = 570.0f;
                }
                if (ep->mtx[0][3] < -570.0f) {
                    ep->mtx[0][3] = -570.0f;
                }
                if (ep->mtx[2][3] > 270.0f) {
                    ep->mtx[2][3] = 270.0f;
                }
                if (ep->mtx[2][3] < -270.0f) {
                    ep->mtx[2][3] = -270.0f;
                }
                break;
            case 0x61:
                ep->flags |= 4;
                if (ep->mtx[1][3] > -100.0f) {
                    ep->mtx[0][3] += s->vx;
                    ep->mtx[1][3] += s->vy;
                    ep->mtx[2][3] += s->vz;
                    if (ep->mtx[2][3] <= -270.0f) {
                        ep->mtx[2][3] = -270.0f;
                    }
                    s->vy -= 0.3f;
                    ep->frame = 24;
                } else {
                    marioGetPtr();
                    ep->mtx[0][3] = randf(-570.0f, 570.0f);
                    ep->mtx[1][3] = 250.0f;
                    ep->mtx[2][3] = randf(-270.0f, 270.0f);
                    ep->rot = randf(0.0f, 360.0f);
                    ep->flags &= ~4;
                    s->state = 0;
                    s->timer = rand() % 1000 + 1;
                    s->vy = 0.0f;
                }
                break;
            case 0x62:
                if (s->timer > 0) {
                    ep->mtx[0][3] += s->vx;
                    ep->mtx[2][3] += s->vz;
                    s->timer--;
                    if (s->timer % 10 == 0) {
                        if (!((s->timer / 5) & 1)) {
                            Vec pos = {0.0f, 0.0f, 0.0f};
                            pos.x = ep->mtx[0][3];
                            pos.y = ep->mtx[1][3];
                            pos.z = ep->mtx[2][3];
                            psndSFXOn_3D((const char*)0xAFB, &pos);
                        } else {
                            Vec pos = {0.0f, 0.0f, 0.0f};
                            pos.x = ep->mtx[0][3];
                            pos.y = ep->mtx[1][3];
                            pos.z = ep->mtx[2][3];
                            psndSFXOn_3D((const char*)0xAFC, &pos);
                        }
                    }
                } else {
                    ep->flags &= ~1;
                    s->state = 0x63;
                }
                ep->frame = (gp->retraceCount + i * i) % 24;
                break;
            case 0x63:
                break;
        }
    }
    if (((skwp->marioPushed & 1) && mario->position.x > 0.0f) || ((skwp->marioPushed & 2) && mario->position.x < 0.0f)) {
        f32 mz = -mario->position.z;
        f32 mx = -mario->position.x;

        dist = k_sqrtf(mx * mx + mz * mz);
        switch (mario->currMotionId) {
            case 0x12:
            case 0x13:
                speed = 0.0f;
                break;
            case 1:
                speed = randf(3.0f, 3.5f);
                break;
            case 2:
                speed = randf(3.8f, 4.3f);
                break;
            case 3:
                speed = randf(3.3f, 3.8f);
                break;
            default:
                speed = randf(1.7f, 2.2f);
                break;
        }
        mario->position.x += speed * (mx / dist);
        mario->position.z += speed * (mz / dist);
    }
}
