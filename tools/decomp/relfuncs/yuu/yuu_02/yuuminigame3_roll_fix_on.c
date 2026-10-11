// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: void marioRollFixOn(void);
// proto: USER_FUNC(yuuminigame3_roll_fix_on);
USER_FUNC(yuuminigame3_roll_fix_on) {
    marioRollFixOn();
    return EVT_RETURN_DONE;
}
