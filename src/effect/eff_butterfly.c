#include "eff/eff_butterfly.h"
#include "eff/n64/eff_butterfly_n64.h"

EffectEntry* effButterflyEntry(s32 type, f32 x, f32 y, f32 z) {
    return effButterflyN64Entry(type, x, y, z);
}
