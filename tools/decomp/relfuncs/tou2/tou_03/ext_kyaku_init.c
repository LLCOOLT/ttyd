// include: mario/mariost.h
// include: memory.h
// include: string.h
// include: system.h
// include: driver/hitdrv.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Kyaku { u16 flags; u8 pad_0x2[2]; Vec pos; s16 animIdx; u8 pad_0x12[6]; u64 time; } Kyaku;
// decl: typedef struct KyakuAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } KyakuAnim;
// decl: typedef struct KyakuWork { s32 field_0x0; s32 num; Kyaku* kyakus; s32 animNum; KyakuAnim anim[32]; } KyakuWork;
// decl: typedef struct KyakuData { const char* name; const char* anim; f32 rate; } KyakuData;
// decl: KyakuWork* kyaku_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static void pose_init(void);
// decl: static void pose_change(Kyaku* kyaku, const char* name, const char* anim);
// decl: static f32 randf(f32 min, f32 max);
// decl: static f32 cosf(f32 x);
// decl: static f32 sinf(f32 x);
// decl: u32 __tou_rand(void);
// decl: void __tou_srand(u32 seed);
// proto: void ext_kyaku_init(void);
void ext_kyaku_init(void) {
    ExtPose* pose;
    Kyaku* kyaku;
    s32 i;
    s32 far;
    s32 side;
    f32 angle;
    f32 dist;
    f32 x;
    f32 z;
    f32 hx;
    f32 hy;
    f32 hz;
    f32 hd;
    f32 nx;
    f32 ny;
    f32 nz;

    kyaku_wp = _mapAlloc(sizeof(KyakuWork));
    memset(kyaku_wp, 0, sizeof(KyakuWork));
    kyaku_wp->num = extGetPoseNum();
    kyaku_wp->kyakus = _mapAlloc(kyaku_wp->num * sizeof(Kyaku));
    memset(kyaku_wp->kyakus, 0, kyaku_wp->num * sizeof(Kyaku));
    pose_init();
    __tou_srand(0x25B0E2B);
    pose = extGetPosePtr();
    kyaku = kyaku_wp->kyakus;
    for (i = 0; i < kyaku_wp->num; i++, pose++, kyaku++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        while (TRUE) {
            far = __tou_rand() % 100 >= 30;
            angle = randf(0.0f, 6.283184f);
            if (!far) {
                dist = randf(250.0f, 500.0f);
            } else {
                side = angle < 0.7853982f || angle > 5.4977875f;
                if (side) {
                    dist = randf(550.0f, 650.0f);
                } else {
                    dist = randf(550.0f, 850.0f);
                }
            }
            x = dist * sinf(angle);
            z = dist * cosf(angle);
            if (!far) {
                if (__fabs(z) <= 70.0) {
                    continue;
                }
                hd = 100000.0f;
                if (hitCheckFilter(NULL, &hx, &hy, &hz, &hd, &nx, &ny, &nz, x, 100.0f, z, 0.0f, -1.0f, 0.0f) == NULL) {
                    continue;
                }
                if (0.0f != hy) {
                    continue;
                }
                pose->mtx[0][3] = hx;
                pose->mtx[2][3] = hz;
                pose->rot = angleABf(0.0f, 0.0f, hx, hz);
            } else {
                hd = 100000.0f;
                if (hitCheckFilter(NULL, &hx, &hy, &hz, &hd, &nx, &ny, &nz, x, 500.0f, z, 0.0f, -1.0f, 0.0f) == NULL) {
                    continue;
                }
                pose->mtx[0][3] = hx;
                pose->mtx[1][3] = hy;
                pose->mtx[2][3] = hz;
                if (hz > 570.0f && __fabsf(hx) > 40.0f && __fabsf(hx) < 60.0f) {
                    pose->mtx[0][3] += hx > 0.0f ? -15 : 15;
                }
                pose->rot = angleABf(0.0f, 0.0f, hx, hz);
            }
            break;
        }
        if (strcmp(gp->beroEnterName, "s_bero_2") != 0 && pose->mtx[2][3] > 350.0f) {
            pose->flags &= ~1;
        }
        if (0.0f != pose->mtx[1][3]) {
            kyaku->flags |= 1;
        }
        kyaku->pos = (Vec){pose->mtx[0][3], pose->mtx[1][3], pose->mtx[2][3]};
        switch (irand(1000) % 4) {
            case 0:
                pose_change(kyaku, "c_kinopio", "KNP_S_1");
                break;
            case 1:
                pose_change(kyaku, "c_kinopiko", "KNF_S_1");
                break;
            case 2:
                pose_change(kyaku, "c_roten", "S_1");
                break;
            case 3:
                pose_change(kyaku, "c_jugemu", "JGM_S_1");
                break;
        }
    }
}
