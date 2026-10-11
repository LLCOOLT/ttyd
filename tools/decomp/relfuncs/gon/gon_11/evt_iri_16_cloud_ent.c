// include: string.h
// decl: typedef struct CloudWork { s32 used; s32 state; char animName[0x20]; char imgName[0x20]; char offscreenName[0x20]; char groupNames[8][0x20]; char hitName[0x20]; s32 limit; s32 counter; EventEntry* evt; void* endEvt; s32 timer; s32 x; s32 y; s32 w; s32 h; f32 lastFrame; } CloudWork;
// decl: static CloudWork* cloud;
// decl: extern s32 evt_cloud_main_evt[];
// proto: USER_FUNC(evt_iri_16_cloud_ent);
USER_FUNC(evt_iri_16_cloud_ent) {
    s32* args = event->args;
    char** groups;
    char* hitName;
    void* endEvt;
    CloudWork* wp;
    s32 i;
    s32 j;

    groups = (char**)evtGetValue(event, args[0]);
    hitName = (char*)evtGetValue(event, args[1]);
    endEvt = (void*)evtGetValue(event, args[2]);

    for (i = 0; i < 16; i++) {
        if (cloud[i].used == 0) {
            break;
        }
    }
    if (i >= 16) {
        return EVT_RETURN_DONE;
    }
    wp = &cloud[i];
    wp->used = 1;
    strcpy(wp->animName, "P_oof_cloud_1");
    for (j = 0; j < 8; j++) {
        if ((s8)groups[j][0] == 0) {
            break;
        }
        strcpy(wp->groupNames[j], groups[j]);
    }
    strcpy(wp->hitName, hitName);
    wp->endEvt = endEvt;
    wp->limit = 180;
    wp->counter = 0;
    wp->state = 0;
    wp->timer = 0;
    wp->evt = evtEntry(evt_cloud_main_evt, 0, 0);
    wp->evt->lwData[0] = (s32)wp;
    return EVT_RETURN_DONE;
}
