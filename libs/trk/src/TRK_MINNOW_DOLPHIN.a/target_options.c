static unsigned char bUseSerialIO;

/** Stores whether console I/O (printf to the host, requests 0xD0/0xD1) goes over the debug link. */
void SetUseSerialIO(unsigned char sio) { bUseSerialIO = sio; }

/** Returns whether console I/O goes over the debug link. */
unsigned char GetUseSerialIO(void) { return bUseSerialIO; }
