#include <dolphin/exi.h>
#include <dolphin/os.h>
#include <dolphin/vi.h>

#include "__vi.h"

static u8 shadowGPIOOE;
static u8 shadowGPIOData;

// prototypes
static void initGpioExi(void);
static void setVideoReset(int value);
static void setI2CEnable(int value);
static int gpioOutput(u8 value);
static int gpioOE(u8 value);
static int gpioOut(u32 addr, u8 value);
static int gpioInput(u8* p);

/**
 * Resets the video encoder and enables its I2C bus:
 * clears the GPIO shadow registers, pulls the encoder's reset pin low for 100 microseconds,
 * releases it and switches the I2C buffer on.
 */
void __VIInitI2C(void) {
    OSTime time;

    initGpioExi();
    setVideoReset(0);
    time = OSGetTime();
    while (OSGetTime() - time < OS_USEC_TO_TICKS(100)) {}
    setVideoReset(1);
    setI2CEnable(1);
}

/** Clears the cached GPIO output and output-enable values and writes them to the GPIO device. */
static void initGpioExi(void) {
    shadowGPIOOE = 0;
    shadowGPIOData = 0;
    gpioOutput(shadowGPIOData);
    gpioOE(shadowGPIOOE);
}

/**
 * Drives the I2C clock line (GPIO bit 1): a 0 turns on the output enable (pulls the line low),
 * a 1 releases it so the pull-up takes it high.
 */
void __VISetSCL(int value) {
    shadowGPIOOE &= ~2;
    if (value == 0) {
        shadowGPIOOE |= 2;
    }
    gpioOE(shadowGPIOOE);
}

/** Reads the I2C clock line (GPIO input bit 1); returns 1 when it is high. */
int __VIGetSCL(void) {
    u8 value;

    gpioInput(&value);
    if (value & 2) {
        return 1;
    } else {
        return 0;
    }
}

/** Drives the I2C data line (GPIO bit 0): a 0 pulls it low through the output enable, a 1 releases it. */
void __VISetSDA(int value) {
    shadowGPIOOE &= ~1;
    if (value == 0) {
        shadowGPIOOE |= 1;
    }
    gpioOE(shadowGPIOOE);
}

/** Reads the I2C data line (GPIO input bit 0); returns 1 when it is high. */
int __VIGetSDA(void) {
    u8 value;

    gpioInput(&value);
    if (value & 1) {
        return 1;
    } else {
        return 0;
    }
}

/** Sets the encoder reset pin (GPIO bit 2) to value, as an output. */
static void setVideoReset(int value) {
    if (value != 0) {
        shadowGPIOData |= 4;
    } else {
        shadowGPIOData &= ~4;
    }
    shadowGPIOOE |= 4;
    gpioOutput(shadowGPIOData);
    gpioOE(shadowGPIOOE);
}

/**
 * Enables (value nonzero, pin driven low) or disables the buffer that connects the GPIO lines to the encoder's
 * I2C bus (GPIO bit 4).
 */
static void setI2CEnable(int value) {
    if (value != 0) {
        shadowGPIOData &= ~0x10;
    } else {
        shadowGPIOData |= 0x10;
    }
    shadowGPIOOE |= 0x10;
    gpioOutput(shadowGPIOData);
    gpioOE(shadowGPIOOE);
}

/** Writes value to the GPIO output data register (address 0x800404) of the EXI GPIO device. */
static int gpioOutput(u8 value) {
    return gpioOut(0x800404U, value);
}

/** Writes value to the GPIO output-enable register (address 0x800408) of the EXI GPIO device. */
static int gpioOE(u8 value) {
    return gpioOut(0x800408U, value);
}

/**
 * Writes one byte to register addr of the GPIO device on EXI channel 0 (device 1):
 * a write command, then the data byte. Returns 0 if the channel could not be locked or selected.
 */
static int gpioOut(u32 addr, u8 value) {
    u32 cmd;

    cmd = (addr | 0x02000000) << 6;
    if (EXILock(0, 1, 0) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 4) == 0) {
        EXIUnlock(0);
        return 0;
    }

    EXIImm(0, &cmd, 4, EXI_WRITE, 0);
    EXISync(0);
    cmd = value << 24;
    EXIImm(0, &cmd, 1, EXI_WRITE, 0);
    EXISync(0);
    EXIDeselect(0);
    EXIUnlock(0);
    return 1;
}

/**
 * Reads the GPIO input register (command 0x20010100) over EXI channel 0 into p;
 * returns 0 if the channel could not be locked or selected.
 */
static int gpioInput(u8* p) {
    u32 cmd;

    if (EXILock(0, 1, 0) == 0) {
        return 0;
    }
    if (EXISelect(0, 1, 4) == 0) {
        EXIUnlock(0);
        return 0;
    }
    cmd = 0x20010100;
    EXIImm(0, &cmd, 4, EXI_WRITE, 0);
    EXISync(0);
    EXIImm(0, &cmd, 1, EXI_READ, 0);
    EXISync(0);
    EXIDeselect(0);
    EXIUnlock(0);
    *p = cmd >> 24;
    return 1;
}
