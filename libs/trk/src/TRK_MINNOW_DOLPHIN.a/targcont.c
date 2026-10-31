typedef int DSError;

DSError TRKTargetSetStopped(unsigned int stopped);
void UnreserveEXI2Port(void);
void TRKSwapAndGo(void);
void ReserveEXI2Port(void);

/**
 * Resumes the game: clears the stopped flag, releases the debug port,
 * swaps the saved game registers back in and runs it;
 * when the game next traps into the stub it claims the port again and returns 0.
 */
DSError TRKTargetContinue(void) {
    TRKTargetSetStopped(0);
    UnreserveEXI2Port();
    TRKSwapAndGo();
    ReserveEXI2Port();
    return 0;
}
