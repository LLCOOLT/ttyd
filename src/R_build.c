/* Build stamp object linked ahead of system.o: owns the first 0x18 bytes of .rodata
   (0x802C0F20-0x802C0F38). Splitting it out moves system.c's .rodata to 0x802C0F38, so
   MWCC anchors system.c's float/double pool there, as in the target. */
#include "version.h"
#if VERSION >= VERSION_DEMO_EU
/** Build date of the EU version (26 September 2004), the stamp kept as build info. */
const char R_build_date[] = "Sep 26 2004";
/** Build time of the EU version (15:37:03). */
const char R_build_time[] = "15:37:03";
#elif VERSION >= VERSION_US
/** Build date of the US version (9 September 2004), the stamp kept as build info. */
const char R_build_date[] = "Sep  9 2004";
/** Build time of the US version (09:34:02). */
const char R_build_time[] = "09:34:02";
#else
/** Build date of the Japanese release and both demos (17 June 2004), the stamp kept as build info. */
const char R_build_date[] = "Jun 17 2004";
/** Build time of the Japanese release and both demos (17:20:01). */
const char R_build_time[] = "17:20:01";
#endif
