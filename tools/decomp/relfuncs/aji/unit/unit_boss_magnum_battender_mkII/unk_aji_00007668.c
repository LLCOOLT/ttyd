// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// decl: f32 intplGetValue(f32 start, f32 end, s32 mode, s32 cur, s32 steps);
// decl: u8 psndSFX_get_vol(s32 id);
// decl: void psndSFX_vol(s32 id, u8 vol);
// decl: u8 unk_aji_bss00000164;
// decl: u8 unk_aji_bss00000165;
// decl: s32 unk_aji_bss00000168;
// decl: s32 screamId;
// proto: USER_FUNC(unk_aji_00007668);
USER_FUNC(unk_aji_00007668) {
    if (isFirstCall) {
        unk_aji_bss00000168 = 120;
        unk_aji_bss00000165 = psndSFX_get_vol(screamId);
    }
    unk_aji_bss00000168--;
    unk_aji_bss00000164 = intplGetValue(unk_aji_bss00000165, 0.0f, 0, 120 - unk_aji_bss00000168, 120);
    psndSFX_vol(screamId, unk_aji_bss00000164);
    if (unk_aji_bss00000168 <= 0) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
