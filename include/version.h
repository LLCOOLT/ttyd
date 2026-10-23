#ifndef VERSION_H
#define VERSION_H

// VERSION_PICK(jp, us): the JP value, or the US value when building G8ME01.
#ifdef VERSION_G8ME01
#define VERSION_PICK(jp, us) (us)
#else
#define VERSION_PICK(jp, us) (jp)
#endif

// FPS_EASE(n): easing divisor. US scales it by the frame rate (gp->framerate / 60); JP uses n as is.
// Needs mario/mariost.h for gp.
#ifdef VERSION_G8ME01
#define FPS_EASE(n) ((n) * gp->framerate / 60.0f)
#else
#define FPS_EASE(n) (n)
#endif

// FPS_EASE_D(us, jp): for JP sites written with a double literal (8.0) that US writes as a float (8.0f).
#ifdef VERSION_G8ME01
#define FPS_EASE_D(us, jp) FPS_EASE(us)
#else
#define FPS_EASE_D(us, jp) (jp)
#endif

// FPS_FRAMES(n): integer frame count. US scales it to the frame rate (n * gp->framerate / 60).
#ifdef VERSION_G8ME01
#define FPS_FRAMES(n) ((n) * gp->framerate / 60)
#else
#define FPS_FRAMES(n) (n)
#endif

#endif
