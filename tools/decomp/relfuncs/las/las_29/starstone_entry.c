// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// decl: double sin(double);
// decl: double cos(double);
// decl: EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// proto: static USER_FUNC(starstone_entry);
static USER_FUNC(starstone_entry) {
    char name[16];
    s32* args = event->args;
    f32 x;
    f32 z;
    f32 r;
    f32 c;
    f32 angle;
    f32 y;
    f32 s;
    EffectEntry* eff;
    s32 i;

    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    r = evtGetFloat(event, args[3]);
    for (i = 0; i < 7; i++) {
        angle = 6.2831855f * i / 7.0f;
        c = cos(angle);
        s = sin(angle);
        sprintf(name, "starstone%d", i);
        eff = effStarStoneEntry(i, r * c + x, y, r * s + z, 1.0f);
        effSetName(eff, name);
        *(u16*)((u8*)eff->userdata + 4) &= ~4;
    }
    return EVT_RETURN_DONE;
}
