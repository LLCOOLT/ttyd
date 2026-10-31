#include <dolphin.h>
#include <dolphin/os.h>

#define ROUND(n, a) (((u32)(n) + (a)-1) & ~((a)-1))
#define TRUNC(n, a) (((u32)(n)) & ~((a)-1))

/** Top of the arena, the free memory the OS has not handed out yet. */
static void* __OSArenaHi;
/** Bottom of the arena; -1 until OSInit sets it, which the getters assert on. */
static void* __OSArenaLo = (void*)-1;

/** Returns the top of the arena, the end of the memory the OS has not handed out yet. */
void* OSGetArenaHi(void) {
    ASSERTMSGLINE(55, (u32)__OSArenaLo != -1, "OSGetArenaHi(): OSInit() must be called in advance.");
    ASSERTMSGLINE(57, (u32)__OSArenaLo <= (u32)__OSArenaHi, "OSGetArenaHi(): invalid arena (hi < lo).");
    return __OSArenaHi;
}

/** Returns the bottom of the arena, the first free address after the program image and stack. */
void* OSGetArenaLo(void) {
    ASSERTMSGLINE(73, (u32)__OSArenaLo != -1, "OSGetArenaLo(): OSInit() must be called in advance.");
    ASSERTMSGLINE(75, (u32)__OSArenaLo <= (u32)__OSArenaHi, "OSGetArenaLo(): invalid arena (hi < lo).");
    return __OSArenaLo;
}

/** Sets the top of the arena. */
void OSSetArenaHi(void* newHi) {
    __OSArenaHi = newHi;
}

/** Sets the bottom of the arena. */
void OSSetArenaLo(void* newLo) {
    __OSArenaLo = newLo;
}

/**
 * Carves size bytes off the bottom of the arena, aligning both the start and the new arena bottom to align,
 * and returns the block.
 */
void* OSAllocFromArenaLo(u32 size, u32 align) {
  void* ptr;
  u8* arenaLo;

  ptr = OSGetArenaLo();
  arenaLo = ptr = (void*)ROUND(ptr, align);
  arenaLo += size;
  arenaLo = (u8*)ROUND(arenaLo, align);
  OSSetArenaLo(arenaLo);
  return ptr;
}

/** Carves size bytes off the top of the arena, aligning the new arena top down to align, and returns the block. */
void* OSAllocFromArenaHi(u32 size, u32 align) {
  void* ptr;
  u8* arenaHi;

  arenaHi = OSGetArenaHi();
  arenaHi = (u8*)TRUNC(arenaHi, align);
  arenaHi -= size;
  arenaHi = ptr = (void*)TRUNC(arenaHi, align);
  OSSetArenaHi(arenaHi);
  return ptr;
}
