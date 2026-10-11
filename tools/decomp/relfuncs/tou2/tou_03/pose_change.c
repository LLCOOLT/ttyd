// include: string.h
// include: stdlib.h
// include: mario/mariost.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Kyaku { u16 flags; u8 pad_0x2[2]; Vec pos; s16 animIdx; u8 pad_0x12[6]; u64 time; } Kyaku;
// decl: typedef struct KyakuAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } KyakuAnim;
// decl: typedef struct KyakuWork { s32 field_0x0; s32 num; Kyaku* kyakus; s32 animNum; KyakuAnim anim[32]; } KyakuWork;
// decl: typedef struct KyakuData { const char* name; const char* anim; f32 rate; } KyakuData;
// decl: KyakuWork* kyaku_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: static void pose_change(Kyaku* kyaku, const char* name, const char* anim);
static void pose_change(Kyaku* kyaku, const char* name, const char* anim) {
    KyakuAnim* a;
    s32 i;

    for (i = 0, a = kyaku_wp->anim; i < kyaku_wp->animNum; i++, a++) {
        if (strcmp(a->name, name) == 0 && strcmp(a->anim, anim) == 0) {
            break;
        }
    }
    if (i < kyaku_wp->animNum && kyaku->animIdx != i) {
        kyaku->animIdx = i;
        kyaku->time = gp->renderTime + rand();
    }
}
