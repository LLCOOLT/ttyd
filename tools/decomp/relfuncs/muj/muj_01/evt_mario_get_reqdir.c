// include: mario/mario.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(evt_mario_get_reqdir);
USER_FUNC(evt_mario_get_reqdir) {
    s32* args = event->args;

    evtSetFloat(event, args[0], marioGetPtr()->unk1AC);
    return EVT_RETURN_DONE;
}
