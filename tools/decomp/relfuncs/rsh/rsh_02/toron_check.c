// include: mario/mario.h
// include: mario/mariost.h
// include: driver/npcdrv.h
// decl: NpcEntry* fbatHitCheckAll(void);
// proto: USER_FUNC(toron_check);
USER_FUNC(toron_check) {
    NpcEntry* hit = fbatHitCheckAll();
    // トロン
    NpcEntry* npc = npcNameToPtr("\x83\x67\x83\x8D\x83\x93");
    BOOL busy = FALSE;

    if (marioKeyOffChk() || marioCtrlOffChk()) {
        busy = TRUE;
    }
    if ((u32)marioStGetSystemLevel() != 0) {
        busy = TRUE;
    }
    if (npc == hit && !busy) {
        evtSetValue(event, LW(10), 1);
    } else {
        evtSetValue(event, LW(10), 0);
    }
    return EVT_RETURN_DONE;
}
