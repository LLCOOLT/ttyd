// include: manager/evtmgr_cmd.h
// include: driver/mapdrv.h
// include: mario/mariost.h
// include: dolphin/os.h
// decl: typedef struct YukaAnimData { u16 flags; u8 field_0x2[6]; OSTime time; f32 frame; f32 speed; struct { u8 field_0x0[8]; f32 length; }* data; } YukaAnimData;
// decl: typedef struct YukaAnim { YukaAnimData* anim; u32 flags; } YukaAnim;
// decl: YukaAnim yuka_anim;
// proto: USER_FUNC(yuka_anim_reverse_end);
USER_FUNC(yuka_anim_reverse_end) {
    yuka_anim.flags |= 2;
    return EVT_RETURN_DONE;
}
