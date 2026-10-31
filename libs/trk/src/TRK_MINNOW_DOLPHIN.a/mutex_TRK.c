typedef int DSError;

/** Mutex stub: the nub does not need locking here, so this does nothing and returns 0. */
DSError TRKInitializeMutex(void* p) { return 0; }

/** Mutex stub: does nothing and returns 0. */
DSError TRKAcquireMutex(void* p) { return 0; }

/** Mutex stub: does nothing and returns 0. */
DSError TRKReleaseMutex(void* p) { return 0; }
