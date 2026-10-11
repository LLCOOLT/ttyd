// include: driver/effdrv.h
// decl: double sin(double);
// decl: double cos(double);
// proto: USER_FUNC(disp_lighteffect_func);
USER_FUNC(disp_lighteffect_func) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    f32 ry = evtGetFloat(event, args[4]);
    EffectEntry* eff = effNameToPtr(name);
    f32 s;
    f32 c;
    f32 angle = 6.2831855f * -ry / 360.0f;

    s = sin(angle);
    c = cos(angle);
    ((f32*)eff->userdata)[1] = 30.0f * s + x;
    ((f32*)eff->userdata)[2] = y;
    ((f32*)eff->userdata)[3] = 30.0f * -c + z;
    return EVT_RETURN_DONE;
}
