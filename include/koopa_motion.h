// koopa_motion.c: Bowser's motions in the side-scrolling interludes (kpa_walk, kpa_jump, kpa_hip, swim, power-ups).
#pragma once

#include <dolphin/types.h>

void kpa_dash(void);
void kpa_walk(void);

void quake_kpaLandOn(void);

void kpaSetSpec(void);
BOOL kpaHipAttackOk(void);
void kpa_stay(void);
void kpa_jump(void);
void kpa_fall(void);
void kpa_hip(void);
BOOL kpaPowUp(void);
BOOL kpaPowDown(void);
void kpa_powup(void);
void kpa_powdown(void);
void kpa_swim(void);
void quake_kpaHipAttack(void);
