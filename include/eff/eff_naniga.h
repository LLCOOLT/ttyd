// eff_naniga.c: item-reveal effect entry (effNanigaEntry), the "what is it" roulette of the battle item code.
#pragma once

#include <dolphin/types.h>
#include "driver/effdrv.h"

EffectEntry* effNanigaEntry(s32 type, f32 x, f32 y, f32 z, s32* list, s32 item);
