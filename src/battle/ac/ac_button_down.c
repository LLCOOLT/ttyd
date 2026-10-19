#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/icondrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#ifdef NONMATCHING
#define EXT_LIT(sym, val) (val)
#else
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802fd5d0[3];
__declspec(section ".rodata") extern const f32 vec3_802fd5dc[3];
__declspec(section ".rodata") extern const f32 vec3_802fd5e8[3];
__declspec(section ".rodata") extern const f32 vec3_802fd5f4[3];
__declspec(section ".rodata") extern const f32 vec3_802fd600[3];
__declspec(section ".rodata") extern const u32 gap_04_802FD60C_rodata;
__declspec(section ".rodata") extern const f64 double_to_int_802fd610;
__declspec(section ".rodata") extern const char str_802FD618[20];
__declspec(section ".rodata") extern const u32 gap_04_802FD62C_rodata;
__declspec(section ".sdata2") extern const f32 float_neg200_804204e8;
__declspec(section ".sdata2") extern const f32 float_40_804204ec;
__declspec(section ".sdata2") extern const f32 float_70_804204f0;
__declspec(section ".sdata2") extern const f32 float_1_804204f4;
__declspec(section ".sdata2") extern const f32 float_16_804204f8;
__declspec(section ".sdata2") extern const f32 float_neg300_804204fc;
__declspec(section ".sdata2") extern const f32 float_0_80420500;
#endif

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

void *memset(void *dest, int ch, size_t count);
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
        ((f32 *) disp)[5] = EXT_LIT(float_neg300_804204fc, -300.0f);
        ((f32 *) disp)[6] = EXT_LIT(float_0_80420500, 0.0f);
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
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
s32 battleAcMain_ButtonDown(BattleWork *work) {
	asm volatile {
		opword 0x7C761B78
		opword 0x3B200000
		opword 0x3BB61F4C
		opword 0x3B961F20
		opword 0x80631C90
		opword 0x88030303
		opword 0x28000000
		opword 0x41820008
		opword 0x3B200001
		lis r3, str_802FD618@ha
		addi r31, r3, str_802FD618@l
		opword 0x80161C9C
		opword 0x3B600000
		opword 0x2C0003E8
		opword 0x4182028C
		opword 0x40800028
		opword 0x2C000063
		opword 0x41820544
		opword 0x40800010
		opword 0x2C000000
		opword 0x4182003C
		opword 0x48000534
		opword 0x2C000065
		opword 0x4080052C
		opword 0x4800024C
		opword 0x2C0003EC
		opword 0x418204E8
		opword 0x40800014
		opword 0x2C0003EA
		opword 0x418204C0
		opword 0x408004C4
		opword 0x480004B0
		opword 0x2C0003EE
		opword 0x40800504
		opword 0x480004EC
		opword 0x38000001
		opword 0x7F83E378
		opword 0x90161CB8
		opword 0x38800000
		opword 0x38A0002C
		bl memset
		lfs f1, float_neg300_804204fc(r2)
		opword 0x38000014
		lfs f0, float_0_80420500(r2)
		opword 0x387D0008
		opword 0xD03C0014
		opword 0x38800000
		opword 0x38A00034
		opword 0xD01C0018
		opword 0x901C0020
		bl memset
		opword 0x387D003C
		opword 0x38800001
		opword 0x38A00034
		bl memset
		opword 0x3BC00000
		opword 0x3B400000
		opword 0x480001B0
		opword 0x80161CD4
		opword 0x2C00FFFD
		opword 0x41820074
		opword 0x40800010
		opword 0x2C00FFFC
		opword 0x4080003C
		opword 0x48000114
		opword 0x2C00FFFF
		opword 0x4080010C
		opword 0x38600064
		bl irand
		opword 0x2C030032
		opword 0x38600200
		opword 0x40800008
		opword 0x38600100
		opword 0x7C9DD214
		opword 0x38000000
		opword 0x90640008
		opword 0x9004003C
		opword 0x48000158
		opword 0x38600064
		bl irand
		opword 0x2C030032
		opword 0x38600400
		opword 0x40800008
		opword 0x38600200
		opword 0x7C9DD214
		opword 0x38000000
		opword 0x90640008
		opword 0x9004003C
		opword 0x4800012C
		opword 0x80161CC4
		opword 0x5400077B
		opword 0x4182002C
		opword 0x38600004
		bl irand
		opword 0x5460103A
		la r3, _button_table(r13)
		opword 0x7C63002E
		opword 0x7C9DD214
		opword 0x38000000
		opword 0x90640008
		opword 0x9004003C
		opword 0x480000F8
		li r20, 0x0
		la r21, _button_table(r13)
		opword 0x48000058
		opword 0x38600004
		bl irand
		opword 0x349EFFFF
		opword 0x5463103A
		opword 0x7F15182E
		opword 0x38A00001
		opword 0x38040001
		opword 0x5483103A
		opword 0x7C0903A6
		opword 0x41800024
		opword 0x38030008
		opword 0x7C1D002E
		opword 0x7C00C040
		opword 0x40820008
		opword 0x38A00000
		opword 0x3884FFFF
		opword 0x3863FFFC
		opword 0x4200FFE4
		opword 0x2C050000
		opword 0x41820008
		opword 0x3A800001
		opword 0x2C140000
		opword 0x4182FFA8
		opword 0x7C7DD214
		opword 0x38000000
		opword 0x93030008
		opword 0x9003003C
		opword 0x4800007C
		opword 0x3A800000
		la r21, _button_table(r13)
		opword 0x48000058
		opword 0x38600007
		bl irand
		opword 0x349EFFFF
		opword 0x5463103A
		opword 0x7EF5182E
		opword 0x38A00001
		opword 0x38040001
		opword 0x5483103A
		opword 0x7C0903A6
		opword 0x41800024
		opword 0x38030008
		opword 0x7C1D002E
		opword 0x7C00B840
		opword 0x40820008
		opword 0x38A00000
		opword 0x3884FFFF
		opword 0x3863FFFC
		opword 0x4200FFE4
		opword 0x2C050000
		opword 0x41820008
		opword 0x3A800001
		opword 0x2C140000
		opword 0x4182FFA8
		opword 0x7C7DD214
		opword 0x38000000
		opword 0x92E30008
		opword 0x9003003C
		opword 0x3BDE0001
		opword 0x3B5A0004
		opword 0x80161CD0
		opword 0x7C1E0000
		opword 0x4180FE4C
		opword 0x38000063
		opword 0x90161C9C
		opword 0x480002E0
		opword 0x386003E8
		opword 0x38000000
		opword 0x90761C9C
		opword 0x901D0004
		opword 0x80161CC8
		opword 0x901D0000
		opword 0x80961C94
		opword 0x548007FF
		opword 0x4182006C
		opword 0x80761C90
		opword 0x80030278
		opword 0x540006F7
		opword 0x4182005C
		opword 0x548007BD
		opword 0x4182001C
		opword 0x80761C98
		opword 0x3803FFFF
		opword 0x90161C98
		opword 0x80161C98
		opword 0x2C000000
		opword 0x4080028C
		opword 0x38600064
		bl irand
		opword 0x2C030000
		opword 0x41800010
		opword 0x38000000
		opword 0x90161CB8
		opword 0x48000018
		opword 0x38000002
		opword 0x90161CB8
		opword 0x80761CB4
		opword 0x38030001
		opword 0x90161CB4
		opword 0x38600000
		opword 0x48000260
		opword 0xA8761D18
		opword 0x2C030000
		opword 0x40810024
		opword 0x3803FFFF
		opword 0x38600002
		opword 0xB0161D18
		opword 0x380003E9
		opword 0x3B600001
		opword 0x90761CB8
		opword 0x90161C9C
		opword 0x48000228
		opword 0x3BC00000
		opword 0x3B400001
		opword 0x93D61CE8
		opword 0x7FD5F378
		opword 0x480000F8
		opword 0x7E9DAA14
		opword 0x80140008
		opword 0x28000000
		opword 0x418200E0
		opword 0x8014003C
		opword 0x2C000000
		opword 0x41820014
		opword 0x80761CE8
		opword 0x38030001
		opword 0x90161CE8
		opword 0x480000C4
		bl BattlePadGetTrigger
		opword 0x80140008
		opword 0x7C001840
		opword 0x4182000C
		opword 0x2C190000
		opword 0x4182003C
		opword 0x38000001
		opword 0x9014003C
		opword 0x80761CE8
		opword 0x38030001
		opword 0x90161CE8
		opword 0x80161CCC
		opword 0x2C000001
		opword 0x4082008C
		opword 0x80161CD0
		opword 0x387E0001
		opword 0x7C030000
		opword 0x40800090
		opword 0x3B400000
		opword 0x48000088
		bl BattlePadGetTrigger
		opword 0x28030000
		opword 0x41820058
		opword 0x38000000
		opword 0x386003E9
		opword 0x90161CB8
		opword 0x90761C9C
		opword 0x80161CC4
		opword 0x540007BD
		opword 0x41820034
		opword 0x80161CE8
		opword 0x2C000000
		opword 0x40810028
		opword 0x80161CB8
		opword 0x3B600001
		opword 0x60000002
		opword 0x90161CB8
		opword 0x80161CB8
		opword 0x5400003C
		opword 0x90161CB8
		opword 0x90761C9C
		opword 0x48000030
		opword 0x38600001
		opword 0x48000144
		opword 0x80161CCC
		opword 0x3B400000
		opword 0x2C000001
		opword 0x41820018
		opword 0x3BDE0001
		opword 0x3AB50004
		opword 0x80161CD0
		opword 0x7C1E0000
		opword 0x4180FF04
		opword 0x807D0004
		opword 0x80161CE8
		opword 0x7C030000
		opword 0x41820014
		opword 0x7FE3FB78
		bl psndSFXOn
		opword 0x80161CE8
		opword 0x901D0004
		opword 0x2C1A0000
		opword 0x4182002C
		opword 0x80761CB8
		opword 0x380003E9
		opword 0x3B600001
		opword 0x60630002
		opword 0x90761CB8
		opword 0x80761CB8
		opword 0x5463003C
		opword 0x90761CB8
		opword 0x90161C9C
		opword 0x480000C4
		opword 0x807D0000
		opword 0x3803FFFF
		opword 0x901D0000
		opword 0x801D0000
		opword 0x2C000000
		opword 0x408000AC
		opword 0x38000000
		opword 0x386003E9
		opword 0x90161CB8
		opword 0x3B600001
		opword 0x90761C9C
		opword 0x80161CC4
		opword 0x540007BD
		opword 0x4182008C
		opword 0x80161CE8
		opword 0x2C000000
		opword 0x40810080
		opword 0x80161CB8
		opword 0x60000002
		opword 0x90161CB8
		opword 0x80161CB8
		opword 0x5400003C
		opword 0x90161CB8
		opword 0x90761C9C
		opword 0x48000060
		opword 0x380003EA
		opword 0x90161C9C
		opword 0x38600000
		opword 0x4800005C
		opword 0x3860003C
		opword 0x380003EC
		opword 0x907D0070
		opword 0x90161C9C
		opword 0x4800003C
		opword 0x807D0070
		opword 0x3803FFFF
		opword 0x901D0070
		opword 0x801D0070
		opword 0x2C000000
		opword 0x41810024
		opword 0x380003ED
		opword 0x90161C9C
		opword 0x48000018
		opword 0x38000000
		opword 0x90161CA0
		opword 0x90161CA8
		opword 0x90161CA4
		opword 0x90161CAC
		opword 0x2C1B0000
		opword 0x4082FAA0
		opword 0x38600001
	}
}
#pragma pop
#endif

s32 battleAcResult_ButtonDown(BattleWork* work) {
    return work->actionCommands.result;
}

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
            x = intplGetValue(4, 20 - disp[8], 20, EXT_LIT(float_neg300_804204fc, -300.0f), EXT_LIT(float_0_80420500, 0.0f));
            y = EXT_LIT(float_0_80420500, 0.0f);
            break;
        default:
            x = y = EXT_LIT(float_0_80420500, 0.0f);
            break;
    }
    actionCommandDisp(0, x, y);
}

void battleAcDelete_ButtonDown(BattleWork* work) {
    work->actionCommands.mAcState = 1003;
}

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
  f32 bx = (EXT_LIT(float_neg200_804204e8, -200.0f)) + x;
  f32 by;
  f32 lx = bx - 40.0f;
  Vec pos = {0.0f, 0.0f, -2.0f};
  by = EXT_LIT(float_70_804204f0, 70.0f) + y;
  pos.x = lx;
  pos.y = by;
  iconDispGx(&pos, 16, 0x8f, EXT_LIT(float_1_804204f4, 1.0f));
  lx += EXT_LIT(float_16_804204f8, 16.0f);
  for (k = 1; k < end; k++)
  {
    Vec pos2 = {0.0f, 0.0f, -2.0f};
    pos2.x = lx;
    pos2.y = by;
    size = 16;
    iconDispGx(&pos2, size, 0x8e, EXT_LIT(float_1_804204f4, 1.0f));
    lx += EXT_LIT(float_16_804204f8, 16.0f);
  }

  {
    Vec pos3 = {0.0f, 0.0f, -2.0f};
    pos3.x = lx;
    pos3.y = by;
    iconDispGx(&pos3, 16, 0x90, EXT_LIT(float_1_804204f4, 1.0f));
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
      ((void (*)(Vec *, s32, s32, f32)) iconDispGx)(&pos4, size, a, EXT_LIT(float_1_804204f4, 1.0f));
    }
    else
    {
      Vec pos5 = {0.0f, 0.0f, 0.0f};
      pos5.x = bx + ((f32) off);
      pos5.y = by;
      ((void (*)(Vec *, s32, s32, f32)) iconDispGx)(&pos5, size, b, EXT_LIT(float_1_804204f4, 1.0f));
    }
  }

}
#else
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
static void actionCommandDisp(s32 unused, f32 x, f32 y) {
	char _af_pad[72];
	asm volatile {
		lfs f0, float_neg200_804204e8(r2)
		lis r3, vec3_802fd5d0@ha
		addi r31, r3, vec3_802fd5d0@l
		lwz r26, _battleWorkPointer(r13)
		opword 0xEFC0082A
		lfs f1, float_40_804204ec(r2)
		lfs f0, float_70_804204f0(r2)
		opword 0x3BDA1F4C
		opword 0x809A1CD0
		la r3, _af_pad+48
		opword 0x801F0000
		opword 0x1CA40003
		opword 0x809F0004
		fsubs f28, f30, f1
		opword 0x90010038
		opword 0xEFA0102A
		opword 0x801F0008
		opword 0x9081003C
		opword 0x3B850002
		lfs f1, float_1_804204f4(r2)
		opword 0x38800010
		opword 0x90010040
		opword 0x38A0008F
		opword 0xD3810038
		opword 0xD3A1003C
		bl iconDispGx
		lfs f31, float_16_804204f8(r2)
		opword 0x3B600001
		opword 0xEF9CF82A
		opword 0x48000040
		opword 0x801F000C
		opword 0x3861002C
		opword 0x80DF0010
		opword 0x38800010
		opword 0x9001002C
		opword 0x38A0008E
		opword 0x801F0014
		opword 0x90C10030
		lfs f1, float_1_804204f4(r2)
		opword 0x90010034
		opword 0xD381002C
		opword 0xD3A10030
		bl iconDispGx
		opword 0xEF9CF82A
		opword 0x3B7B0001
		opword 0x7C1BE000
		opword 0x4180FFC0
		opword 0x801F0018
		opword 0x38610020
		opword 0x80DF001C
		opword 0x38800010
		opword 0x90010020
		opword 0x38A00090
		opword 0x801F0020
		opword 0x90C10024
		lfs f1, float_1_804204f4(r2)
		opword 0x90010028
		opword 0xD3810020
		opword 0xD3A10024
		bl iconDispGx
		opword 0x801A1CC4
		opword 0x540007FF
		opword 0x41820048
		opword 0x809A1CD0
		opword 0x3B800000
		opword 0x38600000
		opword 0x7C8903A6
		opword 0x2C040000
		opword 0x40810020
		opword 0x3803003C
		opword 0x7C1E002E
		opword 0x2C000000
		opword 0x41820010
		opword 0x3B9C0001
		opword 0x38630004
		opword 0x4200FFE8
		opword 0x7C1C2000
		opword 0x40800010
		opword 0x3B9C0001
		opword 0x48000008
		opword 0x839A1CD0
		opword 0x3BA00000
		opword 0x3B600000
		opword 0x3B400000
		opword 0x48000194
		opword 0x7C9ED214
		opword 0x80640008
		opword 0x28030000
		opword 0x41820178
		opword 0x2C030200
		opword 0x4182006C
		opword 0x40800034
		opword 0x2C030040
		opword 0x41820084
		opword 0x4080001C
		opword 0x2C030020
		opword 0x41820084
		opword 0x40800098
		opword 0x2C030010
		opword 0x41820084
		opword 0x4800008C
		opword 0x2C030100
		opword 0x41820030
		opword 0x48000080
		opword 0x2C030800
		opword 0x41820048
		opword 0x40800010
		opword 0x2C030400
		opword 0x41820030
		opword 0x48000068
		opword 0x3C000004
		opword 0x7C030000
		opword 0x4182005C
		opword 0x48000058
		opword 0x38A00065
		opword 0x38C00064
		opword 0x48000054
		opword 0x38A00067
		opword 0x38C00066
		opword 0x48000048
		opword 0x38A00069
		opword 0x38C00068
		opword 0x4800003C
		opword 0x38A0006B
		opword 0x38C0006A
		opword 0x48000030
		opword 0x38A0007F
		opword 0x38C0007E
		opword 0x48000024
		opword 0x38A00081
		opword 0x38C00080
		opword 0x48000018
		opword 0x38A00083
		opword 0x38C00082
		opword 0x4800000C
		opword 0x38A00078
		opword 0x38C00079
		opword 0x8004003C
		opword 0x2C000000
		opword 0x41820058
		opword 0x6F638000
		opword 0x3C004330
		opword 0x9061004C
		opword 0x38610014
		opword 0x80FF0024
		opword 0x38800010
		opword 0x90010048
		opword 0xC83F0040
		opword 0xC8010048
		opword 0x80DF0028
		opword 0xEC000828
		opword 0x801F002C
		opword 0x90C10018
		lfs f1, float_1_804204f4(r2)
		opword 0xEC1E002A
		opword 0x90E10014
		opword 0x9001001C
		opword 0xD0010014
		opword 0xD3A10018
		bl iconDispGx
		opword 0x48000058
		opword 0x6F638000
		opword 0x3C004330
		opword 0x9061004C
		opword 0x7CC53378
		opword 0x80FF0030
		opword 0x38610008
		opword 0x90010048
		opword 0x38800010
		opword 0xC83F0040
		opword 0xC8010048
		opword 0x80DF0034
		opword 0xEC000828
		opword 0x801F0038
		opword 0x90C1000C
		lfs f1, float_1_804204f4(r2)
		opword 0xEC1E002A
		opword 0x90E10008
		opword 0x90010010
		opword 0xD0010008
		opword 0xD3A1000C
		bl iconDispGx
		opword 0x3BBD0001
		opword 0x3B7B0030
		opword 0x3B5A0004
		opword 0x7C1DE000
		opword 0x4180FE6C
	}
}
#pragma pop
#endif


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".sdata") u32 gap_07_8041406C_sdata[1] = {0};
#pragma force_active reset

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fd5d0[3] = {0.0f, 0.0f, -2.0f};
__declspec(section ".rodata") const f32 vec3_802fd5dc[3] = {0.0f, 0.0f, -2.0f};
__declspec(section ".rodata") const f32 vec3_802fd5e8[3] = {0.0f, 0.0f, -2.0f};
__declspec(section ".rodata") const f32 vec3_802fd5f4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fd600[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const u32 gap_04_802FD60C_rodata = 0x00000000;
__declspec(section ".rodata") const f64 double_to_int_802fd610 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802FD618[20] = "SFX_AC_BUTTON_PUSH1";
__declspec(section ".rodata") const u32 gap_04_802FD62C_rodata = 0x00000000;
__declspec(section ".sdata2") const f32 float_neg200_804204e8 = -200.0f;
__declspec(section ".sdata2") const f32 float_40_804204ec = 40.0f;
__declspec(section ".sdata2") const f32 float_70_804204f0 = 70.0f;
__declspec(section ".sdata2") const f32 float_1_804204f4 = 1.0f;
__declspec(section ".sdata2") const f32 float_16_804204f8 = 16.0f;
__declspec(section ".sdata2") const f32 float_neg300_804204fc = -300.0f;
__declspec(section ".sdata2") const f32 float_0_80420500 = 0.0f;
__declspec(section ".sdata2") const u32 gap_09_80420504_sdata2[1] = {0};
#endif
