// decl: typedef struct ExtPose { s32 flags; f32 rot; s32 field_0x8; f32 (*mtx)[4]; s32 frame; u8 field_0x14[0x20 - 0x14]; } ExtPose;
// decl: typedef struct Chorobon { s16 flags; s16 state; s16 field_0x4; u8 field_0x6[2]; Vec target; f32 vy; s16 timer; u8 field_0x1a[2]; f32 speed; f32 gravity; s16 next; u8 field_0x26[0x30 - 0x26]; } Chorobon;
// decl: typedef struct ChorobonWork { s32 field_0x0; s32 count; Chorobon* chb; } ChorobonWork;
// decl: static ChorobonWork* wp;
// decl: ExtPose* extGetPosePtr(void);
// decl: void extReset(void);
// proto: USER_FUNC(evt_chorobon_wait);
USER_FUNC(evt_chorobon_wait) {
    ExtPose* pose = extGetPosePtr();
    Chorobon* chb = wp->chb;
    s32 i;

    for (i = 0; i < wp->count; i++, chb++) {
        if (chb->state != 99) {
            return EVT_RETURN_BLOCK;
        }
    }
    extReset();
    return EVT_RETURN_DONE;
}
