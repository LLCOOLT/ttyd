// include: string.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Kyaku { u16 flags; u8 pad_0x2[2]; Vec pos; s16 animIdx; u8 pad_0x12[6]; u64 time; } Kyaku;
// decl: typedef struct KyakuAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } KyakuAnim;
// decl: typedef struct KyakuWork { s32 field_0x0; s32 num; Kyaku* kyakus; s32 animNum; KyakuAnim anim[32]; } KyakuWork;
// decl: typedef struct KyakuData { const char* name; const char* anim; f32 rate; } KyakuData;
// decl: KyakuWork* kyaku_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: static void pose_init(void);
#pragma dont_inline on
static void pose_init(void) {
    char name[32];
    char anim[32];
    KyakuData* d = (KyakuData*)ext_kyaku_data;
    s32 i = 0;
    s32 start;

    strcpy(name, "");
    strcpy(anim, "");
    kyaku_wp->animNum = -1;
    do {
        if (strcmp(d->name, name) != 0) {
            strcpy(name, d->name);
            strcpy(anim, "");
        }
        if (strcmp(d->anim, anim) != 0) {
            strcpy(anim, d->anim);
            start = i;
            kyaku_wp->animNum++;
        }
        strcpy(kyaku_wp->anim[kyaku_wp->animNum].name, name);
        strcpy(kyaku_wp->anim[kyaku_wp->animNum].anim, anim);
        kyaku_wp->anim[kyaku_wp->animNum].start = start;
        kyaku_wp->anim[kyaku_wp->animNum].count = i - start + 1;
        kyaku_wp->anim[kyaku_wp->animNum].rate = d->rate;
        kyaku_wp->anim[kyaku_wp->animNum].loop = 1;
        i++;
        d++;
    } while (d->name != NULL);
    kyaku_wp->animNum++;
}
#pragma dont_inline reset
