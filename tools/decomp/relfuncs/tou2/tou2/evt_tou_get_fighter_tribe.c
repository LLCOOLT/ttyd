// include: tou2.h
// include: dolphin/types.h
// include: dolphin/mtx.h
// include: dolphin/gx.h
// include: driver/swdrv.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// include: driver/camdrv.h
// include: driver/effdrv.h
// include: driver/dispdrv.h
// include: driver/windowdrv.h
// include: driver/icondrv.h
// include: driver/msgdrv.h
// include: manager/fontmgr.h
// include: manager/evtmgr_cmd.h
// include: evt/evt_cmd.h
// include: battle/battle_monosiri.h
// include: data/mapdata.h
// include: mario/mario_pouch.h
// include: pmario_sound.h
// include: system.h
// include: memory.h
// include: string.h
// include: stdio.h
// note: tou2.c is hand-maintained (typed data/structs are defined there); this snippet mirrors it
// proto: USER_FUNC(evt_tou_get_fighter_tribe);
USER_FUNC(evt_tou_get_fighter_tribe) {
    s32* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 idx = evtGetValue(event, args[1]);
    s32 setupId = fighterDt[id].setupId;
    TattleEntry* tattle = battleGetUnitMonosiriPtr(btlsetup_tou_tbl[setupId].loadouts->group->units[idx].kind->type);
    NpcTribeInfo* tribe;
    const char* name;
    BOOL found = FALSE;

    for (tribe = npcTribe; tribe->nameJp != NULL; tribe++) {
        if (strcmp(tribe->modelName, tattle->modelName) == 0) {
            found = TRUE;
            break;
        }
    }
    if (!found) {
        name = "\x83\x4E\x83\x8A\x83\x7B\x81\x5B";
        tribe = npcGetTribe(name);
    } else {
        name = tribe->nameJp;
    }
    if (setupId == 2 && idx == 1) {
        name = "\x83\x70\x83\x5E\x83\x74\x83\x40\x83\x43\x83\x5E\x81\x5B";
        tribe = npcGetTribe(name);
    }
    if (setupId == 10 && idx == 1) {
        name = "\x83\x41\x83\x43\x83\x41\x83\x93\x83\x56\x83\x93\x83\x47\x83\x82\x83\x93\x32";
        tribe = npcGetTribe(name);
    }
    if (setupId == 13 && idx == 1) {
        name = "\x83\x45\x83\x89\x83\x70\x83\x5E";
        tribe = npcGetTribe(name);
    }
    if (setupId == 15 && idx == 2) {
        name = "\x83\x4A\x83\x81\x83\x62\x83\x4E\x97\xCE\x8B\xF3";
        tribe = npcGetTribe(name);
    }
    if (setupId == 11) {
        name = "\x83\x6E\x83\x43\x83\x70\x81\x5B\x83\x67\x83\x51\x83\x81\x83\x62\x83\x67";
        tribe = npcGetTribe(name);
    }
    evtSetValue(event, args[2], (s32)tribe->modelName);
    evtSetValue(event, args[3], (s32)name);
    return EVT_RETURN_DONE;
}
