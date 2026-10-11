// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// decl: double sin(double);
// decl: double cos(double);
// proto: static USER_FUNC(starstone_set_pos);
static USER_FUNC(starstone_set_pos) {
    char name[16];
    s32* args = event->args;
    f32 x = evtGetFloat(event, args[0]);
    f32 y = evtGetFloat(event, args[1]);
    f32 z = evtGetFloat(event, args[2]);
    f32 phase = evtGetFloat(event, args[3]);
    f32 r = evtGetFloat(event, args[4]);
    f32 c;
    f32 angle;
    f32 s;
    EffectEntry* eff;
    s32 i;

    for (i = 0; i < 7; i++) {
        angle = 6.2831855f * i / 7.0f + phase;
        if (angle >= 6.2831855f) {
            angle -= 6.2831855f;
        }
        c = cos(angle);
        s = sin(angle);
        sprintf(name, "starstone%d", i);
        eff = effNameToPtr(name);
        ((f32*)eff->userdata)[2] = r * c + x;
        ((f32*)eff->userdata)[3] = y;
        ((f32*)eff->userdata)[4] = r * s + z;
    }
    return EVT_RETURN_DONE;
}
