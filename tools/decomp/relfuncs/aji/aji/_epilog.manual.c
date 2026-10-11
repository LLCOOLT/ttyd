// include: mario/mario.h
// include: party.h
// include: driver/swdrv.h
// include: mario/mario_party.h
// decl: void partySetFamicomMode(PartyEntry* party, s32 mode);
void _epilog(void) {
    voidfunctionptr* dtor;

    if (swGet(0x1079)) {
        marioSetFamicomMode(0);
        partySetFamicomMode(partyGetPtr(marioGetPartyId()), 0);
        swClear(0x1079);
    }
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}
