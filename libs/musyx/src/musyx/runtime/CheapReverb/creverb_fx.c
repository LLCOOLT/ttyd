/* ---------------------------------------








   ---------------------------------------
*/

#include "musyx/musyx.h"

#include "musyx/assert.h"

// The standard reverb in creverb.c; no MusyX header declares these.
extern bool ReverbSTDCreate(_SND_REVSTD_WORK* rv, f32 coloration, f32 time, f32 mix, f32 damping,
                            f32 preDelay);
extern void ReverbSTDFree(_SND_REVSTD_WORK* rev);
extern void ReverbSTDCallback(s32* left, s32* right, s32* surround, _SND_REVSTD_WORK* rv);
extern unsigned long ReverbSTDModify(_SND_REVSTD_WORK* rv, float coloration, float time, float mix,
                                     float damping, float predelay);

/** Aux effect callback for the standard reverb: on a buffer update it runs the reverb on the frame's buffers (unless
 * the effect is temporarily disabled); parameter updates are not implemented. */
void sndAuxCallbackReverbSTD(u8 reason, SND_AUX_INFO* info, void* user) {
  switch (reason) {
  case SND_AUX_REASON_BUFFERUPDATE:
    if ((u8)((SND_AUX_REVERBSTD*)user)->tempDisableFX == 0) {
      ReverbSTDCallback(info->data.bufferUpdate.left, info->data.bufferUpdate.right,
                        info->data.bufferUpdate.surround, &((SND_AUX_REVERBSTD*)user)->rv);
    }
    break;
  case SND_AUX_REASON_PARAMETERUPDATE:
    // UNIMPLEMENTED
    break;
  default:
    MUSY_ASSERT(FALSE);
    break;
  }
}
/** Applies changed settings of a standard reverb by rebuilding it, with the effect muted meanwhile. Returns TRUE. */
bool sndAuxCallbackUpdateSettingsReverbSTD(SND_AUX_REVERBSTD* rev) {
  rev->tempDisableFX = TRUE;
  ReverbSTDModify(&rev->rv, rev->coloration, rev->time, rev->mix, rev->damping, rev->preDelay);
  rev->tempDisableFX = FALSE;
  return TRUE;
}

/** Creates the standard reverb from the user's settings (coloration, time, mix, damping, pre-delay). Returns FALSE if
 * the settings are out of range. */
bool sndAuxCallbackPrepareReverbSTD(SND_AUX_REVERBSTD* rev) {
  rev->tempDisableFX = 0;
  return ReverbSTDCreate(&rev->rv, rev->coloration, rev->time, rev->mix, rev->damping,
                         rev->preDelay);
}
/** Frees the standard reverb. Returns TRUE. */
bool sndAuxCallbackShutdownReverbSTD(SND_AUX_REVERBSTD* rev) {
  ReverbSTDFree(&rev->rv);
  return TRUE;
}
