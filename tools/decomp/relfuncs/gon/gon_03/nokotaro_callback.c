// include: party.h
// decl: extern s32 partyCtrlNo;
// decl: void partyChgPose(PartyEntry* party, const char* pose);
// proto: void nokotaro_callback(s32 type);
void nokotaro_callback(s32 type) {
    PartyEntry* party = partyGetPtr(partyCtrlNo);

    switch (type) {
        case 0:
            partyChgPose(party, (const char*)nokotaro_pose[1]);
            break;
        case 2:
            partyChgPose(party, (const char*)nokotaro_pose[0]);
            break;
        case 3:
            partyChgPose(party, (const char*)nokotaro_pose[1]);
            break;
        case 1:
            partyChgPose(party, (const char*)nokotaro_pose[0]);
            break;
    }
}
