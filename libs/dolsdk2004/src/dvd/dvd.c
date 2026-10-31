#include <dolphin.h>
#include <dolphin/os.h>
#include <dolphin/dvd.h>

#include "os/__os.h"
#include "__dvd.h"

// externs
extern void __DVDPrintFatalMessage();
extern int DVDCompareDiskID(const struct DVDDiskID * id1 /* r29 */, const struct DVDDiskID * id2 /* r30 */);
extern int __DVDLowTestAlarm(const OSAlarm * alarm /* r3 */);

#ifdef DEBUG
/** Library version string kept in the binary (debug build). */
const char* __DVDVersion = "<< Dolphin SDK - DVD\tdebug build: Apr  5 2004 03:56:07 (0x2301) >>";
#else
/** Library version string kept in the binary (release build). */
const char* __DVDVersion = "<< Dolphin SDK - DVD\trelease build: Apr  5 2004 04:14:51 (0x2301) >>";
#endif

/**
 * When set, read commands invalidate the data cache over their destination
 * before the read (DVDSetAutoInvalidation).
 */
static BOOL autoInvalidation = TRUE;

static void defaultOptionalCommandChecker(DVDCommandBlock*, DVDCommandCheckerCallback);
/**
 * Hook stateBusy calls for command numbers it does not know; replaced with __DVDSetOptionalCommandChecker.
 */
static DVDCommandChecker checkOptionalCommand = defaultOptionalCommandChecker;

static DVDBB2 BB2;
static DVDDiskID CurrDiskID;
static DVDCommandBlock DummyCommandBlock;
static OSAlarm ResetAlarm;

static DVDCommandBlock* executing;
static DVDDiskID* IDShouldBe;
static OSBootInfo* bootInfo;
static volatile int PauseFlag;
static volatile int PausingFlag;
static int AutoFinishing;
static BOOL FatalErrorFlag;
static volatile u32 CurrCommand;
static volatile u32 Canceling;
static void (*CancelCallback)(s32, DVDCommandBlock*);
static volatile u32 ResumeFromHere;
static volatile u32 CancelLastError;
static u32 LastError;
static volatile s32 NumInternalRetry;
static int ResetRequired;
static int CancelAllSyncComplete;
static volatile u32 ResetCount;
static BOOL FirstTimeInBootrom;
static u32 MotorState;
static int DVDInitialized;
void (*LastState)(DVDCommandBlock*);

// prototypes
static void stateReadingFST();
static void cbForStateReadingFST(u32 intType);
static void cbForStateError(u32 intType);
static void stateError(u32 error);
static void stateTimeout();
static void stateGettingError();
static u32 CategorizeError(u32 error);
static BOOL CheckCancel(u32 resume);
static void cbForStateGettingError(u32 intType);
static void cbForUnrecoveredError(u32 intType);
static void cbForUnrecoveredErrorRetry(u32 intType);
static void stateGoToRetry();
static void cbForStateGoToRetry(u32 intType);
static void stateCheckID();
static void stateCheckID3();
static void stateCheckID2a();
static void stateCheckID2();
static void cbForStateCheckID1(u32 intType);
static void cbForStateCheckID2(u32 intType);
static void cbForStateCheckID3(u32 intType);
static void cbForStateCheckID2a(u32 intType);
static void AlarmHandler(OSAlarm* alarm, OSContext* context);
static void stateCoverClosed();
static void stateCoverClosed_CMD(DVDCommandBlock* command);
static void cbForStateCoverClosed(u32 intType);
static void stateMotorStopped();
static void cbForStateMotorStopped(u32 intType);
static void stateReady();
static void stateBusy(DVDCommandBlock* block);
static BOOL IsImmCommandWithResult(u32 command);
static int IsDmaCommand(u32 command);
static void cbForStateBusy(u32 intType);
static int issueCommand(s32 prio, DVDCommandBlock* block);
static void cbForCancelStreamSync(s32 result, DVDCommandBlock* block);
static void cbForStopStreamAtEndSync(s32 result, DVDCommandBlock* block);
static void cbForGetStreamErrorStatusSync(s32 result, DVDCommandBlock* block);
static void cbForGetStreamPlayAddrSync(s32 result, DVDCommandBlock* block);
static void cbForGetStreamStartAddrSync(s32 result, DVDCommandBlock* block);
static void cbForGetStreamLengthSync(s32 result, DVDCommandBlock* block);
static void cbForChangeDiskSync(s32 result, DVDCommandBlock* block);
static void cbForStopMotorSync(s32 result, DVDCommandBlock* block);
static void cbForInquirySync(s32 result, DVDCommandBlock* block);
static void cbForCancelSync(s32 result, DVDCommandBlock* block);
static void cbForCancelAllSync(s32 result, DVDCommandBlock* block);

/** Default for the optional command hook; does nothing, so unknown command numbers are never issued to the drive. */
static void defaultOptionalCommandChecker(DVDCommandBlock*, DVDCommandCheckerCallback) {}

/**
 * Sets the hook stateBusy calls for command numbers it does not know (the "optional" commands)
 * and returns the new hook.
 */
DVDCommandChecker __DVDSetOptionalCommandChecker(DVDCommandChecker func) {
    DVDCommandChecker old = checkOptionalCommand;
    checkOptionalCommand = func;
    return checkOptionalCommand;
}

/**
 * One-time DVD setup: initializes the file system, the waiting queues and the low-level read workaround,
 * installs the DI interrupt handler (interrupt 0x15) and clears the DI status.
 * If the boot info magic is 0xE5207C22 it also runs __fstLoad;
 * a magic other than 0x0D15EA5E marks the first run from the bootrom.
 */
void DVDInit(void) {
    if (!DVDInitialized) {
        OSRegisterVersion(__DVDVersion);
        DVDInitialized = TRUE;

        __DVDFSInit();
        __DVDClearWaitingQueue();
        __DVDInitWA();

        MotorState = 0;
        bootInfo = (void*)OSPhysicalToCached(0);
        IDShouldBe = &bootInfo->DVDDiskID;

        __OSSetInterruptHandler(0x15, __DVDInterruptHandler);
        __OSUnmaskInterrupts(0x400);
        OSInitThreadQueue(&__DVDThreadQueue);
        __DIRegs[0] = 0x2A;
        __DIRegs[1] = 0;

        if (bootInfo->magic == 0xE5207C22) {
            OSReport("load fst\n");
            __fstLoad();
        } else if (bootInfo->magic == 0x0D15EA5E) {

        } else {
            FirstTimeInBootrom = TRUE;
        }
    }
}

/**
 * DVD state: reads the FST (length rounded up to 32 bytes,
 * from the position in the BB2 block just read) into the FST location in the boot info.
 */
static void stateReadingFST() {
    LastState = stateReadingFST;
    ASSERTLINE(652, ((u32)(bootInfo->FSTLocation) & (32 - 1)) == 0);
    DVD_ASSERTMSGLINE(661, bootInfo->FSTMaxLength >= BB2.FSTLength, "DVDChangeDisk(): FST in the new disc is too big.   ");
    DVDLowRead(bootInfo->FSTLocation, (u32)(BB2.FSTLength + 0x1F) & 0xFFFFFFE0, BB2.FSTPosition, cbForStateReadingFST);
}

/** Extra command number (one slot, 0xFFFFFFFF: empty) that IsDmaCommand treats as a DMA transfer. */
static u32 DmaCommand[1] = {0xFFFFFFFF};

/**
 * Callback for stateReadingFST.
 * On success it re-initializes the file system from the new FST,
 * completes the current command with result 0 and goes to stateReady;
 * a timeout goes to stateTimeout and any other failure asks the drive for its error.
 */
static void cbForStateReadingFST(u32 intType) {
    DVDCommandBlock* finished;

    if (intType == 16) {
        stateTimeout();
        return;
    }

    ASSERTLINE(680, (intType & DVD_INTTYPE_CVR) == 0);

    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(685, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;

        __DVDFSInit();
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = DVD_STATE_END;

        if (finished->callback) {
            finished->callback(0, finished);
        }

        stateReady();
        return;
    }

    ASSERTLINE(712, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

/**
 * Fatal-error handler, run after the motor stop:
 * marks the command as failed, shows the fatal message, sets FatalErrorFlag,
 * completes the command (and any cancel callback) with -1 and moves on. A timeout goes to stateTimeout instead.
 */
static void cbForStateError(u32 intType) {
	DVDCommandBlock* finished;
    executing->state = -1;

	if (intType == 16) {
		stateTimeout();
		return;
	}

    __DVDPrintFatalMessage();

	FatalErrorFlag = TRUE;
	finished = executing;
	executing = &DummyCommandBlock;

	if (finished->callback) {
		(finished->callback)(-1, finished);
	}

	if (Canceling) {
		Canceling = FALSE;
		if (CancelCallback)
			(CancelCallback)(0, finished);
	}

	stateReady();
}

/** DVD state: records the error code in SRAM (__DVDStoreErrorCode) and stops the motor, ending in cbForStateError. */
static void stateError(u32 error) {
    __DVDStoreErrorCode(error);
    DVDLowStopMotor(&cbForStateError);
}

/**
 * DVD state: a command timed out.
 * Records code 0x01234568, resets the drive and goes straight to the fatal-error handler.
 */
static void stateTimeout() {
    __DVDStoreErrorCode(0x01234568);
    DVDReset();
    cbForStateError(0);
}

/** DVD state: asks the drive for its error code (DVDLowRequestError); the reply goes to cbForStateGettingError. */
static void stateGettingError() {
    DVDLowRequestError(cbForStateGettingError);
}

/**
 * Sorts a drive error into 0 (ignorable: 0x62800, 0x23A00 and 0xB5A01),
 * 1 (fatal: 0x20400, or the same error twice in a row on the second try),
 * 2 (retry after stopping the motor: a different error on the second try, 0x31100,
 * or any error on a disc ID read) or 3 (retry the command at once). Counts attempts in NumInternalRetry.
 */
static u32 CategorizeError(u32 error) {
    if (error == 0x20400) {
        LastError = error;
        return 1;
    }
    
    error &= 0x00FFFFFF;
    if (error == 0x62800 || error == 0x23A00 || error == 0xB5A01) {
        return 0;
    }

    NumInternalRetry++;
    if (NumInternalRetry == 2) {
        if (error == LastError) {
            LastError = error;
            return 1;
        }
        LastError = error;
        return 2;
    }

    LastError = error;

    if (error == 0x31100 || executing->command == DVD_COMMAND_READID) {
        return 2;
    }

    return 3;
}

/**
 * If the game has cancelled the running command, saves where to resume (resume),
 * completes the command as canceled (callbacks get -3 and 0), runs the next queued command and returns true.
 * Otherwise returns false.
 */
static BOOL CheckCancel(u32 resume) {
	DVDCommandBlock* finished;

	if (Canceling) {
		ResumeFromHere = resume;
		Canceling = FALSE;

		finished = executing;
		executing = &DummyCommandBlock;

		finished->state = 10;

		if (finished->callback)
			(*finished->callback)(-3, finished);

		if (CancelCallback)
			(CancelCallback)(0, finished);

		stateReady();
		return TRUE;
	}

	return FALSE;
}

/**
 * Handles the drive's error reply (code read from DI register 8).
 * Fatal errors go to stateError; retry categories either stop the motor and retry
 * or reissue the command (seeking first for 0x31100);
 * the ignorable ones are decoded from the status byte as motor stopped, cover opened or no disc,
 * and sent to the matching wait state.
 */
static void cbForStateGettingError(u32 intType) {
	u32 error;
	u32 status;
	u32 errorCategory;
	u32 resume;

	if (intType == 16) {
		stateTimeout();
		return;
	}

	if (intType & 2) {
		stateError(0x1234567);
		return;
	}

    ASSERTLINE(956, intType == DVD_INTTYPE_TC);

	error = __DIRegs[8];
	status = error & 0xff000000;

	errorCategory = CategorizeError(error);

	if (errorCategory == 1) {
		stateError(error);
		return;
	}

	if (errorCategory == 2 || errorCategory == 3) {
		resume = 0;
	} else {
		if (status == 0x01000000)
			resume = 4;
		else if (status == 0x02000000)
			resume = 6;
		else if (status == 0x03000000)
			resume = 3;
		else
			resume = 5;
	}

	if (CheckCancel(resume))
		return;

	if (errorCategory == 2) {
		__DVDStoreErrorCode(error);
		stateGoToRetry();
		return;
	}

	if (errorCategory == 3) {
		if ((error & 0x00ffffff) == 0x00031100) {
			DVDLowSeek(executing->offset, cbForUnrecoveredError);
		} else {
			LastState(executing);
		}
		return;
	}

	if (status == 0x01000000) {
		executing->state = 5;
		stateMotorStopped();
		return;
	} else if (status == 0x02000000) {
		executing->state = 3;
		stateCoverClosed();
		return;
	} else if (status == 0x03000000) {
		executing->state = 4;
		stateMotorStopped();
		return;
	} else {
		stateError(0x1234567);
		return;
	}
}

/**
 * Callback after the recovery seek for error 0x31100: on success it stops the motor and retries;
 * otherwise it requests the drive's error code again.
 */
static void cbForUnrecoveredError(u32 intType) {
	if (intType == 16) {
		stateTimeout();
		return;
	}

	if (intType & 1) {
		stateGoToRetry();
		return;
	}

    ASSERTLINE(1055, intType == DVD_INTTYPE_DE);
	DVDLowRequestError(cbForUnrecoveredErrorRetry);
}

/**
 * Callback with the drive's error after a failed recovery seek:
 * a fatal error with that code (or 0x01234567 if the request itself failed); a timeout goes to stateTimeout.
 */
static void cbForUnrecoveredErrorRetry(u32 intType) {
	if (intType == 0x10) {
        stateTimeout();
	} else {
        if (intType & 2) {
            stateError(0x01234567);
            return;
        }

        stateError(__DIRegs[8]);
    }
}

/** DVD state: stops the drive motor before retrying the command. */
static void stateGoToRetry() {
    DVDLowStopMotor(cbForStateGoToRetry);
}

/**
 * Callback after the retry motor stop: clears the retry count, flags a reset as required after a failed BS read,
 * disc ID read, audio buffer config or BS disc change,
 * sets the command state to RETRY and waits for the cover (stateMotorStopped).
 */
static void cbForStateGoToRetry(u32 intType) {
	if (intType == 16) {
		stateTimeout();
		return;
	}

	if (intType & 2) {
		stateError(0x1234567);
		return;
	}

    ASSERTLINE(1104, intType == DVD_INTTYPE_TC);
	NumInternalRetry = 0;

	if (CurrCommand == 4 || CurrCommand == 5 || CurrCommand == 13 || CurrCommand == 15) {
		ResetRequired = TRUE;
	}

	if (!CheckCancel(2)) {
		executing->state = 11;
		stateMotorStopped();
	}
}

/**
 * DVD state: checks the disc that was just read.
 * For a disc change it compares the new ID with the wanted one,
 * adopts it and goes on to configure the audio buffer.
 * For other commands it compares with the boot disc ID;
 * if it is wrong it stops the motor and reports a wrong disc.
 */
static void stateCheckID() {
    switch(CurrCommand) {
    case DVD_COMMAND_CHANGE_DISK:
        if (DVDCompareDiskID(&CurrDiskID, executing->id)) {
            memcpy(IDShouldBe, &CurrDiskID, sizeof(DVDDiskID));
            executing->state = DVD_STATE_BUSY;
            DCInvalidateRange(&BB2.bootFilePosition, 0x20);
            LastState = stateCheckID2a;
            stateCheckID2a(executing);
        } else {
            DVDLowStopMotor(cbForStateCheckID1);
        }
        break;
    default:
        if (memcmp(&CurrDiskID, IDShouldBe, sizeof(DVDDiskID)) != 0) {
            DVDLowStopMotor(cbForStateCheckID1);
        } else {
            LastState = stateCheckID3;
            stateCheckID3(executing);
        }
        break;
    }
}

/**
 * DVD state: sets the drive's audio buffer according to the streaming flag of the boot disc ID,
 * then returns to the interrupted command in cbForStateCheckID3.
 */
static void stateCheckID3() {
    DVDLowAudioBufferConfig(IDShouldBe->streaming, 0xA, cbForStateCheckID3);
}

/**
 * DVD state: sets the drive's audio buffer according to the streaming flag of the boot disc ID,
 * then reads the BB2 block in cbForStateCheckID2a.
 */
static void stateCheckID2a() {
    DVDLowAudioBufferConfig(IDShouldBe->streaming, 0xA, cbForStateCheckID2a);
}

/**
 * Callback after the audio buffer was set following a disc change:
 * goes on to read the BB2 block, or asks for the error on a failure.
 */
static void cbForStateCheckID2a(u32 intType) {
    if (intType == 16) {
		stateTimeout();
		return;
	}

    ASSERTLINE(1227, (intType & DVD_INTTYPE_CVR) == 0);

    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(1232, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        stateCheckID2(executing);
        return;
    }

    ASSERTLINE(1243, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

/** DVD state: reads the 0x20 byte BB2 block (which holds the FST position and size) from disc offset 0x420. */
static void stateCheckID2() {
    DVDLowRead(&BB2, 0x20, 0x420, cbForStateCheckID2);
}

/**
 * Callback after the stop-motor of a wrong disc:
 * unless the command was cancelled, marks it WRONG_DISK and waits for a cover change.
 */
static void cbForStateCheckID1(u32 intType) {
    if (intType == 16) {
		stateTimeout();
		return;
	}

    if (intType & DVD_INTTYPE_DE) {
        stateError(0x01234567);
        return;
    }

    ASSERTLINE(1279, intType == DVD_INTTYPE_TC);
    NumInternalRetry = 0;

    if (CheckCancel(1) == FALSE) {
        executing->state = DVD_STATE_WRONG_DISK;
        stateMotorStopped();
    }
}

/** Callback after the BB2 read: continues with reading the FST (stateReadingFST). */
static void cbForStateCheckID2(u32 intType) {
    if (intType == 16) {
		stateTimeout();
		return;
	}

    ASSERTLINE(1300, (intType & DVD_INTTYPE_CVR) == 0);

    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(1305, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        stateReadingFST();
        return;
    }

    ASSERTLINE(1321, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

/** Callback after the audio buffer was set: unless cancelled, restarts the interrupted command with stateBusy. */
static void cbForStateCheckID3(u32 intType) {
    if (intType == 16) {
		stateTimeout();
		return;
	}

    ASSERTLINE(1336, (intType & DVD_INTTYPE_CVR) == 0);

    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(1341, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        if (CheckCancel(0) == FALSE) {
            executing->state = DVD_STATE_BUSY;
            stateBusy(executing);
        }
        return;
    }

    ASSERTLINE(1355, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

/** Alarm handler, 1150 ms after a cover close: resets the drive and starts reading the disc ID into CurrDiskID. */
static void AlarmHandler(OSAlarm* alarm, OSContext* context) {
    DVDReset();
    DCInvalidateRange(&CurrDiskID, sizeof(DVDDiskID));
    LastState = &stateCoverClosed_CMD;
    stateCoverClosed_CMD(executing);
}

/**
 * DVD state: the cover has been closed.
 * For boot-strap commands, disc ID reads and audio buffer config it clears the queue
 * and fails the command with -4; for others it resets the drive and sets a 1150 ms alarm
 * before re-reading the disc ID.
 */
static void stateCoverClosed() {
    DVDCommandBlock* finished;

    switch(CurrCommand) {
    case DVD_COMMAND_BSREAD:
    case DVD_COMMAND_READID:
    case DVD_COMMAND_AUDIO_BUFFER_CONFIG:
    case DVD_COMMAND_BS_CHANGE_DISK:
        __DVDClearWaitingQueue();
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            finished->callback(-4, finished);
        }
        stateReady();
        break;
    default:
        MotorState = 0;
        DVDReset();
        OSCreateAlarm(&ResetAlarm);
        OSSetAlarm(&ResetAlarm, OSMillisecondsToTicks(1150), &AlarmHandler);
        break;
    }
}

/** DVD state: reads the disc ID from the disc into CurrDiskID; cbForStateCoverClosed then checks it. */
static void stateCoverClosed_CMD(DVDCommandBlock* command) {
    DVDLowReadDiskID(&CurrDiskID, cbForStateCoverClosed);
}

/** Callback after the disc ID read: goes on to the ID check (stateCheckID), or asks for the error. */
static void cbForStateCoverClosed(u32 intType) {
    if (intType == 16) {
		stateTimeout();
		return;
	}

    ASSERTLINE(1437, (intType & DVD_INTTYPE_CVR) == 0);

    if (intType & DVD_INTTYPE_TC) {
        ASSERTLINE(1442, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;
        stateCheckID();
        return;
    }

    ASSERTLINE(1454, intType == DVD_INTTYPE_DE);
    stateGettingError();
}

/** DVD state: waits until the drive cover is closed (DVDLowWaitCoverClose). */
static void stateMotorStopped() {
    DVDLowWaitCoverClose(cbForStateMotorStopped);
}

/**
 * Callback once the cover has closed: clears the cover interrupt,
 * sets the command state to COVER_CLOSED and goes to stateCoverClosed.
 */
static void cbForStateMotorStopped(u32 intType) {
    ASSERTLINE(1483, intType == DVD_INTTYPE_CVR);
    __DIRegs[1] = 0;
    executing->state = DVD_STATE_COVER_CLOSED;
    stateCoverClosed();
}

/**
 * DVD state: takes the next command off the waiting queue and starts it.
 * Stays idle if the queue is empty or the library is paused,
 * fails the command with -1 if a fatal error occurred, resumes a saved wait state,
 * or runs the command through stateBusy (or stateCoverClosed if the motor was stopped).
 */
static void stateReady() {
    if (__DVDCheckWaitingQueue() == 0) {
        executing = NULL;
        return;
    }

    if (PauseFlag != 0) {
        PausingFlag = 1;
        executing = NULL;
        return;
    }

    executing = __DVDPopWaitingQueue();

    if (FatalErrorFlag) {
        DVDCommandBlock* finished;

        executing->state = DVD_STATE_FATAL_ERROR;
        finished = executing;
        executing = &DummyCommandBlock;
        if (finished->callback) {
            (*finished->callback)(-1, finished);
        }

        stateReady();
        return;
    }

    CurrCommand = executing->command;
    if (ResumeFromHere != 0) {
        switch (ResumeFromHere) {
        case 2:
            executing->state = DVD_STATE_RETRY;
            stateMotorStopped();
            break;
        case 3:
            executing->state = DVD_STATE_NO_DISK;
            stateMotorStopped();
            break;
        case 4:
            executing->state = DVD_STATE_COVER_OPEN;
            stateMotorStopped();
            break;
        case 1:
        case 6:
        case 7:
            executing->state = DVD_STATE_COVER_CLOSED;
            stateCoverClosed();
            break;
        case 5:
            stateError(CancelLastError);
            break;
        }

        ResumeFromHere = 0;
        return;
    }

    if (MotorState == 0) {
        executing->state = DVD_STATE_BUSY;
        stateBusy(executing);
    } else {
        stateCoverClosed();
    }
}

/**
 * DVD state: issues the executing command to the drive by command number (read in chunks of up to 0x80000 bytes,
 * seek, disc ID, change disc, the audio stream commands, buffer config, inquiry, stop motor).
 * Unknown commands go to the optional command hook.
 */
static void stateBusy(DVDCommandBlock* block) {
    DVDCommandBlock* finished;
    LastState = stateBusy;

    switch(block->command) {
    case DVD_COMMAND_READID:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = 0x20;
        DVDLowReadDiskID(block->addr, cbForStateBusy);
        return;
    case DVD_COMMAND_READ:
    case DVD_COMMAND_BSREAD:
        if (block->length == 0) {
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = 0;

            if (finished->callback != 0) {
                (*finished->callback)(0, finished);
            }

            stateReady();
        } else {
            __DIRegs[1] = __DIRegs[1];
            block->currTransferSize = (block->length - block->transferredSize > 0x80000) ? 0x80000 : (block->length - block->transferredSize);
            DVDLowRead((char*)block->addr + block->transferredSize, block->currTransferSize, block->offset + block->transferredSize, cbForStateBusy);
        }
        return;
    case DVD_COMMAND_SEEK:
        __DIRegs[1] = __DIRegs[1];
        DVDLowSeek(block->offset, cbForStateBusy);
        return;
    case DVD_COMMAND_CHANGE_DISK:
        DVDLowStopMotor(cbForStateBusy);
        return;
    case DVD_COMMAND_BS_CHANGE_DISK:
        DVDLowStopMotor(cbForStateBusy);
        return;
    case DVD_COMMAND_INITSTREAM:
        __DIRegs[1] = __DIRegs[1];
        if (AutoFinishing != 0) {
            executing->currTransferSize = 0;
            DVDLowRequestAudioStatus(0, cbForStateBusy);
            return;
        }
        executing->currTransferSize = 1;
        DVDLowAudioStream(0, block->length, block->offset, cbForStateBusy);
        return;
    case DVD_COMMAND_CANCELSTREAM:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioStream(0x10000, 0U, 0U, cbForStateBusy);
        return;
    case DVD_COMMAND_STOP_STREAM_AT_END:
        __DIRegs[1] = __DIRegs[1];
        AutoFinishing = 1;
        DVDLowAudioStream(0, 0U, 0U, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_AUDIO_ERROR:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_PLAY_ADDR:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x10000, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_START_ADDR:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x20000, cbForStateBusy);
        return;
    case DVD_COMMAND_REQUEST_LENGTH:
        __DIRegs[1] = __DIRegs[1];
        DVDLowRequestAudioStatus(0x30000, cbForStateBusy);
        return;
    case DVD_COMMAND_AUDIO_BUFFER_CONFIG:
        __DIRegs[1] = __DIRegs[1];
        DVDLowAudioBufferConfig(block->offset, block->length, cbForStateBusy);
        return;
    case DVD_COMMAND_INQUIRY:
        __DIRegs[1] = __DIRegs[1];
        block->currTransferSize = 0x20;
        DVDLowInquiry(block->addr, cbForStateBusy);
        return;
    case DVD_COMMAND_UNK_16:
        __DIRegs[1] = __DIRegs[1];
        DVDLowStopMotor(cbForStateBusy);
        return;
    default:
        checkOptionalCommand(block, cbForStateBusy);
        return;
    }
}

/** Extra command numbers (three slots, 0xFFFFFFFF: empty) treated as immediate commands with a result. */
static u32 ImmCommand[3] = {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF};

/** Adds a command number to the list (three slots) of immediate commands that return a result in DI register 8. */
void __DVDSetImmCommand(u32 command) {
    static u32 immCount;
    ASSERTLINE(1790, immCount < sizeof(ImmCommand)/sizeof(ImmCommand[0]));
    ImmCommand[immCount++] = command;
}

/** Adds a command number to the list of commands that move data by DMA. */
void __DVDSetDmaCommand(u32 command) {
    static u32 dmaCount;
    ASSERTLINE(1798, dmaCount < sizeof(DmaCommand)/sizeof(DmaCommand[0]));
    DmaCommand[dmaCount++] = command;
}

/**
 * Returns true for commands that give a result in DI register 8:
 * audio error, play address, start address and length requests, plus any added with __DVDSetImmCommand.
 */
static BOOL IsImmCommandWithResult(u32 command) {
    u32 i;

    if (command == 9 || command == 10 || command == 11 || command == 12) {
        return 1;
    }

    for (i = 0; i < 3; i++) {
        if (command == ImmCommand[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * Returns true for commands that DMA data into memory:
 * read, BS read, disc ID read and inquiry, plus any added with __DVDSetDmaCommand.
 */
static int IsDmaCommand(u32 command) {
    u32 i;

    if (command == 1 || command == 4 || command == 5 || command == 14) {
        return 1;
    }

    for (i = 0; i < 1; i++) {
        if (command == DmaCommand[i]) {
            return TRUE;
        }
    }

    return FALSE;
}

/**
 * Completion callback of the executing command.
 * Handles timeouts, breaks (cancel), disc change completion and DMA progress,
 * then finishes the command with its callback (bytes transferred for DMA commands,
 * the register value for immediate ones, 0 otherwise) and starts the next one;
 * anything unexpected goes to error handling.
 */
static void cbForStateBusy(u32 intType) {
    DVDCommandBlock* finished;
    s32 result;

    if (intType == 16) {
		stateTimeout();
		return;
	}

    if ((CurrCommand == DVD_COMMAND_CHANGE_DISK) || (CurrCommand == DVD_COMMAND_BS_CHANGE_DISK)) {
        if (intType & DVD_INTTYPE_DE) {
            stateError(0x01234567);
            return;
        }

        ASSERTLINE(1857, intType == DVD_INTTYPE_TC);
        NumInternalRetry = 0;

        if (CurrCommand == DVD_COMMAND_BS_CHANGE_DISK) {
            ResetRequired = 1;
        }

        if (CheckCancel(7) == FALSE) {
            executing->state = DVD_STATE_MOTOR_STOPPED;
            stateMotorStopped();
        }
        return;
    }

    ASSERTLINE(1877, (intType & DVD_INTTYPE_CVR) == 0);

    if (IsDmaCommand(CurrCommand)) {
        executing->transferredSize += executing->currTransferSize - __DIRegs[6];
    }

    if (intType & 8) {
        Canceling = 0;
        finished = executing;
        executing = &DummyCommandBlock;
        finished->state = DVD_STATE_CANCELED;

        if (finished->callback) {
            finished->callback(-3, finished);
        }

        if (CancelCallback) {
            CancelCallback(0, finished);
        }

        stateReady();
        return;
    }

    if (intType & 1) {
        ASSERTLINE(1915, (intType & DVD_INTTYPE_DE) == 0);
        NumInternalRetry = 0;

        if (CurrCommand == 0x10) {
            MotorState = 1;
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = 0;

            if (finished->callback != 0) {
                (*finished->callback)(0, finished);
            }

            stateReady();
            return;
        }

        if (CheckCancel(0) != FALSE) {
            return;
        }

        if (IsDmaCommand(CurrCommand)) {
            if (executing->transferredSize != executing->length) {
                stateBusy(executing);
                return;
            }

            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(finished->transferredSize, finished);
            }

            stateReady();
            return;
        } else if (IsImmCommandWithResult(CurrCommand)) {
            if (CurrCommand == DVD_COMMAND_REQUEST_START_ADDR || CurrCommand == DVD_COMMAND_REQUEST_PLAY_ADDR) {
                result = __DIRegs[8] * 4;
            } else {
                result = __DIRegs[8];
            }

            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(result, finished);
            }

            stateReady();
            return;
        } else if (CurrCommand == DVD_COMMAND_INITSTREAM) {
            if (executing->currTransferSize == 0) {
                if (__DIRegs[8] & 1) {
                    finished = executing;
                    executing = &DummyCommandBlock;
                    finished->state = DVD_STATE_IGNORED;
                    if (finished->callback) {
                        finished->callback(-2, finished);
                    }
                    stateReady();
                    return;
                }

                AutoFinishing = 0;
                executing->currTransferSize = 1;
                DVDLowAudioStream(0, executing->length, executing->offset, cbForStateBusy);
                return;
            }

            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(0, finished);
            }

            stateReady();
            return;
        } else {
            finished = executing;
            executing = &DummyCommandBlock;
            finished->state = DVD_STATE_END;
            if (finished->callback) {
                finished->callback(0, finished);
            }

            stateReady();
            return;
        }
    } else {
        ASSERTLINE(2063, intType == DVD_INTTYPE_DE);

        if (CurrCommand == 14) {
			stateError(0x01234567);
			return;
		}

		if ((CurrCommand == 1 || CurrCommand == 4 || CurrCommand == 5 || CurrCommand == 14)
		    && (executing->transferredSize == executing->length)) {

			if (CheckCancel(0)) {
				return;
			}
			finished  = executing;
			executing = &DummyCommandBlock;

			finished->state = DVD_STATE_END;
			if (finished->callback) {
				(finished->callback)((s32)finished->transferredSize, finished);
			}
			stateReady();
			return;
		}

        stateGettingError();
    }
}

/** Returns the address of issueCommand. */
void* __DVDGetIssueCommandAddr(void) {
    return issueCommand;
}

/**
 * Queues a command block at the given priority.
 * First invalidates the destination cache range for reads and inquiries if auto invalidation is on,
 * then starts it immediately if the drive is idle and not paused.
 * Returns the result of pushing it on the waiting queue.
 */
static int issueCommand(s32 prio, DVDCommandBlock* block) {
    BOOL level;
    int result;

    if (autoInvalidation != 0 && (block->command == DVD_COMMAND_READ || block->command == DVD_COMMAND_BSREAD 
        || block->command == DVD_COMMAND_READID || block->command == DVD_COMMAND_INQUIRY)) {
        DCInvalidateRange(block->addr, block->length);
    }

    level = OSDisableInterrupts();
#if DEBUG
    if (executing == block || block->state == DVD_STATE_WAITING && __DVDIsBlockInWaitingQueue(block)) {
        ASSERTMSGLINE(2151, FALSE, "DVD library: Specified command block (or file info) is already in use\n");
    }
#endif

    block->state = DVD_STATE_WAITING;
    result = __DVDPushWaitingQueue(prio, block);
    if (executing == NULL && PauseFlag == 0) {
        stateReady();
    }

    OSRestoreInterrupts(level);
    return result;
}

/**
 * Queues a read of length bytes from an absolute disc offset into addr, at the given priority;
 * the callback gets the bytes read.
 */
int DVDReadAbsAsyncPrio(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback, s32 prio) {
    int idle;

    ASSERTMSGLINE(2191, block, "DVDReadAbsAsync(): null pointer is specified to command block address.");
    ASSERTMSGLINE(2192, addr, "DVDReadAbsAsync(): null pointer is specified to addr.");
    ASSERTMSGLINE(2194, !OFFSET(addr, 32), "DVDReadAbsAsync(): address must be aligned with 32 byte boundary.");
    ASSERTMSGLINE(2196, !(length & (32-1)), "DVDReadAbsAsync(): length must be a multiple of 32.");
    ASSERTMSGLINE(2198, !(offset & (4-1)), "DVDReadAbsAsync(): offset must be a multiple of 4.");
    ASSERTMSGLINE(2200, length >= 0, "DVD read: negative value was specified to length of the read\n");
    
    block->command = DVD_COMMAND_READ;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(prio, block);
    ASSERTMSGLINE(2210, idle, "DVDReadAbsAsync(): command block is used for processing previous request.");
    return idle;
}

/** Queues a seek to an absolute disc offset. */
int DVDSeekAbsAsyncPrio(DVDCommandBlock* block, s32 offset, DVDCBCallback callback, s32 prio) {
    int idle;

    ASSERTMSGLINE(2233, block, "DVDSeekAbs(): null pointer is specified to command block address.");
    ASSERTMSGLINE(2235, !(offset & (4-1)), "DVDSeekAbs(): offset must be a multiple of 4.");
    
    block->command = DVD_COMMAND_SEEK;
    block->offset = offset;
    block->callback = callback;

    idle = issueCommand(prio, block);
    ASSERTMSGLINE(2242, idle, "DVDSeekAbs(): command block is used for processing previous request.");
    return idle;
}

/**
 * Queues a read from an absolute offset at priority 2 for the boot-strap code (used by __fstLoad);
 * a failed disc check fails it with -4 instead of retrying.
 */
int DVDReadAbsAsyncForBS(DVDCommandBlock* block, void* addr, s32 length, s32 offset, DVDCBCallback callback) {
    int idle;

    ASSERTMSGLINE(2272, block, "DVDReadAbsAsyncForBS(): null pointer is specified to command block address.");
    ASSERTMSGLINE(2273, addr, "DVDReadAbsAsyncForBS(): null pointer is specified to addr.");
    ASSERTMSGLINE(2275, !OFFSET(addr, 32), "DVDReadAbsAsyncForBS(): address must be aligned with 32 byte boundary.");
    ASSERTMSGLINE(2277, !(length & (32-1)), "DVDReadAbsAsyncForBS(): length must be a multiple of 32.");
    ASSERTMSGLINE(2279, !(offset & (4-1)), "DVDReadAbsAsyncForBS(): offset must be a multiple of 4.");
    
    block->command = DVD_COMMAND_BSREAD;
    block->addr = addr;
    block->length = length;
    block->offset = offset;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    ASSERTMSGLINE(2289, idle, "DVDReadAbsAsyncForBS(): command block is used for processing previous request.");
    return idle;
}

/** Queues a priority 2 read of the 0x20 byte disc ID from the start of the disc. */
int DVDReadDiskID(DVDCommandBlock* block, DVDDiskID* diskID, DVDCBCallback callback) {
    int idle;

    ASSERTMSGLINE(2312, block, "DVDReadDiskID(): null pointer is specified to command block address.");
    ASSERTMSGLINE(2313, diskID, "DVDReadDiskID(): null pointer is specified to id address.");
    ASSERTMSGLINE(2315, !OFFSET(diskID, 32), "DVDReadDiskID(): id must be aligned with 32 byte boundary.");

    block->command = DVD_COMMAND_READID;
    block->addr = diskID;
    block->length = 0x20;
    block->offset = 0;
    block->transferredSize = 0;
    block->callback = callback;

    idle = issueCommand(2, block);
    ASSERTMSGLINE(2325, idle, "DVDReadDiskID(): command block is used for processing previous request.");
    return idle;
}

/** Queues (priority 1) a command that prepares audio streaming of length bytes from an absolute disc offset. */
int DVDPrepareStreamAbsAsync(DVDCommandBlock* block, u32 length, u32 offset, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_INITSTREAM;
    block->length = length;
    block->offset = offset;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

/** Queues (priority 1) a command that cancels the audio stream. */
int DVDCancelStreamAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_CANCELSTREAM;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

/**
 * Cancels the audio stream and sleeps until it is done.
 * Returns the result of the command, or -1 if it could not be queued.
 */
s32 DVDCancelStream(DVDCommandBlock* block) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDCancelStreamAsync(block, cbForCancelStreamSync);
    if (result == 0) {
        return -1; 
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            retVal = block->transferredSize;
            break;
        } 

        OSSleepThread(&__DVDThreadQueue);
    }
    
    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Stores the command result in the block and wakes the threads sleeping on the DVD thread queue. */
static void cbForCancelStreamSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

/** Queues (priority 1) a command that makes the drive stop the audio stream when it reaches its end. */
int DVDStopStreamAtEndAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_STOP_STREAM_AT_END;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

/** Waits for the stop-at-end command; returns its result, or -1 if it could not be queued. */
s32 DVDStopStreamAtEnd(DVDCommandBlock* block) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDStopStreamAtEndAsync(block, cbForStopStreamAtEndSync);
    if (result == 0) {
        return -1; 
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            retVal = block->transferredSize;
            break;
        } 

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Stores the command result in the block and wakes the threads sleeping on the DVD thread queue. */
static void cbForStopStreamAtEndSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

/** Queues (priority 1) a request for the audio stream error status. */
int DVDGetStreamErrorStatusAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_REQUEST_AUDIO_ERROR;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

/** Waits for the stream error status request; returns the status, or -1 if it could not be queued. */
s32 DVDGetStreamErrorStatus(DVDCommandBlock* block) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDGetStreamErrorStatusAsync(block, cbForGetStreamErrorStatusSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            retVal = block->transferredSize;
            break;
        } 

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Stores the command result in the block and wakes the threads sleeping on the DVD thread queue. */
static void cbForGetStreamErrorStatusSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

/** Queues (priority 1) a request for the disc address the audio stream is playing; the callback gets the address. */
int DVDGetStreamPlayAddrAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_REQUEST_PLAY_ADDR;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

/**
 * Waits for the play address request; returns the address (the register value times 4),
 * or -1 if it could not be queued.
 */
s32 DVDGetStreamPlayAddr(DVDCommandBlock* block) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDGetStreamPlayAddrAsync(block, cbForGetStreamPlayAddrSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            retVal = block->transferredSize;
            break;
        } 

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Stores the command result in the block and wakes the threads sleeping on the DVD thread queue. */
static void cbForGetStreamPlayAddrSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

/** Queues (priority 1) a request for the disc address where the audio stream started. */
int DVDGetStreamStartAddrAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_REQUEST_START_ADDR;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

/**
 * Waits for the start address request; returns the address (the register value times 4),
 * or -1 if it could not be queued.
 */
s32 DVDGetStreamStartAddr(DVDCommandBlock* block) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDGetStreamStartAddrAsync(block, cbForGetStreamStartAddrSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            retVal = block->transferredSize;
            break;
        } 

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Stores the command result in the block and wakes the threads sleeping on the DVD thread queue. */
static void cbForGetStreamStartAddrSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

/** Queues (priority 1) a request for the length of the current audio stream. */
int DVDGetStreamLengthAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_REQUEST_LENGTH;
    block->callback = callback;
    idle = issueCommand(1, block);
    return idle;
}

/** Waits for the stream length request; returns the length, or -1 if it could not be queued. */
s32 DVDGetStreamLength(DVDCommandBlock* block) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDGetStreamLengthAsync(block, cbForGetStreamLengthSync);
    if (result == 0) {
        return -1;
    }
    enabled = OSDisableInterrupts();

    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            retVal = block->transferredSize;
            break;
        } 

        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Stores the command result in the block and wakes the threads sleeping on the DVD thread queue. */
static void cbForGetStreamLengthSync(s32 result, DVDCommandBlock* block) {
    block->transferredSize = (u32)result;
    OSWakeupThread(&__DVDThreadQueue);
}

/**
 * Queues a priority 2 command that sets the drive's audio buffer:
 * enable flag and size (kept in the block's offset and length fields). No return value.
 */
void __DVDAudioBufferConfig(DVDCommandBlock* block, u32 enable, u32 size, DVDCBCallback callback) {
    int idle;

    block->command = DVD_COMMAND_AUDIO_BUFFER_CONFIG;
    block->offset = enable;
    block->length = size;
    block->callback = callback;
    idle = issueCommand(2, block);
}

/** Queues a priority 2 boot-strap disc change, which stops the motor and waits for a cover cycle. */
int DVDChangeDiskAsyncForBS(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;

    ASSERTMSGLINE(2869, block, "DVDChangeDiskAsyncForBS(): null pointer is specified to command block address.");
    
    block->command = DVD_COMMAND_BS_CHANGE_DISK;
    block->callback = callback;
    idle = issueCommand(2, block);
    ASSERTMSGLINE(2875, idle, "DVDChangeDiskAsyncForBS(): command block is used for processing previous request.");
    return idle;
}

/**
 * Queues a priority 2 disc change.
 * The motor is stopped and the drive waits for the cover to be opened and closed;
 * the new disc must match id (checked with DVDCompareDiskID) and its FST is loaded.
 * The cached FST range is invalidated first.
 */
int DVDChangeDiskAsync(DVDCommandBlock* block, DVDDiskID* id, DVDCBCallback callback) {
    int idle;

    ASSERTMSGLINE(2896, block, "DVDChangeDisk(): null pointer is specified to command block address.");
    ASSERTMSGLINE(2897, id, "DVDChangeDisk(): null pointer is specified to id address.");

    if (id->company[0] == 0) {
        OSReport("DVDChangeDiskAsync(): You can't specify NULL to company name.  \n");
        DVD_ASSERTMSGLINE(2902, 0, "");
    }

    block->command = DVD_COMMAND_CHANGE_DISK;
    block->id = id;
    block->callback = callback;
    DCInvalidateRange(bootInfo->FSTLocation, bootInfo->FSTMaxLength);
    
    idle = issueCommand(2, block);
    ASSERTMSGLINE(2913, idle, "DVDChangeDisk(): command block is used for processing previous request.");
    return idle;
}

/**
 * Waits for the disc change to finish.
 * Returns 0 on success, -1 on a fatal error or if it could not be queued, -3 if canceled.
 */
s32 DVDChangeDisk(DVDCommandBlock* block, DVDDiskID* id) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDChangeDiskAsync(block, id, cbForChangeDiskSync);
    if (result == 0) {
        return -1;
    }

    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == DVD_STATE_END) {
            retVal = 0;
            break;
        } else if (state == DVD_STATE_FATAL_ERROR) {
            retVal = -1;
            break;
        } else if (state == DVD_STATE_CANCELED) {
            retVal = -3;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Wakes the threads sleeping on the DVD thread queue so DVDChangeDisk can check the command state. */
static void cbForChangeDiskSync(s32 result, DVDCommandBlock* block) {
    OSWakeupThread(&__DVDThreadQueue);
}

/**
 * Queues a priority 2 command that stops the disc motor;
 * the next command then goes through the cover-closed spin-up path.
 */
int DVDStopMotorAsync(DVDCommandBlock* block, DVDCBCallback callback) {
    int idle;
    ASSERTMSGLINE(2996, block, "DVDStopMotor(): Null address was specified for block");

    block->command = DVD_COMMAND_UNK_16;
    block->callback = callback;
    
    idle = issueCommand(2, block);
    ASSERTMSGLINE(3002, idle, "DVDStopMotor(): command block is used for processing previous request.");
    return idle;
}

/**
 * Waits for the stop-motor command.
 * Returns 0 on success, -1 on a fatal error or if it could not be queued, -3 if canceled.
 */
s32 DVDStopMotor(DVDCommandBlock* block) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDStopMotorAsync(block, cbForStopMotorSync);
    if (result == 0) {
        return -1;
    }

    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == DVD_STATE_END) {
            retVal = 0;
            break;
        } else if (state == DVD_STATE_FATAL_ERROR) {
            retVal = -1;
            break;
        } else if (state == DVD_STATE_CANCELED) {
            retVal = -3;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Wakes the threads sleeping on the DVD thread queue so DVDStopMotor can check the command state. */
static void cbForStopMotorSync(s32 result, DVDCommandBlock* block) {
    OSWakeupThread(&__DVDThreadQueue);
}

/** Queues a priority 2 drive inquiry that stores the drive's DVDDriveInfo in info. */
int DVDInquiryAsync(DVDCommandBlock* block, DVDDriveInfo* info, DVDCBCallback callback) {
    int idle;

    ASSERTMSGLINE(3085, block, "DVDInquiry(): Null address was specified for block");
    ASSERTMSGLINE(3086, info, "DVDInquiry(): Null address was specified for info");
    ASSERTMSGLINE(3088, !OFFSET(info, 32), "DVDInquiry(): Address for info is not 32 bytes aligned");

    block->command = DVD_COMMAND_INQUIRY;
    block->addr = info;
    block->length = 0x20;
    block->transferredSize = 0;
    block->callback = callback;
    idle = issueCommand(2, block);
    return idle;
}

/**
 * Waits for the inquiry.
 * Returns the bytes transferred on success, -1 on a fatal error or if it could not be queued, -3 if canceled.
 */
s32 DVDInquiry(DVDCommandBlock* block, DVDDriveInfo* info) {
    int result;
    s32 state;
    BOOL enabled;
    s32 retVal;

    result = DVDInquiryAsync(block, info, cbForInquirySync);
    if (result == 0) {
        return -1;
    }

    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == DVD_STATE_END) {
            retVal = (u32)block->transferredSize;
            break;
        } else if (state == DVD_STATE_FATAL_ERROR) { 
            retVal = -1;
            break;
        } else if (state == DVD_STATE_CANCELED) {
            retVal = -3;
            break;
        }
        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Wakes the threads sleeping on the DVD thread queue so DVDInquiry can check the command state. */
static void cbForInquirySync(s32 result, DVDCommandBlock* block) {
    OSWakeupThread(&__DVDThreadQueue);
}

/** Resets the drive (DVDLowReset), clears the DI status, and clears the "reset required" and resume-from state. */
void DVDReset(void) {
    DVDLowReset();
    __DIRegs[0] = 0x2A;
    __DIRegs[1] = __DIRegs[1];
    ResetRequired = 0;
    ResumeFromHere = 0;
}

/** Returns whether the game must reset the drive (set after a failed boot-strap command or retry). */
int DVDResetRequired(void) {
    return ResetRequired;
}

/**
 * Returns the state of a command block, with interrupts off.
 * The internal COVER_CLOSED state is reported as 1 (busy).
 */
s32 DVDGetCommandBlockStatus(const DVDCommandBlock* block) {
    BOOL enabled;
    s32 retVal;

    ASSERTMSGLINE(3197, block, "DVDGetCommandBlockStatus(): null pointer is specified to command block address.");
    enabled = OSDisableInterrupts();

	if (block->state == 3) {
		retVal = 1;
	} else {
		retVal = block->state;
	}

	OSRestoreInterrupts(enabled);
	return retVal;
}

/**
 * Returns the state of the command being executed:
 * fatal error if one has occurred, pausing if paused, otherwise the executing block's state (END when idle).
 */
s32 DVDGetDriveStatus(void) {
	BOOL enabled = OSDisableInterrupts();
	s32 retVal;
    
	if (FatalErrorFlag != FALSE) {
		retVal = DVD_STATE_FATAL_ERROR;
	} else {
		if (PausingFlag != FALSE) {
			retVal = DVD_STATE_PAUSING;
		} else {
			if (executing == NULL) {
				retVal = DVD_STATE_END;
			} else if (executing == &DummyCommandBlock) {
				retVal = DVD_STATE_END;
			} else {
				retVal = DVDGetCommandBlockStatus((DVDCommandBlock*)executing);
			}
		}
	}
	OSRestoreInterrupts(enabled);
	return retVal;
}

/**
 * Sets whether issueCommand invalidates the data cache over the destination of reads and inquiries;
 * returns the old setting.
 */
BOOL DVDSetAutoInvalidation(BOOL autoInval) {
    BOOL prev;

    prev = autoInvalidation;
    autoInvalidation = autoInval;
    return prev;
}

/** Stops the state machine from starting new commands; the command already running finishes. */
void DVDPause(void) {
    BOOL level;

    level = OSDisableInterrupts();
    PauseFlag = 1;
    if (executing == NULL) {
        PausingFlag = 1;
    }
    OSRestoreInterrupts(level);
}

/** Clears the pause and starts the next queued command if the machine had stopped. */
void DVDResume(void) {
    BOOL level;

    level = OSDisableInterrupts();
    PauseFlag = 0;
    if (PausingFlag != 0) {
        PausingFlag = 0;
        stateReady();
    }
    OSRestoreInterrupts(level);
}

/**
 * Cancels a command block according to its state:
 * waiting blocks are removed from the queue and finish as canceled, a running read is broken off,
 * and blocks in cover-wait or retry states are completed as canceled. The callback is called with 0 when done.
 * Returns false if it cannot be cancelled (a cancel is already in progress).
 */
int DVDCancelAsync(DVDCommandBlock* block, DVDCBCallback callback) {
	BOOL enabled;
	DVDLowCallback old;
    DVDCommandBlock* finished;

	enabled = OSDisableInterrupts();

	switch (block->state) {
	case DVD_STATE_FATAL_ERROR:
	case DVD_STATE_END:
	case DVD_STATE_CANCELED:
		if (callback)
			(*callback)(0, block);
		break;
	case DVD_STATE_BUSY:
		if (Canceling) {
			OSRestoreInterrupts(enabled);
			return FALSE;
		}

		Canceling = TRUE;
		CancelCallback = callback;
		if (block->command == DVD_COMMAND_BSREAD || block->command == DVD_COMMAND_READ) {
			DVDLowBreak();
		}
		break;
	case DVD_STATE_WAITING:
		__DVDDequeueWaitingQueue(block);
		block->state = DVD_STATE_CANCELED;

		if (block->callback)
			(block->callback)(-3, block);

		if (callback)
			(*callback)(0, block);
		break;
	case DVD_STATE_COVER_CLOSED:
		switch (block->command) {
		case DVD_COMMAND_READID:
		case DVD_COMMAND_BSREAD:
		case DVD_COMMAND_AUDIO_BUFFER_CONFIG:
		case DVD_COMMAND_BS_CHANGE_DISK:
			if (callback)
				(*callback)(0, block);
			break;

		default:
			if (Canceling) {
				OSRestoreInterrupts(enabled);
				return FALSE;
			}
			Canceling = TRUE;
			CancelCallback = callback;
			break;
		}
		break;
	case DVD_STATE_NO_DISK:
	case DVD_STATE_COVER_OPEN:
	case DVD_STATE_WRONG_DISK:
	case DVD_STATE_MOTOR_STOPPED:
	case DVD_STATE_RETRY:
		old = DVDLowClearCallback();
        ASSERTLINE(3418, old == cbForStateMotorStopped);

		if (old != cbForStateMotorStopped) {
			OSRestoreInterrupts(enabled);
			return FALSE;
		}

		if (block->state == DVD_STATE_NO_DISK)
			ResumeFromHere = 3;
		if (block->state == DVD_STATE_COVER_OPEN)
			ResumeFromHere = 4;
		if (block->state == DVD_STATE_WRONG_DISK)
			ResumeFromHere = 1;
		if (block->state == DVD_STATE_RETRY)
			ResumeFromHere = 2;
		if (block->state == DVD_STATE_MOTOR_STOPPED)
			ResumeFromHere = 7;

        finished = executing;
        executing = &DummyCommandBlock;

		block->state = DVD_STATE_CANCELED;
		if (block->callback) {
			(block->callback)(-3, block);
		}

		if (callback) {
			(callback)(0, block);
		}
		stateReady();
		break;
	}

	OSRestoreInterrupts(enabled);
	return TRUE;
}

/** Cancels a command block and sleeps until it is finished. Returns 0, or -1 if the cancel could not be started. */
s32 DVDCancel(volatile DVDCommandBlock* block) {
    int result;
    s32 state;
    u32 command;
    BOOL enabled;

    result = DVDCancelAsync((void*)block, cbForCancelSync);
    if (result == 0) {
        return -1;
    }

    enabled = OSDisableInterrupts();
    while (1) {
        state = block->state;
        if (state == DVD_STATE_END || state == DVD_STATE_FATAL_ERROR || state == DVD_STATE_CANCELED) {
            break;
        }

        if (state == DVD_STATE_COVER_CLOSED) {
            command = block->command;
            if ((command == DVD_COMMAND_BSREAD) || (command == DVD_COMMAND_READID) || (command == DVD_COMMAND_AUDIO_BUFFER_CONFIG) || (command == DVD_COMMAND_BS_CHANGE_DISK)) {
                break;
            }
        }
        OSSleepThread(&__DVDThreadQueue);
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

/** Wakes the threads sleeping on the DVD thread queue so DVDCancel can check the command state. */
static void cbForCancelSync(s32 result, DVDCommandBlock* block) {
    OSWakeupThread(&__DVDThreadQueue);
}

/**
 * Pauses the library, cancels every waiting block and the executing one, then resumes.
 * The callback runs when the running command has stopped (at once if none).
 */
int DVDCancelAllAsync(DVDCBCallback callback) {
    BOOL enabled;
    DVDCommandBlock* p;
    int retVal;

    enabled = OSDisableInterrupts();
    DVDPause();
    while ((p = __DVDPopWaitingQueue())) {
        DVDCancelAsync(p, NULL);
    }

    if (executing) {
        retVal = DVDCancelAsync(executing, callback);
    } else {
        retVal = 1;
        if (callback) {
            callback(0, NULL);
        }
    }

    DVDResume();
    OSRestoreInterrupts(enabled);
    return retVal;
}

/** Cancels everything and sleeps until the cancel callback has fired. Returns 0, or -1 if the cancel failed. */
s32 DVDCancelAll(void) {
    int result;
    BOOL enabled;

    enabled = OSDisableInterrupts();
    CancelAllSyncComplete = 0;
    result = DVDCancelAllAsync(cbForCancelAllSync);
    if (result == 0) {
        OSRestoreInterrupts(enabled);
        return -1;
    }

    while (1) {
        if (CancelAllSyncComplete == 0) {
            OSSleepThread(&__DVDThreadQueue);
        } else {
            break;
        }
    }

    OSRestoreInterrupts(enabled);
    return 0;
}

/** Marks the cancel-all as complete and wakes the threads sleeping on the DVD thread queue. */
static void cbForCancelAllSync(s32 result, DVDCommandBlock* block) {
    CancelAllSyncComplete = 1;
    OSWakeupThread(&__DVDThreadQueue);
}

/** Returns the disc ID kept at the start of memory (the DVDDiskID field of the OS boot info). */
DVDDiskID* DVDGetCurrentDiskID(void) {
    return (void*)OSPhysicalToCached(0);
}

/**
 * Returns true if the drive is working normally:
 * busy or waiting is fine, while fatal error, retry, wrong disc and cover states give false.
 * When idle it also checks that the cover is closed in the DI cover register and no resume is pending.
 */
BOOL DVDCheckDisk(void) {
	BOOL enabled;
	s32 retVal;
	s32 state;
	u32 coverReg;

	enabled = OSDisableInterrupts();

	if (FatalErrorFlag) {
		state = -1;
	} else if (PausingFlag) {
		state = 8;
	} else {
		if (executing == NULL) {
			state = 0;
		} else if (executing == &DummyCommandBlock) {
			state = 0;
		} else {
			state = executing->state;
		}
	}

	switch (state) {
	case DVD_STATE_BUSY:
	case DVD_STATE_IGNORED:
	case DVD_STATE_CANCELED:
	case DVD_STATE_WAITING:
		retVal = TRUE;
		break;
	case DVD_STATE_FATAL_ERROR:
	case DVD_STATE_RETRY:
	case DVD_STATE_MOTOR_STOPPED:
	case DVD_STATE_COVER_CLOSED:
	case DVD_STATE_NO_DISK:
	case DVD_STATE_COVER_OPEN:
	case DVD_STATE_WRONG_DISK:
		retVal = FALSE;
		break;
	case DVD_STATE_END:
	case DVD_STATE_PAUSING:
		coverReg = __DIRegs[1];
		if (((coverReg >> 2) & 1) || (coverReg & 1)) {
			retVal = FALSE;
		} else if (ResumeFromHere != 0) {
			retVal = FALSE;
		} else {
            retVal = TRUE;
        }
	}

	OSRestoreInterrupts(enabled);
	return retVal;
}

/**
 * Prepares for a console reset: clears the waiting queue,
 * drops the running command's callback and cancels everything. The callback is called when that has finished.
 */
void __DVDPrepareResetAsync(DVDCBCallback callback) {
	BOOL enabled;

	enabled = OSDisableInterrupts();

	__DVDClearWaitingQueue();

	if (Canceling) {
		CancelCallback = callback;
	} else {
		if (executing) {
			executing->callback = NULL;
		}

		DVDCancelAllAsync(callback);
	}

	OSRestoreInterrupts(enabled);
}

/** Returns 1 if the alarm is the DVD library's reset alarm or one of the low-level driver's alarms. */
int __DVDTestAlarm(const OSAlarm* alarm) {
    if (alarm == &ResetAlarm) {
        return 1;
    }
    return __DVDLowTestAlarm(alarm);
}
