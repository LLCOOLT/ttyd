#include <dolphin/card.h>

#include "os/__os.h"
#include "__card.h"

u16 __CARDVendorID = 0xFFFF;
u8 __CARDPermMask = 0x1C;

/** Sets the vendor ID this library will accept for cards whose EXI ID is 0x80000004 and returns the previous one. */
u16 CARDSetVendorID(u16 vendorID) {
    u16 prevID = __CARDVendorID;
    __CARDVendorID = vendorID;

    return prevID;
}

/** Returns the vendor ID previously set with CARDSetVendorID (0xFFFF if none). */
u16 CARDGetVendorID() {
    return __CARDVendorID;
}

/** Returns a 64-bit card serial number: the XOR of the header's serial words, read from the mount work area. */
s32 CARDGetSerialNo(s32 chan, u64* serialNo) {
    CARDControl* card;
    s32 result;
    CARDID* id;
    u64 code;
    int i;

    ASSERTLINE(105, 0 <= chan && chan < 2);

    if (!(0 <= chan && chan < 2)) {
        return CARD_RESULT_FATAL_ERROR;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    id = (CARDID*)card->workArea;
    for (code = 0, i = 0; i < sizeof(id->serial) / sizeof(u64); ++i) {
        code ^= *(u64*)&id->serial[sizeof(u64) * i];
    }
    *serialNo = code;

    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

/** Copies the 8 bytes stored in SRAM at offset 4 of the channel's flash ID. */
s32 CARDGetUniqueCode(s32 chan, u64* uniqueCode) {
    CARDControl* card;
    s32 result;
    OSSramEx* sram;

    ASSERTLINE(146, 0 <= chan && chan < 2);

    if (!(0 <= chan && chan < 2)) {
        return CARD_RESULT_FATAL_ERROR;
    }

    result = __CARDGetControlBlock(chan, &card);
    if (result < 0) {
        return result;
    }

    sram = __OSLockSramEx();
    memcpy(uniqueCode, &sram->flashID[chan][4], 8);
    __OSUnlockSramEx(0);
    return __CARDPutControlBlock(card, CARD_RESULT_READY);
}

/** Reads a file's permission byte from its directory entry. */
s32 CARDGetAttributes(s32 chan, s32 fileNo, u8* attr) {
    CARDDir dirent;
    s32 result;

    result = __CARDGetStatusEx(chan, fileNo, &dirent);
    if (result == 0) {
        *attr = dirent.permission;
    }

    return result;
}

#define CARDCheckAttr(attr, flag) ((u32)(attr & flag) != 0)

/**
 * Changes a file's permission byte.
 * Fails with NOPERM if it uses bits outside the allowed mask,
 * drops or adds the 0x20 and 0x40 bits in a disallowed way, or sets both of them.
 * Saves the directory through __CARDSetStatusExAsync.
 */
s32 CARDSetAttributesAsync(s32 chan, s32 fileNo, u8 attr, CARDCallback callback) {
    CARDDir dirent;
    s32 result;

    if (attr & ~__CARDPermMask) {
        return CARD_RESULT_NOPERM;
    }

    result = __CARDGetStatusEx(chan, fileNo, &dirent);
    if (result < 0) {
        return result;
    }

    if ((CARDCheckAttr(dirent.permission, 0x20) && !CARDCheckAttr(attr, 0x20)) || (CARDCheckAttr(dirent.permission, 0x40) && !CARDCheckAttr(attr, 0x40))) {
        return CARD_RESULT_NOPERM;
    }

    if ((CARDCheckAttr(attr, 0x20) && CARDCheckAttr(attr, 0x40)) || (CARDCheckAttr(attr, 0x20) && CARDCheckAttr(dirent.permission, 0x40)) || (CARDCheckAttr(attr, 0x40) && CARDCheckAttr(dirent.permission, 0x20))) {
        return CARD_RESULT_NOPERM;
    }

    dirent.permission = attr;
    return __CARDSetStatusExAsync(chan, fileNo, &dirent, callback);
}

/** Blocking CARDSetAttributesAsync. */
s32 CARDSetAttributes(s32 chan, s32 fileNo, u8 attr) {
    s32 result;

    result = CARDSetAttributesAsync(chan, fileNo, attr, __CARDSyncCallback);
    if (result < 0) {
        return result;
    }

    return __CARDSync(chan);
}

/** Sets or clears a bit in the permission mask that CARDSetAttributes accepts and returns whether it was set before. */
static int __CARDEnablePerm(u8 perm, BOOL enable) {
    int prev;
    prev = __CARDPermMask & perm ? TRUE : FALSE;

    if (enable) {
        __CARDPermMask |= perm;
    } else {
        __CARDPermMask &= ~perm;
    }

    return prev;
}

/** Allows or forbids permission bit 0x20 (global) in the mask and returns whether it was allowed before. */
int __CARDEnableGlobal(BOOL enable) {
    return __CARDEnablePerm(0x20, enable);
}

/** Allows or forbids permission bit 0x40 (company) in the mask and returns whether it was allowed before. */
int __CARDEnableCompany(BOOL enable) {
    return __CARDEnablePerm(0x40, enable);
}
