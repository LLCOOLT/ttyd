// include: manager/evtmgr_cmd.h
// include: battle/battle.h
// include: battle/battle_unit.h
// decl: s32 jetCount;
// proto: USER_FUNC(aud_jet_end);
USER_FUNC(aud_jet_end) {
    jetCount = 1;
    return EVT_RETURN_DONE;
}
