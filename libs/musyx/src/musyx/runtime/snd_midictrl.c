
/*















*/

#include "musyx/assert.h"
#include "musyx/sal.h"
#include "musyx/seq.h"
#include "musyx/synth.h"

#include <string.h>

#define SYNTH_FX_MIDISET 0xFF

static u8 midi_lastNote[8][16];

static u8 fx_lastNote[64];

static u8 midi_ctrl[8][16][134];

static u8 fx_ctrl[64][134];

static u32 inpGlobalMIDIDirtyFlags[8][16];

static CHANNEL_DEFAULTS inpChannelDefaults[8][16];

static CHANNEL_DEFAULTS inpFXChannelDefaults[64];

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
/** Default cut-off settings of the low-pass filter. */
static u32 lpfHighFrequencyDefault = 0;
static u32 lpfLowFrequencyDefault = 0;
#endif

/** Returns whether any of the bits in flag are set in the global dirty flags of this MIDI channel. */
static inline bool GetGlobalFlagSet(u8 chan, u8 midiSet, s32 flag) {
  return (flag & inpGlobalMIDIDirtyFlags[midiSet][chan]) != 0;
}

/*






*/
static void inpResetGlobalMIDIDirtyFlags() {
  u32 i, j;
  for (i = 0; i < 8; ++i) {
    for (j = 0; j < 16; ++j) {
      inpGlobalMIDIDirtyFlags[i][j] = 0xFF;
    }
  }
}

/** Returns nonzero if any bit of flag was set in the channel's global dirty flags, clearing those bits. Not allowed for
 * the effect set (0xFF). */
static u32 inpResetGlobalMIDIDirtyFlag(u8 chan, u8 midiSet, u32 flag) {
  u32 ret;
  // clang-format off
  MUSY_ASSERT(midiSet!=SYNTH_FX_MIDISET);
  // clang-format on
  ;
  if ((ret = (flag & inpGlobalMIDIDirtyFlags[midiSet][chan]) != 0) != 0) {
    inpGlobalMIDIDirtyFlags[midiSet][chan] &= ~flag;
  }
  return ret;
}

/** Sets bits in the global dirty flags of a MIDI channel so aux inputs are recomputed next time. */
void inpSetGlobalMIDIDirtyFlag(u8 chan, u8 midiSet, s32 flag) {
  // clang-format off
  MUSY_ASSERT(midiSet!=SYNTH_FX_MIDISET);
  // clang-format on
  inpGlobalMIDIDirtyFlags[midiSet][chan] |= flag;
}

/** Handles a data-entry MSB (controller 6) for the registered parameter selected by controllers 100/101: RPN 0 sets the
 * pitch bend range (up to 24 semitones), RPN 0x7F7D and 0x7F7E set the high bits of the low-pass filter lower and upper
 * boundary frequencies. Updates the channel defaults and the matching voices. */
void inpSetRPNHi(u8 set, u8 channel, u8 value) {
  u16 rpn;  // r28
  u32 i;    // r31
  u8 range; // r29

  rpn = (midi_ctrl[set][channel][100]) | (midi_ctrl[set][channel][101] << 8);
  switch (rpn) {
  case 0:
    range = value > 24 ? 24 : value;
    inpChannelDefaults[set][channel].pbRange = range;

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].pbUpperKeyRange = range;
        synthVoice[i].pbLowerKeyRange = range;
      }
    }
    break;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
  case 0x7f7d: {
    u32 frq = (value << 9) | (inpChannelDefaults[set][channel].lpfLowerFrqBoundary & 0x1FF);
    inpChannelDefaults[set][channel].lpfLowerFrqBoundary = frq;

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfLowerFrqBoundary = frq;
      }
    }
  } break;

  case 0x7f7e: {
    u32 frq = (value << 9) | (inpChannelDefaults[set][channel].lpfUpperFrqBoundary & 0x1FF);
    inpChannelDefaults[set][channel].lpfUpperFrqBoundary = frq;

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfUpperFrqBoundary = frq;
      }
    }
  } break;
#endif
  default:
    break;
  }
}

/** Handles a data-entry LSB (controller 38): sets the low bits of the filter lower or upper boundary frequency for RPN
 * 0x7F7D / 0x7F7E. */
void inpSetRPNLo(u8 set, u8 channel, u8 value) {
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
  u16 rpn; // r28
  u32 i;   // r31

  rpn = (midi_ctrl[set][channel][100]) | (midi_ctrl[set][channel][101] << 8);
  switch (rpn) {
  case 0x7f7d: {
    u32 frq = (value << 2) | (inpChannelDefaults[set][channel].lpfLowerFrqBoundary & (u16)(~0x1FF));
    inpChannelDefaults[set][channel].lpfLowerFrqBoundary = frq;

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfLowerFrqBoundary = frq;
      }
    }
  } break;

  case 0x7f7e: {
    u32 frq = (value << 2) | (inpChannelDefaults[set][channel].lpfUpperFrqBoundary & (u16)(~0x1FF));
    inpChannelDefaults[set][channel].lpfUpperFrqBoundary = frq;

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfUpperFrqBoundary = frq;
      }
    }
  } break;
  }
#endif
}

/** Data decrement (controller 96): lowers the selected parameter by one (pitch bend range or filter boundary frequency)
 * and updates the matching voices. */
void inpSetRPNDec(u8 set, u8 channel) {
  u16 rpn;  // r28
  u32 i;    // r31
  u8 range; // r30

  rpn = (midi_ctrl[set][channel][100]) | (midi_ctrl[set][channel][101] << 8);
  switch (rpn) {
  case 0:
    range = inpChannelDefaults[set][channel].pbRange;
    if (range != 0) {
      --range;
    }
    inpChannelDefaults[set][channel].pbRange = range;
    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].pbUpperKeyRange = range;
        synthVoice[i].pbLowerKeyRange = range;
      }
    }
    break;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
  case 0x7f7d: {
    if (inpChannelDefaults[set][channel].lpfLowerFrqBoundary != 0) {
      --inpChannelDefaults[set][channel].lpfLowerFrqBoundary;
    }

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfLowerFrqBoundary = inpChannelDefaults[set][channel].lpfLowerFrqBoundary;
      }
    }
  } break;

  case 0x7f7e: {
    if (inpChannelDefaults[set][channel].lpfUpperFrqBoundary != 0) {
      --inpChannelDefaults[set][channel].lpfUpperFrqBoundary;
    }

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfUpperFrqBoundary = inpChannelDefaults[set][channel].lpfUpperFrqBoundary;
      }
    }
  } break;
#endif
  default:
    break;
  }
}

/** Data increment (controller 97): raises the selected parameter by one (pitch bend range up to 24, or filter boundary
 * up to 0x3FFF) and updates the matching voices. */
void inpSetRPNInc(u8 set, u8 channel) {
  u16 rpn;  // r28
  u32 i;    // r31
  u8 range; // r30

  rpn = (midi_ctrl[set][channel][100]) | (midi_ctrl[set][channel][101] << 8);
  switch (rpn) {
  case 0:
    range = inpChannelDefaults[set][channel].pbRange;
    if (range < 24) {
      ++range;
    }

    inpChannelDefaults[set][channel].pbRange = range;
    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].pbUpperKeyRange = range;
        synthVoice[i].pbLowerKeyRange = range;
      }
    }
    break;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
  case 0x7f7d: {
    if (inpChannelDefaults[set][channel].lpfLowerFrqBoundary != 0x3FFF) {
      ++inpChannelDefaults[set][channel].lpfLowerFrqBoundary;
    }

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfLowerFrqBoundary = inpChannelDefaults[set][channel].lpfLowerFrqBoundary;
      }
    }
  } break;

  case 0x7f7e: {
    if (inpChannelDefaults[set][channel].lpfUpperFrqBoundary != 0x3FFF) {
      ++inpChannelDefaults[set][channel].lpfUpperFrqBoundary;
    }

    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].lpfUpperFrqBoundary = inpChannelDefaults[set][channel].lpfUpperFrqBoundary;
      }
    }
  } break;
#endif
  default:
    break;
  }
}

/** Sets a 7-bit MIDI controller on a channel (set 0xFF = sound effect channel). Controllers 6, 38, 96 and 97 go to the
 * RPN handlers. If the value changed, every voice on that channel is flagged to recompute its inputs. */
void inpSetMidiCtrl(u8 ctrl, u8 channel, u8 set, u8 value) {
  u32 i;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
  bool changed;
#endif
  if (channel == 0xFF) {
    return;
  }

  if (set != 0xFF) {
    switch (ctrl) {
    case 6:
      inpSetRPNHi(set, channel, value);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
    case 38:
      inpSetRPNLo(set, channel, value);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
    case 96:
      inpSetRPNDec(set, channel);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
    case 97:
      inpSetRPNInc(set, channel);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
    default:
      changed = midi_ctrl[set][channel][ctrl] != (u8)(value & 0x7f);
      break;
#endif
    }

    midi_ctrl[set][channel][ctrl] = (value & 0x7f);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
    if (changed) {
      for (i = 0; i < synthInfo.voiceNum; ++i) {
        if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
          synthVoice[i].midiDirtyFlags = 0x7fff;
          synthKeyStateUpdate(&synthVoice[i]);
        }
      }
      inpGlobalMIDIDirtyFlags[set][channel] = 0xff;
    }
#else
    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].midiDirtyFlags = 0x1fff;
        synthKeyStateUpdate(&synthVoice[i]);
      }
    }
    inpGlobalMIDIDirtyFlags[set][channel] = 0xff;
#endif

  } else {
    switch (ctrl) {
    case 6:
      inpSetRPNHi(set, channel, value);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
    case 38:
      inpSetRPNLo(set, channel, value);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
    case 96:
      inpSetRPNDec(set, channel);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
    case 97:
      inpSetRPNInc(set, channel);
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
      changed = TRUE;
#endif
      break;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
    default:
      changed = fx_ctrl[channel][ctrl] != (u8)(value & 0x7f);
      break;
#endif
    }

    fx_ctrl[channel][ctrl] = value & 0x7f;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
    if (changed) {
      for (i = 0; i < synthInfo.voiceNum; ++i) {
        if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
          synthVoice[i].midiDirtyFlags = 0x7fff;
          synthKeyStateUpdate(&synthVoice[i]);
        }
      }
    }
#else
    for (i = 0; i < synthInfo.voiceNum; ++i) {
      if (set == synthVoice[i].midiSet && channel == synthVoice[i].midi) {
        synthVoice[i].midiDirtyFlags = 0x1fff;
        synthKeyStateUpdate(&synthVoice[i]);
      }
    }
#endif
  }
}

/** Sets a 14-bit controller by writing its MSB and LSB halves (controllers below 64 pair with +32, 128/129 and 132/133
 * are pairs; others take only the MSB). */
void inpSetMidiCtrl14(u8 ctrl, u8 channel, u8 set, u16 value) {

  if (channel == 0xFF) {
    return;
  }

  if (ctrl < 64) {
    inpSetMidiCtrl(ctrl & 31, channel, set, value >> 7);
    inpSetMidiCtrl((ctrl & 31) + 32, channel, set, value & 0x7f);
  } else if (ctrl == 128 || ctrl == 129) {
    inpSetMidiCtrl(ctrl & 254, channel, set, value >> 7);
    inpSetMidiCtrl((ctrl & 254) + 1, channel, set, value & 0x7f);
  } else if (ctrl == 132 || ctrl == 133) {
    inpSetMidiCtrl(ctrl & 254, channel, set, value >> 7);
    inpSetMidiCtrl((ctrl & 254) + 1, channel, set, value & 0x7f);
  } else {
    inpSetMidiCtrl(ctrl, channel, set, value >> 7);
  }
}

/** Values every MIDI controller is set to on a full reset; 0xFF entries are not written. */
static const u8 inpColdMIDIDefaults[134] = {
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x00, 0x00, 0x40, 0x7F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7F, 0x7F, 0x7F, 0x7F, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x00, 0x00, 0x40, 0x00,
};
/** Values the MIDI controllers are set to on a soft reset; 0xFF entries are left alone. */
static const u8 inpWarmMIDIDefaults[134] = {
    0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x7F, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
    0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x40, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,

};

/** Resets a channel's controllers: a cold reset copies the full default table (volume 127, pan 64, expression 127 and
 * so on), a warm reset only applies the defaults flagged in the warm table. Also clears the last note. */
void inpResetMidiCtrl(u8 ch, u8 set, u32 coldReset) {
  const u8* values; // r30
  u8* dest;         // r29
  u32 i;            // r31

  values = (coldReset ? inpColdMIDIDefaults : inpWarmMIDIDefaults);
  dest = set != 0xFF ? midi_ctrl[set][ch] : fx_ctrl[ch];

  if (coldReset) {
    memcpy(dest, values, 134);
  } else {
    for (i = 0; i < 134; ++i) {
      if (values[i] != 0xFF) {
        dest[i] = values[i];
      }
    }
  }

  inpSetMidiLastNote(ch, set, 0xFF);
}

/** Reads a controller as a 14-bit value: controllers below 64 combine MSB and LSB, switches 64-69 read as 0 or 0x3FFF,
 * 128/129 and 132/133 combine two bytes, others are the 7-bit value shifted up by 7. */
u16 inpGetMidiCtrl(u8 ctrl, u8 channel, u8 set) {

  if (channel != 0xff) {
    if (set != 0xff) {

      if (ctrl < 0x40) {
        return midi_ctrl[set][channel][ctrl & 0x1f] << 7 |
               midi_ctrl[set][channel][(ctrl & 0x1f) + 0x20];
      }
      if (ctrl < 0x46) {
        return midi_ctrl[set][channel][ctrl] < 0x40 ? 0 : 0x3fff;
      }
      if (ctrl >= 0x60 && ctrl < 0x66) {
        return 0;
      }

      if ((ctrl == 0x80) || (ctrl == 0x81)) {
        return midi_ctrl[set][channel][ctrl & 0xfe] << 7 |
               midi_ctrl[set][channel][(ctrl & 0xfe) + 1];
      }
      if ((ctrl == 0x84) || (ctrl == 0x85)) {
        return midi_ctrl[set][channel][ctrl & 0xfe] << 7 |
               midi_ctrl[set][channel][(ctrl & 0xfe) + 1];
      }

      return midi_ctrl[set][channel][ctrl] << 7;
    }
    if (ctrl < 0x40) {
      return fx_ctrl[channel][ctrl & 0x1f] << 7 | fx_ctrl[channel][(ctrl & 0x1f) + 0x20];
    }
    if (ctrl < 0x46) {
      return fx_ctrl[channel][ctrl] < 0x40 ? 0 : 0x3fff;
    }
    if (ctrl >= 0x60 && ctrl < 0x66) {
      return 0;
    }
    if ((ctrl == 0x80) || (ctrl == 0x81)) {
      return fx_ctrl[channel][ctrl & 0xfe] << 7 | fx_ctrl[channel][(ctrl & 0xfe) + 1];
    }
    if ((ctrl == 0x84) || (ctrl == 0x85)) {
      return fx_ctrl[channel][ctrl & 0xfe] << 7 | fx_ctrl[channel][(ctrl & 0xfe) + 1];
    }
    return fx_ctrl[channel][ctrl] << 7;
  }
  return 0;
}

/** Returns the defaults (pitch bend range, filter boundary frequencies) of a MIDI channel, or of a sound effect channel
 * when midiSet is 0xFF. */
CHANNEL_DEFAULTS* inpGetChannelDefaults(u8 midi, u8 midiSet) {
  if (midiSet == 0xFF) {
    return &inpFXChannelDefaults[midi];
  }

  return &inpChannelDefaults[midiSet][midi];
}

/** Resets a channel's defaults: pitch bend range 2 semitones and the default low-pass filter boundaries. */
void inpResetChannelDefaults(u8 midi, u8 midiSet) {
  CHANNEL_DEFAULTS* channelDefaults; // r31
  channelDefaults =
      midiSet != 0xFF ? &inpChannelDefaults[midiSet][midi] : &inpFXChannelDefaults[midi];
  channelDefaults->pbRange = 2;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
  channelDefaults->lpfLowerFrqBoundary = lpfLowFrequencyDefault;
  channelDefaults->lpfUpperFrqBoundary = lpfHighFrequencyDefault;
#endif
}

/** Adds a controller source to an input (CTRL_DEST) with a scale and a combine mode (0 starts a new list, up to 4
 * sources); isVar marks the source as a macro variable instead of a MIDI controller. */
void inpAddCtrl(CTRL_DEST* dest, u8 ctrl, s32 scale, u8 comb, u32 isVar) {
  u8 n; // r30
  if (comb == 0) {
    dest->numSource = 0;
  }

  if (dest->numSource < 4) {
    n = dest->numSource++;
    if (isVar == 0) {
      ctrl = inpTranslateExCtrl(ctrl);
    } else {
      comb |= 0x10;
    }

    dest->source[n].midiCtrl = ctrl;
    dest->source[n].combine = comb;
    dest->source[n].scale = scale;
  }
}

/** Copies a controller value (both halves for 14-bit ones) from one sound effect channel to another when cloning a
 * voice's MIDI setup. */
void inpFXCopyCtrl(u8 ctrl, SYNTH_VOICE* dvoice, SYNTH_VOICE* svoice) {
  u8 di; // r30
  u8 si; // r29
  di = dvoice->id;
  si = svoice->id;

  if (ctrl < 64) {
    fx_ctrl[di][ctrl & 31] = fx_ctrl[si][ctrl & 31];
    fx_ctrl[di][(ctrl & 31) + 32] = fx_ctrl[si][(ctrl & 31) + 32];
  } else if (ctrl == 128 || ctrl == 129) {
    fx_ctrl[di][ctrl & 254] = fx_ctrl[si][ctrl & 254];
    fx_ctrl[di][(ctrl & 254) + 1] = fx_ctrl[si][(ctrl & 254) + 1];
  } else if (ctrl == 132 || ctrl == 133) {
    fx_ctrl[di][ctrl & 254] = fx_ctrl[si][ctrl & 254];
    fx_ctrl[di][(ctrl & 254) + 1] = fx_ctrl[si][(ctrl & 254) + 1];
  } else {
    fx_ctrl[di][ctrl] = fx_ctrl[si][ctrl];
  }
}

/** Stores the last key played on a channel (used for portamento). */
void inpSetMidiLastNote(u8 midi, u8 midiSet, u8 key) {
  if (midiSet != 0xFF) {
    midi_lastNote[midiSet][midi] = key;
  } else {
    fx_lastNote[midi] = key;
  }
}

/** Returns the last key played on a channel. */
u8 inpGetMidiLastNote(u8 midi, u8 midiSet) {
  if (midiSet != 0xFF) {
    return midi_lastNote[midiSet][midi];
  }
  return fx_lastNote[midi];
}

/** Computes a voice input (volume, pan, ...) as a 14-bit value by combining its sources in order: each is a MIDI
 * controller, an LFO, the original key, original velocity, elapsed time or a macro variable, scaled, and combined by
 * the source's mode (set, add, multiply, subtract). Signed sources centre on 0x2000. Stores the result as the input's
 * old value. */
static u16 _GetInputValue(struct SYNTH_VOICE* svoice /* r27 */, struct CTRL_DEST* inp /* r24 */,
                          u8 midi /* r22 */, u8 midiSet /* r23 */) {
  u32 i;     // r26
  u32 value; // r29
  u8 ctrl;   // r28
  s32 tmp;   // r31
  s32 vtmp;  // r30
  bool sign; // r25

  for (value = 0, i = 0; i < inp->numSource; ++i) {
    if (inp->source[i].combine & 0x10) {
      tmp = (svoice != NULL ? varGet(svoice, 0, inp->source[i].midiCtrl) : 0);
      goto block_18;
    }
    ctrl = inp->source[i].midiCtrl;
    if (ctrl == 128 || ctrl == 1 || ctrl == 10 || ctrl == 160 || ctrl == 161 || ctrl == 131) {
      switch (ctrl) {
      case 160:
      case 161:
        if (svoice != NULL) {
          tmp = svoice->lfo[ctrl - 160].value << 1;
          svoice->lfoUsedByInput[ctrl - 160] = 1;
        } else {
          tmp = 0;
        }
        break;
      default:
        tmp = inpGetMidiCtrl(ctrl, midi, midiSet) - 0x2000;
        break;
      }
    block_18:
      tmp = (tmp * (inp->source[i].scale >> 1)) >> 15;
      tmp = CLAMP_INV(tmp, -0x2000, 0x1FFF);
      switch (inp->source[i].combine & 15) {
      case 0:
        value = tmp + 0x2000;
        sign = TRUE;
        break;
      case 1:
        if (sign != FALSE) {
          vtmp = (value + tmp);
          vtmp -= 0x2000;
          value = CLAMP_INV(vtmp, -0x2000, 0x1FFF) + 0x2000;
        } else {
          vtmp = value + tmp;
          value = CLAMP(vtmp, 0, 0x3FFF);
        }
        break;
      case 2:
        if (sign != FALSE) {
          vtmp = (s32)((value - 0x2000) * tmp) >> 13;
        } else {
          vtmp = (tmp * value) >> 13;
          sign = TRUE;
        }
        value = CLAMP_INV(vtmp, -0x2000, 0x1FFF) + 0x2000;
        break;
      case 3:
        if (sign != FALSE) {
          vtmp = (value - 0x2000) - tmp;
          value = CLAMP_INV(vtmp, -0x2000, 0x1FFF) + 0x2000;
        } else {
          vtmp = value - tmp;
          value = CLAMP(vtmp, 0, 0x3FFF);
        }
        break;
      }
    } else {
      switch (ctrl) {
      case 162:
        if (svoice != NULL) {
          tmp = svoice->orgNote << 7;
        } else {
          tmp = 0;
        }
        break;
      case 163:
        tmp = svoice != NULL ? svoice->orgVolume >> 9 : 0;
        break;
      case 164:
        if (svoice != NULL) {
          tmp = (synthRealTime - svoice->macStartTime) >> 8;
          if (tmp > 0x3fff) {
            tmp = 0x3fff;
          }
          svoice->timeUsedByInput = 1;
        } else {
          tmp = 0;
        }
        break;
      default:
        tmp = inpGetMidiCtrl(ctrl, midi, midiSet);
        break;
      }
      tmp = (tmp * (inp->source[i].scale >> 1)) >> 15;
      if (tmp > 0x3FFF) {
        tmp = 0x3FFF;
      }
      switch (inp->source[i].combine & 0xF) {
      case 0:
        value = tmp;
        sign = FALSE;
        break;
      case 1:
        if (sign != FALSE) {
          vtmp = (value + tmp);
          vtmp -= 0x2000;
          value = CLAMP_INV(vtmp, -0x2000, 0x1FFF) + 0x2000;
        } else {
          value += tmp;
          value = MIN(value, 0x3FFF);
        }
        break;
      case 2:
        if (sign != FALSE) {
          vtmp = (s32)(tmp * (value - 0x2000)) >> 14;
          value = CLAMP_INV(vtmp, -0x2000, 0x1FFF) + 0x2000;
        } else {
          value = ((value * tmp) >> 0xE);
          value = MIN(value, 0x3FFF);
        }
        break;
      case 3:
        if (sign != FALSE) {
          vtmp = (value - 0x2000) - tmp;
          value = CLAMP_INV(vtmp, -0x2000, 0x1FFF) + 0x2000;
        } else {
          vtmp = value - tmp;
          value = CLAMP(vtmp, 0, 0x3FFF);
        }
        break;
      }
    }
  }
  inp->oldValue = value;
  return value;
}

/** Returns the voice input's value, recomputing it only if its dirty bit is set in the voice's midiDirtyFlags. */
static u16 GetInputValue(SYNTH_VOICE* svoice, CTRL_DEST* inp, u32 dirtyMask) {

  if (!(svoice->midiDirtyFlags & dirtyMask)) {
    return inp->oldValue;
  }

  svoice->midiDirtyFlags &= ~dirtyMask;

  return _GetInputValue(svoice, inp, svoice->midi, svoice->midiSet);
}

/** Returns an aux input's value, recomputing it only if its global dirty flag for the channel was set. */
static u16 GetGlobalInputValue(CTRL_DEST* inp, u32 dirtyMask, u8 midi, u8 midiSet) {
  if (!inpResetGlobalMIDIDirtyFlag(midi, midiSet, dirtyMask)) {
    return inp->oldValue;
  }
  return _GetInputValue(NULL, inp, midi, midiSet);
}

/** Returns the voice's volume input (controllers 7 and 11 by default) as a 14-bit value. */
u16 inpGetVolume(SYNTH_VOICE* svoice) { return GetInputValue(svoice, &svoice->inpVolume, 0x1); }

/** Returns the voice's pan input (controller 10 by default). */
u16 inpGetPanning(SYNTH_VOICE* svoice) { return GetInputValue(svoice, &svoice->inpPanning, 0x2); }

/** Returns the voice's surround pan input (controller 131 by default). */
u16 inpGetSurPanning(SYNTH_VOICE* svoice) {
  return GetInputValue(svoice, &svoice->inpSurroundPanning, 0x4);
}

/** Returns the voice's pitch bend input (controller 128 by default). */
u16 inpGetPitchBend(SYNTH_VOICE* svoice) {
  return GetInputValue(svoice, &svoice->inpPitchBend, 0x8);
}

/** Returns the voice's doppler input (controller 132 by default), used by 3D sound. */
u16 inpGetDoppler(SYNTH_VOICE* svoice) { return GetInputValue(svoice, &svoice->inpDoppler, 0x10); }

/** Returns the voice's modulation input (controller 1 by default). */
u16 inpGetModulation(SYNTH_VOICE* svoice) {
  return GetInputValue(svoice, &svoice->inpModulation, 0x20);
}

/** Returns the voice's sustain pedal input (controller 64 by default). */
u16 inpGetPedal(SYNTH_VOICE* svoice) { return GetInputValue(svoice, &svoice->inpPedal, 0x40); }

/** Returns the voice's pre-fader aux A send input (no source by default). */
u16 inpGetPreAuxA(SYNTH_VOICE* svoice) { return GetInputValue(svoice, &svoice->inpPreAuxA, 0x100); }

/** Returns the voice's reverb send input (controller 91 by default). */
u16 inpGetReverb(SYNTH_VOICE* svoice) { return GetInputValue(svoice, &svoice->inpReverb, 0x200); }

/** Returns the voice's pre-fader aux B send input (no source by default). */
u16 inpGetPreAuxB(SYNTH_VOICE* svoice) { return GetInputValue(svoice, &svoice->inpPreAuxB, 0x400); }

/** Returns the voice's post-fader aux B (chorus) send input (controller 93 by default). */
u16 inpGetPostAuxB(SYNTH_VOICE* svoice) {
  return GetInputValue(svoice, &svoice->inpPostAuxB, 0x800);
}

/** Returns the voice's tremolo input (no source by default). */
u16 inpGetTremolo(SYNTH_VOICE* svoice) {
  return GetInputValue(svoice, &svoice->inpTremolo, 0x1000);
}

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
/** Returns the voice's low-pass filter switch input (controller 0x4F by default). */
u16 inpGetFilterSwitch(SYNTH_VOICE* svoice) {
  return GetInputValue(svoice, &svoice->inpFilterSwitch, 0x2000);
}

/** Returns the voice's low-pass filter cutoff input (controller 0x1F by default). */
u16 inpGetFilterParameter(SYNTH_VOICE* svoice) {
  return GetInputValue(svoice, &svoice->inpFilterParameter, 0x4000);
}
#endif

/** Returns the studio's aux A input number index for a MIDI channel. */
u16 inpGetAuxA(u8 studio, u8 index, u8 midi, u8 midiSet) {
  static u32 dirtyMask[4] = {0x80000001, 0x80000002, 0x80000004, 0x80000008};
  return GetGlobalInputValue(&inpAuxA[studio][index], dirtyMask[index], midi, midiSet);
}

/** Returns the studio's aux B input number index for a MIDI channel. */
u16 inpGetAuxB(u8 studio, u8 index, u8 midi, u8 midiSet) {
  static u32 dirtyMask[4] = {0x80000010, 0x80000020, 0x80000040, 0x80000080};

  return GetGlobalInputValue(&inpAuxB[studio][index], dirtyMask[index], midi, midiSet);
}

/** With a voice: sets up its default controller routing (volume = controller 7 times 11, pan 10, surround 131, pitch
 * bend 128, modulation 1, pedal 64, portamento 65, reverb 91, aux B 93, doppler 132, filter 0x4F/0x1F). With NULL:
 * clears the studio aux inputs and the global dirty flags. Also sets the default low-pass range of 80 to 16000 Hz. */
void inpInit(SYNTH_VOICE* svoice) {
  u32 i; // r30
  u32 s; // r29

  if (svoice != NULL) {
    svoice->inpVolume.source[0].midiCtrl = 7;
    svoice->inpVolume.source[0].combine = 0;
    svoice->inpVolume.source[0].scale = 0x10000;
    svoice->inpVolume.source[1].midiCtrl = 11;
    svoice->inpVolume.source[1].combine = 2;
    svoice->inpVolume.source[1].scale = 0x10000;
    svoice->inpVolume.numSource = 2;
    svoice->inpPanning.source[0].midiCtrl = 10;
    svoice->inpPanning.source[0].combine = 0;
    svoice->inpPanning.source[0].scale = 0x10000;
    svoice->inpPanning.numSource = 1;
    svoice->inpSurroundPanning.source[0].midiCtrl = 131;
    svoice->inpSurroundPanning.source[0].combine = 0;
    svoice->inpSurroundPanning.source[0].scale = 0x10000;
    svoice->inpSurroundPanning.numSource = 1;
    svoice->inpPitchBend.source[0].midiCtrl = 128;
    svoice->inpPitchBend.source[0].combine = 0;
    svoice->inpPitchBend.source[0].scale = 0x10000;
    svoice->inpPitchBend.numSource = 1;
    svoice->inpModulation.source[0].midiCtrl = 1;
    svoice->inpModulation.source[0].combine = 0;
    svoice->inpModulation.source[0].scale = 0x10000;
    svoice->inpModulation.numSource = 1;
    svoice->inpPedal.source[0].midiCtrl = 64;
    svoice->inpPedal.source[0].combine = 0;
    svoice->inpPedal.source[0].scale = 0x10000;
    svoice->inpPedal.numSource = 1;
    svoice->inpPortamento.source[0].midiCtrl = 65;
    svoice->inpPortamento.source[0].combine = 0;
    svoice->inpPortamento.source[0].scale = 0x10000;
    svoice->inpPortamento.numSource = 1;
    svoice->inpPreAuxA.numSource = 0;
    svoice->inpReverb.source[0].midiCtrl = 91;
    svoice->inpReverb.source[0].combine = 0;
    svoice->inpReverb.source[0].scale = 0x10000;
    svoice->inpReverb.numSource = 1;
    svoice->inpPreAuxB.numSource = 0;
    svoice->inpPostAuxB.source[0].midiCtrl = 93;
    svoice->inpPostAuxB.source[0].combine = 0;
    svoice->inpPostAuxB.source[0].scale = 0x10000;
    svoice->inpPostAuxB.numSource = 1;
    svoice->inpDoppler.source[0].midiCtrl = 132;
    svoice->inpDoppler.source[0].combine = 0;
    svoice->inpDoppler.source[0].scale = 0x10000;
    svoice->inpDoppler.numSource = 1;
    svoice->inpTremolo.numSource = 0;
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
    svoice->inpFilterSwitch.source[0].midiCtrl = 0x4f;
    svoice->inpFilterSwitch.source[0].combine = 0;
    svoice->inpFilterSwitch.source[0].scale = 0x10000;
    svoice->inpFilterSwitch.numSource = 1;
    svoice->inpFilterParameter.source[0].midiCtrl = 0x1f;
    svoice->inpFilterParameter.source[0].combine = 0;
    svoice->inpFilterParameter.source[0].scale = 0x10000;
    svoice->inpFilterParameter.numSource = 1;
#endif

#if MUSY_VERSION <= MUSY_VERSION_CHECK(2, 0, 0)
    svoice->midiDirtyFlags = 0x1fff;
#else
    svoice->midiDirtyFlags = 0x7fff;
#endif
    svoice->lfoUsedByInput[0] = 0;
    svoice->lfoUsedByInput[1] = 0;
    svoice->timeUsedByInput = 0;
  } else {
    for (s = 0; s < 8; ++s) {
      for (i = 0; i < 4; ++i) {
        inpAuxA[s][i].numSource = 0;
        inpAuxB[s][i].numSource = 0;
      }
    }

    inpResetGlobalMIDIDirtyFlags();
  }

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
  lpfLowFrequencyDefault = 80;
  lpfHighFrequencyDefault = 16000;
#endif
}

#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 1)
/** Sets the default low and high filter boundary frequencies used by inpResetChannelDefaults. */
void inpSetLPFDefaultRange(u32 lowFrq, u32 highFrq) {
  lpfLowFrequencyDefault = lowFrq;
  lpfHighFrequencyDefault = highFrq;
}
#endif

/** Maps the extended controller numbers used in macro data (0x80-0x88) to the internal controller numbers (LFO 0/1 as
 * 160/161, key, velocity and time sources as 162-164, and so on). */
u8 inpTranslateExCtrl(u8 ctrl) {
  switch (ctrl) {
  case 0x80:
    ctrl = 0x80;
    break;
  case 0x81:
    ctrl = 0x82;
    break;
  case 0x82:
    ctrl = 0xa0;
    break;
  case 0x83:
    ctrl = 0xa1;
    break;
  case 0x84:
    ctrl = 0x83;
    break;
  case 0x85:
    ctrl = 0x84;
    break;
  case 0x86:
    ctrl = 0xa2;
    break;
  case 0x87:
    ctrl = 0xa3;
    break;
  case 0x88:
    ctrl = 0xa4;
    break;
  }
  return ctrl;
}
/** Reads an extended controller of a voice as a 14-bit value; the LFO controllers return the voice's LFO value centred
 * on 0x2000, others the MIDI controller of the voice's channel (0 for voices without one). */
u16 inpGetExCtrl(SYNTH_VOICE* svoice, u8 ctrl) {
  u16 v; // r30
  switch (inpTranslateExCtrl(ctrl)) {
  case 160:
    v = (svoice->lfo[0].value << 1) + 0x2000;
    break;
  case 161:
    v = (svoice->lfo[1].value << 1) + 0x2000;
    break;
  default:
    v = svoice->midi != 0xFF ? inpGetMidiCtrl(ctrl, svoice->midi, svoice->midiSet) : 0;
    break;
  }

  return v;
}
/** Sets an extended controller of a voice from v (clamped to 0..0x3FFF) by writing the MIDI controller of the voice's
 * channel; LFO controllers cannot be set. */
void inpSetExCtrl(SYNTH_VOICE* svoice, u8 ctrl, s16 v) {
  v = v < 0 ? 0 : v > 0x3fff ? 0x3fff : v;

  switch (inpTranslateExCtrl(ctrl)) {
  case 161:
  case 160:
    break;
  default:
    if (svoice->midi != 0xFF) {
      inpSetMidiCtrl14(ctrl, svoice->midi, svoice->midiSet, v);
    }
    break;
  }
}
