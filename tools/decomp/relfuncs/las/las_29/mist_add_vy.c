// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// proto: USER_FUNC(mist_add_vy);
USER_FUNC(mist_add_vy) {
    char name[16];
    f32 vy = evtGetFloat(event, event->args[0]);
    s32 i;

    for (i = 0; i < 10; i++) {
        sprintf(name, "mist%d", i);
        ((f32*)effNameToPtr(name)->userdata)[2] += vy;
    }
    return EVT_RETURN_DONE;
}
