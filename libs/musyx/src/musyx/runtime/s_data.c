#define _MATH_H_

#include "musyx/assert.h"
#include "musyx/hardware.h"
#include "musyx/s3d.h"
#include "musyx/seq.h"
#include "musyx/synth.h"
#include "musyx/synthdata.h"

typedef struct GSROOT {
  struct GSROOT* next;
  s32 id;
  s16 sp;
  GSTACK stack[128];
  ARAMInfo aramInfo;
} GSROOT;

static GSROOT gsDefault;
static s32 gsUnused;
static GSROOT* gsRoot;
static GSROOT* gsCurrent;
static s32 gsNextID;

/** Resets the sound-group stack: makes the default group root (id -2, empty) own ARAM from aramBase to aramBase +
 * aramSize, ready for sndPushGroup. */
void dataInitStack(unsigned long aramBase, unsigned long aramSize) {
  gsRoot = NULL;
  gsDefault.id = -2;
  gsDefault.sp = 0;
  gsDefault.aramInfo.aramBase = aramBase;
  gsDefault.aramInfo.aramWrite = aramBase;
  gsDefault.aramInfo.aramTop = aramBase + aramSize;
  gsDefault.next = NULL;
  gsRoot = &gsDefault;
  gsNextID = 0;
  gsCurrent = &gsDefault;
}

/** Returns the ARAM allocation info (base, write pointer, top) of the default group. */
ARAMInfo* dataARAMDefaultGetInfo() { return &gsDefault.aramInfo; }

/** Walks a chain of MEM_DATA records (linked by nextOff, ended by 0xFFFFFFFF) and returns the one with the given id, or
 * NULL. */
static inline MEM_DATA* GetPoolAddr(u16 id, MEM_DATA* m) {
  while (m->nextOff != 0xFFFFFFFF) {
    if (m->id == id) {
      return m;
    }

    m = (MEM_DATA*)((u8*)m + m->nextOff);
  }
  return NULL;
}

/** Finds macro id in the pool's macro list; NULL if there is no pool or no such macro. */
static inline MEM_DATA* GetMacroAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->macroOff));
}

/** Finds curve id in the pool's curve list; NULL if there is no pool or no such curve. */
static inline MEM_DATA* GetCurveAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->curveOff));
}
/** Finds keymap id in the pool's keymap list; NULL if there is no pool or no such keymap. */
static inline MEM_DATA* GetKeymapAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->keymapOff));
}
/** Finds layer id in the pool's layer list; NULL if there is no pool or no such layer. */
static inline MEM_DATA* GetLayerAddr(u16 id, POOL_DATA* pool) {
  return pool == NULL ? NULL : GetPoolAddr(id, (MEM_DATA*)((u8*)pool + pool->layerOff));
}

/** Adds one item to, or removes it from, the global data tables. dataType: 0 macro, 1 sample (reference-counted), 2
 * keymap (id | 0x4000), 3 layer (id | 0x8000), 4 curve. When inserting, items missing from the pool are registered as
 * NULL entries. */
void InsertData(u16 id, void* data, u8 dataType, u32 remove) {
  MEM_DATA* m; // r30

  switch (dataType) {
  case 0:
    if (!remove) {
      if ((m = GetMacroAddr(id, data)) != NULL) {
        dataInsertMacro(id, &m->data.cmd);

      } else {
        dataInsertMacro(id, NULL);
      }
    } else {
      dataRemoveMacro(id);
    }
    break;
  case 2: {
    id |= 0x4000;
    if (!remove) {
      if ((m = GetKeymapAddr(id, data)) != NULL) {
        dataInsertKeymap(id, &m->data.map);
      } else {
        dataInsertKeymap(id, NULL);
      }
    } else {
      dataRemoveKeymap(id);
    }
  } break;
  case 3: {
    id |= 0x8000;
    if (!remove) {
      if ((m = GetLayerAddr(id, data)) != NULL) {
        dataInsertLayer(id, &m->data.layer.entry, m->data.layer.num);
      } else {
        dataInsertLayer(id, NULL, 0);
      }
    } else {
      dataRemoveLayer(id);
    }
  } break;
  case 4:
    if (!remove) {
      if ((m = GetCurveAddr(id, data)) != NULL) {
        dataInsertCurve(id, &m->data.tab);
      } else {
        dataInsertCurve(id, NULL);
      }
    } else {
      dataRemoveCurve(id);
    }
    break;
  case 1:
    if (!remove) {
#if 1
      dataAddSampleReference(id, &gsCurrent->aramInfo);
#else
      // TODO
#endif
    } else {
#if 1
      dataRemoveSampleReference(id, &gsCurrent->aramInfo);
#else
      // TODO
#endif
    }
    break;
  }
}

/** Applies InsertData to every ID in a list ended by 0xFFFF. An entry with bit 15 set starts a range: the low 14 bits
 * to the next entry inclusive. */
static inline void ScanIDList(u16* ref, void* data, u8 dataType, u32 remove) {
  u16 id; // r30

  while (*ref != 0xFFFF) {
    if ((*ref & 0x8000)) {
      id = *ref & 0x3fff;
      while (id <= ref[1]) {
        InsertData(id, data, dataType, remove);
        ++id;
      }
      ref += 2;

    } else {
      InsertData(*ref++, data, dataType, remove);
    }
  }
}

/** Same list format as ScanIDList but walks it from the end to the start, so samples are released in the reverse order
 * they were added. */
static inline void ScanIDListReverse(u16* refBase, void* data, u8 dataType, u32 remove) {
  s16 id;
  u16* ref;

  if (*refBase != 0xffff) {
    ref = refBase;
    while (*ref != 0xffff) {
      ref++;
    }
    ref--;

    while (ref >= refBase) {
      if (ref != refBase) {
        if ((ref[-1] & 0x8000) != 0) {
          id = *ref;
          while (id >= (s16)(ref[-1] & 0x3fff)) {
            InsertData(id, data, dataType, remove);
            id--;
          }
          ref -= 2;
        } else {
          InsertData(*ref, data, dataType, remove);
          ref--;
        }
      } else {
        InsertData(*ref, data, dataType, remove);
        ref--;
      }
    }
  }
}

/** Registers every macro in the group's macro ID list, taking the data from pool. */
static inline void InsertMacros(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 0, 0); }

/** Registers every curve in the group's curve ID list, taking the data from pool. */
static inline void InsertCurves(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 4, 0); }

/** Registers every keymap in the group's keymap ID list, taking the data from pool. */
static inline void InsertKeymaps(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 2, 0); }

/** Registers every layer in the group's layer ID list, taking the data from pool. */
static inline void InsertLayers(unsigned short* ref, void* pool) { ScanIDList(ref, pool, 3, 0); }

/** Unregisters every macro in the group's macro ID list. */
static inline void RemoveMacros(unsigned short* ref) { ScanIDList(ref, NULL, 0, 1); }

/** Unregisters every curve in the group's curve ID list. */
static inline void RemoveCurves(unsigned short* ref) { ScanIDList(ref, NULL, 4, 1); }

/** Unregisters every keymap in the group's keymap ID list. */
static inline void RemoveKeymaps(unsigned short* ref) { ScanIDList(ref, NULL, 2, 1); }

/** Unregisters every layer in the group's layer ID list. */
static inline void RemoveLayers(unsigned short* ref) { ScanIDList(ref, NULL, 3, 1); }

/** Registers the sample directory sdir (with its sample data translated by hwTransAddr) and then adds a reference for
 * every sample ID in ref. */
static inline void InsertSamples(u16* ref, void* samples, void* sdir) {
  samples = hwTransAddr(samples);
  if (dataInsertSDir((SDIR_DATA*)sdir, samples)) {
    ScanIDList(ref, sdir, 1, 0);
  }
}

/** Drops the references of every sample ID in ref (last to first) and removes the sample directory. */
static inline void RemoveSamples(unsigned short* ref, void* sdir) {
  ScanIDListReverse(ref, NULL, 1, 1);
  dataRemoveSDir(sdir);
}

/** Registers a song group's sound-effect table under the group ID gid. */
static inline void InsertFXTab(unsigned short gid, FX_DATA* fd) { dataInsertFX(gid, fd->fx, fd->num); }

/** Unregisters the sound-effect table of group gid. */
static inline void RemoveFXTab(unsigned short gid) { dataRemoveFX(gid); }

/** Public: sets the callback that fetches sample data in chunkSize pieces when it is copied to ARAM (see
 * aramStoreData). */
void sndSetSampleDataUploadCallback(void* (*callback)(u32, u32), u32 chunckSize) {
  hwSetSaveSampleCallback(callback, chunckSize);
}

/** Public: loads group gid from the project data prj_data on top of the group stack: registers its samples, macros,
 * curves, keymaps, layers and (for type 1 groups) its sound-effect table, then waits for the ARAM uploads. Returns
 * FALSE if the sound system is off, the stack (128 deep) is full or the group is not found. */
bool sndPushGroup(void* prj_data, u16 gid, void* samples, void* sdir, void* pool) {
  GROUP_DATA* g; // r31
  MUSY_ASSERT_MSG(prj_data != NULL, "Project data pointer is NULL");
  MUSY_ASSERT_MSG(sdir != NULL, "Sample directory pointer is NULL");

  if (sndActive && gsCurrent->sp < 128) {
    g = prj_data;

    while (g->nextOff != 0xFFFFFFFF) {
      if (g->id == gid) {
        gsCurrent->stack[gsCurrent->sp].gAddr = g;
        gsCurrent->stack[gsCurrent->sp].prjAddr = prj_data;
        gsCurrent->stack[gsCurrent->sp].sdirAddr = sdir;
        InsertSamples((u16*)((u8*)prj_data + g->sampleOff), samples, sdir);
        InsertMacros((u16*)((u8*)prj_data + g->macroOff), pool);
        InsertCurves((u16*)((u8*)prj_data + g->curveOff), pool);
        InsertKeymaps((u16*)((u8*)prj_data + g->keymapOff), pool);
        InsertLayers((u16*)((u8*)prj_data + g->layerOff), pool);
        if (g->type == 1) {
          InsertFXTab(gid, (FX_DATA*)((u8*)prj_data + g->data.song.normpageOff));
        }
        hwSyncSampleMem();
        ++gsCurrent->sp;
        return TRUE;
      }

      g = (GROUP_DATA*)((u8*)prj_data + g->nextOff);
    }
  }

  MUSY_DEBUG("Group ID=%d could not be pushed.\n", gid);
  return FALSE;
}

/*










*/
bool sndPopGroup() {
  GROUP_DATA* g;
  SDIR_DATA* sdir;
  void* prj;
  FX_DATA* fd;

  MUSY_ASSERT_MSG(sndActive != FALSE, "Sound system is not initialized.");
  MUSY_ASSERT_MSG(gsCurrent->sp != 0, "Soundstack is empty.");
  g = gsCurrent->stack[--gsCurrent->sp].gAddr;
  prj = gsCurrent->stack[gsCurrent->sp].prjAddr;
  sdir = gsCurrent->stack[gsCurrent->sp].sdirAddr;
  hwDisableIrq();

  if (g->type == 1) {
    fd = (FX_DATA*)((u8*)prj + g->data.song.normpageOff);
    s3dKillEmitterByFXID(fd->fx, fd->num);
  } else {
    seqKillInstancesByGroupID(g->id);
  }

  synthKillVoicesByMacroReferences((u16*)((u8*)prj + g->macroOff));
  synthKillVoicesBySampleReferences((u16*)((u8*)prj + g->sampleOff));
  hwEnableIrq();
  RemoveSamples((u16*)((u8*)prj + g->sampleOff), sdir);
  RemoveMacros((u16*)((u8*)prj + g->macroOff));
  RemoveCurves((u16*)((u8*)prj + g->curveOff));
  RemoveKeymaps((u16*)((u8*)prj + g->keymapOff));
  RemoveLayers((u16*)((u8*)prj + g->layerOff));
  if (g->type == 1) {
    RemoveFXTab(g->id);
  }
  return 1;
}

/*












*/

/** Looks up song group sgid on the stack, finds song sid in its MIDI setup list and starts it with seqStartPlay on the
 * given studio (disabling interrupts around it unless irq_call). Returns the sequence ID, or 0xFFFFFFFF if the group or
 * song is missing or the group is not a song group. */
u32 seqPlaySong(u16 sgid, u16 sid, void* arrfile, SND_PLAYPARA* para, u8 irq_call, u8 studio) {
  int i;
  GROUP_DATA* g;
  PAGE* norm;
  PAGE* drum;
  MIDISETUP* midiSetup;
  GSROOT* root;
  u32 seqId;
  void* prj;
  MUSY_ASSERT_MSG(sndActive != FALSE, "Sound system is not initialized.");

  for (root = gsRoot; root != NULL; root = root->next) {
    for (i = 0; i < root->sp; ++i) {
    if (root->stack[i].gAddr->id != sgid) {
      continue;
    }

    if (root->stack[i].gAddr->type == 0) {
      g = root->stack[i].gAddr;
      prj = root->stack[i].prjAddr;
      norm = (PAGE*)((size_t)prj + g->data.song.normpageOff);
      drum = (PAGE*)((size_t)prj + g->data.song.drumpageOff);
      midiSetup = (MIDISETUP*)((size_t)prj + g->data.song.midiSetupOff);
      while (midiSetup->songId != 0xFFFF) {
        if (midiSetup->songId == sid) {
          if (irq_call != 0) {
            seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
          } else {
            hwDisableIrq();
            seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
            hwEnableIrq();
          }
          return seqId;
        }

        ++midiSetup;
      }

      MUSY_DEBUG("Song ID=%d is not in group ID=%d.", sid, sgid);
      return 0xffffffff;
    } else {
      MUSY_DEBUG("Group ID=%d is no songgroup.", sgid);
      return 0xffffffff;
    }
  }
  }

  MUSY_DEBUG("Group ID=%d is not on soundstack.", sgid);
  seqId = 0xffffffff;
done:
  return seqId;
}

/** Public: starts song sid of song group sgid on the given studio (always with interrupts disabled around
 * seqStartPlay). Returns the sequence ID, or 0xFFFFFFFF if the group or song is not found. */
u32 sndSeqPlayEx(u16 sgid, u16 sid, void* arrfile, SND_PLAYPARA* para, u8 studio) {
  int i;
  u32 seqId;
  GROUP_DATA* g;
  MIDISETUP* midiSetup;
  PAGE* drum;
  PAGE* norm;
  GSROOT* root;
  void* prj;
  for (root = gsRoot; root != NULL; root = root->next) {
    /* FAKE: r steps one GSTACK per i; reproduces the register use of seqPlaySong(.., 0, ..) inlined */
    GSROOT* r;
    for (i = 0, r = root; i < root->sp; r = (GSROOT*)((u8*)r + sizeof(GSTACK)), ++i) {
      if (r->stack[0].gAddr->id != sgid) {
        continue;
      }
      if (root->stack[i].gAddr->type == 0) {
        g = root->stack[i].gAddr;
        prj = root->stack[i].prjAddr;
        norm = (PAGE*)((size_t)prj + g->data.song.normpageOff);
        drum = (PAGE*)((size_t)prj + g->data.song.drumpageOff);
        midiSetup = (MIDISETUP*)((size_t)prj + g->data.song.midiSetupOff);
        while (midiSetup->songId != 0xFFFF) {
          if (midiSetup->songId == sid) {
            hwDisableIrq();
            seqId = seqStartPlay(norm, drum, midiSetup, arrfile, para, studio, sgid);
            hwEnableIrq();
            goto done;
          }
          ++midiSetup;
        }
        seqId = 0xffffffff; goto done;
      } else {
        seqId = 0xffffffff; goto done;
      }
    }
  }
  seqId = 0xffffffff;
done:
  return seqId;
}
