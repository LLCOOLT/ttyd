// proto: USER_FUNC(_snow_control);
struct EffEntry* effSnowfallN64Entry(s32 type, s32 count);

USER_FUNC(_snow_control) {
    if (isFirstCall) {
        effSnowfallN64Entry(0, 64);
    }
    return EVT_RETURN_BLOCK;
}
