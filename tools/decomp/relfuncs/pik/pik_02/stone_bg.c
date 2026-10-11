// include: driver/effdrv.h
// include: mario/mario.h
// proto: static USER_FUNC(stone_bg);
static USER_FUNC(stone_bg) {
    EffectEntry* eff;

    eff = effNameToPtr("sub_bg");
    ((s32*)eff->userdata)[14] = 5;
    eff = effNameToPtr("nise");
    ((s32*)eff->userdata)[14] = 5;
    marioSetCamId(5);
    return EVT_RETURN_DONE;
}
