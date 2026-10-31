#include <dolphin.h>
#include <dolphin/ax.h>

#include "__ax.h"

static AXPROFILE* __AXProfile;
static u32 __AXMaxProfiles;
static u32 __AXCurrentProfile;
static u32 __AXProfileInitialized;

/**
 * Returns the next slot of the profile ring buffer registered with AXInitProfile (advancing and wrapping the
 * index), or NULL if profiling was not set up.
 */
AXPROFILE* __AXGetCurrentProfile(void) {
    AXPROFILE* profile;

    if (__AXProfileInitialized != 0) {
        profile = &__AXProfile[__AXCurrentProfile];
        __AXCurrentProfile += 1;
        __AXCurrentProfile %= __AXMaxProfiles;
        return profile;
    }

    return 0;
}

/** Gives AX an array of maxProfiles profile records to fill, one per audio frame, and starts profiling. */
void AXInitProfile(AXPROFILE* profile, u32 maxProfiles) {
    ASSERTLINE(60, profile);
    ASSERTLINE(61, maxProfiles);

    __AXProfile = profile;
    __AXMaxProfiles = maxProfiles;
    __AXCurrentProfile = 0;
    __AXProfileInitialized = 1;
}

/**
 * Returns how many profile records were filled since the last call (minus one when any)
 * and restarts the ring from slot 0.
 */
u32 AXGetProfile(void) {
    BOOL old;
    u32 n;

    old = OSDisableInterrupts();
    n = __AXCurrentProfile;
    if (n != 0) {
        n -= 1;
    }

    __AXCurrentProfile = 0;
    OSRestoreInterrupts(old);
    return n;
}
