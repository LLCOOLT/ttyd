
#include "musyx/musyx.h"

#include "musyx/assert.h"
#include "musyx/hardware.h"
#include "musyx/macros.h"
#include "musyx/stream.h"
#include "musyx/voice.h"

void voiceResetLastStarted(SYNTH_VOICE* svoice);

static VID_LIST vidList[128];
static u8 synth_last_started[8][16];
static u8 synth_last_fxstarted[64];
SYNTH_VOICELIST voiceList[64];
SYNTH_ROOTLIST voicePrioSortRootList[256];
u8 voicePrioSortVoicesRoot[256];
SYNTH_VOICELIST voicePrioSortVoices[64];
static VID_LIST* vidFree = NULL;
static VID_LIST* vidRoot = NULL;
static u32 vidCurrentId = 0;
u16 voicePrioSortRootListRoot = 0;
u8 voiceMusicRunning = 0;
u8 voiceFxRunning = 0;
u8 voiceListInsert = 0;
u8 voiceListRoot = 0;

/** Resets the voice ID system: builds the free list of 128 VID_LIST entries and restarts the ID counter. A "voice ID"
 * is the public handle the game holds; it maps to a chain of internal voices (layers and legato retunes). */
void vidInit() {
  int i;
  VID_LIST* lvl;
  vidCurrentId = 0;
  vidRoot = NULL;
  vidFree = vidList;
  for (lvl = NULL, i = 0; i < 128; lvl = &vidList[i], ++i) {
    vidList[i].prev = lvl;
    if (lvl != NULL) {
      lvl->next = &vidList[i];
    }
  }
  lvl->next = NULL;
}

/** Finds the VID_LIST entry for voice ID vid in the sorted list, or NULL. */
static inline VID_LIST* get_vidlist(u32 vid) {
  VID_LIST* vl = vidRoot;
  while (vl != NULL) {
    if (vl->vid == vid) {
      return vl;
    }
    if (vl->vid > vid) {
      break;
    }
    vl = vl->next;
  }

  return NULL;
}

/** Returns the next voice ID, skipping 0xFFFFFFFF (reserved for "none"). */
static inline u32 get_newvid() {
  u32 vid; // r31
  do {
    vid = vidCurrentId++;
  } while (vid == 0xFFFFFFFF);

  return vid;
}

/** Unlinks a VID_LIST entry, puts it back on the free list and sets the caller's pointer to NULL. */
static inline void vidRemove(VID_LIST** vidList) {
  if ((*vidList)->prev != NULL) {
    (*vidList)->prev->next = (*vidList)->next;
  } else {
    vidRoot = (*vidList)->next;
  }

  if ((*vidList)->next != NULL) {
    (*vidList)->next->prev = (*vidList)->prev;
  }

  (*vidList)->next = vidFree;

  if (vidFree != NULL) {
    vidFree->prev = *vidList;
  }

  (*vidList)->prev = NULL;
  vidFree = *vidList;
  *vidList = NULL;
}

/** Detaches a voice from the voice ID tables before it is reused: unlinks it from its parent/child chain and frees its
 * ID entry (the child becomes the new chain root when the root voice is removed). */
void vidRemoveVoiceReferences(SYNTH_VOICE* svoice) {
  if (svoice->id == 0xFFFFFFFF) {
    return;
  }

  voiceResetLastStarted(svoice);
  if (svoice->parent != 0xFFFFFFFF) {
    synthVoice[svoice->parent & 0xFF].child = svoice->child;
    if (svoice->child != 0xFFFFFFFF) {
      synthVoice[svoice->child & 0xFF].parent = svoice->parent;
    }

    vidRemove(&svoice->vidList);
  } else if (svoice->child != 0xFFFFFFFF) {
    svoice->vidList->root = svoice->child;
    if (svoice->vidList != svoice->vidMasterList) {
      svoice->vidMasterList->root = svoice->child;
    }
    synthVoice[svoice->child & 0xFF].parent = 0xFFFFFFFF;
    synthVoice[svoice->child & 0xFF].vidMasterList = svoice->vidMasterList;
    if (svoice->vidList != svoice->vidMasterList) {
      vidRemove(&svoice->vidList);
    }

    svoice->vidMasterList = svoice->vidList = NULL;
  } else if (svoice->vidList != svoice->vidMasterList) {
    vidRemove(&svoice->vidList);
    vidRemove(&svoice->vidMasterList);
  } else {
    vidRemove(&svoice->vidList);
    svoice->vidMasterList = NULL;
  }
}

/** Makes the voice's ID entry the master one (the handle the game keeps) and returns the voice ID. */
u32 vidMakeRoot(SYNTH_VOICE* svoice) {
  svoice->vidMasterList = svoice->vidList;
  return svoice->vidList->vid;
}

/** Creates a new voice ID entry for a voice (IDs stay unique and the list sorted). Returns the public voice ID if
 * isMaster, otherwise the voice's internal ID, or 0xFFFFFFFF if no entry is free. */
u32 vidMakeNew(SYNTH_VOICE* svoice, u32 isMaster) {
  u32 vid;       // r29
  VID_LIST* nvl; // r30
  VID_LIST* lvl; // r28
  VID_LIST* vl;  // r31

  vid = get_newvid();
_restart:
  lvl = NULL;
  nvl = vidRoot;

  while (nvl != NULL) {
    if (nvl->vid > vid) {
      break;
    }

    if (nvl->vid == vid) {
      vid = get_newvid();
      if (vid < nvl->vid) {
        goto _restart;
      }
    }

    lvl = nvl;
    nvl = nvl->next;
  }

  if ((vl = vidFree) == NULL) {
    return 0xFFFFFFFF;
  }

  if ((vidFree = vidFree->next) != NULL) {
    vidFree->prev = NULL;
  }

  if (lvl == NULL) {
    vidRoot = vl;
  } else {
    lvl->next = vl;
  }

  vl->prev = lvl;
  vl->next = nvl;

  if (nvl != NULL) {
    nvl->prev = vl;
  }

  vl->vid = vid;
  vl->root = svoice->id;
  svoice->vidMasterList = isMaster ? vl : NULL;
  svoice->vidList = vl;

  return isMaster ? vid : svoice->id;
}

/** Converts a public voice ID to the internal ID of the first voice of its chain; 0xFFFFFFFF if unknown. */
u32 vidGetInternalId(u32 vid) {
  VID_LIST* vl;

  if (vid != 0xffffffff) {
    if ((vl = get_vidlist(vid)) != NULL) {
      return vl->root;
    }
  }

  return 0xffffffff;
}

/** Finds the public voice ID of the chain that contains the internal voice ID vid; 0xFFFFFFFF if none. */
u32 vidGetPublicId(u32 vid) {
  VID_LIST* vl;
  u32 id;

  for (vl = vidRoot; vl != NULL; vl = vl->next) {
    for (id = vl->root; id != 0xFFFFFFFF; id = synthVoice[id & 0xFF].child) {
      if (id == vid) {
        return vl->vid;
      }
    }
  }

  return 0xFFFFFFFF;
}

/** Clears the per-priority lists (256 priority levels) that order running voices by priority. */
static inline void voiceInitPrioSort() {
  u32 i;

  for (i = 0; i < synthInfo.voiceNum; ++i) {
    voicePrioSortVoices[i].user = 0;
  }

  for (i = 0; i < 256; ++i) {
    voicePrioSortVoicesRoot[i] = 0xff;
  }

  voicePrioSortRootListRoot = 0xffff;
}

/** Removes a voice from the priority-sorted lists, also dropping its priority level from the list of levels when it was
 * the last voice of that level. */
inline void voiceRemovePriority(SYNTH_VOICE* svoice) {
  SYNTH_VOICELIST* vps; // r31
  SYNTH_ROOTLIST* rps;  // r30

  vps = &voicePrioSortVoices[svoice->id & 0xFF];
  if (vps->user != 1) {
    return;
  }

  if (vps->prev != 0xFF) {
    voicePrioSortVoices[vps->prev].next = vps->next;
  } else {
    voicePrioSortVoicesRoot[svoice->prio] = vps->next;
  }

  if (vps->next != 0xFF) {
    voicePrioSortVoices[vps->next].prev = vps->prev;
  } else if (vps->prev == 0xFF) {
    rps = &voicePrioSortRootList[svoice->prio];

    if (rps->prev != 0xFFFF) {
      voicePrioSortRootList[rps->prev].next = rps->next;

    } else {
      voicePrioSortRootListRoot = rps->next;
    }

    if (rps->next != 0xFFFF) {
      voicePrioSortRootList[rps->next].prev = rps->prev;
    }
  }

  vps->user = 0;
}

/** Places a voice in the priority-sorted lists at the given priority (taking it out of its old level) and tells the DSP
 * its priority and age. */
void voiceSetPriority(SYNTH_VOICE* svoice, u8 prio) {
  u16 li;               // r25
  SYNTH_VOICELIST* vps; // r27
  u16 i;                // r29
  u32 v;                // r26
  v = (u8)svoice->id;
  vps = &voicePrioSortVoices[v];
  if (vps->user == 1) {
    if (svoice->prio == prio) {
      return;
    }

    voiceRemovePriority(svoice);
  }

  vps->user = 1;
  vps->prev = 0xff;
  if ((vps->next = voicePrioSortVoicesRoot[prio]) != 0xFF) {
    voicePrioSortVoices[voicePrioSortVoicesRoot[prio]].prev = v;
  } else if (voicePrioSortRootListRoot != 0xFFFF) {
    if (prio >= voicePrioSortRootListRoot) {
      for (i = voicePrioSortRootListRoot; i != 0xFFFF; i = voicePrioSortRootList[i].next) {
        if ((u16)i > prio) {
          break;
        }
        li = i;
      }

      voicePrioSortRootList[li].next = (u16)prio;
      voicePrioSortRootList[prio].prev = li;
      voicePrioSortRootList[prio].next = i;
      if (i != 0xFFFF) {
        voicePrioSortRootList[i].prev = prio;
      }

    } else {
      voicePrioSortRootList[prio].next = voicePrioSortRootListRoot;
      voicePrioSortRootList[prio].prev = 0xFFFF;
      voicePrioSortRootList[voicePrioSortRootListRoot].prev = prio;
      voicePrioSortRootListRoot = prio;
    }
  } else {
    voicePrioSortRootList[prio].next = 0xFFFF;
    voicePrioSortRootList[prio].prev = 0xFFFF;
    voicePrioSortRootListRoot = prio;
  }

  voicePrioSortVoicesRoot[prio] = v;
  svoice->prio = prio;
  hwSetPriority(svoice->id & 0xFF, ((u32)prio << 24) | (svoice->age >> 15));
}

/** Chooses a voice to start a new sound. If the sound's group (allocId) already uses maxVoices voices the oldest lower
 * priority one of the group is stolen; otherwise a free voice is used, and if none is free the oldest voice with equal
 * or lower priority (of the same music/effect kind when that class is over its quota) is stolen. Returns the voice
 * index or -1. */
static s32 voiceAllocateFind(u8 priority, u8 maxVoices, u32 allocId, u8 fxFlag) {
  s32 i;
  s32 num;
  s32 voice;
  u16 p;
  u32 type_alloc;

  if (!synthIdleWaitActive) {
    if (fxFlag) {
      type_alloc = (voiceFxRunning >= synthInfo.maxSFX && synthInfo.voiceNum > synthInfo.maxSFX);

      if (synthInfo.maxSFX <= maxVoices) {
        goto _skip_alloc;
      }
    } else {
      type_alloc =
          (voiceMusicRunning >= synthInfo.maxMusic && synthInfo.voiceNum > synthInfo.maxMusic);

      if (synthInfo.maxMusic <= maxVoices) {
        goto _skip_alloc;
      }
    }

    num = 0;
    voice = -1;

    p = voicePrioSortRootListRoot;
    while (p != 0xFFFF && priority >= p && voice == -1) {
      for (i = voicePrioSortVoicesRoot[p]; i != 0xff; i = voicePrioSortVoices[i].next) {
        if (allocId != synthVoice[i].allocId)
          continue;
        ++num;
        if (synthVoice[i].block)
          continue;

        if (!type_alloc || fxFlag == synthVoice[i].fxFlag) {
          if ((synthVoice[i].cFlags & 2))
            continue;
          if (voice != -1) {
            if (synthVoice[i].age < synthVoice[voice].age)
              voice = i;
          } else
            voice = i;
        }
      }

      p = voicePrioSortRootList[p].next;
    }

    if (num >= maxVoices) {
      return voice;
    }

    while (p != 0xffff && num < maxVoices) {
      i = voicePrioSortVoicesRoot[p];
      while (i != 0xff) {
        if (allocId == synthVoice[i].allocId) {
          num++;
        }

        i = voicePrioSortVoices[i].next;
      }

      p = voicePrioSortRootList[p].next;
    }

    if (num >= maxVoices) {
      return voice;
    }

  _skip_alloc:
    if (voiceListRoot != 0xff && type_alloc == 0) {
      return voiceListRoot;
    }

    if (priority < voicePrioSortRootListRoot) {
      return -1;
    }

    voice = -1;
    p = voicePrioSortRootListRoot;

    while (p != 0xFFFF && priority >= p && voice == -1) {
      for (i = voicePrioSortVoicesRoot[p]; i != 0xff; i = voicePrioSortVoices[i].next) {
        if (synthVoice[i].block != 0)
          continue;

        if (!type_alloc || fxFlag == synthVoice[i].fxFlag) {
          if ((synthVoice[i].cFlags & 2))
            continue;
          if (voice != -1) {
            if (synthVoice[voice].age > synthVoice[i].age)
              voice = i;
          } else
            voice = i;
        }
      }
      p = voicePrioSortRootList[p].next;
    }

    if (voice == -1) {
      return -1;
    }

    if (synthVoice[voice].prio > priority) {
      goto _fail;
    }

    return voice;
  }

_fail:
  return -1;
}

/** Allocates a voice with voiceAllocateFind: takes it off the free list (or counts the stolen voice out of its old
 * class) and counts it in the music or effect class. Returns the voice index or -1. */
u32 voiceAllocate(u8 priority, u8 maxVoices, u32 allocId, u8 fxFlag) {
  s32 voice;
  SYNTH_VOICELIST* sfv;
  s32 i;

  voice = voiceAllocateFind(priority, maxVoices, allocId, fxFlag);
  if (voice != -1) {
    if (voiceList[voice].user == 1) {
      sfv = voiceList + voice;
      i = sfv->prev;

      if (i != 0xff) {
        voiceList[i].next = sfv->next;
      } else {
        voiceListRoot = sfv->next;
      }

      i = sfv->next;
      if (i != 0xff) {
        voiceList[i].prev = sfv->prev;
      }

      if (voice == voiceListInsert) {
        voiceListInsert = sfv->prev;
      }

      sfv->user = 0;
    } else if (synthVoice[voice].fxFlag) {
      voiceFxRunning--;
    } else {
      voiceMusicRunning--;
    }
    if (fxFlag != FALSE) {
      ++voiceFxRunning;
    } else {
      ++voiceMusicRunning;
    }
  }
  return voice;
}

/** Like voiceAllocate but changes nothing: returns 1 and the allocation group of the voice that would be stolen in
 * *currentAllocId, or 0 if a free voice or none would be used. */
int voiceAllocatePeek(u8 priority, u8 maxVoices, u32 allocId, u8 fxFlag, u32* currentAllocId) {
  s32 voice = voiceAllocateFind(priority, maxVoices, allocId, fxFlag);

  if (voice == -1) {
    return 0;
  }
  if (voiceList[voice].user == 1) {
    return 0;
  }
  *currentAllocId = synthVoice[voice].allocId;
  return 1;
}

/** Releases a voice: stops its macro, removes it from the priority lists, returns it to the free list and updates the
 * music/effect voice counts. */
void voiceFree(SYNTH_VOICE* svoice) {
  u32 i;                // r29
  SYNTH_VOICELIST* sfv; // r30
  MUSY_ASSERT(svoice->id != 0xFFFFFFFF);
  macMakeInactive(svoice, MAC_STATE_STOPPED);
  voiceRemovePriority(svoice);
  svoice->addr = NULL;
  svoice->prio = 0;
  sfv = &voiceList[(i = svoice->id & 0xFF)];
  if (sfv->user == 0) {
    sfv->user = 1;
    if (voiceListRoot != 0xFF) {
      sfv->next = 0xFF;
      sfv->prev = voiceListInsert;
      voiceList[voiceListInsert].next = i;
    } else {
      sfv->next = 0xFF;
      sfv->prev = 0xFF;
      voiceListRoot = i;
    }

    voiceListInsert = i;
    if (svoice->fxFlag != 0) {
      --voiceFxRunning;
    } else {
      --voiceMusicRunning;
    }
  }

  svoice->id = 0xFFFFFFFF;
}

/** Links all synth voices into the free list. */
static inline void voiceInitFreeList() {
  u32 i; // r31

  for (i = 0; i < synthInfo.voiceNum; ++i) {
    voiceList[i].prev = i - 1;
    voiceList[i].next = i + 1;
    voiceList[i].user = 1;
  }

  voiceList[0].prev = 0xff;
  voiceList[synthInfo.voiceNum - 1].next = 0xff;
  voiceListRoot = 0;
  voiceListInsert = synthInfo.voiceNum - 1;
}

/** Initializes the free list, the priority lists and the running voice counters. */
void synthInitAllocationAids() {
  voiceInitFreeList();
  voiceInitPrioSort();
  voiceFxRunning = 0;
  voiceMusicRunning = 0;
}

/** Reserves a voice for exclusive use (a stream) at priority prio: allocates it as an effect voice, stops whatever it
 * played and marks it blocked so the synth jobs skip it. Returns the voice index or 0xFFFFFFFF. */
u32 voiceBlock(u8 prio) {
  u32 voice;

  if ((voice = voiceAllocate(prio, 0xFF, 0xFFFF, 1)) != 0xFFFFFFFF) {
    synthVoice[voice].block = 1;
    synthVoice[voice].fxFlag = 1;

#if MUSY_VERSION >= MUSY_VERSION_CHECK(1, 5, 4)
    synthVoice[voice].allocId = 0xFFFFFFFF;
#endif

    vidRemoveVoiceReferences(&synthVoice[voice]);
    synthVoice[voice].id = voice | 0xFFFFFF00;

    if (hwIsActive(voice)) {
      hwBreak(voice);
    }

    macMakeInactive(&synthVoice[voice], MAC_STATE_STOPPED);
    synthVoice[voice].addr = NULL;
    voiceSetPriority(&synthVoice[voice], prio);
  }

  return voice;
}

/** Gives a blocked voice back: stops the DSP voice, frees it and clears the blocked flag. */
void voiceUnblock(u32 voice) {
  if (voice == 0xFFFFFFFF) {
    return;
  }

  if (hwIsActive(voice)) {
    hwBreak(voice);
  }

  synthVoice[voice].id = voice;
  voiceFree(&synthVoice[voice]);
  synthVoice[voice].block = 0;
}

/** Kills voice vi: detaches its ID, frees it, stops the stream if it was blocked for one and breaks the DSP voice. */
void voiceKill(u32 vi) {
  SYNTH_VOICE* sv = &synthVoice[vi]; // r31
  if (sv->addr != NULL) {
    vidRemoveVoiceReferences(sv);
    sv->cFlags &= ~3;
    sv->age = 0;
    voiceFree(sv);
  }

  if (sv->block != 0) {
    streamKill(vi);
  }

  hwBreak(vi);
}

/** Kills every voice of the chain behind a public voice ID; returns 0 if a voice was killed, -1 otherwise. */
s32 voiceKillSound(u32 voiceid) {
  s32 ret = -1;     // r29
  u32 next_voiceid; // r28
  u32 i;            // r30
  if (sndActive != FALSE) {
    for (voiceid = vidGetInternalId(voiceid); voiceid != -1; voiceid = next_voiceid) {
      i = voiceid & 0xff;
      next_voiceid = synthVoice[i].child;
      if (voiceid == synthVoice[i].id) {
        voiceKill(i);
        ret = 0;
      }
    }
  }

  return ret;
}

/** Kills all voices, or with musiconly set only the music voices (plus voices not running a macro). */
void synthKillAllVoices(unsigned char musiconly) {
  u32 i;

  for (i = 0; i < synthInfo.voiceNum; ++i) {
    if (synthVoice[i].addr != NULL) {
      if (musiconly == 0 || (musiconly != 0 && synthVoice[i].fxFlag == 0)) {
        voiceKill(i);
      }
    } else {
      voiceKill(i);
    }
  }
}

/** Kills voices that are not running a macro and every voice running one of the macros in the 0xFFFF-terminated ID list
 * ref (with ranges flagged by bit 15); used before unloading a group. */
void synthKillVoicesByMacroReferences(u16* ref) {
  u32 i;  // r31
  u16 id; // r29

  for (i = 0; i < synthInfo.voiceNum; ++i) {
    if (synthVoice[i].addr == NULL && synthVoice[i].block == 0) {
      voiceKill(i);
    }
  }

  while (*ref != 0xFFFF) {
    if ((*ref & 0x8000)) {
      id = *ref & 0x3fff;
      while (id <= ref[1]) {
        for (i = 0; i < synthInfo.voiceNum; ++i) {
          if (synthVoice[i].addr != NULL && id == synthVoice[i].macroId) {
            voiceKill(i);
          }
        }
        ++id;
      }
      ref += 2;
    } else {
      for (i = 0; i < synthInfo.voiceNum; ++i) {
        if (synthVoice[i].addr != NULL && *ref == synthVoice[i].macroId) {
          voiceKill(i);
        }
      }
      ++ref;
    }
  }
}

/** Kills voices that are not running a macro and every voice playing one of the samples in the ID list ref; used before
 * unloading a group. */
void synthKillVoicesBySampleReferences(u16* ref) {
  u32 i;
  u16 id;

  for (i = 0; i < synthInfo.voiceNum; ++i) {
    if (synthVoice[i].addr == NULL && synthVoice[i].block == 0) {
      voiceKill(i);
    }
  }

  while (*ref != 0xFFFF) {
    if ((*ref & 0x8000)) {
      id = *ref & 0x3fff;
      while (id <= ref[1]) {
        for (i = 0; i < synthInfo.voiceNum; ++i) {
          if (synthVoice[i].addr != NULL && id == synthVoice[i].sampleId) {
            voiceKill(i);
          }
        }
        ++id;
      }
      ref += 2;
    } else {
      for (i = 0; i < synthInfo.voiceNum; ++i) {
        if (synthVoice[i].addr != NULL && *ref == synthVoice[i].sampleId) {
          voiceKill(i);
        }
      }
      ++ref;
    }
  }
}

/** Returns TRUE if the voice is the most recently started one on its MIDI channel (or sound effect slot); portamento
 * uses this. */
u32 voiceIsLastStarted(SYNTH_VOICE* svoice) {
  u32 i; // r31

  if (svoice->id != 0xFFFFFFFF && svoice->midi != 0xFF) {
    i = svoice->id & 0xFF;
    if (svoice->midiSet == 0xFF) {
      if (synth_last_fxstarted[i] == i) {
        return TRUE;
      }
    } else if (synth_last_started[svoice->midiSet][svoice->midi] == i) {
      return TRUE;
    }
  }

  return FALSE;
}

/** Records the voice as the latest one started on its MIDI channel (or effect slot). */
void voiceSetLastStarted(SYNTH_VOICE* svoice) {
  u32 i; // r31

  if (svoice->id != 0xFFFFFFFF && svoice->midi != 0xFF) {
    i = svoice->id & 0xFF;
    if (svoice->midiSet == 0xFF) {
      synth_last_fxstarted[i] = i;
    } else {
      synth_last_started[svoice->midiSet][svoice->midi] = i;
    }
  }
}

/** Forgets the voice as the latest started one of its channel if it is. */
void voiceResetLastStarted(struct SYNTH_VOICE* svoice) {
  u32 i;

  if ((svoice->id != 0xffffffff) && (svoice->midi != 0xff)) {
    i = svoice->id & 0xff;
    if (svoice->midiSet == 0xff) {
      if (synth_last_fxstarted[i] == i) {
        synth_last_fxstarted[i] = 0xff;
      }
    } else if (i == synth_last_started[svoice->midiSet][svoice->midi]) {
      synth_last_started[svoice->midiSet][svoice->midi] = 0xff;
    }
  }
}

/** Clears the latest-started voice for all MIDI channels and effect slots. */
void voiceInitLastStarted() {
  u32 i;
  u32 j;

  for (i = 0; i < 8; ++i) {
    for (j = 0; j < 16; ++j) {
      synth_last_started[i][j] = 0xFF;
    }
  }

  for (j = 0; j < 64; ++j) {
    synth_last_fxstarted[j] = 0xFF;
  }
}
