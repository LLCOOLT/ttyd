// include: driver/npcdrv.h
// include: driver/effdrv.h
// include: eff/eff_syuryou.h
// proto: USER_FUNC(syuryo_baria);
USER_FUNC(syuryo_baria) {
    // ピーチ単
    NpcEntry* npc = npcNameToPtr("\x83\x73\x81\x5B\x83\x60\x95\x50");
    EffectEntry* eff = effSyuryouEntry(1, 1000, npc->position.x, npc->position.y - 8.0f, 10.0f + npc->position.z);

    ((f32*)eff->userdata)[4] = 2.0f;
    effSetName(eff, "baria");
    return EVT_RETURN_DONE;
}
