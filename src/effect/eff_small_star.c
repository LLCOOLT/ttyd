#include "eff/eff_small_star.h"
#include "eff/n64/eff_small_star_n64.h"

EffectEntry* effSmallStarEntry(s32 type, s32 arg1, f32 x, f32 y, f32 z, f32 arg5, f32 arg6, f32 arg7) {
    return effSmallStarN64Entry(type, arg1, x, y, z, arg5, arg6, arg7);
}

void effSmallStarCamChg(EffectEntry* effect, s32 cameraId) {
    effSmallStarN64CamChg(effect, cameraId);
}
