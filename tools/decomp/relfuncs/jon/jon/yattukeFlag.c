// include: driver/npcdrv.h
// proto: USER_FUNC(yattukeFlag);
USER_FUNC(yattukeFlag) {
    npcNameToPtr("\223G")->battleInfo.field_4 |= 0x10000000;
    return EVT_RETURN_DONE;
}
