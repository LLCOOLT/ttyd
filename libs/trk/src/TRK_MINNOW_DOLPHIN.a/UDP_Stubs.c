#pragma weak udp_cc_initialize
/**
 * Weak stub for the network (BBA/UDP) debugger channel's initialize entry;
 * this build has no UDP transport, so it returns -1.
 */
int udp_cc_initialize(void* flagOut, void* func) { return -1; }

#pragma weak udp_cc_shutdown
/** Weak stub for the UDP debugger channel's shutdown entry; returns -1 (no UDP transport). */
int udp_cc_shutdown(void) { return -1; }

#pragma weak udp_cc_open
/** Weak stub for the UDP debugger channel's open entry; returns -1 (no UDP transport). */
int udp_cc_open(void) { return -1; }

#pragma weak udp_cc_close
/** Weak stub for the UDP debugger channel's close entry; returns -1 (no UDP transport). */
int udp_cc_close(void) { return -1; }

#pragma weak udp_cc_read
/** Weak stub for the UDP debugger channel's read entry; returns -1 (no UDP transport). */
int udp_cc_read(unsigned char* buf, int len) { return 0; }

#pragma weak udp_cc_write
/** Weak stub for the UDP debugger channel's write entry; returns -1 (no UDP transport). */
int udp_cc_write(const unsigned char* buf, int len) { return 0; }

#pragma weak udp_cc_peek
/** Weak stub for the UDP debugger channel's peek (bytes waiting) entry; returns -1 (no UDP transport). */
int udp_cc_peek(void) { return 0; }

#pragma weak udp_cc_pre_continue
/** Weak stub for the UDP debugger channel's hook that runs before the game resumes; returns -1 (no UDP transport). */
int udp_cc_pre_continue(void) { return -1; }

#pragma weak udp_cc_post_stop
/** Weak stub for the UDP debugger channel's hook that runs after the game stops; returns -1 (no UDP transport). */
int udp_cc_post_stop(void) { return -1; }
