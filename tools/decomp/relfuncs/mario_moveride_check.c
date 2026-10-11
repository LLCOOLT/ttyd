// include: mario/mario.h
// include: driver/hitdrv.h
// include: string.h
// proto: USER_FUNC(mario_moveride_check);
USER_FUNC(mario_moveride_check) {
    s32 i;
    const char* name;
    s32 anim;
    HitEntry* hit = marioGetPtr()->hitobjStandOn;

    name = NULL;
    for (i = 0; i < 17; i++) {
        if (hit != NULL && strcmp(hitGetName(hit), (const char*)hitname[i]) == 0) {
            name = (const char*)hitname[i];
            anim = mapanim[i];
            break;
        }
    }
    event->lwData[0] = 0;
    if (name != NULL && event->lwData[1] != (s32)name) {
        event->lwData[0] = anim;
    }
    event->lwData[1] = (s32)name;
    return EVT_RETURN_DONE;
}
