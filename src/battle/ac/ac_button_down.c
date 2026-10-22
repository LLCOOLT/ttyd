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

void *memset(void *dest, int ch, size_t count);
s32 battleAcMain_ButtonDown(BattleWork *work)
{
  s32 off;
  BattleActions *ac = &work->actionCommands;
  BDWork *p = (BDWork *) (((u8 *) work) + 0x1f4c);
  u8 *disp = ((u8 *) work) + 0x1f20;
  s32 i;
  s32 off2;
  s32 k;
  s32 done;
  s32 allDone;
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
        for (off = 0, i = 0; i < (*((s32 *) (((u8 *) work) + 0x1cd0))); off += 4, i++)
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
        done = 1;
        for (i = 0, off2 = 0; i < (*((s32 *) (((u8 *) work) + 0x1cd0))); i++, off2 += 4)
      {
        if (*((u32 *) (((u8 *) p) + (off2 + 8))))
        {
          if (*((s32 *) (((u8 *) p) + (off2 + 0x3c))))
          {
            (*((s32 *) (&ac->outputParams[0])))++;
          }
          else
            if (((*((u32 *) (((u8 *) p) + (off2 + 8)))) == BattlePadGetTrigger()) || flag)
          {
            *((s32 *) (((u8 *) p) + (off2 + 0x3c))) = 1;
            (*((s32 *) (&ac->outputParams[0])))++;
            if ((*((s32 *) (((u8 *) work) + 0x1ccc))) == 1)
            {
              if ((i + 1) < (*((s32 *) (((u8 *) work) + 0x1cd0))))
              {
                done = 0;
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
            done = 0;
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
        if (done)
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
            x = intplGetValue(4, 20 - disp[8], 20, -300.0f, 0.0f);
            y = 0.0f;
            break;
        default:
            x = y = 0.0f;
            break;
    }
    actionCommandDisp(0, x, y);
}

void battleAcDelete_ButtonDown(BattleWork* work) {
    work->actionCommands.mAcState = 1003;
}

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


