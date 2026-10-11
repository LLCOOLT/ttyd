// include: party.h
// include: driver/animdrv.h
// proto: USER_FUNC(party_tev);
USER_FUNC(party_tev) {
    animPoseSetMaterialFlagOff(partyGetPtr(0)->paperAnimGroup, 0x0F000000);
    return EVT_RETURN_DONE;
}
