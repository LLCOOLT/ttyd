// include: driver/effdrv.h
// proto: USER_FUNC(hoshi_delete);
USER_FUNC(hoshi_delete) {
    effSoftDelete((EffectEntry*)event->lwData[10]);
    return EVT_RETURN_DONE;
}
