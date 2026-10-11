// include: manager/evtmgr_cmd.h
// decl: s32 kpaMutekiCheck(void);
// proto: USER_FUNC(kpa_muteki_check);
USER_FUNC(kpa_muteki_check) {
    event->lwData[0] = kpaMutekiCheck();
    return EVT_RETURN_DONE;
}
