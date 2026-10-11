// include: party.h
// include: driver/animdrv.h
// proto: USER_FUNC(check);
USER_FUNC(check) {
    if (partyGetPtr(0) != NULL) {
        animPoseSetMaterialFlagOff(partyGetPtr(0)->paperAnimGroup, 0x0A000000);
    }
    return EVT_RETURN_BLOCK;
}
