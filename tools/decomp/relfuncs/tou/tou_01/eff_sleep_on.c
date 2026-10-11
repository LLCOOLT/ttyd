// include: driver/effdrv.h
// include: driver/npcdrv.h
// include: eff/eff_sleep.h
// proto: USER_FUNC(eff_sleep_on);
USER_FUNC(eff_sleep_on) {
    EffectEntry* eff = effNameToPtr("eff_sleep");
    NpcEntry* npc = npcNameToPtr_NoAssert("\202\275\202\334\202\262");

    if (eff == NULL) {
        effSetName(effSleepEntry(0, 0, npc->position.x, 16.0f + npc->position.y, npc->position.z, 1.0f, 65.0f),
                   "eff_sleep");
    }
    return EVT_RETURN_DONE;
}
