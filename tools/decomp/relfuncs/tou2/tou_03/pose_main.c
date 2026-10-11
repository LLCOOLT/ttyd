// include: mario/mariost.h
// include: dolphin/os.h
// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Kyaku { u16 flags; u8 pad_0x2[2]; Vec pos; s16 animIdx; u8 pad_0x12[6]; u64 time; } Kyaku;
// decl: typedef struct KyakuAnim { char name[16]; char anim[8]; s16 loop; f32 rate; s32 start; s32 count; } KyakuAnim;
// decl: typedef struct KyakuWork { s32 field_0x0; s32 num; Kyaku* kyakus; s32 animNum; KyakuAnim anim[32]; } KyakuWork;
// decl: typedef struct KyakuData { const char* name; const char* anim; f32 rate; } KyakuData;
// decl: KyakuWork* kyaku_wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: s32 extGetPoseNum(void);
// proto: static void pose_main(void);
#pragma dont_inline on
static void pose_main(void) {
    s32 i;
    ExtPose* pose;
    Kyaku* kyaku;
    KyakuAnim* a;
    f32 t;

    pose = extGetPosePtr();
    kyaku = kyaku_wp->kyakus;

    for (i = 0; i < kyaku_wp->num; i++, kyaku++, pose++) {
        a = &kyaku_wp->anim[kyaku->animIdx];
        t = 60.0f * OSTicksToMilliseconds((u64)(gp->renderTime - kyaku->time)) / 1000.0f / a->rate;
        if (t >= 1.0f) {
            kyaku->time = gp->renderTime;
            t = 0.0f;
        }
        pose->frame = a->start + (s32)((a->count - 1) * t);
    }
}
#pragma dont_inline reset
