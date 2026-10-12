// include: memory.h
// include: string.h
// include: stdlib.h
// include: system.h
// include: mario/mariost.h
// include: pmario_sound.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct ExtAnimDef { const char* file; const char* name; f32 time; } ExtAnimDef;
// decl: typedef struct BomAnim { char name[8]; f32 time; s32 start; s32 count; } BomAnim;
// decl: typedef struct Bom { u8 state; u8 next; u8 pad_2[2]; Vec target; f32 field_0x10; f32 gravity; s16 timer; u8 pad_1a[2]; f32 vy; s32 anim; u8 pad_24[4]; OSTime time; } Bom;
// decl: typedef struct BomWork { u16 flags; u8 pad_2[2]; s32 count; BomAnim anims[8]; s32 animCount; u8 pad_ac[4]; Bom bom[1000]; } BomWork;
// decl: smartEntry* lp;
// decl: #define EXT_DATA ((ExtAnimDef*)ext_data)
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static inline f32 chb_sin(f32 x) { f32 a = 0.00761f; f32 b = 0.16605f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; a = a * x; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = a * y; a = -a; } return a; }
// decl: static inline f32 chb_cos(f32 x) { f32 a = 0.03705f; f32 b = 0.4967f; f32 c = 1.0f; f32 y; f32 x2; if (x <= 3.1415927f) { if (x <= 1.5707964f) { x2 = x * x; a = a * x2 - b; a = a * x2 + c; } else { y = 1.5707964f - (x - 1.5707964f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } } else if (x < 4.712389f) { y = x - 3.1415927f; x2 = y * y; a = a * x2 - b; a = a * x2 + c; a = -a; } else { y = 1.5707964f - (x - 4.712389f); x2 = y * y; a = a * x2 - b; a = a * x2 + c; } return a; }
// decl: double sin(double x);
// decl: void jump(s32 i, s32 next, f32 x, f32 y, f32 z, f32 speed, f32 gravity);
// decl: static void pose_main(void);
// proto: static void ext_main(void);
#pragma opt_propagation off
#pragma opt_lifetimes off
static void ext_main(void) {
    BomWork* wp = lp->address;
    ExtPose* pose = extGetPosePtr();
    s32 i;
    f32 angle;
    f32 dist;
    f32 speed;
    f32 gravity;
    f32 x;
    f32 z;
    f32 rad;
    Mtx m1;
    Mtx m2;
    Mtx m3;
    const char* se = "SFX_STG7_BOMB_FALL1";

    for (i = 0; i < wp->count; i++, pose++) {
        Vec center = {0.0f, 0.0f, 0.0f};
        Vec pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        Vec move = {0.0f, 0.0f, 0.0f};
        Vec dir;

        switch ((s8)wp->bom[i].state) {
            case 0:
                if (PSVECDistance(&center, &pos) > 280.0f) {
                    PSVECSubtract(&center, &pos, &dir);
                    PSVECNormalize(&dir, &dir);
                    PSVECScale(&dir, &move, 3.0f);
                    PSVECAdd(&pos, &move, &pos);
                    pose->mtx[0][3] = pos.x;
                    pose->mtx[1][3] = pos.y;
                    pose->mtx[2][3] = pos.z;
                    pose->rot = angleABf(0.0f, 0.0f, pos.x, pos.z);
                } else {
                    wp->bom[i].state++;
                }
                break;
            case 1:
                angle = 6.2831855f * rand() / 32767.0f;
                dist = 150.0f + 30.0f * rand() / 32767.0f;
                gravity = 0.1f + 0.1f * rand() / 32767.0f;
                speed = 3.0f + rand() / 32767.0f;
                z = dist * -chb_cos(angle);
                x = dist * chb_sin(angle);
                jump(i, 2, x, 150.0f, z, speed, gravity);
                break;
            case 2:
                angle = 6.2831855f * rand() / 32767.0f;
                dist = 50.0f + 30.0f * rand() / 32767.0f;
                gravity = 0.1f + 0.1f * rand() / 32767.0f;
                speed = 3.0f + rand() / 32767.0f;
                z = dist * -chb_cos(angle);
                x = dist * chb_sin(angle);
                jump(i, 3, x, 400.0f, z, speed, gravity);
                break;
            case 3:
                angle = 6.2831855f * rand() / 32767.0f;
                dist = 70.0f * rand() / 32767.0f;
                gravity = 0.1f + 0.0f * rand() / 32767.0f;
                speed = 3.0f + 0.0f * rand() / 32767.0f;
                z = dist * -chb_cos(angle);
                x = dist * chb_sin(angle) + (100.0f + i % 100);
                jump(i, 4, x, 350.0f + i % 150, z, speed, gravity);
                break;
            case 4:
                wp->bom[i].state++;
                break;
            case 5:
                break;
            case 100:
                pose->mtx[1][3] += wp->bom[i].vy;
                wp->bom[i].vy -= wp->bom[i].gravity;
                rad = 3.1415927f * angleABf(pose->mtx[0][3], pose->mtx[2][3], wp->bom[i].target.x, wp->bom[i].target.z) / 180.0f;
                pose->mtx[0][3] += wp->bom[i].field_0x10 * chb_sin(rad);
                pose->mtx[2][3] += wp->bom[i].field_0x10 * -chb_cos(rad);
                if (--wp->bom[i].timer < 0) {
                    pose->mtx[0][3] = wp->bom[i].target.x;
                    pose->mtx[1][3] = wp->bom[i].target.y;
                    pose->mtx[2][3] = wp->bom[i].target.z;
                    wp->bom[i].state = wp->bom[i].next;
                }
                break;
            case 127:
                if (pose->mtx[1][3] > -1000.0f) {
                    pose->mtx[1][3] = pose->mtx[1][3] - 2.0f;
                    pose->flags &= ~2;
                    PSMTXTrans(m1, 0.0f, -20.0f, 0.0f);
                    PSMTXRotRad(m2, 'z', 0.017453292f * (10.0f * (f32)sin((gp->retraceCount + i) / 100.0f)));
                    PSMTXTrans(m3, 0.0f, 20.0f, 0.0f);
                    PSMTXConcat(m1, m2, m2);
                    PSMTXConcat(m2, m3, m3);
                    PSMTXTrans(m1, pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]);
                    PSMTXConcat(m1, m3, pose->mtx);
                    if (irand(100) == 0) {
                        Vec p = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
                        psndSFXOn_3D(se, &p);
                    }
                }
                break;
        }
    }
    pose_main();
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
