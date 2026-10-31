#include "musyx/musyx.h"

#include "musyx/assert.h"
#include "musyx/hardware.h"
#include "musyx/macros.h"
#include "musyx/snd.h"
#include "musyx/voice.h"

#if MUSY_TARGET == MUSY_TARGET_DOLPHIN
#include <dolphin/os.h>
#endif

u32 vidGetPublicId(u32 voice);
u32 seqGetInstanceForVoice(u32 vid);
u32 hwGetSampleExtraData(u32 voice);

VS vs;

/**
 * Clears the virtual sample tables (the 64 voice-to-buffer slots) and the application callback.
 * Virtual samples are samples whose data the game supplies on the fly through a callback into an ARAM loop
 * buffer.
 */
void vsInit() {
  u32 i;
  vs.numBuffers = 0;
  for (i = 0; i < 64; i++) {
    vs.voices[i] = 0xFF;
  }

  vs.nextInstID = 0;
  vs.callback = NULL;
}

/** Returns an instance ID for a new virtual sample that no active buffer uses. */
static inline u16 vsNewInstanceID() {
  u8 i;       // r31
  u16 instID; // r29
  do {
    instID = vs.nextInstID++;
    for (i = 0; i < vs.numBuffers; ++i) {
      if (vs.streamBuffer[i].state != 0 && vs.streamBuffer[i].info.instID == instID) {
        break;
      }
    }
  } while (i != vs.numBuffers);

  return instID;
}

/** Reserves the first free virtual sample buffer slot and returns its index, or 0xFF if all are in use. */
static inline u8 vsAllocateBuffer() {
  u8 i;

  for (i = 0; i < vs.numBuffers; ++i) {
    if (vs.streamBuffer[i].state != 0) {
      continue;
    }
    vs.streamBuffer[i].state = 1;
    vs.streamBuffer[i].last = 0;
    return i;
  }

  return 0xFF;
}

/** Releases a virtual sample buffer slot and its voice mapping. */
static inline void vsFreeBuffer(u8 bufferIndex) {
  vs.streamBuffer[bufferIndex].state = 0;
  vs.voices[vs.streamBuffer[bufferIndex].voice] = 0xFF;
}

/**
 * Called when a voice starts a virtual sample: frees any old buffer of that voice,
 * assigns a new buffer and ARAM loop buffer, fills in the sample ID, instance ID,
 * owning sequence and extra data, then asks the application callback (reason 0) to start supplying data.
 * Returns the voice/instance handle, or 0xFFFFFFFF if the voice could not be set up or the callback refused.
 */
u32 vsSampleStartNotify(unsigned long vid) {
  u8 voice;
  u8 v1 = vid;
  u8 sb;       // r29
  u8 i;        // r28
  size_t addr; // r27

  voice = v1 & 0xFF;
  for (i = 0; i < vs.numBuffers; ++i) {
    if (vs.streamBuffer[i].state != 0 && vs.streamBuffer[i].voice == voice) {
      vsFreeBuffer(i);
    }
  }

  sb = vs.voices[voice] = vsAllocateBuffer();
  if (sb != 0xFF) {
    addr = aramGetStreamBufferAddress(vs.voices[voice], 0);
    hwSetVirtualSampleLoopBuffer(voice, (void*)addr, vs.bufferLength);
    vs.streamBuffer[sb].info.smpID = hwGetSampleID(voice);
    vs.streamBuffer[sb].info.instID = vsNewInstanceID();
    if ((vs.streamBuffer[sb].info.pubID = vidGetPublicId(vid)) != 0xFFFFFFFF) {
      vs.streamBuffer[sb].info.seqInstID = seqGetInstanceForVoice(vs.streamBuffer[sb].info.pubID);
    } else {
      vs.streamBuffer[sb].info.seqInstID = 0xFFFFFFFF;
    }
    vs.streamBuffer[sb].info.data.extraData = hwGetSampleExtraData(voice);
    vs.streamBuffer[sb].smpType = hwGetSampleType(voice);
    vs.streamBuffer[sb].voice = voice;
    if (vs.callback != NULL && vs.callback(0, &vs.streamBuffer[sb].info) == 0) {
      return (vs.streamBuffer[sb].info.instID << 8) | voice;
    }
    hwSetVirtualSampleLoopBuffer(voice, 0, 0);
    vs.streamBuffer[sb].state = 0;
    vs.voices[vs.streamBuffer[sb].voice] = 0xFF;
  } else {
    hwSetVirtualSampleLoopBuffer(voice, 0, 0);
  }

  return 0xFFFFFFFF;
}

/**
 * Called when a virtual sample voice ends: if the handle still matches its buffer,
 * tells the callback (reason 2) and frees the buffer.
 */
void vsSampleEndNotify(u32 pubID) {
  u8 sb;
  u8 voice;

  if (pubID != 0xFFFFFFFF) {
    u8 id = (u8)pubID;
    sb = vs.voices[id];
    if (sb != 0xFF) {
      if (vs.streamBuffer[sb].info.instID == ((pubID >> 8) & 0xFFFF)) {
        if (vs.callback != NULL) {
          vs.callback(2, &vs.streamBuffer[sb].info);
        }
        vsFreeBuffer(sb);
      }
    }
  }
}

/**
 * Asks the application callback (reason 1) to refill the part of the loop buffer that the voice has played since
 * last time, for ADPCM (type 5, 14 samples per 8 bytes) or 16-bit PCM (type 6) data,
 * handling the wrap at the end of the buffer.
 */
void vsUpdateBuffer(struct VS_BUFFER* sb, unsigned long cpos) {
  u32 len;
  if (sb->last == cpos) {
    return;
  }
  if (sb->last < cpos) {
    switch (sb->smpType) {
    case 5: {
      sb->info.data.update.off1 = (sb->last / 14) * 8;
      sb->info.data.update.len1 = cpos - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        sb->last = (sb->last + len) % vs.bufferLength;
      }
    } break;
    case 6: {
      sb->info.data.update.off1 = sb->last * 2;
      sb->info.data.update.len1 = cpos - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        sb->last = (sb->last + len) % vs.bufferLength;
      }
    } break;
    default:
      break;
    }
  } else if (cpos == 0) {
    switch (sb->smpType) {
    case 5: {
      sb->info.data.update.off1 = (sb->last / 14) * 8;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        sb->last = (sb->last + len) % vs.bufferLength;
      }
    } break;
    case 6: {
      sb->info.data.update.off1 = sb->last * 2;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = 0;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        sb->last = (sb->last + len) % vs.bufferLength;
      }
    } break;
    default:
      break;
    }
  } else {
    switch (sb->smpType) {
    case 5: {
      sb->info.data.update.off1 = (sb->last / 14) * 8;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = cpos;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        sb->last = (sb->last + len) % vs.bufferLength;
      }
    } break;
    case 6: {
      sb->info.data.update.off1 = sb->last * 2;
      sb->info.data.update.len1 = vs.bufferLength - sb->last;
      sb->info.data.update.off2 = 0;
      sb->info.data.update.len2 = cpos;
      if ((len = vs.callback(1, &sb->info)) != 0) {
        sb->last = (sb->last + len) % vs.bufferLength;
      }
    } break;
    default:
      break;
    }
  }
}

/**
 * Per-frame virtual sample service: for each voice playing from a loop buffer it refills played data via
 * vsUpdateBuffer, and once a sample is ending (states 2 and 3) it counts the remaining valid samples
 * and stops the voice when less than one frame's worth is left.
 */
void vsSampleUpdates() {
  u32 i;           // r29
  u32 cpos;        // r27
  u32 realCPos;    // r28
  VS_BUFFER* sb;   // r31
  u32 nextSamples; // r26

  if (vs.callback == NULL) {
    return;
  }

  for (i = 0; i < 64; ++i) {
    if (vs.voices[i] != 0xFF && hwGetVirtualSampleState(i) != 0) {
      sb = &vs.streamBuffer[vs.voices[i]];
      realCPos = hwGetPos(i);
      if (sb->smpType == 5) {
        cpos = (realCPos / 14) * 14;
      } else {
        cpos = realCPos;
      }

      switch (sb->state) {
      case 1:
        vsUpdateBuffer(sb, cpos);
        break;
      case 2:
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 0)
      case 3:
#endif
        if (((sb->info.instID << 8) | sb->voice) == hwGetVirtualSampleID(sb->voice)) {
          vsUpdateBuffer(sb, cpos);

          if (realCPos >= sb->finalLast) {
            sb->finalGoodSamples -= (realCPos - sb->finalLast);
          } else {
            sb->finalGoodSamples -= (vs.bufferLength - (sb->finalLast - realCPos));
          }

          sb->finalLast = realCPos;
          nextSamples = (synthVoice[sb->voice].curPitch * 160 + 0xFFF) / 4096;
          if ((s32)nextSamples > (s32)sb->finalGoodSamples) {
            if (!hwVoiceInStartup(sb->voice)) {
#if MUSY_VERSION >= MUSY_VERSION_CHECK(2, 0, 0)
              if (sb->state == 2) {
                hwBreak(sb->voice);
                macSampleEndNotify(&synthVoice[sb->voice]);
              } else {
                voiceKill(sb->voice);
              }
#else
              hwBreak(sb->voice);
#endif
            }

            sb->state = 0;
            vs.voices[sb->voice] = 0xff;
          }
        } else {
          sb->state = 0;
          vs.voices[sb->voice] = 0xff;
        }
        break;
      }
    }
  }
}
