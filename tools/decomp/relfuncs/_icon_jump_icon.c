// include: battle/battle.h
// include: manager/evtmgr_cmd.h
// include: driver/dispdrv.h
// include: driver/camdrv.h
// include: system.h
// decl: void btlMovePos(f32 speed, f32 angle, f32* x, f32* z);
// decl: typedef struct IconJumpWork { Vec start; Vec pos; Vec end; s32 frames; f32 speed; f32 gravity; f32 vy; u8 pad[0x7C - 0x34]; } IconJumpWork;
// decl: static void _disp_icon(CameraId camera, void* param);
// proto: USER_FUNC(_icon_jump_icon);
USER_FUNC(_icon_jump_icon) {
    s32* args = event->args;
    s32 icon = evtGetValue(event, args[0]);
    f32 x0 = evtGetFloat(event, args[1]);
    f32 y0 = evtGetFloat(event, args[2]);
    f32 z0 = evtGetFloat(event, args[3]);
    f32 x1 = evtGetFloat(event, args[4]);
    f32 y1 = evtGetFloat(event, args[5]);
    f32 z1 = evtGetFloat(event, args[6]);
    f32 gravity = evtGetFloat(event, args[7]);
    s32 frames = evtGetValue(event, args[8]);
    IconJumpWork* wk;

    if (isFirstCall) {
        Vec start;

        event->userdatap[0] = BattleAlloc(sizeof(IconJumpWork));
        wk = event->userdatap[0];
        wk->end.x = x1;
        wk->end.y = y1;
        wk->end.z = z1;
        start.x = x0;
        start.y = y0;
        start.z = z0;
        wk->pos = start;
        wk->start = start;
        wk->gravity = gravity;
        wk->frames = frames;
        wk->vy = (wk->end.y - wk->start.y) / wk->frames + wk->gravity * wk->frames / 2;
        wk->speed = distABf(wk->start.x, wk->start.z, wk->end.x, wk->end.z) / wk->frames;
        event->userdata[1] = icon;
        event->userdata[2] = 0;
    }
    wk = event->userdatap[0];
    if (event->userdata[2]) {
        BattleFree(wk);
        return EVT_RETURN_DONE;
    }
    wk->pos.y += wk->vy;
    wk->vy -= wk->gravity;
    if (wk->vy < 0.0f && wk->pos.y < wk->end.y) {
        wk->pos.y = wk->end.y;
    }
    btlMovePos(wk->speed, angleABf(wk->start.x, wk->start.z, wk->end.x, wk->end.z), &wk->pos.x, &wk->pos.z);
    wk->frames--;
    if (wk->frames <= 0) {
        event->userdata[2] = 1;
        wk->pos = wk->end;
    }
    dispEntry(CAMERA_3D, 900.0f, 1, _disp_icon, event);
    return EVT_RETURN_BLOCK;
}
