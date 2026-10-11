// include: driver/itemdrv.h
// include: mario/mariost.h
// include: manager/evtmgr_cmd.h
// include: system.h
// include: dolphin/os.h
// proto: USER_FUNC(muj_item_move_3d_position);
USER_FUNC(muj_item_move_3d_position) {
    s32* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    f32 x = evtGetValue(event, args[1]);
    f32 y = evtGetValue(event, args[2]);
    f32 z = evtGetValue(event, args[3]);
    s32 frames = evtGetValue(event, args[4]);
    s32 mode = evtGetValue(event, args[5]);
    f32 yOffset = evtGetFloat(event, args[6]);
    ItemEntry* item = itemNameToPtr(name);
    s32 elapsed;

    if (isFirstCall) {
        if (item == NULL) {
            return EVT_RETURN_DONE;
        }
        event->savedTime = gp->renderTime;
        event->userdataf[1] = item->position.x;
        event->userdataf[2] = item->position.y;
        *(f32*)&event->field_84 = item->position.z;
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - (u32)event->savedTime);
    if (elapsed < frames) {
        // the elapsed time is kept in the (dead) isFirstCall parameter
        isFirstCall = elapsed;
        item->position.x = intplGetValue(mode, isFirstCall, frames, event->userdataf[1], x);
        item->position.y = intplGetValue(mode, isFirstCall, frames, event->userdataf[2], y);
        item->position.z = intplGetValue(mode, isFirstCall, frames, *(f32*)&event->field_84, z);
        item->position.y += yOffset;
        return EVT_RETURN_BLOCK;
    }
    item->position.x = x;
    item->position.y = y;
    item->position.z = z;
    return EVT_RETURN_DONE;
}
