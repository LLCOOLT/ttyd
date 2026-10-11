// include: manager/evtmgr.h
// include: driver/mapdrv.h
// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; Vec field_0x30; s16 pose; u8 field_0x3e[2]; OSTime startTime; s16 group; s16 order; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; void* escapeEvt; s32 animPoseId; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; s16 chainNum[128]; s16 chainIdx[128][2]; } MoamoaWork;
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
// include: driver/npcdrv.h
// include: driver/animdrv.h
// decl: extern const char* g_moamoa_chain_tbl[][2];
// decl: extern const s32 dat_80419a28;
// decl: #pragma inline_max_total_size(100000)
// decl: static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// include: mario/mario.h
// include: party.h
// include: party/party_cloud.h
// include: driver/camdrv.h
// include: pmario_sound.h
// include: system.h
// decl: f32 cloudGetBreathDist(void);
// decl: double sin(double x);
// decl: double cos(double x);
// decl: static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
// decl: static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
// decl: void moamoa_joint_position(Moamoa* moa, Vec* out);
// proto: static void ext_moamoa_main(void);
#pragma opt_propagation off
#pragma opt_lifetimes off
static void ext_moamoa_main(void) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party = partyGetPtr(0);
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 cnt = 0.0f;
    s32 hit = 0;
    const char* sfx;
    s32 sndFlag;
    s32 i;
    s32 ret;
    s32 idx;
    ExtPose* pose;
    ExtPose* other;
    Moamoa* moa;
    Moamoa* m;
    f32 rad;
    f32 angle;
    f32 dist;
    f32 x, y, z;
    f32 spd;
    f32 grav;
    f32 s;
    f32 tx, ty, tz;
    Vec jv;
    Vec pv;
    Vec sp;
    Mtx rot;

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
        wp->breathPos.x = wp->breathDist * moa_sin(6.2831855f * wp->breathDir / 360.0f) + party->position.x;
        wp->breathPos.y = party->position.y;
        wp->breathPos.z = party->position.z - wp->breathDist * moa_cos(6.2831855f * wp->breathDir / 360.0f);
    }

    pose = extGetPosePtr();
    sfx = "SFX_STG6_MOAMOA_VOICE1";
    sndFlag = 0;
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        wp->angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        wp->dist = distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        if (!(moa->flags & 0x154) && mario->position.y > 200.0f && wp->dist < 30.0f) {
            cnt += 1.0f;
        }
        if ((wp->flags & 1) && !(wp->flags & 4) && !marioKeyOffChk() && !marioCtrlOffChk() && !hit && !(moa->flags & 0x154)) {
            ret = moamoa_hit_check(pose, moa);
            if (ret == 1) {
                moa->flags |= 4;
                moa->state = 36;
                wp->field_0x38++;
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                hit = 1;
            } else if (ret == 2 || ret == 4) {
                moa->flags |= 0xc;
                moa->state = 47;
                wp->field_0x38++;
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                if (ret != 4) {
                    hit = 1;
                }
            } else if (ret == 3) {
                moa->flags |= 0x84;
                moa->state = 48;
                angle = (wp->breathDir + wp->angle) / 2;
                moa->target = (Vec){0.0f, 0.0f, 0.0f};
                spd = randf(0.1f, 0.2f);
                rad = 6.2831855f * angle / 360.0f;
                moa->vy = spd * moa_sin(rad);
                moa->speed = randf(0.03f, 0.06f);
                moa->gravity = spd * -moa_cos(rad);
                moa->jumpTimer = 120;
                wp->field_0x38++;
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                hit = 1;
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x155)) {
            if (mario->currMotionId == 0 || (u16)(mario->currMotionId - 1) <= 1 || (u16)(mario->currMotionId - 0x15) <= 1 ||
                mario->currMotionId == 0x1a) {
                if (mario->position.y > 200.0f && wp->dist > 30.0f && wp->dist < 100.0f && (i & 1)) {
                    if (moa->flags & 2) {
                        moa->next = 2;
                    } else {
                        moa->state = 2;
                    }
                }
            } else if (wp->dist < 50.0f) {
                if (moa->flags & 2) {
                    moa->next = 1;
                } else {
                    moa->state = 1;
                }
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x444) && i == gp->retraceCount % wp->count && irand(1000) < 200) {
            sp = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
            psndSFXOn_3D(sfx, &sp);
        }
        switch (moa->state) {
            case 0:
                if (moa->flags & 0x40) {
                    break;
                }
                rad = 6.2831855f * randf(0.0f, 360.0f) / 360.0f;
                x = 5.0f * moa_sin(rad) + pose->mtx[0][3];
                z = pose->mtx[2][3] - 5.0f * moa_cos(rad);
                moamoa_jump(pose, moa, moa->state, 0, x, 215.0f, z, randf(0.3f, 0.5f), randf(0.5f, 0.8f));
                break;
            case 14:
            case 50:
                if (--moa->timer < 0) {
                    moa->timer = 0;
                    moa->state++;
                }
                break;
            case 15:
                dist = distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                if (dist > 31.0f) {
                    rad = 6.2831855f * angle / 360.0f;
                    x = 30.0f * moa_sin(rad) + pose->mtx[0][3];
                    z = pose->mtx[2][3] - 30.0f * moa_cos(rad);
                    spd = 2.0f * randf(1.0f, 1.0f);
                    grav = 2.0f * randf(0.4f, 0.4f);
                    moamoa_jump(pose, moa, moa->state, 0, x, 215.0f, z, spd, grav);
                } else {
                    moamoa_joint_position(moa, &jv);
                    PSVECAdd(&jv, &moa->field_0x30, &jv);
                    spd = 2.0f * randf(1.5f, 1.5f);
                    grav = 2.0f * randf(0.8f, 0.8f);
                    moamoa_jump(pose, moa, 61, 0, jv.x, jv.y, jv.z, spd, grav);
                    moa->flags |= 0x200;
                    pose->flags |= 4;
                }
                break;
            case 61:
                moamoa_joint_position(moa, &pv);
                PSVECAdd(&pv, &moa->field_0x30, &pv);
                pose->mtx[0][3] = pv.x;
                pose->mtx[1][3] = pv.y;
                pose->mtx[2][3] = pv.z;
                break;
            case 51:
                moa->speed = randf(0.0f, 200.0f);
                s = 300.0f * moa->speed / 200.0f;
                moa->gravity = randf(0.0f, s);
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
                tx = wp->target[i % 3].x;
                ty = wp->target[i % 3].y;
                tz = wp->target[i % 3].z;
                tx += s * (moa->gravity * (f32)sin((i + gp->retraceCount) * 0.25f));
                ty += moa->speed * s;
                tz += s * (-moa->gravity * (f32)cos((i + gp->retraceCount) * 0.25f));
                pose->mtx[0][3] += (tx - pose->mtx[0][3]) / 15.0f;
                pose->mtx[1][3] += (ty - pose->mtx[1][3]) / 15.0f;
                pose->mtx[2][3] += (tz - pose->mtx[2][3]) / 15.0f;
                moa->timer++;
                break;
            case 1:
                rad = 6.2831855f * (wp->angle + randf(-45.0f, 45.0f)) / 360.0f;
                dist = wp->dist;
                x = 15.0f * moa_sin(rad) + pose->mtx[0][3];
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - 15.0f * moa_cos(rad);
                spd = randf(1.0f, 1.0f);
                grav = randf(0.4f, 0.4f);
                moamoa_jump(pose, moa, dist < 100.0f ? moa->state : 0, 0, x, y, z, spd, grav);
                break;
            case 2:
                rad = 6.2831855f * (wp->angle + randf(-45.0f, 45.0f) + 180.0f) / 360.0f;
                dist = wp->dist;
                x = 30.0f * moa_sin(rad) + pose->mtx[0][3];
                y = pose->mtx[1][3];
                z = pose->mtx[2][3];
                spd = 2.0f * randf(1.0f, 1.0f);
                grav = 2.0f * randf(0.4f, 0.4f);
                moamoa_jump(pose, moa, dist < 100.0f ? moa->state : 0, 0, x, y, z, spd, grav);
                break;
            case 3:
                pose->mtx[1][3] += moa->vy;
                moa->vy -= moa->gravity;
                rad = 6.2831855f * angleABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z) / 360.0f;
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
                    tx = mario->position.x;
                    tz = mario->position.z;
                } else {
                    tx = wp->target[i % 3].x;
                    tz = wp->target[i % 3].z;
                }
                rad = 6.2831855f * (angleABf(tx, tz, pose->mtx[0][3], pose->mtx[2][3]) + randf(-45.0f, 45.0f)) / 360.0f;
                x = 15.0f * moa_sin(rad) + pose->mtx[0][3];
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - 15.0f * moa_cos(rad);
                spd = randf(1.0f, 1.0f);
                grav = randf(1.0f, 1.0f);
                moamoa_jump(pose, moa, moa->state + 1, 1, x, y, z, spd, grav);
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
                dist = randf(200.0f, 500.0f);
                x = dist * moa_sin(rad) + pose->mtx[0][3];
                z = pose->mtx[2][3] - dist * moa_cos(rad);
                spd = randf(5.0f, 6.0f);
                s = randf(0.2f, 0.3f);
                if (!sndFlag) {
                    Vec p;
                    p = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
                    psndSFXOn_3D((const char*)0x6c3, &p);
                    sndFlag = 1;
                }
                moamoa_jump(pose, moa, 49, 0, x, -100.0f, z, spd, s);
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
                PSMTXIdentity(pose->mtx);
                do {
                    idx = rand() % 700;
                    m = &wp->moa[idx];
                } while ((m->state != 0 && m->state != 3) || (m->flags & 0x40));
                other = extGetPosePtr() + idx;
                pose->mtx[0][3] = other->mtx[0][3];
                pose->mtx[1][3] = 215.0f;
                pose->mtx[2][3] = other->mtx[2][3];
                moa->flags = 0;
                moa->state = 0;
                moa->timer = 0;
                break;
            case 62:
                moa->flags |= 0x20;
                pose->flags &= ~1;
                pose->flags |= 4;
                break;
            case 63:
                angle = randf(225.0f, 315.0f);
                spd = randf(2.0f, 3.0f);
                moa->timer = irand(i / 2);
                rad = 6.2831855f * angle / 360.0f;
                moa->target.x = spd * moa_sin(rad);
                moa->target.y = randf(1.0f, 2.0f);
                moa->target.z = spd * -moa_cos(rad);
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
                PSMTXRotRad(rot, 'y', 0.20943952f);
                PSMTXConcat(pose->mtx, rot, pose->mtx);
                pose->flags &= ~2;
                if (pose->mtx[0][3] < -1000.0f) {
                    moa->state = 62;
                }
                break;
        }
        if (!(moa->flags & 0x588)) {
            if (cam->cameraAt.x - pose->mtx[0][3] > 250.0f) {
                x = 450.0f + pose->mtx[0][3];
                if (x < -50.0f) {
                    pose->mtx[0][3] = x;
                }
            } else if (pose->mtx[0][3] - cam->cameraAt.x > 250.0f) {
                x = pose->mtx[0][3] - 450.0f;
                if (x > -1870.0f) {
                    pose->mtx[0][3] = x;
                }
            }
        }
        if (!(moa->flags & 0x588)) {
            if (pose->mtx[0][3] > 100.0f) {
                pose->mtx[0][3] = 100.0f + randf(0.0f, 5.0f);
            }
            if (pose->mtx[0][3] < -1870.0f) {
                pose->mtx[0][3] = -1870.0f + randf(0.0f, 5.0f);
            }
            if (!(moa->flags & 0x40)) {
                if (pose->mtx[2][3] > 45.0f) {
                    pose->mtx[2][3] = 45.0f + randf(0.0f, 5.0f);
                }
                if (pose->mtx[2][3] < -45.0f) {
                    pose->mtx[2][3] = -45.0f + randf(0.0f, 5.0f);
                }
            }
        }
        moa->field_0x28 = pose->mtx[0][3];
        moa->field_0x2c = pose->mtx[2][3];
    }
    moamoa_pose_main();
    mario->unk174.x = 0.0f;
    mario->unk174.y = 0.0f;
    mario->unk174.z = 0.0f;
    if (!(wp->flags & 0x18)) {
        mario->unk174.x = -cnt / 20.0f;
    }
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
