#include "eff/eff_hit.h"
#include "eff/n64/eff_hit_n64.h"

EffectEntry* effHitEntry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5) {
    return effHitN64Entry(type, arg1, x, y, z, arg5);
}
