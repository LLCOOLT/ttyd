// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: mario/mario.h
// include: mario/mariost.h
// include: string.h
// decl: NpcEntry* marioGetTouchNpcPtr(void);
// proto: USER_FUNC(unk_gon_00000374);
USER_FUNC(unk_gon_00000374) {
    NpcEntry* npc = marioGetTouchNpcPtr();
    BOOL off = FALSE;

    if (marioKeyOffChk() || marioCtrlOffChk()) {
        off = TRUE;
    }
    if (marioStGetSystemLevel() != 0U) {
        off = TRUE;
    }
    if (npc != NULL && strcmp(npc->description, "\203\212\201[\203_\201[") == 0 && !off) {
        evtSetValue(event, LW(0), 1);
    } else {
        evtSetValue(event, LW(0), 0);
    }
    return EVT_RETURN_DONE;
}
