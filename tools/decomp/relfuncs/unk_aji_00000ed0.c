// include: manager/evtmgr.h
// proto: void unk_aji_00000ed0(s32 type, void** work);
void unk_aji_00000ed0(s32 type, void** work) {
    EventEntry* evt = *(EventEntry**)((u8*)*work + 0x7A00);

    if (((EventEntry*)evt->lwData[8] == NULL || !evtCheckID(((EventEntry*)evt->lwData[8])->eventId)) && type == 5) {
        evt->lwData[8] = (s32)evtEntry(UNK_0x00022c3c, 0, 0);
    }
}
