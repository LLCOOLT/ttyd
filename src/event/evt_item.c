// Script commands for field items: spawning, collecting and item flags (itemdrv).
#include "evt/evt_item.h"
#include "evt/evt_cmd.h"
#include "driver/itemdrv.h"
#include "manager/evtmgr_cmd.h"
#include "mario/mario.h"
#include "mario/mariost.h"
#include "system.h"
#include <dolphin/os.h>

/** Polynomial sine for x in radians, 0 to 2*pi, folded into the first quadrant; used by evt_item_get_important_item. */
static inline f32 item_sin(f32 x) {
    f32 a = 0.00761f;
    f32 b = 0.16605f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * x;
        } else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = a * y;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = a * y;
        a = -a;
    }
    return a;
}
/** Polynomial cosine for x in radians, 0 to 2*pi, folded like item_sin; used by evt_item_get_important_item. */
static inline f32 item_cos(f32 x) {
    f32 a = 0.03705f;
    f32 b = 0.4967f;
    f32 c = 1.0f;
    f32 y;
    f32 x2;
    if (x <= 3.1415927f) {
        if (x <= 1.5707964f) {
            x2 = x * x;
            a = a * x2 - b;
            a = a * x2 + c;
        } else {
            y = 1.5707964f - (x - 1.5707964f);
            x2 = y * y;
            a = a * x2 - b;
            a = a * x2 + c;
            a = -a;
        }
    } else if (x < 4.712389f) {
        y = x - 3.1415927f;
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
        a = -a;
    } else {
        y = 1.5707964f - (x - 4.712389f);
        x2 = y * y;
        a = a * x2 - b;
        a = a * x2 + c;
    }
    return a;
}

#define ITEM(ev) itemNameToPtr((char*)evtGetValue(ev, args[0]))

/**
 * Spawns a field item: args are name, item id, x, y, z (integers), ItemEntryType,
 * the collect flag (GSWF/LSWF passed unevaluated, or -1) and a pickup script. Wraps itemEntry.
 */
USER_FUNC(evt_item_entry) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    s32 itemId = evtGetValue(event, args[1]);
    s32 x = evtGetValue(event, args[2]);
    s32 y = evtGetValue(event, args[3]);
    s32 z = evtGetValue(event, args[4]);
    s32 type = evtGetValue(event, args[5]);
    s32 evtId = args[6];
    s32 a5 = evtGetValue(event, args[7]);
    itemEntry(x, y, z, name, itemId, type, evtId, (EvtWord*)a5);
    return EVT_RETURN_DONE;
}

/** Deletes the field item named in args[0]. */
USER_FUNC(evt_item_delete) {
    itemDelete((char*)evtGetValue(event, event->args[0]));
    return EVT_RETURN_DONE;
}

/** Writes 1 to args[1] when no field item named args[0] exists any more (collected or deleted), else 0. */
USER_FUNC(evt_item_delete_check) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    if (item != NULL) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], 1);
    }
    return EVT_RETURN_DONE;
}

/** Sets the ItemFlags in args[1] (a literal, not evaluated) on the field item named args[0]; no-op if it is missing. */
USER_FUNC(evt_item_flag_on) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    u16 flags = args[1];
    if (item == NULL)
        return EVT_RETURN_DONE;
    itemFlagOn(item, flags);
    return EVT_RETURN_DONE;
}

/** Clears the ItemFlags in args[1] (a literal) on the field item named args[0]; no-op if it is missing. */
USER_FUNC(evt_item_flag_off) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    u16 flags = args[1];
    if (item == NULL)
        return EVT_RETURN_DONE;
    itemFlagOff(item, flags);
    return EVT_RETURN_DONE;
}

/** Sets the ItemStatusFlags in args[1] (a literal) on the field item named args[0]; no-op if it is missing. */
USER_FUNC(evt_item_status_on) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    u32 flags = args[1];
    if (item == NULL)
        return EVT_RETURN_DONE;
    itemStatusOn(item, flags);
    return EVT_RETURN_DONE;
}

/** Sets the field item's direction (args[1], degrees) and horizontal speed (args[2], float) for its next launch. */
USER_FUNC(evt_item_set_move_dir_speed) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    s32 dir = evtGetValue(event, args[1]);
    f32 speed = evtGetFloat(event, args[2]);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->direction = dir;
    item->speed = speed;
    return EVT_RETURN_DONE;
}

/** Sets the field item's vertical velocity (args[1], float), the jump power of its launch. */
USER_FUNC(evt_item_set_jump_power) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    f32 v = evtGetFloat(event, args[1]);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->velocityY = v;
    return EVT_RETURN_DONE;
}

/** Sets the field item's gravity scale (args[1], float). */
USER_FUNC(evt_item_set_gravity) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    f32 v = evtGetFloat(event, args[1]);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->gravityScale = v;
    return EVT_RETURN_DONE;
}

/** Sets the field item's bounce factor (args[1], float): how much speed it keeps each bounce. */
USER_FUNC(evt_item_set_bound_rate) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    f32 v = evtGetFloat(event, args[1]);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->bounceFactor = v;
    return EVT_RETURN_DONE;
}

/** Sets the field item's maximum number of bounces (args[1]). */
USER_FUNC(evt_item_set_bound_limit) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    s32 v = evtGetValue(event, args[1]);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->maxBounces = v;
    return EVT_RETURN_DONE;
}

/**
 * Forces Mario to collect the field item named args[0] (itemForceGet) and blocks
 * until its get sequence is over (ITEM_STATUS_GET_ENDED or END_WAIT), or the item is gone.
 */
USER_FUNC(evt_item_get_item) {
    EvtWord* args = event->args;
    ItemEntry* item = itemNameToPtr((char*)evtGetValue(event, args[0]));
    if (isFirstCall) {
        itemForceGet(item);
        return EVT_RETURN_BLOCK;
    }
    if (item == NULL)
        return EVT_RETURN_DONE;
    if (!(item->flags & ITEM_FLAG_USED))
        return EVT_RETURN_DONE;
    if (itemStatus(item, ITEM_STATUS_END_WAIT))
        return EVT_RETURN_DONE;
    return itemStatus(item, ITEM_STATUS_GET_ENDED) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/** Blocks until the get sequence of the field item named args[0] is over, without starting it; done if it is gone. */
USER_FUNC(evt_item_get_item_end_wait) {
    ItemEntry* item = itemNameToPtr((char*)evtGetValue(event, event->args[0]));
    if (item == NULL)
        return EVT_RETURN_DONE;
    if (!(item->flags & ITEM_FLAG_USED))
        return EVT_RETURN_DONE;
    if (itemStatus(item, ITEM_STATUS_END_WAIT))
        return EVT_RETURN_DONE;
    return itemStatus(item, ITEM_STATUS_GET_ENDED) ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}

/** Switches the field item named args[0] to mode args[1] (itemModeChange restarts that mode's state). */
USER_FUNC(evt_item_change_mode) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    s32 mode = evtGetValue(event, args[1]);
    ItemEntry* item = itemNameToPtr(name);
    if (item == NULL)
        return EVT_RETURN_DONE;
    itemModeChange(item, (u16)mode);
    return EVT_RETURN_DONE;
}

/** Sets the speed (args[1], float) the field item takes on its first bounce when ITEM_FLAG_RESTORE_MOTION is set. */
USER_FUNC(evt_item_set_bound_next_speed) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    f32 v = evtGetFloat(event, args[1]);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->savedSpeed = v;
    return EVT_RETURN_DONE;
}

/** Sets the direction (args[1]) the field item takes on its first bounce when ITEM_FLAG_RESTORE_MOTION is set. */
USER_FUNC(evt_item_set_bound_next_dir) {
    EvtWord* args = event->args;
    ItemEntry* item = ITEM(event);
    s32 v = evtGetValue(event, args[1]);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->savedDirection = v;
    return EVT_RETURN_DONE;
}

/** Moves the field item named args[0] to the float position args[1..3]. */
USER_FUNC(evt_item_set_position) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    ItemEntry* item = itemNameToPtr(name);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->position.x = x;
    item->position.y = y;
    item->position.z = z;
    return EVT_RETURN_DONE;
}

/** Writes the position of the field item named args[0] to the float variables args[1..3]. */
USER_FUNC(evt_item_get_position) {
    EvtWord* args = event->args;
    ItemEntry* item;
    s32 a1, a2, a3;
    char* name = (char*)evtGetValue(event, args[0]);
    a1 = args[1];
    a2 = args[2];
    a3 = args[3];
    item = itemNameToPtr(name);
    if (item == NULL)
        return EVT_RETURN_DONE;
    evtSetFloat(event, a1, item->position.x);
    evtSetFloat(event, a2, item->position.y);
    evtSetFloat(event, a3, item->position.z);
    return EVT_RETURN_DONE;
}

/** Sets the draw scale (args[1], float) of the field item named args[0]. */
USER_FUNC(evt_item_set_scale) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    f32 v = evtGetFloat(event, args[1]);
    ItemEntry* item = itemNameToPtr(name);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->scale = v;
    return EVT_RETURN_DONE;
}

/** Sets the alpha (args[1], 0-255) of the field item named args[0]. */
USER_FUNC(evt_item_set_alpha) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    u8 v = evtGetValue(event, args[1]);
    ItemEntry* item = itemNameToPtr(name);
    if (item == NULL)
        return EVT_RETURN_DONE;
    item->alpha = v;
    return EVT_RETURN_DONE;
}

/**
 * Slides the field item named args[0] to the integer position args[1..3] over args[4] milliseconds with
 * interpolation mode args[5] (intplGetValue), blocking until it arrives.
 */
USER_FUNC(evt_item_move_3d_position) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    f32 x = (f32)evtGetValue(event, args[1]);
    f32 y = (f32)evtGetValue(event, args[2]);
    f32 z = (f32)evtGetValue(event, args[3]);
    s32 ms = evtGetValue(event, args[4]);
    s32 mode = evtGetValue(event, args[5]);
    ItemEntry* item = itemNameToPtr(name);
    u32 elapsed;
    f32* z0 = (f32*)&event->userdata3;
    if (isFirstCall) {
        if (item == NULL)
            return EVT_RETURN_DONE;
        event->userdata[0] = (s32)gp->renderTime;
        event->userdataf[1] = item->position.x;
        event->userdataf[2] = item->position.y;
        *z0 = item->position.z;
    }
    if ((s32)(elapsed = OSTicksToMilliseconds((u32)gp->renderTime - event->userdata[0])) < ms) {
        item->position.x = intplGetValue(mode, event->userdataf[1], x, (s32)elapsed, ms);
        item->position.y = intplGetValue(mode, event->userdataf[2], y, (s32)elapsed, ms);
        item->position.z = intplGetValue(mode, *z0, z, (s32)elapsed, ms);
        return EVT_RETURN_BLOCK;
    }
    item->position.x = x;
    item->position.y = y;
    item->position.z = z;
    return EVT_RETURN_DONE;
}

// FAKE: #pragma opt_propagation off and opt_lifetimes off for evt_item_get_important_item: no copy propagation or lifetime splitting, which gives the target temporaries and registers; without them the function is 209 instructions instead of 191
#pragma opt_propagation off
#pragma opt_lifetimes off
/**
 * Flies the field item named args[0] to Mario (raised by his collision box height) in an arc:
 * 0.5 units per frame toward him with 0.1 per-frame gravity, blocking until it reaches him.
 * Assumes the item exists (no NULL check).
 */
USER_FUNC(evt_item_get_important_item) {
    ItemEntry* item = itemNameToPtr((char*)evtGetValue(event, event->args[0]));
    MarioWork* mario = marioGetPtr();
    f32 mx, my, mz;
    f32 tb;
    f32 spd;
    f32 ta;
    f32 rad, s, c;
    mx = mario->position.x;
    my = mario->position.y + mario->wPlayerCollisionBox.y;
    mz = mario->position.z;
    spd = 0.5f;
    if (isFirstCall) {
        f32 dist = distABf(mx, mz, item->position.x, item->position.z);
        f32 dy = my - item->position.y;
        ta = dist / spd;
        tb = dy / ta + (ta * 0.1f) / 2.0f;
        event->userdata[0] = *(s32*)&ta;
        event->userdata[1] = *(s32*)&tb;
        event->userdata[2] = *(s32*)&spd;
        event->userdata3 = 0;
    }
    ta = event->userdataf[0];
    tb = event->userdataf[1];
    spd = event->userdataf[2];
    rad = 6.2831855f * angleABf(item->position.x, item->position.z, mx, mz) / 360.0f;
    s = item_sin(rad);
    item->position.x = spd * s + item->position.x;
    c = item_cos(rad);
    item->position.z = item->position.z - spd * c;
    item->position.y += tb;
    tb = tb - 0.1f;
    ta = ta - 1.0f;
    if (ta < 0.0f) {
        item->position.x = mx;
        item->position.y = my;
        item->position.z = mz;
        return EVT_RETURN_DONE;
    }
    event->userdata[0] = *(s32*)&ta;
    event->userdata[1] = *(s32*)&tb;
    return EVT_RETURN_BLOCK;
}
#pragma opt_propagation reset
#pragma opt_lifetimes reset
