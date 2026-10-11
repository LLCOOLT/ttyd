// include: mario/mario.h
// include: mario/mario_party.h
// include: party.h
// include: driver/hitdrv.h
// decl: BOOL hitIsGroup(HitEntry* target, HitEntry* group);
// proto: USER_FUNC(mario_chk);
USER_FUNC(mario_chk) {
    MarioWork* mario = marioGetPtr();
    PartyEntry* party;

    if (mario != NULL && mario->hitobjStandOn != NULL) {
        if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_ue"))) {
            mario->unk174.x = 1.0f;
        } else if (hitIsGroup(mario->hitobjStandOn, hitNameToPtr("A_b_shita"))) {
            mario->unk174.x = -1.0f;
        }
    }
    party = partyGetPtr(marioGetPartyId());
    if (party != NULL && party->field_138 != NULL) {
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_ue"))) {
            party->field_AC = 1.0f;
        }
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_shita"))) {
            party->field_AC = -1.0f;
        }
    }
    party = partyGetPtr(marioGetExtraPartyId());
    if (party != NULL && party->field_138 != NULL) {
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_ue"))) {
            party->field_AC = 1.0f;
        }
        if (hitIsGroup(party->field_138, hitNameToPtr("A_b_shita"))) {
            party->field_AC = -1.0f;
        }
    }
    return EVT_RETURN_BLOCK;
}
