// include: mario/mario.h
// include: driver/npcdrv.h
// include: string.h
// decl: NpcEntry* fbatNpcTalkCheck(void);
// proto: USER_FUNC(mario_flag);
USER_FUNC(mario_flag) {
    static BOOL flg;
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    NpcEntry* npc;

    marioGetPtr();
    npc = fbatNpcTalkCheck();
    if (npc != NULL) {
        strcpy(tmp, npc->description);
        flg = TRUE;
    }
    if (flg && strcmp(name, tmp) == 0) {
        evtSetValue(event, args[1], 1);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[1], 0);
    return EVT_RETURN_DONE;
}
