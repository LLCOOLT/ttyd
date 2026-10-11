// include: memory.h
// proto: USER_FUNC(unk_gor_0000050c);
USER_FUNC(unk_gor_0000050c) {
    if (unk_gor_bss00000000 == NULL) {
        return EVT_RETURN_DONE;
    }
    _mapFree(unk_gor_bss00000000);
    unk_gor_bss00000000 = NULL;
    return EVT_RETURN_DONE;
}
