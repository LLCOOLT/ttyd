// include: manager/evtmgr_cmd.h
// include: driver/mapdrv.h
// include: mario/mariost.h
// include: dolphin/os.h
// decl: typedef struct YukaAnimData { u16 flags; u8 field_0x2[6]; OSTime time; f32 frame; f32 speed; struct { u8 field_0x0[8]; f32 length; }* data; } YukaAnimData;
// decl: typedef struct YukaAnim { YukaAnimData* anim; u32 flags; } YukaAnim;
// decl: YukaAnim yuka_anim;
// decl: #define YUKA_NOW() OSTicksToMilliseconds(gp->inBattle ? gp->renderTime : gp->renderFieldTime)
// proto: USER_FUNC(yuka_anim_reverse_play);
USER_FUNC(yuka_anim_reverse_play) {
    f32 frame;

    if (isFirstCall) {
        yuka_anim.anim = (YukaAnimData*)mapSearchAnmObj("yuka");
        yuka_anim.flags = 0;
        yuka_anim.anim->time = YUKA_NOW();
        yuka_anim.anim->flags |= 0x10;
        yuka_anim.anim->flags &= ~0x20;
    }
    if (yuka_anim.flags & 2) {
        return EVT_RETURN_DONE;
    }
    if (!(yuka_anim.flags & 1)) {
        {
            f32 dt = 60.0f * (f32)(u64)(YUKA_NOW() - yuka_anim.anim->time) / 1000.0f;

            yuka_anim.anim->frame -= dt * yuka_anim.anim->speed;
        }
        if (yuka_anim.anim->frame <= 0.0f) {
            for (frame = yuka_anim.anim->frame; frame < 0.0f; frame += yuka_anim.anim->data->length) {
            }
            yuka_anim.anim->frame = frame;
        }
    }
    yuka_anim.anim->time = YUKA_NOW();
    return EVT_RETURN_BLOCK;
}
