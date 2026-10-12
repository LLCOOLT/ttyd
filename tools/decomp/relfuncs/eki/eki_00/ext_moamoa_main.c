// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// include: manager/evtmgr.h
// include: manager/evtmgr.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; u8 field_0x30[0x3c - 0x30]; s16 pose; u8 field_0x3e[2]; OSTime startTime; u8 field_0x48[4]; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; u8 field_0xc[8]; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; EventEntry* escapeEvt; u8 field_0x48[4]; s32 numDefs; MoamoaPoseDef defs[32]; f32 angleToMario; f32 distToMario; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; u8 field_0x570[0x870 - 0x570]; } MoamoaWork;
// decl: typedef struct MoamoaData { const char* model; const char* anim; f32 speed; } MoamoaData;
// decl: static MoamoaWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: void extReset(void);
// decl: int rand(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: static void moamoa_pose_init(void);
// decl: static void moamoa_pose_main(void);
// decl: static void moamoa_pose_change(Moamoa* moa, const char* model, const char* anim);
// decl: #pragma inline_max_total_size(100000)
// decl: static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
// decl: static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
// include: mario/mario.h
// include: mario/mario_motion.h
// include: party.h
// include: driver/camdrv.h
// include: system.h
// include: pmario_sound.h
// decl: static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
// decl: static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
// decl: f32 cloudGetBreathDir(void);
// decl: f32 cloudGetBreathDist(void);
// decl: double sin(double);
// decl: double cos(double);
// proto: static void ext_moamoa_main(void);
#pragma opt_propagation off
#pragma opt_lifetimes off
static void ext_moamoa_main(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    s32 voice;
    s32 done = 0;

    const char* sfx;

    s32 i;
    s32 hit;
    ExtPose* pose;
    Moamoa* moa;
    s32 j;
    Moamoa* m;

    Vec* t;
    f32 angle;
    f32 dist;
    f32 rad;
    f32 speed;
    f32 x, y, z;
    f32 s;
    Mtx m1;
    Mtx m2;
    Vec v;

    if (mario->currMotionId == 0x12) {
        wp->field_0x40++;
    } else {
        wp->field_0x40 = 0;
    }
    if (mario->currMotionId == 0) {
        wp->field_0x42++;
        if (wp->field_0x42 > 1000) {
            wp->field_0x42 = 1000;
        }
    } else {
        wp->field_0x42 = 0;
    }
    if (party->flags & 0x100) {
        wp->flags |= 0x10;
    } else {
        wp->flags &= ~0x10;
    }
    wp->breathDir = -1.0f;
    wp->breathDist = -1.0f;
    if (party->currentMemberId == 5 && (party->flags & 0x100)) {
        wp->breathDir = cloudGetBreathDir();
        wp->breathDist = cloudGetBreathDist();
        wp->breathPos.x = party->position.x + wp->breathDist * moa_sin(6.2831855f * wp->breathDir / 360.0f);
        wp->breathPos.y = party->position.y;
        wp->breathPos.z = party->position.z - wp->breathDist * moa_cos(6.2831855f * wp->breathDir / 360.0f);
    }
    if (wp->field_0x38 > 250) {
        extGetPosePtr();
        m = wp->moa;
        for (j = 0; j < wp->count; j++, m++) {
            if (m->flags & 4) {
                continue;
            }
            if (m->flags & 0x10) {
                break;
            }
            m->state = 25;
            m->timer = 0;
            m->flags |= 0x10;
        }
        if (wp->escapeEvt == NULL) {
            wp->escapeEvt = evtEntry(evt_moamoa_escape, 0, 0);
        }
    }

    pose = extGetPosePtr();
    sfx = "SFX_STG6_MOAMOA_VOICE1";
    voice = 0;
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        wp->angleToMario = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        wp->distToMario = distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        if ((wp->flags & 1) && !(wp->flags & 4) && !marioKeyOffChk() && !marioCtrlOffChk() && !done && !(moa->flags & 0x154)) {
            hit = moamoa_hit_check(pose, moa);
            if (hit == 1) {
                moa->flags |= 4;
                moa->state = 36;
                wp->field_0x38++;
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                done = 1;
            } else if (hit == 2 || hit == 4) {
                moa->flags |= 0xc;
                moa->state = 47;
                wp->field_0x38++;
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                if (hit != 4) {
                    done = 1;
                }
            } else if (hit == 3) {
                moa->flags |= 0x84;
                moa->state = 48;
                moa->target = (Vec){0.0f, 0.0f, 0.0f};
                angle = (wp->breathDir + wp->angleToMario) * 0.5f;
                speed = randf(0.1f, 0.2f);
                rad = 6.2831855f * angle / 360.0f;
                moa->vy = speed * moa_sin(rad);
                moa->speed = randf(0.03f, 0.06f);
                moa->gravity = speed * -moa_cos(rad);
                moa->jumpTimer = 120;
                wp->field_0x38++;
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                done = 1;
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x155) && wp->distToMario < 50.0f) {
            if (moa->flags & 2) {
                moa->next = 1;
            } else {
                moa->state = 1;
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x444) && i == gp->retraceCount % wp->count && irand(1000) < 200) {
            v = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]}; psndSFXOn_3D(sfx, &v);
        }
        switch (moa->state) {
            case 0:
                if (i % 50 < 20) {
                    angle = randf(0.0f, 6.2831855f);
                    dist = randf(0.0f, 50.0f);
                    t = &wp->target[i % 3];
                    angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], t->x + dist * moa_sin(angle), t->z - dist * moa_cos(angle));
                    rad = 6.2831855f * angle / 360.0f;
                    x = pose->mtx[0][3] + 15.0f * moa_sin(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - 15.0f * moa_cos(rad);
                    moamoa_jump(pose, moa, moa->state, 1, x, y, z, randf(1.5f, 3.0f), randf(0.8f, 2.0f));
                    moa->flags |= 1;
                } else {
                    t = &wp->target[i % 3];
                    dist = distABf(pose->mtx[0][3], pose->mtx[2][3], t->x, t->z);
                    angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                    if (dist < 100.0f) {
                        angle = randf(0.0f, 360.0f);
                    }
                    rad = 6.2831855f * angle / 360.0f;
                    x = pose->mtx[0][3] + 5.0f * moa_sin(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - 5.0f * moa_cos(rad);
                    moamoa_jump(pose, moa, moa->state, 1, x, y, z, randf(0.3f, 0.5f), randf(0.5f, 0.8f));
                    moa->flags &= ~1;
                }
                break;
            case 50:
                if (--moa->timer < 0) {
                    moa->timer = 0;
                    moa->state++;
                }
                break;
            case 51:
                moa->speed = randf(0.0f, 200.0f);
                moa->gravity = randf(0.0f, 300.0f * moa->speed / 200.0f);
                moa->state++;
                moa->timer = 0;
            case 52:
                if (moa->timer < 200) {
                    s = 1.0f;
                } else {
                    s = (800 - moa->timer) / 600.0f;
                }
                if (s < 0.0f) {
                    s = 0.0f;
                    moa->flags |= 0x200;
                }
                x = wp->target[i % 3].x;
                y = wp->target[i % 3].y;
                z = wp->target[i % 3].z;
                x += s * (moa->gravity * (f32)sin((i + gp->retraceCount) * 0.25f));
                y += moa->speed * s;
                z += s * (-moa->gravity * (f32)cos((i + gp->retraceCount) * 0.25f));
                pose->mtx[0][3] += (x - pose->mtx[0][3]) / 15.0f;
                pose->mtx[1][3] += (y - pose->mtx[1][3]) / 15.0f;
                pose->mtx[2][3] += (z - pose->mtx[2][3]) / 15.0f;
                moa->timer++;
                break;
            case 1:
                angle = wp->angleToMario + randf(-45.0f, 45.0f);
                dist = wp->distToMario;
                rad = 6.2831855f * angle / 360.0f;
                x = pose->mtx[0][3] + 15.0f * moa_sin(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - 15.0f * moa_cos(rad);
                moamoa_jump(pose, moa, dist < 100.0f ? moa->state : 0, 1, x, y, z, randf(1.0f, 1.0f), randf(0.4f, 0.4f));
                break;
            case 2:
                angle = wp->angleToMario + randf(-45.0f, 45.0f) + 180.0f;
                dist = wp->distToMario;
                rad = 6.2831855f * angle / 360.0f;
                x = pose->mtx[0][3] + 30.0f * moa_sin(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3];
                moamoa_jump(pose, moa, dist < 100.0f ? moa->state : 0, 1, x, y, z, 2.0f * randf(1.0f, 1.0f), 2.0f * randf(0.4f, 0.4f));
                break;
            case 3:
                pose->mtx[1][3] += moa->vy;
                moa->vy -= moa->gravity;
                angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z);
                rad = 6.2831855f * angle / 360.0f;
                pose->mtx[0][3] += moa->speed * moa_sin(rad);
                pose->mtx[2][3] += moa->speed * -moa_cos(rad);
                if (--moa->jumpTimer < 0) {
                    pose->mtx[0][3] = moa->target.x;
                    pose->mtx[1][3] = moa->target.y;
                    pose->mtx[2][3] = moa->target.z;
                    moa->flags &= ~2;
                    pose->flags &= ~0x10;
                    moa->timer = 0;
                    moa->state++;
                }
                break;
            case 4:
                if (++moa->timer > 4) {
                    moa->state = moa->next;
                }
                break;
            case 36:
            case 37:
            case 38:
                if (!(moa->flags & 1)) {
                    x = mario->position.x;
                    z = mario->position.z;
                } else {
                    x = wp->target[i % 3].x;
                    z = wp->target[i % 3].z;
                }
                angle = angleABf(x, z, pose->mtx[0][3], pose->mtx[2][3]) + randf(-45.0f, 45.0f);
                rad = 6.2831855f * angle / 360.0f;
                x = pose->mtx[0][3] + 15.0f * moa_sin(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - 15.0f * moa_cos(rad);
                moamoa_jump(pose, moa, moa->state + 1, 1, x, y, z, randf(1.0f, 1.0f), randf(1.0f, 1.0f));
                break;
            case 39:
                if (++moa->timer < 30) {
                    pose->mtx[0][0] *= 0.9f;
                    pose->mtx[1][1] *= 0.9f;
                    pose->mtx[2][2] *= 0.9f;
                } else {
                    moa->state = 49;
                }
                break;
            case 47:
                rad = 6.2831855f * randf(135.0f, 225.0f) / 360.0f;
                dist = randf(300.0f, 500.0f);
                x = pose->mtx[0][3] + dist * moa_sin(rad);
                z = pose->mtx[2][3] - dist * moa_cos(rad);
                speed = randf(5.0f, 6.0f);
                s = randf(0.2f, 0.3f);
                if (!voice) {
                    psndSFXOn_3D((const char*)0x6c3, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                    voice = 1;
                }
                moamoa_jump(pose, moa, 49, 0, x, -100.0f, z, speed, s);
                break;
            case 48:
                if (--moa->jumpTimer > 0) {
                    moa->target.x += moa->vy;
                    moa->target.y += moa->speed;
                    moa->target.z += moa->gravity;
                    pose->mtx[0][3] += moa->target.x;
                    pose->mtx[1][3] += moa->target.y;
                    pose->mtx[2][3] += moa->target.z;
                } else {
                    moa->state = 49;
                }
                break;
            case 49:
                if ((wp->flags & 0x1000) && (wp->flags & 0x2000)) {
                    moa->state = 62;
                } else if (wp->field_0x38 < 250) {
                    PSMTXIdentity(pose->mtx);
                    pose->mtx[0][3] = wp->target[i % 3].x;
                    pose->mtx[1][3] = wp->target[i % 3].y;
                    pose->mtx[2][3] = wp->target[i % 3].z;
                    moa->flags = 0;
                    moa->state = 0;
                    moa->timer = 0;
                } else {
                    moa->state = 62;
                }
                break;
            case 25:
                if (moa->timer < 30) {
                    PSMTXRotRad(m1, 'y', 0.20943952f);
                    PSMTXConcat(pose->mtx, m1, pose->mtx);
                    pose->flags &= ~2;
                    moa->timer++;
                } else {
                    pose->flags |= 2;
                    moa->timer = (100.0f - distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z)) * 0.5f;
                    moa->state++;
                }
                break;
            case 26:
                if (--moa->timer < 0) {
                    moa->state++;
                }
                break;
            case 27:
                if (__fabs(pose->mtx[0][3]) < 300.0 && __fabs(pose->mtx[2][3]) < 300.0) {
                    angle = angleABf(wp->target[i % 3].x, wp->target[i % 3].z, pose->mtx[0][3], pose->mtx[2][3]) + randf(-45.0f, 45.0f);
                    rad = 6.2831855f * angle / 360.0f;
                    x = pose->mtx[0][3] + 15.0f * moa_sin(rad);
                    z = pose->mtx[2][3] - 15.0f * moa_cos(rad);
                    moamoa_jump(pose, moa, moa->state, 1, x, 0.0f, z, 3.0f * randf(1.0f, 1.0f), randf(1.0f, 1.0f));
                } else {
                    moa->state = 62;
                }
                break;
            case 62:
                moa->flags |= 0x20;
                pose->flags &= ~1;
                pose->flags |= 4;
                break;
            case 63:
                rad = 6.2831855f * randf(225.0f, 315.0f) / 360.0f;
                speed = randf(2.0f, 3.0f);
                moa->timer = irand(i / 2);
                moa->target.x = speed * moa_sin(rad);
                moa->target.y = randf(1.0f, 2.0f);
                moa->target.z = speed * -moa_cos(rad);
                moa->state++;
                break;
            case 64:
                if (--moa->timer < 0) {
                    moa->state++;
                }
                break;
            case 65:
                moa->target.x *= 1.1f;
                moa->target.y *= 1.02f;
                moa->target.z *= 1.1f;
                pose->mtx[0][3] += moa->target.x;
                pose->mtx[1][3] += moa->target.y;
                pose->mtx[2][3] += moa->target.z;
                PSMTXRotRad(m2, 'y', 0.20943952f);
                PSMTXConcat(pose->mtx, m2, pose->mtx);
                pose->flags &= ~2;
                if (pose->mtx[0][3] < -1000.0f) {
                    moa->state = 62;
                }
                break;
        }
        if (!(moa->flags & 0x98)) {
            if (pose->mtx[0][3] > 280.0f) {
                pose->mtx[0][3] = 280.0f;
            }
            if (pose->mtx[0][3] < -120.0f) {
                pose->mtx[0][3] = -120.0f;
            }
            if (pose->mtx[2][3] > 70.0f) {
                pose->mtx[2][3] = 70.0f;
            }
            if (pose->mtx[2][3] < -70.0f) {
                pose->mtx[2][3] = -70.0f;
            }
        }
        moa->field_0x28 = pose->mtx[0][3];
        moa->field_0x2c = pose->mtx[2][3];
    }
    moamoa_pose_main();
    if (wp->flags & 0x10) {
        mario->unk174.x = 0.0f;
        mario->unk174.y = 0.0f;
        mario->unk174.z = 0.0f;
    } else {
        v = (Vec){mario->unk174.x, mario->unk174.y, mario->unk174.z};
        if (PSVECMag(&v) > 2.0f) {
            PSVECNormalize(&v, &v);
            mario->unk174.x = 2.0f * v.x;
            mario->unk174.y = 2.0f * v.y;
            mario->unk174.z = 2.0f * v.z;
        }
    }
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
