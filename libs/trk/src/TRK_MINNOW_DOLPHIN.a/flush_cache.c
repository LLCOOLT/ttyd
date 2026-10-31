/**
 * Makes a changed address range (r3 start, r4 length) visible to instruction fetch:
 * walks it in 32-byte cache lines with dcbst/dcbf and invalidates the instruction cache lines,
 * so breakpoints and writes from the debugger take effect.
 */
asm void TRK_flush_cache(void) {
    nofralloc
    lis r5, 0xffff
    ori r5, r5, 0xfff1
    and r5, r5, r3
    subf r3, r5, r3
    add r4, r4, r3
L_8025AF88:
    dcbst r0, r5
    dcbf r0, r5
    sync
    icbi r0, r5
    addic r5, r5, 0x8
    subic. r4, r4, 0x8
    bge L_8025AF88
    isync
    blr
}

