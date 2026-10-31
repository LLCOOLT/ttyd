#pragma once

// Gundan zako (the X-Naut horde in the chapter 5 boss fight): the shared work of
// unit_boss_gundan_zako_group1.c (owner of `zakogun` and `work`), group2 and group3.

#include "battle/battle_unit.h"
#include "driver/extdrv.h"
#include "evt/evt_cmd.h"
#include "version.h"
#include <dolphin/mtx.h>
#include <dolphin/types.h>

// One X-Naut of the horde, drawn as an ext pose.
typedef struct ZakoGun {
    s8 flags;      // 0x00
    s8 state;      // 0x01
    s32 timer;     // 0x04
    s32 timerMax;  // 0x08
    Vec pos;       // 0x0C
    Vec home;      // 0x18
    s32 poseBase;  // 0x24, zakogun_set_pose: first texture
    s32 poseNum;   // 0x28, number of textures
    s32 poseDiv;   // 0x2C, frames per texture
    s32 poseCount; // 0x30
    Vec start;     // 0x34
    Vec target;    // 0x40
    Vec vel;       // 0x4C
    Vec ofs;       // 0x58, offset from the group's centre (group 3 circle formation)
    Vec rot;       // 0x64
} ZakoGun;

// The horde controller (BattleAlloc'd by group 1). Offsets are JP; US and PAL insert targetPos at 0x08.
typedef struct ZakoGunWork {
    s32 flag;     // 0x00
    s32 targetId; // 0x04
#if VERSION >= VERSION_US
    Vec targetPos; // 0x08, US/PAL only (group 2)
#endif
    s32 state;              // 0x08, group 3 formation
    s32 timer;              // 0x0C, group 3
    Vec pos;                // 0x10, group 3 formation centre
    u8 pad_1C[0x34 - 0x1C]; // 0x1C, never accessed
    f32 radius;             // 0x34, group 3 formation
    f32 angle;              // 0x38
    f32 speed;              // 0x3C
    u8 pad_40[0x48 - 0x40]; // 0x40, never accessed
    Vec start;              // 0x48, group 2 move of the leader
    Vec end;                // 0x54
    s32 moveTimer;          // 0x60, counts down from steps
    s32 steps;              // 0x64
    s32 count;              // 0x68
    s32 sfx;                // 0x6C
    ZakoGun* zako;          // 0x70
} ZakoGunWork;

extern ZakoGun* zakogun;
extern ZakoGunWork* work;

void zakogun_set_pose(ZakoGun* zako, s32 base, s32 num, s32 div);
BattleUnit* zakogun_get_ptr(void);
void zakogun_ext_init123_common(ExtdrvPose* pose, s32 i);
USER_FUNC(zakogun_get_kanbu_id_evtcmd);
USER_FUNC(zakogun_ext_init2);
USER_FUNC(zakogun_escape3);
