#ifndef _MUSYX_S3D_KEY
#define _MUSYX_S3D_KEY

#include "musyx/musyx.h"

/* start key of an emitter: value of its 0x8000 parameter, 0xff if none (snd3d.c) */
static inline u8 s3dGetEmitterKey(SND_EMITTER* em) {
  u8 i;
  SND_PARAMETER* pPtr;
  if (em->paraInfo == NULL) {
    return 0xff;
  }
  pPtr = em->paraInfo->paraArray;
  for (i = 0; i < em->paraInfo->numPara; ++pPtr, ++i) {
    if (pPtr->ctrl == 0x8000) {
      return pPtr->paraData.value7;
    }
  }
  return 0xff;
}

#endif
