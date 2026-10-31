extern void (*__stdio_exit)(void);
void __close_all(void);

/** Registers __close_all as the stdio exit hook, so exit() flushes and closes all open streams. */
void __stdio_atexit(void) {
    __stdio_exit = __close_all;
}
