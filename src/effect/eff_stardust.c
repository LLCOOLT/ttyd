#include "eff/eff_stardust.h"
#include "eff/n64/eff_stardust2_n64.h"

EffectEntry* effStardustEntry(s32 type, s32 arg1, s32 arg2, f32 x, f32 y, f32 z, f32 arg6, f32 arg7) {
    return effStardust2N64Entry(type, arg1, arg2, x, y, z, arg6, arg7);
}
