typedef int DSError;

typedef struct TRKBuffer TRKBuffer;

typedef struct TRKEvent {
    int eventType;
    int eventID;
    int msgBufID;
} TRKEvent;

typedef struct TRKFramingState {
    int msgBufID;
    TRKBuffer* buffer;
    int receiveState;
    int isEscape;
    int fcsType;
} TRKFramingState;

typedef struct TRKPacketHeader {
    unsigned int size;
    unsigned char pad[0x3C];
} TRKPacketHeader;

void MWTRACE(unsigned char level, char* fmt, ...);
int TRKPollUART(void);
DSError TRKGetFreeBuffer(int* bufIdx, TRKBuffer** buf);
DSError TRKSetBufferPosition(TRKBuffer* msg, unsigned int pos);
int TRKReadUARTN(void* bytes, unsigned int length);
DSError TRKAppendBuffer_ui8(TRKBuffer* buffer, const unsigned char* data, int count);
void TRKReleaseBuffer(int idx);
void* TRKGetBuffer(int idx);
void TRKConstructEvent(TRKEvent* event, int eventType);
DSError TRKPostEvent(TRKEvent* event);

static TRKFramingState gTRKFramingState;
void* gTRKInputPendingPtr;

/**
 * If the host link has data, grabs a free buffer,
 * reads a 0x40-byte packet header and then the rest of the packet (the header's size field gives the total) into
 * it. Returns the buffer index, or -1 if nothing arrived or the read failed.
 */
int TRKTestForPacket(void) {
    int bytes;
    int id;
    int bufIdx;
    TRKBuffer* b;
    TRKPacketHeader hdr;
    unsigned char payload[0x880];

    if (TRKPollUART() <= 0)
        return -1;

    id = TRKGetFreeBuffer(&bufIdx, &b);
    MWTRACE(4, "TestForPacket : FreeBuffer is  %ld\n", id);
    TRKSetBufferPosition(b, 0);

    if (TRKReadUARTN(&hdr, 0x40) == 0) {
        TRKAppendBuffer_ui8(b, (unsigned char*)&hdr, 0x40);
        id = bufIdx;

        if ((bytes = hdr.size - 0x40) > 0) {
            MWTRACE(1, "Reading payload %ld bytes\n", bytes);

            if (TRKReadUARTN(payload, hdr.size - 0x40) == 0) {
                TRKAppendBuffer_ui8(b, payload, hdr.size);
            } else {
                MWTRACE(8, "TestForPacket : Invalid size of packet hdr.size\n");
                TRKReleaseBuffer(id);
                id = -1;
            }
        }
    } else {
        MWTRACE(8, "TestForPacket : Invalid size of packet\n");
        TRKReleaseBuffer(id);
        id = -1;
    }

    MWTRACE(1, "TestForPacket returning %ld\n", id);
    return id;
}

void TRKProcessInput(int bufferIdx);

/** Polls for a packet and, if one arrived, hands its buffer on to TRKProcessInput. */
void TRKGetInput(void) {
    int id;

    id = TRKTestForPacket();

    if (id != -1) {
        TRKGetBuffer(id);
        TRKProcessInput(id);
    }
}

/** Posts a message event (type 2) for the received buffer so the main loop dispatches it. */
void TRKProcessInput(int bufferIdx) {
    TRKEvent event;

    TRKConstructEvent(&event, 2);
    gTRKFramingState.msgBufID = -1;
    event.msgBufID = bufferIdx;
    TRKPostEvent(&event);
}

/** Resets the packet framing state and prints the sizes of the protocol structures; returns 0. */
DSError TRKInitializeSerialHandler(void) {
    gTRKFramingState.msgBufID = -1;
    gTRKFramingState.receiveState = 0;
    gTRKFramingState.isEscape = 0;

    MWTRACE(1, "TRK_Packet_Header \t    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_ReadMemory     %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_WriteMemory    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_Connect \t    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_ReplyAck\t    %ld bytes\n", 0x40);
    MWTRACE(1, "TRK_CMD_ReadRegisters\t%ld bytes\n", 0x40);

    return 0;
}

/** Serial handler shutdown; nothing to do, returns 0. */
DSError TRKTerminateSerialHandler(void) {
    return 0;
}
