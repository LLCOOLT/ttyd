// decl: void mapGrpFlagOn(const char* name, u32 flags);
// decl: typedef struct SlotDrum { const char* drum[3]; const char* reber; const char* anim; const char* window[3][3]; const char* neon[3]; } SlotDrum;
// decl: #define DRUMNAME ((SlotDrum*)drumname)
// proto: void goryuugijo_upsidewindow_disp_sub(s32 slot, s32 reel);
void goryuugijo_upsidewindow_disp_sub(s32 slot, s32 reel) {
    mapGrpFlagOn(DRUMNAME[slot].window[reel][0], 1);
    mapGrpFlagOn(DRUMNAME[slot].window[reel][1], 1);
    mapGrpFlagOn(DRUMNAME[slot].window[reel][2], 1);
}
