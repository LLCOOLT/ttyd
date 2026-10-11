// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(mario_shabon_effpos);
USER_FUNC(mario_shabon_effpos) {
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);

    ((f32*)marioeff->userdata)[1] = x;
    ((f32*)marioeff->userdata)[2] = y;
    ((f32*)marioeff->userdata)[3] = z;
    return EVT_RETURN_DONE;
}
