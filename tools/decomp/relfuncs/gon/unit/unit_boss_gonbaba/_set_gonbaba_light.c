// include: dolphin/mtx.h
// decl: u8* lightGetPaperCraft(void);
// proto: USER_FUNC(_set_gonbaba_light);
USER_FUNC(_set_gonbaba_light) {
    u8* light = lightGetPaperCraft();
    Mtx mtx;

    *(Vec*)(light + 0x24) = (Vec){-200.0f, 50.0f, 500.0f};
    PSMTXScale(mtx, 3.0f, 3.0f, 3.0f);
    PSMTXMultVec(mtx, (Vec*)(light + 0x24), (Vec*)(light + 0x24));
    return EVT_RETURN_DONE;
}
