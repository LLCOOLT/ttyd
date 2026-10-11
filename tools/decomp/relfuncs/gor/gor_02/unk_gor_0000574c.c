// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(unk_gor_0000574c);
USER_FUNC(unk_gor_0000574c) {
    s32* args = event->args;

    evtSetFloat(event, args[0], marioGetPtr()->unk1AC);
    return EVT_RETURN_DONE;
}
