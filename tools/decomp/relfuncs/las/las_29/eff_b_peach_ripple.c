// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: eff/eff_ripple.h
// proto: USER_FUNC(eff_b_peach_ripple);
USER_FUNC(eff_b_peach_ripple) {
    NpcEntry* npc = npcNameToPtr("\203u\203\211\203b\203N\203s\201[\203`");

    effRippleSetRxRz(effRippleEntry(3, npc->position.x, 30.0f + npc->position.y, npc->position.z), 0.0f, 176.0f);
    return EVT_RETURN_DONE;
}
