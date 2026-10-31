#pragma once

// Declarations shared by the usu.rel units (ウスグラ村, Twilight Town).

#include "dolphin/types.h"
#include "evt/evt_word.h"
#include "evt/evt_cmd.h"

// The Twilight Town villagers turned into pigs (NPCs "ブタ村人Ａ".., "ブタ村長"), lit by usu_00's booboo_main.
typedef struct BoobooName {
    const char* name; // 0x0
    u8 villagerNo;    // 0x4, which villager; never read
    u8 isVillager;    // 0x5, 0 for the mayor; never read
    u8 pad_6[2];      // 0x6
} BoobooName;

extern EvtWord all_party_lecture[];
extern EvtWord evt_usu_kagemario_party_kill[];
extern EvtWord roll_majin_lecture[];
extern EvtWord roll_majin_lecture_init[];
extern EvtWord usu_00_init_evt[];
extern EvtWord usu_01_init_evt[];

USER_FUNC(evt_kagemario_init);
