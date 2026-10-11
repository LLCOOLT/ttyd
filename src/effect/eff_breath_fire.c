#include "eff/eff_breath_fire.h"
#include "eff/n64/eff_breath_fire_n64.h"

EffectEntry* effBreathFireEntry(s32 type, s32 arg1, s32 arg2, s32 arg3, f32 x, f32 y, f32 z, f32 arg7,
                         f32 arg8, f32 arg9) {
    return effBreathFireN64Entry(type, arg1, arg2, arg3, x, y, z, arg7, arg8, arg9);
}
