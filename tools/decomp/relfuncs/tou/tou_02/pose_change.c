// include: string.h
// include: mario/mariost.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
// decl: typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
// decl: typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
// decl: typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
// decl: FanWork* fan_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: static void pose_change(Fan* fan, const char* name, const char* anim);
static void pose_change(Fan* fan, const char* name, const char* anim) {
    FanAnim* a;
    s32 i;

    for (i = 0, a = fan_wp->anim; i < fan_wp->animNum; i++, a++) {
        if (strcmp(a->name, name) == 0 && strcmp(a->anim, anim) == 0) {
            break;
        }
    }
    if (i < fan_wp->animNum && fan->animIdx != i) {
        fan->animIdx = i;
        fan->time = gp->renderTime;
    }
}
