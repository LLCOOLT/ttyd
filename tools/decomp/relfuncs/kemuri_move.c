// include: driver/effdrv.h
// include: manager/evtmgr_cmd.h
// proto: USER_FUNC(kemuri_move);
USER_FUNC(kemuri_move) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    f32 dy = evtGetFloat(event, args[1]);
    EffectEntry* eff = effNameToPtr(name);

    if (eff == NULL) {
        return EVT_RETURN_DONE;
    }
    if (isFirstCall) {
        return EVT_RETURN_BLOCK;
    }
    ((f32*)eff->userdata)[1] += dy;
    return EVT_RETURN_BLOCK;
}
