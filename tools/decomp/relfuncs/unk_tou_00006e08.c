// include: driver/effdrv.h
// include: driver/npcdrv.h
// proto: USER_FUNC(unk_tou_00006e08);
USER_FUNC(unk_tou_00006e08) {
    EffectEntry* eff = effNameToPtr("belt");
    // ベルト
    NpcEntry* npc = npcNameToPtr("\x83\x78\x83\x8B\x83\x67");

    ((s32*)eff->userdata)[14] = 7;
    npc->cameraId = 7;
    return EVT_RETURN_DONE;
}
