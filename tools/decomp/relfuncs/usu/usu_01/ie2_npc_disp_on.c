// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: USER_FUNC(ie2_npc_disp_on);
USER_FUNC(ie2_npc_disp_on) {
    const char* hide[] = {"\202\250\223X\202\314\211\234\202\263\202\361", "\203L\203U\226\354\230Y",
                          "\203u\203^\203L\203U\226\354\230Y", "\223X\202\314\216\345\220l", NULL};
    const char* show[] = {"\203y\203\211\226\202\220l", NULL};
    s32 i;

    for (i = 0; hide[i] != NULL; i++) {
        animPoseSetMaterialFlagOn(npcNameToPtr(hide[i])->poseId, 0x1800);
    }
    for (i = 0; show[i] != NULL; i++) {
        animPoseSetMaterialFlagOff(npcNameToPtr(show[i])->poseId, 0x1800);
    }
    return EVT_RETURN_DONE;
}
