#include <dolphin.h>

// prototypes
__declspec(weak) int Hu_IsStub();
void DBInitInterrupts();
s32 DBQueryData();
u32 DBRead();
u32 DBWrite();
void DBOpen();
void DBClose();

__declspec(weak) int Hu_IsStub() {
    return 1;
}

/** Stub of the EXI debugger communication setup (ODEMU); the retail build does nothing. */
void DBInitComm(int* inputFlagPtr, int* mtrCallback) {}

/** Stub of the debugger interrupt setup; does nothing in the retail build. */
void DBInitInterrupts() {}

/** Stub debugger query: reports that no debugger data is waiting (returns 0). */
s32 DBQueryData() {
    return 0;
}

/** Stub debugger read: reads nothing and returns 0. */
u32 DBRead() {
    return 0;
}

/** Stub debugger write: writes nothing and returns 0. */
u32 DBWrite() {
    return 0;
}

/** Stub that would open the debugger channel; does nothing. */
void DBOpen() {}

/** Stub that would close the debugger channel; does nothing. */
void DBClose() {}
