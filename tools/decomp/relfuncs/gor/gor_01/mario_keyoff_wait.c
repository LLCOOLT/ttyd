// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: static USER_FUNC(mario_keyoff_wait);
static USER_FUNC(mario_keyoff_wait) {
    switch (!marioChkKey()) {
        default:
            return EVT_RETURN_BLOCK;
        case 0:
            return EVT_RETURN_YIELD;
    }
}
