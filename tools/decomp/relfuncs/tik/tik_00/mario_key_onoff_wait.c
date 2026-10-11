// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(mario_key_onoff_wait);
USER_FUNC(mario_key_onoff_wait) {
    marioGetPtr();
    switch (!marioChkKey()) {
        default:
            return EVT_RETURN_BLOCK;
        case 0:
            return EVT_RETURN_DONE;
    }
}
