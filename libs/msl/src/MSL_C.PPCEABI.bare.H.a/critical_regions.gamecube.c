/**
 * No-op on GameCube: the MSL hook for leaving a thread-safety critical region (there is only one thread of
 * control).
 */
void __end_critical_region(int region) {}

/** No-op on GameCube: the MSL hook for entering a thread-safety critical region. */
void __begin_critical_region(int region) {}

/** No-op on GameCube: the MSL hook for destroying all critical-region locks at exit. */
void __kill_critical_regions(void) {}
