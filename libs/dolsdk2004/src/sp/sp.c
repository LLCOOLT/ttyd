#include <dolphin.h>
#include <dolphin/sp.h>

/**
 * Relocates a sound table loaded from a file: adds the ARAM base to each entry's current,
 * end and loop addresses, converted to the unit of its sample format (4-bit ADPCM nibbles, 16-bit or 8-bit PCM
 * samples), and points looping-less entries at the zero sample (zeroBase).
 * ADPCM entries (types 0 and 1) are given their coefficient block, stored after the entries.
 */
void SPInitSoundTable(SPSoundTable* table, u32 aramBase, u32 zeroBase) {
    int i;
    SPSoundEntry* sound;
    SPADPCM* adpcm;
    u32 aramBase4, aramBase8, aramBase16;
    u32 zeroBase4, zeroBase8, zeroBase16;

    ASSERTLINE(34, table);

    aramBase4 = aramBase << 1;
    zeroBase4 = (zeroBase << 1) + 2;
    aramBase8 = aramBase;

    zeroBase8 = zeroBase;
    aramBase16 = aramBase >> 1;
    zeroBase16 = zeroBase >> 1;

    sound = &table->sound[0];
    adpcm = (SPADPCM*)&table->sound[table->entries];

    for (i = 0; i < table->entries; i++) {
        switch (sound->type) {
        case 0:
            sound->loopAddr = zeroBase4;
            sound->loopEndAddr = 0;
            sound->endAddr = aramBase4 + sound->endAddr;
            sound->currentAddr = aramBase4 + sound->currentAddr;
            sound->adpcm = adpcm;
            adpcm++;
            break;
        case 1:
            sound->loopAddr = aramBase4 + sound->loopAddr;
            sound->loopEndAddr = aramBase4 + sound->loopEndAddr;
            sound->endAddr = aramBase4 + sound->endAddr;
            sound->currentAddr = aramBase4 + sound->currentAddr;
            sound->adpcm = adpcm;
            adpcm++;
            break;
        case 2:
            sound->loopAddr = zeroBase16;
            sound->loopEndAddr = 0;
            sound->endAddr = aramBase16 + sound->endAddr;
            sound->currentAddr = aramBase16 + sound->currentAddr;
            break;
        case 3:
            sound->loopAddr = aramBase16 + sound->loopAddr;
            sound->loopEndAddr = aramBase16 + sound->loopEndAddr;
            sound->endAddr = aramBase16 + sound->endAddr;
            sound->currentAddr = aramBase16 + sound->currentAddr;
            break;
        case 4:
            sound->loopAddr = zeroBase8;
            sound->loopEndAddr = 0;
            sound->endAddr = aramBase8 + sound->endAddr;
            sound->currentAddr = aramBase8 + sound->currentAddr;
            break;
        case 5:
            sound->loopAddr = aramBase8 + sound->loopAddr;
            sound->loopEndAddr = aramBase8 + sound->loopEndAddr;
            sound->endAddr = aramBase8 + sound->endAddr;
            sound->currentAddr = aramBase8 + sound->currentAddr;
            break;
        }
        sound++;
    }
}

/** Returns entry number index of a sound table, or NULL when index is beyond the number of entries. */
SPSoundEntry* SPGetSoundEntry(SPSoundTable* table, u32 index) {
    ASSERTLINE(123, table);

    if (table->entries > index) {
        return &table->sound[index];
    }

    return NULL;
}

/**
 * Programs an AX voice parameter block to play a sound entry:
 * sets its format and loop flag (type 0/1 ADPCM, 2/3 16-bit PCM, 4/5 8-bit PCM, odd types loop), the loop,
 * end and current sample addresses, the ADPCM coefficients for ADPCM,
 * and the sample-rate-converter ratio for sampleRate relative to 32 kHz.
 * Queues the update to AX through the voice's sync flags, with interrupts disabled.
 */
void SPPrepareSound(SPSoundEntry* sound, AXVPB* axvpb, u32 sampleRate) {
    BOOL old;
    u32 srcBits;
    u32 loopAddr, endAddr, currentAddr;
    u16* p;
    u16* p1;

    ASSERTLINE(140, sound);
    ASSERTLINE(141, axvpb);

    srcBits = 0x10000 * ((f32)sampleRate / 32000);

    switch (sound->type) {
    case 0:
        loopAddr = sound->loopAddr;
        endAddr = sound->endAddr;
        currentAddr = sound->currentAddr;

        p = (u16*)&axvpb->pb.addr;
        p1 = (u16*)sound->adpcm;

        old = OSDisableInterrupts();

        *p++ = 0;
        *p++ = 0;
        *p++ = (u16)(loopAddr >> 0x10);
        *p++ = (u16)(loopAddr & 0xFFFF);
        *p++ = (u16)(endAddr >> 0x10);
        *p++ = (u16)(endAddr & 0xFFFF);
        *p++ = (u16)(currentAddr >> 0x10);
        *p++ = (u16)(currentAddr & 0xFFFF);
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = (u16)(srcBits >> 0x10);
        *p++ = (u16)(srcBits & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;

        axvpb->sync |= 0x61000;
        OSRestoreInterrupts(old);
        break;
    case 1:
        loopAddr = sound->loopAddr;
        endAddr = sound->loopEndAddr;
        currentAddr = sound->currentAddr;

        p = (u16*)&axvpb->pb.addr;
        p1 = (u16*)sound->adpcm;

        old = OSDisableInterrupts();

        *p++ = 1;
        *p++ = 0;
        *p++ = (u16)(loopAddr >> 0x10);
        *p++ = (u16)(loopAddr & 0xFFFF);
        *p++ = (u16)(endAddr >> 0x10);
        *p++ = (u16)(endAddr & 0xFFFF);
        *p++ = (u16)(currentAddr >> 0x10);
        *p++ = (u16)(currentAddr & 0xFFFF);
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = (u16)(srcBits >> 0x10);
        *p++ = (u16)(srcBits & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = *p1++;
        *p++ = *p1++;
        *p++ = *p1++;

        axvpb->sync |= 0x161000;
        OSRestoreInterrupts(old);
        break;
    case 2:
        loopAddr = sound->loopAddr;
        endAddr = sound->endAddr;
        currentAddr = sound->currentAddr;

        p = (u16*)&axvpb->pb.addr;

        old = OSDisableInterrupts();

        *p++ = 0;
        *p++ = 10;
        *p++ = (u16)(loopAddr >> 0x10);
        *p++ = (u16)(loopAddr & 0xFFFF);
        *p++ = (u16)(endAddr >> 0x10);
        *p++ = (u16)(endAddr & 0xFFFF);
        *p++ = (u16)(currentAddr >> 0x10);
        *p++ = (u16)(currentAddr & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0x800;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = (u16)(srcBits >> 0x10);
        *p++ = (u16)(srcBits & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;

        axvpb->sync |= 0x61000;
        OSRestoreInterrupts(old);
        break;
    case 3:
        loopAddr = sound->loopAddr;
        endAddr = sound->loopEndAddr;
        currentAddr = sound->currentAddr;

        p = (u16*)&axvpb->pb.addr;

        old = OSDisableInterrupts();

        *p++ = 1;
        *p++ = 10;
        *p++ = (u16)(loopAddr >> 0x10);
        *p++ = (u16)(loopAddr & 0xFFFF);
        *p++ = (u16)(endAddr >> 0x10);
        *p++ = (u16)(endAddr & 0xFFFF);
        *p++ = (u16)(currentAddr >> 0x10);
        *p++ = (u16)(currentAddr & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0x800;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = (u16)(srcBits >> 0x10);
        *p++ = (u16)(srcBits & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;

        axvpb->sync |= 0x61000;
        OSRestoreInterrupts(old);
        break;
    case 4:
        loopAddr = sound->loopAddr;
        endAddr = sound->endAddr;
        currentAddr = sound->currentAddr;

        p = (u16*)&axvpb->pb.addr;

        old = OSDisableInterrupts();

        *p++ = 0;
        *p++ = 0x19;
        *p++ = (u16)(loopAddr >> 0x10);
        *p++ = (u16)(loopAddr & 0xFFFF);
        *p++ = (u16)(endAddr >> 0x10);
        *p++ = (u16)(endAddr & 0xFFFF);
        *p++ = (u16)(currentAddr >> 0x10);
        *p++ = (u16)(currentAddr & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0x100;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = (u16)(srcBits >> 0x10);
        *p++ = (u16)(srcBits & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;

        axvpb->sync |= 0x61000;
        OSRestoreInterrupts(old);
        break;
    case 5:
        loopAddr = sound->loopAddr;
        endAddr = sound->loopEndAddr;
        currentAddr = sound->currentAddr;

        p = (u16*)&axvpb->pb.addr;

        old = OSDisableInterrupts();

        *p++ = 1;
        *p++ = 0x19;
        *p++ = (u16)(loopAddr >> 0x10);
        *p++ = (u16)(loopAddr & 0xFFFF);
        *p++ = (u16)(endAddr >> 0x10);
        *p++ = (u16)(endAddr & 0xFFFF);
        *p++ = (u16)(currentAddr >> 0x10);
        *p++ = (u16)(currentAddr & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0x100;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = (u16)(srcBits >> 0x10);
        *p++ = (u16)(srcBits & 0xFFFF);
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;
        *p++ = 0;

        axvpb->sync |= 0x61000;
        OSRestoreInterrupts(old);
        break;
    }
}

/**
 * Makes a playing voice finish: clears its loop flag and sets its end address to the sound's end address
 * so it stops after the current pass.
 */
void SPPrepareEnd(SPSoundEntry* sound, AXVPB* axvpb) {
    BOOL old;

    ASSERTLINE(497, sound);
    ASSERTLINE(498, axvpb);

    old = OSDisableInterrupts();

    axvpb->pb.addr.loopFlag = 0;
    axvpb->pb.addr.endAddressHi = sound->endAddr >> 0x10;
    axvpb->pb.addr.endAddressLo = sound->endAddr & 0xFFFF;

    axvpb->sync |= 0xA000;
    OSRestoreInterrupts(old);
}
