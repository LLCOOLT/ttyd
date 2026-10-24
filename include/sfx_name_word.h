#pragma once

#include <dolphin/types.h>

/* A sound name parameter takes a name or an id. Names are addresses in main
 * memory (0x80000000 and up); a word that is non-negative as an s32 is an id
 * and is used as the index directly. SfxNameWord is that name-or-id word.
 *
 * SFX_NAME_WORD(x) passes an id, or a name literal through the word: for a
 * literal it is the same pointer, but the compiler then treats the address as
 * a loop-invariant word and loads it once (an @ temp), which is the shape
 * some callers were compiled with. */
typedef u32 SfxNameWord;
#define SFX_NAME_WORD(lit) ((const char*)(SfxNameWord)(lit))
/* the id a name parameter holds, when SFX_NAME_IS_ID (a direct s32 cast: the
 * SfxNameWord round trip changes register allocation in psndENVSearch) */
#define SFX_NAME_ID(name) ((s32)(name))
#define SFX_NAME_IS_ID(name) (SFX_NAME_ID(name) >= 0)
