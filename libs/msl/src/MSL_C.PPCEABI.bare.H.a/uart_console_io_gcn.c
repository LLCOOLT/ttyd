#include "ansi_files.h"

typedef void (*__idle_proc)(void);

unsigned long OSGetConsoleType(void);
int InitializeUART(unsigned long baudRate);
int WriteUARTN(const void* buf, unsigned long len);
int __TRK_write_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc);

/**
 * Console write handler (stdout/stderr) for GameCube:
 * unless the OSGetConsoleType() bit 0x20000000 is set,
 * initialises the UART at 57600 baud once and writes the bytes with WriteUARTN (count becomes 0 and an I/O error
 * is returned on failure); then also passes them to the TRK debugger console.
 */
int __write_console(__file_handle handle, unsigned char* buffer, size_t* count, __idle_proc idle_proc) {
    static int initialized = 0;
    int ret;

    if ((OSGetConsoleType() & 0x20000000) == 0) {
        ret = 0;
        if (initialized == 0) {
            ret = InitializeUART(57600);
            if (ret == 0)
                initialized = 1;
        }
        if (ret != 0)
            return __io_error;
        if (WriteUARTN(buffer, *count) != 0) {
            *count = 0;
            return __io_error;
        }
    }
    __TRK_write_console(handle, buffer, count, idle_proc);
    return __no_io_error;
}
