// include: seq/seq_demo.h
// proto: void dig_thpStop(void);
void dig_thpStop(void) {
    u32 type;

    EXIGetType(0, 2, &type);
    if (type != 0x05070000) {
        THPSimpleAudioStop();
        THPSimpleLoadStop();
        THPSimpleClose();
        THPSimpleQuit();
    }
}
