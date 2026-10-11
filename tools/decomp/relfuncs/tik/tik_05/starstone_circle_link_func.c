// include: driver/effdrv.h
// decl: double sin(double);
// decl: double cos(double);
// proto: USER_FUNC(starstone_circle_link_func);
USER_FUNC(starstone_circle_link_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 idx = evtGetValue(event, args[1]) - 1;
    f32 x = evtGetFloat(event, args[2]);
    f32 y = evtGetFloat(event, args[3]);
    f32 z = evtGetFloat(event, args[4]);
    f32 ry = evtGetFloat(event, args[5]);
    f32 r = evtGetFloat(event, args[6]);
    EffectEntry* eff = effNameToPtr(name);
    f32 angle;
    f32 s;
    f32 c;

    ry = ry - 360.0f * ((s32)ry / 360);
    angle = 6.2831855f * (360.0f * idx / 7.0f + ry) / 360.0f;
    s = sin(angle);
    c = cos(angle);

    ((f32*)eff->userdata)[2] = s * r + x;
    ((f32*)eff->userdata)[3] = y;
    ((f32*)eff->userdata)[4] = -c * r + z;
    return EVT_RETURN_DONE;
}
