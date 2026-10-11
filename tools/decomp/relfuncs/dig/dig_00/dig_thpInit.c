// include: seq/seq_demo.h
// include: memory.h
// proto: void dig_thpInit(void);
void dig_thpInit(void) {
    u32 type;

    EXIGetType(0, 2, &type);
    if (type != 0x05070000) {
        THPSimpleInit(2);
        THPSimpleOpen("demo.thp");
        THPSimpleSetBuffer(_mapAlloc(THPSimpleCalcNeedMemory()));
        THPSimpleAudioStop();
        THPSimplePreLoad(0);
        THPSimpleAudioStart();
        THPSimpleSetVolume(80, 0);
    }
}
