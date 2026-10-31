// PI, TWO_PI, DEG_TO_RAD and the other float constants the game code is compiled with.
#pragma once

// Maths constants shared by the game code.
//
// Each value is the single-precision literal the game's code was compiled with
// (MWCC folds the expression the same way whether the literal or the name is
// written), so replacing a literal with its name never changes the code.
// Use them where the code means the angle; keep the literal where the value
// only happens to be equal. Some files use slightly different values that
// are not these floats (3.141592f, 6.283184f, 57.29578f, 57.29492f); leave
// those as written, they are not the same constant.
//
// Degree/radian conversion appears in three spellings in the game, each with
// its own rounding, so keep the one a function uses:
//   DEG_TO_RAD * deg          (0.017453292f * deg)
//   TWO_PI * deg / 360.0f     (most effects and drivers)
//   PI * deg / 180.0f

#define PI 3.1415927f      // pi
#define TWO_PI 6.2831855f  // 2 pi, a full turn in radians
#define HALF_PI 1.5707964f // pi / 2, a quarter turn in radians

#define DEG_TO_RAD 0.017453292f // pi / 180: multiply degrees by it to get radians
#define RAD_TO_DEG 57.29579f    // 180 / pi as the game writes it (one float step above the nearest float,
                                // 57.29578f, which cam_road.c uses): multiply radians by it to get degrees
