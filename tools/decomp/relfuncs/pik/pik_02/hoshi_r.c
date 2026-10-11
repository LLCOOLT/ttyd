// include: driver/effdrv.h
// proto: USER_FUNC(hoshi_r);
USER_FUNC(hoshi_r) {
    EffectEntry* eff = (EffectEntry*)event->lwData[10];

    ((f32*)eff->userdata)[7] = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}
