// include: manager/evtmgr_cmd.h
// include: mario/mario.h
// proto: USER_FUNC(kpa_nohitenemy_ct_clear);
USER_FUNC(kpa_nohitenemy_ct_clear) {
    MarioWork* mario = marioGetPtr();

    *(s16*)mario->unk78 = 0;
    return EVT_RETURN_DONE;
}
