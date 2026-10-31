/* ---------------------------------------








   ---------------------------------------
*/

#include "musyx/musyx.h"

#include "musyx/assert.h"

extern bool ReverbHICreate(_SND_REVHI_WORK* rev, f32 coloration, f32 time, f32 mix, f32 damping,
                           f32 preDelay, f32 crosstalk);
extern void ReverbHIFree(_SND_REVHI_WORK* rev);
extern void ReverbHIModify(_SND_REVHI_WORK* rev, f32 coloration, f32 time, f32 mix, f32 damping,
                           f32 preDelay, f32 crosstalk);
extern void ReverbHICallback(s32* left, s32* right, s32* surround, SND_AUX_REVERBHI* rev);

/** Aux effect callback for the high-quality reverb: on a buffer update it runs ReverbHICallback on the frame's buffers
 * (unless the effect is temporarily disabled); parameter updates are ignored. */
void sndAuxCallbackReverbHI(u8 reason, SND_AUX_INFO* info, void* user) {
  switch (reason) {
  case SND_AUX_REASON_BUFFERUPDATE:
    if (((SND_AUX_REVERBHI*)user)->tempDisableFX == 0) {
      ReverbHICallback(info->data.bufferUpdate.left, info->data.bufferUpdate.right,
                       info->data.bufferUpdate.surround, (SND_AUX_REVERBHI*)user);
    }

    break;
  case SND_AUX_REASON_PARAMETERUPDATE:
    break;
  default:
    MUSY_ASSERT(FALSE);
    break;
  }
}

/** Applies changed settings of the high-quality reverb through ReverbHIModify, with the effect muted meanwhile. Returns
 * TRUE. */
bool sndAuxCallbackUpdateSettingsReverbHI(SND_AUX_REVERBHI* rev) {
  rev->tempDisableFX = TRUE;
  ReverbHIModify(&rev->rv, rev->coloration, rev->time, rev->mix, rev->damping, rev->preDelay,
                 rev->crosstalk);
  rev->tempDisableFX = FALSE;
  return TRUE;
}

/** Creates the high-quality reverb from the user's settings (coloration, time, mix, damping, pre-delay, crosstalk).
 * Returns FALSE if the settings are out of range. */
bool sndAuxCallbackPrepareReverbHI(SND_AUX_REVERBHI* rev) {
  rev->tempDisableFX = FALSE;
  return ReverbHICreate(&rev->rv, rev->coloration, rev->time, rev->mix, rev->damping, rev->preDelay,
                        rev->crosstalk);
}

/** Frees the high-quality reverb. Returns TRUE. */
bool sndAuxCallbackShutdownReverbHI(SND_AUX_REVERBHI* rev) {
  ReverbHIFree(&rev->rv);
  return TRUE;
}
