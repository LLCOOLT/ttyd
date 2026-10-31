typedef int BOOL;
typedef int DSError;

typedef struct TRKEvent {
    int eventType;
    int eventID;
    int msgBufID;
} TRKEvent;

extern void* gTRKInputPendingPtr;

BOOL TRKGetNextEvent(TRKEvent* event);
void* TRKGetBuffer(int idx);
void TRKDispatchMessage(void* msg);
void TRKTargetInterrupt(TRKEvent* event);
void TRKTargetSupportRequest(void);
void TRKDestructEvent(TRKEvent* event);
void TRKGetInput(void);
BOOL TRKTargetStopped(void);
DSError TRKTargetContinue(void);

/**
 * The stub's event loop: takes events off the queue and handles them (type 2 message goes to TRKDispatchMessage,
 * 1 shuts the loop down, 3 and 4 are CPU interrupts for TRKTargetInterrupt, 5 is a game file-support request).
 * With the queue empty it polls the host link for a packet, and resumes the game if it is not stopped.
 */
void TRKNubMainLoop(void) {
    void* msg;
    TRKEvent event;
    BOOL isShutdownRequested = 0;
    BOOL isNewInput = 0;

    while (isShutdownRequested == 0) {
        if (TRKGetNextEvent(&event) != 0) {
            isNewInput = 0;

            switch (event.eventType) {
            case 0:
                break;
            case 2:
                msg = TRKGetBuffer(event.msgBufID);
                TRKDispatchMessage(msg);
                break;
            case 1:
                isShutdownRequested = 1;
                break;
            case 3:
            case 4:
                TRKTargetInterrupt(&event);
                break;
            case 5:
                TRKTargetSupportRequest();
                break;
            }

            TRKDestructEvent(&event);
            continue;
        }

        if ((isNewInput == 0) || (*(unsigned char*)gTRKInputPendingPtr != '\0')) {
            isNewInput = 1;
            TRKGetInput();
            continue;
        }

        if (TRKTargetStopped() == 0)
            TRKTargetContinue();

        isNewInput = 0;
    }
}
