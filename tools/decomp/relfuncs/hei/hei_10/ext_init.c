// include: memory.h
// include: string.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Chorobon { s16 flags; s16 state; s16 field_0x4; u8 field_0x6[2]; Vec target; f32 vy; s16 timer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[0x30 - 0x26]; } Chorobon;
// decl: typedef struct ChorobonWork { s32 field_0x0; s32 count; Chorobon* chb; } ChorobonWork;
// decl: static ChorobonWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static f32 randf(f32 min, f32 max);
// proto: static void ext_init(void);
static void ext_init(void) {
    s32 i;
    ExtPose* pose;
    Chorobon* chb;

    wp = _mapAlloc(sizeof(ChorobonWork));
    memset(wp, 0, sizeof(ChorobonWork));
    wp->count = extGetPoseNum();
    wp->chb = _mapAlloc(wp->count * sizeof(Chorobon));
    memset(wp->chb, 0, wp->count * sizeof(Chorobon));
    pose = extGetPosePtr();
    chb = wp->chb;
    for (i = 0; i < wp->count; i++, pose++, chb++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = randf(-230.0f, 230.0f);
        pose->mtx[1][3] = -15.0f;
        pose->mtx[2][3] = randf(-100.0f, 100.0f);
        chb->flags = 0;
        chb->state = 0;
        chb->field_0x4 = 0;
    }
}
