// include: mario/mario.h
// include: party/party_cloud.h
// include: system.h
// include: pmario_sound.h
// include: driver/npcdrv.h
// include: driver/hitdrv.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
// decl: typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
// decl: typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
// decl: typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
// decl: FanWork* fan_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static inline f32 fan_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 fan_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// decl: s32 check_hammer(Fan* fan);
// decl: static f32 randf(f32 min, f32 max);
// decl: void psndSFX_pos(s32 id, Vec* pos);
// decl: void psndSFX_vol(s32 id, u8 vol);
// proto: void ext_fan_main(void);
#pragma opt_propagation off
#pragma opt_lifetimes off
void ext_fan_main(void) {
    MarioWork* mario = marioGetPtr();
    Vec dir;
    Vec target = {0.0f, 0.0f, 0.0f};

    if (mario->currMotionId == 0x12) {
        fan_wp->hammerTimer++;
    } else {
        fan_wp->hammerTimer = 0;
    }
    if (evtGetValue(NULL, GF(10))) {
        ExtPose* pose = extGetPosePtr();
        Fan* fan = fan_wp->fans;
        s32 i;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                fan->pos = mario->position;
                target = fan->pos;
                pose->flags &= ~1;
                fan->flags |= 1;
                break;
            }
        }
    } else {
        s32 i;
        ExtPose* pose;
        Fan* fan;
        s32 found = 0;

        pose = extGetPosePtr();
        fan = fan_wp->fans;

        for (i = 0; i < fan_wp->num; i++, fan++, pose++) {
            if (fan->state == 0) {
                if (!found) {
                    found = 1;
                    fan->pos = mario->position;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                } else {
                    fan->pos = npcNameToPtr("\203`\203\203\203\223\203s\203\207\203\223")->position;
                    target = fan->pos;
                    pose->flags &= ~1;
                    fan->flags |= 1;
                    break;
                }
            }
        }
    }

    {
        Fan* fan;
        s32 i;

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                PSVECSubtract(&target, &fan->pos, &dir);
                if (PSVECMag(&dir)) {
                    PSVECNormalize(&dir, &dir);
                    dir.y = 0.0f;
                    PSVECScale(&dir, &dir, 0.1f);
                    PSVECAdd(&fan->vel, &dir, &fan->vel);
                }
            }
        }
    }

    {
        s32 i;
        Fan* fan;

        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                s32 j;
                Fan* other;

                for (j = 0, other = fan_wp->fans; j < fan_wp->num; j++, other++) {
                    if (other->state == 0 && i != j && PSVECSquareDistance(&fan->pos, &other->pos) < 900.0f) {
                        PSVECSubtract(&fan->pos, &other->pos, &dir);
                        dir.y = 0.0f;
                        PSVECNormalize(&dir, &dir);
                        PSVECScale(&dir, &dir, 5.0f);
                        PSVECAdd(&fan->vel, &dir, &fan->vel);
                        PSVECSubtract(&other->vel, &dir, &other->vel);
                    }
                }
            }
        }
    }

    {
        const char* sfx1;
        const char* sfx2;
        s32 i;
        Fan* fan;
        f32 angle;
        f32 dist;
        f32 dy;
        f32 spd;
        f32 x;
        f32 z;
        f32 dir2;

        sfx1 = "SFX_STG3_AUDIENCE_FAN_FLY1";
        sfx2 = "SFX_STG3_AUDIENCE_FAN_FLY1";
        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++) {
            if (fan->state == 0) {
                switch (check_hammer(fan)) {
                    case 0:
                        break;
                    case 1:
                        fan->state = 10;
                        angle = 6.2831855f * randf(135.0f, 225.0f) / 360.0f;
                        dist = randf(400.0f, 500.0f);
                        x = fan->pos.x + dist * fan_sin(angle);
                        z = fan->pos.z - dist * fan_cos(angle);
                        {
                            Vec tgt = {0.0f, 0.0f, 0.0f};

                            tgt.x = x;
                            tgt.y = -100.0f;
                            tgt.z = z;
                            fan->target = tgt;
                        }
                        fan->param.y = randf(4.0f, 6.0f);
                        fan->param.z = randf(0.1f, 0.2f);
                        dy = fan->target.y - fan->pos.y;
                        dist = distABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                        fan->timer = dist / fan->param.y;
                        fan->param.x = dy / fan->timer + fan->param.z * fan->timer * 0.5f;
                        psndSFXOn_3D(sfx1, &fan->pos);
                        break;
                    case 2: {
                        static const Vec zero = {0.0f, 0.0f, 0.0f};

                        angle = angleABf(mario->position.x, mario->position.z, fan->pos.x, fan->pos.z);
                        dir2 = cloudGetBreathDir();
                        angle = (angle + dir2) * 0.5f;
                        fan->state = 20;
                        fan->target = zero;
                        spd = randf(0.1f, 0.2f);
                        angle = 6.2831855f * angle / 360.0f;
                        fan->param.x = spd * fan_sin(angle);
                        fan->param.y = randf(0.03f, 0.06f);
                        fan->param.z = spd * -fan_cos(angle);
                        fan->timer = 120;
                        psndSFXOn_3D(sfx2, &fan->pos);
                        break;
                    }
                }
            }
        }
    }
    fan_wp->count = fan_wp->num;

    {
        HitCheckQuery query;
        s32 i;
        ExtPose* pose;
        Fan* fan;
        f32 angle;
        f32 dist;
        f32 h;

        pose = extGetPosePtr();
        for (i = 0, fan = fan_wp->fans; i < fan_wp->num; i++, fan++, pose++) {
            switch (fan->state) {
                case 0:
                    PSVECNormalize(&fan->vel, &fan->vel);
                    dist = PSVECMag(&fan->vel);
                    query.targetPos = fan->pos;
                    query.targetPos.y += 4.0f;
                    query.targetDir = fan->vel;
                    query.targetDir.y = 0.0f;
                    query.targetDistance = 25.0f + dist;
                    if (hitCheckVecFilter(&query, NULL) != NULL) {
                        C_VECReflect(&fan->vel, &query.hitNormal, &fan->vel);
                    } else {
                        fan->pos.x += fan->vel.x;
                        fan->pos.z += fan->vel.z;
                        fan->vel.x *= 0.6f;
                        fan->vel.z *= 0.6f;
                    }
                    if (fan->pos.x < -350.0f) {
                        fan->pos.x = -350.0f;
                    }
                    if (fan->pos.x > 350.0f) {
                        fan->pos.x = 350.0f;
                    }
                    h = 195.0f + i / 100.0f;
                    if (fan->pos.y > h) {
                        fan->pos.y = h;
                    }
                    break;
                case 10:
                    fan->pos.y += fan->param.x;
                    fan->param.x -= fan->param.z;
                    angle = angleABf(fan->pos.x, fan->pos.z, fan->target.x, fan->target.z);
                    angle = 6.2831855f * angle / 360.0f;
                    fan->pos.x += fan->param.y * fan_sin(angle);
                    fan->pos.z += fan->param.y * -fan_cos(angle);
                    if (--fan->timer < 0) {
                        fan->state = 100;
                    }
                    break;
                case 20:
                    if (--fan->timer > 0) {
                        fan->target.x += fan->param.x;
                        fan->target.y += fan->param.y;
                        fan->target.z += fan->param.z;
                        fan->pos.x += fan->target.x;
                        fan->pos.y += fan->target.y;
                        fan->pos.z += fan->target.z;
                    } else {
                        fan->state = 100;
                    }
                    break;
                case 100:
                    pose->flags &= ~3;
                    fan->state++;
                    break;
                case 101:
                    break;
            }
            if (fan->flags & 1) {
                fan_wp->count--;
            } else if (fan->state != 0) {
                fan_wp->count--;
            }
            pose->mtx[0][3] = fan->pos.x;
            pose->mtx[1][3] = fan->pos.y;
            pose->mtx[2][3] = fan->pos.z;
            pose->rot = angleABf(target.x, target.z, fan->pos.x, fan->pos.z);
        }
    }
    psndSFX_pos(fan_wp->sfxId, &target);
    psndSFX_vol(fan_wp->sfxId, fan_wp->vol * fan_wp->count / fan_wp->num);
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
