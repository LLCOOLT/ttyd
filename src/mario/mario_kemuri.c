#include "mario/mario.h"
#include "mario/mariost.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "eff/eff_kemuri.h"
#include "eff/eff_ripple.h"
#include "eff/n64/eff_kemuri7_n64.h"
#include "party.h"
#include "system.h"
#include <string.h>

extern s32 kpaGetLevel(void);
extern f32 kpaGetBaseScale(s32 level);
extern s32 kpaGetStageViewType(void);
extern s32 kpaGetBodyStatus(void);
extern f32 toMovedirSimple(f32 angle);
extern int rand(void);
extern EffectEntry* effKemuri2Entry(s32 type, f32 x, f32 y, f32 z, f32 s, f32 c);
extern EffectEntry* effMugiKemuriEntry(f32 x, f32 y, f32 z, f32 dir);
extern EffectEntry* effMugiKemuri2Entry(s32 type, f32 x, f32 y, f32 z, f32 dir, f32 side);
extern EffectEntry* effWaterDamageN64Entry(s32 type, s32 count, f32 x, f32 y, f32 z, f32 scale);

#pragma dont_inline on
void kemuri(void);
void kemuri_mugi(void);
void mario_kemuri_landon(void);

#define kemuriEntry ((EffectEntry * (*)(s32, f32, f32, f32, f32))effKemuriEntry)
#define MF(p, off) (*(f32*)((u8*)(p) + (off)))
#define MU8(p, off) (*(u8*)((u8*)(p) + (off)))
#define MS8(p, off) (*(s8*)((u8*)(p) + (off)))
#define MS16(p, off) (*(s16*)((u8*)(p) + (off)))
#define MPTR(p, off) (*(void**)((u8*)(p) + (off)))

static void mario_kemuri_80130474(void) {
    static s32 ct = 8;
    static s32 left_or_right;
    MarioWork* mario = marioGetPtr();
    u32 attr;

    attr = 0;

    if ((u32)marioStGetSystemLevel() == 0 && !(mario->flags & 0x01000000)) {
        if (mario->currMotionId == 0x1D) {
            attr = 0;
        }
        else if (mario->currMotionId != 3) {
            if (mario->hitobjStandOn != NULL) {
                attr = hitGetAttr(mario->hitobjStandOn);
            }
        }
        else if (mario->hitobjJumpFrom != NULL) {
            attr = hitGetAttr(mario->hitobjJumpFrom);
        }
        {
            if (attr & 0x1000) {
                kemuri_mugi();
            }
            else if (attr & 0x100) {
                mario_kemuri_landon();
            }
            else if (attr & 0x100000) {
                f32 c, s;
                mario = marioGetPtr();
                if (mario->currMotionId != 2 && mario->currMotionId != 1) {
                    ct = 8;
                }
                else if (ct++ > 8) {
                    ct = 0;
                    sincosf(&s, &c, 6.2831855f * reviseAngle(-mario->directionView) / 360.0f);
                    effKemuri7N64Entry(mario->position.x + 0.2f * (mario->wPlayerCollisionBox.x * s),
                                       0.5f + mario->position.y,
                                       mario->position.z + 0.2f * (mario->wPlayerCollisionBox.x * c),
                                       -mario->directionView, (f32)left_or_right);
                    left_or_right = left_or_right == 0;
                }
            }
            else if (!(mario->flags & 0x01000000)) {
                if (kpaGetBodyStatus() <= 0 && mario->characterId != 1) {
                    kemuri();
                }
            }
        }
    }
}

void mario_simple_kemuri(void) {
    MarioWork* mario = marioGetPtr();
    EffectEntry* eff = kemuriEntry(0, mario->position.x, mario->position.y, mario->position.z, 0.0f);

    if (mario->flags & 0x02000000) {
        MF(eff->userdata, 0x74) = 0.6f;
    }
}

void unk_80130374(void) {
    MarioWork* mario = marioGetPtr();
    HitEntry* hit = mario->hitobjStandOn;
    u32 attr;
    EffectEntry* eff;

    if (hit != NULL) {
        if (mario->trigFlags & 0x20000) {
            mario->trigFlags &= ~0x20000;
        }
        else {
            attr = hitGetAttr(hit);
            if (attr & 0x1000) {
                kemuri_mugi();
            }
            else if (attr & 0x100) {
                mario_kemuri_landon();
            }
            else {
                eff = kemuriEntry(0, mario->position.x, mario->position.y, mario->position.z, 0.0f);
                if (mario->flags & 0x02000000) {
                    MF(eff->userdata, 0x74) = 0.6f;
                }
            }
        }
    }
}

void mario_kemuri_landon(void) {
    static s32 cnt;
    static s32 cnt2 = 10;
    MarioWork* mario = marioGetPtr();
    s32 type = 0;

    if (strcmp(gp->currentMapName, "mri_05\0") == 0) {
        type = 10;
    }
    if (mario->currMotionId == 3 && mario->airTimer == 1 && cnt2 == 10) {
        effWaterDamageN64Entry(type + 5, 30, mario->position.x, mario->position.y, mario->position.z, 1.0f);
        cnt2 = 0;
        effRippleEntry(0, mario->position.x, 11.0f + mario->position.y, mario->position.z);
    }
    cnt2++;
    if (cnt2 > 10) {
        cnt2 = 10;
    }
    if (mario->currMotionId == 2 || mario->currMotionId == 1 || !mario->currMotionId || mario->currMotionId == 0xD) {
        if (mario->currMotionId == 0xD) {
            cnt = 0;
        }
        if (--cnt < 0) {
            cnt = rand() % 20 + 30;
            effRippleEntry(0, mario->position.x, 11.0f + mario->position.y, mario->position.z);
        }
        if (mario->currMotionId == 1 || mario->currMotionId == 2 || mario->currMotionId == 0xD) {
            if (gp->retraceCount % 20 == 0 || mario->currMotionId == 0xD) {
                effWaterDamageN64Entry(type + 7, 30, mario->position.x, 11.0f + mario->position.y, mario->position.z, 1.0f);
            }
        }
    }
}

void kemuri_mugi(void) {
    static f32 dir;
    static s32 ct = 4;
    static s32 ct2 = 10;
    static s32 left_or_right;
    MarioWork* mario = marioGetPtr();

    if (strncmp(gp->currentMapName, "mri", 3) == 0) {
        if (mario->currMotionId == 0 && gp->retraceCount % 30 == 0) {
            effWaterDamageN64Entry(16, 30, mario->position.x, 11.0f + mario->position.y, mario->position.z, 0.8f);
        }
        if (mario->currMotionId == 1 || mario->currMotionId == 2 || mario->currMotionId == 0xD) {
            if (gp->retraceCount % 20 == 0 || mario->currMotionId == 0xD) {
                effWaterDamageN64Entry(17, 30, mario->position.x, 11.0f + mario->position.y, mario->position.z, 0.8f);
            }
        }
    }
    else if (mario->currMotionId == 3 && mario->airTimer == 1 && ct2 == 10) {
        effMugiKemuriEntry(mario->position.x, 14.0f + mario->position.y, mario->position.z, dir);
        dir = reviseAngle(35.0f + dir);
        ct2 = 0;
    }
    else {
        ct2++;
        if (ct2 > 10) {
            ct2 = 10;
        }
        if (mario->currMotionId != 2 && mario->currMotionId != 1) {
            ct = 2;
        }
        else if (ct++ > 2) {
            f32 s, c;
            f32 x, y, z;
            ct = 0;
            sincosf(&s, &c, 6.2831855f * reviseAngle(-mario->directionView) / 360.0f);
            x = -0.4f * (mario->wPlayerCollisionBox.x * s) + mario->position.x;
            y = 3.0f + mario->position.y;
            z = -0.4f * (mario->wPlayerCollisionBox.x * c) + mario->position.z;
            effMugiKemuri2Entry(0, x, y, z, -mario->directionView + (f32)(rand() % 10) - 5.0f, (f32)left_or_right);
            left_or_right = left_or_right == 0;
        }
    }
}

void kemuri(void) {
    static f32 dir;
    static s32 ct = 4;
    MarioWork* mario = marioGetPtr();
    EffectEntry* eff;
    f32 s, c;
    f32 x, y, z;

    if (MS16(mario, 0x54) != 0 && MPTR(mario, 0x208) == NULL && mario->hitobjStandOn != NULL) {
        if (mario->trigFlags & 0x20000) {
            mario->trigFlags &= ~0x20000;
        }
        else {
            x = mario->position.x;
            y = mario->position.y;
            z = mario->position.z;
            if (mario->characterId == 2) {
                eff = kemuriEntry(0, x, y, 10.0f + z, 0.0f);
                MF(eff->userdata, 0x74) = kpaGetBaseScale(kpaGetLevel());
            }
            else {
                kemuriEntry(0, x, y, z, dir);
            }
        }
    }
    else if (mario->currMotionId != 2) {
        ct = 7;
    }
    else if (mario->characterId != 2) {
        if (ct++ > 6) {
            ct = 0;
            sincosf(&s, &c, 6.2831855f * reviseAngle(-mario->directionView) / 360.0f);
            {
            x = mario->position.x + 0.2f * (mario->wPlayerCollisionBox.x * s);
            y = 1.5f + mario->position.y;
            z = mario->position.z + 0.2f * (mario->wPlayerCollisionBox.x * c);
            eff = effKemuri2Entry(0, x, y, z, s, c);
            }
            if (mario->flags & 0x02000000) {
                MF(eff->userdata, 0x74) = 0.6f;
            }
        }
    }
    else if (--ct <= 0) {
        f32 scale, dist;
        sincosf(&s, &c, 6.2831855f * reviseAngle(-mario->directionView) / 360.0f);
        sincosf(&s, &c, toMovedirSimple(180.0f + (kpaGetStageViewType() == 0 ? mario->unk1AC : mario->unk1A8)));
        switch (kpaGetLevel()) {
        case 0:
            ct = 4;
            dist = 10.0f;
            scale = 0.5f;
            break;
        case 1:
            ct = 7;
            dist = 15.0f;
            scale = 1.0f;
            break;
        case 2:
            ct = 10;
            dist = 20.0f;
            scale = 2.0f;
            break;
        case 3:
            ct = 10;
            dist = 50.0f;
            scale = 4.0f;
            break;
        }
        x = mario->position.x + dist * s;
        y = 1.5f + mario->position.y;
        z = mario->position.z + dist * c;
        eff = effKemuri2Entry(0, x, y, z, s, c);
        MF(eff->userdata, 0x74) = scale;
    }
}

void party_kemuri(PartyEntry* party) {

    if (MU8(party, 0x32) != 1) {
        if (MU8(party, 0x34) == 3 && MS8(party, 0x31) == 4) {
            if (MPTR(party, 0x138) != NULL) {
                if (MF(party, 0x104) < 2.0f) {
                    MS8(party, 0x2c) = 7;
                }
                else if (MS8(party, 0x2c)++ > 6) {
                    f32 c, s;
                    f32 x, y, z;
                    MS8(party, 0x2c) = 0;
                    sincosf(&s, &c, 6.2831855f * reviseAngle(-MF(party, 0x100)) / 360.0f);
                    effKemuri2Entry(0, MF(party, 0x58) + 0.2f * (MF(party, 0xF4) * s), 1.5f + MF(party, 0x5C), MF(party, 0x60) + 0.2f * (MF(party, 0xF4) * c), s, c);
                }
            }
            else {
                MS8(party, 0x2c) = 4;
            }
        }
        else if (MU8(party, 0x36) == 1) {
            if (MPTR(party, 0x138) != NULL) {
                if (MF(party, 0x104) < 2.0f) {
                    MS8(party, 0x2c) = 7;
                }
                else if (MS8(party, 0x2c)++ > 6) {
                    f32 c, s;
                    f32 x, y, z;
                    MS8(party, 0x2c) = 0;
                    sincosf(&s, &c, 6.2831855f * reviseAngle(-MF(party, 0x100)) / 360.0f);
                    effKemuri2Entry(0, MF(party, 0x58) + 0.2f * (MF(party, 0xF4) * s), 1.5f + MF(party, 0x5C), MF(party, 0x60) + 0.2f * (MF(party, 0xF4) * c), s, c);
                }
            }
            else {
                MS8(party, 0x2c) = 4;
            }
        }
    }
}
#pragma dont_inline reset
