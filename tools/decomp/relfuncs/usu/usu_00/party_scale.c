// include: party.h
// proto: USER_FUNC(party_scale);
// The target copies from a non-const Vec (lwz,lwz,stw,stw,lwz,stw) that lives in .rodata.
__declspec(section ".rodata") Vec party_scale_vec = {1.0f, 1.0f, 1.0f};

USER_FUNC(party_scale) {
    partyGetPtr(0)->scale = party_scale_vec;
    return EVT_RETURN_DONE;
}
