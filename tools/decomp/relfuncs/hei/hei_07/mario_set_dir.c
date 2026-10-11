// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// include: system.h
// proto: USER_FUNC(mario_set_dir);
USER_FUNC(mario_set_dir) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        event->userdataf[1] = mario->unk19C;
        event->userdataf[2] = evtGetFloat(event, args[0]) - event->userdataf[1];
        event->field_84 = evtGetValue(event, args[1]);
        mario->multiTimer = 0;
        if (event->userdataf[2] < -180.0f) {
            event->userdataf[2] = 360.0f + event->userdataf[2];
        }
        if (event->userdataf[2] > 180.0f) {
            event->userdataf[2] -= 360.0f;
        }
    }
    if ((s32)event->field_84 > 0) {
        mario->multiTimer++;
        mario->unk19C = reviseAngle(event->userdataf[1] + event->userdataf[2] * (s32)mario->multiTimer / (s32)event->field_84);
        return (s32)mario->multiTimer >= (s32)event->field_84;
    }
    mario->unk19C = reviseAngle(mario->unk19C + event->userdataf[2]);
    return EVT_RETURN_DONE;
}
