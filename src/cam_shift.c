// Camera shift: pans the field camera sideways with the C stick (L/R shift) and eases it back.
#include "driver/camdrv.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "system.h"
#include "cam_road.h"
#include "version.h"

typedef struct CamShiftWork {
    f32 current;            // 0x0
    f32 target;             // 0x4
    f32 rate;               // 0x8
    f32 stickAccum;         // 0xC
    f32 active;             // 0x10
    u8 pad_14[0x18 - 0x14]; // 0x14, aligns prevTime
    OSTime prevTime;        // 0x18
    f32 stickLimit;         // 0x20
    f32 maxSpeed;           // 0x24
    f32 accel;              // 0x28
    f32 lastX;              // 0x2C
    f32 lastZ;              // 0x30
    u8 pad_34[0x38 - 0x34]; // 0x34, pads to the 8-byte alignment
} CamShiftWork;

// The demo times the shift with the field clock (it stops in battle), retail with the render clock.
static inline OSTime camShiftClock(void) {
#if VERSION == VERSION_DEMO
    return gp->renderFieldTime;
#else
    return gp->renderTime;
#endif
}

static CamShiftWork work;
static CamShiftWork* wp = &work;

void camShiftInit(void) {
    wp->current = 0.0f;
    wp->target = 0.0f;
    wp->rate = 0.0f;
    wp->stickAccum = 0.0f;
    wp->active = 0.0f;
    wp->stickLimit = 300.0f;
    wp->maxSpeed = 3.0f;
    wp->accel = 0.002f;
    wp->lastX = 0.0f;
    wp->lastZ = 0.0f;
}

void camShiftMain(CameraEntry* camera, MarioWork* mario, f32* out) {
    f32 shiftRate;
    f32 stick;
    f32 speed;
    f32 diff;
    BOOL reset = FALSE;

    shiftRate = camRoadGetCurrentShiftXRate();
    if (camera->flags & CAM_FLAG_ROAD_SHIFT_OFF) {
        reset = TRUE;
    }
    if (reset) {
        wp->rate = 1.0f;
        stick = 0.0f;
        wp->target = stick;
        wp->active = 1.0f;
    } else {
        stick = (s8)mario->wStickDir1;
        if (stick > 0.0f) {
            stick = 25.0f;
        }
        if (stick < 0.0f) {
            stick = -25.0f;
        }
        if (mario->position.x == wp->lastX && mario->position.z == wp->lastZ) {
            stick = 0.0f;
        }
        wp->lastX = mario->position.x;
        wp->lastZ = mario->position.z;
    }

    if (stick) {
        if (stick < 0.0f) {
            if (wp->stickAccum > 0.0f) {
                wp->stickAccum = getV60FPS(stick, wp->prevTime, camShiftClock());
            } else {
                wp->stickAccum += getV60FPS(stick, wp->prevTime, camShiftClock());
            }
            if (wp->stickAccum <= -wp->stickLimit) {
                wp->active = 1.0f;
                if (wp->target > 0.0f) {
                    wp->rate = 0.0f;
                }
                wp->target = -shiftRate;
                wp->stickAccum = -wp->stickLimit;
            }
        } else {
            if (wp->stickAccum < 0.0f) {
                wp->stickAccum = getV60FPS(stick, wp->prevTime, camShiftClock());
            } else {
                wp->stickAccum += getV60FPS(stick, wp->prevTime, camShiftClock());
            }
            if (wp->stickAccum >= wp->stickLimit) {
                wp->active = 1.0f;
                if (wp->target < 0.0f) {
                    wp->rate = 0.0f;
                }
                wp->target = shiftRate;
                wp->stickAccum = wp->stickLimit;
            }
        }
    }

    if (wp->active) {
        wp->rate += getV60FPS(wp->accel, wp->prevTime, camShiftClock());
        if (wp->rate > 1.0f) {
            wp->rate = 1.0f;
        }
    }

    if (0.0f == wp->target - wp->current) {
        wp->rate = 0.0f;
        wp->active = 0.0f;
    }

    speed = wp->rate * (diff = wp->target - wp->current);
    if (diff > 0.0f) {
        if (diff < 0.0001f) {
            speed = diff;
        }
        if (speed > wp->maxSpeed) {
            speed = wp->maxSpeed;
        }
    } else {
        if (diff > -0.0001f) {
            speed = diff;
        }
        if (speed < -wp->maxSpeed) {
            speed = -wp->maxSpeed;
        }
    }

    if (stick || reset) {
        wp->current += getV60FPS(speed, wp->prevTime, camShiftClock());
        if (wp->target < 0.0f) {
            if (wp->current < wp->target) {
                wp->current = wp->target;
            }
        } else {
            if (wp->current > wp->target) {
                wp->current = wp->target;
            }
        }
    } else {
        wp->rate = 0.0f;
    }
    *out = wp->current;
}

void camShiftPostMain(void) {
    wp->prevTime = camShiftClock();
}

void camShiftReset(void) {
    wp->current = 0.0f;
    wp->target = 0.0f;
    wp->rate = 0.0f;
    wp->stickAccum = 0.0f;
    wp->active = 0.0f;
    wp->stickLimit = 300.0f;
    wp->maxSpeed = 3.0f;
    wp->accel = 0.002f;
    wp->lastX = 0.0f;
    wp->lastZ = 0.0f;
}
