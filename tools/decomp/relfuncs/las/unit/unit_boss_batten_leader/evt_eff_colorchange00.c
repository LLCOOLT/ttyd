// include: driver/effdrv.h
// proto: USER_FUNC(evt_eff_colorchange00);
USER_FUNC(evt_eff_colorchange00) {
    EffectEntry* eff = effNameToPtr((const char*)evtGetValue(event, event->args[0]));

    ((s32*)eff->userdata)[6] = 255;
    ((s32*)eff->userdata)[7] = 255;
    ((s32*)eff->userdata)[8] = 255;
    ((s32*)eff->userdata)[10] = 255;
    ((s32*)eff->userdata)[11] = 245;
    ((s32*)eff->userdata)[12] = 0;
    ((f32*)eff->userdata)[2] = 65.0f + ((f32*)eff->userdata)[2];
    ((f32*)eff->userdata)[3] = 10.0f + ((f32*)eff->userdata)[3];

    return EVT_RETURN_DONE;
}
