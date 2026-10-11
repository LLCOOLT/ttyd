// include: system.h
// include: mario/mario.h
// include: mario/mariost.h
// include: pmario_sound.h
// include: stdlib.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Chorobon { s16 flags; s16 state; s16 field_0x4; u8 field_0x6[2]; Vec target; f32 vy; s16 timer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[0x30 - 0x26]; } Chorobon;
// decl: typedef struct ChorobonWork { s32 field_0x0; s32 count; Chorobon* chb; } ChorobonWork;
// decl: static ChorobonWork* wp;
// decl: static inline f32 chb_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 chb_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// decl: ExtPose* extGetPosePtr(void);
// decl: static f32 randf(f32 min, f32 max);
// decl: void chb_jump(ExtPose* pose, Chorobon* chb, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
// decl: static inline f32 randf_scale(f32 r, f32 min, f32 max) { return r * (max - min) + min; }
// proto: static void ext_main(void);
#pragma opt_propagation off
#pragma opt_lifetimes off
static void ext_main(void) {
    MarioWork* mario = marioGetPtr();
    const char* sfx;
    s32 i;
    ExtPose* pose;
    Chorobon* chb;
    f32 angle;
    f32 dist;
    f32 rad;
    f32 x;
    f32 y;
    f32 z;
    f32 speed;
    f32 gravity;
    Vec pos;

    pose = extGetPosePtr();
    sfx = "SFX_STG1_CHORO_ESCAPE1";
    chb = wp->chb;
    for (i = 0; i < wp->count; i++, pose++, chb++) {
        switch (chb->state) {
            case 0:
                angle = rand() / 32767.0f;
                dist = randf(4.0f, 7.0f);
                rad = 3.1415927f * randf_scale(angle, 0.0f, 360.0f) / 180.0f;
                x = pose->mtx[0][3] + dist * chb_sin(rad);
                y = pose->mtx[1][3];
                z = pose->mtx[2][3] - dist * chb_cos(rad);
                speed = rand() / 32767.0f;
                gravity = rand() / 32767.0f;
                chb_jump(pose, chb, chb->state, x, y, z, randf_scale(speed, 0.3f, 0.5f), randf_scale(gravity, 0.5f, 0.8f));
                break;
            case 1:
                if (distABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]) < 800.0f) {
                    rad = rand() / 32767.0f;
                    angle = angleABf(mario->position.x, mario->position.z, pose->mtx[0][3], pose->mtx[2][3]);
                    angle = angle + randf_scale(rad, -45.0f, 45.0f);
                    dist = rand() / 32767.0f;
                    rad = 3.1415927f * angle / 180.0f;
                    dist = randf_scale(dist, 15.0f, 20.0f);
                    x = pose->mtx[0][3] + dist * chb_sin(rad);
                    y = pose->mtx[1][3];
                    z = pose->mtx[2][3] - dist * chb_cos(rad);
                    speed = rand() / 32767.0f;
                    gravity = rand() / 32767.0f;
                    speed = 2.0f * randf_scale(speed, 1.0f, 1.2f);
                    gravity = randf_scale(gravity, 0.8f, 0.8f);
                    chb_jump(pose, chb, chb->state, x, y, z, speed, gravity);
                    if (rand() % 150 == 0) {
                        pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
                        psndSFXOn_3D(sfx, &pos);
                    }
                } else {
                    chb->state = 99;
                }
                break;
            case 99:
                break;
            case 100:
                pose->mtx[1][3] += chb->vy;
                chb->vy -= chb->gravity;
                angle = angleABf(pose->mtx[0][3], pose->mtx[2][3], chb->target.x, chb->target.z);
                rad = 3.1415927f * angle / 180.0f;
                pose->mtx[0][3] += chb->speed * chb_sin(rad);
                pose->mtx[2][3] += chb->speed * -chb_cos(rad);
                if (--chb->timer < 0) {
                    pose->mtx[0][3] = chb->target.x;
                    pose->mtx[1][3] = chb->target.y;
                    pose->mtx[2][3] = chb->target.z;
                    chb->state = chb->next;
                }
                break;
        }
        switch (chb->state) {
            case 0:
                if (pose->mtx[0][3] > 230.0f) {
                    pose->mtx[0][3] = 230.0f;
                }
                if (pose->mtx[0][3] < -230.0f) {
                    pose->mtx[0][3] = -230.0f;
                }
                if (pose->mtx[2][3] > 100.0f) {
                    pose->mtx[2][3] = 100.0f;
                }
                if (pose->mtx[2][3] < -100.0f) {
                    pose->mtx[2][3] = -100.0f;
                }
                break;
        }
        if (gp->retraceCount & 1) {
            pose->frame = (gp->retraceCount + i) % 20;
        }
    }
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
