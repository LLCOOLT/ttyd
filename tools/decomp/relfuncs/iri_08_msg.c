// proto: void iri_08_msg(s32 type, void** work);
void iri_08_msg(s32 type, void** work) {
    u16* msg = *work;

    if (type == 3 && msg[4] == 9) {
        evtSetValue(NULL, GF(0), 0);
    }
}
