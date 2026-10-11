// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(peach_evt_toumei_onoff);
USER_FUNC(peach_evt_toumei_onoff) {
    s32* args = event->args;
    MarioWork* mario = marioGetPtr();

    if (evtGetValue(event, args[0])) {
        mario->scale.x = 0.0f;
        mario->scale.y = 0.0f;
        mario->scale.z = 0.0f;
    } else {
        mario->scale.x = 1.0f;
        mario->scale.y = 1.0f;
        mario->scale.z = 1.0f;
    }
    return EVT_RETURN_DONE;
}
