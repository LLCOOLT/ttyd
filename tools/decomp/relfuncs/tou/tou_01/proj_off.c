// include: mario/mario.h
// include: mario/mario_party.h
// include: party.h
// include: driver/animdrv.h
// proto: static USER_FUNC(proj_off);
static USER_FUNC(proj_off) {
    animPoseSetMaterialFlagOff(marioGetPtr()->paperAnimGroupId[0], 0x400);
    animPoseSetMaterialFlagOff(marioGetPtr()->paperAnimGroupId[1], 0x400);
    animPoseSetMaterialFlagOff(marioGetPtr()->paperAnimGroupId[2], 0x400);
    if (partyGetPtr(marioGetPartyId()) != NULL) {
        animPoseSetMaterialFlagOff(partyGetPtr(marioGetPartyId())->paperAnimGroup, 0x400);
    }
    if (partyGetPtr(marioGetExtraPartyId()) != NULL) {
        animPoseSetMaterialFlagOff(partyGetPtr(marioGetExtraPartyId())->paperAnimGroup, 0x400);
    }
    return EVT_RETURN_DONE;
}
