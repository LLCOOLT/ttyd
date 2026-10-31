#include <math.h>
#include <dolphin.h>
#include <dolphin/pad.h>

/**
 * Limits used to clamp raw controller readings: trigger minimum and maximum, then the same three values for
 * each stick.
 */
static const PADClampRegion ClampRegion = {
    // Triggers
    30,
    180,

    // Left stick
    15,
    72,
    40,

    // Right stick
    15,
    59,
    31,

    // Stick radii
    56,
    44,
};

// prototypes
static void ClampStick(s8* px, s8* py, s8 max, s8 xy, s8 min);
static void ClampCircle(s8* px, s8* py, s8 radius, s8 min);
static void ClampTrigger(u8* trigger, u8 min, u8 max);

/**
 * Clamps an analog stick to an octagon: removes a dead zone of min,
 * then scales (x, y) down when the weighted distance (xy for the diagonal, max for the axes) exceeds max.
 */
static void ClampStick(s8* px, s8* py, s8 max, s8 xy, s8 min) {
    int x = *px;
    int y = *py;
    int signX;
    int signY;
    int d;

    if (0 <= x) {
        signX = 1;
    } else {
        signX = -1;
        x = -x;
    }

    if (0 <= y) {
        signY = 1;
    } else {
        signY = -1;
        y = -y;
    }

    if (x <= min) {
        x = 0;
    } else {
        x -= min;
    }
    if (y <= min) {
        y = 0;
    } else {
        y -= min;
    }

    if (x == 0 && y == 0) {
        *px = *py = 0;
        return;
    }

    if (xy * y <= xy * x) {
        d = xy * x + (max - xy) * y;
        if (xy * max < d) {
            x = (s8)(xy * max * x / d);
            y = (s8)(xy * max * y / d);
        }
    } else {
        d = xy * y + (max - xy) * x;
        if (xy * max < d) {
            x = (s8)(xy * max * x / d);
            y = (s8)(xy * max * y / d);
        }
    }

    *px = (s8)(signX * x);
    *py = (s8)(signY * y);
}

/**
 * Clamps an analog stick to a circle: removes a dead zone of min on each axis,
 * then scales the vector down when its length exceeds radius.
 */
static void ClampCircle(s8* px, s8* py, s8 radius, s8 min) {
    int x = *px;
    int y = *py;
    int squared;
    int length;

    if (-min < x && x < min) {
        x = 0;
    } else if (0 < x) {
        x -= min;
    } else {
        x += min;
    }

    if (-min < y && y < min) {
        y = 0;
    } else if (0 < y) {
        y -= min;
    } else {
        y += min;
    }

    squared = x * x + y * y;
    if (radius * radius < squared) {
        length = sqrtf(squared);
        x = (x * radius) / length;
        y = (y * radius) / length;
    }

    *px = x;
    *py = y;
}

/** Clamps an analog trigger: values up to min read as 0, values above max are limited to max, and min is subtracted. */
static void ClampTrigger(u8* trigger, u8 min, u8 max) {
    if (*trigger <= min) {
        *trigger = 0;
    } else {
        if (max < *trigger) {
            *trigger = max;
        }
        *trigger -= min;
    }
}

/**
 * For each of the four PADStatus entries with no error,
 * clamps the stick and sub-stick to octagons and both triggers with the constants in ClampRegion.
 * Call it after PADRead.
 */
void PADClamp(PADStatus * status) {
    int i;

    for (i = 0; i < 4; i++, status++) {
        if (status->err == PAD_ERR_NONE) {
            ClampStick(&status->stickX, &status->stickY, ClampRegion.maxStick, ClampRegion.xyStick, ClampRegion.minStick);
            ClampStick(&status->substickX, &status->substickY, ClampRegion.maxSubstick, ClampRegion.xySubstick, ClampRegion.minSubstick);
            ClampTrigger(&status->triggerLeft, ClampRegion.minTrigger, ClampRegion.maxTrigger);
            ClampTrigger(&status->triggerRight, ClampRegion.minTrigger, ClampRegion.maxTrigger);
        }
    }
}

/** Like PADClamp, but clamps the stick and sub-stick to circles (ClampRegion radii) instead of octagons. */
void PADClampCircle(PADStatus* status) {
    int i;
    for (i = 0; i < 4; ++i, status++) {
        if (status->err == PAD_ERR_NONE) {
            ClampCircle(&status->stickX, &status->stickY, ClampRegion.radStick, ClampRegion.minStick);
            ClampCircle(&status->substickX, &status->substickY, ClampRegion.radSubstick, ClampRegion.minSubstick);
            ClampTrigger(&status->triggerLeft, ClampRegion.minTrigger, ClampRegion.maxTrigger);
            ClampTrigger(&status->triggerRight, ClampRegion.minTrigger, ClampRegion.maxTrigger);
        }
    }
}
