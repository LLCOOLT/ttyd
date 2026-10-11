// include: manager/evtmgr.h
// include: pmario_sound.h
// include: string.h
// proto: void callback(s32 type, void** work);
void psndBGMOff(u32 flags);

void callback(s32 type, void** work) {
    EventEntry* evt = *(EventEntry**)((u8*)*work + 0x7A00);

    if (strcmp(*(const char**)*work, "stg7_aji_06") == 0) {
        if (type == 3) {
            evt->lwData[5]++;
            if (evt->lwData[5] == 3) {
                psndSFXOn("SFX_STG7_QUIZ_START1");
            } else if (evt->lwData[5] == 4) {
                psndBGMOff(0x400);
                psndBGMOn(1, "BGM_EVT_QUIZ2");
            }
        }
    } else if (type == 3) {
        evt->lwData[5]++;
        if (evt->lwData[5] == 1) {
            psndBGMOff(0x400);
            psndBGMOn(1, "BGM_EVT_QUIZ2");
        }
    }
    evt = *(EventEntry**)((u8*)*work + 0x7A00);
    if (((EventEntry*)evt->lwData[8] == NULL || !evtCheckID(((EventEntry*)evt->lwData[8])->eventId)) && type == 5) {
        evt->lwData[8] = (s32)evtEntry(UNK_0x00022c3c, 0, 0);
    }
}
