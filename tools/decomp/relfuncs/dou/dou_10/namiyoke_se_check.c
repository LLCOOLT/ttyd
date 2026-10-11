// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// include: dolphin/mtx.h
// proto: USER_FUNC(namiyoke_se_check);
USER_FUNC(namiyoke_se_check) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    Vec pos;
    s32 dist;

    pos.x = x;
    pos.y = y;
    pos.z = z;
    dist = PSVECSquareDistance(&pos, &mario->position);
    if (dist < event->lwData[7]) {
        event->lwData[6] = event->lwData[10];
        event->lwData[7] = dist;
    }
    return EVT_RETURN_DONE;
}
