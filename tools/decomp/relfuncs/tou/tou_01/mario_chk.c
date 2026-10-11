// include: mario/mario.h
// proto: static USER_FUNC(mario_chk);
static USER_FUNC(mario_chk) {
    s32* args = event->args;
    BOOL ok = FALSE;

    if (marioChkKey() && marioChkCtrl()) {
        ok = TRUE;
    }
    evtSetValue(event, args[0], ok != FALSE);
    return EVT_RETURN_DONE;
}
