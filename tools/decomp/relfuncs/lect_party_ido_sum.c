// include: party.h
// include: manager/evtmgr_cmd.h
// include: dolphin/os.h
// decl: extern s32 partyCtrlNo;
// decl: static OSTime wwstart;
// proto: static USER_FUNC(lect_party_ido_sum);
static USER_FUNC(lect_party_ido_sum) {
    s32* args = event->args;
    PartyEntry* party = partyGetPtr(args[0] == 0 ? partyCtrlNo : 1);
    s32 frames = evtGetValue(event, args[1]);
    s32 elapsed;

    if (isFirstCall) {
        wwstart = event->lifetime;
        evtSetFloat(event, LW(3), party->position.x);
        evtSetFloat(event, LW(4), party->position.y);
        evtSetFloat(event, LW(5), party->position.z);
        return EVT_RETURN_BLOCK;
    }
    elapsed = OSTicksToMilliseconds((u64)(s32)((u32)event->lifetime - (u32)wwstart));
    if (elapsed > frames) {
        elapsed = frames;
    }
    party->position.x = lect_party_ido_sub(elapsed, frames, evtGetFloat(event, LW(3)), evtGetFloat(event, LW(0)));
    party->position.y = lect_party_ido_sub(elapsed, frames, evtGetFloat(event, LW(4)), evtGetFloat(event, LW(1)));
    party->position.z = lect_party_ido_sub(elapsed, frames, evtGetFloat(event, LW(5)), evtGetFloat(event, LW(2)));
    if (elapsed >= frames) {
        return EVT_RETURN_DONE;
    }
    return EVT_RETURN_BLOCK;
}
