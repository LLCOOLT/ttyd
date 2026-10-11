// include: driver/effdrv.h
// proto: USER_FUNC(reset_stone_cam);
USER_FUNC(reset_stone_cam) {
    EffectEntry* eff = effNameToPtr("nise");

    ((s32*)eff->userdata)[14] = 4;
    return EVT_RETURN_DONE;
}
