// include: string.h
// include: memory.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: mario/mariost.h
// include: driver/mapdrv.h
// include: manager/evtmgr.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; f32 field_0x14; f32 field_0x18; f32 field_0x1c; } ExtPose;
// decl: typedef struct MoamoaPoseDef { char model[16]; char anim[8]; s16 loop; f32 speed; s32 start; s32 count; } MoamoaPoseDef;
// decl: typedef struct Moamoa { u16 flags; s16 state; s16 timer; u8 field_0x6[2]; Vec target; f32 vy; s16 jumpTimer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[2]; f32 field_0x28; f32 field_0x2c; u8 field_0x30[0x3c - 0x30]; s16 pose; u8 field_0x3e[2]; OSTime startTime; u8 field_0x48[4]; u8 kind; u8 field_0x4d[3]; } Moamoa;
// decl: typedef struct MoamoaWork { u16 flags; u8 field_0x2[2]; s32 count; Moamoa* moa; MapObject* mobj; f32 mobjY; Vec target[3]; s16 field_0x38; s16 field_0x3a[2]; s16 field_0x3e; s16 field_0x40; s16 field_0x42; EventEntry* escapeEvt; u8 field_0x48[0x4c - 0x48]; s32 numDefs; MoamoaPoseDef defs[32]; f32 angle; f32 dist; s32 field_0x558; f32 breathDir; f32 breathDist; Vec breathPos; u8 field_0x570[0x870 - 0x570]; } MoamoaWork;
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
// decl: static inline f32 moa_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 moa_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// include: mario/mario.h
// include: party.h
// include: party/party_cloud.h
// include: driver/camdrv.h
// include: pmario_sound.h
// include: system.h
// include: math.h
// decl: f32 cloudGetBreathDist(void);
// decl: static s32 moamoa_hit_check(ExtPose* pose, Moamoa* moa);
// decl: static void moamoa_jump(ExtPose* pose, Moamoa* moa, s32 next, s32 checkGround, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
// proto: static void ext_moamoa_main(void);
// decl: static inline f32 moa_sinx(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; a = -a; } return a; }
// decl: static inline f32 moa_cosx(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { x = 1.5707964f - (x - 1.5707964f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { x = x - 3.1415927f; x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = -a; } else { x = 1.5707964f - (x - 4.712389f); x2 = x * x; a = a * x2 - b; a = a * x2 + c; } return a; }
static void ext_moamoa_main(void) {
    MarioWork* mario;
    PartyEntry* party;
    s32 hit;
    const char* voice;
    s32 sfx;
    s32 i;
    ExtPose* pose;
    Moamoa* moa;
    s32 ret;
    s32 idx;
    f32 a;
    f32 s;
    f32 rad;
    f32 d;
    f32 x;
    f32 y;
    f32 z;
    f32 t;
    f32 r;
    Mtx m;
    Vec v;

    mario = marioGetPtr();
    party = partyGetPtr(0);
    camGetPtr(CAMERA_3D);
    hit = 0;
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
        wp->breathPos.x = wp->breathDist * moa_sinx(6.2831855f * wp->breathDir / 360.0f) + party->position.x;
        wp->breathPos.y = party->position.y;
        wp->breathPos.z = party->position.z - wp->breathDist * moa_cosx(6.2831855f * wp->breathDir / 360.0f);
    }
    if (wp->field_0x3a[0] > 50) {
        wp->target[0] = wp->target[1];
        if (!(wp->flags & 0x1000)) {
            wp->flags |= 0x1000;
            evtEntry(evt_moamoa_escape0, 0, 0);
        }
    }
    if (wp->field_0x3a[1] > 50) {
        wp->target[1] = wp->target[0];
        if (!(wp->flags & 0x2000)) {
            wp->flags |= 0x2000;
            evtEntry(evt_moamoa_escape1, 0, 0);
        }
    }
    if ((wp->flags & 0x1000) && (wp->flags & 0x2000)) {
        s32 j;
        Moamoa* m2;

        extGetPosePtr();
        m2 = wp->moa;
        for (j = 0; j < wp->count; j++, m2++) {
            if (m2->flags & 4) {
                continue;
            }
            if (m2->flags & 0x10) {
                break;
            }
            m2->state = 0x19;
            m2->timer = 0;
            m2->flags |= 0x10;
        }
        if (wp->escapeEvt == NULL) {
            wp->escapeEvt = evtEntry(evt_moamoa_escape, 0, 0);
        }
    }

    pose = extGetPosePtr();
    voice = "SFX_STG6_MOAMOA_VOICE1";
    sfx = 0;
    moa = wp->moa;
    for (i = 0; i < wp->count; i++, pose++, moa++) {
        wp->angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        wp->dist = distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
        if ((wp->flags & 1) && !(wp->flags & 4) && !marioKeyOffChk() && !marioCtrlOffChk() && !hit && !(moa->flags & 0x154)) {
            ret = moamoa_hit_check(pose, moa);
            if (ret == 1) {
                moa->flags |= 4;
                moa->state = 0x24;
                idx = i % 3;
                wp->field_0x38++;
                if (distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[idx].x, wp->target[idx].z) < 200.0f) {
                    wp->field_0x3a[idx]++;
                }
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                hit = 1;
            } else if (ret == 2 || ret == 4) {
                moa->flags |= 0xc;
                moa->state = 0x2f;
                idx = i % 3;
                wp->field_0x38++;
                if (distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[idx].x, wp->target[idx].z) < 200.0f) {
                    wp->field_0x3a[idx]++;
                }
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                if (ret != 4) {
                    hit = 1;
                }
            } else if (ret == 3) {
                moa->flags |= 0x84;
                moa->state = 0x30;
                a = (wp->breathDir + wp->angle) * 0.5f;
                moa->target = (Vec){0.0f, 0.0f, 0.0f};
                s = randf(0.1f, 0.2f);
                rad = 6.2831855f * a / 360.0f;
                moa->vy = s * moa_sinx(rad);
                moa->speed = randf(0.03f, 0.06f);
                moa->gravity = s * -moa_cosx(rad);
                moa->jumpTimer = 120;
                idx = i % 3;
                wp->field_0x38++;
                if (distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[idx].x, wp->target[idx].z) < 200.0f) {
                    wp->field_0x3a[idx]++;
                }
                moamoa_pose_change(moa, "c_n_moa_a", "D_1");
                hit = 1;
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x155) && wp->dist < 50.0f) {
            if (moa->flags & 2) {
                moa->next = 1;
            } else {
                moa->state = 1;
            }
        }
        if ((wp->flags & 1) && !(moa->flags & 0x444) && i == gp->retraceCount % wp->count && irand(1000) < 200) {
            psndSFXOn_3D(voice, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
        }
        switch (moa->state) {
            case 0:
                if (i % 133 < 100) {
                    a = randf(0.0f, 6.2831855f);
                    d = randf(0.0f, 50.0f);
                    x = wp->target[i % 3].x + d * moa_sinx(a);
                    z = wp->target[i % 3].z - d * moa_cosx(a);
                    rad = 6.2831855f * angleABf(pose->mtx[0][3], pose->mtx[2][3], x, z) / 360.0f;
                    x = pose->mtx[0][3] + 15.0f * moa_sinx(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - 15.0f * moa_cosx(rad);
                    s = randf(1.5f, 3.0f);
                    moamoa_jump(pose, moa, moa->state, 1, x, y, z, s, randf(0.8f, 2.0f));
                    moa->flags |= 1;
                } else {
                    d = distABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                    a = angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->target[i % 3].x, wp->target[i % 3].z);
                    if (d < 200.0f) {
                        a = randf(0.0f, 360.0f);
                    }
                    rad = 6.2831855f * a / 360.0f;
                    x = pose->mtx[0][3] + 5.0f * moa_sinx(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - 5.0f * moa_cosx(rad);
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
                    t = 1.0f;
                } else {
                    t = (800 - moa->timer) / 600.0f;
                }
                if (t < 0.0f) {
                    t = 0.0f;
                    moa->flags |= 0x200;
                }
                x = wp->target[i % 3].x;
                y = wp->target[i % 3].y;
                z = wp->target[i % 3].z;
                x += t * (moa->gravity * (f32)sin((f32)(i + gp->retraceCount) * 0.25f));
                y += moa->speed * t;
                z += t * (-moa->gravity * (f32)cos((f32)(i + gp->retraceCount) * 0.25f));
                pose->mtx[0][3] += (x - pose->mtx[0][3]) / 15.0f;
                pose->mtx[1][3] += (y - pose->mtx[1][3]) / 15.0f;
                pose->mtx[2][3] += (z - pose->mtx[2][3]) / 15.0f;
                moa->timer++;
                break;
            case 1:
                a = wp->angle + randf(-45.0f, 45.0f);
                d = wp->dist;
                rad = 6.2831855f * a / 360.0f;
                x = pose->mtx[0][3] + 15.0f * moa_sinx(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - 15.0f * moa_cosx(rad);
                moamoa_jump(pose, moa, d < 100.0f ? moa->state : 0, 1, x, y, z, randf(1.0f, 1.0f), randf(0.4f, 0.4f));
                break;
            case 2:
                a = wp->angle + randf(-45.0f, 45.0f) + 180.0f;
                d = wp->dist;
                rad = 6.2831855f * a / 360.0f;
                x = pose->mtx[0][3] + 30.0f * moa_sinx(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - 30.0f * moa_cosx(rad);
                moamoa_jump(pose, moa, d < 100.0f ? moa->state : 0, 1, x, y, z, 2.0f * randf(1.0f, 1.0f), 2.0f * randf(0.4f, 0.4f));
                break;
            case 3:
                pose->mtx[1][3] += moa->vy;
                moa->vy -= moa->gravity;
                rad = 6.2831855f * angleABf(pose->mtx[0][3], pose->mtx[2][3], moa->target.x, moa->target.z) / 360.0f;
                pose->mtx[0][3] += moa->speed * moa_sinx(rad);
                pose->mtx[2][3] += moa->speed * -moa_cosx(rad);
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
                r = randf(-45.0f, 45.0f);
                rad = 6.2831855f * (angleABf(x, z, pose->mtx[0][3], pose->mtx[2][3]) + r) / 360.0f;
                x = pose->mtx[0][3] + 15.0f * moa_sinx(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - 15.0f * moa_cosx(rad);
                moamoa_jump(pose, moa, moa->state + 1, 1, x, y, z, randf(1.0f, 1.0f), randf(1.0f, 1.0f));
                break;
            case 39:
                if (++moa->timer < 30) {
                    pose->mtx[0][0] *= 0.9f;
                    pose->mtx[1][1] *= 0.9f;
                    pose->mtx[2][2] *= 0.9f;
                } else {
                    moa->state = 0x31;
                }
                break;
            case 47:
                rad = 6.2831855f * randf(135.0f, 225.0f) / 360.0f;
                d = randf(300.0f, 500.0f);
                x = pose->mtx[0][3] + d * moa_sinx(rad);
                z = pose->mtx[2][3] - d * moa_cosx(rad);
                a = randf(5.0f, 6.0f);
                s = randf(0.2f, 0.3f);
                if (!sfx) {
                    psndSFXOn_3D((const char*)0x6c3, &(Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]});
                    sfx = 1;
                }
                moamoa_jump(pose, moa, 0x31, 0, x, -100.0f, z, a, s);
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
                    moa->state = 0x31;
                }
                break;
            case 49:
                if ((wp->flags & 0x1000) && (wp->flags & 0x2000)) {
                    moa->state = 0x3e;
                } else if (wp->field_0x38 < 500) {
                    PSMTXIdentity(pose->mtx);
                    pose->mtx[0][3] = wp->target[i % 3].x;
                    pose->mtx[1][3] = wp->target[i % 3].y;
                    pose->mtx[2][3] = wp->target[i % 3].z;
                    moa->flags = 0;
                    moa->state = 0;
                    moa->timer = 0;
                } else {
                    moa->state = 0x3e;
                }
                break;
            case 25:
                if (moa->timer < 30) {
                    PSMTXRotRad(m, 'y', 0.20943952f);
                    PSMTXConcat(m, pose->mtx, pose->mtx);
                    pose->flags &= ~2;
                    moa->timer++;
                } else {
                    pose->flags |= 2;
                    moa->timer = rand() % 30;
                    moa->state++;
                }
                break;
            case 26:
                if (--moa->timer < 0) {
                    moa->timer = 0;
                    moa->state++;
                }
                break;
            case 27:
                d = distABf(pose->mtx[0][3], pose->mtx[2][3], -275.0f, -100.0f);
                r = randf(-45.0f, 45.0f);
                a = angleABf(pose->mtx[0][3], pose->mtx[2][3], -275.0f, -100.0f) + r;
                if (d > 6.0f && (y = pose->mtx[1][3]) < 60.0f) {
                    rad = 6.2831855f * a / 360.0f;
                    x = pose->mtx[0][3] + 15.0f * moa_sinx(rad);
                    z = pose->mtx[2][3] - 15.0f * moa_cosx(rad);
                    moamoa_jump(pose, moa, moa->state, 1, x, y, z, 3.0f * randf(1.0f, 1.0f), randf(1.0f, 1.0f));
                } else {
                    moa->state++;
                }
                break;
            case 28:
                if (pose->mtx[0][3] > -350.0f) {
                    r = randf(-45.0f, 45.0f);
                    rad = 6.2831855f * (angleABf(pose->mtx[0][3], pose->mtx[2][3], -350.0f, -100.0f) + r) / 360.0f;
                    x = pose->mtx[0][3] + 15.0f * moa_sinx(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - 15.0f * moa_cosx(rad);
                    moamoa_jump(pose, moa, moa->state, 1, x, y, z, 3.0f * randf(1.0f, 1.0f), randf(1.0f, 1.0f));
                } else {
                    moa->state = 0x3e;
                }
                break;
            case 62:
                moa->flags |= 0x20;
                pose->flags &= ~1;
                pose->flags |= 4;
                break;
            case 63:
                a = randf(225.0f, 315.0f);
                s = randf(2.0f, 3.0f);
                moa->timer = irand(i / 2);
                rad = 6.2831855f * a / 360.0f;
                moa->target.x = s * moa_sinx(rad);
                moa->target.y = randf(1.0f, 2.0f);
                moa->target.z = s * -moa_cosx(rad);
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
                PSMTXRotRad(m, 'y', 0.20943952f);
                PSMTXConcat(m, pose->mtx, pose->mtx);
                pose->flags &= ~2;
                if (pose->mtx[0][3] < -1000.0f) {
                    moa->state = 0x3e;
                }
                break;
        }
        if (!(moa->flags & 0x98)) {
            if (pose->mtx[0][3] > 290.0f) {
                pose->mtx[0][3] = 290.0f;
            }
            if (pose->mtx[0][3] < -290.0f) {
                pose->mtx[0][3] = -290.0f;
            }
            if (pose->mtx[2][3] > 50.0f) {
                pose->mtx[2][3] = 50.0f;
            }
            if (pose->mtx[2][3] < -130.0f) {
                pose->mtx[2][3] = -130.0f;
            }
        }
        pose->mtx[1][3] += wp->mobj->modelWorldMtx[1][3] - wp->mobjY;
        moa->field_0x28 = pose->mtx[0][3];
        moa->field_0x2c = pose->mtx[2][3];
    }
    moamoa_pose_main();
    wp->mobjY = wp->mobj->modelWorldMtx[1][3];
    if (wp->flags & 0x10) {
        mario->unk174.x = 0.0f;
        mario->unk174.y = 0.0f;
        mario->unk174.z = 0.0f;
    } else {
        v = (Vec){mario->unk174.x, mario->unk174.y, mario->unk174.z};
        if (PSVECMag(&v) > 2.0f) {
            PSVECNormalize(&v, &v);
            mario->unk174 = (Vec){2.0f * v.x, 2.0f * v.y, 2.0f * v.z};
        }
    }
}
