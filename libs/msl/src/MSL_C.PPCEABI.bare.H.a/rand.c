static unsigned long next = 1;

/**
 * Standard rand(): LCG next = next * 1103515245 + 12345 on a static seed starting at 1,
 * returning bits 16..30 (0 to 32767).
 */
int rand(void) {
    next = next * 1103515245 + 12345;
    return (next >> 16) & 0x7FFF;
}
