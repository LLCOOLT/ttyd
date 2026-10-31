/* Build stamp object linked ahead of system.o: owns the first 0x18 bytes of .rodata
   (0x802C0F20-0x802C0F38). Splitting it out moves system.c's .rodata to 0x802C0F38, so
   MWCC anchors system.c's float/double pool there, as in the target. */
#if defined(VERSION_G8MP01)
const char R_build_date[] = "Sep 26 2004";
const char R_build_time[] = "15:37:03";
#elif defined(VERSION_G8ME01)
const char R_build_date[] = "Sep  9 2004";
const char R_build_time[] = "09:34:02";
#else
const char R_build_date[] = "Jun 17 2004";
const char R_build_time[] = "17:20:01";
#endif
