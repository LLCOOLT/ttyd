#include <dolphin.h>
#include <dolphin/amc/AmcExi2Comm.h>

// prototypes
int AMC_IsStub(void);

/** Stub of the AMC (debug monitor) EXI2 initialiser; does nothing in this build, which has no debugger link. */
void EXI2_Init(volatile unsigned char **inputPendingPtrRef, EXICallback monitorCallback) {}

/** Stub; does nothing. */
void EXI2_EnableInterrupts(void) {}

/** Stub; always reports that nothing is pending (0). */
int EXI2_Poll(void) {
    return 0;
}

/** Stub; reads nothing and reports AMC_EXI_NO_ERROR. */
AmcExiError EXI2_ReadN(void *bytes, unsigned long length) {
    return AMC_EXI_NO_ERROR;
}

/** Stub; writes nothing and reports AMC_EXI_NO_ERROR. */
AmcExiError EXI2_WriteN(const void *bytes, unsigned long length) { 
    return AMC_EXI_NO_ERROR;
}

/** Stub; does nothing. */
void EXI2_Reserve(void) {}

/** Stub; does nothing. */
void EXI2_Unreserve(void) {}

/**
 * Returns 1 to tell the debug monitor code that these are the stub versions of the EXI2 routines,
 * i.e. no real AMC link.
 */
int AMC_IsStub(void) {
    return 1;
}
