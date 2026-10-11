// include: driver/msgdrv.h
// include: memory.h
// include: string.h
// include: stdio.h
// proto: USER_FUNC(unk_gor_0000041c);
USER_FUNC(unk_gor_0000041c) {
    s32* args = event->args;
    const char* head = (const char*)evtGetValue(event, args[0]);
    const char* msg = msgSearch((const char*)evtGetValue(event, args[1]));
    const char* tail = (const char*)evtGetValue(event, args[2]);
    s32 size = strlen(head) + strlen(msg) + strlen(tail) + 1;

    unk_gor_bss00000000 = _mapAlloc(size);
    memset(unk_gor_bss00000000, 0, size);
    sprintf(unk_gor_bss00000000, "%s%s%s", head, msg, tail);
    evtSetValue(event, args[3], (s32)unk_gor_bss00000000);
    return EVT_RETURN_DONE;
}
