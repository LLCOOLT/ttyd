#include <dolphin.h>
#include <dolphin/ar.h>

#include "__ar.h"

#ifdef DEBUG
/** Library version string kept in the binary (debug build). */
const char* __ARQVersion = "<< Dolphin SDK - ARQ\tdebug build: Apr  5 2004 03:56:20 (0x2301) >>";
#else
/** Library version string kept in the binary (release build). */
const char* __ARQVersion = "<< Dolphin SDK - ARQ\trelease build: Apr  5 2004 04:15:04 (0x2301) >>";
#endif

static ARQRequest* __ARQRequestQueueHi;
static ARQRequest* __ARQRequestTailHi;
static ARQRequest* __ARQRequestQueueLo;
static ARQRequest* __ARQRequestTailLo;
static ARQRequest* __ARQRequestQueueTemp;
static ARQRequest* __ARQRequestTailTemp;
static ARQRequest* __ARQRequestPendingHi;
static ARQRequest* __ARQRequestPendingLo;
static ARQCallback __ARQCallbackHi;
static ARQCallback __ARQCallbackLo;
static u32 __ARQChunkSize;
static BOOL __ARQ_init_flag;

/**
 * Takes the next request off the high-priority queue, if any, and starts its DMA as a single transfer,
 * remembering its callback and making it the pending high-priority request.
 */
void __ARQPopTaskQueueHi(void) {
    if (__ARQRequestQueueHi) {
        if (__ARQRequestQueueHi->type == 0) {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->source, __ARQRequestQueueHi->dest, __ARQRequestQueueHi->length);
        } else {
            ARStartDMA(__ARQRequestQueueHi->type, __ARQRequestQueueHi->dest, __ARQRequestQueueHi->source, __ARQRequestQueueHi->length);
        }
        __ARQCallbackHi = __ARQRequestQueueHi->callback;
        __ARQRequestPendingHi = __ARQRequestQueueHi;
        __ARQRequestQueueHi = __ARQRequestQueueHi->next;
    }
}

/**
 * Advances the low-priority queue by one chunk: if no low-priority request is in progress it takes the next one;
 * then it starts a DMA of at most the chunk size (4 KB by default) from that request,
 * shrinking its remaining length and moving its addresses.
 * Only the last chunk sets the completion callback,
 * so a large transfer is split so that high-priority requests can run in between.
 */
void __ARQServiceQueueLo(void) {
    if (__ARQRequestPendingLo == 0 && __ARQRequestQueueLo) {
        __ARQRequestPendingLo = __ARQRequestQueueLo;
        __ARQRequestQueueLo = __ARQRequestQueueLo->next;
    }

    if (__ARQRequestPendingLo) {
        if (__ARQRequestPendingLo->length <= __ARQChunkSize) {
            if (__ARQRequestPendingLo->type == 0) {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->length);
            } else {
                ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->source, __ARQRequestPendingLo->length);
            }
            __ARQCallbackLo = __ARQRequestPendingLo->callback;
        } else if (__ARQRequestPendingLo->type == 0) {
            ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->source, __ARQRequestPendingLo->dest, __ARQChunkSize);
        } else {
            ARStartDMA(__ARQRequestPendingLo->type, __ARQRequestPendingLo->dest, __ARQRequestPendingLo->source, __ARQChunkSize);
        }

        __ARQRequestPendingLo->length -= __ARQChunkSize;
        __ARQRequestPendingLo->source += __ARQChunkSize;
        __ARQRequestPendingLo->dest += __ARQChunkSize;
    }
}

/** Empty callback substituted for requests posted without one. */
void __ARQCallbackHack(u32 unused) {}

/**
 * DMA-complete handler of the ARQ (installed by ARQInit):
 * calls the finished request's callback (high priority first), clears the pending request,
 * then starts the next high-priority request or, if there is none, the next chunk of the low-priority one.
 */
void __ARQInterruptServiceRoutine() {
    if (__ARQCallbackHi) {
        __ARQCallbackHi((u32)__ARQRequestPendingHi);
        __ARQRequestPendingHi = NULL;
        __ARQCallbackHi = NULL;        
    } else if (__ARQCallbackLo) {
        __ARQCallbackLo((u32)__ARQRequestPendingLo);
        __ARQRequestPendingLo = NULL;
        __ARQCallbackLo = NULL;        
    }

    __ARQPopTaskQueueHi();

    if (__ARQRequestPendingHi == 0) {
        __ARQServiceQueueLo();
    }
}

/** Empties the temporary queue used while removing requests. */
void __ARQInitTempQueue(void) {
    __ARQRequestQueueTemp = NULL;
    __ARQRequestTailTemp = NULL;
}

/** Appends a request to the temporary queue used while removing requests. */
void __ARQPushTempQueue(ARQRequest* task) {
    if (!__ARQRequestQueueTemp) {
        __ARQRequestQueueTemp = task;
        __ARQRequestTailTemp = task;
    } else {
        __ARQRequestTailTemp->next = task;
        __ARQRequestTailTemp = task;
    }
}

/**
 * Initialises the ARAM request queue once: empties both priority queues,
 * sets the chunk size to 4 KB and installs __ARQInterruptServiceRoutine as the ARAM DMA-complete callback.
 */
void ARQInit(void) {
    if (__ARQ_init_flag != TRUE) {
        OSRegisterVersion(__ARQVersion);

        __ARQRequestQueueHi = __ARQRequestQueueLo = NULL;
        __ARQChunkSize = 0x1000;
        ARRegisterDMACallback(__ARQInterruptServiceRoutine);
        __ARQRequestPendingHi = NULL;
        __ARQRequestPendingLo = NULL;
        __ARQCallbackHi = NULL;
        __ARQCallbackLo = NULL;
        __ARQ_init_flag = TRUE;
    }
}

/** Clears the initialised flag so ARQInit can run again. */
void ARQReset(void) {
    __ARQ_init_flag = FALSE;
}

/**
 * Queues an ARAM DMA request (type 0 main memory to ARAM, 1 ARAM to main memory; priority 0 low,
 * 1 high) tagged with an owner, with the source,
 * destination and length (a multiple of 32) and a completion callback.
 * If the DMA engine is idle it starts the request immediately.
 */
void ARQPostRequest(ARQRequest* request, u32 owner, u32 type, u32 priority, u32 source, u32 dest, u32 length, ARQCallback callback) {
    BOOL level;

    ASSERTLINE(437, request);
    ASSERTLINE(438, (type == ARQ_TYPE_MRAM_TO_ARAM) || (type == ARQ_TYPE_ARAM_TO_MRAM));
    ASSERTLINE(439, (priority == ARQ_PRIORITY_LOW) || (priority == ARQ_PRIORITY_HIGH));
    ASSERTLINE(442, (length % ARQ_DMA_ALIGNMENT) == 0);

    request->next = NULL;
    request->owner = owner;
    request->type = type;
    request->source = source;
    request->dest = dest;
    request->length = length;
    if (callback) {
        request->callback = callback;
    } else {
        request->callback = __ARQCallbackHack;
    }

    level = OSDisableInterrupts();
    switch(priority) {
    case ARQ_PRIORITY_LOW:
        if (__ARQRequestQueueLo) {
            __ARQRequestTailLo->next = request;
        } else {
            __ARQRequestQueueLo = request;
        }
        __ARQRequestTailLo = request;
        break;
    case ARQ_PRIORITY_HIGH:
        if (__ARQRequestQueueHi) {
            __ARQRequestTailHi->next = request;
        } else {
            __ARQRequestQueueHi = request;
        }
        __ARQRequestTailHi = request;
        break;
    }

    if ((__ARQRequestPendingHi == 0) && ( __ARQRequestPendingLo == 0)) {
        __ARQPopTaskQueueHi();
        if ( __ARQRequestPendingHi == 0) {
            __ARQServiceQueueLo();
        }
    }

    OSRestoreInterrupts(level);
}

/** Removes one request from both queues; a request whose transfer has already started is not affected. */
void ARQRemoveRequest(ARQRequest* request) {
    ARQRequest* thisRequest;
    BOOL level;

    level = OSDisableInterrupts();
    __ARQInitTempQueue();

    for (thisRequest = __ARQRequestQueueHi; thisRequest; thisRequest = thisRequest->next) {
        if (thisRequest != request) {
            __ARQPushTempQueue(thisRequest);
        }
    }

    __ARQRequestQueueHi = __ARQRequestQueueTemp;
    __ARQRequestTailHi = __ARQRequestTailTemp;
    __ARQInitTempQueue();

    for (thisRequest = __ARQRequestQueueLo; thisRequest; thisRequest = thisRequest->next) {
        if (thisRequest != request) {
            __ARQPushTempQueue(thisRequest);
        }
    }

    __ARQRequestQueueLo = __ARQRequestQueueTemp;
    __ARQRequestTailLo = __ARQRequestTailTemp;
    OSRestoreInterrupts(level);
}

/** Removes every queued request belonging to the given owner from both queues. */
void ARQRemoveOwnerRequest(u32 owner) {
    ARQRequest* thisRequest;
    BOOL level;

    level = OSDisableInterrupts();
    __ARQInitTempQueue();

    for (thisRequest = __ARQRequestQueueHi; thisRequest; thisRequest = thisRequest->next) {
        if (thisRequest->owner != owner) {
            __ARQPushTempQueue(thisRequest);
        }
    }

    __ARQRequestQueueHi = __ARQRequestQueueTemp;
    __ARQRequestTailHi = __ARQRequestTailTemp;
    __ARQInitTempQueue();

    for (thisRequest = __ARQRequestQueueLo; thisRequest; thisRequest = thisRequest->next) {
        if (thisRequest->owner != owner) {
            __ARQPushTempQueue(thisRequest);
        }
    }

    __ARQRequestQueueLo = __ARQRequestQueueTemp;
    __ARQRequestTailLo = __ARQRequestTailTemp;
    OSRestoreInterrupts(level);
}

/** Discards all queued requests in both priority queues. */
void ARQFlushQueue(void) {
    BOOL level;

    level = OSDisableInterrupts();
    __ARQRequestQueueHi = NULL;
    __ARQRequestTailHi = NULL;
    __ARQRequestQueueLo = NULL;
    __ARQRequestTailLo = NULL;

    OSRestoreInterrupts(level);
}

/** Sets the size that low-priority transfers are split into, rounded up to a multiple of 32 bytes. */
void ARQSetChunkSize(u32 size) {
    u32 i;

    i = size & 0x1F;
    if (i) {
        __ARQChunkSize = size + (0x20 - i);
        return;
    }
    __ARQChunkSize = size;
}

/** Returns the current chunk size in bytes. */
u32 ARQGetChunkSize(void) {
    return __ARQChunkSize;
}

/** Returns whether ARQInit has been called. */
BOOL ARQCheckInit(void) {
    return __ARQ_init_flag;
}
