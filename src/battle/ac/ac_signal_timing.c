#pragma optimize_for_size on
#include "battle/battle.h"
#include "battle/battle_ac.h"
#include "battle/battle_pad.h"
#include "battle/battle_unit.h"
#include "driver/camdrv.h"
#include "driver/icondrv.h"
#include "pmario_sound.h"
#include "system.h"
#include <string.h>
#ifndef NONMATCHING
#define EXT_LIT(sym, val) (sym)
__declspec(section ".rodata") extern const f32 vec3_802fedc8[3];
__declspec(section ".rodata") extern const f32 vec3_802fedd4[3];
__declspec(section ".rodata") extern const f32 vec3_802fede0[3];
__declspec(section ".rodata") extern const f32 vec3_802fedec[3];
__declspec(section ".rodata") extern const f32 vec3_802fedf8[3];
__declspec(section ".rodata") extern const f32 vec3_802fee04[3];
__declspec(section ".rodata") extern const f32 vec3_802fee10[3];
__declspec(section ".rodata") extern const f32 vec3_802fee1c[3];
__declspec(section ".rodata") extern const f32 vec3_802fee28[3];
__declspec(section ".rodata") extern const f32 vec3_802fee34[3];
__declspec(section ".rodata") extern const f32 vec3_802fee40[3];
__declspec(section ".rodata") extern const f32 vec3_802fee4c[3];
__declspec(section ".rodata") extern const f32 vec3_802fee58[3];
__declspec(section ".rodata") extern const f32 vec3_802fee64[3];
__declspec(section ".rodata") extern const f64 double_to_int_802fee70;
__declspec(section ".rodata") extern const char str_802FEE78[12];
__declspec(section ".rodata") extern const char str_802FEE84[16];
__declspec(section ".rodata") extern const char str_802FEE94[20];
__declspec(section ".rodata") extern const char str_802FEEA8[20];
__declspec(section ".sdata2") extern const u32 dat_804216d0;
__declspec(section ".sdata2") extern const u32 dat_804216d4;
__declspec(section ".sdata2") extern const u32 dat_804216d8;
__declspec(section ".sdata2") extern const u32 dat_804216dc;
__declspec(section ".sdata2") extern const f32 float_neg200_804216e0;
__declspec(section ".sdata2") extern const f32 float_70_804216e4;
__declspec(section ".sdata2") extern const f32 float_1_804216e8;
__declspec(section ".sdata2") extern const f32 float_neg288_804216ec;
__declspec(section ".sdata2") extern const f32 float_25_804216f0;
__declspec(section ".sdata2") extern const f32 float_0_804216f4;
__declspec(section ".sdata2") extern const f32 float_1p5_804216f8;
__declspec(section ".sdata2") extern const f32 float_0p5_804216fc;
__declspec(section ".sdata2") extern const f32 float_15_80421700;
__declspec(section ".sdata2") extern const f32 float_0p8_80421704;
__declspec(section ".sdata2") extern const f32 float_0p6_80421708;
__declspec(section ".sdata2") extern const f32 float_20p8_8042170c;
__declspec(section ".sdata2") extern const f32 float_neg300_80421710;
__declspec(section ".sdata2") extern const f32 float_30_80421714;
#endif

u16 BattleACGetButtonIcon(s32 button, s32 pressed);
void btlDispTexPlane(u32 id, GXColor color, s32 unk, f32 tX, f32 tY, f32 tZ, f32 sX, f32 sY);

typedef struct SignalTimingWork {
    s32 hits;       // 0x0
    s32 misses;     // 0x4
    s32 index;      // 0x8
    s32 next;       // 0xC
    s32 frame;      // 0x10
    s32 rangeStart; // 0x14
    s32 rangeEnd;   // 0x18
    s32 okStart;    // 0x1C
    s32 okEnd;      // 0x20
    s32 pressed;    // 0x24
    s32 unk28;      // 0x28
    s32 difficulty; // 0x2C
    s32 okFlag;     // 0x30
    u32 button;     // 0x34
    u32 buttons[5]; // 0x38
    s8 results[8];  // 0x4C
    s32 endTimer;   // 0x54
} SignalTimingWork;

#define ST_FIELD30(w) ((w)->actionCommands.field_0x30)
#define ST_FLAGS(w) ((w)->actionCommands.acFlags)
#define ST_COUNT(w) ((w)->actionCommands.params[0])    /* number of signals */
#define ST_MODE(w) ((w)->actionCommands.params[1])     /* 1: use the wider ok-frame table */
#define ST_STEP(w) ((w)->actionCommands.params[2])     /* frames per signal */
#define ST_NEEDED(w) ((w)->actionCommands.params[3])   /* hits needed for success */
#define ST_BUTTONS(w) ((w)->actionCommands.params[4])  /* 1: d-pad directions, 2: A/B/X/Y */
#define ST_EXTRA(w) ((w)->actionCommands.params[5])    /* added to hits for the displayed count */
#define ST_LEAD(w) ((w)->actionCommands.params[6])     /* lead-in signals before the first button */
#define ST_OKBASE(w) ((w)->actionCommands.params[7])   /* base ok frame range */
#define ST_OUT_HITS(w) ((w)->actionCommands.outputParams[0])
#define ST_OUT_RESULT(w) ((w)->actionCommands.outputParams[1])
#define ST_COUNTDOWN(w) ((w)->actionCommands.countdown)
#define ST_CONF(work) ((work->actionCommands.setupFlags & 1) && (work->actionCommands.mAcUnit->mTokenFlags & kConfusedAction))

#ifdef NONMATCHING
u32 _button_table_4dir[4] = {0x10000, 0x20000, 0x40000, 0x80000};
u32 _button_table_abxy[4] = {0x100, 0x200, 0x400, 0x800};
#endif
#ifndef NONMATCHING
__declspec(section ".sdata") u32 _button_table_4dir[4] = {0x10000, 0x20000, 0x40000, 0x80000};
__declspec(section ".sdata") u32 _button_table_abxy[4] = {0x100, 0x200, 0x400, 0x800};
#endif
s32 ac_signaltiming_ok_frame_range[7] = {20, 16, 12, 10, 6, 4, 2};
s32 ac_signaltiming_ok_frame_range_2[7] = {30, 30, 30, 30, 25, 20, 15};

static void actionCommandDisp(f32 x, f32 y);
s32 _get_ok_frame_range(s32 difficulty);

#pragma dont_inline on
s32 _get_ok_frame_range(s32 difficulty) {
    BattleWork* work = _battleWorkPointer;
    switch (ST_MODE(work)) {
        case 1:
            return ST_OKBASE(work) + ac_signaltiming_ok_frame_range_2[difficulty];
    }
    return ST_OKBASE(work) + ac_signaltiming_ok_frame_range[difficulty];
}

#pragma dont_inline reset
#ifdef NONMATCHING
s32 battleAcMain_SignalTiming(BattleWork *work)
{
  const char *sfxPi;
  const char *sfxPone;
  const char *sfxOk;
  const char *sfxNg;
  s32 j;
  s32 i;
  s32 k;
  BOOL unique;
  BattleActions *ac = &work->actionCommands;
  SignalTimingWork *w = (SignalTimingWork *) (((u8 *) ac) + 0x2BC);
  BattleACDispParams *disp = (BattleACDispParams *) (((u8 *) ac) + 0x290);
  BOOL loop;
  BOOL autoCommand = 0;
  BOOL got;
  BOOL good;
  u32 btn;
  BOOL done;
  if (ac->mAcUnit->badgesEquipped.AutoCommand)
  {
    autoCommand = 1;
  }
  sfxPi = "SFX_AC_PI1";
  sfxPone = "SFX_AC_PONE1";
  sfxOk = "SFX_AC_COMMAND_OK1";
  sfxNg = "SFX_AC_COMMAND_NG1";
  do
  {
    loop = 0;
    got = 0;
    switch (ac->mAcState)
    {
      case 0:
        ac->result = 1;
        memset(disp, 0, sizeof(BattleACDispParams));
        disp->iconX = -300.0f;
        disp->iconY = 0.0f;
        *((s32 *) (&disp->field_0x1C[4])) = 20;
        w->hits = 0;
        w->misses = 0;
        w->frame = 0;
        w->index = 0;
        w->next = 0;
        w->difficulty = ((s32 (*)(BattleWork *)) BattleActionCommandGetDifficulty)(work);
        w->okFlag = 0;
        ST_OUT_RESULT(work) = 0;
        for (k = 0; k < 5; k++)
      {
        w->results[k] = 0;
      }

        switch ST_BUTTONS(work)
      {
        case 1:

        case 2:
          for (i = 0; i < ST_COUNT(work); i++)
        {
          done = 0;
          while (!done)
          {
            if (ST_BUTTONS(work) == 1)
            {
              btn = _button_table_4dir[irand(4)];
            }
            else
            {
              btn = _button_table_abxy[irand(4)];
            }
            unique = 1;
            for (j = i - 1; j >= 0; j--)
            {
              if (w->buttons[j] == btn)
              {
                unique = 0;
              }
            }

            if (unique)
            {
              done = 1;
            }
          }

          w->buttons[i] = btn;
        }

          w->button = w->buttons[0];
          break;

        default:
          w->button = 0x100;
          for (i = 0; i < ST_COUNT(work); i++)
        {
          w->buttons[i] = 0x100;
        }

          w->button = w->buttons[0];

      }

        ac->mAcState = 99;
        break;

      case 99:
        break;

      case 100:
        if (ST_COUNTDOWN(work) > 0)
      {
        ST_COUNTDOWN(work)--;
        ac->result = 2;
        loop = 1;
        ac->mAcState = 1002;
        break;
      }
        w->rangeStart = w->index * ST_STEP(work);
        w->rangeEnd = ((w->index + 1) * ST_STEP(work)) - 1;
        w->okStart = w->rangeStart;
        j = _get_ok_frame_range(w->difficulty) - 1;
        w->okEnd = w->okStart + j;
        ac->mAcState = 1000;

      case 1000:
        w->unk28 = ((w->next + 1) * ST_STEP(work)) - 1;
        w->next++;
        if (w->next < (ST_LEAD(work) + 1))
      {
        if (!((work->actionCommands.setupFlags & 1) && (work->actionCommands.mAcUnit->mTokenFlags & kConfusedAction)))
        {
          psndSFXOn(sfxPi);
        }
      }
      else
        if (!((work->actionCommands.setupFlags & 1) && (work->actionCommands.mAcUnit->mTokenFlags & kConfusedAction)))
      {
        psndSFXOn(sfxPone);
      }
        w->pressed = 0;
        ac->mAcState = 1001;

      case 1001:
        w->frame++;
        if (w->pressed)
      {
        w->okFlag = 0;
      }
      else
        if (w->index >= ST_LEAD(work))
      {
        if ((w->frame >= w->okStart) && (w->frame <= w->okEnd))
        {
          w->okFlag = 1;
        }
        else
        {
          w->okFlag = 0;
        }
      }
      else
      {
        w->okFlag = 0;
      }
        good = 0;
        if (BattlePadCheckTrigger(w->button))
      {
        got = 1;
      }
        if (got)
      {
        switch ST_BUTTONS(work)
        {
          case 2:
            if (w->button == BattlePadGetTrigger())
          {
            good = 1;
          }
          else
          {
            good = 0;
          }
            break;

          default:
            good = 1;

        }

      }
        if (autoCommand && w->okFlag)
      {
        got = 1;
        good = 1;
      }
        if ((w->hits + w->misses) >= ST_COUNT(work))
      {
        got = 0;
      }
        if (((w->index >= ST_LEAD(work)) && got) && (!w->pressed))
      {
        w->pressed = 1;
        if (((w->frame >= w->okStart) && (w->frame <= w->okEnd)) && good)
        {
          w->hits++;
          ST_OUT_RESULT(work) = 1;
          if ((w->index >= ST_LEAD(work)) && (w->index < (ST_COUNT(work) + ST_LEAD(work))))
          {
            w->results[w->index - ST_LEAD(work)] = 1;
            if (!((work->actionCommands.setupFlags & 1) && (work->actionCommands.mAcUnit->mTokenFlags & kConfusedAction)))
            {
              psndSFXOn(sfxOk);
            }
          }
          if (ST_FLAGS(work) & 0x10)
          {
            ST_OUT_HITS(work) = w->hits;
            ac->result &= ~1;
            if (w->hits >= ST_NEEDED(work))
            {
              ac->result |= 2;
            }
            loop = 1;
            ac->mAcState = 1002;
          }
        }
        else
          if ((w->index >= ST_LEAD(work)) && (w->index < (ST_COUNT(work) + ST_LEAD(work))))
        {
          w->misses++;
          if (w->frame >= w->rangeStart)
          {
            w->results[w->index - ST_LEAD(work)] = -1;
            if (!((work->actionCommands.setupFlags & 1) && (work->actionCommands.mAcUnit->mTokenFlags & kConfusedAction)))
            {
              psndSFXOn(sfxNg);
            }
            ST_OUT_RESULT(work) = -1;
          }
          else
          {
            w->pressed = 0;
          }
        }
      }
        if ((!w->pressed) && (w->frame > w->okEnd))
      {
        w->pressed = 1;
        ST_OUT_RESULT(work) = -1;
        if ((w->index >= ST_LEAD(work)) && (w->index < (ST_COUNT(work) + ST_LEAD(work))))
        {
          w->misses++;
          w->results[w->index - ST_LEAD(work)] = -1;
          if (!((work->actionCommands.setupFlags & 1) && (work->actionCommands.mAcUnit->mTokenFlags & kConfusedAction)))
          {
            psndSFXOn(sfxNg);
          }
        }
      }
        if (w->pressed && (w->index < (ST_COUNT(work) + ST_LEAD(work))))
      {
        w->index++;
        if (w->index < (ST_COUNT(work) + ST_LEAD(work)))
        {
          w->rangeStart = (w->index * ST_STEP(work)) - 10;
          w->rangeEnd = ((w->index + 1) * ST_STEP(work)) - 1;
          w->okStart = w->index * ST_STEP(work);
          j = _get_ok_frame_range(w->difficulty) - 1;
          w->okEnd = w->okStart + j;
          w->pressed = 0;
          if ((w->index >= ST_LEAD(work)) && (w->index < (ST_COUNT(work) + ST_LEAD(work))))
          {
            w->button = w->buttons[w->index - ST_LEAD(work)];
          }
        }
      }
        if (w->frame >= (w->next * ST_STEP(work)))
      {
        if (w->next < (ST_COUNT(work) + ST_LEAD(work)))
        {
          ac->mAcState = 1000;
        }
        else
        {
          ST_OUT_HITS(work) = w->hits;
          ac->result &= ~1;
          if (w->hits >= ST_NEEDED(work))
          {
            ac->result |= 2;
          }
          loop = 1;
          ac->mAcState = 1002;
        }
      }
        break;

      case 1002:
        ac->mAcState = 1003;
        break;

      case 1003:
        break;

      case 1004:
        ST_FIELD30(work) |= 1;
        w->okFlag = 0;
        w->endTimer = 60;
        ac->mAcState = 1005;
        break;

      case 1005:
        w->endTimer--;
        if (w->endTimer <= 0)
      {
        ac->mAcState = 1006;
      }
        break;

      case 1006:
        ac->maincb = (void *) 0;
        ac->dispcb = (void *) 0;
        ac->resultcb = (void *) 0;
        ac->deletecb = (void *) 0;
        break;

    }

  }
  while (loop);
  return 1;
#endif
#ifndef NONMATCHING
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
void *memset(void *dest, int ch, size_t count);
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
s32 battleAcMain_SignalTiming(BattleWork *work) {
	asm volatile {
		opword 0x9421FFC0
		opword 0x7C0802A6
		lis r4, vec3_802fedc8@ha
		opword 0x90010044
		addi r4, r4, vec3_802fedc8@l
		opword 0xBE61000C
		opword 0x7C741B78
		opword 0x3B541F4C
		opword 0x3AE00000
		opword 0x3B341F20
		opword 0x80631C90
		opword 0x88030303
		opword 0x28000000
		opword 0x41820008
		opword 0x3AE00001
		opword 0x3B8400E0
		opword 0x3BE400B0
		opword 0x3BC400BC
		opword 0x3BA400CC
		opword 0x80141C9C
		opword 0x3B000000
		opword 0x3B600000
		opword 0x2C0003E9
		opword 0x41820308
		opword 0x40800030
		opword 0x2C000063
		opword 0x418207C4
		opword 0x40800010
		opword 0x2C000000
		opword 0x41820044
		opword 0x480007B4
		opword 0x2C0003E8
		opword 0x40800250
		opword 0x2C000065
		opword 0x408007A4
		opword 0x480001C8
		opword 0x2C0003ED
		opword 0x41820760
		opword 0x40800014
		opword 0x2C0003EB
		opword 0x4182078C
		opword 0x40800728
		opword 0x48000718
		opword 0x2C0003EF
		opword 0x4080077C
		opword 0x48000764
		opword 0x38000001
		opword 0x7F23CB78
		opword 0x90141CB8
		opword 0x38800000
		opword 0x38A0002C
		bl memset
		lfs f1, float_neg300_80421710(r2)
		opword 0x38800014
		lfs f0, float_0_804216f4(r2)
		opword 0x38000000
		opword 0xD0390014
		opword 0x7E83A378
		opword 0xD0190018
		opword 0x90990020
		opword 0x901A0000
		opword 0x901A0004
		opword 0x901A0010
		opword 0x901A0008
		opword 0x901A000C
		bl BattleActionCommandGetDifficulty
		opword 0x907A002C
		opword 0x38600000
		opword 0x38000005
		opword 0x38800000
		opword 0x907A0030
		opword 0x90741CEC
		opword 0x7C0903A6
		opword 0x3804004C
		opword 0x38840001
		opword 0x7C7A01AE
		opword 0x4200FFF4
		opword 0x80141CD8
		opword 0x2C000003
		opword 0x408000D4
		opword 0x2C000001
		opword 0x40800008
		opword 0x480000C8
		opword 0x3B600000
		opword 0x3A600000
		opword 0x480000A4
		opword 0x3AC00000
		opword 0x48000084
		opword 0x80141CD8
		opword 0x2C000001
		opword 0x4082001C
		opword 0x38600004
		bl irand
		opword 0x5460103A
		la r3, _button_table_4dir(r13)
		opword 0x7C03002E
		opword 0x48000018
		opword 0x38600004
		bl irand
		opword 0x5460103A
		la r3, _button_table_abxy(r13)
		opword 0x7C03002E
		opword 0x349BFFFF
		opword 0x7C150378
		opword 0x38A00001
		opword 0x38040001
		opword 0x5483103A
		opword 0x7C0903A6
		opword 0x41800024
		opword 0x38030038
		opword 0x7C1A002E
		opword 0x7C00A840
		opword 0x40820008
		opword 0x38A00000
		opword 0x3884FFFF
		opword 0x3863FFFC
		opword 0x4200FFE4
		opword 0x2C050000
		opword 0x41820008
		opword 0x3AC00001
		opword 0x2C160000
		opword 0x4182FF7C
		opword 0x38130038
		opword 0x3A730004
		opword 0x7EBA012E
		opword 0x3B7B0001
		opword 0x80141CC8
		opword 0x7C1B0000
		opword 0x4180FF58
		opword 0x801A0038
		opword 0x901A0034
		opword 0x4800003C
		opword 0x38800100
		opword 0x38A00000
		opword 0x909A0034
		opword 0x7CA32B78
		opword 0x48000014
		opword 0x38030038
		opword 0x38630004
		opword 0x7C9A012E
		opword 0x38A50001
		opword 0x80141CC8
		opword 0x7C050000
		opword 0x4180FFE8
		opword 0x801A0038
		opword 0x901A0034
		opword 0x38000063
		opword 0x90141C9C
		opword 0x480005DC
		opword 0xA8741D18
		opword 0x2C030000
		opword 0x40810024
		opword 0x3803FFFF
		opword 0x38600002
		opword 0xB0141D18
		opword 0x380003EA
		opword 0x3B000001
		opword 0x90741CB8
		opword 0x90141C9C
		opword 0x480005B0
		opword 0x807A0008
		opword 0x80141CD0
		opword 0x7C0301D6
		opword 0x901A0014
		opword 0x807A0008
		opword 0x80141CD0
		opword 0x38630001
		opword 0x7C6301D6
		opword 0x3803FFFF
		opword 0x901A0018
		opword 0x801A0014
		opword 0x901A001C
		opword 0x807A002C
		bl _get_ok_frame_range
		opword 0x809A001C
		opword 0x3863FFFF
		opword 0x380003E8
		opword 0x7C641A14
		opword 0x907A0020
		opword 0x90141C9C
		opword 0x807A000C
		opword 0x80141CD0
		opword 0x38630001
		opword 0x7C6301D6
		opword 0x3803FFFF
		opword 0x901A0028
		opword 0x807A000C
		opword 0x38030001
		opword 0x901A000C
		opword 0x80741CE0
		opword 0x809A000C
		opword 0x38030001
		opword 0x7C040000
		opword 0x4080002C
		opword 0x80141C94
		opword 0x540007FF
		opword 0x41820014
		opword 0x80741C90
		opword 0x80030278
		opword 0x540006F7
		opword 0x40820034
		opword 0x7FE3FB78
		bl psndSFXOn
		opword 0x48000028
		opword 0x80141C94
		opword 0x540007FF
		opword 0x41820014
		opword 0x80741C90
		opword 0x80030278
		opword 0x540006F7
		opword 0x4082000C
		opword 0x7FC3F378
		bl psndSFXOn
		opword 0x38600000
		opword 0x380003E9
		opword 0x907A0024
		opword 0x90141C9C
		opword 0x807A0010
		opword 0x38030001
		opword 0x901A0010
		opword 0x801A0024
		opword 0x2C000000
		opword 0x41820010
		opword 0x38000000
		opword 0x901A0030
		opword 0x48000050
		opword 0x807A0008
		opword 0x80141CE0
		opword 0x7C030000
		opword 0x41800038
		opword 0x807A0010
		opword 0x801A001C
		opword 0x7C030000
		opword 0x4180001C
		opword 0x801A0020
		opword 0x7C030000
		opword 0x41810010
		opword 0x38000001
		opword 0x901A0030
		opword 0x48000018
		opword 0x38000000
		opword 0x901A0030
		opword 0x4800000C
		opword 0x38000000
		opword 0x901A0030
		opword 0x807A0034
		opword 0x3AC00000
		bl BattlePadCheckTrigger
		opword 0x2C030000
		opword 0x41820008
		opword 0x3B600001
		opword 0x2C1B0000
		opword 0x41820038
		opword 0x80141CD8
		opword 0x2C000002
		opword 0x41820008
		opword 0x48000024
		bl BattlePadGetTrigger
		opword 0x801A0034
		opword 0x7C001840
		opword 0x4082000C
		opword 0x3AC00001
		opword 0x48000010
		opword 0x3AC00000
		opword 0x48000008
		opword 0x3AC00001
		opword 0x2C170000
		opword 0x41820018
		opword 0x801A0030
		opword 0x2C000000
		opword 0x4182000C
		opword 0x3B600001
		opword 0x3AC00001
		opword 0x809A0000
		opword 0x807A0004
		opword 0x80141CC8
		opword 0x7C641A14
		opword 0x7C030000
		opword 0x41800008
		opword 0x3B600000
		opword 0x807A0008
		opword 0x80141CE0
		opword 0x7C030000
		opword 0x4180017C
		opword 0x2C1B0000
		opword 0x41820174
		opword 0x801A0024
		opword 0x2C000000
		opword 0x40820168
		opword 0x38800001
		opword 0x909A0024
		opword 0x807A0010
		opword 0x801A001C
		opword 0x7C030000
		opword 0x418000C4
		opword 0x801A0020
		opword 0x7C030000
		opword 0x418100B8
		opword 0x2C160000
		opword 0x418200B0
		opword 0x807A0000
		opword 0x38030001
		opword 0x901A0000
		opword 0x90941CEC
		opword 0x80BA0008
		opword 0x80741CE0
		opword 0x7C051800
		opword 0x41800044
		opword 0x80141CC8
		opword 0x7C001A14
		opword 0x7C050000
		opword 0x40800034
		opword 0x7C632850
		opword 0x3803004C
		opword 0x7C9A01AE
		opword 0x80141C94
		opword 0x540007FF
		opword 0x41820014
		opword 0x80741C90
		opword 0x80030278
		opword 0x540006F7
		opword 0x4082000C
		opword 0x7FA3EB78
		bl psndSFXOn
		opword 0x80141CC4
		opword 0x540006F7
		opword 0x418200D0
		opword 0x801A0000
		opword 0x90141CE8
		opword 0x80141CB8
		opword 0x5400003C
		opword 0x90141CB8
		opword 0x807A0000
		opword 0x80141CD4
		opword 0x7C030000
		opword 0x41800010
		opword 0x80141CB8
		opword 0x60000002
		opword 0x90141CB8
		opword 0x380003EA
		opword 0x3B000001
		opword 0x90141C9C
		opword 0x48000090
		opword 0x809A0008
		opword 0x80741CE0
		opword 0x7C041800
		opword 0x41800080
		opword 0x80141CC8
		opword 0x7C001A14
		opword 0x7C040000
		opword 0x40800070
		opword 0x807A0004
		opword 0x38030001
		opword 0x901A0004
		opword 0x807A0010
		opword 0x801A0014
		opword 0x7C030000
		opword 0x4180004C
		opword 0x80741CE0
		opword 0x3880FFFF
		opword 0x801A0008
		opword 0x7C630050
		opword 0x3803004C
		opword 0x7C9A01AE
		opword 0x80141C94
		opword 0x540007FF
		opword 0x41820014
		opword 0x80741C90
		opword 0x80030278
		opword 0x540006F7
		opword 0x4082000C
		opword 0x7F83E378
		bl psndSFXOn
		opword 0x3800FFFF
		opword 0x90141CEC
		opword 0x4800000C
		opword 0x38000000
		opword 0x901A0024
		opword 0x801A0024
		opword 0x2C000000
		opword 0x40820088
		opword 0x807A0010
		opword 0x801A0020
		opword 0x7C030000
		opword 0x40810078
		opword 0x38000001
		opword 0x3880FFFF
		opword 0x901A0024
		opword 0x90941CEC
		opword 0x80BA0008
		opword 0x80741CE0
		opword 0x7C051800
		opword 0x41800058
		opword 0x80141CC8
		opword 0x7C001A14
		opword 0x7C050000
		opword 0x40800048
		opword 0x807A0004
		opword 0x38030001
		opword 0x901A0004
		opword 0x80741CE0
		opword 0x801A0008
		opword 0x7C630050
		opword 0x3803004C
		opword 0x7C9A01AE
		opword 0x80141C94
		opword 0x540007FF
		opword 0x41820014
		opword 0x80741C90
		opword 0x80030278
		opword 0x540006F7
		opword 0x4082000C
		opword 0x7F83E378
		bl psndSFXOn
		opword 0x801A0024
		opword 0x2C000000
		opword 0x418200C8
		opword 0x80741CC8
		opword 0x80141CE0
		opword 0x809A0008
		opword 0x7C030214
		opword 0x7C040000
		opword 0x408000B0
		opword 0x38040001
		opword 0x901A0008
		opword 0x80741CC8
		opword 0x80141CE0
		opword 0x809A0008
		opword 0x7C030214
		opword 0x7C040000
		opword 0x40800090
		opword 0x80141CD0
		opword 0x7C6401D6
		opword 0x3803FFF6
		opword 0x901A0014
		opword 0x807A0008
		opword 0x80141CD0
		opword 0x38630001
		opword 0x7C6301D6
		opword 0x3803FFFF
		opword 0x901A0018
		opword 0x807A0008
		opword 0x80141CD0
		opword 0x7C0301D6
		opword 0x901A001C
		opword 0x807A002C
		bl _get_ok_frame_range
		opword 0x809A001C
		opword 0x3863FFFF
		opword 0x38000000
		opword 0x7C641A14
		opword 0x907A0020
		opword 0x901A0024
		opword 0x809A0008
		opword 0x80741CE0
		opword 0x7C041800
		opword 0x41800028
		opword 0x80141CC8
		opword 0x7C001A14
		opword 0x7C040000
		opword 0x40800018
		opword 0x7C032050
		opword 0x5403103A
		opword 0x38030038
		opword 0x7C1A002E
		opword 0x901A0034
		opword 0x809A000C
		opword 0x80141CD0
		opword 0x807A0010
		opword 0x7C0401D6
		opword 0x7C030000
		opword 0x418000D0
		opword 0x80741CC8
		opword 0x80141CE0
		opword 0x7C030214
		opword 0x7C040000
		opword 0x40800010
		opword 0x380003E8
		opword 0x90141C9C
		opword 0x480000B0
		opword 0x801A0000
		opword 0x90141CE8
		opword 0x80141CB8
		opword 0x5400003C
		opword 0x90141CB8
		opword 0x807A0000
		opword 0x80141CD4
		opword 0x7C030000
		opword 0x41800010
		opword 0x80141CB8
		opword 0x60000002
		opword 0x90141CB8
		opword 0x380003EA
		opword 0x3B000001
		opword 0x90141C9C
		opword 0x48000070
		opword 0x380003EB
		opword 0x90141C9C
		opword 0x48000064
		opword 0x80B41CC0
		opword 0x38800000
		opword 0x3860003C
		opword 0x380003ED
		opword 0x60A50001
		opword 0x90B41CC0
		opword 0x909A0030
		opword 0x907A0054
		opword 0x90141C9C
		opword 0x4800003C
		opword 0x807A0054
		opword 0x3803FFFF
		opword 0x901A0054
		opword 0x801A0054
		opword 0x2C000000
		opword 0x41810024
		opword 0x380003EE
		opword 0x90141C9C
		opword 0x48000018
		opword 0x38000000
		opword 0x90141CA0
		opword 0x90141CA8
		opword 0x90141CA4
		opword 0x90141CAC
		opword 0x2C180000
		opword 0x4082F81C
		opword 0xBA61000C
		opword 0x38600001
		opword 0x80010044
		opword 0x7C0803A6
		opword 0x38210040
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

s32 battleAcResult_SignalTiming(BattleWork* work) {
    return work->actionCommands.result;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs repeated mnemonic loads
#endif
void battleAcDisp_SignalTiming(CameraId cameraId, BattleWork* work) {
#ifdef NONMATCHING
    BattleActions* ac = &work->actionCommands;
    BattleACDispParams* disp = (BattleACDispParams*)((u8*)ac + 0x290);

    switch (ac->mAcState) {
        case 99:
        case 100:
            disp->iconX = ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(-300.0f, 30.0f, 4, 20 - *(s32*)&disp->field_0x1C[4], 20);
            actionCommandDisp(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[4] > 0) {
                (*(s32*)&disp->field_0x1C[4])--;
            }
            break;
        case 1000:
        case 1001:
        case 1002:
        case 1003:
            actionCommandDisp(30.0f, 0.0f);
            break;
        case 1004:
        case 1005:
            if (*(s32*)&disp->field_0x1C[4] >= 40) {
                disp->iconX = ((f32(*)(f32, f32, s32, s32, s32))intplGetValue)(30.0f, -300.0f, 4, *(s32*)&disp->field_0x1C[4] - 40, 20);
            } else {
                disp->iconX = 30.0f;
            }
            actionCommandDisp(disp->iconX, disp->iconY);
            if (*(s32*)&disp->field_0x1C[4] < 60) {
                (*(s32*)&disp->field_0x1C[4])++;
            }
            break;
    }
#endif
#ifndef NONMATCHING
	asm volatile {
		opword 0x9421FFF0
		opword 0x7C0802A6
		opword 0x90010014
		opword 0x93E1000C
		opword 0x3BE41F20
		opword 0x80041C9C
		opword 0x2C0003E8
		opword 0x40800018
		opword 0x2C000065
		opword 0x408000CC
		opword 0x2C000063
		opword 0x4080001C
		opword 0x480000C0
		opword 0x2C0003EE
		opword 0x408000B8
		opword 0x2C0003EC
		opword 0x4080005C
		opword 0x48000048
		opword 0x801F0020
		opword 0x38600004
		lfs f1, float_neg300_80421710(r2)
		opword 0x38A00014
		lfs f2, float_30_80421714(r2)
		opword 0x20800014
		bl intplGetValue
		opword 0xD03F0014
		opword 0xC03F0014
		opword 0xC05F0018
		bl actionCommandDisp
		opword 0x807F0020
		opword 0x2C030000
		opword 0x40810074
		opword 0x3803FFFF
		opword 0x901F0020
		opword 0x48000068
		lfs f1, float_30_80421714(r2)
		lfs f2, float_0_804216f4(r2)
		bl actionCommandDisp
		opword 0x48000058
		opword 0x807F0020
		opword 0x2C030028
		opword 0x41800024
		lfs f1, float_30_80421714(r2)
		opword 0x3883FFD8
		lfs f2, float_neg300_80421710(r2)
		opword 0x38600004
		opword 0x38A00014
		bl intplGetValue
		opword 0xD03F0014
		opword 0x4800000C
		lfs f0, float_30_80421714(r2)
		opword 0xD01F0014
		opword 0xC03F0014
		opword 0xC05F0018
		bl actionCommandDisp
		opword 0x807F0020
		opword 0x2C03003C
		opword 0x4080000C
		opword 0x38030001
		opword 0x901F0020
		opword 0x80010014
		opword 0x83E1000C
		opword 0x7C0803A6
		opword 0x38210010
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif

void battleAcDelete_SignalTiming(BattleWork* work) {
    work->actionCommands.mAcState = 1004;
}

#ifndef NONMATCHING
// FAKE (asmfake --minimal): target code as opwords; the C above is the NONMATCHING version
#pragma push
#pragma optimization_level 0  // else MWCC CSEs/drops repeated mnemonic loads
#endif
static void actionCommandDisp(f32 x, f32 y) {
#ifdef NONMATCHING
    BattleWork* work = _battleWorkPointer;
    BattleActions* ac = &work->actionCommands;
    SignalTimingWork* w;
    s32 i;
    s32 count;
    s32 next;
    s32 n;
    s32 num;
    s32 num2;
    f32 yb;
    f32 yd;
    f32 fx;
    f32 yc;
    Mtx mOut;
    Mtx mTrans;
    Mtx mScale;

    camGetPtr(8);
    w = (SignalTimingWork*)((u8*)ac + 0x2BC);
    count = ST_COUNT(work);
    next = w->next;
    if (!(ST_FLAGS(work) & 1)) {
        if (w->okFlag) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = -200.0f + x;
            pos.y = 70.0f + y;
            iconDispGx(&pos, 0x10, 0x65, 1.0f);
        } else {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = -200.0f + x;
            pos.y = 70.0f + y;
            iconDispGx(&pos, 0x10, 0x64, 1.0f);
        }
    }

    switch (count) {
        case 1:
            n = ST_LEAD(work) * 2 + 5;
            break;
        case 3:
            n = ST_LEAD(work) * 2 + 11;
            break;
        case 4:
            n = ST_LEAD(work) * 2 + 13;
            break;
        case 5:
            n = ST_LEAD(work) * 2 + 15;
            break;
        default:
            n = ST_LEAD(work) * 2 + 11;
            break;
    }

    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = -288.0f + x;
        pos.y = yb = 25.0f + y;
        iconDispGx(&pos, 0x10, 0x8F, 1.0f);
    }
    for (i = 1; i < n; i++) {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = x + (f32)(i * 16 - 288);
        pos.y = yb;
        iconDispGx(&pos, 0x10, 0x8E, 1.0f);
    }
    {
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = x + (f32)(i * 16 - 288);
        pos.y = yb;
        iconDispGx(&pos, 0x10, 0x90, 1.0f);
    }

    if (!(ST_FLAGS(work) & 4)) {
        fx = -200.0f + x;
        num = w->hits + ST_EXTRA(work);
PSMTXTrans(mTrans, fx + (f32)((ST_FLAGS(work) & 1) ? count * 0x30 - 26 + ST_LEAD(work) * 32 : count * 0x30 - 26 + ST_LEAD(work) * 32), yb, 0.0f);
        if (ST_FLAGS(work) & 8) {
            PSMTXScale(mScale, 1.5f, 1.5f, 1.5f);
        } else {
            PSMTXScale(mScale, 1.0f, 1.0f, 1.0f);
        }
        PSMTXConcat(mTrans, mScale, mOut);
        iconNumberDispGx(mOut, num, 0, (GXColor){255, 255, 255, 255});
    }

    for (i = 0; i < ST_LEAD(work); i++) {
        if (i < w->next) {
            if (i < ST_LEAD(work)) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 33 - 258);
                pos.y = yb;
                iconDispGx(&pos, 0x10, (u16)(0x92 + i), 1.0f);
            } else {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 33 - 258);
                pos.y = yb;
                iconDispGx(&pos, 0x10, 0x94, 1.0f);
            }
        } else {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = x + (f32)(i * 33 - 258);
            pos.y = yb;
            iconDispGx(&pos, 0x10, 0x91, 0.5f);
        }
    }

    if (!(ST_FLAGS(work) & 1)) {
        for (i = 0; i < count; i++) {
            if (i + ST_LEAD(work) < next) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250));
                pos.y = yb;
                iconDispGx(&pos, 0x10, 0x95, 1.0f);
            } else {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250));
                pos.y = yb;
                iconDispGx(&pos, 0x10, 0x91, 1.0f);
            }
        }
    } else if (!(ST_FLAGS(work) & 2)) {
        yc = 15.0f + y;
        for (i = 0; i < count; i++) {
            f32 scale = 0.8f;
            if (w->next == (i + ST_LEAD(work)) && w->frame >= ST_STEP(work) * (i + ST_LEAD(work)) - 5 && w->frame < ST_STEP(work) * (i + ST_LEAD(work))) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250));
                pos.y = yc;
                iconDispGx(&pos, 0x10, BattleACGetButtonIcon(w->buttons[i], 0), 0.8f);
            } else {
                s32 dy;
                if (w->next <= (i + ST_LEAD(work))) {
                    scale = 0.6f;
                    dy = -2;
                } else {
                    dy = -10;
                }
                {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250));
                pos.y = (f32)(dy + 25) + y;
                iconDispGx(&pos, 0x10, BattleACGetButtonIcon(w->buttons[i], 1), scale);
                }
            }
        }
    } else {
        yc = 20.800001f + yb;
        for (i = 0; i < count; i++) {
            if (w->next == (i + ST_LEAD(work)) && w->frame >= ST_STEP(work) * (i + ST_LEAD(work)) - 20 && w->frame <= ST_STEP(work) * (i + ST_LEAD(work))) {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250));
                pos.y = yb;
                iconDispGx(&pos, 0x10, BattleACGetButtonIcon(w->buttons[i], 0), 0.8f);
            } else if (w->next <= (i + ST_LEAD(work))) {
                if (i >= count - 1) {
                    btlDispTexPlane(0x40, (GXColor){255, 255, 255, 255}, 0, x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250)), yc, 0.0f, 0.8f, 0.8f);
                }
            } else {
                Vec pos = {0.0f, 0.0f, 0.0f};
                pos.x = x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250));
                pos.y = yb;
                iconDispGx(&pos, 0x10, BattleACGetButtonIcon(w->buttons[i], 1), 0.8f);
            }
        }
    }

    yd = yb - 25.0f;
    for (i = 0; i < count; i++) {
        if (w->results[i] == 1) {
            btlDispTexPlane(0x3E, (GXColor){255, 255, 255, 255}, 0, x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250)), yd, 0.0f, 1.0f, 1.0f);
        } else if (w->results[i] == -1) {
            btlDispTexPlane(0x3F, (GXColor){255, 255, 255, 255}, 0, x + (f32)(i * 48 + (ST_LEAD(work) * 33 - 250)), yd, 0.0f, 1.0f, 1.0f);
        }
    }
#endif
#ifndef NONMATCHING
	char _af_pad[348];
	asm volatile {
		opword 0xFFA00890
		lis r3, vec3_802fedc8@ha
		opword 0xFFC01090
		lwz r31, _battleWorkPointer(r13)
		addi r30, r3, vec3_802fedc8@l
		opword 0x38600008
		bl camGetPtr
		opword 0x801F1CC4
		opword 0x3B9F1F4C
		opword 0x837F1CC8
		opword 0x540007FF
		opword 0x835F1F58
		opword 0x4082009C
		opword 0x801C0030
		opword 0x2C000000
		opword 0x4182004C
		lfs f1, float_neg200_804216e0(r2)
		la r3, _af_pad+172
		lfs f0, float_70_804216e4(r2)
		opword 0x38800010
		opword 0x801E0000
		opword 0xEC41E82A
		opword 0x80DE0004
		opword 0xEC00F02A
		opword 0x900100B4
		opword 0x38A00065
		opword 0x801E0008
		opword 0x90C100B8
		lfs f1, float_1_804216e8(r2)
		opword 0x900100BC
		opword 0xD04100B4
		opword 0xD00100B8
		bl iconDispGx
		opword 0x48000048
		lfs f1, float_neg200_804216e0(r2)
		opword 0x386100A8
		lfs f0, float_70_804216e4(r2)
		opword 0x38800010
		opword 0x801E000C
		opword 0xEC41E82A
		opword 0x80DE0010
		opword 0xEC00F02A
		opword 0x900100A8
		opword 0x38A00064
		opword 0x801E0014
		opword 0x90C100AC
		lfs f1, float_1_804216e8(r2)
		opword 0x900100B0
		opword 0xD04100A8
		opword 0xD00100AC
		bl iconDispGx
		opword 0x2C1B0003
		opword 0x41820034
		opword 0x40800010
		opword 0x2C1B0001
		opword 0x41820018
		opword 0x48000054
		opword 0x2C1B0005
		opword 0x4182003C
		opword 0x40800048
		opword 0x48000024
		opword 0x801F1CE0
		opword 0x5403083C
		addi r23, r3, 0x5
		opword 0x48000040
		opword 0x801F1CE0
		opword 0x5403083C
		opword 0x3AE3000B
		opword 0x48000030
		opword 0x801F1CE0
		opword 0x5403083C
		opword 0x3AE3000D
		opword 0x48000020
		opword 0x801F1CE0
		opword 0x5403083C
		opword 0x3AE3000F
		opword 0x48000010
		opword 0x801F1CE0
		opword 0x5403083C
		opword 0x3AE3000B
		lfs f1, float_neg288_804216ec(r2)
		opword 0x3861009C
		lfs f0, float_25_804216f0(r2)
		opword 0x38800010
		opword 0x801E0018
		opword 0xEC41E82A
		opword 0x80DE001C
		opword 0xEFE0F02A
		opword 0x9001009C
		opword 0x38A0008F
		opword 0x801E0020
		opword 0x90C100A0
		lfs f1, float_1_804216e8(r2)
		opword 0x900100A4
		opword 0xD041009C
		opword 0xD3E100A0
		bl iconDispGx
		opword 0xCB9E00A8
		opword 0x3B000001
		opword 0x3B200010
		opword 0x3FA04330
		opword 0x4800005C
		opword 0x3819FEE0
		opword 0x80FE0024
		opword 0x6C008000
		opword 0x80DE0028
		opword 0x90010154
		opword 0x38610090
		opword 0x801E002C
		opword 0x38800010
		opword 0x93A10150
		opword 0x38A0008E
		lfs f1, float_1_804216e8(r2)
		opword 0xC8010150
		opword 0x90C10094
		opword 0xEC00E028
		opword 0x90E10090
		opword 0xEC1D002A
		opword 0x90010098
		opword 0xD3E10094
		opword 0xD0010090
		bl iconDispGx
		opword 0x3B180001
		opword 0x3B390010
		opword 0x7C18B800
		opword 0x4180FFA4
		opword 0x57032036
		opword 0x3C004330
		opword 0x3863FEE0
		opword 0x811E0030
		opword 0x6C638000
		opword 0x80FE0034
		opword 0x90610154
		opword 0x38610084
		opword 0x80DE0038
		opword 0x38800010
		opword 0x90010150
		opword 0x38A00090
		opword 0xC83E00A8
		opword 0xC8010150
		opword 0x90E10088
		opword 0xEC000828
		lfs f1, float_1_804216e8(r2)
		opword 0x91010084
		opword 0xEC1D002A
		opword 0x90C1008C
		opword 0xD3E10088
		opword 0xD0010084
		bl iconDispGx
		opword 0x807F1CC4
		opword 0x5460077B
		opword 0x408200E0
		lfs f0, float_neg200_804216e0(r2)
		opword 0x546007FF
		opword 0x809C0000
		opword 0x386100F0
		opword 0x801F1CDC
		opword 0xEC80E82A
		opword 0x7FA40214
		opword 0x4182001C
		opword 0x801F1CE0
		opword 0x1C9B0030
		opword 0x54002834
		opword 0x7C840214
		opword 0x3884FFE6
		opword 0x48000018
		opword 0x801F1CE0
		opword 0x1C9B0030
		opword 0x54002834
		opword 0x7C840214
		opword 0x3884FFE6
		opword 0x6C848000
		opword 0x3C004330
		opword 0x90810154
		opword 0xFC40F890
		opword 0xC83E00A8
		opword 0x90010150
		lfs f3, float_0_804216f4(r2)
		opword 0xC8010150
		opword 0xEC000828
		opword 0xEC24002A
		bl PSMTXTrans
		opword 0x801F1CC4
		opword 0x54000739
		opword 0x4182001C
		lfs f1, float_1p5_804216f8(r2)
		opword 0x386100C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x48000018
		lfs f1, float_1_804216e8(r2)
		opword 0x386100C0
		opword 0xFC400890
		opword 0xFC600890
		bl PSMTXScale
		opword 0x386100F0
		opword 0x388100C0
		opword 0x38A10120
		bl PSMTXConcat
		lwz r0, dat_804216d0(r2)
		opword 0x7FA4EB78
		opword 0x38610120
		opword 0x38C10014
		opword 0x90010014
		opword 0x38A00000
		bl iconNumberDispGx
		opword 0x3BA00000
		opword 0x3B200000
		opword 0x48000134
		opword 0x801C000C
		opword 0x7C1D0000
		opword 0x408000C8
		opword 0x7C1D1800
		opword 0x40800064
		opword 0x3819FEFE
		opword 0x3C804330
		opword 0x6C008000
		opword 0x80FE003C
		opword 0x90010154
		opword 0x381D0092
		opword 0x80DE0040
		opword 0x38610078
		opword 0x90810150
		opword 0x5405043E
		opword 0xC83E00A8
		opword 0x38800010
		opword 0xC8010150
		opword 0x90C1007C
		opword 0xEC000828
		opword 0x801E0044
		opword 0x90E10078
		lfs f1, float_1_804216e8(r2)
		opword 0xEC1D002A
		opword 0x90010080
		opword 0xD3E1007C
		opword 0xD0010078
		bl iconDispGx
		opword 0x480000B8
		opword 0x3879FEFE
		opword 0x3C004330
		opword 0x6C638000
		opword 0x80FE0048
		opword 0x90610154
		opword 0x3861006C
		opword 0x80DE004C
		opword 0x38800010
		opword 0x90010150
		opword 0x38A00094
		opword 0xC83E00A8
		opword 0xC8010150
		opword 0x90C10070
		opword 0xEC000828
		opword 0x801E0050
		opword 0x90E1006C
		lfs f1, float_1_804216e8(r2)
		opword 0xEC1D002A
		opword 0x90010074
		opword 0xD3E10070
		opword 0xD001006C
		bl iconDispGx
		opword 0x4800005C
		opword 0x3879FEFE
		opword 0x3C004330
		opword 0x6C638000
		opword 0x80FE0054
		opword 0x90610154
		opword 0x38610060
		opword 0x80DE0058
		opword 0x38800010
		opword 0x90010150
		opword 0x38A00091
		opword 0xC83E00A8
		opword 0xC8010150
		opword 0x90C10064
		opword 0xEC000828
		opword 0x801E005C
		opword 0x90E10060
		lfs f1, float_0p5_804216fc(r2)
		opword 0xEC1D002A
		opword 0x90010068
		opword 0xD3E10064
		opword 0xD0010060
		bl iconDispGx
		opword 0x3BBD0001
		opword 0x3B390021
		opword 0x807F1CE0
		opword 0x7C1D1800
		opword 0x4180FEC8
		opword 0x807F1CC4
		opword 0x546007FF
		opword 0x408200F8
		opword 0x3BA00000
		opword 0x3B200000
		opword 0x480000E0
		opword 0x807F1CE0
		opword 0x7C1D1A14
		opword 0x7C00D000
		opword 0x40800068
		opword 0x1CA30021
		opword 0x3C004330
		opword 0x811E0060
		opword 0x38610054
		opword 0x80DE0064
		opword 0x38800010
		opword 0x7CA5CA14
		opword 0x90C10058
		opword 0x38A5FF06
		opword 0x80FE0068
		opword 0x6CA68000
		opword 0x90010150
		opword 0xC85E00A8
		opword 0x38A00095
		opword 0x90C10154
		lfs f1, float_1_804216e8(r2)
		opword 0xC8010150
		opword 0x91010054
		opword 0xEC001028
		opword 0x90E1005C
		opword 0xEC1D002A
		opword 0xD3E10058
		opword 0xD0010054
		bl iconDispGx
		opword 0x48000064
		opword 0x1CA30021
		opword 0x3C004330
		opword 0x811E006C
		opword 0x38610048
		opword 0x80DE0070
		opword 0x38800010
		opword 0x7CA5CA14
		opword 0x90C1004C
		opword 0x38A5FF06
		opword 0x80FE0074
		opword 0x6CA68000
		opword 0x90010150
		opword 0xC85E00A8
		opword 0x38A00091
		opword 0x90C10154
		lfs f1, float_1_804216e8(r2)
		opword 0xC8010150
		opword 0x91010048
		opword 0xEC001028
		opword 0x90E10050
		opword 0xEC1D002A
		opword 0xD3E1004C
		opword 0xD0010048
		bl iconDispGx
		opword 0x3BBD0001
		opword 0x3B390030
		opword 0x7C1DD800
		opword 0x4180FF20
		opword 0x48000348
		opword 0x546007BD
		opword 0x40820188
		lfs f0, float_15_80421700(r2)
		opword 0x3BA00000
		opword 0x3B200000
		opword 0x3B400000
		opword 0xEF80F02A
		opword 0x48000164
		opword 0x807F1CE0
		opword 0x80FC000C
		opword 0x7C9D1A14
		lfs f27, float_0p8_80421704(r2)
		opword 0x7C072000
		opword 0x40820098
		opword 0x801F1CD0
		opword 0x80DC0010
		opword 0x7CA021D6
		opword 0x3805FFFB
		opword 0x7C060000
		opword 0x41800080
		opword 0x7C062800
		opword 0x40800078
		opword 0x1CA30021
		opword 0x3C604330
		opword 0x80FE0078
		opword 0x38190038
		opword 0x80DE007C
		opword 0x38800000
		opword 0x7CA5D214
		opword 0x90C10040
		opword 0x38A5FF06
		opword 0x80DE0080
		opword 0x6CA58000
		opword 0x90610150
		opword 0xC83E00A8
		opword 0x90A10154
		opword 0xC8010150
		opword 0x90E1003C
		opword 0xEC000828
		opword 0x90C10044
		opword 0xEC1D002A
		opword 0xD3810040
		opword 0xD001003C
		opword 0x7C7C002E
		bl BattleACGetButtonIcon
		lfs f1, float_0p8_80421704(r2)
		opword 0x7C651B78
		opword 0x3861003C
		opword 0x38800010
		bl iconDispGx
		opword 0x480000AC
		opword 0x7C072000
		opword 0x41810010
		lfs f27, float_0p6_80421708(r2)
		opword 0x3860FFFE
		opword 0x48000008
		opword 0x3860FFF6
		opword 0x809E0084
		opword 0x3CA04330
		opword 0x80FE0088
		opword 0x38030019
		opword 0x80DE008C
		opword 0x6C038000
		opword 0x90810030
		opword 0x38190038
		opword 0xC85E00A8
		opword 0x38800001
		opword 0x90E10034
		opword 0x90C10038
		opword 0x80DF1CE0
		opword 0x90A10150
		opword 0x1CC60021
		opword 0x9061015C
		opword 0x7C66D214
		opword 0x90A10158
		opword 0x3863FF06
		opword 0x6C638000
		opword 0xC8010158
		opword 0x90610154
		opword 0xEC001028
		opword 0xC8210150
		opword 0xEC211028
		opword 0xEC00F02A
		opword 0xEC3D082A
		opword 0xD0010034
		opword 0xD0210030
		opword 0x7C7C002E
		bl BattleACGetButtonIcon
		opword 0xFC20D890
		opword 0x7C651B78
		opword 0x38610030
		opword 0x38800010
		bl iconDispGx
		opword 0x3BBD0001
		opword 0x3B390004
		opword 0x3B5A0030
		opword 0x7C1DD800
		opword 0x4180FE9C
		opword 0x480001BC
		lfs f0, float_20p8_8042170c(r2)
		opword 0x3BA00000
		opword 0x3B400000
		opword 0x3B200000
		opword 0xEF80F82A
		opword 0x4800019C
		opword 0x807F1CE0
		opword 0x80FC000C
		opword 0x7C9D1A14
		opword 0x7C072000
		opword 0x40820098
		opword 0x801F1CD0
		opword 0x80DC0010
		opword 0x7CA021D6
		opword 0x3805FFEC
		opword 0x7C060000
		opword 0x41800080
		opword 0x7C062800
		opword 0x41810078
		opword 0x1CA30021
		opword 0x3C604330
		opword 0x80FE0090
		opword 0x381A0038
		opword 0x80DE0094
		opword 0x38800000
		opword 0x7CA5CA14
		opword 0x90C10028
		opword 0x38A5FF06
		opword 0x80DE0098
		opword 0x6CA58000
		opword 0x90610158
		opword 0xC83E00A8
		opword 0x90A1015C
		opword 0xC8010158
		opword 0x90E10024
		opword 0xEC000828
		opword 0x90C1002C
		opword 0xEC1D002A
		opword 0xD3E10028
		opword 0xD0010024
		opword 0x7C7C002E
		bl BattleACGetButtonIcon
		lfs f1, float_0p8_80421704(r2)
		opword 0x7C651B78
		opword 0x38610024
		opword 0x38800010
		bl iconDispGx
		opword 0x480000E8
		opword 0x7C072000
		opword 0x4181006C
		opword 0x381BFFFF
		opword 0x7C1D0000
		opword 0x418000D4
		lwz r3, dat_804216d4(r2)
		opword 0x3C004330
		lfs f4, float_0p8_80421704(r2)
		opword 0xFC40E090
		opword 0x90610010
		opword 0x38810010
		opword 0xC83E00A8
		opword 0xFCA02090
		opword 0x80BF1CE0
		opword 0x90010158
		opword 0x38600040
		opword 0x1C050021
		lfs f3, float_0_804216f4(r2)
		opword 0x38A00000
		opword 0x7CC0CA14
		opword 0x3806FF06
		opword 0x6C008000
		opword 0x9001015C
		opword 0xC8010158
		opword 0xEC000828
		opword 0xEC3D002A
		bl btlDispTexPlane
		opword 0x48000078
		opword 0x80FE009C
		opword 0x3C604330
		opword 0x80DE00A0
		opword 0x381A0038
		opword 0x80BE00A4
		opword 0x38800001
		opword 0x90E10018
		opword 0xC83E00A8
		opword 0x90C1001C
		opword 0x90A10020
		opword 0x80BF1CE0
		opword 0x90610158
		opword 0x1C650021
		opword 0xD3E1001C
		opword 0x7C63CA14
		opword 0x3863FF06
		opword 0x6C638000
		opword 0x9061015C
		opword 0xC8010158
		opword 0xEC000828
		opword 0xEC1D002A
		opword 0xD0010018
		opword 0x7C7C002E
		bl BattleACGetButtonIcon
		lfs f1, float_0p8_80421704(r2)
		opword 0x7C651B78
		opword 0x38610018
		opword 0x38800010
		bl iconDispGx
		opword 0x3BBD0001
		opword 0x3B5A0004
		opword 0x3B390030
		opword 0x7C1DD800
		opword 0x4180FE64
		lfs f0, float_25_804216f0(r2)
		opword 0x3BA00000
		opword 0x3B400000
		opword 0xEF9F0028
		opword 0x480000DC
		opword 0x381D004C
		opword 0x7C1C00AE
		opword 0x7C000774
		opword 0x2C000001
		opword 0x40820060
		lwz r3, dat_804216d8(r2)
		opword 0x3C004330
		lfs f4, float_1_804216e8(r2)
		opword 0xFC40E090
		opword 0x9061000C
		opword 0x3881000C
		opword 0xC83E00A8
		opword 0xFCA02090
		opword 0x80BF1CE0
		opword 0x90010158
		opword 0x3860003E
		opword 0x1C050021
		lfs f3, float_0_804216f4(r2)
		opword 0x38A00000
		opword 0x7CC0D214
		opword 0x3806FF06
		opword 0x6C008000
		opword 0x9001015C
		opword 0xC8010158
		opword 0xEC000828
		opword 0xEC3D002A
		bl btlDispTexPlane
		opword 0x48000064
		opword 0x2C00FFFF
		opword 0x4082005C
		lwz r3, dat_804216dc(r2)
		opword 0x3C004330
		lfs f4, float_1_804216e8(r2)
		opword 0xFC40E090
		opword 0x90610008
		opword 0x38810008
		opword 0xC83E00A8
		opword 0xFCA02090
		opword 0x80BF1CE0
		opword 0x90010158
		opword 0x3860003F
		opword 0x1C050021
		lfs f3, float_0_804216f4(r2)
		opword 0x38A00000
		opword 0x7CC0D214
		opword 0x3806FF06
		opword 0x6C008000
		opword 0x9001015C
		opword 0xC8010158
		opword 0xEC000828
		opword 0xEC3D002A
		bl btlDispTexPlane
		opword 0x3BBD0001
		opword 0x3B5A0030
		opword 0x7C1DD800
		opword 0x4180FF24
	}
#endif
}
#ifndef NONMATCHING
#pragma pop
#endif


// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
#ifdef NONMATCHING
__declspec(section ".rodata") const u32 gap_04_802FEEBC_rodata[1] = {0};
#endif
#pragma force_active reset
#pragma force_active reset

#ifndef NONMATCHING
// literal pool in target order (asmfake --minimal)
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fedc8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fedd4[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fede0[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fedec[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fedf8[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee04[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee10[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee1c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee28[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee34[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee40[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee4c[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee58[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f32 vec3_802fee64[3] = {0.0f, 0.0f, 0.0f};
__declspec(section ".rodata") const f64 double_to_int_802fee70 = 4503601774854144.0;
__declspec(section ".rodata") const char str_802FEE78[12] = "SFX_AC_PI1\0";
__declspec(section ".rodata") const char str_802FEE84[16] = "SFX_AC_PONE1\0\0\0";
__declspec(section ".rodata") const char str_802FEE94[20] = "SFX_AC_COMMAND_OK1\0";
__declspec(section ".rodata") const char str_802FEEA8[20] = "SFX_AC_COMMAND_NG1\0";
__declspec(section ".rodata") const u32 gap_04_802FEEBC_rodata[1] = {0};
__declspec(section ".sdata2") const u32 dat_804216d0 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_804216d4 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_804216d8 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_804216dc = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_neg200_804216e0 = -200.0f;
__declspec(section ".sdata2") const f32 float_70_804216e4 = 70.0f;
__declspec(section ".sdata2") const f32 float_1_804216e8 = 1.0f;
__declspec(section ".sdata2") const f32 float_neg288_804216ec = -288.0f;
__declspec(section ".sdata2") const f32 float_25_804216f0 = 25.0f;
__declspec(section ".sdata2") const f32 float_0_804216f4 = 0.0f;
__declspec(section ".sdata2") const f32 float_1p5_804216f8 = 1.5f;
__declspec(section ".sdata2") const f32 float_0p5_804216fc = 0.5f;
__declspec(section ".sdata2") const f32 float_15_80421700 = 15.0f;
__declspec(section ".sdata2") const f32 float_0p8_80421704 = 0.8f;
__declspec(section ".sdata2") const f32 float_0p6_80421708 = 0.6f;
__declspec(section ".sdata2") const f32 float_20p8_8042170c = 20.800001f;
__declspec(section ".sdata2") const f32 float_neg300_80421710 = -300.0f;
__declspec(section ".sdata2") const f32 float_30_80421714 = 30.0f;

#endif