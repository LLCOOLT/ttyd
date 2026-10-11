// include: mario/mario.h
// include: mario/mario_party.h
// include: party.h
// include: driver/npcdrv.h
// include: driver/animdrv.h
// proto: static USER_FUNC(proj_on);
static USER_FUNC(proj_on) {
    animPoseSetMaterialFlagOn(marioGetPtr()->paperAnimGroupId[0], 0x400);
    animPoseSetMaterialFlagOn(marioGetPtr()->paperAnimGroupId[1], 0x400);
    animPoseSetMaterialFlagOn(marioGetPtr()->paperAnimGroupId[2], 0x400);
    if (partyGetPtr(marioGetPartyId()) != NULL) {
        animPoseSetMaterialFlagOn(partyGetPtr(marioGetPartyId())->paperAnimGroup, 0x400);
    }
    if (partyGetPtr(marioGetExtraPartyId()) != NULL) {
        animPoseSetMaterialFlagOn(partyGetPtr(marioGetExtraPartyId())->paperAnimGroup, 0x400);
    }
    animPoseSetMaterialFlagOn(npcNameToPtr("\224\362\213\363\221D")->poseId, 0x400);
    return EVT_RETURN_DONE;
}
