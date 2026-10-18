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

u32 _button_table_4dir[4] = {0x10000, 0x20000, 0x40000, 0x80000};
u32 _button_table_abxy[4] = {0x100, 0x200, 0x400, 0x800};
s32 ac_signaltiming_ok_frame_range[7] = {20, 16, 12, 10, 6, 4, 2};
s32 ac_signaltiming_ok_frame_range_2[7] = {30, 30, 30, 30, 25, 20, 15};

static void actionCommandDisp(f32 x, f32 y);
s32 _get_ok_frame_range(s32 difficulty);

#pragma dont_inline on
#ifdef NONMATCHING
s32 _get_ok_frame_range(s32 difficulty) {
    BattleWork* work = _battleWorkPointer;
    switch (ST_MODE(work)) {
        case 1:
            return ST_OKBASE(work) + ac_signaltiming_ok_frame_range_2[difficulty];
    }
    return ST_OKBASE(work) + ac_signaltiming_ok_frame_range[difficulty];
}
#endif

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
}
#endif

#ifdef NONMATCHING
s32 battleAcResult_SignalTiming(BattleWork* work) {
    return work->actionCommands.result;
}
#endif

#ifdef NONMATCHING
void battleAcDisp_SignalTiming(CameraId cameraId, BattleWork* work) {
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
}
#endif

#ifdef NONMATCHING
void battleAcDelete_SignalTiming(BattleWork* work) {
    work->actionCommands.mAcState = 1004;
}
#endif

#ifdef NONMATCHING
static void actionCommandDisp(f32 x, f32 y) {
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
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): _get_ok_frame_range (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const f32 vec3_802fedc8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fedd4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fede0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fedec[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fedf8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee04[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee10[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee1c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee28[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee34[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee40[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee4c[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee58[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802fee64[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_802fee70 = 4503601774854144;
__declspec(section ".rodata") const char str_802FEE78[] = "SFX_AC_PI1\000";
__declspec(section ".rodata") const char str_802FEE84[] = "SFX_AC_PONE1\000\000\000";
__declspec(section ".rodata") const char str_802FEE94[] = "SFX_AC_COMMAND_OK1\000";
__declspec(section ".rodata") const char str_802FEEA8[] = "SFX_AC_COMMAND_NG1\000";
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

asm static void actionCommandDisp(f32 x, f32 y) {
	nofralloc
	stwu r1, -0x1e0(r1)
	mflr r0
	stw r0, 0x1e4(r1)
	stfd f31, 0x1d0(r1)
	psq_st f31, 0x1d8(r1), 0, 0
	stfd f30, 0x1c0(r1)
	psq_st f30, 0x1c8(r1), 0, 0
	stfd f29, 0x1b0(r1)
	psq_st f29, 0x1b8(r1), 0, 0
	stfd f28, 0x1a0(r1)
	psq_st f28, 0x1a8(r1), 0, 0
	stfd f27, 0x190(r1)
	psq_st f27, 0x198(r1), 0, 0
	stmw r23, 0x16c(r1)
	fmr f29, f1
	lis r3, vec3_802fedc8@ha
	fmr f30, f2
	lwz r31, _battleWorkPointer(r13)
	addi r30, r3, vec3_802fedc8@l
	li r3, 0x8
	bl camGetPtr
	lwz r0, 0x1cc4(r31)
	addi r28, r31, 0x1f4c
	lwz r27, 0x1cc8(r31)
	clrlwi. r0, r0, 31
	lwz r26, 0x1f58(r31)
	bne @1
	lwz r0, 0x30(r28)
	cmpwi r0, 0x0
	beq @2
	lfs f1, float_neg200_804216e0(r2)
	addi r3, r1, 0xb4
	lfs f0, float_70_804216e4(r2)
	li r4, 0x10
	lwz r0, 0x0(r30)
	fadds f2, f1, f29
	lwz r6, 0x4(r30)
	fadds f0, f0, f30
	stw r0, 0xb4(r1)
	li r5, 0x65
	lwz r0, 0x8(r30)
	stw r6, 0xb8(r1)
	lfs f1, float_1_804216e8(r2)
	stw r0, 0xbc(r1)
	stfs f2, 0xb4(r1)
	stfs f0, 0xb8(r1)
	bl iconDispGx
	b @1
	@2:
	lfs f1, float_neg200_804216e0(r2)
	addi r3, r1, 0xa8
	lfs f0, float_70_804216e4(r2)
	li r4, 0x10
	lwz r0, 0xc(r30)
	fadds f2, f1, f29
	lwz r6, 0x10(r30)
	fadds f0, f0, f30
	stw r0, 0xa8(r1)
	li r5, 0x64
	lwz r0, 0x14(r30)
	stw r6, 0xac(r1)
	lfs f1, float_1_804216e8(r2)
	stw r0, 0xb0(r1)
	stfs f2, 0xa8(r1)
	stfs f0, 0xac(r1)
	bl iconDispGx
	@1:
	cmpwi r27, 0x3
	beq @3
	bge @4
	cmpwi r27, 0x1
	beq @5
	b @6
	@4:
	cmpwi r27, 0x5
	beq @7
	bge @6
	b @8
	@5:
	lwz r0, 0x1ce0(r31)
	slwi r3, r0, 1
	addi r23, r3, 0x5
	b @9
	@3:
	lwz r0, 0x1ce0(r31)
	slwi r3, r0, 1
	addi r23, r3, 0xb
	b @9
	@8:
	lwz r0, 0x1ce0(r31)
	slwi r3, r0, 1
	addi r23, r3, 0xd
	b @9
	@7:
	lwz r0, 0x1ce0(r31)
	slwi r3, r0, 1
	addi r23, r3, 0xf
	b @9
	@6:
	lwz r0, 0x1ce0(r31)
	slwi r3, r0, 1
	addi r23, r3, 0xb
	@9:
	lfs f1, float_neg288_804216ec(r2)
	addi r3, r1, 0x9c
	lfs f0, float_25_804216f0(r2)
	li r4, 0x10
	lwz r0, 0x18(r30)
	fadds f2, f1, f29
	lwz r6, 0x1c(r30)
	fadds f31, f0, f30
	stw r0, 0x9c(r1)
	li r5, 0x8f
	lwz r0, 0x20(r30)
	stw r6, 0xa0(r1)
	lfs f1, float_1_804216e8(r2)
	stw r0, 0xa4(r1)
	stfs f2, 0x9c(r1)
	stfs f31, 0xa0(r1)
	bl iconDispGx
	lfd f28, 0xa8(r30)
	li r24, 0x1
	li r25, 0x10
	lis r29, 0x4330
	b @10
	@11:
	subi r0, r25, 0x120
	lwz r7, 0x24(r30)
	xoris r0, r0, 0x8000
	lwz r6, 0x28(r30)
	stw r0, 0x154(r1)
	addi r3, r1, 0x90
	lwz r0, 0x2c(r30)
	li r4, 0x10
	stw r29, 0x150(r1)
	li r5, 0x8e
	lfs f1, float_1_804216e8(r2)
	lfd f0, 0x150(r1)
	stw r6, 0x94(r1)
	fsubs f0, f0, f28
	stw r7, 0x90(r1)
	fadds f0, f29, f0
	stw r0, 0x98(r1)
	stfs f31, 0x94(r1)
	stfs f0, 0x90(r1)
	bl iconDispGx
	addi r24, r24, 0x1
	addi r25, r25, 0x10
	@10:
	cmpw r24, r23
	blt @11
	slwi r3, r24, 4
	lis r0, 0x4330
	subi r3, r3, 0x120
	lwz r8, 0x30(r30)
	xoris r3, r3, 0x8000
	lwz r7, 0x34(r30)
	stw r3, 0x154(r1)
	addi r3, r1, 0x84
	lwz r6, 0x38(r30)
	li r4, 0x10
	stw r0, 0x150(r1)
	li r5, 0x90
	lfd f1, 0xa8(r30)
	lfd f0, 0x150(r1)
	stw r7, 0x88(r1)
	fsubs f0, f0, f1
	lfs f1, float_1_804216e8(r2)
	stw r8, 0x84(r1)
	fadds f0, f29, f0
	stw r6, 0x8c(r1)
	stfs f31, 0x88(r1)
	stfs f0, 0x84(r1)
	bl iconDispGx
	lwz r3, 0x1cc4(r31)
	rlwinm. r0, r3, 0, 29, 29
	bne @12
	lfs f0, float_neg200_804216e0(r2)
	clrlwi. r0, r3, 31
	lwz r4, 0x0(r28)
	addi r3, r1, 0xf0
	lwz r0, 0x1cdc(r31)
	fadds f4, f0, f29
	add r29, r4, r0
	beq @13
	lwz r0, 0x1ce0(r31)
	mulli r4, r27, 0x30
	slwi r0, r0, 5
	add r4, r4, r0
	subi r4, r4, 0x1a
	b @14
	@13:
	lwz r0, 0x1ce0(r31)
	mulli r4, r27, 0x30
	slwi r0, r0, 5
	add r4, r4, r0
	subi r4, r4, 0x1a
	@14:
	xoris r4, r4, 0x8000
	lis r0, 0x4330
	stw r4, 0x154(r1)
	fmr f2, f31
	lfd f1, 0xa8(r30)
	stw r0, 0x150(r1)
	lfs f3, float_0_804216f4(r2)
	lfd f0, 0x150(r1)
	fsubs f0, f0, f1
	fadds f1, f4, f0
	bl PSMTXTrans
	lwz r0, 0x1cc4(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq @15
	lfs f1, float_1p5_804216f8(r2)
	addi r3, r1, 0xc0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	b @16
	@15:
	lfs f1, float_1_804216e8(r2)
	addi r3, r1, 0xc0
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	@16:
	addi r3, r1, 0xf0
	addi r4, r1, 0xc0
	addi r5, r1, 0x120
	bl PSMTXConcat
	lwz r0, dat_804216d0(r2)
	mr r4, r29
	addi r3, r1, 0x120
	addi r6, r1, 0x14
	stw r0, 0x14(r1)
	li r5, 0x0
	bl iconNumberDispGx
	@12:
	li r29, 0x0
	li r25, 0x0
	b @17
	@18:
	lwz r0, 0xc(r28)
	cmpw r29, r0
	bge @19
	cmpw r29, r3
	bge @20
	subi r0, r25, 0x102
	lis r4, 0x4330
	xoris r0, r0, 0x8000
	lwz r7, 0x3c(r30)
	stw r0, 0x154(r1)
	addi r0, r29, 0x92
	lwz r6, 0x40(r30)
	addi r3, r1, 0x78
	stw r4, 0x150(r1)
	clrlwi r5, r0, 16
	lfd f1, 0xa8(r30)
	li r4, 0x10
	lfd f0, 0x150(r1)
	stw r6, 0x7c(r1)
	fsubs f0, f0, f1
	lwz r0, 0x44(r30)
	stw r7, 0x78(r1)
	lfs f1, float_1_804216e8(r2)
	fadds f0, f29, f0
	stw r0, 0x80(r1)
	stfs f31, 0x7c(r1)
	stfs f0, 0x78(r1)
	bl iconDispGx
	b @21
	@20:
	subi r3, r25, 0x102
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lwz r7, 0x48(r30)
	stw r3, 0x154(r1)
	addi r3, r1, 0x6c
	lwz r6, 0x4c(r30)
	li r4, 0x10
	stw r0, 0x150(r1)
	li r5, 0x94
	lfd f1, 0xa8(r30)
	lfd f0, 0x150(r1)
	stw r6, 0x70(r1)
	fsubs f0, f0, f1
	lwz r0, 0x50(r30)
	stw r7, 0x6c(r1)
	lfs f1, float_1_804216e8(r2)
	fadds f0, f29, f0
	stw r0, 0x74(r1)
	stfs f31, 0x70(r1)
	stfs f0, 0x6c(r1)
	bl iconDispGx
	b @21
	@19:
	subi r3, r25, 0x102
	lis r0, 0x4330
	xoris r3, r3, 0x8000
	lwz r7, 0x54(r30)
	stw r3, 0x154(r1)
	addi r3, r1, 0x60
	lwz r6, 0x58(r30)
	li r4, 0x10
	stw r0, 0x150(r1)
	li r5, 0x91
	lfd f1, 0xa8(r30)
	lfd f0, 0x150(r1)
	stw r6, 0x64(r1)
	fsubs f0, f0, f1
	lwz r0, 0x5c(r30)
	stw r7, 0x60(r1)
	lfs f1, float_0p5_804216fc(r2)
	fadds f0, f29, f0
	stw r0, 0x68(r1)
	stfs f31, 0x64(r1)
	stfs f0, 0x60(r1)
	bl iconDispGx
	@21:
	addi r29, r29, 0x1
	addi r25, r25, 0x21
	@17:
	lwz r3, 0x1ce0(r31)
	cmpw r29, r3
	blt @18
	lwz r3, 0x1cc4(r31)
	clrlwi. r0, r3, 31
	bne @22
	li r29, 0x0
	li r25, 0x0
	b @23
	@24:
	lwz r3, 0x1ce0(r31)
	add r0, r29, r3
	cmpw r0, r26
	bge @25
	mulli r5, r3, 0x21
	lis r0, 0x4330
	lwz r8, 0x60(r30)
	addi r3, r1, 0x54
	lwz r6, 0x64(r30)
	li r4, 0x10
	add r5, r5, r25
	stw r6, 0x58(r1)
	subi r5, r5, 0xfa
	lwz r7, 0x68(r30)
	xoris r6, r5, 0x8000
	stw r0, 0x150(r1)
	lfd f2, 0xa8(r30)
	li r5, 0x95
	stw r6, 0x154(r1)
	lfs f1, float_1_804216e8(r2)
	lfd f0, 0x150(r1)
	stw r8, 0x54(r1)
	fsubs f0, f0, f2
	stw r7, 0x5c(r1)
	fadds f0, f29, f0
	stfs f31, 0x58(r1)
	stfs f0, 0x54(r1)
	bl iconDispGx
	b @26
	@25:
	mulli r5, r3, 0x21
	lis r0, 0x4330
	lwz r8, 0x6c(r30)
	addi r3, r1, 0x48
	lwz r6, 0x70(r30)
	li r4, 0x10
	add r5, r5, r25
	stw r6, 0x4c(r1)
	subi r5, r5, 0xfa
	lwz r7, 0x74(r30)
	xoris r6, r5, 0x8000
	stw r0, 0x150(r1)
	lfd f2, 0xa8(r30)
	li r5, 0x91
	stw r6, 0x154(r1)
	lfs f1, float_1_804216e8(r2)
	lfd f0, 0x150(r1)
	stw r8, 0x48(r1)
	fsubs f0, f0, f2
	stw r7, 0x50(r1)
	fadds f0, f29, f0
	stfs f31, 0x4c(r1)
	stfs f0, 0x48(r1)
	bl iconDispGx
	@26:
	addi r29, r29, 0x1
	addi r25, r25, 0x30
	@23:
	cmpw r29, r27
	blt @24
	b @27
	@22:
	rlwinm. r0, r3, 0, 30, 30
	bne @28
	lfs f0, float_15_80421700(r2)
	li r29, 0x0
	li r25, 0x0
	li r26, 0x0
	fadds f28, f0, f30
	b @29
	@30:
	lwz r3, 0x1ce0(r31)
	lwz r7, 0xc(r28)
	add r4, r29, r3
	lfs f27, float_0p8_80421704(r2)
	cmpw r7, r4
	bne @31
	lwz r0, 0x1cd0(r31)
	lwz r6, 0x10(r28)
	mullw r5, r0, r4
	subi r0, r5, 0x5
	cmpw r6, r0
	blt @31
	cmpw r6, r5
	bge @31
	mulli r5, r3, 0x21
	lis r3, 0x4330
	lwz r7, 0x78(r30)
	addi r0, r25, 0x38
	lwz r6, 0x7c(r30)
	li r4, 0x0
	add r5, r5, r26
	stw r6, 0x40(r1)
	subi r5, r5, 0xfa
	lwz r6, 0x80(r30)
	xoris r5, r5, 0x8000
	stw r3, 0x150(r1)
	lfd f1, 0xa8(r30)
	stw r5, 0x154(r1)
	lfd f0, 0x150(r1)
	stw r7, 0x3c(r1)
	fsubs f0, f0, f1
	stw r6, 0x44(r1)
	fadds f0, f29, f0
	stfs f28, 0x40(r1)
	stfs f0, 0x3c(r1)
	lwzx r3, r28, r0
	bl BattleACGetButtonIcon
	lfs f1, float_0p8_80421704(r2)
	mr r5, r3
	addi r3, r1, 0x3c
	li r4, 0x10
	bl iconDispGx
	b @32
	@31:
	cmpw r7, r4
	bgt @33
	lfs f27, float_0p6_80421708(r2)
	li r3, -0x2
	b @34
	@33:
	li r3, -0xa
	@34:
	lwz r4, 0x84(r30)
	lis r5, 0x4330
	lwz r7, 0x88(r30)
	addi r0, r3, 0x19
	lwz r6, 0x8c(r30)
	xoris r3, r0, 0x8000
	stw r4, 0x30(r1)
	addi r0, r25, 0x38
	lfd f2, 0xa8(r30)
	li r4, 0x1
	stw r7, 0x34(r1)
	stw r6, 0x38(r1)
	lwz r6, 0x1ce0(r31)
	stw r5, 0x150(r1)
	mulli r6, r6, 0x21
	stw r3, 0x15c(r1)
	add r3, r6, r26
	stw r5, 0x158(r1)
	subi r3, r3, 0xfa
	xoris r3, r3, 0x8000
	lfd f0, 0x158(r1)
	stw r3, 0x154(r1)
	fsubs f0, f0, f2
	lfd f1, 0x150(r1)
	fsubs f1, f1, f2
	fadds f0, f0, f30
	fadds f1, f29, f1
	stfs f0, 0x34(r1)
	stfs f1, 0x30(r1)
	lwzx r3, r28, r0
	bl BattleACGetButtonIcon
	fmr f1, f27
	mr r5, r3
	addi r3, r1, 0x30
	li r4, 0x10
	bl iconDispGx
	@32:
	addi r29, r29, 0x1
	addi r25, r25, 0x4
	addi r26, r26, 0x30
	@29:
	cmpw r29, r27
	blt @30
	b @27
	@28:
	lfs f0, float_20p8_8042170c(r2)
	li r29, 0x0
	li r26, 0x0
	li r25, 0x0
	fadds f28, f0, f31
	b @35
	@36:
	lwz r3, 0x1ce0(r31)
	lwz r7, 0xc(r28)
	add r4, r29, r3
	cmpw r7, r4
	bne @37
	lwz r0, 0x1cd0(r31)
	lwz r6, 0x10(r28)
	mullw r5, r0, r4
	subi r0, r5, 0x14
	cmpw r6, r0
	blt @37
	cmpw r6, r5
	bgt @37
	mulli r5, r3, 0x21
	lis r3, 0x4330
	lwz r7, 0x90(r30)
	addi r0, r26, 0x38
	lwz r6, 0x94(r30)
	li r4, 0x0
	add r5, r5, r25
	stw r6, 0x28(r1)
	subi r5, r5, 0xfa
	lwz r6, 0x98(r30)
	xoris r5, r5, 0x8000
	stw r3, 0x158(r1)
	lfd f1, 0xa8(r30)
	stw r5, 0x15c(r1)
	lfd f0, 0x158(r1)
	stw r7, 0x24(r1)
	fsubs f0, f0, f1
	stw r6, 0x2c(r1)
	fadds f0, f29, f0
	stfs f31, 0x28(r1)
	stfs f0, 0x24(r1)
	lwzx r3, r28, r0
	bl BattleACGetButtonIcon
	lfs f1, float_0p8_80421704(r2)
	mr r5, r3
	addi r3, r1, 0x24
	li r4, 0x10
	bl iconDispGx
	b @38
	@37:
	cmpw r7, r4
	bgt @39
	subi r0, r27, 0x1
	cmpw r29, r0
	blt @38
	lwz r3, dat_804216d4(r2)
	lis r0, 0x4330
	lfs f4, float_0p8_80421704(r2)
	fmr f2, f28
	stw r3, 0x10(r1)
	addi r4, r1, 0x10
	lfd f1, 0xa8(r30)
	fmr f5, f4
	lwz r5, 0x1ce0(r31)
	stw r0, 0x158(r1)
	li r3, 0x40
	mulli r0, r5, 0x21
	lfs f3, float_0_804216f4(r2)
	li r5, 0x0
	add r6, r0, r25
	subi r0, r6, 0xfa
	xoris r0, r0, 0x8000
	stw r0, 0x15c(r1)
	lfd f0, 0x158(r1)
	fsubs f0, f0, f1
	fadds f1, f29, f0
	bl btlDispTexPlane
	b @38
	@39:
	lwz r7, 0x9c(r30)
	lis r3, 0x4330
	lwz r6, 0xa0(r30)
	addi r0, r26, 0x38
	lwz r5, 0xa4(r30)
	li r4, 0x1
	stw r7, 0x18(r1)
	lfd f1, 0xa8(r30)
	stw r6, 0x1c(r1)
	stw r5, 0x20(r1)
	lwz r5, 0x1ce0(r31)
	stw r3, 0x158(r1)
	mulli r3, r5, 0x21
	stfs f31, 0x1c(r1)
	add r3, r3, r25
	subi r3, r3, 0xfa
	xoris r3, r3, 0x8000
	stw r3, 0x15c(r1)
	lfd f0, 0x158(r1)
	fsubs f0, f0, f1
	fadds f0, f29, f0
	stfs f0, 0x18(r1)
	lwzx r3, r28, r0
	bl BattleACGetButtonIcon
	lfs f1, float_0p8_80421704(r2)
	mr r5, r3
	addi r3, r1, 0x18
	li r4, 0x10
	bl iconDispGx
	@38:
	addi r29, r29, 0x1
	addi r26, r26, 0x4
	addi r25, r25, 0x30
	@35:
	cmpw r29, r27
	blt @36
	@27:
	lfs f0, float_25_804216f0(r2)
	li r29, 0x0
	li r26, 0x0
	fsubs f28, f31, f0
	b @40
	@41:
	addi r0, r29, 0x4c
	lbzx r0, r28, r0
	extsb r0, r0
	cmpwi r0, 0x1
	bne @42
	lwz r3, dat_804216d8(r2)
	lis r0, 0x4330
	lfs f4, float_1_804216e8(r2)
	fmr f2, f28
	stw r3, 0xc(r1)
	addi r4, r1, 0xc
	lfd f1, 0xa8(r30)
	fmr f5, f4
	lwz r5, 0x1ce0(r31)
	stw r0, 0x158(r1)
	li r3, 0x3e
	mulli r0, r5, 0x21
	lfs f3, float_0_804216f4(r2)
	li r5, 0x0
	add r6, r0, r26
	subi r0, r6, 0xfa
	xoris r0, r0, 0x8000
	stw r0, 0x15c(r1)
	lfd f0, 0x158(r1)
	fsubs f0, f0, f1
	fadds f1, f29, f0
	bl btlDispTexPlane
	b @43
	@42:
	cmpwi r0, -0x1
	bne @43
	lwz r3, dat_804216dc(r2)
	lis r0, 0x4330
	lfs f4, float_1_804216e8(r2)
	fmr f2, f28
	stw r3, 0x8(r1)
	addi r4, r1, 0x8
	lfd f1, 0xa8(r30)
	fmr f5, f4
	lwz r5, 0x1ce0(r31)
	stw r0, 0x158(r1)
	li r3, 0x3f
	mulli r0, r5, 0x21
	lfs f3, float_0_804216f4(r2)
	li r5, 0x0
	add r6, r0, r26
	subi r0, r6, 0xfa
	xoris r0, r0, 0x8000
	stw r0, 0x15c(r1)
	lfd f0, 0x158(r1)
	fsubs f0, f0, f1
	fadds f1, f29, f0
	bl btlDispTexPlane
	@43:
	addi r29, r29, 0x1
	addi r26, r26, 0x30
	@40:
	cmpw r29, r27
	blt @41
	psq_l f31, 0x1d8(r1), 0, 0
	lfd f31, 0x1d0(r1)
	psq_l f30, 0x1c8(r1), 0, 0
	lfd f30, 0x1c0(r1)
	psq_l f29, 0x1b8(r1), 0, 0
	lfd f29, 0x1b0(r1)
	psq_l f28, 0x1a8(r1), 0, 0
	lfd f28, 0x1a0(r1)
	psq_l f27, 0x198(r1), 0, 0
	lfd f27, 0x190(r1)
	lmw r23, 0x16c(r1)
	lwz r0, 0x1e4(r1)
	mtlr r0
	addi r1, r1, 0x1e0
	blr
}

asm void battleAcDelete_SignalTiming(BattleWork* work) {
	nofralloc
	li r0, 0x3ec
	stw r0, 0x1c9c(r3)
	blr
}

asm void battleAcDisp_SignalTiming(CameraId cameraId, BattleWork* work) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	addi r31, r4, 0x1f20
	lwz r0, 0x1c9c(r4)
	cmpwi r0, 0x3e8
	bge @1
	cmpwi r0, 0x65
	bge @2
	cmpwi r0, 0x63
	bge @3
	b @2
	@1:
	cmpwi r0, 0x3ee
	bge @2
	cmpwi r0, 0x3ec
	bge @4
	b @5
	@3:
	lwz r0, 0x20(r31)
	li r3, 0x4
	lfs f1, float_neg300_80421710(r2)
	li r5, 0x14
	lfs f2, float_30_80421714(r2)
	subfic r4, r0, 0x14
	bl intplGetValue
	stfs f1, 0x14(r31)
	lfs f1, 0x14(r31)
	lfs f2, 0x18(r31)
	bl actionCommandDisp
	lwz r3, 0x20(r31)
	cmpwi r3, 0x0
	ble @2
	subi r0, r3, 0x1
	stw r0, 0x20(r31)
	b @2
	@5:
	lfs f1, float_30_80421714(r2)
	lfs f2, float_0_804216f4(r2)
	bl actionCommandDisp
	b @2
	@4:
	lwz r3, 0x20(r31)
	cmpwi r3, 0x28
	blt @6
	lfs f1, float_30_80421714(r2)
	subi r4, r3, 0x28
	lfs f2, float_neg300_80421710(r2)
	li r3, 0x4
	li r5, 0x14
	bl intplGetValue
	stfs f1, 0x14(r31)
	b @7
	@6:
	lfs f0, float_30_80421714(r2)
	stfs f0, 0x14(r31)
	@7:
	lfs f1, 0x14(r31)
	lfs f2, 0x18(r31)
	bl actionCommandDisp
	lwz r3, 0x20(r31)
	cmpwi r3, 0x3c
	bge @2
	addi r0, r3, 0x1
	stw r0, 0x20(r31)
	@2:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm s32 battleAcResult_SignalTiming(BattleWork* work) {
	nofralloc
	lwz r3, 0x1cb8(r3)
	blr
}

asm s32 battleAcMain_SignalTiming(BattleWork *work) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	lis r4, vec3_802fedc8@ha
	stw r0, 0x44(r1)
	addi r4, r4, vec3_802fedc8@l
	stmw r19, 0xc(r1)
	mr r20, r3
	addi r26, r20, 0x1f4c
	li r23, 0x0
	addi r25, r20, 0x1f20
	lwz r3, 0x1c90(r3)
	lbz r0, 0x303(r3)
	cmplwi r0, 0x0
	beq @1
	li r23, 0x1
	@1:
	addi r28, r4, 0xe0
	addi r31, r4, 0xb0
	addi r30, r4, 0xbc
	addi r29, r4, 0xcc
	@2:
	lwz r0, 0x1c9c(r20)
	li r24, 0x0
	li r27, 0x0
	cmpwi r0, 0x3e9
	beq @3
	bge @4
	cmpwi r0, 0x63
	beq @5
	bge @6
	cmpwi r0, 0x0
	beq @7
	b @5
	@6:
	cmpwi r0, 0x3e8
	bge @8
	cmpwi r0, 0x65
	bge @5
	b @9
	@4:
	cmpwi r0, 0x3ed
	beq @10
	bge @11
	cmpwi r0, 0x3eb
	beq @5
	bge @12
	b @13
	@11:
	cmpwi r0, 0x3ef
	bge @5
	b @14
	@7:
	li r0, 0x1
	mr r3, r25
	stw r0, 0x1cb8(r20)
	li r4, 0x0
	li r5, 0x2c
	bl memset
	lfs f1, float_neg300_80421710(r2)
	li r4, 0x14
	lfs f0, float_0_804216f4(r2)
	li r0, 0x0
	stfs f1, 0x14(r25)
	mr r3, r20
	stfs f0, 0x18(r25)
	stw r4, 0x20(r25)
	stw r0, 0x0(r26)
	stw r0, 0x4(r26)
	stw r0, 0x10(r26)
	stw r0, 0x8(r26)
	stw r0, 0xc(r26)
	bl BattleActionCommandGetDifficulty
	stw r3, 0x2c(r26)
	li r3, 0x0
	li r0, 0x5
	li r4, 0x0
	stw r3, 0x30(r26)
	stw r3, 0x1cec(r20)
	mtctr r0
	@15:
	addi r0, r4, 0x4c
	addi r4, r4, 0x1
	stbx r3, r26, r0
	bdnz @15
	lwz r0, 0x1cd8(r20)
	cmpwi r0, 0x3
	bge @16
	cmpwi r0, 0x1
	bge @17
	b @16
	@17:
	li r27, 0x0
	li r19, 0x0
	b @18
	@19:
	li r22, 0x0
	b @20
	@21:
	lwz r0, 0x1cd8(r20)
	cmpwi r0, 0x1
	bne @22
	li r3, 0x4
	bl irand
	slwi r0, r3, 2
	la r3, _button_table_4dir(r13)
	lwzx r0, r3, r0
	b @23
	@22:
	li r3, 0x4
	bl irand
	slwi r0, r3, 2
	la r3, _button_table_abxy(r13)
	lwzx r0, r3, r0
	@23:
	subic. r4, r27, 0x1
	mr r21, r0
	li r5, 0x1
	addi r0, r4, 0x1
	slwi r3, r4, 2
	mtctr r0
	blt @24
	@25:
	addi r0, r3, 0x38
	lwzx r0, r26, r0
	cmplw r0, r21
	bne @26
	li r5, 0x0
	@26:
	subi r4, r4, 0x1
	subi r3, r3, 0x4
	bdnz @25
	@24:
	cmpwi r5, 0x0
	beq @20
	li r22, 0x1
	@20:
	cmpwi r22, 0x0
	beq @21
	addi r0, r19, 0x38
	addi r19, r19, 0x4
	stwx r21, r26, r0
	addi r27, r27, 0x1
	@18:
	lwz r0, 0x1cc8(r20)
	cmpw r27, r0
	blt @19
	lwz r0, 0x38(r26)
	stw r0, 0x34(r26)
	b @27
	@16:
	li r4, 0x100
	li r5, 0x0
	stw r4, 0x34(r26)
	mr r3, r5
	b @28
	@29:
	addi r0, r3, 0x38
	addi r3, r3, 0x4
	stwx r4, r26, r0
	addi r5, r5, 0x1
	@28:
	lwz r0, 0x1cc8(r20)
	cmpw r5, r0
	blt @29
	lwz r0, 0x38(r26)
	stw r0, 0x34(r26)
	@27:
	li r0, 0x63
	stw r0, 0x1c9c(r20)
	b @5
	@9:
	lha r3, 0x1d18(r20)
	cmpwi r3, 0x0
	ble @30
	subi r0, r3, 0x1
	li r3, 0x2
	sth r0, 0x1d18(r20)
	li r0, 0x3ea
	li r24, 0x1
	stw r3, 0x1cb8(r20)
	stw r0, 0x1c9c(r20)
	b @5
	@30:
	lwz r3, 0x8(r26)
	lwz r0, 0x1cd0(r20)
	mullw r0, r3, r0
	stw r0, 0x14(r26)
	lwz r3, 0x8(r26)
	lwz r0, 0x1cd0(r20)
	addi r3, r3, 0x1
	mullw r3, r3, r0
	subi r0, r3, 0x1
	stw r0, 0x18(r26)
	lwz r0, 0x14(r26)
	stw r0, 0x1c(r26)
	lwz r3, 0x2c(r26)
	bl _get_ok_frame_range
	lwz r4, 0x1c(r26)
	subi r3, r3, 0x1
	li r0, 0x3e8
	add r3, r4, r3
	stw r3, 0x20(r26)
	stw r0, 0x1c9c(r20)
	@8:
	lwz r3, 0xc(r26)
	lwz r0, 0x1cd0(r20)
	addi r3, r3, 0x1
	mullw r3, r3, r0
	subi r0, r3, 0x1
	stw r0, 0x28(r26)
	lwz r3, 0xc(r26)
	addi r0, r3, 0x1
	stw r0, 0xc(r26)
	lwz r3, 0x1ce0(r20)
	lwz r4, 0xc(r26)
	addi r0, r3, 0x1
	cmpw r4, r0
	bge @31
	lwz r0, 0x1c94(r20)
	clrlwi. r0, r0, 31
	beq @32
	lwz r3, 0x1c90(r20)
	lwz r0, 0x278(r3)
	rlwinm. r0, r0, 0, 27, 27
	bne @33
	@32:
	mr r3, r31
	bl psndSFXOn
	b @33
	@31:
	lwz r0, 0x1c94(r20)
	clrlwi. r0, r0, 31
	beq @34
	lwz r3, 0x1c90(r20)
	lwz r0, 0x278(r3)
	rlwinm. r0, r0, 0, 27, 27
	bne @33
	@34:
	mr r3, r30
	bl psndSFXOn
	@33:
	li r3, 0x0
	li r0, 0x3e9
	stw r3, 0x24(r26)
	stw r0, 0x1c9c(r20)
	@3:
	lwz r3, 0x10(r26)
	addi r0, r3, 0x1
	stw r0, 0x10(r26)
	lwz r0, 0x24(r26)
	cmpwi r0, 0x0
	beq @35
	li r0, 0x0
	stw r0, 0x30(r26)
	b @36
	@35:
	lwz r3, 0x8(r26)
	lwz r0, 0x1ce0(r20)
	cmpw r3, r0
	blt @37
	lwz r3, 0x10(r26)
	lwz r0, 0x1c(r26)
	cmpw r3, r0
	blt @38
	lwz r0, 0x20(r26)
	cmpw r3, r0
	bgt @38
	li r0, 0x1
	stw r0, 0x30(r26)
	b @36
	@38:
	li r0, 0x0
	stw r0, 0x30(r26)
	b @36
	@37:
	li r0, 0x0
	stw r0, 0x30(r26)
	@36:
	lwz r3, 0x34(r26)
	li r22, 0x0
	bl BattlePadCheckTrigger
	cmpwi r3, 0x0
	beq @39
	li r27, 0x1
	@39:
	cmpwi r27, 0x0
	beq @40
	lwz r0, 0x1cd8(r20)
	cmpwi r0, 0x2
	beq @41
	b @42
	@41:
	bl BattlePadGetTrigger
	lwz r0, 0x34(r26)
	cmplw r0, r3
	bne @43
	li r22, 0x1
	b @40
	@43:
	li r22, 0x0
	b @40
	@42:
	li r22, 0x1
	@40:
	cmpwi r23, 0x0
	beq @44
	lwz r0, 0x30(r26)
	cmpwi r0, 0x0
	beq @44
	li r27, 0x1
	li r22, 0x1
	@44:
	lwz r4, 0x0(r26)
	lwz r3, 0x4(r26)
	lwz r0, 0x1cc8(r20)
	add r3, r4, r3
	cmpw r3, r0
	blt @45
	li r27, 0x0
	@45:
	lwz r3, 0x8(r26)
	lwz r0, 0x1ce0(r20)
	cmpw r3, r0
	blt @46
	cmpwi r27, 0x0
	beq @46
	lwz r0, 0x24(r26)
	cmpwi r0, 0x0
	bne @46
	li r4, 0x1
	stw r4, 0x24(r26)
	lwz r3, 0x10(r26)
	lwz r0, 0x1c(r26)
	cmpw r3, r0
	blt @47
	lwz r0, 0x20(r26)
	cmpw r3, r0
	bgt @47
	cmpwi r22, 0x0
	beq @47
	lwz r3, 0x0(r26)
	addi r0, r3, 0x1
	stw r0, 0x0(r26)
	stw r4, 0x1cec(r20)
	lwz r5, 0x8(r26)
	lwz r3, 0x1ce0(r20)
	cmpw r5, r3
	blt @48
	lwz r0, 0x1cc8(r20)
	add r0, r0, r3
	cmpw r5, r0
	bge @48
	subf r3, r3, r5
	addi r0, r3, 0x4c
	stbx r4, r26, r0
	lwz r0, 0x1c94(r20)
	clrlwi. r0, r0, 31
	beq @49
	lwz r3, 0x1c90(r20)
	lwz r0, 0x278(r3)
	rlwinm. r0, r0, 0, 27, 27
	bne @48
	@49:
	mr r3, r29
	bl psndSFXOn
	@48:
	lwz r0, 0x1cc4(r20)
	rlwinm. r0, r0, 0, 27, 27
	beq @46
	lwz r0, 0x0(r26)
	stw r0, 0x1ce8(r20)
	lwz r0, 0x1cb8(r20)
	clrrwi r0, r0, 1
	stw r0, 0x1cb8(r20)
	lwz r3, 0x0(r26)
	lwz r0, 0x1cd4(r20)
	cmpw r3, r0
	blt @50
	lwz r0, 0x1cb8(r20)
	ori r0, r0, 0x2
	stw r0, 0x1cb8(r20)
	@50:
	li r0, 0x3ea
	li r24, 0x1
	stw r0, 0x1c9c(r20)
	b @46
	@47:
	lwz r4, 0x8(r26)
	lwz r3, 0x1ce0(r20)
	cmpw r4, r3
	blt @46
	lwz r0, 0x1cc8(r20)
	add r0, r0, r3
	cmpw r4, r0
	bge @46
	lwz r3, 0x4(r26)
	addi r0, r3, 0x1
	stw r0, 0x4(r26)
	lwz r3, 0x10(r26)
	lwz r0, 0x14(r26)
	cmpw r3, r0
	blt @51
	lwz r3, 0x1ce0(r20)
	li r4, -0x1
	lwz r0, 0x8(r26)
	subf r3, r3, r0
	addi r0, r3, 0x4c
	stbx r4, r26, r0
	lwz r0, 0x1c94(r20)
	clrlwi. r0, r0, 31
	beq @52
	lwz r3, 0x1c90(r20)
	lwz r0, 0x278(r3)
	rlwinm. r0, r0, 0, 27, 27
	bne @53
	@52:
	mr r3, r28
	bl psndSFXOn
	@53:
	li r0, -0x1
	stw r0, 0x1cec(r20)
	b @46
	@51:
	li r0, 0x0
	stw r0, 0x24(r26)
	@46:
	lwz r0, 0x24(r26)
	cmpwi r0, 0x0
	bne @54
	lwz r3, 0x10(r26)
	lwz r0, 0x20(r26)
	cmpw r3, r0
	ble @54
	li r0, 0x1
	li r4, -0x1
	stw r0, 0x24(r26)
	stw r4, 0x1cec(r20)
	lwz r5, 0x8(r26)
	lwz r3, 0x1ce0(r20)
	cmpw r5, r3
	blt @54
	lwz r0, 0x1cc8(r20)
	add r0, r0, r3
	cmpw r5, r0
	bge @54
	lwz r3, 0x4(r26)
	addi r0, r3, 0x1
	stw r0, 0x4(r26)
	lwz r3, 0x1ce0(r20)
	lwz r0, 0x8(r26)
	subf r3, r3, r0
	addi r0, r3, 0x4c
	stbx r4, r26, r0
	lwz r0, 0x1c94(r20)
	clrlwi. r0, r0, 31
	beq @55
	lwz r3, 0x1c90(r20)
	lwz r0, 0x278(r3)
	rlwinm. r0, r0, 0, 27, 27
	bne @54
	@55:
	mr r3, r28
	bl psndSFXOn
	@54:
	lwz r0, 0x24(r26)
	cmpwi r0, 0x0
	beq @56
	lwz r3, 0x1cc8(r20)
	lwz r0, 0x1ce0(r20)
	lwz r4, 0x8(r26)
	add r0, r3, r0
	cmpw r4, r0
	bge @56
	addi r0, r4, 0x1
	stw r0, 0x8(r26)
	lwz r3, 0x1cc8(r20)
	lwz r0, 0x1ce0(r20)
	lwz r4, 0x8(r26)
	add r0, r3, r0
	cmpw r4, r0
	bge @56
	lwz r0, 0x1cd0(r20)
	mullw r3, r4, r0
	subi r0, r3, 0xa
	stw r0, 0x14(r26)
	lwz r3, 0x8(r26)
	lwz r0, 0x1cd0(r20)
	addi r3, r3, 0x1
	mullw r3, r3, r0
	subi r0, r3, 0x1
	stw r0, 0x18(r26)
	lwz r3, 0x8(r26)
	lwz r0, 0x1cd0(r20)
	mullw r0, r3, r0
	stw r0, 0x1c(r26)
	lwz r3, 0x2c(r26)
	bl _get_ok_frame_range
	lwz r4, 0x1c(r26)
	subi r3, r3, 0x1
	li r0, 0x0
	add r3, r4, r3
	stw r3, 0x20(r26)
	stw r0, 0x24(r26)
	lwz r4, 0x8(r26)
	lwz r3, 0x1ce0(r20)
	cmpw r4, r3
	blt @56
	lwz r0, 0x1cc8(r20)
	add r0, r0, r3
	cmpw r4, r0
	bge @56
	subf r0, r3, r4
	slwi r3, r0, 2
	addi r0, r3, 0x38
	lwzx r0, r26, r0
	stw r0, 0x34(r26)
	@56:
	lwz r4, 0xc(r26)
	lwz r0, 0x1cd0(r20)
	lwz r3, 0x10(r26)
	mullw r0, r4, r0
	cmpw r3, r0
	blt @5
	lwz r3, 0x1cc8(r20)
	lwz r0, 0x1ce0(r20)
	add r0, r3, r0
	cmpw r4, r0
	bge @57
	li r0, 0x3e8
	stw r0, 0x1c9c(r20)
	b @5
	@57:
	lwz r0, 0x0(r26)
	stw r0, 0x1ce8(r20)
	lwz r0, 0x1cb8(r20)
	clrrwi r0, r0, 1
	stw r0, 0x1cb8(r20)
	lwz r3, 0x0(r26)
	lwz r0, 0x1cd4(r20)
	cmpw r3, r0
	blt @58
	lwz r0, 0x1cb8(r20)
	ori r0, r0, 0x2
	stw r0, 0x1cb8(r20)
	@58:
	li r0, 0x3ea
	li r24, 0x1
	stw r0, 0x1c9c(r20)
	b @5
	@13:
	li r0, 0x3eb
	stw r0, 0x1c9c(r20)
	b @5
	@12:
	lwz r5, 0x1cc0(r20)
	li r4, 0x0
	li r3, 0x3c
	li r0, 0x3ed
	ori r5, r5, 0x1
	stw r5, 0x1cc0(r20)
	stw r4, 0x30(r26)
	stw r3, 0x54(r26)
	stw r0, 0x1c9c(r20)
	b @5
	@10:
	lwz r3, 0x54(r26)
	subi r0, r3, 0x1
	stw r0, 0x54(r26)
	lwz r0, 0x54(r26)
	cmpwi r0, 0x0
	bgt @5
	li r0, 0x3ee
	stw r0, 0x1c9c(r20)
	b @5
	@14:
	li r0, 0x0
	stw r0, 0x1ca0(r20)
	stw r0, 0x1ca8(r20)
	stw r0, 0x1ca4(r20)
	stw r0, 0x1cac(r20)
	@5:
	cmpwi r24, 0x0
	bne @2
	lmw r19, 0xc(r1)
	li r3, 0x1
	lwz r0, 0x44(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm s32 _get_ok_frame_range(s32 difficulty) {
	nofralloc
	lwz r4, _battleWorkPointer(r13)
	lwz r0, 0x1ccc(r4)
	cmpwi r0, 0x1
	beq @1
	b @2
	@1:
	slwi r0, r3, 2
	la r3, ac_signaltiming_ok_frame_range_2(r13)
	lwz r4, 0x1ce4(r4)
	lwzx r0, r3, r0
	add r3, r4, r0
	blr
	@2:
	slwi r0, r3, 2
	la r3, ac_signaltiming_ok_frame_range(r13)
	lwz r4, 0x1ce4(r4)
	lwzx r0, r3, r0
	add r3, r4, r0
	blr
}
// clang-format on
#endif

// target pad words (G5: section sizes must match or later DOL addresses shift)
#pragma force_active on
__declspec(section ".rodata") const u32 gap_04_802FEEBC_rodata[1] = {0};
#pragma force_active reset
#pragma force_active reset
