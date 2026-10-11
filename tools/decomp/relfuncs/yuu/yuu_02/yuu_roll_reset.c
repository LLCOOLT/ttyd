// include: manager/evtmgr_cmd.h
// include: driver/camdrv.h
// decl: void marioResetRollSpd(void);
// decl: void clrRollEvtFlag(void);
// proto: USER_FUNC(yuu_roll_reset);
USER_FUNC(yuu_roll_reset) {
    marioResetRollSpd();
    clrRollEvtFlag();
    return EVT_RETURN_DONE;
}
