// include: memory.h
// include: pmario_sound.h
// include: system.h
// include: dolphin/mtx.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
// decl: typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
// decl: typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
// decl: typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
// decl: FanWork* fan_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// decl: static void pose_init(void);
// decl: static void pose_change(Fan* fan, const char* name, const char* anim);
// decl: static f32 randf(f32 min, f32 max);
// decl: u8 psndSFX_get_vol(s32 id);
// proto: void ext_fan_init(void);
void ext_fan_init(void) {
    s32 i;
    ExtPose* pose;
    Fan* fan;

    fan_wp = _mapAlloc(sizeof(FanWork));
    memset(fan_wp, 0, sizeof(FanWork));
    fan_wp->num = extGetPoseNum();
    fan_wp->fans = _mapAlloc(fan_wp->num * sizeof(Fan));
    memset(fan_wp->fans, 0, fan_wp->num * sizeof(Fan));
    pose_init();
    pose = extGetPosePtr();
    fan = fan_wp->fans;
    for (i = 0; i < fan_wp->num; i++, pose++, fan++) {
        pose->flags |= 7;
        PSMTXIdentity(pose->mtx);
        pose->mtx[0][3] = 0.0f;
        pose->mtx[1][3] = 0.0f;
        pose->mtx[2][3] = 0.0f;
        pose->rot = randf(0.0f, 360.0f);
        switch (irand(1000) % 3) {
            case 0:
                pose_change(fan, "c_kinopio", "KNP_W_1");
                break;
            case 1:
                pose_change(fan, "c_kinopiko", "KNF_W_1");
                break;
            case 2:
            default:
                pose_change(fan, "c_jugemu", "JGM_W_1");
                break;
        }
        fan->state = 0;
        {
            Vec pos = {0.0f, 0.0f, 0.0f};

            pos.x = randf(-100.0f, 100.0f);
            pos.z = randf(-100.0f, 100.0f);
            fan->pos = pos;
            fan->vel = (Vec){0.0f, 0.0f, 0.0f};
        }
    }
    fan_wp->sfxId = psndSFXOn_3D("SFX_STG3_AUDIENCE_FAN1", &(Vec){0.0f, 0.0f, 0.0f});
    fan_wp->vol = psndSFX_get_vol(fan_wp->sfxId);
}
