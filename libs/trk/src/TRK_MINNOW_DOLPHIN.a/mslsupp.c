typedef unsigned long size_t;
typedef int BOOL;

BOOL GetTRKConnected(void);
unsigned char GetUseSerialIO(void);
unsigned char TRKAccessFile(unsigned int cmd, unsigned int file_handle, size_t* length, unsigned char* buffer);
unsigned char TRKCloseFile(unsigned int cmd, unsigned int file_handle);

enum { DS_IONoError, DS_IOError, DS_IOEOF };

/**
 * Shared helper for the MSL console hooks: forwards a read or write request to the host through TRKAccessFile,
 * passing the byte count in and out; returns DS_IOError when the stub is not connected,
 * DS_IONoError or DS_IOEOF otherwise.
 */
static inline int __access_file(unsigned int handle, unsigned char* buffer, size_t* count, void* ref_con,
                                unsigned int cmd) {
    size_t countTemp;
    unsigned char r0;

    if (GetTRKConnected() == 0)
        return DS_IOError;

    countTemp = *count;
    r0 = TRKAccessFile(cmd, handle, &countTemp, buffer);
    *count = countTemp;

    switch (r0) {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    }

    return DS_IOError;
}

/**
 * MSL console-read hook: reads from the host's stdin through the debugger (file-support request 0xD1);
 * returns an I/O error if the stub is not connected or serial I/O is off.
 */
int __read_console(unsigned long handle, unsigned char* buffer, size_t* count, void* ref_con) {
    if (GetUseSerialIO() == 0)
        return DS_IOError;
    return __access_file(0, buffer, count, ref_con, 0xD1);
}

/**
 * MSL console-write hook: sends printf output to the host's console through the debugger (file-support request
 * 0xD0); returns an I/O error if the stub is not connected or serial I/O is off.
 */
int __TRK_write_console(unsigned long handle, unsigned char* buffer, size_t* count, void* ref_con) {
    if (GetUseSerialIO() == 0)
        return DS_IOError;
    return __access_file(1, buffer, count, ref_con, 0xD0);
}

/**
 * MSL console-close hook: asks the debugger host to close the file handle (request 0xD3);
 * I/O error if not connected.
 */
int __close_console(unsigned long handle) {
    unsigned int r0;

    if (GetTRKConnected() == 0)
        return DS_IOError;

    r0 = TRKCloseFile(0xD3, handle);

    switch ((unsigned char)r0) {
    case DS_IONoError:
        return DS_IONoError;
    case DS_IOEOF:
        return DS_IOEOF;
    }

    return DS_IOError;
}
