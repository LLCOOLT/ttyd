// include: pmario_sound.h
// decl: static s32 unk_gor_bss00000004;
// decl: static char* unk_gor_bss00000000;
// proto: USER_FUNC(unk_gor_000000cc);
USER_FUNC(unk_gor_000000cc) {
    if (unk_gor_bss00000004 != -1) {
        psndSFXOff(unk_gor_bss00000004);
    }
    return EVT_RETURN_DONE;
}
