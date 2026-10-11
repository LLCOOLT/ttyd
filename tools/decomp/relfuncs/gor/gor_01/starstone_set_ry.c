// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// proto: static USER_FUNC(starstone_set_ry);
static USER_FUNC(starstone_set_ry) {
    char name[16];
    f32 ry = evtGetFloat(event, event->args[0]);
    s32 i;

    for (i = 0; i < 7; i++) {
        sprintf(name, "starstone%d", i);
        ((f32*)effNameToPtr(name)->userdata)[7] = ry;
    }
    return EVT_RETURN_DONE;
}
