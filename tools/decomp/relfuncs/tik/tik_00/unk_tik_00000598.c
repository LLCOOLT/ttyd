// include: manager/evtmgr_cmd.h
// include: pmario_sound.h
// proto: USER_FUNC(unk_tik_00000598);
USER_FUNC(unk_tik_00000598) {
    psndClearFlag(0x80);
    return EVT_RETURN_DONE;
}
