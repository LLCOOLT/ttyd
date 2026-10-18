#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/icondrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>

typedef struct BDWork {
    s32 timer;
    s32 sndCount;
    u32 button[13];
    s32 pressed[13];
    s32 endTimer;
} BDWork;

#define NN (*(s32*)((u8*)work + 0x1cd0))
#define OUT (*(s32*)&ac->outputParams[0])
#define BTN(i) (*(u32*)((u8*)p + 8 + (i) * 4))
#define PRS(i) (*(s32*)((u8*)p + 0x3c + (i) * 4))

static u32 _button_table[7] = {0x100, 0x200, 0x400, 0x800, 0x40, 0x20, 0x10};

static void actionCommandDisp(s32 unused, f32 x, f32 y);

#ifdef NONMATCHING
s32 battleAcMain_ButtonDown(BattleWork *work)
{
  s32 off;
  BattleActions *ac = &work->actionCommands;
  u8 *disp = ((u8 *) work) + 0x1f20;
  s32 i;
  s32 k;
  s32 allDone;
  BDWork *p = (BDWork *) (((u8 *) work) + 0x1f4c);
  s32 flag = 0;
  const char *sfx;
  if (*(((u8 *) ac->mAcUnit) + 0x303))
  {
    flag = 1;
  }
  sfx = (0, "SFX_AC_BUTTON_PUSH1");
  do
  {
    allDone = 0;
    switch (ac->mAcState)
    {
      case 0:
      {
        ac->result = 1;
        memset(disp, 0, 0x2c);
        ((f32 *) disp)[5] = -300.0f;
        ((f32 *) disp)[6] = 0.0f;
        ((s32 *) disp)[8] = 20;
        memset(p->button, 0, 0x34);
        memset(p->pressed, 1, 0x34);
        for (i = 0, off = 0; i < (*((s32 *) (((u8 *) work) + 0x1cd0))); i++, off += 4)
        {
          switch (*((s32 *) (((u8 *) work) + 0x1cd4)))
          {
            case -2:
              *((u32 *) (((u8 *) p) + (off + 8))) = (irand(100) < 50) ? (0x100) : (0x200);
              *((s32 *) (((u8 *) p) + (off + 0x3c))) = 0;
              break;

            case -4:
              *((u32 *) (((u8 *) p) + (off + 8))) = (irand(100) < 50) ? (0x200) : (0x400);
              *((s32 *) (((u8 *) p) + (off + 0x3c))) = 0;
              break;

            case -3:
              if ((*((u32 *) (((u8 *) work) + 0x1cc4))) & 4)
            {
              *((u32 *) (((u8 *) p) + (off + 8))) = _button_table[irand(4)];
              *((s32 *) (((u8 *) p) + (off + 0x3c))) = 0;
            }
            else
            {
              s32 found = 0;
              u32 cand;
              s32 ok;
              while (!found)
              {
                s32 j;
                cand = _button_table[irand(4)];
                ok = 1;
                for (j = i - 1, k = j * 4; j >= 0; j--, k -= 4)
                {
                  if (cand == (*((u32 *) (((u8 *) p) + (k + 8)))))
                  {
                    ok = 0;
                  }
                }

                if (ok)
                {
                  found = 1;
                }
              }

              *((u32 *) (((u8 *) p) + (off + 8))) = cand;
              *((s32 *) (((u8 *) p) + (off + 0x3c))) = 0;
            }
              break;

            default:
            {
              s32 found = 0;
              u32 cand;
              s32 ok;
              while (!found)
              {
                s32 j;
                cand = _button_table[irand(7)];
                ok = 1;
                for (j = i - 1, k = j * 4; j >= 0; j--, k -= 4)
                {
                  if (cand == (*((u32 *) (((u8 *) p) + (k + 8)))))
                  {
                    ok = 0;
                  }
                }

                if (ok)
                {
                  found = 1;
                }
              }

              *((u32 *) (((u8 *) p) + (off + 8))) = cand;
              *((s32 *) (((u8 *) p) + (off + 0x3c))) = 0;
              break;
            }

          }

        }

        ac->mAcState = 99;
        break;
      }

      case 99:
        break;

      case 100:
        ac->mAcState = 1000;
        p->sndCount = 0;
        p->timer = *((s32 *) (((u8 *) work) + 0x1cc8));

      case 1000:
        if ((ac->setupFlags & 1) && ((*((u32 *) (((u8 *) ac->mAcUnit) + 0x278))) & 0x10))
      {
        if (ac->setupFlags & 2)
        {
          ac->setupParam--;
          if (ac->setupParam >= 0)
          {
            break;
          }
        }
        if (irand(100) >= 0)
        {
          ac->result = 0;
        }
        else
        {
          ac->result = 2;
          ac->mResultCount++;
        }
        return 0;
      }
        if ((*((s16 *) (((u8 *) work) + 0x1d18))) > 0)
      {
        (*((s16 *) (((u8 *) work) + 0x1d18)))--;
        ac->result = 2;
        allDone = 1;
        ac->mAcState = 1001;
        break;
      }
        *((s32 *) (&ac->outputParams[0])) = 0;
        allDone = 1;
        for (i = 0, off = 0; i < (*((s32 *) (((u8 *) work) + 0x1cd0))); i++, off += 4)
      {
        if (*((u32 *) (((u8 *) p) + (off + 8))))
        {
          if (*((s32 *) (((u8 *) p) + (off + 0x3c))))
          {
            (*((s32 *) (&ac->outputParams[0])))++;
          }
          else
            if (((*((u32 *) (((u8 *) p) + (off + 8)))) == BattlePadGetTrigger()) || flag)
          {
            *((s32 *) (((u8 *) p) + (off + 0x3c))) = 1;
            (*((s32 *) (&ac->outputParams[0])))++;
            if ((*((s32 *) (((u8 *) work) + 0x1ccc))) == 1)
            {
              if ((i + 1) < (*((s32 *) (((u8 *) work) + 0x1cd0))))
              {
                allDone = 0;
              }
              break;
            }
          }
          else
            if (BattlePadGetTrigger())
          {
            ac->result = 0;
            ac->mAcState = 1001;
            if (((*((u32 *) (((u8 *) work) + 0x1cc4))) & 2) && ((*((s32 *) (&ac->outputParams[0]))) > 0))
            {
              allDone = 1;
              ac->result |= 2;
              ac->result &= ~1;
              ac->mAcState = 1001;
              break;
            }
            return 1;
          }
          else
          {
            allDone = 0;
            if ((*((s32 *) (((u8 *) work) + 0x1ccc))) == 1)
            {
              break;
            }
          }
        }
      }

        if (p->sndCount != (*((s32 *) (&ac->outputParams[0]))))
      {
        psndSFXOn(sfx);
        p->sndCount = *((s32 *) (&ac->outputParams[0]));
      }
        if (allDone)
      {
        ac->result |= 2;
        allDone = 1;
        ac->result &= ~1;
        ac->mAcState = 1001;
        break;
      }
        p->timer--;
        if (p->timer < 0)
      {
        ac->result = 0;
        allDone = 1;
        ac->mAcState = 1001;
        if (((*((u32 *) (((u8 *) work) + 0x1cc4))) & 2) && ((*((s32 *) (&ac->outputParams[0]))) > 0))
        {
          ac->result |= 2;
          ac->result &= ~1;
          ac->mAcState = 1001;
        }
      }
        break;

      case 1001:
        ac->mAcState = 1002;

      case 1002:
        return 0;

      case 1003:
        p->endTimer = 60;
        ac->mAcState = 1004;
        break;

      case 1004:
        p->endTimer--;
        if (p->endTimer <= 0)
      {
        ac->mAcState = 1005;
      }
        break;

      case 1005:
        ac->maincb = (void *) 0;
        ac->dispcb = (void *) 0;
        ac->resultcb = (void *) 0;
        ac->deletecb = (void *) 0;
        break;

    }

  }
  while (allDone);
  return 1;
}
#endif

#ifdef NONMATCHING
s32 battleAcResult_ButtonDown(BattleWork* work) {
    return work->actionCommands.result;
}
#endif

#ifdef NONMATCHING
void battleAcDisp_ButtonDown(CameraId cameraId, void* param) {
    BattleWork* work = (BattleWork*)param;
    BattleActions* ac = &work->actionCommands;
    s32* disp;
    f32 x, y;
    disp = (s32*)((u8*)ac + 0x290);
    switch (ac->mAcState) {
        case 99:
        case 0:
            if (disp[8] > 0) {
                disp[8]--;
            }
            x = intplGetValue(4, 20 - disp[8], 20, -300.0f, 0.0f);
            y = 0.0f;
            break;
        default:
            x = y = 0.0f;
            break;
    }
    actionCommandDisp(0, x, y);
}
#endif

#ifdef NONMATCHING
void battleAcDelete_ButtonDown(BattleWork* work) {
    work->actionCommands.mAcState = 1003;
}
#endif

#ifdef NONMATCHING
static void actionCommandDisp(s32 unused, f32 x, f32 y)
{
  BattleWork *work = _battleWorkPointer;
  BDWork *p = (BDWork *) (((u8 *) work) + 0x1f4c);
  s32 k;
  s32 end = ((*((s32 *) (((u8 *) work) + 0x1cd0))) * 3) + 2;
  int size;
  s32 i;
  s32 count;
  s32 off;
  s32 j;
  f32 bx = (-200.0f) + x;
  f32 by;
  f32 lx = bx - 40.0f;
  Vec pos = {0.0f, 0.0f, -2.0f};
  by = 70.0f + y;
  pos.x = lx;
  pos.y = by;
  iconDispGx(&pos, 16, 0x8f, 1.0f);
  lx += 16.0f;
  for (k = 1; k < end; k++)
  {
    Vec pos2 = {0.0f, 0.0f, -2.0f};
    pos2.x = lx;
    pos2.y = by;
    size = 16;
    iconDispGx(&pos2, size, 0x8e, 1.0f);
    lx += 16.0f;
  }

  {
    Vec pos3 = {0.0f, 0.0f, -2.0f};
    pos3.x = lx;
    pos3.y = by;
    iconDispGx(&pos3, 16, 0x90, 1.0f);
  }
  if ((*((u32 *) (((u8 *) work) + 0x1cc4))) & 1)
  {
    for (count = 0, j = 0; count < (*((s32 *) (((u8 *) work) + 0x1cd0))); count++, j += 4)
    {
      if (!p->pressed[j >> 2])
      {
        break;
      }
    }

    if (count < (*((s32 *) (((u8 *) work) + 0x1cd0))))
    {
      count++;
    }
  }
  else
  {
    count = *((s32 *) (((u8 *) work) + 0x1cd0));
  }
  for (i = 0, off = 0, j = 0; i < count; i++, off += 0x30, j += 4)
  {
    s32 a;
    s32 b;
    if (p->button[j >> 2] == 0U)
    {
      continue;
    }
    switch (p->button[(j >> 1) >> 1])
    {
      case 0x100:
        a = 0x65;
        b = 0x64;
        break;

      case 0x200:
        a = 0x67;
        b = 0x66;
        break;

      case 0x400:
        a = 0x69;
        b = 0x68;
        break;

      case 0x800:
        a = 0x6b;
        b = 0x6a;
        break;

      case 0x40:
        a = 0x7f;
        b = 0x7e;
        break;

      case 0x20:
        a = 0x81;
        b = 0x80;
        break;

      case 0x10:
        a = 0x83;
        b = 0x82;
        break;

      case 0x40000:

      default:
        a = 0x78;
        b = 0x79;
        break;

    }

    if (p->pressed[j >> 2])
    {
      Vec pos4 = {0.0f, 0.0f, 0.0f};
      pos4.x = bx + ((f32) off);
      pos4.y = by;
      ((void (*)(Vec *, s32, s32, f32)) iconDispGx)(&pos4, size, a, 1.0f);
    }
    else
    {
      Vec pos5 = {0.0f, 0.0f, 0.0f};
      pos5.x = bx + ((f32) off);
      pos5.y = by;
      ((void (*)(Vec *, s32, s32, f32)) iconDispGx)(&pos5, size, b, 1.0f);
    }
  }

}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): battleAcMain_ButtonDown (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fd5d0[3] = { 0.0f, 0.0f, -2.0f };
__declspec(section ".rodata") const f32 vec3_802fd5dc[3] = { 0.0f, 0.0f, -2.0f };
__declspec(section ".rodata") const f32 vec3_802fd5e8[3] = { 0.0f, 0.0f, -2.0f };
__declspec(section ".rodata") const f32 vec3_802fd5f4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fd600[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const u32 gap_04_802FD60C_rodata[1] = { 0x00000000 };
__declspec(section ".rodata") const f64 double_to_int_802fd610 = 4503601774854144;
__declspec(section ".rodata") const char str_802FD618[] = "SFX_AC_BUTTON_PUSH1";
__declspec(section ".rodata") const u32 gap_04_802FD62C_rodata[1] = { 0x00000000 };
#pragma force_active reset
__declspec(section ".sdata2") const f32 float_neg200_804204e8 = -200.0f;
__declspec(section ".sdata2") const f32 float_40_804204ec = 40.0f;
__declspec(section ".sdata2") const f32 float_70_804204f0 = 70.0f;
__declspec(section ".sdata2") const f32 float_1_804204f4 = 1.0f;
__declspec(section ".sdata2") const f32 float_16_804204f8 = 16.0f;
__declspec(section ".sdata2") const f32 float_neg300_804204fc = -300.0f;
__declspec(section ".sdata2") const f32 float_0_80420500 = 0.0f;

asm static void actionCommandDisp(s32 unused, f32 x, f32 y) {
	nofralloc
	stwu r1, -0xb0(r1)
	mflr r0
	stw r0, 0xb4(r1)
	stfd f31, 0xa0(r1)
	psq_st f31, 0xa8(r1), 0, 0
	stfd f30, 0x90(r1)
	psq_st f30, 0x98(r1), 0, 0
	stfd f29, 0x80(r1)
	psq_st f29, 0x88(r1), 0, 0
	stfd f28, 0x70(r1)
	psq_st f28, 0x78(r1), 0, 0
	stmw r26, 0x58(r1)
	lfs f0, float_neg200_804204e8(r2)
	lis r3, vec3_802fd5d0@ha
	addi r31, r3, vec3_802fd5d0@l
	lwz r26, _battleWorkPointer(r13)
	fadds f30, f0, f1
	lfs f1, float_40_804204ec(r2)
	lfs f0, float_70_804204f0(r2)
	addi r30, r26, 0x1f4c
	lwz r4, 0x1cd0(r26)
	addi r3, r1, 0x38
	lwz r0, 0x0(r31)
	mulli r5, r4, 0x3
	lwz r4, 0x4(r31)
	fsubs f28, f30, f1
	stw r0, 0x38(r1)
	fadds f29, f0, f2
	lwz r0, 0x8(r31)
	stw r4, 0x3c(r1)
	addi r28, r5, 0x2
	lfs f1, float_1_804204f4(r2)
	li r4, 0x10
	stw r0, 0x40(r1)
	li r5, 0x8f
	stfs f28, 0x38(r1)
	stfs f29, 0x3c(r1)
	bl iconDispGx
	lfs f31, float_16_804204f8(r2)
	li r27, 0x1
	fadds f28, f28, f31
	b @1
	@2:
	lwz r0, 0xc(r31)
	addi r3, r1, 0x2c
	lwz r6, 0x10(r31)
	li r4, 0x10
	stw r0, 0x2c(r1)
	li r5, 0x8e
	lwz r0, 0x14(r31)
	stw r6, 0x30(r1)
	lfs f1, float_1_804204f4(r2)
	stw r0, 0x34(r1)
	stfs f28, 0x2c(r1)
	stfs f29, 0x30(r1)
	bl iconDispGx
	fadds f28, f28, f31
	addi r27, r27, 0x1
	@1:
	cmpw r27, r28
	blt @2
	lwz r0, 0x18(r31)
	addi r3, r1, 0x20
	lwz r6, 0x1c(r31)
	li r4, 0x10
	stw r0, 0x20(r1)
	li r5, 0x90
	lwz r0, 0x20(r31)
	stw r6, 0x24(r1)
	lfs f1, float_1_804204f4(r2)
	stw r0, 0x28(r1)
	stfs f28, 0x20(r1)
	stfs f29, 0x24(r1)
	bl iconDispGx
	lwz r0, 0x1cc4(r26)
	clrlwi. r0, r0, 31
	beq @3
	lwz r4, 0x1cd0(r26)
	li r28, 0x0
	li r3, 0x0
	mtctr r4
	cmpwi r4, 0x0
	ble @4
	@5:
	addi r0, r3, 0x3c
	lwzx r0, r30, r0
	cmpwi r0, 0x0
	beq @4
	addi r28, r28, 0x1
	addi r3, r3, 0x4
	bdnz @5
	@4:
	cmpw r28, r4
	bge @6
	addi r28, r28, 0x1
	b @6
	@3:
	lwz r28, 0x1cd0(r26)
	@6:
	li r29, 0x0
	li r27, 0x0
	li r26, 0x0
	b @7
	@8:
	add r4, r30, r26
	lwz r3, 0x8(r4)
	cmplwi r3, 0x0
	beq @9
	cmpwi r3, 0x200
	beq @10
	bge @11
	cmpwi r3, 0x40
	beq @12
	bge @13
	cmpwi r3, 0x20
	beq @14
	bge @15
	cmpwi r3, 0x10
	beq @16
	b @15
	@13:
	cmpwi r3, 0x100
	beq @17
	b @15
	@11:
	cmpwi r3, 0x800
	beq @18
	bge @19
	cmpwi r3, 0x400
	beq @20
	b @15
	@19:
	lis r0, 0x4
	cmpw r3, r0
	beq @15
	b @15
	@17:
	li r5, 0x65
	li r6, 0x64
	b @21
	@10:
	li r5, 0x67
	li r6, 0x66
	b @21
	@20:
	li r5, 0x69
	li r6, 0x68
	b @21
	@18:
	li r5, 0x6b
	li r6, 0x6a
	b @21
	@12:
	li r5, 0x7f
	li r6, 0x7e
	b @21
	@14:
	li r5, 0x81
	li r6, 0x80
	b @21
	@16:
	li r5, 0x83
	li r6, 0x82
	b @21
	@15:
	li r5, 0x78
	li r6, 0x79
	@21:
	lwz r0, 0x3c(r4)
	cmpwi r0, 0x0
	beq @22
	xoris r3, r27, 0x8000
	lis r0, 0x4330
	stw r3, 0x4c(r1)
	addi r3, r1, 0x14
	lwz r7, 0x24(r31)
	li r4, 0x10
	stw r0, 0x48(r1)
	lfd f1, 0x40(r31)
	lfd f0, 0x48(r1)
	lwz r6, 0x28(r31)
	fsubs f0, f0, f1
	lwz r0, 0x2c(r31)
	stw r6, 0x18(r1)
	lfs f1, float_1_804204f4(r2)
	fadds f0, f30, f0
	stw r7, 0x14(r1)
	stw r0, 0x1c(r1)
	stfs f0, 0x14(r1)
	stfs f29, 0x18(r1)
	bl iconDispGx
	b @9
	@22:
	xoris r3, r27, 0x8000
	lis r0, 0x4330
	stw r3, 0x4c(r1)
	mr r5, r6
	lwz r7, 0x30(r31)
	addi r3, r1, 0x8
	stw r0, 0x48(r1)
	li r4, 0x10
	lfd f1, 0x40(r31)
	lfd f0, 0x48(r1)
	lwz r6, 0x34(r31)
	fsubs f0, f0, f1
	lwz r0, 0x38(r31)
	stw r6, 0xc(r1)
	lfs f1, float_1_804204f4(r2)
	fadds f0, f30, f0
	stw r7, 0x8(r1)
	stw r0, 0x10(r1)
	stfs f0, 0x8(r1)
	stfs f29, 0xc(r1)
	bl iconDispGx
	@9:
	addi r29, r29, 0x1
	addi r27, r27, 0x30
	addi r26, r26, 0x4
	@7:
	cmpw r29, r28
	blt @8
	psq_l f31, 0xa8(r1), 0, 0
	lfd f31, 0xa0(r1)
	psq_l f30, 0x98(r1), 0, 0
	lfd f30, 0x90(r1)
	psq_l f29, 0x88(r1), 0, 0
	lfd f29, 0x80(r1)
	psq_l f28, 0x78(r1), 0, 0
	lfd f28, 0x70(r1)
	lmw r26, 0x58(r1)
	lwz r0, 0xb4(r1)
	mtlr r0
	addi r1, r1, 0xb0
	blr
}

asm void battleAcDelete_ButtonDown(BattleWork* work) {
	nofralloc
	li r0, 0x3eb
	stw r0, 0x1c9c(r3)
	blr
}

asm void battleAcDisp_ButtonDown(CameraId cameraId, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r0, 0x1c9c(r4)
	addi r4, r4, 0x1f20
	cmpwi r0, 0x63
	beq @1
	bge @2
	cmpwi r0, 0x0
	beq @1
	b @2
	@1:
	lwz r3, 0x20(r4)
	cmpwi r3, 0x0
	ble @3
	subi r0, r3, 0x1
	stw r0, 0x20(r4)
	@3:
	lwz r0, 0x20(r4)
	li r3, 0x4
	lfs f1, float_neg300_804204fc(r2)
	li r5, 0x14
	lfs f2, float_0_80420500(r2)
	subfic r4, r0, 0x14
	bl intplGetValue
	lfs f2, float_0_80420500(r2)
	b @4
	@2:
	lfs f2, float_0_80420500(r2)
	fmr f1, f2
	@4:
	li r3, 0x0
	bl actionCommandDisp
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 battleAcResult_ButtonDown(BattleWork* work) {
	nofralloc
	lwz r3, 0x1cb8(r3)
	blr
}

asm s32 battleAcMain_ButtonDown(BattleWork* work) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stmw r20, 0x10(r1)
	mr r22, r3
	li r25, 0x0
	addi r29, r22, 0x1f4c
	addi r28, r22, 0x1f20
	lwz r3, 0x1c90(r3)
	lbz r0, 0x303(r3)
	cmplwi r0, 0x0
	beq @1
	li r25, 0x1
	@1:
	lis r3, str_802FD618@ha
	addi r31, r3, str_802FD618@l
	@2:
	lwz r0, 0x1c9c(r22)
	li r27, 0x0
	cmpwi r0, 0x3e8
	beq @3
	bge @4
	cmpwi r0, 0x63
	beq @5
	bge @6
	cmpwi r0, 0x0
	beq @7
	b @5
	@6:
	cmpwi r0, 0x65
	bge @5
	b @8
	@4:
	cmpwi r0, 0x3ec
	beq @9
	bge @10
	cmpwi r0, 0x3ea
	beq @11
	bge @12
	b @13
	@10:
	cmpwi r0, 0x3ee
	bge @5
	b @14
	@7:
	li r0, 0x1
	mr r3, r28
	stw r0, 0x1cb8(r22)
	li r4, 0x0
	li r5, 0x2c
	bl memset
	lfs f1, float_neg300_804204fc(r2)
	li r0, 0x14
	lfs f0, float_0_80420500(r2)
	addi r3, r29, 0x8
	stfs f1, 0x14(r28)
	li r4, 0x0
	li r5, 0x34
	stfs f0, 0x18(r28)
	stw r0, 0x20(r28)
	bl memset
	addi r3, r29, 0x3c
	li r4, 0x1
	li r5, 0x34
	bl memset
	li r30, 0x0
	li r26, 0x0
	b @15
	@16:
	lwz r0, 0x1cd4(r22)
	cmpwi r0, -0x3
	beq @17
	bge @18
	cmpwi r0, -0x4
	bge @19
	b @20
	@18:
	cmpwi r0, -0x1
	bge @20
	li r3, 0x64
	bl irand
	cmpwi r3, 0x32
	li r3, 0x200
	bge @21
	li r3, 0x100
	@21:
	add r4, r29, r26
	li r0, 0x0
	stw r3, 0x8(r4)
	stw r0, 0x3c(r4)
	b @22
	@19:
	li r3, 0x64
	bl irand
	cmpwi r3, 0x32
	li r3, 0x400
	bge @23
	li r3, 0x200
	@23:
	add r4, r29, r26
	li r0, 0x0
	stw r3, 0x8(r4)
	stw r0, 0x3c(r4)
	b @22
	@17:
	lwz r0, 0x1cc4(r22)
	rlwinm. r0, r0, 0, 29, 29
	beq @24
	li r3, 0x4
	bl irand
	slwi r0, r3, 2
	la r3, _button_table(r13)
	lwzx r3, r3, r0
	add r4, r29, r26
	li r0, 0x0
	stw r3, 0x8(r4)
	stw r0, 0x3c(r4)
	b @22
	@24:
	li r20, 0x0
	la r21, _button_table(r13)
	b @25
	@26:
	li r3, 0x4
	bl irand
	subic. r4, r30, 0x1
	slwi r3, r3, 2
	lwzx r24, r21, r3
	li r5, 0x1
	addi r0, r4, 0x1
	slwi r3, r4, 2
	mtctr r0
	blt @27
	@28:
	addi r0, r3, 0x8
	lwzx r0, r29, r0
	cmplw r0, r24
	bne @29
	li r5, 0x0
	@29:
	subi r4, r4, 0x1
	subi r3, r3, 0x4
	bdnz @28
	@27:
	cmpwi r5, 0x0
	beq @25
	li r20, 0x1
	@25:
	cmpwi r20, 0x0
	beq @26
	add r3, r29, r26
	li r0, 0x0
	stw r24, 0x8(r3)
	stw r0, 0x3c(r3)
	b @22
	@20:
	li r20, 0x0
	la r21, _button_table(r13)
	b @30
	@31:
	li r3, 0x7
	bl irand
	subic. r4, r30, 0x1
	slwi r3, r3, 2
	lwzx r23, r21, r3
	li r5, 0x1
	addi r0, r4, 0x1
	slwi r3, r4, 2
	mtctr r0
	blt @32
	@33:
	addi r0, r3, 0x8
	lwzx r0, r29, r0
	cmplw r0, r23
	bne @34
	li r5, 0x0
	@34:
	subi r4, r4, 0x1
	subi r3, r3, 0x4
	bdnz @33
	@32:
	cmpwi r5, 0x0
	beq @30
	li r20, 0x1
	@30:
	cmpwi r20, 0x0
	beq @31
	add r3, r29, r26
	li r0, 0x0
	stw r23, 0x8(r3)
	stw r0, 0x3c(r3)
	@22:
	addi r30, r30, 0x1
	addi r26, r26, 0x4
	@15:
	lwz r0, 0x1cd0(r22)
	cmpw r30, r0
	blt @16
	li r0, 0x63
	stw r0, 0x1c9c(r22)
	b @5
	@8:
	li r3, 0x3e8
	li r0, 0x0
	stw r3, 0x1c9c(r22)
	stw r0, 0x4(r29)
	lwz r0, 0x1cc8(r22)
	stw r0, 0x0(r29)
	@3:
	lwz r4, 0x1c94(r22)
	clrlwi. r0, r4, 31
	beq @35
	lwz r3, 0x1c90(r22)
	lwz r0, 0x278(r3)
	rlwinm. r0, r0, 0, 27, 27
	beq @35
	rlwinm. r0, r4, 0, 30, 30
	beq @36
	lwz r3, 0x1c98(r22)
	subi r0, r3, 0x1
	stw r0, 0x1c98(r22)
	lwz r0, 0x1c98(r22)
	cmpwi r0, 0x0
	bge @5
	@36:
	li r3, 0x64
	bl irand
	cmpwi r3, 0x0
	blt @37
	li r0, 0x0
	stw r0, 0x1cb8(r22)
	b @38
	@37:
	li r0, 0x2
	stw r0, 0x1cb8(r22)
	lwz r3, 0x1cb4(r22)
	addi r0, r3, 0x1
	stw r0, 0x1cb4(r22)
	@38:
	li r3, 0x0
	b @39
	@35:
	lha r3, 0x1d18(r22)
	cmpwi r3, 0x0
	ble @40
	subi r0, r3, 0x1
	li r3, 0x2
	sth r0, 0x1d18(r22)
	li r0, 0x3e9
	li r27, 0x1
	stw r3, 0x1cb8(r22)
	stw r0, 0x1c9c(r22)
	b @5
	@40:
	li r30, 0x0
	li r26, 0x1
	stw r30, 0x1ce8(r22)
	mr r21, r30
	b @41
	@42:
	add r20, r29, r21
	lwz r0, 0x8(r20)
	cmplwi r0, 0x0
	beq @43
	lwz r0, 0x3c(r20)
	cmpwi r0, 0x0
	beq @44
	lwz r3, 0x1ce8(r22)
	addi r0, r3, 0x1
	stw r0, 0x1ce8(r22)
	b @43
	@44:
	bl BattlePadGetTrigger
	lwz r0, 0x8(r20)
	cmplw r0, r3
	beq @45
	cmpwi r25, 0x0
	beq @46
	@45:
	li r0, 0x1
	stw r0, 0x3c(r20)
	lwz r3, 0x1ce8(r22)
	addi r0, r3, 0x1
	stw r0, 0x1ce8(r22)
	lwz r0, 0x1ccc(r22)
	cmpwi r0, 0x1
	bne @43
	lwz r0, 0x1cd0(r22)
	addi r3, r30, 0x1
	cmpw r3, r0
	bge @47
	li r26, 0x0
	b @47
	@46:
	bl BattlePadGetTrigger
	cmplwi r3, 0x0
	beq @48
	li r0, 0x0
	li r3, 0x3e9
	stw r0, 0x1cb8(r22)
	stw r3, 0x1c9c(r22)
	lwz r0, 0x1cc4(r22)
	rlwinm. r0, r0, 0, 30, 30
	beq @49
	lwz r0, 0x1ce8(r22)
	cmpwi r0, 0x0
	ble @49
	lwz r0, 0x1cb8(r22)
	li r27, 0x1
	ori r0, r0, 0x2
	stw r0, 0x1cb8(r22)
	lwz r0, 0x1cb8(r22)
	clrrwi r0, r0, 1
	stw r0, 0x1cb8(r22)
	stw r3, 0x1c9c(r22)
	b @47
	@49:
	li r3, 0x1
	b @39
	@48:
	lwz r0, 0x1ccc(r22)
	li r26, 0x0
	cmpwi r0, 0x1
	beq @47
	@43:
	addi r30, r30, 0x1
	addi r21, r21, 0x4
	@41:
	lwz r0, 0x1cd0(r22)
	cmpw r30, r0
	blt @42
	@47:
	lwz r3, 0x4(r29)
	lwz r0, 0x1ce8(r22)
	cmpw r3, r0
	beq @50
	mr r3, r31
	bl psndSFXOn
	lwz r0, 0x1ce8(r22)
	stw r0, 0x4(r29)
	@50:
	cmpwi r26, 0x0
	beq @51
	lwz r3, 0x1cb8(r22)
	li r0, 0x3e9
	li r27, 0x1
	ori r3, r3, 0x2
	stw r3, 0x1cb8(r22)
	lwz r3, 0x1cb8(r22)
	clrrwi r3, r3, 1
	stw r3, 0x1cb8(r22)
	stw r0, 0x1c9c(r22)
	b @5
	@51:
	lwz r3, 0x0(r29)
	subi r0, r3, 0x1
	stw r0, 0x0(r29)
	lwz r0, 0x0(r29)
	cmpwi r0, 0x0
	bge @5
	li r0, 0x0
	li r3, 0x3e9
	stw r0, 0x1cb8(r22)
	li r27, 0x1
	stw r3, 0x1c9c(r22)
	lwz r0, 0x1cc4(r22)
	rlwinm. r0, r0, 0, 30, 30
	beq @5
	lwz r0, 0x1ce8(r22)
	cmpwi r0, 0x0
	ble @5
	lwz r0, 0x1cb8(r22)
	ori r0, r0, 0x2
	stw r0, 0x1cb8(r22)
	lwz r0, 0x1cb8(r22)
	clrrwi r0, r0, 1
	stw r0, 0x1cb8(r22)
	stw r3, 0x1c9c(r22)
	b @5
	@13:
	li r0, 0x3ea
	stw r0, 0x1c9c(r22)
	@11:
	li r3, 0x0
	b @39
	@12:
	li r3, 0x3c
	li r0, 0x3ec
	stw r3, 0x70(r29)
	stw r0, 0x1c9c(r22)
	b @5
	@9:
	lwz r3, 0x70(r29)
	subi r0, r3, 0x1
	stw r0, 0x70(r29)
	lwz r0, 0x70(r29)
	cmpwi r0, 0x0
	bgt @5
	li r0, 0x3ed
	stw r0, 0x1c9c(r22)
	b @5
	@14:
	li r0, 0x0
	stw r0, 0x1ca0(r22)
	stw r0, 0x1ca8(r22)
	stw r0, 0x1ca4(r22)
	stw r0, 0x1cac(r22)
	@5:
	cmpwi r27, 0x0
	bne @2
	li r3, 0x1
	@39:
	lmw r20, 0x10(r1)
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_8041406C_sdata[1] = {0};
__declspec(section ".sdata2") const u32 gap_09_80420504_sdata2[1] = {0};
#pragma force_active reset
