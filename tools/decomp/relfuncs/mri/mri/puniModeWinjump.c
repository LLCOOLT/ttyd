// include: mario/mariost.h
// include: dolphin/os.h
// include: dolphin/mtx.h
// include: pmario_sound.h
// decl: typedef struct MriPuni { u8 field_0x0[0x4]; u32 flags; u32 flags2; u16 anim; u8 field_0xE[0x114 - 0xE]; u16 mode; s16 groupInit; s16 group; s16 order; s16 moveFlag; u8 field_0x11E[0x124 - 0x11E]; s32 field_0x124; u8 field_0x128[0x12C - 0x128]; Vec pos; u8 field_0x138[0x148 - 0x138]; f32 field_0x148; u8 field_0x14C[0x15C - 0x14C]; Vec vel; u8 field_0x168[0x174 - 0x168]; f32 field_0x174; u8 field_0x178[0x184 - 0x178]; f32 field_0x184; f32 field_0x188; u8 field_0x18C[0x190 - 0x18C]; f32 radius; u8 field_0x194[0x1A8 - 0x194]; f32 dist; u8 field_0x1AC[0x1C8 - 0x1AC]; OSTime time; struct MriPuni* parent; struct MriPuni* child; u8 field_0x1D8[0x1E4 - 0x1D8]; s32 field_0x1E4; u8 field_0x1E8[0x1EC - 0x1E8]; f32 baseY; f32 vy; f32 field_0x1F4; Vec field_0x1F8; u8 field_0x204[0x56C - 0x204]; void* modeFunc; void* moveFunc; s16 field_0x574; s16 field_0x576; u8 field_0x578[0x5A8 - 0x578]; } MriPuni;
// decl: MriPuni* puniGetPunidat(void);
// decl: void puniMoveDecel(MriPuni* puni);
// proto: void puniModeWinjump(MriPuni* puni);
void puniModeWinjump(MriPuni* puni) {
    s32 elapsed;
    f32 t;

    switch (puni->mode) {
        case 0:
            puni->time = gp->renderTime;
            puni->field_0x1E4 = 0;
            puni->baseY = puni->pos.y;
            puni->vy = -72.0f;
            puni->field_0x1F4 = -puni->vy;
            puni->mode = 1;
            psndSFXOn_3D("SFX_STG2_PUNI_JUMP1", &puni->pos);
        case 1:
            elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)puni->time);
            if (elapsed > 100 && puni->field_0x1E4 == 0) {
                puni->field_0x1E4 = 1;
                puni->field_0x124 = 0;
            }
            if (elapsed < 200) {
                t = elapsed / 200.0f;
                puni->pos.y = puni->baseY + t * (puni->vy * t + puni->field_0x1F4);
            } else {
                puni->pos.y = puni->baseY;
                puni->anim = 0x1B;
                puni->moveFlag = 1;
                puni->mode = 0;
            }
            break;
    }
}
