// include: driver/itemdrv.h
// include: manager/evtmgr_cmd.h
// include: system.h
// include: pmario_sound.h
// decl: static f32 cosf(f32 x);
// decl: static f32 sinf(f32 x);
// proto: USER_FUNC(item_jump);
USER_FUNC(item_jump) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    ItemEntry* item = itemNameToPtr("stone");
    f32 dy;
    f32 t;
    f32 vy;
    f32 angle;
    Vec pos;

    if (isFirstCall) {
        dy = y - item->position.y;
        t = distABf(x, z, item->position.x, item->position.z) / 1.0f;
        vy = dy / t + 0.5f * t * 0.5f;
        angle = angleABf(item->position.x, item->position.z, x, z);
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&angle;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    angle = event->userdataf[2];
    item->position.x += 1.0f * sinf(6.2831855f * angle / 360.0f);
    item->position.z -= 1.0f * cosf(6.2831855f * angle / 360.0f);
    item->position.y += vy;
    t -= 1.0f;
    vy -= 0.5f;
    if (t < 0.0f) {
        item->position.x = x;
        item->position.y = y;
        item->position.z = z;
        pos = (Vec){item->position.x, item->position.y, item->position.z};
        psndSFXOn_3D("SFX_EVT_STARSTONE_JUMP1", &pos);
        return EVT_RETURN_DONE;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return EVT_RETURN_BLOCK;
}
