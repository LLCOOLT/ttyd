#include "battle/battle_audience.h"
#include "battle/battle.h"
#include "pmario_sound.h"
#include "system.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "eff/eff_sleep.h"
#include "eff/eff_small_star.h"
#include <string.h>
#include "battle/battle_audience_kinopio.h"
#include "battle/battle_database_common.h"

#pragma optimize_for_size on
#pragma dont_inline on

#define AM_F32(p, off) (*(f32*)((u8*)(p) + (off)))
#define AM_S32(p, off) (*(s32*)((u8*)(p) + (off)))

double sin(double);
double sqrt(double);
double fabs(double);
double __fabs(double);
s32 rand();
s32 BattleAudienceDetectPakkunEatTarget(s32 index);
void BattleAudiencePuniAllEscape(void);
void BattleAudienceSoundSing(s32 index);
void BattleAudienceSoundShell(s32 index);
void BattleAudienceSoundBombIgnite(s32 index, s32 duration, s32 fade);
void BattleAudienceSoundBombFire(s32 index);
void BattleAudienceSoundPakkunEat(s32 index);
void BattleAudienceSoundSleep(s32 index);
void BattleAudienceSoundZZZ(s32 index);
BOOL BtlUnit_CheckShadowGuard(BattleUnit* unit);
EffectEntry* effOnpuN64Entry(s32 type, f32 x, f32 y, f32 z);
EffectEntry* effSandarsEntry(s32 type, f32 x, f32 y, f32 z, f32 w);
void btl_camera_set_mode(s32 a, s32 b);
void btl_camera_set_moveto(s32 a, s32 b, f32 c, f32 d, f32 e, f32 f, f32 g, f32 h, s32 i);
void btl_camera_set_moveSpeedLv(s32 a, s32 b);
void btl_camera_shake_h(s32 a, f32 b, f32 c, s32 d, s32 e);
s32 BattleStage_ObjectFallCheck();
void BattleStage_NozzleWorkCheck(s32 a);
BattleStage* BattleStageGetPtr(void);
s32 BattleBreakSlot_GetBreakTurn();
BOOL BattleAudience_GetAnimEnd();
u8 BattleAudience_GetEscapeChangeOK();
BOOL BattleAudience_GetFront(s32 index);
s32 BattleAudience_GetAudienceNoFromOffset(s32 index, s32 column, s32 row);
void BattleAudienceAddTargetNum(f32 a, f32 b);
void BattleAudienceSoundItemThrow(s32 kind, s32 index);

void BattleAudienceCtrlProcessKinopioWait(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioWaitHurimuki(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioWaitKubiKatamuke(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioWaitJump(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioJoyRaiseArm(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioJoyJump(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioJoyJump2(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioItemOn(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioItemThrow();
void BattleAudienceCtrlProcessKinopioBooing();
void BattleAudienceCtrlProcessKinopioDamage();
void BattleAudienceCtrlProcessKinopioEnter();
void BattleAudienceCtrlProcessKinopioEscape();
void BattleAudienceCtrlProcessKinopioSleep(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioTransEvt();
void BattleAudienceCtrlProcessKinopioIntrude();
void BattleAudienceCtrlProcessKinopioSing();
void BattleAudienceCtrlProcessKinopioShell();
void BattleAudienceCtrlProcessKinopioIgnite(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioFire(s32 index, s32 front);
void BattleAudienceCtrlProcessKinopioEat();
void BattleAudienceCtrlProcessKinopioSingSub(s32 index);
void BattleAudienceCtrlProcessKinopioFireSub(s32 index);

void BattleAudienceCtrlProcessKinopio(s32 index) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    BOOL front = BattleAudience_GetFront(index);
    switch (m->status) {
    case 0:
        BattleAudienceCtrlProcessKinopioWait(index, front);
        break;
    case 1:
        BattleAudienceCtrlProcessKinopioWaitHurimuki(index, front);
        break;
    case 2:
        BattleAudienceCtrlProcessKinopioWaitKubiKatamuke(index, front);
        break;
    case 3:
        BattleAudienceCtrlProcessKinopioWaitJump(index, front);
        break;
    case 4:
        BattleAudienceCtrlProcessKinopioJoyRaiseArm(index, front);
        break;
    case 5:
        BattleAudienceCtrlProcessKinopioJoyJump(index, front);
        break;
    case 6:
        BattleAudienceCtrlProcessKinopioJoyJump2(index, front);
        break;
    case 7:
        BattleAudienceCtrlProcessKinopioItemOn(index, front);
        break;
    case 8:
        BattleAudienceCtrlProcessKinopioItemThrow(index, front);
        break;
    case 9:
        BattleAudienceCtrlProcessKinopioBooing(index, front);
        break;
    case 10:
        BattleAudienceCtrlProcessKinopioDamage(index, front);
        break;
    case 11:
        BattleAudienceCtrlProcessKinopioEnter(index, front);
        break;
    case 12:
        BattleAudienceCtrlProcessKinopioEscape(index, front);
        break;
    case 13:
        BattleAudienceCtrlProcessKinopioSleep(index, front);
        break;
    case 14:
        BattleAudienceCtrlProcessKinopioTransEvt(index, front);
        break;
    case 15:
        BattleAudienceCtrlProcessKinopioIntrude(index, front);
        break;
    case 16:
        BattleAudienceCtrlProcessKinopioSing(index, front);
        break;
    case 17:
        BattleAudienceCtrlProcessKinopioShell(index, front);
        break;
    case 18:
        BattleAudienceCtrlProcessKinopioIgnite(index, front);
        break;
    case 19:
        BattleAudienceCtrlProcessKinopioFire(index, front);
        break;
    case 20:
        BattleAudienceCtrlProcessKinopioEat(index, front);
        break;
    }
    m->position.x += m->field_0x78.x;
    m->field_0x78.x += AM_F32(m, 0x84);
    m->position.y += m->field_0x78.y;
    m->field_0x78.y += m->unk88;
    m->position.z += m->field_0x78.z;
    m->field_0x78.z += m->unk8C;
    if (m->field_0x78.x > 0.0f) {
        m->angle = 90.0f;
    } else if (m->field_0x78.x < 0.0f) {
        m->angle = 270.0f;
    }
    if (m->unkD0 < 0.0f) {
        m->unkD0 = 0.0f;
        m->unkDC = 0.0f;
        m->unkE4 = 0.0f;
    }
    if (m->type == 11) {
        m->unkDC = 0.0f;
        m->unkD0 = 0.0f;
        m->unkE4 = 0.0f;
    } else {
        m->unkD0 += m->unkDC;
        m->unkDC += m->unkE4;
    }
    if (m->type == 2) {
        AM_F32(m, 0x12C) += 0.05f;
        if (AM_F32(m, 0x12C) >= 6.283184f) {
            AM_F32(m, 0x12C) -= 6.283184f;
        }
        m->unk130 = 5.0f * (f32)sin(AM_F32(m, 0x12C));
        m->unkC0 = m->position.x + m->unkCC;
        m->unkC4 = m->unk130 + (m->position.y + m->unkD0);
        m->unkC8 = m->position.z + m->unkD4;
    } else {
        m->unkC0 = m->position.x + m->unkCC;
        m->unkC4 = m->position.y + m->unkD0;
        m->unkC8 = m->position.z + m->unkD4;
    }
}

#pragma opt_propagation off
#pragma opt_lifetimes off
void BattleAudienceCtrlProcessKinopioWait(s32 index, s32 front) {
    BattleAudience* base;
    BattleAudienceMember* m;
    f32 a;
    f32 b;
    f32 scale;
    f32 speed;
    f32 r;
    s32 th;
    s32 rnd;
    s32 n;
    base = BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    pouchGetPtr();
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 0, FALSE);
    } else {
        BattleAudience_SetAnim(index, 1, FALSE);
    }
    r = (base->mTargetAudienceCount + base->mAddedAudienceCount) / base->mAudienceDeltaMultiplier;
    if (r >= 0.75f) {
        speed = 1.0f;
        scale = speed;
    } else if (r >= 0.5f) {
        speed = 0.5f;
        scale = 2.0f;
    } else if (r >= 0.25f) {
        speed = 0.25f;
        scale = 4.0f;
    } else {
        speed = 0.0f;
    }
    if (r >= 1.75f) {
        a = 10.0f;
        b = 4.0f;
    } else if (r >= 1.5f) {
        a = 5.0f;
        b = 2.0f;
    } else if (r >= 1.25f) {
        a = 2.0f;
        b = 1.0f;
    } else if (r >= 1.0f) {
        a = 1.0f;
        b = 0.0f;
    } else {
        b = a = 0.0f;
    }
    switch (m->type) {
    case 4:
        if (m->field_0x30 > 180) {
            if (m->field_0x30 <= 188) {
                m->baseScale.y += 0.005f * speed;
            } else if ((f32)m->field_0x30 <= 8.0f * scale + 188.0f) {
                m->baseScale.y -= 0.005f * speed;
            } else if ((f32)m->field_0x30 <= 16.0f * scale + 188.0f) {
                m->baseScale.y += 0.005f * speed;
            } else if ((f32)m->field_0x30 <= 24.0f * scale + 188.0f) {
                m->baseScale.y -= 0.005f * speed;
            } else if ((f32)m->field_0x30 <= 32.0f * scale + 188.0f) {
                m->baseScale.y += 0.005f * speed;
            } else if ((f32)m->field_0x30 <= 40.0f * scale + 188.0f) {
                m->baseScale.y -= 0.005f * speed;
            } else {
                m->baseScale.y = 1.0f;
                m->field_0x30 = 0;
            }
        }
        m->field_0x30++;
        break;
    case 6:
        if ((f32)m->field_0x30 >= 36.0f * scale) {
            m->baseScale.y = 1.0f;
            m->field_0x30 = 0;
        }
        if ((f32)m->field_0x30 <= 17.0f * scale) {
            m->baseScale.y += 0.00175f * speed;
        } else {
            m->baseScale.y -= 0.00175f * speed;
        }
        m->field_0x30++;
        break;
    case 7:
        if ((f32)m->field_0x30 >= 22.0f * scale) {
            m->baseScale.y = 1.0f;
            m->field_0x30 = 0;
        }
        if ((f32)m->field_0x30 <= 10.0f * scale) {
            m->baseScale.y += 0.00375f * speed;
        } else {
            m->baseScale.y -= 0.00375f * speed;
        }
        m->field_0x30++;
        break;
    case 9:
        if ((f32)m->field_0x30 >= 64.0f * scale) {
            m->baseScale.y = 1.0f;
            m->field_0x30 = 0;
        }
        if ((f32)m->field_0x30 <= 31.0f * scale) {
            m->baseScale.y += 0.00125f * speed;
        } else {
            m->baseScale.y -= 0.00125f * speed;
        }
        m->field_0x30++;
        break;
    case 2:
        break;
    default:
        if ((f32)m->field_0x30 >= 32.0f * scale) {
            m->baseScale.y = 1.0f;
            m->field_0x30 = 0;
        }
        if ((f32)m->field_0x30 <= 15.0f * scale) {
            m->baseScale.y += 0.0025f * speed;
        } else {
            m->baseScale.y -= 0.0025f * speed;
        }
        m->field_0x30++;
        break;
    }
    if (m->flags & 0x40) {
        m->flags &= ~0x60;
        BattleAudience_ChangeStatus(index, 10);
        if (!(BattleAudienceItemGetPtr(0)->mItemType >= 0xEC && BattleAudienceItemGetPtr(0)->mItemType < 0xF0)) {
            BattleAudienceAddTargetNum(-0.14999999f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
        }
    } else if (!(m->flags & 0x20)) {
        switch (m->itemId) {
        case -1: {
            rnd = irand(360000);
            if (rnd < 10) {
                BattleAudience_ChangeStatus(index, 1);
            } else {
                th = 20;
                if (rnd < th) {
                    BattleAudience_ChangeStatus(index, 2);
                } else {
                    th = (s32)(th + (f32)(10.0f * a));
                    if (rnd < th) {
                        BattleAudience_ChangeStatus(index, 4);
                    } else if (BattleBreakSlot_GetBreakTurn() >= 1 || base->excited == 1) {
                        if (rnd < th + 300) {
                            if (m->type != 11) {
                                BattleAudience_ChangeStatus(index, 3);
                            }
                        }
                    } else {
                        th += (s32)(10.0f * b);
                        if (rnd < th) {
                            n = BattleAudience_GetAudienceNoFromOffset(index, 0, 1);
                            if (n != -1) {
                                BattleAudienceGetPtr(n);
                                if (m->type != 11) {
                                    if ((u8)BattleAudience_GetExist(n) == 1) {
                                        BattleAudience_ChangeStatus(index, 3);
                                    }
                                }
                            }
                        }
                    }
                }
            }
            break; }
        }
    }
}

#pragma opt_propagation reset
#pragma opt_lifetimes reset
void BattleAudienceCtrlProcessKinopioWaitHurimuki(s32 index, s32 front) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 0, FALSE);
    } else {
        BattleAudience_SetAnim(index, 1, FALSE);
    }
    if (m->field_0x30 <= 15) {
        m->mRotation.y = 12.0f * (f32)m->field_0x30;
    }
    if (m->field_0x30 >= 30) {
        m->mRotation.y = 12.0f * (f32)(45 - m->field_0x30);
    }
    if (m->field_0x30 > 45) {
        BattleAudience_ChangeStatus(index, 0);
    } else {
        m->field_0x30++;
    }
}

void BattleAudienceCtrlProcessKinopioWaitKubiKatamuke(s32 index, s32 front) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 0, FALSE);
    } else {
        BattleAudience_SetAnim(index, 1, FALSE);
    }
    if (m->field_0x30 >= 0 && m->field_0x30 <= 10) {
        m->dispOffset.x = 1.5f * (f32)m->field_0x30;
    }
    if (m->field_0x30 >= 20 && m->field_0x30 <= 40) {
        m->dispOffset.x -= 1.5f;
    }
    if (m->field_0x30 >= 50 && m->field_0x30 <= 60) {
        m->dispOffset.x += 1.5f;
    }
    if (m->field_0x30 > 60) {
        BattleAudience_ChangeStatus(index, 0);
    } else {
        m->field_0x30++;
    }
}

void BattleAudienceCtrlProcessKinopioWaitJump(s32 index, s32 front) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 2, FALSE);
    } else {
        BattleAudience_SetAnim(index, 3, FALSE);
    }
    switch (m->field_0x4) {
    case 0:
        if (m->type == 7) {
            m->field_0x8 = 3;
        } else {
            m->field_0x8 = 1;
        }
        m->field_0x4++;
    case 1:
        if (m->type == 7) {
            m->unkDC = 5.0f;
            m->unkE4 = -1.0f;
        } else {
            m->unkDC = 3.4f;
            m->unkE4 = -0.2f;
        }
        m->field_0x4++;
    case 2:
        if (0.0f == m->unkE4) {
            m->field_0x8--;
            if (m->field_0x8 <= 0) {
                BattleAudience_ChangeStatus(index, 0);
            } else {
                m->field_0x4 = 1;
            }
        }
    }
}

void BattleAudienceCtrlProcessKinopioJoyRaiseArm(s32 index, s32 front) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if ((u8)front == 0) {
        BattleAudience_SetAnim(index, 4, FALSE);
    }
    switch (m->field_0x4) {
    case 0:
        if (irand(2) == 0) {
            m->angle = 270.0f;
        } else {
            m->angle = 90.0f;
        }
        m->field_0x4++;
    case 1:
        m->dispOffset.y = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(0.0f, 10.0f, 4, m->field_0x8, 15);
        m->field_0x8++;
        if (m->field_0x8 > 30) {
            m->field_0xC -= 1.0f;
            if (m->field_0xC <= 0.0f) {
                BattleAudience_ChangeStatus(index, 0);
            } else {
                m->field_0x8 = 0;
            }
        }
    }
}

void BattleAudienceCtrlProcessKinopioJoyJump(s32 index, s32 front) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 2, FALSE);
    } else {
        BattleAudience_SetAnim(index, 3, FALSE);
    }
    switch (m->field_0x4) {
    case 0:
        m->field_0x8 = 1;
        m->field_0x4++;
    case 1:
        m->unkDC = 3.4f + (f32)rand() / 32767.0f;
        m->unkE4 = -0.2f;
        m->field_0x4++;
    case 2:
        if (0.0f == m->unkE4) {
            m->field_0x8--;
            if (m->field_0x8 <= 0) {
                BattleAudience_ChangeStatus(index, 0);
            } else {
                m->field_0x4 = 1;
            }
        }
    }
}

void BattleAudienceCtrlProcessKinopioJoyJump2(s32 index, s32 front) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 2, FALSE);
    } else {
        BattleAudience_SetAnim(index, 3, FALSE);
    }
    switch (m->field_0x4) {
    case 0:
        m->field_0x8 = 2;
        m->field_0x4++;
    case 1:
        m->unkDC = 4.0f + (f32)rand() / 32767.0f;
        m->unkE4 = -0.2f;
        m->field_0x4++;
    case 2:
        m->mRotation.y += 20.0f;
        if (0.0f == m->unkE4) {
            m->field_0x8--;
            if (m->field_0x8 <= 0) {
                BattleAudience_ChangeStatus(index, 0);
            } else {
                m->field_0x4 = 1;
            }
        }
    }
}

void BattleAudienceCtrlProcessKinopioItemOn(s32 index, s32 front) {
    BattleWork* bw = _battleWorkPointer;
    BattleAudience* base = BattleAudienceBaseGetPtr();
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    BattleAudienceItem* item;
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 0, FALSE);
    } else {
        BattleAudience_SetAnim(index, 5, FALSE);
    }
    if (m->flags & 0x40) {
        item = BattleAudienceItemGetPtr(m->itemId);
        m->flags &= ~0x60;
        m->itemId = -1;
        item->flags = 0;
        BattleAudience_ChangeStatus(index, 10);
        if (!(BattleAudienceItemGetPtr(0)->mItemType >= 0xEC && BattleAudienceItemGetPtr(0)->mItemType < 0xF0)) {
            BattleAudienceAddTargetNum(-0.14999999f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
        }
    } else if (!(m->flags & 0x20) && (bw->flags & 0x80)) {
        item = BattleAudienceItemGetPtr(m->itemId);
        if (!(base->flags & 0x40000)) {
            AM_S32(item, 8)--;
            if ((item->flags & 1) && AM_S32(item, 8) <= 0 && item->state == 1) {
                BattleAudience_ChangeStatus(index, 8);
                BattleAudienceSoundItemThrow(0, index);
            }
        }
    }
}

void BattleAudienceCtrlProcessKinopioItemThrow(s32 index) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    BattleAudience_SetAnim(index, 6, FALSE);
    if (BattleAudience_GetAnimEnd(index) == 1) {
        BattleAudience_ChangeStatus(index, 0);
    }
    if (m->flags & 0x40) {
        m->flags &= ~0x60;
        BattleAudience_ChangeStatus(index, 10);
        if (!(BattleAudienceItemGetPtr(0)->mItemType >= 0xEC && BattleAudienceItemGetPtr(0)->mItemType < 0xF0)) {
            BattleAudienceAddTargetNum(-0.14999999f * BattleAudienceBaseGetPtr()->mAudienceDeltaMultiplier, 0.0f);
        }
    } else {
        if (m->flags & 0x20) {
            return;
        }
    }
}

void BattleAudienceCtrlProcessKinopioBooing(s32 index) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    BattleAudience_SetAnim(index, 4, FALSE);
    switch (m->field_0x4) {
    case 0:
        if (irand(2) == 0) {
            m->angle = 270.0f;
        } else {
            m->angle = 90.0f;
        }
        m->field_0x4++;
    case 1:
        m->dispOffset.y = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(0.0f, 10.0f, 4, m->field_0x8, 15);
        m->field_0x8++;
        if (m->field_0x8 > 30) {
            m->field_0xC -= 1.0f;
            if (m->field_0xC <= 0.0f) {
                BattleAudience_ChangeStatus(index, 0);
            } else {
                m->field_0x8 = 0;
            }
        }
    }
}

void BattleAudienceCtrlProcessKinopioDamage(s32 index) {
    BattleAudienceMember* m;
    BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    switch (m->field_0x4) {
    case 0:
        BattleAudience_SetAnim(index, 9, FALSE);
        m->unkDC = 8.0f;
        m->unkE4 = -1.0f;
        m->field_0x30 = 0;
        m->angle = 270.0f;
        m->field_0x4++;
    case 1:
        if (m->field_0x30 >= 8) {
            m->baseScale.y = 1.0f;
            m->field_0x30 = 0;
        }
        if (m->field_0x30 <= 4) {
            m->baseScale.y -= 0.1f;
        } else {
            m->baseScale.y += 0.1f;
        }
        m->field_0x30++;
        if (BattleAudience_GetAnimEnd(index) == 1) {
            m->baseScale.y = 1.0f;
            m->field_0x30 = 0;
            if (BattleAudience_GetEscapeChangeOK(index) == 1) {
                BattleAudience_ChangeStatus(index, 12);
                psndSFXOn_3D("SFX_AUDIENCE_PANIC_SCREAM2\0", &m->position);
            } else {
                BattleAudience_ChangeStatus(index, 0);
            }
        }
    }
}

void BattleAudienceCtrlProcessKinopioEnter(s32 index) {
    BattleAudienceMember* m;
    f32 dx;
    f32 dz;
    BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    camGetPtr(8);
    BattleAudience_SetAnim(index, 7, FALSE);
    if (m->type == 11) {
        switch (m->field_0x4) {
        case 0:
            m->position.x = m->mHomePosition.x;
            m->position.y = -100.0f;
            m->position.z = m->mHomePosition.z;
            m->field_0x78.x = 0.0f;
            m->field_0x78.y = 0.0f;
            m->field_0x78.z = 0.0f;
            m->field_0x8 += irand(60) + 1;
            m->field_0x4++;
            break;
        case 1:
            m->field_0x8--;
            if (m->field_0x8 <= 0) {
                m->field_0x78.x = 0.0f;
                m->field_0x78.y = 1.0f;
                m->field_0x78.z = 0.0f;
                m->field_0x4++;
            }
            break;
        case 2:
            if (m->position.y >= m->mHomePosition.y) {
                m->position.y = m->mHomePosition.y;
                BattleAudience_ChangeStatus(index, 0);
                m->field_0x4++;
            }
            break;
        }
    } else {
        switch (m->field_0x4) {
        case 0:
            m->position.x = (f32)(irand(400) - 200);
            m->position.y = m->mHomePosition.y;
            m->position.z = 1000.0f;
            m->field_0x78.x = 0.0f;
            m->field_0x78.y = 0.0f;
            m->field_0x78.z = 0.0f;
            m->field_0x8 += irand(60) + 1;
            m->field_0x4++;
            break;
        case 1:
            m->field_0x8--;
            if (m->field_0x8 <= 0) {
                dx = m->mHomePosition.x - m->position.x;
                dz = m->mHomePosition.z - m->position.z;

                {
                    f32 d = (f32)sqrt(dx * dx + dz * dz);
                    m->field_0x78.x = 10.0f * (dx / d);
                    m->field_0x78.y = 0.0f;
                    m->field_0x78.z = 10.0f * (dz / d);
                    m->field_0xC = 10.0f;
                    m->field_0x10 = 10.0f;
                    m->field_0x14 = d;
                }
                m->field_0x4++;
            }
            break;
        case 2:
            m->field_0xC += m->field_0x10;
            if (m->field_0xC >= m->field_0x14) {
                m->position.x = m->mHomePosition.x;
                m->position.y = m->mHomePosition.y;
                m->position.z = m->mHomePosition.z;
                BattleAudience_ChangeStatus(index, 0);
            }
            break;
        }
    }
}

void BattleAudienceCtrlProcessKinopioEscape(s32 index) {
    BattleAudienceMember* m;
    BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    BattleAudience_SetAnim(index, 7, FALSE);
    if (m->type == 11) {
        switch (m->field_0x4) {
        case 0:
            m->field_0x8--;
            if (m->field_0x8 <= 0) {
                m->field_0x78.x = 0.0f;
                m->field_0x78.y = -1.0f;
                m->field_0x78.z = 0.0f;
                m->field_0x4++;
            }
            break;
        case 1:
            if (m->position.y <= -100.0f) {
                BattleAudience_Delete(index);
                m->field_0x4++;
            }
            break;
        }
    } else {
        switch (m->field_0x4) {
        case 0:
            m->field_0x8--;
            if (m->field_0x8 <= 0) {
                m->field_0x78.x = 2.0f * (f32)rand() / 32767.0f - 1.0f - m->position.x / 120.0f;
                m->field_0x78.y = 0.0f;
                m->field_0x78.z = 8.0f;
                m->unkDC = 6.0f;
                m->unkE4 = -0.5f;
                m->field_0x4++;
                psndSFXOn_3D("SFX_AUDIENCE_RUN3", &m->position);
            }
            break;
        case 1:
            if (0.0f == m->unkE4) {
                m->field_0x4++;
            }
            break;
        case 2:
            if (m->position.z >= 600.0f) {
                BattleAudience_Delete(index);
            }
            break;
        }
    }
}

void BattleAudienceCtrlProcessKinopioSleep(s32 index, s32 front) {
    BattleAudience* base;
    BattleAudienceMember* m;
    base = BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    if (m->field_0x4 <= 1) {
        if ((u8)front == 1) {
            BattleAudience_SetAnim(index, 10, FALSE);
        } else {
            BattleAudience_SetAnim(index, 11, FALSE);
        }
        if (m->field_0x30 >= 320) {
            m->baseScale.y = 1.0f;
            m->field_0x30 = 0;
        }
        if (m->field_0x30 <= 160) {
            m->baseScale.y -= 0.0025f;
        } else {
            m->baseScale.y += 0.0025f;
        }
        m->field_0x30++;
        m->colorB += m->field_0x18;
        if (m->colorB >= 200) {
            *(s8*)&m->field_0x18 = -4;
        } else if (m->colorB <= 5) {
            m->field_0x18 = 4;
        }
    }
    switch (m->field_0x4) {
    case 0:
        BattleAudienceSoundSleep(index);
        m->field_0x4++;
    case 1:
        if (irand(36000) == 0) {
            effSleepEntry(0, 180, m->position.x, 25.0f + m->position.y, m->position.z, 1.0f, 45.0f);
            BattleAudienceSoundZZZ(index);
        }
        break;
    case 2:
        m->unkDC = 6.0f + (f32)rand() / 32767.0f;
        m->unkE4 = -0.5f;
        if ((u8)front == 1) {
            BattleAudience_SetAnim(index, 0, FALSE);
        } else {
            BattleAudience_SetAnim(index, 1, FALSE);
        }
        m->baseScale.y = 1.0f;
        m->colorB = 0;
        m->field_0x4++;
    case 3:
        if (0.0f == m->unkE4) {
            BattleAudience_ChangeStatus(index, 0);
        }
        break;
    }
}

static BattleWeapon weapon_teresa_trans = {
    NULL, 0, // name..icon
    {0}, // field_0x6
    0, NULL, // itemId..description
    100, // baseAccuracy
    0, 0, 0, 0.0f, 0, 0, 0, 0, // baseFpCost..field_0x1B
    NULL, // hpDamageFn
    {0}, // hpDamageWork
    NULL, // fpDamageFn
    {0}, // fpDamageWork
    0x1100060, // targetClassFlags
    0x20000000, // targetPropertyFlags
    0, 0, // element..damagePattern
    3, // acLevel
    2, // field_0x6F
    NULL, // acHelpMsg
    0x20008, // special
    0x7FF, // counterResistFlags
    0, 0, 0, 0, 0, 0, 0, 0, // targetWeightFlags..poisonChance
    0, 0, 0, 0, 0, 0, 0, 0, // poisonTime..dodgyTime
    0, 0, 0, 0, 0, 0, 0, 0, // burnChance..atkChangeChance
    0, 0, 0, 0, 0, 0, 0, 0, // atkChangeTime..ohkoChance
    0, 0, 0, 0, 0, 0, 0, 0, // chargeStrength..paybackTime
    0, // holdFastTime
    100, // invisibleChance
    2, // invisibleTime
    0, 0, 0, 0, // hpRegenTime..fpRegenStrength
    {0}, // field_AE
    NULL, // mAttackEvtScript
    {0, 0, 0, 100, 0, 0, 0, 0, 0, 0, 0, 0}, // field_B4
};

void BattleAudienceCtrlProcessKinopioTransEvt(s32 index) {
    BattleWork* bw = _battleWorkPointer;
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    static f32 x;
    static f32 y;
    static f32 z;
    BattleUnit* unit;
    BattleUnitPart* parts;
    s32 partsId;
    s8 st1;
    s8 st0;
    switch (m->field_0x4) {
    case 0:
        BattleAudience_SetAnim(index, 1, FALSE);
        m->unkEC = (s32)BattleAudienceDetectTargetAll();
        m->field_0x8 = 0;
        psndSFXOn_3D("SFX_AUDIENCE_TELESA_MOVE1", &m->position);
        m->field_0x4 = 5;
    case 5:
        unit = (BattleUnit*)m->unkEC;
        parts = BattleGetUnitPartsPtr(BtlUnit_GetUnitId(unit), BtlUnit_GetBodyPartsId(unit));

        m->field_0x8++;
        m->position.x = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(m->mHomePosition.x, 0.0f, 5, m->field_0x8, 60);
        m->position.y = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(m->mHomePosition.y, 80.0f, 5, m->field_0x8, 60);
        m->position.z = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(m->mHomePosition.z, 100.0f, 5, m->field_0x8, 60);
        if (m->field_0x8 >= 60) {
            BattleAudience_SetAnim(index, 7, FALSE);
            BtlUnit_GetHitPos(unit, parts, &x, &y, &z);
            if (m->position.x >= x) {
                m->angle = 270.0f;
            } else {
                m->angle = 90.0f;
            }
            m->field_0x4 = 10;
            m->field_0x8 = 0;
            unit = (BattleUnit*)m->unkEC;
            parts = BattleGetUnitPartsPtr(BtlUnit_GetUnitId(unit), BtlUnit_GetBodyPartsId(unit));
            BtlUnit_GetHitPos(unit, parts, &x, &y, &z);
            psndSFXOn_3D("SFX_AUDIENCE_TELESA_MOVE1", &m->position);
        }
        break;
    case 10:
        m->field_0x8++;
        m->position.x = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(0.0f, x, 0, m->field_0x8, 30);
        m->position.y = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(80.0f, y - 15.0f, 4, m->field_0x8, 30);
        m->position.z = ((f32 (*)(f32, f32, s32, s32, s32))intplGetValue)(100.0f, z, 0, m->field_0x8, 30);
        if (m->field_0x8 == 30) {
            unit = (BattleUnit*)m->unkEC;
            parts = BattleGetUnitPartsPtr(BtlUnit_GetUnitId(unit), BtlUnit_GetBodyPartsId(unit));
            BtlUnit_GetStatus(unit, 0x12, &st1, &st0);
            if (st1 < 1 && !BtlUnit_CheckShadowGuard(unit)) {
                BattleCheckDamage(BattleGetSystemPtr(bw), unit, (struct BattleWorkUnitPart*)parts,
                                  &weapon_teresa_trans, 0x100);
                BtlUnit_snd_se(unit, "SFX_AUDIENCE_TELESA_INVISIBLE1", 0xF1194D80, 0);
            }
        }
        if (m->field_0x8 >= 120) {
            BattleAudience_ChangeStatus(index, 11);
        }
        break;
    }
}

s32 intrudeSound;

__declspec(section ".rodata") static Vec v0 = {0.0f, 0.0f, 0.0f};
void BattleAudienceCtrlProcessKinopioIntrude(s32 index) {
    BattleWork* bw = _battleWorkPointer;
    BattleAudienceMember* m;
    PouchData* pouch;
    f32 dx;
    f32 dz;
    f32 d;
    f32 tx;
    f32 tz;
    BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    pouch = pouchGetPtr();
    BattleAudience_SetAnim(index, 7, FALSE);
    switch (m->field_0x4) {
    case 0:
        if (irand(2) == 0) {
            m->field_0xC = 1.0f;
        } else {
            m->field_0xC = -1.0f;
        }
        if (pouch->rank == 0) {
            m->field_0x4 = 3;
        } else if (irand(2) == 0) {
            m->field_0x4 = 3;
        } else {
            m->field_0x4 = 50;
        }
        break;
    case 3:
        m->field_0x4 = 5;
        tx = 25.0f * m->field_0xC;
        tz = 110.0f;
        dx = tx - m->position.x;
        dz = tz - m->position.z;
        d = (f32)sqrt(dx * dx + dz * dz);
        m->field_0x78.x = 5.0f * (dx / d);
        m->field_0x78.y = 0.0f;
        m->unk88 = 0.0f;
        m->field_0x78.z = 5.0f * (dz / d);
        intrudeSound = ((s32 (*)(const char*))psndSFXOn)("SFX_AUDIENCE_HEIHO_MOVE1");
    case 5:
        if (m->position.z <= 110.0f) {
            m->field_0x4 = 10;
            m->position.z = 110.0f;
            m->field_0x78.x = 0.0f;
            m->field_0x78.y = 10.0f;
            m->unk88 = -0.7f;
            m->field_0x78.z = -1.5f;
            psndSFXOff(intrudeSound);
        }
        break;
    case 10:
        if (m->field_0x78.y <= 0.0f && m->position.y <= 0.0f) {
            m->field_0x4 = 15;
            m->position.y = 0.0f;
            m->field_0x78.y = 0.0f;
            m->unk88 = 0.0f;
            tx = 300.0f * m->field_0xC;
            tz = 0.0f;
            dx = tx - m->position.x;
            dz = tz - m->position.z;
            d = (f32)sqrt(dx * dx + dz * dz);
            m->field_0x78.x = 5.0f * (dx / d);
            m->field_0x78.y = 0.0f;
            m->field_0x78.z = 5.0f * (dz / d);
            btl_camera_set_mode(0, 3);
            btl_camera_set_moveto(0, 30, 698.0f * m->field_0xC, 100.0f, 0.0f, 0.0f, 60.0f, 0.0f, 4);
            intrudeSound = ((s32 (*)(const char*))psndSFXOn)("SFX_AUDIENCE_HEIHO_MOVE1");
        }
        break;
    case 15:
        m->mRotation.y = camGetPtr(4)->viewYaw;
        if (__fabs(m->position.x) >= 450.0) {
            m->field_0x4 = 16;
            m->field_0x8 = 35;
            m->field_0x78 = (Vec){0.0f, 0.0f, 0.0f};
        }
        break;
    case 16:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x4 = 18;
            m->field_0x8 = 25;
            btl_camera_set_mode(0, 0);
            btl_camera_set_moveSpeedLv(0, 2);
            psndSFXOff(intrudeSound);
        }
        break;
    case 18:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x4 = 19;
            m->field_0x8 = 60;
            btl_camera_set_moveSpeedLv(0, 1);
            effSmallStarEntry(0, 4, 185.0f * m->field_0xC, 20.0f, 40.0f, 0.0f, -1.0f, 0.0f);
        }
        break;
    case 19:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x4 = 20;
            btl_camera_set_moveSpeedLv(0, 1);
        }
    case 20:
        m->statusTimer = BattleStage_ObjectFallCheck();
        m->field_0x4 = 25;
        break;
    case 25:
        if (!evtCheckID(m->statusTimer)) {
            m->field_0x4 = 30;
            m->mRotation.y = 0.0f;
        }
        break;
    case 30:
        BattleAudience_ChangeStatus(index, 11);
        break;
    case 50:
        m->field_0x4 = 55;
        tx = 25.0f * m->field_0xC;
        tz = 110.0f;
        dx = tx - m->position.x;
        dz = tz - m->position.z;
        d = (f32)sqrt(dx * dx + dz * dz);
        m->field_0x78.x = 5.0f * (dx / d);
        m->field_0x78.y = 0.0f;
        m->unk88 = 0.0f;
        m->field_0x78.z = 5.0f * (dz / d);
        intrudeSound = ((s32 (*)(const char*))psndSFXOn)("SFX_AUDIENCE_HEIHO_MOVE1");
    case 55:
        if (m->position.z <= 110.0f) {
            m->field_0x4 = 60;
            m->position.z = 110.0f;
            m->field_0x78.x = 0.0f;
            m->field_0x78.y = 10.0f;
            m->unk88 = -0.7f;
            m->field_0x78.z = -1.5f;
            psndSFXOff(intrudeSound);
        }
        break;
    case 60:
        if (m->field_0x78.y <= 0.0f && m->position.y <= 0.0f) {
            m->field_0x4 = 65;
            m->field_0x8 = 0;
            m->position.y = 0.0f;
            m->field_0x78.x = 0.0f;
            m->field_0x78.y = 0.0f;
            m->unk88 = 0.0f;
            m->field_0x78.z = 0.0f;
            intrudeSound = ((s32 (*)(const char*))psndSFXOn)("SFX_AUDIENCE_HEIHO_MOVE1");
        }
        break;
    case 65:
    case 66:
    case 67:
        m->field_0x8++;
        if (1.0f == m->field_0xC) {
            m->angle = 270.0f;
        }
        if (-1.0f == m->field_0xC) {
            m->angle = 90.0f;
        }
        if (m->field_0x8 <= 5) {
            m->position.x -= 5.0f * m->field_0xC;
        } else if (m->field_0x8 <= 10) {
            m->position.x += 5.0f * m->field_0xC;
        }
        if (m->field_0x8 == 10) {
            if (m->field_0x4 == 67) {
                m->field_0x4 = 70;
            } else {
                m->field_0x4++;
            }
            m->field_0x8 = 0;
        }
        break;
    case 70:
        BattleStage_NozzleWorkCheck(1);
        m->statusTimer = bw->unk18298;
        m->field_0x4 = 75;
        tx = 300.0f * m->field_0xC;
        tz = 0.0f;
        dx = tx - m->position.x;
        dz = tz - m->position.z;
        d = (f32)sqrt(dx * dx + dz * dz);
        m->field_0x78.x = 5.0f * (dx / d);
        m->field_0x78.y = 0.0f;
        m->field_0x78.z = 5.0f * (dz / d);
        break;
    case 75:
        if (__fabs(m->position.x) >= 300.0) {
            m->field_0x4 = 80;
            m->field_0x78 = (Vec){0.0f, 0.0f, 0.0f};
            psndSFXOff(intrudeSound);
        }
        break;
    case 80:
        if (!evtCheckID(m->statusTimer)) {
            m->field_0x4 = 85;
        }
        break;
    case 85:
        BattleAudience_ChangeStatus(index, 11);
        break;
    }
}

void BattleAudienceCtrlProcessKinopioSing(s32 index) {
    BattleAudience* base = BattleAudienceBaseGetPtr();
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    f32 y;
    f32 z;
    s32 i;
    switch (m->field_0x4) {
    case 0:
        m->field_0x8 = 30;
        m->field_0x4++;
    case 1:
        m->field_0x8--;
        m->mRotation.y += 6.0f;
        if (m->field_0x8 == 15) {
            BattleAudience_SetAnim(index, 14, FALSE);
            BattleAudienceSoundSing(index);
        }
        if (m->field_0x8 <= 0) {
            m->field_0x8 = 120;
            m->field_0x4++;
        }
        break;
    case 2:
        m->field_0x8--;
        if ((u32)(s32)gp->retraceCount % 10 == 0) {
            z = m->position.z + (f32)irand(10) - 5.0f;
            y = m->position.y + (f32)irand(10);
            effOnpuN64Entry(0, m->position.x + (f32)irand(200) - 100.0f, y, z);
        }
        if (m->field_0x8 <= 0) {
            for (i = 0; i < base->mMaxAudience; i++) {
                if (index != i) {
                    BattleAudienceCtrlProcessKinopioSingSub(i);
                }
            }
            m->field_0x8 = 30;
            m->field_0x4++;
        }
        break;
    case 3:
        m->field_0x8--;
        m->mRotation.y += 6.0f;
        if (m->field_0x8 <= 15) {
            BattleAudience_SetAnim(index, 1, FALSE);
        }
        if (m->field_0x8 <= 0) {
            BattleAudience_ChangeStatus(index, 0);
        }
        break;
    }
}

void BattleAudienceCtrlProcessKinopioSingSub(s32 index) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if (m->flags & 0x100) {
        BattleAudienceCtrlProcessKinopioSingSub(index - 1);
    } else if (m->status != 17) {
        BattleAudience_ChangeStatus(index, 13);
        m->unkF4 = 3;
    }
}

void BattleAudienceCtrlProcessKinopioShell(s32 index) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if (m->field_0x4 >= 2 && m->field_0x4 <= 5) {
        BattleAudience_SetAnim(index, 15, FALSE);
    } else {
        BattleAudience_SetAnim(index, 1, FALSE);
    }
    switch (m->field_0x4) {
    case 0:
        m->field_0x8 = irand(30);
        m->field_0x4++;
    case 1:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x4++;
        }
        break;
    case 2:
        m->unkDC = 5.0f;
        m->unkE4 = -0.3f;
        BattleAudienceSoundShell(index);
        m->field_0x4++;
        break;
    case 3:
        break;
    case 4:
        m->field_0x8 = irand(30);
        m->field_0x4++;
    case 5:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x4++;
        }
        break;
    case 6:
        m->unkDC = 5.0f;
        m->unkE4 = -0.3f;
        m->field_0x8 = 10;
        BattleAudienceSoundShell(index);
        m->field_0x4++;
        break;
    case 7:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            BattleAudience_ChangeStatus(index, 0);
        }
        m->statusTimer = 0;
        break;
    }
}

void BattleAudienceCtrlProcessKinopioIgnite(s32 index, s32 front) {
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 16, FALSE);
    } else {
        BattleAudience_SetAnim(index, 17, FALSE);
    }
    switch (m->field_0x4) {
    case 0:
        m->field_0x8 = 30;
        BattleAudienceSoundBombIgnite(index, 180, 120);
        m->field_0x4++;
    case 1:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x8 = 10;
            m->field_0x4++;
        }
        break;
    case 2:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x4++;
        }
        break;
    case 3:
        break;
    }
}

void BattleAudienceCtrlProcessKinopioFire(s32 index, s32 front) {
    BattleAudience* base;
    BattleAudienceMember* m;
    s32 i;
    base = BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    if ((u8)front == 1) {
        BattleAudience_SetAnim(index, 16, FALSE);
    } else {
        BattleAudience_SetAnim(index, 17, FALSE);
    }
    switch (m->field_0x4) {
    case 0:
        m->field_0x8 = 10;
        m->field_0x4++;
    case 1:
        m->baseScale.x += 0.05f;
        m->baseScale.y += 0.05f;
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            s32 offs[24][2] = {{0, 3},  {-1, 2},  {0, 2},  {1, 2},  {-2, 1},  {-1, 1},  {0, 1},  {1, 1},
                               {2, 1},  {-3, 0},  {-2, 0}, {-1, 0}, {1, 0},   {2, 0},   {3, 0},  {-2, -1},
                               {-1, -1}, {0, -1}, {1, -1}, {2, -1}, {-1, -2}, {0, -2},  {1, -2}, {0, -3}};
            BattleAudienceSoundBombFire(index);
            m->flags &= ~4;
            if (index < 60) {
                effSandarsEntry(4, m->position.x, 35.0f + m->position.y, m->position.z, 0.0f);
            }
            btl_camera_shake_h(0, 5.0f, 0.0f, 30, 0);
            for (i = 0; i < 24; i++) {
                s32 n = BattleAudience_GetAudienceNoFromOffset(index, offs[i][0], offs[i][1]);
                if (n != -1) {
                    BattleAudienceCtrlProcessKinopioFireSub(n);
                }
            }
            BattleAudiencePuniAllEscape();
            m->field_0x8 = 60;
            m->field_0x4++;
        }
        break;
    case 2:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            m->field_0x4++;
        }
        break;
    case 3:
        BattleAudience_Delete(index);
        base->mTargetAudienceCount -= 1.0f;
        break;
    }
}

void BattleAudienceCtrlProcessKinopioFireSub(s32 index) {
    BattleAudience* base = BattleAudienceBaseGetPtr();
    BattleAudienceMember* m = BattleAudienceGetPtr(index);
    if (m->flags & 0x100) {
        BattleAudienceCtrlProcessKinopioFireSub(index - 1);
    } else if ((u8)BattleAudience_GetSysCtrl(index)) {
        if (m->type == 9) {
            if (m->status != 19) {
                BattleAudience_ChangeStatus(index, 19);
            } else {
                return;
            }
        } else if (m->status != 17) {
            BattleAudience_Delete(index);
            base->mTargetAudienceCount -= 1.0f;
        }
    }
}

void BattleAudienceCtrlProcessKinopioEat(s32 index) {
    BattleAudience* base;
    BattleAudienceMember* m;
    BattleStage* stage;
    BattleAudienceMember* t;
    s32 list[60];
    f32 px;
    f32 pz;
    s32 i;
    s32 cnt;
    s32 k;
    base = BattleAudienceBaseGetPtr();
    m = BattleAudienceGetPtr(index);
    stage = BattleStageGetPtr();
    switch (m->field_0x4) {
    case 0:
        k = BattleAudienceDetectPakkunEatTarget(index);
        if (k != -1) {
            m->unkF0 = k;
            t = BattleAudienceGetPtr(m->unkF0);
            if (m->position.x >= t->position.x) {
                m->angle = 270.0f;
            } else {
                m->angle = 90.0f;
            }
            BattleAudience_SetAnim(index, 0, FALSE);
        } else {
            BattleAudience_ChangeStatus(index, 0);
            break;
        }
        m->field_0x8 = 30;
        m->field_0x4++;
    case 1:
        t = BattleAudienceGetPtr(m->unkF0);
        if (m->field_0x8 > 0) {
            m->field_0x8--;
        }
        if (m->field_0x8 <= 0 && 0.0f == t->unkD0) {
            BattleAudience_SetAnim(index, 18, FALSE);
            t->flags |= 2;
            m->field_0x4 = 3;
        }
        break;
    case 3:
        t = BattleAudienceGetPtr(m->unkF0);
        if (m->position.x >= t->position.x) {
            m->dispOffset.x -= 6.0f;
        } else {
            m->dispOffset.x += 6.0f;
        }
        if (m->dispOffset.x <= -60.0f || m->dispOffset.x >= 60.0f) {
            m->field_0x4++;
        }
        break;
    case 4:
        t = BattleAudienceGetPtr(m->unkF0);
        t->flags = 0;
        base->mTargetAudienceCount -= 1.0f;
        BattleAudienceSoundPakkunEat(index);
        m->field_0x4++;
        break;
    case 5:
        if (m->dispOffset.x > 0.0f) {
            m->dispOffset.x -= 6.0f;
            if (m->dispOffset.x <= 0.0f) {
                m->field_0x4 = 7;
            }
        } else {
            m->dispOffset.x += 6.0f;
            if (m->dispOffset.x >= 0.0f) {
                m->field_0x4 = 7;
            }
        }
        break;
    case 7:
        if (BattleAudienceDetectPakkunEatTarget(index) != -1) {
            m->field_0x4 = 99;
            m->field_0x8 = 10;
        } else {
            cnt = 0;
            for (i = 0; i <= 59; i++) {
                if (!(u8)BattleAudience_GetExist(i) && !(BattleAudienceGetPtr(i)->flags & 0x100) &&
                    BattleAudienceDetectPakkunEatTarget(i) != -1) {
                    list[cnt] = i;
                    cnt++;
                }
            }
            if (cnt >= 1) {
                m->field_0x4 = 8;
                m->statusTimer = list[irand(cnt)];
            } else if (i == 60) {
                m->field_0x4 = 99;
                m->field_0x8 = 10;
            }
        }
        break;
    case 8:
        m->field_0x78.x = 0.0f;
        m->field_0x78.y = -1.0f;
        m->field_0x78.z = 0.0f;
        m->field_0x4++;
        break;
    case 9:
        if (m->position.y <= -100.0f) {
            k = m->statusTimer;
            pz = 0.1f * (f32)(k % 20) + (f32)(k / 20 * 30 + 115);
            m->mHomePosition.x = m->position.x = (f32)((rand() * 10 / 32767) + (k % 20 * 25 - 235));
            m->mHomePosition.y = stage->audienceSizeY;
            m->mHomePosition.z = m->position.z = pz;

            m->field_0x4++;
        }
        break;
    case 10:
        m->field_0x78.x = 0.0f;
        m->field_0x78.y = 1.0f;
        m->field_0x78.z = 0.0f;
        m->field_0x4++;
        break;
    case 11:
        if (m->position.y >= stage->audienceSizeY) {
            m->position.y = m->mHomePosition.y = stage->audienceSizeY;
            m->field_0x78.y = 0.0f;
            m->field_0x4 = 99;
            m->field_0x8 = 10;
            memcpy(BattleAudienceGetPtr(m->statusTimer), m, 0x134);
            BattleAudience_Delete(index);
        }
        break;
    case 99:
        m->field_0x8--;
        if (m->field_0x8 <= 0) {
            BattleAudience_ChangeStatus(index, 0);
        }
        break;
    }
}
