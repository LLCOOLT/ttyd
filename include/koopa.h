#pragma once

#include "dolphin/types.h"

s32 kpaGetLevel(void);

u8* getKoopaFireEfp(void);
void kpaAttackStart(void);
void kpaAttackStart2(void);
void kpaCancelAttackMode(void);
void kpaChgPose(const char* a, const char* b);
s32 kpaGetAttackMode(void);
f32 kpaGetBaseScale(s32 lv);
s32 kpaGetBodyStatus(void);
s32 kpaGetStageType(void);
s32 kpaGetStageViewType(void);
f32 kpaGetWidth(s32 lv);
void kpaMSetMutekiTimer(void);
s32 kpaMutekiCheck(void);
void kpaMutekiOff(void);
void kpaMutekiOn(void);
