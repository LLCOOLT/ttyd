// include: driver/itemdrv.h
// include: manager/evtmgr_cmd.h
// include: system.h
// include: pmario_sound.h
// decl: static f32 cosf(f32 x);
// decl: static f32 sinf(f32 x);
// proto: USER_FUNC(item_jump);
static inline s32 item_jump_sub(EventEntry* event, BOOL isFirstCall, f32 speed, f32 g) {
    s32* args = event->args;
    f32 z;
    f32 y;
    f32 x;
    ItemEntry* item;
    f32 angle;
    f32 dy;
    f32 t;
    f32 vy;

    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    item = itemNameToPtr("stone");
    if (isFirstCall) {
        dy = y - item->position.y;
        t = distABf(x, z, item->position.x, item->position.z) / speed;
        vy = dy / t + 0.5f * t * g;
        angle = angleABf(item->position.x, item->position.z, x, z);
        event->userdata[0] = *(s32*)&t;
        event->userdata[1] = *(s32*)&vy;
        event->userdata[2] = *(s32*)&angle;
    }
    t = event->userdataf[0];
    vy = event->userdataf[1];
    angle = event->userdataf[2];
    item->position.x += speed * sinf(6.2831855f * angle / 360.0f);
    item->position.z -= speed * cosf(6.2831855f * angle / 360.0f);
    item->position.y += vy;
    vy -= g;
    t -= speed;
    if (t < 0.0f) {
        item->position.x = x;
        item->position.y = y;
        item->position.z = z;
        {
            Vec zero = {0.0f, 0.0f, 0.0f};
            Vec tmp = {0.0f, 0.0f, 0.0f};
            Vec pos;

            tmp.x = item->position.x;
            tmp.y = item->position.y;
            tmp.z = item->position.z;
            pos = tmp;
            psndSFXOn_3D("SFX_EVT_STARSTONE_JUMP1", &pos);
        }
        return 1;
    }
    event->userdata[0] = *(s32*)&t;
    event->userdata[1] = *(s32*)&vy;
    return EVT_RETURN_BLOCK;
}

USER_FUNC(item_jump) {
    return item_jump_sub(event, isFirstCall, 1.0f, 0.5f);
}
