// include: driver/itemdrv.h
// include: system.h
// include: stdio.h
// proto: USER_FUNC(item_chk);
USER_FUNC(item_chk) {
    char name[256];
    s32* args = event->args;
    f32 x = evtGetValue(event, GW(10));
    f32 z = evtGetValue(event, GW(11));
    f32 minDist = 20.0f;
    s32 i;
    ItemEntry* found = NULL;
    ItemEntry* item;

    for (i = 0; i < 32; i++) {
        sprintf(name, "keihin%02d", i);
        item = itemNameToPtr(name);
        if (item != NULL) {
            f32 dist = distABf(item->position.x, item->position.z, x, z);
            if (dist < minDist) {
                minDist = dist;
                found = item;
            }
        }
    }
    if (found != NULL) {
        evtSetValue(event, args[0], TRUE);
        evtSetValue(event, args[1], (s32)found->name);
    } else {
        evtSetValue(event, args[0], FALSE);
        evtSetValue(event, args[1], 0);
    }
    return EVT_RETURN_DONE;
}
