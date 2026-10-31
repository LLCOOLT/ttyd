// kpa_act.c: the Bowser interlude coin and score counters (kpaAddCoin, kpaAddScore, kpa_score_disp_init).
#pragma once

#include "dolphin/types.h"
#include "dolphin/mtx.h"
#include "evt/evt_cmd.h"

void kpaAddCoin(s32 coins);
void kpaAddScore(s32 score);
void kpaAddScorePos(s32 score, Vec* pos);

USER_FUNC(kpa_score_disp_init);
USER_FUNC(kpa_chg_pose);
void kpaAddCoinPos(s32 coins, Vec* pos);
