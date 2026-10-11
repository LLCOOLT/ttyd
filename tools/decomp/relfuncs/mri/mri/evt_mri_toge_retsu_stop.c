// include: mario/mariost.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: pmario_sound.h
// decl: typedef struct MriPuni { u8 field_0x0[0x4]; u32 flags; u32 flags2; u16 anim; u8 field_0xE[0x114 - 0xE]; u16 mode; s16 groupInit; s16 group; s16 order; s16 moveFlag; u8 field_0x11E[0x124 - 0x11E]; s32 field_0x124; u8 field_0x128[0x12C - 0x128]; Vec pos; u8 field_0x138[0x148 - 0x138]; f32 field_0x148; u8 field_0x14C[0x15C - 0x14C]; Vec vel; u8 field_0x168[0x174 - 0x168]; f32 field_0x174; u8 field_0x178[0x184 - 0x178]; f32 field_0x184; f32 field_0x188; u8 field_0x18C[0x190 - 0x18C]; f32 radius; u8 field_0x194[0x1A8 - 0x194]; f32 dist; u8 field_0x1AC[0x1C8 - 0x1AC]; OSTime time; struct MriPuni* parent; struct MriPuni* child; u8 field_0x1D8[0x1E4 - 0x1D8]; s32 field_0x1E4; u8 field_0x1E8[0x1EC - 0x1E8]; f32 baseY; f32 vy; f32 field_0x1F4; Vec field_0x1F8; u8 field_0x204[0x56C - 0x204]; void* modeFunc; void* moveFunc; s16 field_0x574; s16 field_0x576; u8 field_0x578[0x5A8 - 0x578]; } MriPuni;
// decl: MriPuni* puniGetPunidat(void);
// decl: void puniMoveDecel(MriPuni* puni);
// proto: USER_FUNC(evt_mri_toge_retsu_stop);
USER_FUNC(evt_mri_toge_retsu_stop) {
    s32* args = event->args;
    s16 leader = evtGetValue(event, args[0]);
    s16 start = evtGetValue(event, args[1]);
    s16 end = evtGetValue(event, args[2]);
    s32 i;
    MriPuni* puni = &puniGetPunidat()[leader];

    puni->modeFunc = NULL;
    puni->moveFunc = NULL;
    puni->moveFlag = 0;
    puni->flags &= ~0x80000;
    for (i = start; i <= end; i++) {
        puni = &puniGetPunidat()[i];
        puni->modeFunc = NULL;
        puni->moveFunc = NULL;
        puni->moveFlag = 0;
        puni->flags &= ~0x80000;
    }
    return EVT_RETURN_DONE;
}
