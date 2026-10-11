// include: string.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Fan { u16 flags; s16 state; s16 animIdx; u8 pad_0x6[2]; u64 time; Vec pos; Vec vel; f32 field_0x28; Vec target; Vec param; s16 timer; } Fan;
// decl: typedef struct FanAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } FanAnim;
// decl: typedef struct FanWork { s32 num; Fan* fans; s32 animNum; FanAnim anim[32]; s32 hammerTimer; s32 count; s32 sfxId; u8 vol; } FanWork;
// decl: typedef struct FanData { const char* name; const char* anim; f32 rate; } FanData;
// decl: FanWork* fan_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: static void pose_init(void);
static void pose_init(void) {
    char name[32];
    char anim[32];
    FanData* d = (FanData*)ext_fan_data;
    s32 i = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    fan_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            fan_wp->animNum++;
        }
        strcpy(fan_wp->anim[fan_wp->animNum].name, name);
        strcpy(fan_wp->anim[fan_wp->animNum].anim, anim);
        fan_wp->anim[fan_wp->animNum].start = start;
        fan_wp->anim[fan_wp->animNum].count = i - start + 1;
        fan_wp->anim[fan_wp->animNum].rate = d->rate;
        fan_wp->anim[fan_wp->animNum].loop = 1;
        i++;
        d++;
    } while (d->name != NULL);
    fan_wp->animNum++;
}
