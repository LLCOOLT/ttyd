// include: mario/mario.h
// include: driver/hitdrv.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: USER_FUNC(muj_get_door_check);
USER_FUNC(muj_get_door_check) {
    s32* args = event->args;
    s32* door = (s32*)evtGetValue(event, args[0]);
    f32 range = evtGetFloat(event, args[1]);
    Vec hitPos;
    Vec marioPos;

    hitObjGetPos((const char*)door[5], &hitPos);
    marioPos = marioGetPtr()->position;
    marioPos.y = hitPos.y = 0.0f;
    if (PSVECDistance(&hitPos, &marioPos) > range) {
        evtSetValue(event, args[2], 0);
    } else {
        evtSetValue(event, args[2], 1);
    }
    return EVT_RETURN_DONE;
}
