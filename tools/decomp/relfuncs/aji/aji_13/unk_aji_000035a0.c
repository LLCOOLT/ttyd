// include: driver/hitdrv.h
// decl: BOOL hitIsGroup(HitEntry* target, HitEntry* group);
// proto: USER_FUNC(unk_aji_000035a0);
USER_FUNC(unk_aji_000035a0) {
    s32* args = event->args;
    const char* name1 = (const char*)evtGetValue(event, args[0]);
    const char* name2 = (const char*)evtGetValue(event, args[1]);
    HitEntry* hit1 = name1 != NULL ? hitNameToPtr(name1) : NULL;
    HitEntry* hit2 = name2 != NULL ? hitNameToPtr(name2) : NULL;

    if (hit1 != NULL && hit2 != NULL && hitIsGroup(hit1, hit2)) {
        evtSetValue(event, args[2], TRUE);
    } else {
        evtSetValue(event, args[2], FALSE);
    }
    return EVT_RETURN_DONE;
}
