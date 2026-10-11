// include: manager/evtmgr_cmd.h
// include: driver/npcdrv.h
// include: mario/mario.h
// include: string.h
// decl: NpcEntry* fbatNpcTalkCheck(MarioWork* mario);
// proto: USER_FUNC(chk_marco_fuki);
USER_FUNC(chk_marco_fuki) {
    s32* args = event->args;
    NpcEntry* npc = fbatNpcTalkCheck(marioGetPtr());

    if (npc != NULL && strcmp(npc->description, "\203}\203\213\203R") == 0) {
        evtSetValue(event, args[0], 1);
        return EVT_RETURN_DONE;
    }
    evtSetValue(event, args[0], 0);
    return EVT_RETURN_DONE;
}
