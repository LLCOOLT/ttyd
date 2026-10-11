// include: driver/mapdrv.h
// proto: USER_FUNC(map_anim_flag_off);
USER_FUNC(map_anim_flag_off) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 mask = evtGetValue(event, args[1]);
    MapEntryAnimData* anim = mapSearchAnmObj(name);

    if (anim == NULL) {
        return EVT_RETURN_DONE;
    }
    anim->flags &= ~mask;
    return EVT_RETURN_DONE;
}
