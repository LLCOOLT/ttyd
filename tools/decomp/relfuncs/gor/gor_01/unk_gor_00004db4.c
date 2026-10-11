// include: manager/evtmgr_cmd.h
// decl: s32 U_badgeShop_SpecialCheck(void);
// proto: USER_FUNC(unk_gor_00004db4);
USER_FUNC(unk_gor_00004db4) {
    s32* args = event->args;

    evtSetValue(event, args[0], U_badgeShop_SpecialCheck());
    return EVT_RETURN_DONE;
}
