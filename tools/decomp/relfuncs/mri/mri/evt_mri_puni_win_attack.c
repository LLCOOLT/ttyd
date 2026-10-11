// include: mario/mariost.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: pmario_sound.h
// decl: typedef struct MriPuni { u8 field_0x0[0x4]; u32 flags; u32 flags2; u16 anim; u8 field_0xE[0x114 - 0xE]; u16 mode; s16 groupInit; s16 group; s16 order; s16 moveFlag; u8 field_0x11E[0x124 - 0x11E]; s32 field_0x124; u8 field_0x128[0x12C - 0x128]; Vec pos; u8 field_0x138[0x148 - 0x138]; f32 field_0x148; u8 field_0x14C[0x15C - 0x14C]; Vec vel; u8 field_0x168[0x174 - 0x168]; f32 field_0x174; u8 field_0x178[0x184 - 0x178]; f32 field_0x184; f32 field_0x188; u8 field_0x18C[0x190 - 0x18C]; f32 radius; u8 field_0x194[0x1A8 - 0x194]; f32 dist; u8 field_0x1AC[0x1C8 - 0x1AC]; OSTime time; struct MriPuni* parent; struct MriPuni* child; u8 field_0x1D8[0x1E4 - 0x1D8]; s32 field_0x1E4; u8 field_0x1E8[0x1EC - 0x1E8]; f32 baseY; f32 vy; f32 field_0x1F4; Vec field_0x1F8; u8 field_0x204[0x56C - 0x204]; void* modeFunc; void* moveFunc; s16 field_0x574; s16 field_0x576; u8 field_0x578[0x5A8 - 0x578]; } MriPuni;
// decl: MriPuni* puniGetPunidat(void);
// decl: void puniMoveDecel(MriPuni* puni);
// decl: typedef struct MriPuniWork { u8 field_0x0[0x43C]; s32 field_0x43C; u8 field_0x440[0x47C - 0x440]; s32 field_0x47C; f32 field_0x480; f32 field_0x484; f32 field_0x488; f32 field_0x48C; f32 field_0x490; f32 field_0x494; u8 field_0x498[0x4B0 - 0x498]; f32 field_0x4B0; f32 field_0x4B4; } MriPuniWork;
// decl: MriPuniWork* puniGetPunigp(void);
// decl: void PuniDokuritsu(MriPuni* puni);
// decl: void puniModeWinjump(MriPuni* puni);
// proto: USER_FUNC(evt_mri_puni_win_attack);
USER_FUNC(evt_mri_puni_win_attack) {
    s32* args = event->args;
    f32 x0 = evtGetValue(event, args[0]);
    f32 y0 = evtGetValue(event, args[1]);
    f32 z0 = evtGetValue(event, args[2]);
    f32 x1 = evtGetValue(event, args[3]);
    f32 y1 = evtGetValue(event, args[4]);
    f32 z1 = evtGetValue(event, args[5]);
    MriPuniWork* wp = puniGetPunigp();
    s32 i;

    wp->field_0x47C = 2;
    wp->field_0x480 = x0;
    wp->field_0x484 = y0;
    wp->field_0x488 = z0;
    wp->field_0x4B0 = 100.0f;
    wp->field_0x48C = x1;
    wp->field_0x490 = y1;
    wp->field_0x494 = z1;
    wp->field_0x4B4 = 100.0f;
    for (i = 1; i <= 102; i++) {
        MriPuni* puni = &puniGetPunidat()[i];
        if (puni->flags & 0x400) {
            PuniDokuritsu(puni);
            puni->moveFlag = 1;
            puni->mode = 0;
            if (puni->flags & 0x4000) {
                puni->flags &= ~0x4000;
                puni->anim = 0x1D;
                puni->modeFunc = puniModeWinjump;
                puni->moveFunc = puniMoveDecel;
            } else {
                puni->anim = 0x1B;
            }
        }
    }
    return EVT_RETURN_DONE;
}
