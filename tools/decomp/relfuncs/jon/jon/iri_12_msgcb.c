// include: manager/evtmgr.h
// decl: extern s32 iri_12_makkino_okiru[];
// proto: void iri_12_msgcb(s32 type, void* param);
void iri_12_msgcb(s32 type, void* param) {
    u8* msg = *(u8**)param;

    if (type == 3 && *(u16*)(msg + 8) == 1) {
        evtEntry(iri_12_makkino_okiru, 0, 0);
    }
}
