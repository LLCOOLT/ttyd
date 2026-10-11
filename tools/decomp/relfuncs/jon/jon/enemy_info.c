// include: driver/npcdrv.h
// include: manager/evtmgr_cmd.h
// include: string.h
// decl: extern NpcTribeInfo npcTribe[];
// decl: extern s32 enemy_100[];
// decl: typedef struct JonBtlSetup { const char* name; u8 pad[0x40]; } JonBtlSetup;
// proto: USER_FUNC(enemy_info);
USER_FUNC(enemy_info) {
    s32* args = event->args;
    s32 idx = evtGetValue(event, args[0]);
    s32 no = ((u8*)enemy_100)[idx];
    JonBtlSetup* setup = &((JonBtlSetup*)btlsetup_jon_tbl)[no];
    NpcTribeInfo* tribe = npcTribe;
    const char* name;
    BOOL found = FALSE;

    for (; tribe->nameJp != NULL; tribe++) {
        if (strcmp(tribe->nameJp, setup->name) == 0) {
            found = TRUE;
            break;
        }
    }
    if (!found) {
        // クリボー
        name = "\203N\203\212\203{\201[";
        tribe = npcGetTribe(name);
    } else {
        name = tribe->nameJp;
    }
    evtSetValue(event, args[1], (s32)tribe->modelName);
    evtSetValue(event, args[2], (s32)name);
    evtSetValue(event, args[3], no);
    return EVT_RETURN_DONE;
}
