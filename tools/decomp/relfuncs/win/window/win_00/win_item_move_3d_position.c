// include: driver/itemdrv.h
// include: mario/mariost.h
// include: manager/evtmgr_cmd.h
// include: system.h
// proto: USER_FUNC(win_item_move_3d_position);
USER_FUNC(win_item_move_3d_position) {
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
        event->userdata[0] = gp->renderTime;
        event->userdataf[1] = item->position.x;
        event->userdataf[2] = item->position.y;
        *(f32*)&event->field_84 = item->position.z;
    }
    elapsed = OSTicksToMilliseconds((u32)gp->renderTime - event->userdata[0]);
    if (elapsed < frames) {
        item->position.x = intplGetValue(mode, elapsed, frames, event->userdataf[1], x);
        item->position.y = yOffset + intplGetValue(mode, elapsed, frames, event->userdataf[2], y);
        item->position.z = intplGetValue(mode, elapsed, frames, *(f32*)&event->field_84, z);
        return EVT_RETURN_BLOCK;
    }
    item->position.x = x;
    item->position.y = y + yOffset;
    item->position.z = z;
    return EVT_RETURN_DONE;
}
