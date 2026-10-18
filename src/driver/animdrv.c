// G5 keepall: asm stopgap reaches data via section-relative relocs; keep it from being stripped
#pragma force_active on
/*
 * Warning, inlining hell
 */
#include "driver/animdrv.h"
#include "driver/dispdrv.h"
#include "driver/mapdrv.h"
#include "mario/mariost.h"
#include "memory.h"
#include "system.h"

#include <stdio.h>

#include <string.h>
extern const char str_802C2A98[];
extern const char str_802C2AA4[];
extern const char str_802C2AB4[];
extern const char str_802C2AC4[];
extern const char str_802C2AD4[];
extern const char str_802C2AE4[];
extern const char str_802C2AF4[];
extern const char str_802C2B04[];
extern const char str_802C2B14[];
extern const char str_802C2B24[];
extern const char str_802C2B34[];
extern const char str_802C2B44[];
extern const char str_802C2B54[];
extern const char str_802C2B64[];
extern const char str_802C2B74[];
extern const char str_802C2B84[];
extern const char str_802C2B94[];
extern const char str_802C2BA4[];
extern const char str_802C2BB4[];
extern const char str_802C2BC4[];
extern const char str_802C2BD4[];
extern const char str_802C2BE4[];
extern const char str_802C2BF4[];
extern const char str_802C2C04[];
extern const char str_802C2C18[];
extern const char str_802C2C2C[];
extern const char str_802C2C40[];
extern const char str_802C2C54[];
extern const char str_802C2C68[];
extern const char str_802C2C7C[];
extern const char str_802C2C90[];
extern const char str_802C2CA4[];
extern const char str_802C2CB4[];
extern const char str_802C2CC4[];
extern const char str_802C2CD4[];
extern const char str_802C2CE4[];
extern const char str_802C2CF4[];
extern const char str_802C2D04[];
extern const char str_802C2D14[];
extern const char str_802C2D24[];
extern const char str_802C2D34[];
extern const char str_802C2D44[];
extern const char str_802C2D54[];
extern const char str_802C2D64[];
extern const char str_802C2D74[];
extern const char str_802C2D84[];
extern const char str_802C2D94[];
extern const char str_802C2DA4[];

#define TESTHEAP_SIZE (u32)(1.5 * 1024 * 1024)
#define PI 3.14159265358979323846264338327950288419716939937510f

extern GlobalWork* gp;
extern int sprintf(char* str, const char* format, ...);
extern double tan(double arg);

//.data
u8 _vivihimoData[0xC00] ATTRIBUTE_ALIGN(32) = {  // G5: target .data is 32-aligned
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x99, 0x99, 0x9A, 0x3F, 0x4C, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x33, 0x33, 0x33,
    0x3F, 0x00, 0x00, 0x00, 0x3F, 0x33, 0x33, 0x33, 0x3E, 0xCC, 0xCC, 0xCD, 0x3F, 0x33, 0x33, 0x33,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3E, 0x4C, 0xCC, 0xCD, 0x3F, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3E, 0x4C, 0xCC, 0xCD, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x3F, 0x4C, 0xCC, 0xCD, 0x3F, 0x66, 0x66, 0x66, 0x3F, 0x33, 0x33, 0x33,
    0x3F, 0x19, 0x99, 0x9A, 0x3F, 0x33, 0x33, 0x33, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
    0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00, 0x3F, 0x80, 0x00, 0x00,
};

typedef struct MoaChain {
    const char* a;
    const char* b;
} MoaChain;
const s32 dat_80419a28 = 0x2F;
MoaChain g_moamoa_chain_tbl[47] = {
    { str_802C2A98, str_802C2AA4 },
    { str_802C2AA4, str_802C2AB4 },
    { str_802C2AB4, str_802C2AC4 },
    { str_802C2AC4, str_802C2AD4 },
    { str_802C2AD4, str_802C2AE4 },
    { str_802C2A98, str_802C2AF4 },
    { str_802C2AF4, str_802C2B04 },
    { str_802C2B04, str_802C2B14 },
    { str_802C2B14, str_802C2B24 },
    { str_802C2B24, str_802C2B34 },
    { str_802C2A98, str_802C2B44 },
    { str_802C2B44, str_802C2B54 },
    { str_802C2B54, str_802C2B64 },
    { str_802C2B64, str_802C2B74 },
    { str_802C2B74, str_802C2B84 },
    { str_802C2A98, str_802C2B94 },
    { str_802C2B94, str_802C2BA4 },
    { str_802C2BA4, str_802C2BB4 },
    { str_802C2BB4, str_802C2BC4 },
    { str_802C2BC4, str_802C2BD4 },
    { str_802C2BD4, str_802C2BE4 },
    { str_802C2BE4, str_802C2BF4 },
    { str_802C2BF4, str_802C2C04 },
    { str_802C2C04, str_802C2C18 },
    { str_802C2C18, str_802C2C2C },
    { str_802C2C2C, str_802C2C40 },
    { str_802C2BF4, str_802C2C54 },
    { str_802C2C54, str_802C2C68 },
    { str_802C2C68, str_802C2C7C },
    { str_802C2C7C, str_802C2C90 },
    { str_802C2A98, str_802C2CA4 },
    { str_802C2CA4, str_802C2CB4 },
    { str_802C2CB4, str_802C2CC4 },
    { str_802C2CC4, str_802C2CD4 },
    { str_802C2A98, str_802C2CE4 },
    { str_802C2CE4, str_802C2CF4 },
    { str_802C2CF4, str_802C2D04 },
    { str_802C2D04, str_802C2D14 },
    { str_802C2A98, str_802C2D24 },
    { str_802C2D24, str_802C2D34 },
    { str_802C2D34, str_802C2D44 },
    { str_802C2D44, str_802C2D54 },
    { str_802C2A98, str_802C2D64 },
    { str_802C2D64, str_802C2D74 },
    { str_802C2D74, str_802C2D84 },
    { str_802C2D84, str_802C2D94 },
    { str_802C2A98, str_802C2DA4 },
};

//.bss
Mtx g_modeling_mtx_stack[32];
static AnimationWork work;
f32 tanfTbl[0xB2];

//.sdata
s32 vivihimoTailGroupNo[4] ATTRIBUTE_ALIGN(32) = { 0, 2, -1, -1 };  // G5: target .sdata is 32-aligned
void* vivihimoData[4] = {
    NULL,
    (u8*)&_vivihimoData,
    (u8*)&_vivihimoData + 0x400,
    (u8*)&_vivihimoData + 0x800,
};
static AnimationWork* wp = &work;

//.sbss
s32 anim_unused_sbss;
Mtx* g_modeling_mtx;
s32 g_modeling_mtx_lv;
static u32 g5_mtx_s1454[12];  // target mtx$1454 (function-local static of an asm function)

// local declarations
void animPoseRefresh(void);
void animPaperPoseDisp(CameraId camId, void* param);
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
void animPaperPoseDispSub(s32 unused, AnimationPose* pose);
void renderProc(s32 shapeId, s32 unused);
void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz);
void pushGXModelMtx_TransformNode__(AnimPoseNode* node);
void evalProc(s32 parentId, s32 groupId);


#ifdef NONMATCHING
AnimationWork* animGetPtr(void) {
    return wp;
}
#endif

#ifdef NONMATCHING
OSTime animTimeGetTime(BOOL globalTime) {
    if (globalTime == FALSE) {
        return OSTicksToMilliseconds(gp->renderFieldTime);
    }
    return OSTicksToMilliseconds(gp->renderTime);
}
#endif

#ifdef NONMATCHING
void initTestHeap(void) {
    if (!wp->testHeap) { // allocate 1.5MiB test heap
        wp->testHeap = __memAlloc(HEAP_DEFAULT, TESTHEAP_SIZE);
    }
    wp->testAlloc = (u32)wp->testHeap;
}
#endif

// heavily inlined
#ifdef NONMATCHING
void* testAlloc(u32 size) {
    void* alloc = (void*)wp->testAlloc;

    if (size & 31) {
        size += 32 - (size & 31);
    }
    wp->testAlloc += size;
    if ((u32)wp->testAlloc >= (u32)wp->testHeap + TESTHEAP_SIZE) { // need to allocate more
        animPoseRefresh();
        alloc = testAlloc(size);
    }
    return alloc;
}
#endif

#ifdef NONMATCHING
void animInit(void) {
    int i;
    FileEntry* file;

    wp->totalFiles = 64; // TODO: #define these?
    wp->totalTextures = 64;
    wp->totalPoses = 256;
    wp->mFloatScratchRP = 1024;
    wp->mFloatScratchWP = 0;
    wp->files = __memAlloc(HEAP_DEFAULT, sizeof(AnimationPoseFile) * wp->totalFiles);
    wp->textures = __memAlloc(HEAP_DEFAULT, sizeof(AnimationTextureFile) * wp->totalTextures);
    wp->poses = __memAlloc(HEAP_DEFAULT, sizeof(AnimationPose) * wp->totalPoses);
    wp->mbUseFloatScratch = 0;
    wp->mpFloatScratch = __memAlloc(HEAP_DEFAULT, sizeof(Vec) * wp->mFloatScratchRP);

    wp->mpTexObjs[0] = NULL;
    wp->mpTexObjs[1] = NULL;
    wp->mpCurTexObj = NULL;

    wp->mpTexDatas[0] = NULL;
    wp->mpTexDatas[1] = NULL;
    wp->mpCurTexData = NULL;

    wp->paperMtxPtr[0] = NULL;
    wp->paperMtxPtr[1] = NULL;
    wp->paperMtxPtr[2] = NULL;

    wp->field_0xD8 = 1;
    wp->field_0xDC = 1;

    wp->testHeap = NULL;
    wp->inBattle = FALSE;
    initTestHeap(); // inlined

    for (i = 0; i < 0xB2; i++) {
        tanfTbl[i] = (f32)tan((i - 0x59) * 0.017453289f);
    }
    file = fileAllocf(0, "a/vivian.bin");
    if (file) {
        memcpy_as4(vivihimoData[1], *file->data, sizeof(_vivihimoData));
        memcpy_as4(vivihimoTailGroupNo, (void*)((u32)*file->data + sizeof(_vivihimoData)), sizeof(vivihimoTailGroupNo));
        fileFree(file);
    }
    fileSetCurrentArchiveType(0);
    wp->mp_ag2tg = fileAllocf(0, "a/ag2tg.bin");
}
#endif

#ifdef NONMATCHING
void animMain(void) {
    dispEntry(CAMERA_OFFSCREEN, 0.0f, 1, animPaperPoseDisp, NULL);
}
#endif

inline AnimationPoseData* animPoseGetBaseData(AnimationPose* pose) {
    return *wp->files[pose->fileId].handle->data;
}

#define animPoseGetBaseData(pose) (*(AnimationPoseData**)(wp->files[(pose)->fileId].handle->data))

// heavily inlined, TODO helper function for that AnimPoseData* data, copy of animPoseGetAnimBaseDataPtr with AnimPose*
// arg
#ifdef NONMATCHING
void animPose_AllocBuffer(AnimationPose* pose) {
    pose->mpBufferVtxPos = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferPosNum);
    pose->mpVtxArrayPos = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferPosNum);

    pose->mpBufferVtxNrm = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferNrmNum);
    pose->mpVtxArrayNrm = testAlloc(sizeof(Vec) * animPoseGetBaseData(pose)->mBufferNrmNum);

    pose->mpBufferGroupVisibility = testAlloc(sizeof(u8) * animPoseGetBaseData(pose)->mBufferVisibilityNum);
    pose->mpGroupVisibility = pose->mpBufferGroupVisibility;

    pose->mpBufferNode = testAlloc(sizeof(AnimPoseNode*) * animPoseGetBaseData(pose)->mBufferNodeNum);
    pose->mpNodes = testAlloc(sizeof(AnimPoseNode*) * animPoseGetBaseData(pose)->mBufferNodeNum);

    pose->mpBufferTexAnimEntries = testAlloc(sizeof(AnimTexMtx) * animPoseGetBaseData(pose)->mBufferTexAnimNum);
    pose->mpTexAnimEntries = pose->mpBufferTexAnimEntries;

    pose->lastFrameZero = -1;
}
#endif

// heavily inlined
#ifdef NONMATCHING
void animPoseRefresh(void) {
    int i;

    initTestHeap(); // inline
    for (i = 0; i < wp->totalPoses; i++) {
        AnimationPose* pose = &wp->poses[i]; // inline
        if (pose->flags) {
            // TODO: cleanup in rewrite?
            if ((!wp->inBattle || pose->type != 0) && (wp->inBattle || pose->type != 1)) {
                animPose_AllocBuffer(pose);
                pose->lastFrameZero = -1; // TODO: redundant?
            }
        }
    }
}
#endif

#ifdef NONMATCHING
void animPoseBattleInit(void) {
    wp->inBattle = TRUE;
    animPoseRefresh();
}
#endif

#ifdef NONMATCHING
s32 animPoseEntry(const char *animName, s32 type)
{
  static s32 _dummy = -1;
  AnimationTextureFile *new_var3[2];
  AnimationPoseFile *file;
  AnimationPoseFile *tempfile;
  AnimationPose *pose;
  AnimationPose *temp;
  AnimationPoseData *data;
  s32 texId;
  s32 fileId;
  FileEntry *new_var2;
  s32 poseId;
  AnimationPoseFile *new_var;
  s32 i;
  char textureName[256];
  switch (type)
  {
    case 0:
      fileSetCurrentArchiveType(1);
      break;

    case 1:
      fileSetCurrentArchiveType(2);
      break;

    case 2:
      fileSetCurrentArchiveType(0);
      break;

  }

  for (poseId = 0, i = 0; i < wp->totalPoses; poseId++, i++)
  {
    temp = &wp->poses[poseId];
    if (!temp->flags)
    {
      pose = temp;
      goto label_1;
    }
  }

  pose = (void *) 0;
  poseId = -1;
  label_1:
  pose->flags |= 1;

  pose->typeFlags = 0;
  pose->references = 0;
  texId = wp->totalFiles;
  for (i = 0; i < texId; i++)
  {
    file = &wp->files[i];
    if (file->active)
    {
      data = *file->handle->data;
      if (!strcmp(data->fileName, animName))
      {
        file->references++;
        goto label_5;
      }
    }
  }

  for (i = 0, fileId = 0; i < wp->totalFiles; i++, fileId++)
  {
    tempfile = &wp->files[fileId];
    if (!tempfile->active)
    {
      file = tempfile;
      goto label_2;
    }
  }

  file = (void *) 0;
  fileId = -1;
  label_2:
  file->active = 1;

  file->references++;
  file->handle = fileAllocf(5, "%s/%s", "a", animName);
  new_var2 = file->handle;
  if (!file->handle)
  {
    fileId = -2;
    file->active = 0;
    file->references--;
  }
  else
  {
    data = *file->handle->data;
    if (!data)
    {
      fileFree(new_var2);
      fileId = -2;
      file->active = 0;
      new_var = file;
      new_var->references--;
    }
    else
    {
      sprintf(textureName, "%s/%s-", "a", data->textureName);
      texId = wp->totalTextures;
      for (i = 0; i < texId; i++)
      {
        new_var3[0] = &wp->textures[i];
        if (*((u32 *) (&new_var3[0]->active)))
        {
          if (new_var3[0]->handle)
          {
            if (!strcmp(new_var3[0]->handle->filename, textureName))
            {
              new_var3[0]->references++;
              goto label_4;
            }
          }
        }
      }

      for (i = 0, texId = 0; i < wp->totalTextures; i++, texId++)
      {
        new_var3[1] = &wp->textures[texId];
        if (!(*((u32 *) (&new_var3[1]->active))))
        {
          new_var3[0] = new_var3[1];
          goto label_3;
        }
      }

      new_var3[0] = (void *) 0;
      texId = -1;
      label_3:
      new_var3[0]->active = 1;

      new_var3[0]->references++;
      new_var3[0]->handle = fileAlloc(textureName, 4);
      label_4:
      new_var->textureId = texId;

    }
  }
  label_5:
  pose->fileId = fileId;

  if (pose->fileId == (-2))
  {
    pose->flags = 0;
    return -2;
  }
  pose->animId = 0;
  pose->localTime = animTimeGetTime(type);
  pose->lastFrameZero = -1;
  pose->lastFrameTime = 0.0f;
  pose->field_0x80 = 0;
  pose->loopTime = 0.0f;
  pose->peraRotY = 0.0f;
  pose->rotationY = 0.0f;
  pose->peraTargetRotY = 0.0f;
  pose->type = type;
  pose->paperId = -1;
  animPose_AllocBuffer(pose);
  pose->gxCallback = (void *) 0;
  pose->disableDraw = 0;
  pose->materialFlag = 0;
  pose->materialLightFlag = 0;
  pose->materialColor = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
  pose->materialColor2 = (GXColor){0xFF, 0xFF, 0xFF, 0xFF};
  pose->paperScaleXZ = (pose->paperScaleY = 1.0f);
  pose->paperOfsY = 0.0f;
  pose->localTimeRate = 1.0f;
  PSMTXIdentity(pose->matrix);
  if (!strcmp(animName, "tst_vivi"))
  {
    pose->vivianType = 1;
    pose->vivianGroupNo = &vivihimoTailGroupNo[0];
  }
  else
    if (!strcmp(animName, "c_vivian"))
  {
    pose->vivianType = 1;
    pose->vivianGroupNo = &vivihimoTailGroupNo[1];
  }
  else
    if (!strcmp(animName, "c_maririn"))
  {
    pose->vivianType = 2;
    pose->vivianGroupNo = &vivihimoTailGroupNo[2];
  }
  else
    if (!strcmp(animName, "c_majyorin"))
  {
    pose->vivianType = 3;
    pose->vivianGroupNo = &vivihimoTailGroupNo[3];
  }
  else
  {
    pose->vivianType = 0;
    pose->vivianGroupNo = &_dummy;
  }
  pose->dispCallback = (void *) 0;
  pose->dispUserDataCallback = (void *) 0;
  return poseId;
}
#endif

#ifdef NONMATCHING
s32 animPaperPoseEntry(const char* animName, s32 group) {
    s32 i;
    AnimationPose* pose;

    i = animPaperPoseGetId(animName, group);
    if (i >= 0) {
        pose = animPoseGetAnimPosePtr(i);
        pose->references++;
        return i;
    }
    i = animPoseEntry(animName, group);
    if (i == -2) {
        return i;
    }
    pose = animPoseGetAnimPosePtr(i);
    pose->typeFlags = 3;
    pose->references = 0;
    pose->flags |= 1;
    return i;
}
#endif

const char* animGetTexName(const char* name);

#ifdef NONMATCHING
BOOL animEffectAsync(const char* animName, u32 group) {
    s32 model, anim;
    BOOL ret;

    switch (group) {
        case 0:
            fileSetCurrentArchiveType(1);
            break;
        case 1:
            fileSetCurrentArchiveType(2);
            break;
        case 2:
            fileSetCurrentArchiveType(0);
            break;
    }
    model = fileAsyncf(5, NULL, "%s/%s", "a", animName);
    anim = fileAsyncf(4, NULL, "%s/%s-", "a", animGetTexName(animName));
    if (model == -1) {
        ret = TRUE;
    } else if ((u32)model == 0) {
        ret = FALSE;
    } else if (anim == -1) {
        ret = TRUE;
    } else if ((u32)anim == 0) {
        ret = FALSE;
    } else {
        ret = TRUE;
    }
    return ret;
}
#endif

#ifdef NONMATCHING
void animPosePeraOn(s32 poseId) {
    wp->poses[poseId].flags |= 8;
}
#endif

#ifdef NONMATCHING
void animPosePeraOff(s32 poseId) {
    wp->poses[poseId].flags &= ~8;
}
#endif

#ifdef NONMATCHING
void animPosePaperPeraOn(s32 poseId) {
    AnimationPose* dst = &wp->poses[wp->poses[poseId].paperId];
    AnimationPose* src = &wp->poses[poseId];

    dst->flags |= 8;
    dst->peraRotY = src->peraRotY;
    dst->rotationY = src->rotationY;
    dst->peraTargetRotY = src->peraTargetRotY;
}
#endif

#ifdef NONMATCHING
void animPosePaperPeraOff(s32 poseId) {
    wp->poses[wp->poses[poseId].paperId].flags &= ~8;
}
#endif

#ifdef NONMATCHING
void animPoseSetLocalTimeRate(s32 poseId, f32 localTimeRate) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->localTimeRate = localTimeRate;
}
#endif

#ifdef NONMATCHING
void animPoseSetLocalTime(s32 poseId, f32 localTimeFrames) {
    AnimationPose *pose, *pera;

    pose = &wp->poses[poseId];
    pose->localTime = animTimeGetTime(pose->type) - (u64)(16.666666f * localTimeFrames);
    pose->mLocalTimeInit = pose->localTime;
    if (pose->paperId != -1) {
        pera = &wp->poses[pose->paperId];
        if (!(pera->typeFlags & 2)) {
            pera->localTime = pose->localTime;
        }
    }
}
#endif

#ifdef NONMATCHING
void animPoseSetStartTime(s32 poseId, OSTime startTime) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->localTime = startTime;
}
#endif

#define animPosePaperAnimId(pose) (*(s32*)(pose)->field_0x94)
#define animPoseGetBaseDataId(id) (*(AnimationPoseData**)(wp->files[wp->poses[id].fileId].handle->data))

inline s32 animPoseGetAnimIdx(AnimationPoseData* data, const char* name) {
    s32 i = (s32)name;
    s32 count = data->mAnimCount;

    if (i < 0) {
        for (i = 0; i < count; i++) {
            if (!strcmp(data->mpAnims[i].name, name)) {
                return i;
            }
        }
    }
    else if (i < count) {
        return i;
    }
    return 0;
}

#ifdef NONMATCHING
void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose;
    s32 animId;

    pose = &wp->poses[poseId];
    animId = animPoseGetAnimIdx(animPoseGetBaseData(pose), animName);
    if (reset || animId != pose->animId) {
        pose->animId = animId;
        if (pose->paperId != -1 && pose->flags & 2) {
            pose->flags |= 4;
        }
        pose->localTime = animTimeGetTime(pose->type);
        pose->lastFrameZero = -1;
        pose->lastFrameTime = 0.0f;
        pose->field_0x80 = 0;
        pose->loopTime = 0.0f;
    }
}
#endif

#ifdef NONMATCHING
s32 animPaperPoseGetId(const char* animName, s32 group) {
    AnimationPose* pose;
    s32 i;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = &wp->poses[i];
        if (pose->flags & 1 && pose->typeFlags & 1 && pose->typeFlags & 2 && pose->type == group &&
            !strcmp(animPoseGetBaseData(pose)->fileName, animName)) {
            break;
        }
    }
    if (i == wp->totalPoses) {
        i = -1;
    }
    return i;
}
#endif

#ifdef NONMATCHING
void animPoseSetPaperAnimGroup(s32 poseId, const char* animName, BOOL someflag) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);

    if (!animName) {
        pose->paperId = -1;
        animPoseSetMaterialLightFlagOff(poseId, 1);
        return;
    }
    pose->paperId = animPaperPoseGetId(animName, pose->type);
    if (pose->paperId < 0) {
        pose->paperId = animPaperPoseGetId(animName, 2);
    }
    animPosePaperAnimId(pose) = -1;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    if (someflag) {
        pose->flags |= 2;
        pose->flags |= 4;
    }
    else {
        pose->flags &= ~2;
        pose->flags &= ~4;
    }
    animPoseSetMaterialLightFlagOn(poseId, 1);
}
#endif

#ifdef NONMATCHING
void animPoseSetPaperAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    AnimationPoseData* data;
    s32 id;
    s32 idx;

    data = animPoseGetAnimBaseDataPtr(pose->paperId);
    idx = animPoseGetAnimIdx(data, animName);
    animPosePaperAnimId(pose) = idx;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    id = pose->paperId;
    if (id != -1 && !(*(u32*)((u8*)wp->poses + id * sizeof(AnimationPose) + 4) & 2)) {
        animPoseMain(pose->paperId);
    }
}
#endif

void animPoseFileRelease(s32 fileId);

inline s32 animEffectPoseEntry(const char* animName, s32 group) {
    s32 i;
    AnimationPose* pose;

    i = animPoseEntry(animName, group);
    if (i == -2) {
        return i;
    }
    pose = animPoseGetAnimPosePtr(i);
    pose->typeFlags = 1;
    pose->references = 0;
    pose->flags |= 1;
    return i;
}

#ifdef NONMATCHING
void animPoseSetEffect(s32 poseId, const char* animName, BOOL someflag) {
    AnimationPose* paper;
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);

    if (pose->paperId != -1) {
        if (animName && !strcmp((*(AnimationPoseData**)(((AnimationPoseFile*)((u8*)wp->files + animPoseGetAnimPosePtr(pose->paperId)->fileId * 16))->handle->data))->fileName, animName) &&
            (s32)((pose->flags >> 1) & 1) == someflag) {
            return;
        }
        paper = &wp->poses[pose->paperId];
        paper->references--;
        if (paper->references < 0) {
            animPoseFileRelease(paper->fileId);
            paper->flags = 0;
        }
    }
    if (!animName) {
        pose->paperId = -1;
        animPoseSetMaterialLightFlagOff(poseId, 1);
        return;
    }
    pose->paperId = animEffectPoseEntry(animName, pose->type);
    animPosePaperAnimId(pose) = -1;
    pose->mLocalTimeInit = animTimeGetTime(pose->type);
    if (someflag) {
        pose->flags |= 2;
        pose->flags |= 4;
    }
    else {
        pose->flags &= ~2;
    }
    animPoseSetMaterialLightFlagOn(poseId, 1);
}
#endif

#ifdef NONMATCHING
void animPoseSetEffectAnim(s32 poseId, const char* animName, BOOL reset) {
    AnimationPose* pose = &wp->poses[poseId];

    if (pose->paperId != -1) {
        animPoseSetAnim(pose->paperId, animName, reset);
    }
}
#endif

#ifdef NONMATCHING
void animPoseSetGXFunc(s32 poseId, void (*callback)(s32 wXluStage), BOOL disableDraw) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->gxCallback = callback;
    pose->disableDraw = disableDraw;
}
#endif

#ifdef NONMATCHING
f32 animPoseGetRadius(s32 poseId) {
    return 2.0f * animPoseGetAnimBaseDataPtr(poseId)->radius;
}
#endif

#ifdef NONMATCHING
f32 animPoseGetHeight(s32 poseId) {
    return 2.0f * animPoseGetAnimBaseDataPtr(poseId)->height;
}
#endif

#ifdef NONMATCHING
f32 animPoseGetLoopTimes(s32 id) {
    AnimationPose* pose = &wp->poses[id];
    return pose->loopTime;
}
#endif

#ifdef NONMATCHING
BOOL animPoseGetPeraEnd(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if (!(pose->flags & 8)) {
        return TRUE;
    }
    if (__fabs(pose->peraTargetRotY - pose->rotationY) < 10.0) {
        return TRUE;
    }
    return FALSE;
}
#endif

#ifdef NONMATCHING
void animPoseSetMaterialFlagOn(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialFlag |= mask;
}
#endif

#ifdef NONMATCHING
void animPoseSetMaterialFlagOff(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialFlag &= ~mask;
}
#endif

#ifdef NONMATCHING
void animPoseSetMaterialLightFlagOn(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialLightFlag |= mask;
}
#endif

#ifdef NONMATCHING
void animPoseSetMaterialLightFlagOff(s32 poseId, u32 mask) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialLightFlag &= ~mask;
}
#endif

#ifdef NONMATCHING
void animPoseSetMaterialEvtColor(s32 poseId, GXColor color) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->materialColor = color;
}
#endif

#ifdef NONMATCHING
u32 animPoseGetMaterialFlag(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialFlag;
}
#endif

#ifdef NONMATCHING
u32 animPoseGetMaterialLightFlag(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialLightFlag;
}
#endif

#ifdef NONMATCHING
GXColor animPoseGetMaterialEvtColor(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->materialColor;
}
#endif

extern double atan2(double y, double x);
#define APM_U(p, o) (*(u32*)((u8*)(p) + (o)))
#define APM_S(p, o) (*(s32*)((u8*)(p) + (o)))
#define APM_F(p, o) (*(f32*)((u8*)(p) + (o)))
#define APM_P(p, o) (*(u8**)((u8*)(p) + (o)))
#define APM_S8(dst, p, off) asm { psq_l dst, off(p), 1, 4 }
#ifdef NONMATCHING
static inline void animInitFastCast_(void) {
    asm {
        li r3, 4
        oris r3, r3, 4
        mtspr GQR2, r3
        li r3, 5
        oris r3, r3, 5
        mtspr GQR3, r3
        li r3, 6
        oris r3, r3, 6
        mtspr GQR4, r3
        li r3, 7
        oris r3, r3, 7
        mtspr GQR5, r3
    }
}
static inline f32 animS8a_(register u8* p) { register f32 r; asm { psq_l r, 1(p), 1, 4 } return r; }
static inline f32 animS8b_(register u8* p) { register f32 r; asm { psq_l r, 2(p), 1, 4 } return r; }
static inline f32 animS8c_(register u8* p) { register f32 r; asm { psq_l r, 3(p), 1, 4 } return r; }
void animPoseMain(s32 poseId) {
    s32 nextFrame;
    u8* pose;
    u8* file;
    u8* anim;
    u8* poses;
    u8* grpB;
    u8* grpA;
    u8* q;
    f32 key;
    u8* kf;
    u8* kfEnd;
    u8* v;
    u8* d;
    u8* e;
    f32 x;
    f32 y;
    f32 z;
    s32 loop;
    s32 nD;
    s32 frame;
    s32 cnt;
    s32 i;
    s32 b;
    s32 nA;
    s32 nB;
    s32 nC;
    s32 nE;
    f32 t;
    f32 f;
    f32 cur;
    f32 start;
    f32 len;
    f32 tm;
    f32 dt;
    f32 s;
    f32 t2;
    f32 t3;
    u8* p;
    s64 ms;
    struct APMG { u8 pad[8]; u8* p; u8 pad2[4]; };
    struct APMA { u8 pad[0x3c]; u8* p; };
    struct APMA* aa;
    struct APMK { s32 a; s32 b; };
    struct APMF { u8 pad[0x2c]; };
    struct APMD { u8 pad[0x28]; struct APMF* f; u8 pad2[0x40 - 0x2c]; struct APMK* k; };

    poses = APM_P(wp, 0x10);
    pose = poses + poseId * 0x170;
    file = (u8*)animPoseGetBaseData((AnimationPose*)pose);
    anim = (u8*)((AnimationPoseData*)file)->mpAnims[((AnimationPose*)pose)->animId].data;
    animInitFastCast_();
    if (APM_S(wp, 0xe8) != 0) {
        grpA = APM_P(wp, 0xf8);
        grpB = APM_P(wp, 0xfc);
    } else {
        grpA = APM_P(pose, 0x4c);
        grpB = APM_P(pose, 0x54);
    }
    if (APM_S(pose, 0x90) != -1 && !(APM_U(poses + APM_S(pose, 0x90) * 0x170, 4) & 2)) {
        animPoseMain(APM_S(pose, 0x90));
    }
    if (anim == NULL) return;
    loop = *(s32*)APM_P(anim, 0x24);
    if (APM_S(pose, 0xc) == 0) {
        ms = OSTicksToMilliseconds(gp->renderFieldTime);
    } else {
        ms = OSTicksToMilliseconds(gp->renderTime);
    }
    tm = (f32)(u64)(ms - *(s64*)(pose + 0x18));
    APM_F(pose, 0x20) = 60.0f * tm / 1000.0f;
    APM_F(pose, 0x20) *= APM_F(pose, 0x44);
    cur = APM_F(pose, 0x20);
    f = APM_F(APM_P(anim, 0x24), 8);
    start = APM_F(APM_P(anim, 0x24), 4);
    len = f - start;
    if (0.0f == len) {
        APM_F(pose, 0x84) = cur - start;
    } else if (loop != 0) {
        tm = cur - start;
        if (tm < 0.0f) {
            APM_F(pose, 0x84) = 0.0f;
        } else {
            APM_F(pose, 0x84) = tm / len;
            start = cur - (f32)(s32)APM_F(pose, 0x84) * len;
        }
    } else if (cur < start) {
        APM_F(pose, 0x84) = 0.0f;
    } else if (cur > f) {
        APM_F(pose, 0x84) = (cur - start) / len;
        start = f;
    } else {
        APM_F(pose, 0x84) = (cur - start) / len;
        start = cur;
    }
    APM_F(pose, 0x24) = start;
    key = APM_F(pose, 0x24);
    cnt = APM_S(anim, 8);
    q = APM_P(anim, 0x28);
    for (i = 0; i < cnt; i++, q += 0x2c) {
        if (*(f32*)q > key) break;
    }
    APM_S(pose, 0x28) = i - 1;
    APM_S(pose, 0x2c) = APM_S(pose, 0x28) + 1;
    key = APM_F(pose, 0x24);
    q = APM_P(anim, 0x40);
    cnt = APM_S(anim, 0x20);
    for (i = 0; i < cnt; q += 8, i++) {
        if (*(f32*)q > key) break;
    }
    APM_S(pose, 0x34) = i - 1;
    APM_S(pose, 0x38) = APM_S(pose, 0x34) + 1;
    if (loop == 0) {
        if (APM_S(pose, 0x2c) >= APM_S(anim, 8)) APM_S(pose, 0x2c) = APM_S(pose, 0x28);
        if (APM_S(pose, 0x38) >= APM_S(anim, 0x20)) APM_S(pose, 0x38) = APM_S(pose, 0x34);
    }
    APM_S(pose, 0x80) = ((struct APMD*)anim)->k[APM_S(pose, 0x34)].b;
    start = *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x28) * 0x2c);
    tm = APM_F(pose, 0x24) - start;
    if (loop != 0) {
        if (APM_S(pose, 0x2c) >= APM_S(anim, 8)) {
            APM_S(pose, 0x2c) = 0;
            len = APM_F(APM_P(anim, 0x24), 8) - *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x28) * 0x2c);
        } else {
            len = *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x2c) * 0x2c) - start;
        }
    } else {
        len = *(f32*)(APM_P(anim, 0x28) + APM_S(pose, 0x2c) * 0x2c) - start;
    }
    if (0.0f == len) {
        APM_F(pose, 0x30) = 0.0f;
    } else {
        APM_F(pose, 0x30) = tm / len;
    }
    frame = APM_S(pose, 0x28);
    nextFrame = APM_S(pose, 0x2c);
    t = APM_F(pose, 0x30);
    nA = APM_S(file, 0xf0);
    nB = APM_S(file, 0xf8);
    nC = APM_S(file, 0x13c);
    nD = APM_S(file, 0x140);
    nE = APM_S(file, 0x12c);
    if (APM_S(pose, 0x3c) != frame) {
        if (APM_S(pose, 0x3c) == -1 || APM_S(pose, 0x3c) > frame) {
            kfEnd = (u8*)((struct APMD*)anim)->f + frame * 0x2c + 0x2c;
            kf = (u8*)((struct APMD*)anim)->f;
            if (nA != 0) memcpy_as4(APM_P(pose, 0x48), APM_P(file, 0x154), nA * 0xc);
            if (nB != 0) memcpy_as4(APM_P(pose, 0x50), APM_P(file, 0x15c), nB * 0xc);
            if (nC != 0) memcpy(APM_P(pose, 0x58), APM_P(file, 0x1a0), nC);
            if (nD != 0) memcpy_as4(APM_P(pose, 0x60), APM_P(file, 0x1a4), nD * 4);
            if (nE != 0) memcpy_as4(APM_P(pose, 0x68), APM_P(file, 0x190), nE * 0x18);
            if (APM_S(pose, 0x3c) == -1) APM_S(pose, 0x3c) = 0;
            s = 0.0625f;
            for (; kf < kfEnd; kf += 0x2c) {
                { u8* d; u8* e;
                v = APM_P(pose, 0x48);
                d = APM_P(anim, 0x2c) + APM_S(kf, 4) * 4;
                e = d + APM_S(kf, 8) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x50);
                d = APM_P(anim, 0x30) + APM_S(kf, 0xc) * 4;
                e = d + APM_S(kf, 0x10) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e; u8* v;
                v = APM_P(pose, 0x58);
                d = APM_P(anim, 0x38) + APM_S(kf, 0x1c) * 2;
                e = d + APM_S(kf, 0x20) * 2;
                for (; d < e; d += 2) {
                    v += d[0];
                    v[0] += d[1];
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x60);
                d = APM_P(anim, 0x3c) + APM_S(kf, 0x24) * 4;
                e = d + APM_S(kf, 0x28) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 4;
                    x = animS8a_(d);
                    ((f32*)v)[0] += s * x;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x68);
                d = APM_P(anim, 0x34) + APM_S(kf, 0x14) * 0xc;
                e = d + APM_S(kf, 0x18) * 0xc;
                for (; d < e; d += 0xc) {
                    v += d[0] * 0x18;
                    v[0] += d[1];
                    APM_F(v, 4) += APM_F(d, 4);
                    APM_F(v, 8) += APM_F(d, 8);
                }
                }
            }
        } else if (APM_S(pose, 0x3c) < frame) {
            kf = APM_P(anim, 0x28) + (APM_S(pose, 0x3c) + 1) * 0x2c;
            kfEnd = APM_P(anim, 0x28) + (frame + 1) * 0x2c;
            s = 0.0625f;
            for (; kf < kfEnd; kf += 0x2c) {
                { u8* d; u8* e;
                v = APM_P(pose, 0x48);
                d = APM_P(anim, 0x2c) + APM_S(kf, 4) * 4;
                e = d + APM_S(kf, 8) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x50);
                d = APM_P(anim, 0x30) + APM_S(kf, 0xc) * 4;
                e = d + APM_S(kf, 0x10) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 0xc;
                    x = animS8a_(d);
                    y = animS8b_(d);
                    z = animS8c_(d);
                    ((f32*)v)[0] += s * x;
                    ((f32*)v)[1] += s * y;
                    ((f32*)v)[2] += s * z;
                }
                }
                { u8* d; u8* e; u8* v;
                v = APM_P(pose, 0x58);
                d = APM_P(anim, 0x38) + APM_S(kf, 0x1c) * 2;
                e = d + APM_S(kf, 0x20) * 2;
                for (; d < e; d += 2) {
                    v += d[0];
                    v[0] += d[1];
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x60);
                d = APM_P(anim, 0x3c) + APM_S(kf, 0x24) * 4;
                e = d + APM_S(kf, 0x28) * 4;
                for (; d < e; d += 4) {
                    v += d[0] * 4;
                    x = animS8a_(d);
                    ((f32*)v)[0] += s * x;
                }
                }
                { u8* d; u8* e;
                v = APM_P(pose, 0x68);
                d = APM_P(anim, 0x34) + APM_S(kf, 0x14) * 0xc;
                e = d + APM_S(kf, 0x18) * 0xc;
                for (; d < e; d += 0xc) {
                    v += d[0] * 0x18;
                    v[0] += d[1];
                    APM_F(v, 4) += APM_F(d, 4);
                    APM_F(v, 8) += APM_F(d, 8);
                }
                }
            }
        }
    } else {
        if (APM_F(pose, 0x40) > t) APM_F(pose, 0x40) = 0.0f;
    }
    if (frame == nextFrame) {
        if (nA != 0) memcpy_as4(grpA, APM_P(pose, 0x48), nA * 0xc);
        if (nB != 0) memcpy_as4(grpB, APM_P(pose, 0x50), nB * 0xc);
        if (nD != 0) memcpy_as4(APM_P(pose, 0x64), APM_P(pose, 0x60), nD * 4);
    } else if (frame <= nextFrame) {
        kf = APM_P(anim, 0x28) + nextFrame * 0x2c;
        { u8* d; u8* e;
        s = 0.0625f * t;
        v = grpA;
        d = APM_P(anim, 0x2c) + APM_S(kf, 4) * 4;
        e = d + APM_S(kf, 8) * 4;
        p = APM_P(pose, 0x48);
        if (nA != 0) memcpy_as4(grpA, p, nA * 0xc);
        for (; d < e; d += 4) {
            v += d[0] * 0xc;
            x = animS8a_(d);
            y = animS8b_(d);
            z = animS8c_(d);
            ((f32*)v)[0] += x * s;
            ((f32*)v)[1] += y * s;
            ((f32*)v)[2] += z * s;
        }
        }
        { u8* d; u8* e;
        v = grpB;
        d = APM_P(anim, 0x30) + APM_S(kf, 0xc) * 4;
        e = d + APM_S(kf, 0x10) * 4;
        p = APM_P(pose, 0x50);
        if (nB != 0) memcpy_as4(grpB, p, nB * 0xc);
        for (; d < e; d += 4) {
            v += d[0] * 0xc;
            x = animS8a_(d);
            y = animS8b_(d);
            z = animS8c_(d);
            ((f32*)v)[0] += x * s;
            ((f32*)v)[1] += y * s;
            ((f32*)v)[2] += z * s;
        }
        }
        { u8* d; u8* e; u8* v;
        dt = *(f32*)(APM_P(anim, 0x28) + nextFrame * 0x2c) - *(f32*)(APM_P(anim, 0x28) + frame * 0x2c);
        d = APM_P(anim, 0x3c) + APM_S(kf, 0x24) * 4;
        e = d + APM_S(kf, 0x28) * 4;
        v = APM_P(pose, 0x64);
        p = APM_P(pose, 0x60);
        if (nD != 0) memcpy_as4(v, p, nD * 4);
        for (; d < e; d += 4) {
            b = (s8)d[3];
            v += d[0] * 4;
            if (b < 0x59 && b > -0x59) {
                x = animS8a_(d);
                t2 = t * t;
                t3 = t * t2;
                ((f32*)v)[0] = ((f32*)v)[0] + ((t + (t3 - 2.0f * t2)) * (dt * tanfTbl[(s8)d[2] + 0x59]) +
                                (-2.0f * t3 + 3.0f * t2) * (0.0625f * x) +
                                (t3 - t2) * (dt * tanfTbl[b + 0x59]));
            }
        }
        }
    }
    APM_S(pose, 0x3c) = frame;
    APM_F(pose, 0x40) = t;
    if (APM_U(pose, 0) & 8) {
        CameraEntry* cam = camGetPtr(CAMERA_3D);
        f = 57.29579f * (f32)atan2(-(cam->cameraAt.x - cam->cameraPos.x), -(cam->cameraAt.z - cam->cameraPos.z));
        while (f < -360.0f) f += 360.0f;
        while (f >= 360.0f) f -= 360.0f;
        if (f < 0.0f) f += 360.0f;
        f -= APM_F(pose, 0x74);
        while (f < -360.0f) f += 360.0f;
        while (f >= 360.0f) f -= 360.0f;
        if ((f > 90.0f && f <= 270.0f) || (f < -90.0f && f >= -270.0f)) {
            APM_F(pose, 0x78) = -1.0f;
        } else {
            APM_F(pose, 0x78) = 1.0f;
        }
    }
}
#endif

#ifdef NONMATCHING
void pushGXModelMtx_TransformNode__(AnimPoseNode* node) {
    Mtx trans, scale, rot, tmp;
    Mtx sc1, sc2, sc3;
    Mtx rc1, rc2, rc3;
    MtxPtr p;
    u32 flags;
    f32 sx, sy, sz;
    f32 rx, ry, rz;
    f32 rcx, rcy, rcz;
    f32 scx, scy, scz;
    f32 rtx, rty, rtz;
    f32 stx, sty, stz;
    f32 tx, ty, tz;

    flags = 0;
    tx = node->mTranslation.x;
    ty = node->mTranslation.y;
    tz = node->mTranslation.z;
    sx = node->mScale.x;
    sy = node->mScale.y;
    sz = node->mScale.z;
    rx = 2.0f * node->mRot1.x;
    ry = 2.0f * node->mRot1.y;
    rz = 2.0f * node->mRot1.z;
    rcx = node->mRotationCenter.x;
    rcy = node->mRotationCenter.y;
    rcz = node->mRotationCenter.z;
    scx = node->mScaleCenter.x;
    scy = node->mScaleCenter.y;
    scz = node->mScaleCenter.z;
    rtx = node->mRotationTranslation.x;
    rty = node->mRotationTranslation.y;
    rtz = node->mRotationTranslation.z;
    stx = node->mScaleTranslation.x;
    sty = node->mScaleTranslation.y;
    stz = node->mScaleTranslation.z;

    if (tx || ty || tz) {
        PSMTXTrans(trans, tx, ty, tz);
        flags |= 1;
    }
    if (sx != 1.0f || sy != 1.0f || sz != 1.0f) {
        PSMTXScale(scale, sx, sy, sz);
        flags |= 2;
    }
    if (scx != 0.0f || scy != 0.0f || scz != 0.0f) {
        if (flags & 2) {
            PSMTXTrans(sc2, -scx, -scy, -scz);
            PSMTXTrans(sc1, scx, scy, scz);
            PSMTXTrans(sc3, stx, sty, stz);
            PSMTXConcat(sc3, sc1, tmp);
            PSMTXConcat(tmp, scale, tmp);
            PSMTXConcat(tmp, sc2, scale);
        }
        else if (stx || sty || stz) {
            PSMTXTrans(scale, stx, sty, stz);
            flags |= 2;
        }
    }
    PSMTXIdentity(rot);
    if (rz) {
        PSMTXRotRad(tmp, 'z', 0.017453292f * rz);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (ry) {
        PSMTXRotRad(tmp, 'y', 0.017453292f * ry);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (rx) {
        PSMTXRotRad(tmp, 'x', 0.017453292f * rx);
        PSMTXConcat(rot, tmp, rot);
        flags |= 4;
    }
    if (rcx != 0.0f || rcy != 0.0f || rcz != 0.0f) {
        if (flags & 4) {
            PSMTXTrans(rc2, -rcx, -rcy, -rcz);
            PSMTXTrans(rc1, rcx, rcy, rcz);
            PSMTXTrans(rc3, rtx, rty, rtz);
            PSMTXConcat(rc3, rc1, tmp);
            PSMTXConcat(tmp, rot, rot);
            PSMTXConcat(rot, rc2, rot);
        }
        else if (rtx || rty || rtz) {
            PSMTXTrans(rot, rtx, rty, rtz);
            flags |= 4;
        }
    }
    g_modeling_mtx_lv++;
    g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    switch (flags) {
        case 0:
            PSMTXIdentity(tmp);
            p = tmp;
            break;
        case 1:
            p = trans;
            break;
        case 2:
            p = scale;
            break;
        case 3:
            PSMTXConcat(trans, scale, tmp);
            p = tmp;
            break;
        case 4:
            p = rot;
            break;
        case 5:
            PSMTXConcat(trans, rot, tmp);
            p = tmp;
            break;
        case 6:
            PSMTXConcat(rot, scale, tmp);
            p = tmp;
            break;
        case 7:
            PSMTXConcat(trans, rot, tmp);
            PSMTXConcat(tmp, scale, trans);
            p = trans;
            break;
    }
    PSMTXConcat(g_modeling_mtx_stack[g_modeling_mtx_lv - 1], p, g_modeling_mtx_stack[g_modeling_mtx_lv]);
}
#endif
#ifdef NONMATCHING
void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz) {
    Mtx trans, scale, iscale, rot, tmp;
    MtxPtr p;
    u32 flags;
    f32 tx, ty, tz;
    f32 nsx, nsy, nsz;
    f32 r1x, r1y, r1z;
    f32 r2x, r2y, r2z;

    tx = node->mTranslation.x;
    ty = node->mTranslation.y;
    tz = node->mTranslation.z;
    nsx = node->mScale.x;
    nsy = node->mScale.y;
    nsz = node->mScale.z;
    r1x = 2.0f * node->mRot1.x;
    r1y = 2.0f * node->mRot1.y;
    r1z = 2.0f * node->mRot1.z;
    r2x = node->mRot2.x;
    r2y = node->mRot2.y;
    r2z = node->mRot2.z;
    flags = 0;

    if (tx || ty || tz) {
        PSMTXTrans(trans, tx, ty, tz);
        flags |= 1;
    }
    if (1.0f != sx || 1.0f != sy || 1.0f == sz) {
        if (sx && sy && sz) {
            PSMTXScale(iscale, 1.0f / sx, 1.0f / sy, 1.0f / sz);
        } else {
            PSMTXScale(iscale, 1.0f, 1.0f, 1.0f);
        }
        flags |= 2;
    }
    if (1.0f != nsx || 1.0f != nsy || 1.0f == nsz) {
        PSMTXScale(scale, nsx, nsy, nsz);
        flags |= 4;
    }
    PSMTXIdentity(rot);
    if (r2z) {
        PSMTXRotRad(tmp, 'z', 0.017453292f * r2z);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r2y) {
        PSMTXRotRad(tmp, 'y', 0.017453292f * r2y);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r2x) {
        PSMTXRotRad(tmp, 'x', 0.017453292f * r2x);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r1z) {
        PSMTXRotRad(tmp, 'z', 0.017453292f * r1z);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r1y) {
        PSMTXRotRad(tmp, 'y', 0.017453292f * r1y);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    if (r1x) {
        PSMTXRotRad(tmp, 'x', 0.017453292f * r1x);
        PSMTXConcat(rot, tmp, rot);
        flags |= 8;
    }
    g_modeling_mtx_lv++;
    g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    switch (flags) {
        case 0: PSMTXIdentity(tmp); p = tmp; break;
        case 1: p = trans; break;
        case 2: p = iscale; break;
        case 3: PSMTXConcat(trans, iscale, tmp); p = tmp; break;
        case 4: p = scale; break;
        case 5: PSMTXConcat(trans, scale, tmp); p = tmp; break;
        case 6: PSMTXConcat(iscale, scale, tmp); p = tmp; break;
        case 7: PSMTXConcat(trans, iscale, tmp); PSMTXConcat(tmp, scale, trans); p = trans; break;
        case 8: p = rot; break;
        case 9: PSMTXConcat(trans, rot, tmp); p = tmp; break;
        case 10: PSMTXConcat(iscale, rot, tmp); p = tmp; break;
        case 11: PSMTXConcat(trans, iscale, tmp); PSMTXConcat(tmp, rot, trans); p = trans; break;
        case 12: PSMTXConcat(rot, scale, tmp); p = tmp; break;
        case 13: PSMTXConcat(trans, rot, tmp); PSMTXConcat(tmp, scale, trans); p = trans; break;
        case 14: PSMTXConcat(iscale, rot, tmp); PSMTXConcat(tmp, scale, trans); p = trans; break;
        case 15: PSMTXConcat(trans, iscale, tmp); PSMTXConcat(tmp, rot, trans); PSMTXConcat(trans, scale, tmp); p = tmp; break;
    }
    PSMTXConcat(g_modeling_mtx_stack[g_modeling_mtx_lv - 1], p, g_modeling_mtx_stack[g_modeling_mtx_lv]);
}
#endif

#include "sdk/texPalette.h"

#ifdef NONMATCHING
void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile)
{
  int i;
  s32 wrapFlags;
  s32 bindId;
  u32 texId;
  AnimPoseTexEntry *entry;
  TEXDescriptor *desc;
  TEXHeader *hdr;
  s32 wrapS;
  s32 wrapT;
  u32 mipmap;
  GXTlutObj tlut;
  GXTexObj obj;
  Mtx rot;
  Mtx trans;
  Mtx scale;
  Mtx tmp;
  MtxPtr m;
  AnimTexMtx *anim;
  f32 scaleS;
  f32 scaleT;
  f32 transS;
  f32 transT;
  f32 rotate;
  u32 flags;
  s32 texMtx;
  u32 j;
  for (i = 0; i < texCount; i++)
  {
    s32 id = texIdRemap[(u32) ((texCount - i) - 1)];
    entry = &pTexEntries[id];
    bindId = entry->bindId + animEntries[id].mTexBindIdx;
    if ((bindId < 0) || (bindId >= texBindsCapacity))
    {
      bindId = 0;
            printf("Error: dispSetTevMode: \203x\201[\203X\203\202\203f\203\213%s \203A\203j\203\201 %s \223\340\202\305 \203t\203\214\201[\203\200\203G\203N\203X\203e\203\223\203V\203\207\203\223\202\314\220\335\222\350\202\252\215s\202\355\202\352\202\304\202\242\202\334\202\267\202\252\201A\212Y\223\226\202\267\202\351\203e\203N\203X\203`\203\203\202\252\202\240\202\350\202\334\202\271\202\361 \nframeExt\224\324\215\206 %d? \202\252\226\263\202\242\202\346\202\244\202\305\202\267\201B\203\202\203f\203\213\202\334\202\275\202\315\203A\203j\203\201\202\311\217C\220\263\202\252\225K\227v\202\305\202\267\201BtextureIdx=%d\n",
                   animPoseGetBaseData(wp->mpCurPose)->fileName,
                   animPoseGetBaseData(wp->mpCurPose)->mpAnims[wp->mpCurPose->animId].name);
    }
    wrapFlags = entry->wrapFlags;
    texId = *((u32 *) (((u8 *) (&texBinds[bindId])) + 4));
    if ((*((s32 *) (((u8 *) (&texBinds[bindId])) + 8))) != 0)
    {
      continue;
    }
    if (TEXGet(*((TEXPalette **) texFile->handle->data), texId)->CLUTHeader)
    {
      desc = TEXGet(*((TEXPalette **) texFile->handle->data), texId);
      hdr = desc->textureHeader;
      wrapS = hdr->wrapS;
      wrapT = hdr->wrapT;
      if (wrapFlags >= 0)
      {
        if (wrapFlags & 4)
        {
          wrapS = GX_MIRROR;
        }
        else
        {
          wrapS = wrapFlags;
          wrapS = wrapS & 1;
        }
        if (wrapFlags & 8)
        {
          wrapT = GX_MIRROR;
        }
        else
        {
          wrapT = (wrapFlags >> 1) & 1;
        }
      }
      mipmap = hdr->minLOD != hdr->maxLOD;
      GXInitTlutObj(&tlut, desc->CLUTHeader->data, desc->CLUTHeader->format, desc->CLUTHeader->numEntries);
      GXInitTexObjCI(&obj, desc->textureHeader->data, desc->textureHeader->width, desc->textureHeader->height, (GXCITexFmt) desc->textureHeader->format, wrapS, wrapT, mipmap, 0);
      hdr = desc->textureHeader;
      GXInitTexObjLOD(&obj, hdr->minFilter, hdr->magFilter, hdr->minLOD, hdr->maxLOD, hdr->LODBias, (GXBool) 0, hdr->edgeLODEnable, GX_ANISO_1);
      GXLoadTlut(&tlut, 0);
      GXLoadTexObj(&obj, (GXTexMapID) i);
    }
    else
    {
      desc = TEXGet(*((TEXPalette **) texFile->handle->data), texId);
      hdr = desc->textureHeader;
      wrapS = hdr->wrapS;
      wrapT = hdr->wrapT;
      if (wrapFlags >= 0)
      {
        if (wrapFlags & 4)
        {
          wrapS = GX_MIRROR;
        }
        else
        {
          wrapS = wrapFlags;
          wrapS = wrapS & 1;
        }
        if (wrapFlags & 8)
        {
          wrapT = GX_MIRROR;
        }
        else
        {
          wrapT = (wrapFlags >> 1) & 1;
        }
      }
      GXInitTexObj(&obj, hdr->data, hdr->width, hdr->height, (GXTexFmt) hdr->format, wrapS, wrapT, hdr->minLOD != hdr->maxLOD);
      hdr = desc->textureHeader;
      GXInitTexObjLOD(&obj, hdr->minFilter, hdr->magFilter, hdr->minLOD, hdr->maxLOD, hdr->LODBias, (GXBool) 0, hdr->edgeLODEnable, GX_ANISO_1);
      GXLoadTexObj(&obj, (GXTexMapID) i);
    }
  }

  for (i = 0; i < texCount; i++)
  {
    flags = 0;
    anim = &animEntries[texIdRemap[(u32) ((texCount - i) - 1)]];
    rotate = anim->mRotate;
    scaleS = anim->mScaleS;
    scaleT = anim->mScaleT;
    transS = anim->mTransS;
    transT = anim->mTransT;
    if (rotate != 0.0f)
    {
      flags |= 1;
      PSMTXTrans(tmp, 0.5f, 0.5f, 0.0f);
      PSMTXRotRad(rot, 'z', 0.017453292f * (-rotate));
      PSMTXConcat(tmp, rot, trans);
      PSMTXTrans(tmp, -0.5f, -0.5f, 0.0f);
      PSMTXConcat(trans, tmp, rot);
    }
    if (((transS != 0.0f) || (transT != 0.0f)) || (scaleT != 0.0f))
    {
      flags |= 2;
      PSMTXTrans(trans, transS, (1.0f - transT) - scaleT, 0.0f);
    }
    if ((scaleS != 1.0f) || (scaleT != 1.0f))
    {
      flags |= 4;
      PSMTXScale(scale, scaleS, scaleT, 1.0f);
    }
    switch (flags)
    {
      case 0:
        GXSetTexCoordGen2((GXTexCoordID) i, GX_TG_MTX2x4, (GXTexGenSrc) (GX_TG_TEX0 + i), GX_IDENTITY, (GXBool) 0, GX_PTIDENTITY);
        continue;

      case 1:
        m = rot;
        break;

      case 2:
        m = trans;
        break;

      case 3:
        PSMTXConcat(rot, trans, tmp);
        m = tmp;
        break;

      case 4:
        m = scale;
        break;

      case 5:
        PSMTXConcat(rot, scale, tmp);
        m = tmp;
        break;

      case 6:
        PSMTXConcat(trans, scale, tmp);
        m = tmp;
        break;

      case 7:
        PSMTXConcat(rot, trans, tmp);
        PSMTXConcat(tmp, scale, trans);
        m = trans;
        break;

    }

    j = i * 3;
    texMtx = GX_TEXMTX0 + j;
    GXSetTexCoordGen2((GXTexCoordID) i, GX_TG_MTX2x4, (GXTexGenSrc) (GX_TG_TEX0 + i), texMtx, (GXBool) 0, GX_PTIDENTITY);
    GXLoadTexMtxImm(m, texMtx, GX_MTX2x4);
  }

}
#endif

inline BOOL animSetMaterial_ChangeTexture(AnimationPoseData* data, AnimPoseShapeDraw* draw, AnimationPose* pose, GXTexObj* texObj, void** texData, Mtx mtx, s32 texType) {
    AnimTexBind* bind;
    s32 bindCount;
    AnimTexMtx* texAnim;
    AnimPoseTexEntry* texEntry;
    s32 texCount;
    s32 dataId, bindId, frameExt;
    GXTexObj* smartObj;
    int i;

    bind = data->texBinds;
    bindCount = data->texBindCount;
    texAnim = pose->mpTexAnimEntries;
    texEntry = data->texData;
    texCount = draw->texCount;

    for (i = 0; i < texCount; i++) {
        dataId = texCount - i - 1;
        dataId = draw->texDataIds[dataId];
        frameExt = texAnim[dataId].mTexBindIdx;
        bindId = texEntry[dataId].bindId + frameExt;
        if (bindId < 0 || bindId >= bindCount) {
            bindId = 0;
            //"Error: animSetMaterial_ChangeTexture: テクスチャがありません frameExt=%d\n"
            printf("Error: animSetMaterial_ChangeTexture: "
                   "\x83\x65\x83\x4E\x83\x58\x83\x60\x83\x83\x82\xAA\x82\xA0\x82\xE8\x82\xDC\x82\xB9\x82\xF1 "
                   "frameExt=%d\n",
                   frameExt);
        }
        if (bind[bindId].texType == texType) {
            if (texObj) {
                smartObj = smartTexObj(texObj, texData);
                GXLoadTexObj(smartObj, i);
                if (mtx) {
                    GXLoadTexMtxImm(mtx, GX_TEXMTX0 + (u32)(i * 3), GX_MTX2x4);
                    GXSetTexCoordGen(i, GX_TG_MTX2x4, GX_TG_TEX0 + i, GX_TEXMTX0 + (u32)(i * 3));
                } else {
                    GXSetTexCoordGen(i, GX_TG_MTX2x4, GX_TG_TEX0 + i, GX_IDENTITY);
                }
            }
            return TRUE;
        }
    }
    return FALSE;
}

#ifdef NONMATCHING
static s32 tbl[4] = { 2, 1, 3, 0 };  // target tbl$1109 (g5_tbl_s1109 in the stopgap)
#endif

#ifdef NONMATCHING
void materialProc(s32 shapeId, s32 xluStage)
{
  int i;
  s32 drawCount;
  AnimPoseShapeDraw *draw;
  CameraEntry *camera;
  AnimationPose *pose;
  GXTexObj *texObj;
  GXTexObj *currTexObj;
  BOOL texChange1;
  BOOL check1;
  s32 dispMode;
  AnimPoseShape *shape;
  Mtx camMtx;
  Mtx invCamMtx;
  Vec lightPos;
  if (shapeId != (-1))
  {
    camera = camGetCurPtr();
    PSMTXConcat(camera->view, *g_modeling_mtx, camMtx);
    GXLoadPosMtxImm(camMtx, 0);
    PSMTXInvXpose(camMtx, invCamMtx);
    GXLoadNrmMtxImm(invCamMtx, 0);
    GXSetCurrentMtx(0);
    shape = &wp->mpCurPoseData->shapes[shapeId];
    dispMode = shape->dispMode;
    drawCount = shape->shapeDrawCount;
    draw = &wp->mpCurPoseData->draws[shape->shapeDrawStart];
    if ((dispMode == 0 && wp->currDispMode == 2) || dispMode == wp->currDispMode || wp->mpCurPose->materialColor.a != 0xFF || wp->mpCurPose->materialColor2.a != 0xFF)
    {
      GXSetCullMode(tbl[shape->cullMode]);
      for (i = 0; i < drawCount; i++, draw++)
      {
        s32 texCount = draw->texCount;
        if ((u32)wp->mpCurPose->disableDraw == 0)
        {
          lightPos = (Vec){0.0f, 0.0f, 0.0f};
          PSMTXMultVec(*g_modeling_mtx, &lightPos, &lightPos);
          mapSetMaterialLight(wp->mpCurPose->materialLightFlag, lightPos);
          animSetMaterial_Texture(draw->texCount, draw->texDataIds, wp->mpCurPoseData->texData, wp->mpCurPose->mpTexAnimEntries, wp->mpCurPoseData->texBindCount, wp->mpCurPoseData->texBinds, &wp->textures[wp->files[wp->mpCurPose->fileId].textureId]);
          mapSetMaterialLastStageBlend(wp->mpCurPose->materialFlag, wp->mpCurPose->materialColor, wp->mpCurPose->materialColor2);
          camera = camGetPtr(CAMERA_3D);
          if (camGetCurPtr() == camera)
          {
            mapSetMaterialFog();
          }
          mapSetMaterialTev(texCount, draw->drawMode, wp->mpCurPose->materialFlag, *g_modeling_mtx);
        }
        pose = wp->mpCurPose;
        if ((u32)pose->typeFlags != 0)
        {
          texChange1 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, wp->mpTexObjs[0], wp->mpTexDatas[0], *wp->paperMtxPtr[0], 1);
          check1 = texChange1;
          if (!texChange1)
          {
            check1 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, wp->mpCurPose, wp->mpTexObjs[1], wp->mpTexDatas[1], *wp->paperMtxPtr[1], 2);
          }
          if (check1 && (!draw->drawMode))
          {
            currTexObj = wp->mpCurTexObj;
            if (currTexObj)
            {
              smartTexObj(currTexObj, wp->mpCurTexData);
              if (wp->currDispMode != 3)
              {
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_FALSE);
                GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
              }
              texObj = wp->mpTexObjs[texChange1 == 0];
              if (texObj)
              {
                GXLoadTexObj(texObj, GX_TEXMAP0);
                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
                GXLoadTexMtxImm(*wp->paperMtxPtr[!texChange1], GX_TEXMTX0, GX_MTX2x4);
              }
              GXLoadTexObj(currTexObj, GX_TEXMAP1);
              GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE, GX_PTIDENTITY);
              GXLoadTexMtxImm(*wp->paperMtxPtr[2], GX_TEXMTX1, GX_MTX2x4);
              mapSetMaterialTev(2, 12, wp->mpCurPose->materialFlag, *g_modeling_mtx);
            }
          }
        }
        pose = wp->mpCurPose;
        if (pose->flags & 0x10)
        {
          texObj = wp->mpTexObjs[0];
          if (texObj)
          {
            if (wp->paperMtxPtr[0])
            {
              animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, texObj, wp->mpTexDatas[0], *wp->paperMtxPtr[0], 1);
            }
          }
        }
      }

    }
  }
}
#endif


// I'm so sorry, whoever gets tasked with matching this function
// note: I detect at least 8 inlined functions here, good luck finding the separation
#ifdef NONMATCHING
void renderProc(s32 shapeId, s32 unused) {
    int i;
    CameraEntry* camera;
    AnimationPoseData* data;
    AnimPoseShape *shapes, *shape;
    AnimPoseShapeDraw *draws, *draw;
    s32 dispMode, drawId;
    s32 posFirstVtx, nrmFirstVtx, clr0FirstVtx;

    f32* buffer;
    s32 nrmVtxSize;
    s32 texCount;
    AnimationPose* pose;
    Mtx* mtx;
    GXTexObj* texObj;
    BOOL texChange1, check1, texChange2, check2;
    GXTexObj* currTexObj;
    s8* texIds;
    s32* firstId;
    AnimDrawCallEntry* drawCall;
    s32 drawCallCount;
    GXColor* clr0VtxPtr;
    s32 posFirstId, nrmFirstId, clr0FirstId;
    Vec *nrmVtxPtr, *posVtxPtr;

    s32 count;
    u16 *posIndexPtr, *nrmIndexPtr, *clr0IndexPtr, *texIndexPtr;
    s32 firstDrawId;
    s32 index;
    s32 texIndex;

    int j, k, l, k2;

    // stack variables
    s32 clr0VtxSize, posVtxSize; // TODO: make sure stack, +0xB0, +0xAC
    s32 drawCount;               // TODO: make sure stack, +0xA8
    Mtx camMtx, invCamMtx;
    f32* texVtxIndices[8];
    Vec lightPos, lightPos2; // TODO: rename? 2 is probably implicit stack copy

    if (shapeId != -1) {
        camera = camGetCurPtr();
        MTXConcat(camera->view, *g_modeling_mtx, camMtx);
        GXLoadPosMtxImm(camMtx, 0);
        MTXInvXpose(camMtx, invCamMtx);
        GXLoadNrmMtxImm(invCamMtx, 0);
        GXSetCurrentMtx(0);

        data = wp->mpCurPoseData;
        shapes = data->shapes;
        draws = data->draws;
        shape = &shapes[shapeId];
        dispMode = shape->dispMode;
        drawId = shape->shapeDrawStart;
        posFirstVtx = shape->vtxPos.first;
        nrmFirstVtx = shape->vtxNrm.first;
        clr0FirstVtx = shape->vtxClr0.first;
        drawCount = shape->shapeDrawCount;
        draw = &draws[drawId];

        if ((dispMode == 0 && wp->currDispMode == 2) || dispMode == wp->currDispMode ||
            wp->mpCurPose->materialColor.a != 0xFF || wp->mpCurPose->materialColor2.a != 0xFF) {
            GXSetCullMode(tbl[shape->cullMode]);
            data = wp->mpCurPoseData;
            clr0VtxSize = (s32)sizeof(GXColor) * clr0FirstVtx;
            buffer = data->texVtxBuffer;
            texVtxIndices[0] = &buffer[2 * shape->vtxTex[0].first];
            texVtxIndices[1] = &buffer[2 * shape->vtxTex[1].first];
            texVtxIndices[2] = &buffer[2 * shape->vtxTex[2].first];
            texVtxIndices[3] = &buffer[2 * shape->vtxTex[3].first];
            texVtxIndices[4] = &buffer[2 * shape->vtxTex[4].first];
            texVtxIndices[5] = &buffer[2 * shape->vtxTex[5].first];
            texVtxIndices[6] = &buffer[2 * shape->vtxTex[6].first];
            texVtxIndices[7] = &buffer[2 * shape->vtxTex[7].first];
            nrmVtxSize = (s32)sizeof(Vec) * nrmFirstVtx;
            posVtxSize = (s32)sizeof(Vec) * posFirstVtx;

            for (i = 0; i < drawCount; i++, draw++) {
                texCount = draw->texCount;
                if ((u32)wp->mpCurPose->disableDraw == 0) {
                    lightPos = (Vec){ 0.0f, 0.0f, 0.0f };
                    MTXMultVec(*g_modeling_mtx, &lightPos, &lightPos);
                    lightPos2 = lightPos;
                    mapSetMaterialLight(wp->mpCurPose->materialLightFlag, lightPos2);
                    animSetMaterial_Texture(draw->texCount, draw->texDataIds, wp->mpCurPoseData->texData,
                                            wp->mpCurPose->mpTexAnimEntries, wp->mpCurPoseData->texBindCount,
                                            wp->mpCurPoseData->texBinds,
                                            &wp->textures[wp->files[wp->mpCurPose->fileId].textureId]);
                    mapSetMaterialLastStageBlend(wp->mpCurPose->materialFlag, wp->mpCurPose->materialColor,
                                                 wp->mpCurPose->materialColor2);
                    camera = camGetPtr(CAMERA_3D);
                    if (camGetCurPtr() == camera) {
                        mapSetMaterialFog();
                    }
                    mapSetMaterialTev(texCount, draw->drawMode, wp->mpCurPose->materialFlag, *g_modeling_mtx);
                }
                pose = wp->mpCurPose;
                if ((u32)pose->typeFlags != 0) {
                    texChange1 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, wp->mpTexObjs[0], wp->mpTexDatas[0], *wp->paperMtxPtr[0], 1);
                    check1 = texChange1;
                    if (!texChange1) {
                        pose = wp->mpCurPose;
                        texChange2 = animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, wp->mpTexObjs[1], wp->mpTexDatas[1], *wp->paperMtxPtr[1], 2);
                        check1 = texChange2;
                        check2 = texChange2;
                    } else {
                        check2 = FALSE;
                    }

                    if (check1 && (texChange1 && (s32)wp->field_0xD8 == 0 || check2 && (s32)wp->field_0xDC == 0) && !draw->drawMode) {
                        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_RASA);
                    }
                    if (check1 && !draw->drawMode) {
                        currTexObj = wp->mpCurTexObj;
                        if (currTexObj) {
                            smartTexObj(currTexObj, wp->mpCurTexData);
                            if (wp->currDispMode != 3) {
                                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                                GXSetZCompLoc(GX_FALSE);
                                GXSetAlphaCompare(GX_GEQUAL, 0x80u, GX_AOP_OR, GX_NEVER, 0);
                            }
                            texObj = wp->mpTexObjs[texChange1 == 0];
                            if (texObj) {
                                GXLoadTexObj(texObj, GX_TEXMAP0);
                                GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE,
                                                  GX_PTIDENTITY);
                                GXLoadTexMtxImm(*wp->paperMtxPtr[!texChange1], GX_TEXMTX0, GX_MTX2x4);
                            }
                            GXLoadTexObj(currTexObj, GX_TEXMAP1);
                            GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX1, GX_FALSE,
                                              GX_PTIDENTITY);
                            GXLoadTexMtxImm(*wp->paperMtxPtr[2], GX_TEXMTX1, GX_MTX2x4);
                            mapSetMaterialTev(2, 12, wp->mpCurPose->materialFlag, *g_modeling_mtx);
                        }
                    }
                }

                pose = wp->mpCurPose;
                if (pose->flags & 0x10) {
                    texObj = wp->mpTexObjs[0];
                    if (texObj) {
                        mtx = wp->paperMtxPtr[0];
                        if (mtx) {
                            animSetMaterial_ChangeTexture(wp->mpCurPoseData, draw, pose, texObj, wp->mpTexDatas[0], *mtx, 1);
                        }
                    }
                }

                texIds = (s8*)draw->texArrayIds;
                firstId = draw->firstIdTex;
                data = wp->mpCurPoseData; // inlined function here
                drawCall = &data->drawCalls[draw->firstDrawCall];
                texCount = draw->texCount;
                drawCallCount = draw->drawCallCount;
                clr0VtxPtr = (GXColor*)((u8*)data->clr0VtxBuffer + clr0VtxSize);
                posFirstId = draw->firstIdPos;
                nrmFirstId = draw->firstIdNrm;
                clr0FirstId = draw->firstIdClr0;

                if ((s32)wp->mbUseFloatScratch != 0) {
                    nrmVtxPtr = (Vec*)((u8*)wp->vtxArrayNrm + nrmVtxSize);
                    posVtxPtr = (Vec*)((u8*)wp->vtxArrayPos + posVtxSize);
                } else {
                    pose = wp->mpCurPose;
                    nrmVtxPtr = (Vec*)((u8*)pose->mpVtxArrayNrm + nrmVtxSize);
                    posVtxPtr = (Vec*)((u8*)pose->mpVtxArrayPos + posVtxSize);
                }
                GXClearVtxDesc();
                GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_POS, posVtxPtr, sizeof(Vec));
                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
                GXSetArray(GX_VA_NRM, nrmVtxPtr, sizeof(Vec));
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
                GXSetArray(GX_VA_CLR0, clr0VtxPtr, sizeof(GXColor));

                if (texCount == 1) { // just use texIndex[0]
                    GXSetVtxDesc(GX_VA_TEX0, GX_INDEX16);
                    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
                    GXSetArray(GX_VA_TEX0, texVtxIndices[texIds[0]], sizeof(f32) * 2);
                    for (j = 0; j < drawCallCount; j++, drawCall++) {
                        firstDrawId = drawCall->first;
                        data = wp->mpCurPoseData;
                        posIndexPtr = (u16*)((u32*)data->posIndex + (firstDrawId + posFirstId)) + 1;
                        nrmIndexPtr = (u16*)((u32*)data->nrmIndex + (firstDrawId + nrmFirstId)) + 1;
                        clr0IndexPtr = (u16*)((u32*)data->clr0Index + (firstDrawId + clr0FirstId)) + 1;
                        texIndexPtr = (u16*)((u32*)data->texIndex[texIds[0]] + (firstDrawId + firstId[texIds[0]])) + 1;
                        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, count = (u16)drawCall->count);
                        for (k = count; k > 0; k--) {
                            GXPosition1x16(*posIndexPtr);
                            posIndexPtr += 2;
                            GXNormal1x16(*nrmIndexPtr);
                            nrmIndexPtr += 2;
                            GXColor1x16(*clr0IndexPtr);
                            clr0IndexPtr += 2;
                            GXTexCoord1x16(*texIndexPtr);
                            texIndexPtr += 2;
                        }
                    }
                } else { // enumerate texIndex
                    for (j = 0; j < texCount; j++) {
                        GXSetVtxDesc(GX_VA_TEX0 + j, GX_INDEX16);
                        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0 + j, GX_TEX_ST, GX_F32, 0);
                        GXSetArray(GX_VA_TEX0 + j, texVtxIndices[texIds[texCount - j - 1]], sizeof(f32) * 2);
                    }
                    for (j = 0; j < drawCallCount; j++, drawCall++) {
                        firstDrawId = drawCall->first;
                        data = wp->mpCurPoseData;
                        count = (u16)drawCall->count;
                        posIndexPtr = (u16*)((u32*)data->posIndex + (firstDrawId + posFirstId)) + 1;
                        nrmIndexPtr = (u16*)((u32*)data->nrmIndex + (firstDrawId + nrmFirstId)) + 1;
                        clr0IndexPtr = (u16*)((u32*)data->clr0Index + (firstDrawId + clr0FirstId)) + 1;
                        GXBegin(GX_TRIANGLEFAN, GX_VTXFMT0, count);
                        for (k2 = 0; k2 < count; k2++) {
                            GXPosition1x16(*posIndexPtr);
                            GXNormal1x16(*nrmIndexPtr);
                            GXColor1x16(*clr0IndexPtr);
                            for (l = texCount, index = 0; l > 0; l--, index++) {
                                texIndex = texIds[(u32)(texCount - index - 1)];
                                GXTexCoord1x16((&((u32*)wp->mpCurPoseData->texIndex[texIndex])[firstDrawId + firstId[texIndex]])[k2]);
                            }
                            posIndexPtr += 2;
                            nrmIndexPtr += 2;
                            clr0IndexPtr += 2;
                        }
                    }
                }
            }
        }
    }
}
#endif

// dispProc

void materialProc(s32 shapeId, s32 xluStage);
void vivihimo(Mtx a, Mtx b, f32 speed, f32 scale, f32 offA, f32 offB);

#ifdef NONMATCHING
void dispProc(s32 parentId, s32 groupId, s32 xluStage, s32 arg3, f32 arg4) {
    AnimPoseGroup* group;
    AnimPoseGroup* parent;
    AnimPoseNode* node;
    AnimationPose* pose;
    AnimationPoseData* data;
    f32 sx, sy, sz;

    if (groupId == -1) {
        return;
    }
    pose = wp->mpCurPose;
    data = wp->mpCurPoseData;
    group = &data->groups[groupId];
    if (*(s8*)&pose->mpGroupVisibility[group->visibilityId]) {
        pose = wp->mpCurPose;
        node = (AnimPoseNode*)((u32*)pose->mpNodes + group->nodeId);
        if (group->useSSC) {
            if (parentId == -1) {
                sx = sy = sz = 1.0f;
            }
            else {
                parent = &data->groups[parentId];
                if (!parent->useSSC) {
                    sx = sy = sz = 1.0f;
                }
                else {
                    AnimPoseNode* pnode = (AnimPoseNode*)((u32*)pose->mpNodes + parent->nodeId);
                    sx = pnode->mScale.x;
                    sy = pnode->mScale.y;
                    sz = pnode->mScale.z;
                }
            }
            pushGXModelMtx_JointNode__(node, sx, sy, sz);
        }
        else {
            pushGXModelMtx_TransformNode__(node);
        }
        if (wp->mpCurPose->flags & 0x40) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = (*g_modeling_mtx)[0][3];
            pos.y = (*g_modeling_mtx)[1][3];
            pos.z = (*g_modeling_mtx)[2][3];
            (*wp->mpCurPose->worldPositions)[groupId] = pos;
        }
        if (wp->mpCurPose->flags & 0x80) {
            PSMTXCopy(*g_modeling_mtx, (*wp->mpCurPose->worldMatrices)[groupId]);
        }
        pose = wp->mpCurPose;
        if (pose->flags & 0x20 && groupId == pose->vivianGroupNo[0]) {
            Mtx* m;
            MtxPtr mat;
            f32* speed;
            f32 offA, offB;
            int i, j;
            s32 type;

            offB = offA = 0.0f;
            type = pose->vivianType;
            speed = (f32*)vivihimoData[type] + pose->animId * 2;
            m = g_modeling_mtx;
            mat = pose->matrix;
            switch (type) {
                case 1:
                    offA = -2.0f;
                    offB = 0.5f;
                    break;
                case 2:
                    offA = -3.0f;
                    offB = 0.5f;
                    break;
                case 3:
                    offA = -1.0f;
                    offB = 0.5f;
                    break;
            }
            materialProc(group->shapeId, xluStage);
            vivihimo(*m, mat, speed[0], speed[1], offA, offB);
            wp->mpCurPose->flags &= ~0x20;
            for (i = 0; i < 3; i++) {
                for (j = 0; j < 3; j++) {
                    mat[i][j] += 0.04f * ((*m)[i][j] - mat[i][j]);
                }
            }
        }
        else {
            if (pose->dispCallback) {
                ((void (*)(void*, s32, Mtx*))pose->dispCallback)(pose->dispUserDataCallback, groupId, g_modeling_mtx);
            }
            renderProc(group->shapeId, xluStage);
            dispProc(groupId, group->childGroupId, xluStage, arg3, arg4);
        }
        g_modeling_mtx_lv--;
        g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    }
    dispProc(groupId, group->brotherGroupId, xluStage, arg3, arg4);
}
#endif


#ifdef NONMATCHING
void animPoseDraw(s32 poseId, f32 x, f32 y, f32 z, f32 rotY, f32 scale, s32 xluMode) {
    Mtx matrix;

    MTXTrans(matrix, x, y, z);
    animPoseDrawMtx(poseId, matrix, xluMode, rotY, scale);
}
#endif

// _animPoseDrawMtx
extern BOOL mapTestXLU(u32 flags, GXColor* color, GXColor* matColor);
extern double atan2(double y, double x);
void animPoseMainSub(AnimationPose* pose);

static inline f32 _animClampAngle(f32 a) {
    while (a < -360.0f) a += 360.0f;
    while (a >= 360.0f) a -= 360.0f;
    if (a < 0.0f) a += 360.0f;
    return a;
}

static inline f32 _animClampAngle2(f32 a) {
    while (a < -360.0f) a += 360.0f;
    while (a >= 360.0f) a -= 360.0f;
    return a;
}

static inline f32 _animCamAngle(void) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    return _animClampAngle(57.29579f * (f32)atan2(-(cam->cameraAt.x - cam->cameraPos.x), -(cam->cameraAt.z - cam->cameraPos.z)));
}

#ifdef NONMATCHING
void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale) {
    Mtx result;
    Mtx tmp2;
    Mtx tmp1;
    Mtx tmp3;
    GXColor col1;
    GXColor col2;
    AnimationPoseData* data;
    AnimData* anim;
    s32 arg3, arg4;
    f32 argf;
    f32 diff;
    s32 mode;

    data = animPoseGetBaseData(pose);
    arg3 = *(s32*)((u8*)pose + 0x28);
    arg4 = *(s32*)((u8*)pose + 0x2C);
    argf = *(f32*)((u8*)pose + 0x30);
    anim = data->mpAnims[pose->animId].data;
    if (anim == NULL) {
        return;
    }
    if (wp->inBattle && pose->type == 0) {
        return;
    }
    if (!wp->inBattle && pose->type == 1) {
        return;
    }
    if (!(xluMode == 2 && (data->flags & 1)) && !(data->flags & (1 << xluMode))) {
        return;
    }
    mode = xluMode;
    col2 = pose->materialColor2;
    col1 = pose->materialColor;
    if (mapTestXLU(pose->materialFlag, &col1, &col2)) {
        mode = 3;
    }
    if (pose->gxCallback != NULL) {
        pose->gxCallback(mode);
    }
    else {
        switch (mode) {
            case 1:
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
                break;
            case 0:
            case 2:
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                GXSetBlendMode(GX_BM_NONE, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_FALSE);
                GXSetAlphaCompare(GX_GEQUAL, 0x80, GX_AOP_OR, GX_NEVER, 0);
                break;
            case 3:
                GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_CLEAR);
                GXSetZCompLoc(GX_TRUE);
                GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0);
                break;
        }
        wp->currDispMode = mode;
    }
    if (pose->flags & 8) {
        rotY += -90.0f;
        pose->peraRotY = rotY;
        diff = _animClampAngle2(_animCamAngle() - pose->peraRotY);
        if ((diff > 90.0f && diff <= 270.0f) || (diff < -90.0f && diff >= -270.0f)) {
            pose->peraTargetRotY = _animClampAngle2(180.0f + _animCamAngle());
        }
        else {
            pose->peraTargetRotY = _animCamAngle();
        }
        while (pose->peraTargetRotY - pose->rotationY > 180.0f) {
            pose->rotationY += 360.0f;
        }
        while (pose->peraTargetRotY - pose->rotationY < -180.0f) {
            pose->rotationY -= 360.0f;
        }
        if (pose->flags & 0x100) {
            pose->rotationY = pose->peraTargetRotY;
        }
        else {
            pose->rotationY += 0.1f * (pose->peraTargetRotY - pose->rotationY);
        }
        rotY = pose->rotationY;
        if (rotY != 0.0f) {
            PSMTXRotRad(tmp2, 'y', 0.017453292f * rotY);
            PSMTXConcat(matrix, tmp2, result);
            matrix = result;
        }
        if (pose->field_0x78 == -1.0f) {
            PSMTXScale(tmp2, 1.0f, 1.0f, -1.0f);
            PSMTXConcat(matrix, tmp2, result);
            matrix = result;
        }
    }
    else if (rotY) {
        PSMTXRotRad(tmp1, 'y', 0.017453292f * rotY);
        PSMTXConcat(matrix, tmp1, result);
        matrix = result;
    }
    if (scale != 1.0f) {
        PSMTXScale(tmp3, scale, scale, scale);
        PSMTXConcat(matrix, tmp3, result);
        matrix = result;
    }
    if (pose->lastFrameZero == -1) {
        animPoseMainSub(pose);
    }
    g_modeling_mtx_lv = 0;
    g_modeling_mtx = &g_modeling_mtx_stack[0];
    PSMTXCopy(matrix, *g_modeling_mtx);
    wp->mpCurPose = pose;
    wp->mpCurAnimData = anim;
    wp->mpCurPoseData = data;
    if ((s32)wp->mbUseFloatScratch != 0) {
        DCFlushRange(wp->vtxArrayPos, animPoseGetBaseData(pose)->mBufferPosNum * sizeof(Vec));
        DCFlushRange(wp->vtxArrayNrm, animPoseGetBaseData(pose)->mBufferNrmNum * sizeof(Vec));
    }
    else {
        DCFlushRange(pose->mpVtxArrayPos, animPoseGetBaseData(pose)->mBufferPosNum * sizeof(Vec));
        DCFlushRange(pose->mpVtxArrayNrm, animPoseGetBaseData(pose)->mBufferNrmNum * sizeof(Vec));
    }
    GXInvalidateVtxCache();
    dispProc(-1, data->groupCount - 1, arg3, arg4, argf);
}
#endif



#define PDM_F(p, off) (*(f32*)((u8*)(p) + (off)))

inline void animSetPaperMtx(Mtx m0, Mtx* m1, Mtx* m2) {
    if (m0 == NULL) {
        wp->paperMtxPtr[0] = NULL;
    }
    else {
        PSMTXCopy(m0, wp->paperMtx[0]);
        wp->paperMtxPtr[0] = &wp->paperMtx[0];
    }
    wp->paperMtxPtr[1] = m1;
    wp->paperMtxPtr[2] = m2;
}

#ifdef NONMATCHING
void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale)
{
  Mtx m1;
  static Mtx mtx;
  Mtx m2;
  Mtx scl;
  Mtx rot;
  Mtx tmp;
  AnimationPose *pose;
  AnimationPose *paper;
  AnimationPose *p2;
  AnimationPoseData *data;
  const char *name;
  s32 animId;
  s32 new_var[2];
  pose = &wp->poses[poseId];
  if (pose->paperId != (-1))
  {
    if (pose->flags & 0xC0)
    {
      Mtx *m;
      data = *((AnimationPoseData **) wp->files[pose->fileId].handle->data);
      m = (Mtx *) matrix;
      if ((!(pose->flags & 8)) && rotY)
      {
        PSMTXRotRad(rot, 'y', 0.017453292f * rotY);
        PSMTXConcat(matrix, rot, tmp);
        m = &tmp;
      }
      if (1.0f != scale)
      {
        PSMTXScale(scl, scale, scale, scale);
        PSMTXConcat(*m, scl, tmp);
        m = &tmp;
      }
      g_modeling_mtx_lv = 0;
      g_modeling_mtx = &g_modeling_mtx_stack[0];
      PSMTXCopy(*m, *g_modeling_mtx);
      wp->mpCurPose = pose;
      wp->mpCurPoseData = data;
      evalProc(-1, data->groupCount - 1);
    }
    paper = &wp->poses[pose->paperId];
    data = *((AnimationPoseData **) wp->files[paper->fileId].handle->data);
    if (((xluMode != 2) || (!(data->flags & 1))) && (!(data->flags & (1 << xluMode))))
    {
      return;
    }
    if (paper->typeFlags & 2)
    {
      new_var[1] = data->mBufferPosNum;
      new_var[0] = data->mBufferNrmNum;
      if ((new_var[1] + new_var[0]) <= wp->mFloatScratchRP)
      {
        if ((wp->mFloatScratchWP + (new_var[1] + new_var[0])) > wp->mFloatScratchRP)
        {
          wp->mFloatScratchWP = 0;
        }
        wp->mbUseFloatScratch = 1;
        wp->vtxArrayPos = &wp->mpFloatScratch[wp->mFloatScratchWP];
        wp->mFloatScratchWP += new_var[1];
        wp->vtxArrayNrm = &wp->mpFloatScratch[wp->mFloatScratchWP];
        wp->mFloatScratchWP += new_var[0];
      }
      name = (const char *) (*((s32 *) pose->field_0x94));
      if (name != ((const char *) (-1)))
      {
        p2 = &wp->poses[pose->paperId];
        animId = animPoseGetAnimIdx(*((AnimationPoseData **) wp->files[p2->fileId].handle->data), name);
        if (animId != p2->animId)
        {
          p2->animId = animId;
          if ((p2->paperId != (-1)) && (p2->flags & 2))
          {
            p2->flags |= 4;
          }
          p2->localTime = animTimeGetTime(p2->type);
          p2->lastFrameZero = -1;
          p2->lastFrameTime = 0.0f;
          p2->field_0x80 = 0;
          p2->loopTime = 0.0f;
        }
      }
      paper->localTime = animTimeGetTime(paper->type);
      paper->lastFrameZero = -1;
      paper->lastFrameTime = 0.0f;
      paper->field_0x80 = 0;
      paper->loopTime = 0.0f;
      paper->localTime = pose->mLocalTimeInit;
      animPoseMain(pose->paperId);
    }
    {
      void *t0 = *((void **) (((u8 *) pose) + 0x98));
      void *t1 = *((void **) (((u8 *) pose) + 0x9C));
      wp->mpTexObjs[0] = (t0) ? ((GXTexObj *) (((u8 *) pose) + 0xA0)) : ((void *) 0);
      wp->mpTexObjs[1] = (t1) ? ((GXTexObj *) (((u8 *) pose) + 0xC0)) : ((void *) 0);
      wp->mpCurTexObj = (void *) 0;
      wp->mpTexDatas[0] = t0;
      wp->mpTexDatas[1] = t1;
      wp->mpCurTexData = (void *) 0;
      wp->field_0xD8 = 1;
      p2->field_0x80 = 0;
      wp->field_0xDC = 1;
    }
    paper->materialFlag = pose->materialFlag;
    paper->materialLightFlag = pose->materialLightFlag;
    paper->materialColor = pose->materialColor;
    paper->materialColor2 = pose->materialColor2;
    if (pose->flags & 2)
    {
      PSMTXScale(m1, *((f32 *) (((u8 *) pose) + 0x10C)), *((f32 *) (((u8 *) pose) + 0x110)), 1.0f);
      PSMTXTrans(m2, *((f32 *) (0x104 + ((u8 *) pose))), *((f32 *) (((u8 *) pose) + 0x108)), 0.0f);
      PSMTXConcat(m1, m2, m1);
      animSetPaperMtx(m1, (void *) 0, (void *) 0);
      PSMTXScale(m1, pose->paperScaleXZ, pose->paperScaleY, pose->paperScaleXZ);
      if (wp->inBattle)
      {
        PSMTXTrans(m2, 0.0f, 2.0f * pose->paperOfsY, 0.0f);
      }
      else
      {
        PSMTXTrans(m2, 0.0f, pose->paperOfsY, 0.0f);
      }
      PSMTXConcat(m2, m1, m1);
      PSMTXConcat(matrix, m1, mtx);
      matrix = mtx;
    }
    else
    {
      PSMTXScale(m1, *((f32 *) (((u8 *) pose) + 0x10C)), *((f32 *) (((u8 *) pose) + 0x110)), 1.0f);
      PSMTXTrans(m2, *((f32 *) (((u8 *) pose) + 0x104)), *((f32 *) (((u8 *) pose) + 0x108)), 0.0f);
      PSMTXConcat(m1, m2, m1);
      PSMTXTrans(m2, 0.5f, 1.0f, 0.0f);
      PSMTXConcat(m1, m2, m1);
      PSMTXScale(m2, 1.0f / pose->paperScaleXZ, 1.0f / pose->paperScaleY, 1.0f);
      PSMTXConcat(m1, m2, m1);
      PSMTXTrans(m2, -0.5f, -1.0f, 0.0f);
      PSMTXConcat(m1, m2, m1);
      animSetPaperMtx(m1, (void *) 0, (void *) 0);
    }
  }
  else
  {
    data = *((AnimationPoseData **) wp->files[pose->fileId].handle->data);
    if (((xluMode != 2) || (!(data->flags & 1))) && (!(data->flags & (1 << xluMode))))
    {
      return;
    }
  }
  if (pose->paperId != (-1))
  {
    _animPoseDrawMtx(paper, matrix, xluMode, rotY, scale);
    wp->paperMtxPtr[0] = (void *) 0;
    wp->paperMtxPtr[1] = (void *) 0;
    wp->paperMtxPtr[2] = (void *) 0;
    if (paper->typeFlags & 2)
    {
      wp->mbUseFloatScratch = 0;
    }
  }
  else
  {
    _animPoseDrawMtx(pose, matrix, xluMode, rotY, scale);
  }
}
#endif

u32 anim_ext_tex_size;

#ifdef NONMATCHING
void animSetPaperTexObj(GXTexObj* obj1, GXTexObj* obj2, GXTexObj* obj3, void* data1, void* data2, void* data3, s32 a7, s32 a8) {
    wp->mpTexObjs[0] = data1 ? obj1 : NULL;
    wp->mpTexObjs[1] = data2 ? obj2 : NULL;
    wp->mpCurTexObj = data3 ? obj3 : NULL;
    wp->mpTexDatas[0] = data1;
    wp->mpTexDatas[1] = data2;
    wp->mpCurTexData = data3;
    wp->field_0xD8 = a7;
    wp->field_0xDC = a7;
}
#endif

inline void animPoseFileRelease(s32 fileId) {
    AnimationPoseFile* file = &wp->files[fileId];
    AnimationTextureFile* tex;

    file->references--;
    if (file->references <= 0) {
        file->active = 0;
        tex = &wp->textures[file->textureId];
        tex->references--;
        if (tex->references <= 0) {
            fileFree(tex->handle);
            tex->active = FALSE;
        }
        fileFree(file->handle);
    }
}

#ifdef NONMATCHING
void animPoseRelease(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if ((u32)pose->typeFlags != 0) {
        animPaperPoseRelease(poseId);
    }
    else {
        if (pose->flags & 0x40) {
            smartFree((smartEntry*)pose->worldPositions);
        }
        if (pose->flags & 0x80) {
            smartFree((smartEntry*)pose->worldMatrices);
        }
        animPoseFileRelease(pose->fileId);
        pose->flags = 0;
    }
}
#endif

#ifdef NONMATCHING
void animPaperPoseRelease(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    pose->references--;
    if (pose->references < 0) {
        animPoseFileRelease(pose->fileId);
        pose->flags = 0;
    }
}
#endif

#ifdef NONMATCHING
void animPoseAutoRelease(s32 type) {
    int i;
    AnimationPose* pose;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = animPoseGetAnimPosePtr(i);
        if (pose->flags & 1 && pose->type == type) {
            animPoseRelease(i);
        }
    }
    if (type == 1) {
        wp->inBattle = FALSE;
    }
    animPoseRefresh();
}
#endif

#pragma dont_inline on
#ifdef NONMATCHING
void animPaperPoseDisp(CameraId camId, void* param) {
    int i;
    AnimationPose* pose;

    for (i = 0, pose = wp->poses; i < wp->totalPoses; i++, pose++) {
        if (pose->flags & 1 && pose->paperId != -1) {
            animPaperPoseDispSub(0, pose);
        }
    }
}
#endif
#pragma dont_inline reset

#include "sdk/DEMOInit.h"
void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
typedef struct PaperAnimData {
    u8 pad[0x44];
    f32 x44, x48, x4C, x50, x54;
} PaperAnimData;
#define PP_ENT(p) (*(smartEntry**)((u8*)(p) + 0x98))
#define PP_9C(p) (*(s32*)((u8*)(p) + 0x9C))
#define PP_F(p, o) (*(f32*)((u8*)(p) + (o)))
#define PP_S(p, o) (*(s16*)((u8*)(p) + (o)))

#ifdef NONMATCHING
void animPaperPoseDispSub(s32 unused, AnimationPose* pose) {
    PaperAnimData* d;
    Mtx m, save;
    GXColor col1;
    u16 h;
    GXColor col2;
    s32 lightFlag;
    u32 flags;
    s32 matFlag;
    u16 left, top, right, bottom;
    u16 w;
    f32 scale, hh;
    s32 t, e, b, a, x1, y0, y1;

    scale = 8.0f;
    if (!(pose->flags & 1)) {
        return;
    }
    d = (PaperAnimData*)animPoseGetBaseData(pose)->mpAnims[pose->animId].data;
    scale *= 25.74f / (d->x54 - d->x48);
    hh = 0.75f * DEMOGetRenderModeObj()->efbHeight;
    sysWaitDrawSync();
    GXClearBoundingBox();
    MTXTrans(m, 0.0f, 0.25f * -(f32)DEMOGetRenderModeObj()->efbHeight - d->x48 * scale, 0.0f);
    flags = pose->flags;
    matFlag = pose->materialFlag;
    lightFlag = pose->materialLightFlag;
    col1 = pose->materialColor;
    col2 = pose->materialColor2;
    pose->flags = flags & ~8;
    pose->materialColor = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->materialColor2 = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->materialLightFlag = 0;
    if (pose->vivianType) {
        PSMTXCopy(pose->matrix, save);
        PSMTXCopy(m, pose->matrix);
    }
    _animPoseDrawMtx(pose, m, 2, 0.0f, scale);
    pose->flags = flags;
    pose->materialFlag = matFlag;
    pose->materialColor = col1;
    pose->materialColor2 = col2;
    pose->materialLightFlag = lightFlag;
    if (pose->vivianType) {
        PSMTXCopy(save, pose->matrix);
    }
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    if (left > right) {
        left = 0;
        top = 0;
        right = 16;
        bottom = 16;
    }
    if (pose->flags & 2 && pose->flags & 4 && gp->inBattle) {
        a = d->x44 * scale + (s32)(DEMOGetRenderModeObj()->fbWidth / 2);
        x1 = d->x50 * scale + (s32)(DEMOGetRenderModeObj()->fbWidth / 2);
        y0 = hh - scale * (d->x54 - d->x48);
        y1 = hh;
        if (a <= left && x1 >= right && y0 <= top && y1 >= bottom) {
            left = a;
            right = x1;
            top = y0;
            bottom = y1;
        }
    }
    if (left < 2) {
        left = 2;
    }
    if (top < 2) {
        top = 2;
    }
    if (right > DEMOGetRenderModeObj()->fbWidth - 2) {
        right = DEMOGetRenderModeObj()->fbWidth - 2;
    }
    if (bottom > DEMOGetRenderModeObj()->efbHeight - 2) {
        bottom = DEMOGetRenderModeObj()->efbHeight - 2;
    }
    if (pose->flags & 2) {
        if (pose->flags & 4) {
            a = DEMOGetRenderModeObj()->fbWidth / 2 - left;
            t = right - DEMOGetRenderModeObj()->fbWidth / 2;
            b = a;
            if (a < t) {
                b = t;
            }
            a = 0.5f * b;
            e = 0.14881f * (bottom - top);
            PP_S(pose, 0x114) = DEMOGetRenderModeObj()->fbWidth / 2 - b - a;
            PP_S(pose, 0x116) = DEMOGetRenderModeObj()->fbWidth / 2 + b + a;
            PP_S(pose, 0x118) = top - e;
            PP_S(pose, 0x11A) = bottom + e;
            PP_F(pose, 0xF8) = (8.0f / scale) * ((f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114)) / 150.0f);
            PP_F(pose, 0xFC) = (8.0f / scale) * ((f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118)) / 215.0f);
            PP_F(pose, 0x100) = d->x48 + (hh - bottom) / scale;
            pose->flags &= ~4;
        }
    } else {
        s32 a;
        a = DEMOGetRenderModeObj()->fbWidth / 2 - left;
        t = right - DEMOGetRenderModeObj()->fbWidth / 2;
        b = a;
        if (a < t) {
            b = t;
        }
        a = 0.5f * b;
        e = 0.14881f * (bottom - top);
        PP_S(pose, 0x114) = DEMOGetRenderModeObj()->fbWidth / 2 - b - a;
        PP_S(pose, 0x116) = DEMOGetRenderModeObj()->fbWidth / 2 + b + a;
        PP_S(pose, 0x118) = top - e;
        PP_S(pose, 0x11A) = bottom + e;
        PP_F(pose, 0xF8) = (8.0f / scale) * ((f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114)) / 150.0f);
        PP_F(pose, 0xFC) = (8.0f / scale) * ((f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118)) / 215.0f);
        PP_F(pose, 0x100) = d->x48 + (hh - bottom) / scale;
    }
    left -= 2;
    top -= 2;
    right += 2;
    bottom += 2;
    left -= left & 1;
    top -= top & 1;
    right += right & 1;
    bottom += bottom & 1;
    w = right - left;
    h = bottom - top;
    PP_F(pose, 0x104) = -((f32)left - PP_S(pose, 0x114)) / (f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114));
    PP_F(pose, 0x108) = -((f32)top - PP_S(pose, 0x118)) / (f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118));
    PP_F(pose, 0x10C) = (f32)(PP_S(pose, 0x116) - PP_S(pose, 0x114)) / (f32)w;
    PP_F(pose, 0x110) = (f32)(PP_S(pose, 0x11A) - PP_S(pose, 0x118)) / (f32)h;
    GXSetTexCopySrc(left, top, w, h);
    GXSetTexCopyDst(w, h, GX_TF_RGB5A3, GX_FALSE);
    PP_ENT(pose) = smartAlloc(GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0), 3);
    GXCopyTex(PP_ENT(pose)->address, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj((GXTexObj*)((u8*)pose + 0xA0), PP_ENT(pose)->address, w, h, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    PP_9C(pose) = 0;
}
#endif

void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale);
#include "sdk/DEMOInit.h"
// target .bss/.sbss pad (uninitialised objects are emitted in reverse order, so this sits last)
#pragma force_active on

inline s32 animPoseSearchName(const char* name, s32 type) {
    AnimationPose* pose;
    s32 i;

    for (i = 0; i < wp->totalPoses; i++) {
        pose = &wp->poses[i];
        if (pose->flags & 1 && pose->type == type && !strcmp(animPoseGetBaseData(pose)->fileName, name)) {
            break;
        }
    }
    if (i == wp->totalPoses) {
        i = -1;
    }
    return i;
}

#pragma push
#pragma opt_lifetimes off
#ifdef NONMATCHING
void animPoseDisp_MakeExtTexture(const char* group, const char* anim, f32 frame, f32 scale, GXTexObj* obj,
                                 smartEntry** image, s32* x0, s32* y0, s32* x1, s32* y1) {
    AnimationPose* pose;
    AnimationPose* pera;
    AnimationPose backup;
    Mtx m;
    GXColor col1, col2;
    u32 flags;
    s32 matFlag;
    u16 left, top, right, bottom;
    u16 w, h;
    f32 hw, hh;
    s32 i;

    i = animPoseSearchName(group, gp->inBattle != 0);
    if (i < 0) {
        return;
    }
    pose = &wp->poses[i];
    backup = *pose;
    pose->paperId = -1;
    animPoseSetAnim(i, anim, FALSE);
    pose->localTime = animTimeGetTime(pose->type);
    pose->lastFrameZero = -1;
    pose->lastFrameTime = 0.0f;
    pose->field_0x80 = 0;
    pose->loopTime = 0.0f;
    animPoseSetLocalTime(i, frame);
    animPoseMain(i);

    hw = 0.5f * DEMOGetRenderModeObj()->fbWidth;
    hh = 0.75f * DEMOGetRenderModeObj()->efbHeight;
    sysWaitDrawSync();
    GXClearBoundingBox();
    MTXTrans(m, 0.0f, 0.25f * -(f32)DEMOGetRenderModeObj()->efbHeight, 0.0f);
    flags = pose->flags;
    matFlag = pose->materialFlag;
    col1 = pose->materialColor;
    col2 = pose->materialColor2;
    pose->flags = flags & ~8;
    pose->materialFlag = 0;
    pose->materialColor = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    pose->materialColor2 = (GXColor){ 0xFF, 0xFF, 0xFF, 0xFF };
    _animPoseDrawMtx(pose, m, 1, 0.0f, scale);
    _animPoseDrawMtx(pose, m, 2, 0.0f, scale);
    _animPoseDrawMtx(pose, m, 3, 0.0f, scale);
    pose->materialColor = col1;
    pose->materialColor2 = col2;
    pose->flags = flags;
    pose->materialFlag = matFlag;
    sysWaitDrawSync();
    GXReadBoundingBox(&left, &top, &right, &bottom);
    if (left > right) {
        top = left = 0;
        bottom = right = 16;
    }
    if (left < 2) {
        left = 2;
    }
    if (top < 2) {
        top = 2;
    }
    if (right > DEMOGetRenderModeObj()->fbWidth - 2) {
        right = DEMOGetRenderModeObj()->fbWidth - 2;
    }
    if (top > DEMOGetRenderModeObj()->efbHeight - 2) {
        top = DEMOGetRenderModeObj()->efbHeight - 2;
    }
    left -= left & 1;
    top -= top & 1;
    right += right & 1;
    bottom += bottom & 1;
    w = right - left;
    h = bottom - top;
    GXSetTexCopySrc(left, top, w, h);
    GXSetTexCopyDst(w, h, GX_TF_RGB5A3, GX_FALSE);
    anim_ext_tex_size += GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0);
    *image = smartAlloc(GXGetTexBufferSize(w, h, GX_TF_RGB5A3, GX_FALSE, 0), 1);
    GXCopyTex((*image)->address, GX_TRUE);
    GXPixModeSync();
    GXInitTexObj(obj, (*image)->address, w, h, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    *x0 = left - (s32)hw;
    *y0 = top - (s32)hh;
    *x1 = right - (s32)hw;
    *y1 = bottom - (s32)hh;
    *pose = backup;
}
#endif
#pragma pop


#ifdef NONMATCHING
void animSetPaperTexMtx(Mtx mtx1, Mtx mtx2, Mtx mtx3) {
    if (mtx1 == NULL) {
        wp->paperMtxPtr[0] = NULL;
    }
    else {
        PSMTXCopy(mtx1, wp->paperMtx[0]);
        wp->paperMtxPtr[0] = &wp->paperMtx[0];
    }
    if (mtx2 == NULL) {
        wp->paperMtxPtr[1] = NULL;
    }
    else {
        PSMTXCopy(mtx2, wp->paperMtx[1]);
        wp->paperMtxPtr[1] = &wp->paperMtx[1];
    }
    if (mtx3 == NULL) {
        wp->paperMtxPtr[2] = NULL;
    }
    else {
        PSMTXCopy(mtx3, wp->paperMtx[2]);
        wp->paperMtxPtr[2] = &wp->paperMtx[2];
    }
}
#endif

#ifdef NONMATCHING
BOOL animGroupBaseAsync(const char* name, s32 group, void* callback) {
    s32 model, anim;

    switch (group) {
        case 0:
            fileSetCurrentArchiveType(1);
            break;
        case 1:
            fileSetCurrentArchiveType(2);
            break;
        case 2:
            fileSetCurrentArchiveType(0);
            break;
    }
    model = fileAsyncf(5, callback, "%s/%s", "a", name);
    anim = fileAsyncf(4, NULL, "%s/%s-", "a", animGetTexName(name));
    if (model == -1) {
        return TRUE;
    }
    if ((u32)model == 0) {
        return FALSE;
    }
    if (anim == -1) {
        return TRUE;
    }
    return anim != 0;
}
#endif

#ifdef NONMATCHING  // G5: not a target function; emits literals of its own
const char* animGetTexName(const char* name) {
    void** data = wp->mp_ag2tg->data;
    s32 size;
    s32 i;
    char* entry;

    size = (s32)data[1];
    entry = data[0];

    for (i = 0; i < size; entry += 0x20, i += 0x20) {
        if (!strcmp(entry, name)) {
            return entry + 0x20;
        }
    }
    return "";
}
#endif

#ifdef NONMATCHING  // G5: not a target function; emits literals of its own
void animStrippedPool(f32* p, u32 n) {
    p[0] = 0.0f;
    p[1] = 0.017453292f * p[1];
    p[2] = n;
}
#endif

#ifdef NONMATCHING
AnimationPose* animPoseGetAnimPosePtr(s32 poseId) {
    return &wp->poses[poseId];
}
#endif

#ifdef NONMATCHING
AnimData* animPoseGetAnimDataPtr(s32 poseId) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    return animPoseGetAnimBaseDataPtr(poseId)->mpAnims[pose->animId].data;
}
#endif

#ifdef NONMATCHING
AnimationPoseData* animPoseGetAnimBaseDataPtr(s32 poseId) {
    AnimationPose* pose = animPoseGetAnimPosePtr(poseId);
    return *wp->files[pose->fileId].handle->data;
}
#endif

#ifdef NONMATCHING
AnimTableEntry* animPoseGetCurrentAnim(s32 poseId) {
    AnimationPoseData* data = animPoseGetAnimBaseDataPtr(poseId);
    return &data->mpAnims[animPoseGetAnimPosePtr(poseId)->animId];
}
#endif

#ifdef NONMATCHING
BOOL animPoseTestXLU(s32 poseId) {
    return (animPoseGetAnimBaseDataPtr(poseId)->flags >> 3) & 1;
}
#endif

#ifdef NONMATCHING
void evalProc(s32 parentId, s32 groupId) {
    AnimPoseGroup* group;
    AnimPoseGroup* parent;
    AnimPoseNode* node;
    AnimationPose* pose;
    AnimationPoseData* data;
    f32 sx, sy, sz;

    if (groupId == -1) {
        return;
    }
    pose = wp->mpCurPose;
    data = wp->mpCurPoseData;
    group = &data->groups[groupId];
    if (*(s8*)&pose->mpGroupVisibility[group->visibilityId]) {
        pose = wp->mpCurPose;
        node = (AnimPoseNode*)((u32*)pose->mpNodes + group->nodeId);
        if (group->useSSC) {
            if (parentId == -1) {
                sx = sy = sz = 1.0f;
            }
            else {
                parent = &data->groups[parentId];
                if (!parent->useSSC) {
                    sx = sy = sz = 1.0f;
                }
                else {
                    AnimPoseNode* pnode = (AnimPoseNode*)((u32*)pose->mpNodes + parent->nodeId);
                    sx = pnode->mScale.x;
                    sy = pnode->mScale.y;
                    sz = pnode->mScale.z;
                }
            }
            pushGXModelMtx_JointNode__(node, sx, sy, sz);
        }
        else {
            pushGXModelMtx_TransformNode__(node);
        }
        if (wp->mpCurPose->flags & 0x40) {
            Vec pos = {0.0f, 0.0f, 0.0f};
            pos.x = (*g_modeling_mtx)[0][3];
            pos.y = (*g_modeling_mtx)[1][3];
            pos.z = (*g_modeling_mtx)[2][3];
            (*wp->mpCurPose->worldPositions)[groupId] = pos;
        }
        if (wp->mpCurPose->flags & 0x80) {
            PSMTXCopy(*g_modeling_mtx, (*wp->mpCurPose->worldMatrices)[groupId]);
        }
        if (!(wp->mpCurPose->flags & 0x20) || groupId != wp->mpCurPose->vivianGroupNo[0]) {
            evalProc(groupId, group->childGroupId);
        }
        g_modeling_mtx_lv--;
        g_modeling_mtx = &g_modeling_mtx_stack[g_modeling_mtx_lv];
    }
    evalProc(groupId, group->brotherGroupId);
}
#endif

#ifdef NONMATCHING
void animPoseWorldPositionEvalOn(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    AnimationPoseData* data = animPoseGetBaseData(pose);
    u8 heap;

    if (!(pose->flags & 0x40)) {
        pose->flags |= 0x40;
        switch (pose->type) {
            case 0:
                heap = 1;
                break;
            case 1:
                heap = 2;
                break;
            case 2:
                heap = 0;
                break;
        }
        pose->numWorldPositions = data->groupCount;
        pose->worldPositions = (Vec**)smartAlloc(sizeof(Vec) * data->groupCount, heap);
    }
}
#endif

#ifdef NONMATCHING
void L_animPoseWorldPositionEvalOff(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];

    if (pose->flags & 0x40) {
        pose->flags &= ~0x40;
        smartFree((smartEntry*)pose->worldPositions);
        pose->worldPositions = NULL;
    }
}
#endif

#ifdef NONMATCHING
void animPoseWorldMatrixEvalOn(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    AnimationPoseData* data = animPoseGetBaseData(pose);
    u8 heap;

    if (!(pose->flags & 0x80)) {
        pose->flags |= 0x80;
        switch (pose->type) {
            case 0:
                heap = 1;
                break;
            case 1:
                heap = 2;
                break;
            case 2:
                heap = 0;
                break;
        }
        pose->numWorldMatrices = data->groupCount;
        pose->worldMatrices = (Mtx**)smartAlloc(sizeof(Mtx) * data->groupCount, heap);
    }
}
#endif

#ifdef NONMATCHING
void animPoseVivianMain(s32 poseId, Vec* pos) {
    AnimationPose* pose = &wp->poses[poseId];

    pose->flags |= 0x20;
    pose->matrix[0][3] = pos->x;
    pose->matrix[1][3] = pos->y;
    pose->matrix[2][3] = pos->z;
}
#endif

#ifdef NONMATCHING
s32 animPoseGetVivianType(s32 poseId) {
    AnimationPose* pose = &wp->poses[poseId];
    return pose->vivianType;
}
#endif

#ifdef NONMATCHING
void animPoseSetDispCallBack(s32 poseId, void* callback, void* userData) {
    AnimationPose* pose = &wp->poses[poseId];
    pose->dispCallback = callback;
    pose->dispUserDataCallback = userData;
}
#endif

inline void animPoseMainSub(AnimationPose* pose) {
    s32 id = ((u32)pose - (u32)wp->poses) / sizeof(AnimationPose);
    if (pose->typeFlags & 2) {
        AnimationPoseData* data = animPoseGetBaseData(pose);
        s32 posNum = data->mBufferPosNum;
        s32 nrmNum = data->mBufferNrmNum;
        if (posNum + nrmNum <= wp->mFloatScratchRP) {
            if (wp->mFloatScratchWP + (posNum + nrmNum) > wp->mFloatScratchRP) {
                wp->mFloatScratchWP = 0;
            }
            wp->mbUseFloatScratch = 1;
            wp->vtxArrayPos = &wp->mpFloatScratch[wp->mFloatScratchWP];
            wp->mFloatScratchWP += posNum;
            wp->vtxArrayNrm = &wp->mpFloatScratch[wp->mFloatScratchWP];
            wp->mFloatScratchWP += nrmNum;
        }
        animPoseMain(id);
        wp->mbUseFloatScratch = 0;
    }
    else {
        animPoseMain(id);
    }
}

#ifdef NONMATCHING
void animPoseDrawShape(s32 poseId, s32 shapeId) {
    AnimationPose* pose;
    GXTexObj* texObj0;
    GXTexObj* texObj1;
    GXTexObj* curTexObj;
    void* texData0;
    void* texData1;
    void* curTexData;
    Mtx* paperMtx0;
    Mtx* paperMtx1;
    Mtx* paperMtx2;
    AnimationPose* curPose;
    AnimData* curAnimData;
    AnimationPoseData* curPoseData;
    u32 d8;
    u32 dc;
    s32 id;

    pose = &wp->poses[poseId];
    curPose = wp->mpCurPose;
    curAnimData = wp->mpCurAnimData;
    curPoseData = wp->mpCurPoseData;
    texObj0 = wp->mpTexObjs[0];
    texObj1 = wp->mpTexObjs[1];
    curTexObj = wp->mpCurTexObj;
    texData0 = wp->mpTexDatas[0];
    texData1 = wp->mpTexDatas[1];
    curTexData = wp->mpCurTexData;
    paperMtx0 = wp->paperMtxPtr[0];
    paperMtx1 = wp->paperMtxPtr[1];
    paperMtx2 = wp->paperMtxPtr[2];
    d8 = wp->field_0xD8;
    dc = wp->field_0xDC;

    wp->mpCurPose = pose;
    wp->mpCurAnimData = animPoseGetBaseData(pose)->mpAnims[pose->animId].data;
    wp->mpCurPoseData = animPoseGetBaseData(pose);
    wp->mpTexObjs[0] = NULL;
    wp->mpTexObjs[1] = NULL;
    wp->mpCurTexObj = NULL;
    wp->mpTexDatas[0] = NULL;
    wp->mpTexDatas[1] = NULL;
    wp->mpCurTexData = NULL;
    wp->paperMtxPtr[0] = NULL;
    wp->paperMtxPtr[1] = NULL;
    wp->paperMtxPtr[2] = NULL;
    wp->field_0xD8 = 0;
    wp->field_0xDC = 0;

    if (pose->lastFrameZero == -1) {
        animPoseMainSub(pose);
    }
    renderProc(shapeId, pose->field_0x28);

    wp->mpCurPose = curPose;
    wp->mpCurAnimData = curAnimData;
    wp->mpCurPoseData = curPoseData;
    wp->mpTexObjs[0] = texObj0;
    wp->mpTexObjs[1] = texObj1;
    wp->mpCurTexObj = curTexObj;
    wp->mpTexDatas[0] = texData0;
    wp->mpTexDatas[1] = texData1;
    wp->mpCurTexData = curTexData;
    wp->paperMtxPtr[0] = paperMtx0;
    wp->paperMtxPtr[1] = paperMtx1;
    wp->paperMtxPtr[2] = paperMtx2;
    wp->field_0xD8 = d8;
    wp->field_0xDC = dc;
}
#endif

#ifdef NONMATCHING
s32 animPoseGetShapeIdx(s32 poseId, const char* name) {
    AnimationPoseData* data;
    AnimPoseShape* shape;
    s32 i;

    data = animPoseGetAnimBaseDataPtr(poseId);
    shape = data->shapes;
    for (i = 0; i < data->shapeCount; i++, shape++) {
        if (!strcmp(shape->name, name)) {
            return i;
        }
    }
    return -1;
}
#endif

#ifdef NONMATCHING
s32 animPoseGetGroupIdx(s32 poseId, const char* name) {
    AnimationPoseData* data;
    AnimPoseGroup* group;
    s32 i;

    data = animPoseGetAnimBaseDataPtr(poseId);
    group = data->groups;
    for (i = 0; i < data->groupCount; i++, group++) {
        if (!strcmp(group->name, name)) {
            return i;
        }
    }
    return -1;
}
#endif

#ifdef NONMATCHING
const char* animPoseGetGroupName(s32 poseId, s32 group) {
    return animPoseGetAnimBaseDataPtr(poseId)->groups[group].name;
}
#endif

#ifndef NONMATCHING
// FAKE (asm stopgap): animGetPtr (and the functions before it in the target order, see asm_inline.py) are the
// target code until the C in the NONMATCHING branch matches.
// clang-format off
#pragma force_active on
__declspec(section ".rodata") const char str_802C2A98[] = "joint_00\000\000\000";
__declspec(section ".rodata") const char str_802C2AA4[] = "jointdai1_A01\000\000";
__declspec(section ".rodata") const char str_802C2AB4[] = "jointdai1_A02\000\000";
__declspec(section ".rodata") const char str_802C2AC4[] = "jointdai1_A03\000\000";
__declspec(section ".rodata") const char str_802C2AD4[] = "jointdai1_A04\000\000";
__declspec(section ".rodata") const char str_802C2AE4[] = "jointdai1_A05\000\000";
__declspec(section ".rodata") const char str_802C2AF4[] = "jointdai1_B01\000\000";
__declspec(section ".rodata") const char str_802C2B04[] = "jointdai1_B02\000\000";
__declspec(section ".rodata") const char str_802C2B14[] = "jointdai1_B03\000\000";
__declspec(section ".rodata") const char str_802C2B24[] = "jointdai1_B04\000\000";
__declspec(section ".rodata") const char str_802C2B34[] = "jointdai1_B05\000\000";
__declspec(section ".rodata") const char str_802C2B44[] = "jointdai1_C01\000\000";
__declspec(section ".rodata") const char str_802C2B54[] = "jointdai1_C02\000\000";
__declspec(section ".rodata") const char str_802C2B64[] = "jointdai1_C03\000\000";
__declspec(section ".rodata") const char str_802C2B74[] = "jointdai1_C04\000\000";
__declspec(section ".rodata") const char str_802C2B84[] = "jointdai1_C05\000\000";
__declspec(section ".rodata") const char str_802C2B94[] = "jointdai2_01\000\000\000";
__declspec(section ".rodata") const char str_802C2BA4[] = "jointdai2_02\000\000\000";
__declspec(section ".rodata") const char str_802C2BB4[] = "jointdai2_03\000\000\000";
__declspec(section ".rodata") const char str_802C2BC4[] = "jointdai2_04\000\000\000";
__declspec(section ".rodata") const char str_802C2BD4[] = "jointdai2_05\000\000\000";
__declspec(section ".rodata") const char str_802C2BE4[] = "jointdai2_06\000\000\000";
__declspec(section ".rodata") const char str_802C2BF4[] = "jointdai2_07\000\000\000";
__declspec(section ".rodata") const char str_802C2C04[] = "jointdai2_upper01\000\000";
__declspec(section ".rodata") const char str_802C2C18[] = "jointdai2_upper02\000\000";
__declspec(section ".rodata") const char str_802C2C2C[] = "jointdai2_upper03\000\000";
__declspec(section ".rodata") const char str_802C2C40[] = "jointdai2_upper04\000\000";
__declspec(section ".rodata") const char str_802C2C54[] = "jointdai2_lower01\000\000";
__declspec(section ".rodata") const char str_802C2C68[] = "jointdai2_lower02\000\000";
__declspec(section ".rodata") const char str_802C2C7C[] = "jointdai2_lower03\000\000";
__declspec(section ".rodata") const char str_802C2C90[] = "jointdai2_lower04\000\000";
__declspec(section ".rodata") const char str_802C2CA4[] = "jointasi_A01\000\000\000";
__declspec(section ".rodata") const char str_802C2CB4[] = "jointasi_A02\000\000\000";
__declspec(section ".rodata") const char str_802C2CC4[] = "jointasi_A03\000\000\000";
__declspec(section ".rodata") const char str_802C2CD4[] = "jointasi_A04\000\000\000";
__declspec(section ".rodata") const char str_802C2CE4[] = "jointasi_B01\000\000\000";
__declspec(section ".rodata") const char str_802C2CF4[] = "jointasi_B02\000\000\000";
__declspec(section ".rodata") const char str_802C2D04[] = "jointasi_B03\000\000\000";
__declspec(section ".rodata") const char str_802C2D14[] = "jointasi_B04\000\000\000";
__declspec(section ".rodata") const char str_802C2D24[] = "jointasi_C01\000\000\000";
__declspec(section ".rodata") const char str_802C2D34[] = "jointasi_C02\000\000\000";
__declspec(section ".rodata") const char str_802C2D44[] = "jointasi_C03\000\000\000";
__declspec(section ".rodata") const char str_802C2D54[] = "jointasi_C04\000\000\000";
__declspec(section ".rodata") const char str_802C2D64[] = "jointasi_D01\000\000\000";
__declspec(section ".rodata") const char str_802C2D74[] = "jointasi_D02\000\000\000";
__declspec(section ".rodata") const char str_802C2D84[] = "jointasi_D03\000\000\000";
__declspec(section ".rodata") const char str_802C2D94[] = "jointasi_D04\000\000\000";
__declspec(section ".rodata") const char str_802C2DA4[] = "joint_core\000";
__declspec(section ".rodata") const f32 vec3_802c2db0[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c2dbc[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c2dc8[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f32 vec3_802c2dd4[3] = { 0.0f, 0.0f, 0.0f };
__declspec(section ".rodata") const f64 double_to_int_mask_802c2de0 = 4503599627370496;
__declspec(section ".rodata") const char str_802C2DE8[] = "%s/%s-\000";
__declspec(section ".rodata") const f64 double_to_int_802c2df0 = 4503601774854144;
__declspec(section ".rodata") const char str_802C2DF8[] = "Error: animSetMaterial_ChangeTexture: \203e\203N\203X\203`\203\203\202\252\202\240\202\350\202\334\202\271\202\361 frameExt=%d\n\000\000";
__declspec(section ".rodata") const char str_802C2E44[] = "Error: dispSetTevMode: \203x\201[\203X\203\202\203f\203\213%s \203A\203j\203\201 %s \223\340\202\305 \203t\203\214\201[\203\200\203G\203N\203X\203e\203\223\203V\203\207\203\223\202\314\220\335\222\350\202\252\215s\202\355\202\352\202\304\202\242\202\334\202\267\202\252\201A\212Y\223\226\202\267\202\351\203e\203N\203X\203`\203\203\202\252\202\240\202\350\202\334\202\271\202\361 \nframeExt\224\324\215\206 %d? \202\252\226\263\202\242\202\346\202\244\202\305\202\267\201B\203\202\203f\203\213\202\334\202\275\202\315\203A\203j\203\201\202\311\217C\220\263\202\252\225K\227v\202\305\202\267\201BtextureIdx=%d\n\000";
__declspec(section ".rodata") const f64 double_10_802c2f20 = 10;
__declspec(section ".rodata") const char str_802C2F28[] = "tst_vivi\000\000\000";
__declspec(section ".rodata") const char str_802C2F34[] = "c_vivian\000\000\000";
__declspec(section ".rodata") const char str_802C2F40[] = "c_maririn\000\000";
__declspec(section ".rodata") const char str_802C2F4C[] = "c_majyorin\000";
__declspec(section ".rodata") const char str_802C2F58[] = "a/vivian.bin\000\000\000";
__declspec(section ".rodata") const char str_802C2F68[] = "a/ag2tg.bin";
__declspec(section ".rodata") const u32 gap_04_802C2F74_rodata[1] = { 0x00000000 };
__declspec(section ".sdata2") const u32 dat_80419a2c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a30 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a34 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a38 = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a3c = 0xFFFFFFFF;
__declspec(section ".sdata2") const u32 dat_80419a40 = 0xFFFFFFFF;
__declspec(section ".sdata2") const f32 float_1_80419a44 = 1.0f;
__declspec(section ".sdata2") const f32 float_0_80419a48 = 0.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419a4c = 0.017453292f;
__declspec(section ".sdata2") const u32 zero_80419a50 = 0x00000000;
__declspec(section ".sdata2") const char str_80419A54[8] = "%s/%s\0\0";
__declspec(section ".sdata2") const char str_80419A5C[4] = "a\0\0";
__declspec(section ".sdata2") const f32 float_16p667_80419a60 = 16.666666f;
__declspec(section ".sdata2") const f32 float_0p5_80419a64 = 0.5f;
__declspec(section ".sdata2") const f32 float_0p75_80419a68 = 0.75f;
__declspec(section ".sdata2") const f32 float_0p25_80419a6c = 0.25f;
__declspec(section ".sdata2") const f32 float_8_80419a70 = 8.0f;
__declspec(section ".sdata2") const f32 float_25p74_80419a74 = 25.74f;
__declspec(section ".sdata2") const f32 float_0p14881_80419a78 = 0.14881f;
__declspec(section ".sdata2") const f32 float_150_80419a7c = 150.0f;
__declspec(section ".sdata2") const f32 float_215_80419a80 = 215.0f;
__declspec(section ".sdata2") const f32 float_2_80419a84 = 2.0f;
__declspec(section ".sdata2") const f32 float_neg0p5_80419a88 = -0.5f;
__declspec(section ".sdata2") const f32 float_neg1_80419a8c = -1.0f;
__declspec(section ".sdata2") const f32 float_neg90_80419a90 = -90.0f;
__declspec(section ".sdata2") const f32 float_rad2deg_80419a94 = 57.29579f;
__declspec(section ".sdata2") const f32 float_360_80419a98 = 360.0f;
__declspec(section ".sdata2") const f32 float_neg360_80419a9c = -360.0f;
__declspec(section ".sdata2") const f32 float_90_80419aa0 = 90.0f;
__declspec(section ".sdata2") const f32 float_270_80419aa4 = 270.0f;
__declspec(section ".sdata2") const f32 float_neg270_80419aa8 = -270.0f;
__declspec(section ".sdata2") const f32 float_180_80419aac = 180.0f;
__declspec(section ".sdata2") const f32 float_neg180_80419ab0 = -180.0f;
__declspec(section ".sdata2") const f32 float_0p1_80419ab4 = 0.1f;
__declspec(section ".sdata2") const f32 float_neg2_80419ab8 = -2.0f;
__declspec(section ".sdata2") const f32 float_neg3_80419abc = -3.0f;
__declspec(section ".sdata2") const f32 float_0p04_80419ac0 = 0.04f;
__declspec(section ".sdata2") const f32 float_60_80419ac4 = 60.0f;
__declspec(section ".sdata2") const f32 float_1000_80419ac8 = 1000.0f;
__declspec(section ".sdata2") const f32 float_0p0625_80419acc = 0.0625f;
__declspec(section ".sdata2") const f32 float_3_80419ad0 = 3.0f;
__declspec(section ".sdata2") const f32 float_deg2rad_80419ad4 = 0.017453289f;

void DCFlushRange(void* addr, u32 nBytes);
GXRenderModeObj* DEMOGetRenderModeObj(void);
void GXBegin(GXPrimitive type, GXVtxFmt vtxfmt, u16 nverts);
void GXClearBoundingBox(void);
void GXClearVtxDesc(void);
void GXCopyTex(void* dest, GXBool clear);
u32 GXGetTexBufferSize(u16 width, u16 height, u32 format, u8 mipmap, u8 max_lod);
void GXInitTexObj(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXTexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap);
void GXInitTexObjCI(GXTexObj* obj, void* image_ptr, u16 width, u16 height, GXCITexFmt format, GXTexWrapMode wrap_s, GXTexWrapMode wrap_t, u8 mipmap, u32 tlut_name);
void GXInitTexObjLOD(GXTexObj* obj, GXTexFilter min_filt, GXTexFilter mag_filt,
    f32 min_lod, f32 max_lod, f32 lod_bias, GXBool bias_clamp,
    GXBool do_edge_lod, GXAnisotropy max_aniso);
void GXInitTlutObj(GXTlutObj* tlut_obj, void* lut, GXTlutFmt fmt, u16 n_entries);
void GXInvalidateVtxCache(void);
void GXLoadNrmMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadPosMtxImm(const f32 mtx[3][4], u32 id);
void GXLoadTexMtxImm(const f32 mtx[][4], u32 id, GXTexMtxType type);
void GXLoadTexObj(GXTexObj* obj, GXTexMapID id);
void GXLoadTlut(GXTlutObj* tlut_obj, u32 tlut_name);
void GXPixModeSync(void);
void GXReadBoundingBox(u16* left, u16* top, u16* right, u16* bottom);
void GXSetAlphaCompare(GXCompare comp0, u8 ref0, GXAlphaOp op, GXCompare comp1, u8 ref1);
void GXSetArray(GXAttr attr, void* base_ptr, u8 stride);
void GXSetBlendMode(GXBlendMode type, GXBlendFactor src_factor, GXBlendFactor dst_factor, GXLogicOp op);
void GXSetCullMode(GXCullMode mode);
void GXSetCurrentMtx(u32 id);
void GXSetTevAlphaIn(GXTevStageID stage, GXTevAlphaArg a, GXTevAlphaArg b, GXTevAlphaArg c, GXTevAlphaArg d);
void GXSetTexCoordGen2(GXTexCoordID dst_coord, GXTexGenType func, GXTexGenSrc src_param, u32 mtx, GXBool normalize, u32 pt_texmtx);
void GXSetTexCopyDst(u16 wd, u16 ht, GXTexFmt fmt, GXBool mipmap);
void GXSetTexCopySrc(u16 left, u16 top, u16 wd, u16 ht);
void GXSetVtxAttrFmt(GXVtxFmt vtxfmt, GXAttr attr, GXCompCnt cnt, GXCompType type, u8 frac);
void GXSetVtxDesc(GXAttr attr, GXAttrType type);
void GXSetZCompLoc(GXBool before_tex);
void GXSetZMode(GXBool compare_enable, GXCompare func, GXBool update_enable);
void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
void PSMTXCopy(const Mtx src, Mtx dst);
void PSMTXIdentity(Mtx m);
u32 PSMTXInvXpose(const Mtx src, Mtx invX);
void PSMTXMultVec(const Mtx m, const Vec* src, Vec* dst);
void PSMTXRotRad(Mtx m, char axis, f32 rad);
void PSMTXScale(Mtx m, f32 xS, f32 yS, f32 zS);
void PSMTXTrans(Mtx m, f32 xT, f32 yT, f32 zT);
TEXDescriptor* TEXGet(TEXPalette* pal, u32 id);
void __cvt_dbl_usll();
void __cvt_ull_flt();
void __div2i();
void* __memAlloc(HEAP_TYPE heap, u32 size);
s32 animPoseEntry(const char *animName, s32 type);
void animPoseMain(s32 poseId);
void animPose_AllocBuffer(AnimationPose* pose);
void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile);
CameraEntry* camGetCurPtr(void);
CameraEntry* camGetPtr(CameraId cameraId);
void dispEntry(CameraId camera, f32 order, s32 renderMode, DispCallback callback, void* param);
void dispProc(s32 parentId, s32 groupId, s32 xluStage, s32 arg3, f32 arg4);
FileEntry* fileAlloc(const char* filename, s32 type);
FileEntry* fileAllocf(s32 type, const char* format, ...);
s32 fileAsyncf(s32 type, FileCallback callback, const char* format, ...);
void fileFree(FileEntry* handle);
void fileSetCurrentArchiveType(s32 type);
void initTestHeap(void);
void mapSetMaterialFog(void);
void mapSetMaterialLastStageBlend(s32 flags, GXColor color1, GXColor color2);
void mapSetMaterialLight(s32 flags, Vec position);
void mapSetMaterialTev(s32 texCount, s32 drawMode, s32 flags, Mtx mtx);
void *memcpy(void *dest, const void *src, size_t num);
void* memcpy_as4(void* dest, const void* src, u32 count);
int printf(const char *, ...);
smartEntry* smartAlloc(u32 size, u8 type);
void smartFree(smartEntry* entry);
GXTexObj* smartTexObj(GXTexObj* obj, void** image_ptr);
int strcmp(const char *s1, const char *s2);
void sysWaitDrawSync(void);
void* testAlloc(u32 size);
__declspec(section ".sdata") static u32 g5__dummy_s614[1] = { 0xFFFFFFFF };
__declspec(section ".sdata") static u32 g5_tbl_s1109[4] = { 0x00000002, 0x00000001, 0x00000003, 0x00000000 };
asm const char* animPoseGetGroupName(s32 poseId, s32 group) {
	nofralloc
	lwz r5, wp(r13)
	mulli r3, r3, 0x170
	lwz r6, 0x10(r5)
	lwz r5, 0x0(r5)
	mulli r0, r4, 0x58
	add r3, r6, r3
	lwz r3, 0x10(r3)
	slwi r3, r3, 4
	add r3, r5, r3
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0x1a8(r3)
	add r3, r3, r0
	blr
}

asm s32 animPoseGetGroupIdx(s32 poseId, const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	mulli r0, r3, 0x170
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	li r29, 0x0
	stw r28, 0x10(r1)
	mr r28, r4
	lwz r5, wp(r13)
	lwz r4, 0x10(r5)
	lwz r3, 0x0(r5)
	add r4, r4, r0
	lwz r0, 0x10(r4)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r31, 0x0(r3)
	lwz r30, 0x1a8(r31)
	b L_g5_1
	L_g5_2:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_3
	mr r3, r29
	b L_g5_4
	L_g5_3:
	addi r29, r29, 0x1
	addi r30, r30, 0x58
	L_g5_1:
	lwz r0, 0x144(r31)
	cmpw r29, r0
	blt L_g5_2
	li r3, -0x1
	L_g5_4:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 animPoseGetShapeIdx(s32 poseId, const char* name) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	mulli r0, r3, 0x170
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	li r29, 0x0
	stw r28, 0x10(r1)
	mr r28, r4
	lwz r5, wp(r13)
	lwz r4, 0x10(r5)
	lwz r3, 0x0(r5)
	add r4, r4, r0
	lwz r0, 0x10(r4)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r31, 0x0(r3)
	lwz r30, 0x14c(r31)
	b L_g5_1
	L_g5_2:
	mr r3, r30
	mr r4, r28
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_3
	mr r3, r29
	b L_g5_4
	L_g5_3:
	addi r29, r29, 0x1
	addi r30, r30, 0xa8
	L_g5_1:
	lwz r0, 0xe8(r31)
	cmpw r29, r0
	blt L_g5_2
	li r3, -0x1
	L_g5_4:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile);
__declspec(section ".data") static void* jumptable_803050B8[] = {
    (char*)animSetMaterial_Texture + 0x47C,
    (char*)animSetMaterial_Texture + 0x49C,
    (char*)animSetMaterial_Texture + 0x4A4,
    (char*)animSetMaterial_Texture + 0x4AC,
    (char*)animSetMaterial_Texture + 0x4C4,
    (char*)animSetMaterial_Texture + 0x4CC,
    (char*)animSetMaterial_Texture + 0x4E4,
    (char*)animSetMaterial_Texture + 0x4FC,
};
void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz);
__declspec(section ".data") static void* jumptable_803050D8[] = {
    (char*)pushGXModelMtx_JointNode__ + 0x310,
    (char*)pushGXModelMtx_JointNode__ + 0x320,
    (char*)pushGXModelMtx_JointNode__ + 0x328,
    (char*)pushGXModelMtx_JointNode__ + 0x330,
    (char*)pushGXModelMtx_JointNode__ + 0x348,
    (char*)pushGXModelMtx_JointNode__ + 0x350,
    (char*)pushGXModelMtx_JointNode__ + 0x368,
    (char*)pushGXModelMtx_JointNode__ + 0x380,
    (char*)pushGXModelMtx_JointNode__ + 0x3A8,
    (char*)pushGXModelMtx_JointNode__ + 0x3B0,
    (char*)pushGXModelMtx_JointNode__ + 0x3C8,
    (char*)pushGXModelMtx_JointNode__ + 0x3E0,
    (char*)pushGXModelMtx_JointNode__ + 0x408,
    (char*)pushGXModelMtx_JointNode__ + 0x420,
    (char*)pushGXModelMtx_JointNode__ + 0x448,
    (char*)pushGXModelMtx_JointNode__ + 0x470,
};
void pushGXModelMtx_TransformNode__(AnimPoseNode* node);
__declspec(section ".data") static void* jumptable_80305118[] = {
    (char*)pushGXModelMtx_TransformNode__ + 0x3DC,
    (char*)pushGXModelMtx_TransformNode__ + 0x3EC,
    (char*)pushGXModelMtx_TransformNode__ + 0x3F4,
    (char*)pushGXModelMtx_TransformNode__ + 0x3FC,
    (char*)pushGXModelMtx_TransformNode__ + 0x414,
    (char*)pushGXModelMtx_TransformNode__ + 0x41C,
    (char*)pushGXModelMtx_TransformNode__ + 0x434,
    (char*)pushGXModelMtx_TransformNode__ + 0x44C,
};
asm void animPoseDrawShape(s32 poseId, s32 shapeId) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	mulli r3, r3, 0x170
	stw r0, 0x54(r1)
	li r0, 0x0
	stmw r16, 0x10(r1)
	mr r16, r4
	lwz r6, wp(r13)
	lwz r5, 0x10(r6)
	lwz r21, 0x18(r6)
	lwz r20, 0x1c(r6)
	add r31, r5, r3
	lwz r19, 0x20(r6)
	lwz r30, 0x30(r6)
	lwz r29, 0x34(r6)
	lwz r28, 0x38(r6)
	lwz r27, 0x24(r6)
	lwz r26, 0x28(r6)
	lwz r25, 0x2c(r6)
	lwz r24, 0xcc(r6)
	lwz r23, 0xd0(r6)
	lwz r22, 0xd4(r6)
	lwz r18, 0xd8(r6)
	lwz r17, 0xdc(r6)
	stw r31, 0x18(r6)
	lwz r3, wp(r13)
	lwz r5, 0x10(r31)
	lwz r4, 0x14(r31)
	lwz r6, 0x0(r3)
	slwi r5, r5, 4
	slwi r4, r4, 6
	add r5, r6, r5
	lwz r5, 0x8(r5)
	lwz r5, 0xa0(r5)
	lwz r5, 0x0(r5)
	lwz r5, 0x1ac(r5)
	add r4, r5, r4
	lwz r4, 0x3c(r4)
	stw r4, 0x1c(r3)
	lwz r5, wp(r13)
	lwz r3, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r3, r3, 4
	add r3, r4, r3
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	stw r3, 0x20(r5)
	lwz r3, wp(r13)
	stw r0, 0x30(r3)
	lwz r3, wp(r13)
	stw r0, 0x34(r3)
	lwz r3, wp(r13)
	stw r0, 0x38(r3)
	lwz r3, wp(r13)
	stw r0, 0x24(r3)
	lwz r3, wp(r13)
	stw r0, 0x28(r3)
	lwz r3, wp(r13)
	stw r0, 0x2c(r3)
	lwz r3, wp(r13)
	stw r0, 0xcc(r3)
	lwz r3, wp(r13)
	stw r0, 0xd0(r3)
	lwz r3, wp(r13)
	stw r0, 0xd4(r3)
	lwz r3, wp(r13)
	stw r0, 0xd8(r3)
	lwz r3, wp(r13)
	stw r0, 0xdc(r3)
	lwz r3, 0x3c(r31)
	cmpwi r3, -0x1
	bne L_g5_1
	lwz r6, wp(r13)
	lis r4, 0xb216
	addi r5, r4, 0x42c9
	lwz r3, 0x4(r31)
	lwz r4, 0x10(r6)
	rlwinm. r3, r3, 0, 30, 30
	subf r4, r4, r31
	mulhwu r4, r5, r4
	srwi r3, r4, 8
	beq L_g5_2
	lwz r4, 0x10(r31)
	lwz r5, 0x0(r6)
	slwi r4, r4, 4
	lwz r7, 0xf0(r6)
	add r4, r5, r4
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r5, 0xf0(r4)
	lwz r4, 0xf8(r4)
	add r9, r5, r4
	cmpw r9, r7
	bgt L_g5_3
	lwz r8, 0xf4(r6)
	add r8, r8, r9
	cmpw r8, r7
	ble L_g5_4
	stw r0, 0xf4(r6)
	L_g5_4:
	lwz r6, wp(r13)
	li r0, 0x1
	stw r0, 0xe8(r6)
	lwz r7, wp(r13)
	lwz r0, 0xf4(r7)
	lwz r6, 0xec(r7)
	mulli r0, r0, 0xc
	add r0, r6, r0
	stw r0, 0xf8(r7)
	lwz r6, wp(r13)
	lwz r0, 0xf4(r6)
	add r0, r0, r5
	stw r0, 0xf4(r6)
	lwz r6, wp(r13)
	lwz r0, 0xf4(r6)
	lwz r5, 0xec(r6)
	mulli r0, r0, 0xc
	add r0, r5, r0
	stw r0, 0xfc(r6)
	lwz r5, wp(r13)
	lwz r0, 0xf4(r5)
	add r0, r0, r4
	stw r0, 0xf4(r5)
	L_g5_3:
	bl animPoseMain
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xe8(r3)
	b L_g5_1
	L_g5_2:
	bl animPoseMain
	L_g5_1:
	lwz r4, 0x28(r31)
	mr r3, r16
	bl renderProc
	lwz r3, wp(r13)
	stw r21, 0x18(r3)
	lwz r3, wp(r13)
	stw r20, 0x1c(r3)
	lwz r3, wp(r13)
	stw r19, 0x20(r3)
	lwz r3, wp(r13)
	stw r30, 0x30(r3)
	lwz r3, wp(r13)
	stw r29, 0x34(r3)
	lwz r3, wp(r13)
	stw r28, 0x38(r3)
	lwz r3, wp(r13)
	stw r27, 0x24(r3)
	lwz r3, wp(r13)
	stw r26, 0x28(r3)
	lwz r3, wp(r13)
	stw r25, 0x2c(r3)
	lwz r3, wp(r13)
	stw r24, 0xcc(r3)
	lwz r3, wp(r13)
	stw r23, 0xd0(r3)
	lwz r3, wp(r13)
	stw r22, 0xd4(r3)
	lwz r3, wp(r13)
	stw r18, 0xd8(r3)
	lwz r3, wp(r13)
	stw r17, 0xdc(r3)
	lmw r16, 0x10(r1)
	lwz r0, 0x54(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void animPoseSetDispCallBack(s32 poseId, void* callback, void* userData) {
	nofralloc
	lwz r6, wp(r13)
	mulli r0, r3, 0x170
	lwz r3, 0x10(r6)
	add r3, r3, r0
	stw r4, 0x154(r3)
	stw r5, 0x158(r3)
	blr
}

asm s32 animPoseGetVivianType(s32 poseId) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	addi r0, r3, 0x11c
	lwzx r3, r4, r0
	blr
}

asm void animPoseVivianMain(s32 poseId, Vec* pos) {
	nofralloc
	lwz r5, wp(r13)
	mulli r0, r3, 0x170
	lwz r3, 0x10(r5)
	add r3, r3, r0
	lwz r0, 0x0(r3)
	ori r0, r0, 0x20
	stw r0, 0x0(r3)
	lfs f0, 0x0(r4)
	stfs f0, 0x130(r3)
	lfs f0, 0x4(r4)
	stfs f0, 0x140(r3)
	lfs f0, 0x8(r4)
	stfs f0, 0x150(r3)
	blr
}

asm void animPoseWorldMatrixEvalOn(s32 poseId) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	mulli r0, r3, 0x170
	stw r31, 0xc(r1)
	lwz r5, wp(r13)
	lwz r3, 0x10(r5)
	lwz r5, 0x0(r5)
	add r31, r3, r0
	lwz r0, 0x10(r31)
	lwz r3, 0x0(r31)
	slwi r0, r0, 4
	add r5, r5, r0
	lwz r5, 0x8(r5)
	rlwinm. r0, r3, 0, 24, 24
	lwz r5, 0xa0(r5)
	lwz r5, 0x0(r5)
	bne L_g5_1
	ori r0, r3, 0x80
	stw r0, 0x0(r31)
	lwz r0, 0xc(r31)
	cmpwi r0, 0x1
	beq L_g5_2
	bge L_g5_3
	cmpwi r0, 0x0
	bge L_g5_4
	b L_g5_5
	L_g5_3:
	cmpwi r0, 0x3
	bge L_g5_5
	b L_g5_6
	L_g5_4:
	li r4, 0x1
	b L_g5_5
	L_g5_2:
	li r4, 0x2
	b L_g5_5
	L_g5_6:
	li r4, 0x0
	L_g5_5:
	lwz r0, 0x144(r5)
	stw r0, 0x168(r31)
	lwz r0, 0x144(r5)
	mulli r3, r0, 0x30
	bl smartAlloc
	stw r3, 0x164(r31)
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void L_animPoseWorldPositionEvalOff(s32 poseId) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	mulli r0, r3, 0x170
	stw r31, 0xc(r1)
	lwz r4, wp(r13)
	lwz r3, 0x10(r4)
	add r31, r3, r0
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 25, 25
	beq L_g5_1
	rlwinm r0, r3, 0, 26, 24
	stw r0, 0x0(r31)
	lwz r3, 0x15c(r31)
	bl smartFree
	li r0, 0x0
	stw r0, 0x15c(r31)
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void animPoseWorldPositionEvalOn(s32 poseId) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	mulli r0, r3, 0x170
	stw r31, 0xc(r1)
	lwz r5, wp(r13)
	lwz r3, 0x10(r5)
	lwz r5, 0x0(r5)
	add r31, r3, r0
	lwz r0, 0x10(r31)
	lwz r3, 0x0(r31)
	slwi r0, r0, 4
	add r5, r5, r0
	lwz r5, 0x8(r5)
	rlwinm. r0, r3, 0, 25, 25
	lwz r5, 0xa0(r5)
	lwz r5, 0x0(r5)
	bne L_g5_1
	ori r0, r3, 0x40
	stw r0, 0x0(r31)
	lwz r0, 0xc(r31)
	cmpwi r0, 0x1
	beq L_g5_2
	bge L_g5_3
	cmpwi r0, 0x0
	bge L_g5_4
	b L_g5_5
	L_g5_3:
	cmpwi r0, 0x3
	bge L_g5_5
	b L_g5_6
	L_g5_4:
	li r4, 0x1
	b L_g5_5
	L_g5_2:
	li r4, 0x2
	b L_g5_5
	L_g5_6:
	li r4, 0x0
	L_g5_5:
	lwz r0, 0x144(r5)
	stw r0, 0x160(r31)
	lwz r0, 0x144(r5)
	mulli r3, r0, 0xc
	bl smartAlloc
	stw r3, 0x15c(r31)
	L_g5_1:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void evalProc(s32 parentId, s32 groupId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	mr r30, r4
	cmpwi r30, -0x1
	beq L_g5_1
	lwz r5, wp(r13)
	mulli r0, r30, 0x58
	lwz r4, 0x20(r5)
	lwz r5, 0x18(r5)
	lwz r6, 0x1a8(r4)
	lwz r4, 0x5c(r5)
	add r31, r6, r0
	lwz r0, 0x4c(r31)
	lbzx r0, r4, r0
	extsb. r0, r0
	beq L_g5_2
	lwz r0, 0x54(r31)
	lwz r4, 0x50(r31)
	cmpwi r0, 0x0
	lwz r5, 0x64(r5)
	slwi r0, r4, 2
	add r4, r5, r0
	beq L_g5_3
	cmpwi r3, -0x1
	bne L_g5_4
	lfs f3, float_1_80419a44(r2)
	fmr f2, f3
	fmr f1, f3
	b L_g5_5
	L_g5_4:
	mulli r0, r3, 0x58
	add r3, r6, r0
	lwz r0, 0x54(r3)
	cmpwi r0, 0x0
	bne L_g5_6
	lfs f3, float_1_80419a44(r2)
	fmr f2, f3
	fmr f1, f3
	b L_g5_5
	L_g5_6:
	lwz r0, 0x50(r3)
	slwi r0, r0, 2
	add r3, r5, r0
	lfs f1, 0xc(r3)
	lfs f2, 0x10(r3)
	lfs f3, 0x14(r3)
	L_g5_5:
	mr r3, r4
	bl pushGXModelMtx_JointNode__
	b L_g5_7
	L_g5_3:
	mr r3, r4
	bl pushGXModelMtx_TransformNode__
	L_g5_7:
	lwz r3, wp(r13)
	lwz r4, 0x18(r3)
	lwz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 25, 25
	beq L_g5_8
	lis r3, vec3_802c2dd4@ha
	lwz r7, g_modeling_mtx(r13)
	addi r6, r3, vec3_802c2dd4@l
	lwz r3, 0x15c(r4)
	lwz r5, 0x0(r6)
	mulli r0, r30, 0xc
	lwz r4, 0x4(r6)
	stw r5, 0x8(r1)
	lfs f0, 0xc(r7)
	lwz r5, 0x8(r6)
	stfs f0, 0x8(r1)
	lwz r3, 0x0(r3)
	stw r4, 0xc(r1)
	lfs f1, 0x1c(r7)
	add r4, r3, r0
	stw r5, 0x10(r1)
	lfs f0, 0x2c(r7)
	stfs f1, 0xc(r1)
	lwz r0, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x0(r4)
	lwz r0, 0x10(r1)
	stw r3, 0x4(r4)
	stw r0, 0x8(r4)
	L_g5_8:
	lwz r3, wp(r13)
	lwz r3, 0x18(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 24, 24
	beq L_g5_9
	lwz r4, 0x164(r3)
	mulli r0, r30, 0x30
	lwz r3, g_modeling_mtx(r13)
	lwz r4, 0x0(r4)
	add r4, r4, r0
	bl PSMTXCopy
	L_g5_9:
	lwz r3, wp(r13)
	lwz r3, 0x18(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 26, 26
	beq L_g5_10
	lwz r3, 0x120(r3)
	lwz r0, 0x0(r3)
	cmpw r30, r0
	beq L_g5_11
	L_g5_10:
	lwz r4, 0x44(r31)
	mr r3, r30
	bl evalProc
	L_g5_11:
	lwz r4, g_modeling_mtx_lv(r13)
	lis r3, g_modeling_mtx_stack@ha
	addi r0, r3, g_modeling_mtx_stack@l
	subi r4, r4, 0x1
	mulli r3, r4, 0x30
	stw r4, g_modeling_mtx_lv(r13)
	add r0, r0, r3
	stw r0, g_modeling_mtx(r13)
	L_g5_2:
	lwz r4, 0x40(r31)
	mr r3, r30
	bl evalProc
	L_g5_1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm BOOL animPoseTestXLU(s32 poseId) {
	nofralloc
	lwz r5, wp(r13)
	mulli r0, r3, 0x170
	lwz r4, 0x10(r5)
	lwz r3, 0x0(r5)
	add r4, r4, r0
	lwz r0, 0x10(r4)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xc4(r3)
	extrwi r3, r0, 1, 28
	blr
}

asm AnimTableEntry* animPoseGetCurrentAnim(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r0, r3, 0x170
	lwz r3, 0x10(r4)
	lwz r4, 0x0(r4)
	add r5, r3, r0
	lwz r3, 0x10(r5)
	lwz r0, 0x14(r5)
	slwi r3, r3, 4
	add r3, r4, r3
	slwi r0, r0, 6
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0x1ac(r3)
	add r3, r3, r0
	blr
}

asm AnimationPoseData* animPoseGetAnimBaseDataPtr(s32 poseId) {
	nofralloc
	lwz r5, wp(r13)
	mulli r0, r3, 0x170
	lwz r4, 0x10(r5)
	lwz r3, 0x0(r5)
	add r4, r4, r0
	lwz r0, 0x10(r4)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	blr
}

asm AnimData* animPoseGetAnimDataPtr(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r0, r3, 0x170
	lwz r3, 0x10(r4)
	lwz r4, 0x0(r4)
	add r5, r3, r0
	lwz r3, 0x10(r5)
	lwz r0, 0x14(r5)
	slwi r3, r3, 4
	add r3, r4, r3
	slwi r0, r0, 6
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0x1ac(r3)
	add r3, r3, r0
	lwz r3, 0x3c(r3)
	blr
}

asm AnimationPose* animPoseGetAnimPosePtr(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r0, r3, 0x170
	lwz r3, 0x10(r4)
	add r3, r3, r0
	blr
}

asm BOOL animGroupBaseAsync(const char* name, s32 group, void* callback) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	cmpwi r4, 0x1
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	mr r28, r5
	beq L_g5_1
	bge L_g5_2
	cmpwi r4, 0x0
	bge L_g5_3
	b L_g5_4
	L_g5_2:
	cmpwi r4, 0x3
	bge L_g5_4
	b L_g5_5
	L_g5_3:
	li r3, 0x1
	bl fileSetCurrentArchiveType
	b L_g5_4
	L_g5_1:
	li r3, 0x2
	bl fileSetCurrentArchiveType
	b L_g5_4
	L_g5_5:
	li r3, 0x0
	bl fileSetCurrentArchiveType
	L_g5_4:
	mr r4, r28
	mr r7, r27
	li r3, 0x5
	la r5, str_80419A54(r2)
	la r6, str_80419A5C(r2)
	crclr 6
	bl fileAsyncf
	lwz r4, wp(r13)
	mr r31, r3
	li r29, 0x0
	lwz r3, 0x100(r4)
	lwz r3, 0xa0(r3)
	lwz r28, 0x4(r3)
	lwz r30, 0x0(r3)
	b L_g5_6
	L_g5_7:
	mr r3, r30
	mr r4, r27
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_8
	addi r7, r30, 0x20
	b L_g5_9
	L_g5_8:
	addi r30, r30, 0x20
	addi r29, r29, 0x20
	L_g5_6:
	cmpw r29, r28
	blt L_g5_7
	la r7, zero_80419a50(r2)
	L_g5_9:
	lis r3, str_802C2DE8@ha
	li r4, 0x0
	addi r5, r3, str_802C2DE8@l
	la r6, str_80419A5C(r2)
	li r3, 0x4
	crclr 6
	bl fileAsyncf
	cmpwi r31, -0x1
	bne L_g5_10
	li r3, 0x1
	b L_g5_11
	L_g5_10:
	cmplwi r31, 0x0
	bne L_g5_12
	li r3, 0x0
	b L_g5_11
	L_g5_12:
	cmpwi r3, -0x1
	bne L_g5_13
	li r3, 0x1
	b L_g5_11
	L_g5_13:
	neg r0, r3
	or r0, r0, r3
	srwi r3, r0, 31
	L_g5_11:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animSetPaperTexMtx(Mtx mtx1, Mtx mtx2, Mtx mtx3) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmplwi r3, 0x0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	mr r31, r5
	stw r30, 0x8(r1)
	mr r30, r4
	bne L_g5_1
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xcc(r3)
	b L_g5_2
	L_g5_1:
	lwz r4, wp(r13)
	addi r4, r4, 0x3c
	bl PSMTXCopy
	lwz r3, wp(r13)
	addi r0, r3, 0x3c
	stw r0, 0xcc(r3)
	L_g5_2:
	cmplwi r30, 0x0
	bne L_g5_3
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xd0(r3)
	b L_g5_4
	L_g5_3:
	lwz r4, wp(r13)
	mr r3, r30
	addi r4, r4, 0x6c
	bl PSMTXCopy
	lwz r3, wp(r13)
	addi r0, r3, 0x6c
	stw r0, 0xd0(r3)
	L_g5_4:
	cmplwi r31, 0x0
	bne L_g5_5
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xd4(r3)
	b L_g5_6
	L_g5_5:
	lwz r4, wp(r13)
	mr r3, r31
	addi r4, r4, 0x9c
	bl PSMTXCopy
	lwz r3, wp(r13)
	addi r0, r3, 0x9c
	stw r0, 0xd4(r3)
	L_g5_6:
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void animPoseDisp_MakeExtTexture(const char* group, const char* anim, f32 frame, f32 scale, GXTexObj* obj,
                                 smartEntry** image, s32* x0, s32* y0, s32* x1, s32* y1) {
	nofralloc
	stwu r1, -0x240(r1)
	mflr r0
	stw r0, 0x244(r1)
	stfd f31, 0x230(r1)
	psq_st f31, 0x238(r1), 0, 0
	stfd f30, 0x220(r1)
	psq_st f30, 0x228(r1), 0, 0
	stfd f29, 0x210(r1)
	psq_st f29, 0x218(r1), 0, 0
	stmw r17, 0x1d4(r1)
	lwz r11, gp(r13)
	li r31, 0x0
	fmr f29, f1
	mr r29, r3
	lwz r3, 0x14(r11)
	fmr f31, f2
	mr r20, r4
	mr r25, r5
	neg r0, r3
	mr r27, r6
	or r0, r0, r3
	mr r24, r7
	mr r23, r8
	mr r22, r9
	mr r21, r10
	mr r28, r31
	srwi r26, r0, 31
	b L_g5_1
	L_g5_2:
	lwz r0, 0x10(r5)
	add r3, r0, r28
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_g5_3
	lwz r0, 0xc(r3)
	cmpw r0, r26
	bne L_g5_3
	lwz r0, 0x10(r3)
	mr r4, r29
	lwz r5, 0x0(r5)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r5, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	beq L_g5_4
	L_g5_3:
	addi r28, r28, 0x170
	addi r31, r31, 0x1
	L_g5_1:
	lwz r5, wp(r13)
	lwz r0, 0x14(r5)
	cmpw r31, r0
	blt L_g5_2
	L_g5_4:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r31, r0
	bne L_g5_5
	li r31, -0x1
	L_g5_5:
	cmpwi r31, 0x0
	blt L_g5_6
	mulli r29, r31, 0x170
	lwz r3, 0x10(r3)
	li r0, 0x2e
	addi r5, r1, 0x44
	add r30, r3, r29
	subi r4, r30, 0x4
	mtctr r0
	L_g5_7:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz L_g5_7
	li r0, -0x1
	cmpwi r20, 0x0
	stw r0, 0x90(r30)
	lwz r3, wp(r13)
	lwz r0, 0x10(r3)
	lwz r3, 0x0(r3)
	add r28, r0, r29
	lwz r0, 0x10(r28)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r18, 0x0(r3)
	lwz r26, 0x148(r18)
	bge L_g5_8
	li r19, 0x0
	mr r17, r19
	b L_g5_9
	L_g5_10:
	lwz r0, 0x1ac(r18)
	mr r4, r20
	add r3, r0, r17
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_11
	b L_g5_12
	L_g5_11:
	addi r17, r17, 0x40
	addi r19, r19, 0x1
	L_g5_9:
	cmpw r19, r26
	blt L_g5_10
	b L_g5_13
	L_g5_8:
	cmpw r20, r26
	bge L_g5_13
	mr r19, r20
	b L_g5_12
	L_g5_13:
	li r19, 0x0
	L_g5_12:
	lwz r0, 0x14(r28)
	cmpw r19, r0
	beq L_g5_14
	stw r19, 0x14(r28)
	lwz r0, 0x90(r28)
	cmpwi r0, -0x1
	beq L_g5_15
	lwz r3, 0x0(r28)
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_15
	ori r0, r3, 0x4
	stw r0, 0x0(r28)
	L_g5_15:
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	bne L_g5_16
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_17
	L_g5_16:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_17:
	stw r4, 0x1c(r28)
	li r4, -0x1
	lfs f0, float_0_80419a48(r2)
	li r0, 0x0
	stw r3, 0x18(r28)
	stw r4, 0x3c(r28)
	stfs f0, 0x40(r28)
	stw r0, 0x80(r28)
	stfs f0, 0x84(r28)
	L_g5_14:
	lwz r0, 0xc(r30)
	cmpwi r0, 0x0
	bne L_g5_18
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_19
	L_g5_18:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_19:
	stw r4, 0x1c(r30)
	li r4, -0x1
	lfs f0, float_16p667_80419a60(r2)
	li r0, 0x0
	stw r3, 0x18(r30)
	fmuls f1, f0, f29
	lfs f0, float_0_80419a48(r2)
	stw r4, 0x3c(r30)
	stfs f0, 0x40(r30)
	stw r0, 0x80(r30)
	stfs f0, 0x84(r30)
	lwz r3, wp(r13)
	lwz r0, 0x10(r3)
	add r29, r0, r29
	bl __cvt_dbl_usll
	lwz r0, 0xc(r29)
	mr r28, r4
	mr r26, r3
	cmpwi r0, 0x0
	bne L_g5_20
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_21
	L_g5_20:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_21:
	subfc r0, r28, r4
	stw r0, 0x1c(r29)
	subfe r0, r26, r3
	stw r0, 0x18(r29)
	lwz r0, 0x18(r29)
	lwz r3, 0x1c(r29)
	stw r3, 0x8c(r29)
	stw r0, 0x88(r29)
	lwz r0, 0x90(r29)
	cmpwi r0, -0x1
	beq L_g5_22
	lwz r3, wp(r13)
	mulli r0, r0, 0x170
	lwz r3, 0x10(r3)
	add r4, r3, r0
	lwz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 30, 30
	bne L_g5_22
	lwz r0, 0x18(r29)
	lwz r3, 0x1c(r29)
	stw r3, 0x1c(r4)
	stw r0, 0x18(r4)
	L_g5_22:
	mr r3, r31
	bl animPoseMain
	bl DEMOGetRenderModeObj
	lhz r4, 0x4(r3)
	lis r0, 0x4330
	lis r3, double_to_int_mask_802c2de0@ha
	stw r0, 0x1b8(r1)
	lfd f2, double_to_int_mask_802c2de0@l(r3)
	stw r4, 0x1bc(r1)
	lfs f0, float_0p5_80419a64(r2)
	lfd f1, 0x1b8(r1)
	fsubs f1, f1, f2
	fmuls f30, f0, f1
	bl DEMOGetRenderModeObj
	lhz r4, 0x6(r3)
	lis r0, 0x4330
	lis r3, double_to_int_mask_802c2de0@ha
	stw r0, 0x1c0(r1)
	lfd f2, double_to_int_mask_802c2de0@l(r3)
	stw r4, 0x1c4(r1)
	lfs f0, float_0p75_80419a68(r2)
	lfd f1, 0x1c0(r1)
	fsubs f1, f1, f2
	fmuls f29, f0, f1
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	bl DEMOGetRenderModeObj
	lhz r4, 0x6(r3)
	lis r0, 0x4330
	lis r3, double_to_int_mask_802c2de0@ha
	lfs f1, float_0_80419a48(r2)
	stw r4, 0x1cc(r1)
	lfd f4, double_to_int_mask_802c2de0@l(r3)
	fmr f3, f1
	stw r0, 0x1c8(r1)
	addi r3, r1, 0x18
	lfs f0, float_0p25_80419a6c(r2)
	lfd f2, 0x1c8(r1)
	fsubs f2, f2, f4
	fneg f2, f2
	fmuls f2, f0, f2
	bl PSMTXTrans
	lwz r17, 0x0(r30)
	li r0, 0x0
	lwz r4, 0xf0(r30)
	fmr f2, f31
	lwz r6, 0xf4(r30)
	rlwinm r5, r17, 0, 29, 27
	lwz r18, 0xe8(r30)
	mr r3, r30
	stw r4, 0x14(r1)
	lfs f1, float_0_80419a48(r2)
	addi r4, r1, 0x18
	stw r5, 0x0(r30)
	li r5, 0x1
	stw r0, 0xe8(r30)
	lwz r0, dat_80419a3c(r2)
	stw r6, 0x10(r1)
	stw r0, 0xf0(r30)
	lwz r0, dat_80419a40(r2)
	stw r0, 0xf4(r30)
	bl _animPoseDrawMtx
	fmr f2, f31
	lfs f1, float_0_80419a48(r2)
	mr r3, r30
	addi r4, r1, 0x18
	li r5, 0x2
	bl _animPoseDrawMtx
	fmr f2, f31
	lfs f1, float_0_80419a48(r2)
	mr r3, r30
	addi r4, r1, 0x18
	li r5, 0x3
	bl _animPoseDrawMtx
	lwz r3, 0x14(r1)
	lwz r0, 0x10(r1)
	stw r3, 0xf0(r30)
	stw r0, 0xf4(r30)
	stw r17, 0x0(r30)
	stw r18, 0xe8(r30)
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lhz r3, 0xe(r1)
	lhz r0, 0xa(r1)
	cmplw r3, r0
	ble L_g5_23
	li r3, 0x0
	li r0, 0x10
	sth r3, 0xe(r1)
	sth r3, 0xc(r1)
	sth r0, 0xa(r1)
	sth r0, 0x8(r1)
	L_g5_23:
	lhz r0, 0xe(r1)
	cmplwi r0, 0x2
	bge L_g5_24
	li r0, 0x2
	sth r0, 0xe(r1)
	L_g5_24:
	lhz r0, 0xc(r1)
	cmplwi r0, 0x2
	bge L_g5_25
	li r0, 0x2
	sth r0, 0xc(r1)
	L_g5_25:
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	lhz r0, 0xa(r1)
	subi r3, r3, 0x2
	cmpw r0, r3
	ble L_g5_26
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	subi r0, r3, 0x2
	sth r0, 0xa(r1)
	L_g5_26:
	bl DEMOGetRenderModeObj
	lhz r3, 0x6(r3)
	lhz r0, 0xc(r1)
	subi r3, r3, 0x2
	cmpw r0, r3
	ble L_g5_27
	bl DEMOGetRenderModeObj
	lhz r3, 0x6(r3)
	subi r0, r3, 0x2
	sth r0, 0xc(r1)
	L_g5_27:
	lhz r3, 0xe(r1)
	lhz r6, 0xc(r1)
	clrlwi r0, r3, 31
	lhz r5, 0xa(r1)
	subf r9, r0, r3
	lhz r4, 0x8(r1)
	clrlwi r0, r6, 31
	clrlwi r3, r5, 31
	add r7, r5, r3
	sth r9, 0xe(r1)
	subf r8, r0, r6
	clrlwi r0, r4, 31
	add r6, r4, r0
	clrlwi r3, r9, 16
	clrlwi r5, r7, 16
	clrlwi r4, r8, 16
	clrlwi r0, r6, 16
	sth r8, 0xc(r1)
	subf r5, r3, r5
	subf r0, r4, r0
	sth r7, 0xa(r1)
	clrlwi r17, r5, 16
	clrlwi r18, r0, 16
	sth r6, 0x8(r1)
	mr r5, r17
	mr r6, r18
	bl GXSetTexCopySrc
	mr r3, r17
	mr r4, r18
	li r5, 0x5
	li r6, 0x0
	bl GXSetTexCopyDst
	mr r3, r17
	mr r4, r18
	li r5, 0x5
	li r6, 0x0
	li r7, 0x0
	bl GXGetTexBufferSize
	lwz r0, anim_ext_tex_size(r13)
	mr r4, r18
	li r5, 0x5
	li r6, 0x0
	add r0, r0, r3
	mr r3, r17
	stw r0, anim_ext_tex_size(r13)
	li r7, 0x0
	bl GXGetTexBufferSize
	li r4, 0x1
	bl smartAlloc
	stw r3, 0x0(r27)
	li r4, 0x1
	lwz r3, 0x0(r27)
	lwz r3, 0x0(r3)
	bl GXCopyTex
	bl GXPixModeSync
	lwz r4, 0x0(r27)
	mr r3, r25
	mr r5, r17
	mr r6, r18
	lwz r4, 0x0(r4)
	li r7, 0x5
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	fctiwz f1, f30
	lhz r3, 0xe(r1)
	fctiwz f0, f29
	li r0, 0x2e
	subi r5, r30, 0x4
	addi r4, r1, 0x44
	stfd f1, 0x1c8(r1)
	lwz r6, 0x1cc(r1)
	stfd f0, 0x1c0(r1)
	subf r3, r6, r3
	stw r3, 0x0(r24)
	lwz r7, 0x1c4(r1)
	lhz r3, 0xc(r1)
	subf r3, r7, r3
	stw r3, 0x0(r23)
	lhz r3, 0xa(r1)
	subf r3, r6, r3
	stw r3, 0x0(r22)
	lhz r3, 0x8(r1)
	subf r3, r7, r3
	stw r3, 0x0(r21)
	mtctr r0
	L_g5_28:
	lwz r3, 0x4(r4)
	lwzu r0, 0x8(r4)
	stw r3, 0x4(r5)
	stwu r0, 0x8(r5)
	bdnz L_g5_28
	L_g5_6:
	psq_l f31, 0x238(r1), 0, 0
	lfd f31, 0x230(r1)
	psq_l f30, 0x228(r1), 0, 0
	lfd f30, 0x220(r1)
	psq_l f29, 0x218(r1), 0, 0
	lfd f29, 0x210(r1)
	lmw r17, 0x1d4(r1)
	lwz r0, 0x244(r1)
	mtlr r0
	addi r1, r1, 0x240
	blr
}

asm void animPaperPoseDispSub(s32 unused, AnimationPose* pose) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stfd f31, 0xf0(r1)
	psq_st f31, 0xf8(r1), 0, 0
	stfd f30, 0xe0(r1)
	psq_st f30, 0xe8(r1), 0, 0
	stmw r27, 0xcc(r1)
	lwz r0, 0x0(r4)
	mr r30, r4
	lfs f31, float_8_80419a70(r2)
	clrlwi. r0, r0, 31
	beq L_g5_1
	lwz r3, wp(r13)
	lwz r0, 0x10(r30)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	lwz r0, 0x14(r30)
	add r3, r4, r3
	lfs f2, float_25p74_80419a74(r2)
	lwz r3, 0x8(r3)
	slwi r0, r0, 6
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0x1ac(r3)
	add r3, r3, r0
	lwz r29, 0x3c(r3)
	lfs f1, 0x54(r29)
	lfs f0, 0x48(r29)
	fsubs f0, f1, f0
	fdivs f0, f2, f0
	fmuls f31, f31, f0
	bl DEMOGetRenderModeObj
	lhz r4, 0x6(r3)
	lis r0, 0x4330
	lis r3, double_to_int_mask_802c2de0@ha
	stw r0, 0x78(r1)
	lfd f2, double_to_int_mask_802c2de0@l(r3)
	stw r4, 0x7c(r1)
	lfs f0, float_0p75_80419a68(r2)
	lfd f1, 0x78(r1)
	fsubs f1, f1, f2
	fmuls f30, f0, f1
	bl sysWaitDrawSync
	bl GXClearBoundingBox
	bl DEMOGetRenderModeObj
	lhz r4, 0x6(r3)
	lis r0, 0x4330
	lfs f0, 0x48(r29)
	lis r3, double_to_int_mask_802c2de0@ha
	stw r4, 0x84(r1)
	addi r4, r3, double_to_int_mask_802c2de0@l
	lfs f1, float_0_80419a48(r2)
	fmuls f0, f0, f31
	stw r0, 0x80(r1)
	addi r3, r1, 0x48
	lfd f5, 0x0(r4)
	fmr f3, f1
	lfd f4, 0x80(r1)
	lfs f2, float_0p25_80419a6c(r2)
	fsubs f4, f4, f5
	fneg f4, f4
	fmsubs f2, f2, f4, f0
	bl PSMTXTrans
	lwz r28, 0x0(r30)
	li r0, 0x0
	lwz r5, 0xf0(r30)
	lwz r4, 0xf4(r30)
	rlwinm r3, r28, 0, 29, 27
	lwz r31, 0xe8(r30)
	lwz r27, 0xec(r30)
	stw r5, 0x14(r1)
	stw r3, 0x0(r30)
	lwz r3, dat_80419a34(r2)
	stw r4, 0x10(r1)
	stw r3, 0xf0(r30)
	lwz r3, dat_80419a38(r2)
	stw r3, 0xf4(r30)
	stw r0, 0xec(r30)
	lwz r0, 0x11c(r30)
	cmpwi r0, 0x0
	beq L_g5_2
	addi r3, r30, 0x124
	addi r4, r1, 0x18
	bl PSMTXCopy
	addi r3, r1, 0x48
	addi r4, r30, 0x124
	bl PSMTXCopy
	L_g5_2:
	fmr f2, f31
	lfs f1, float_0_80419a48(r2)
	mr r3, r30
	addi r4, r1, 0x48
	li r5, 0x2
	bl _animPoseDrawMtx
	stw r28, 0x0(r30)
	lwz r3, 0x14(r1)
	stw r31, 0xe8(r30)
	lwz r0, 0x10(r1)
	stw r3, 0xf0(r30)
	stw r0, 0xf4(r30)
	stw r27, 0xec(r30)
	lwz r0, 0x11c(r30)
	cmpwi r0, 0x0
	beq L_g5_3
	addi r3, r1, 0x18
	addi r4, r30, 0x124
	bl PSMTXCopy
	L_g5_3:
	bl sysWaitDrawSync
	addi r3, r1, 0xe
	addi r4, r1, 0xc
	addi r5, r1, 0xa
	addi r6, r1, 0x8
	bl GXReadBoundingBox
	lhz r3, 0xe(r1)
	lhz r0, 0xa(r1)
	cmplw r3, r0
	ble L_g5_4
	li r3, 0x0
	li r0, 0x10
	sth r3, 0xe(r1)
	sth r3, 0xc(r1)
	sth r0, 0xa(r1)
	sth r0, 0x8(r1)
	L_g5_4:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_5
	rlwinm. r0, r3, 0, 29, 29
	beq L_g5_5
	lwz r3, gp(r13)
	lwz r0, 0x14(r3)
	cmpwi r0, 0x0
	beq L_g5_5
	bl DEMOGetRenderModeObj
	lhz r4, 0x4(r3)
	lis r0, 0x4330
	stw r0, 0x80(r1)
	lis r3, double_to_int_802c2df0@ha
	srwi r0, r4, 1
	lfd f2, double_to_int_802c2df0@l(r3)
	xoris r0, r0, 0x8000
	lfs f0, 0x44(r29)
	stw r0, 0x84(r1)
	lfd f1, 0x80(r1)
	fsubs f1, f1, f2
	fmadds f0, f0, f31, f1
	fctiwz f0, f0
	stfd f0, 0x78(r1)
	lwz r27, 0x7c(r1)
	bl DEMOGetRenderModeObj
	lhz r0, 0x4(r3)
	lis r3, 0x4330
	lis r5, double_to_int_802c2df0@ha
	fctiwz f0, f30
	srwi r4, r0, 1
	lhz r0, 0xe(r1)
	xoris r4, r4, 0x8000
	stw r3, 0x88(r1)
	lfd f4, double_to_int_802c2df0@l(r5)
	stw r4, 0x8c(r1)
	cmpw r27, r0
	lfs f2, 0x54(r29)
	lfd f3, 0x88(r1)
	lfs f1, 0x48(r29)
	fsubs f4, f3, f4
	lfs f3, 0x50(r29)
	fsubs f1, f2, f1
	stfd f0, 0xa0(r1)
	fmadds f2, f3, f31, f4
	lwz r5, 0xa4(r1)
	fnmsubs f0, f31, f1, f30
	fctiwz f1, f2
	fctiwz f0, f0
	stfd f1, 0x90(r1)
	stfd f0, 0x98(r1)
	lwz r3, 0x94(r1)
	lwz r4, 0x9c(r1)
	bgt L_g5_5
	lhz r0, 0xa(r1)
	cmpw r3, r0
	blt L_g5_5
	lhz r0, 0xc(r1)
	cmpw r4, r0
	bgt L_g5_5
	lhz r0, 0x8(r1)
	cmpw r5, r0
	blt L_g5_5
	sth r27, 0xe(r1)
	sth r3, 0xa(r1)
	sth r4, 0xc(r1)
	sth r5, 0x8(r1)
	L_g5_5:
	lhz r0, 0xe(r1)
	cmplwi r0, 0x2
	bge L_g5_6
	li r0, 0x2
	sth r0, 0xe(r1)
	L_g5_6:
	lhz r0, 0xc(r1)
	cmplwi r0, 0x2
	bge L_g5_7
	li r0, 0x2
	sth r0, 0xc(r1)
	L_g5_7:
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	lhz r0, 0xa(r1)
	subi r3, r3, 0x2
	cmpw r0, r3
	ble L_g5_8
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	subi r0, r3, 0x2
	sth r0, 0xa(r1)
	L_g5_8:
	bl DEMOGetRenderModeObj
	lhz r3, 0x6(r3)
	lhz r0, 0x8(r1)
	subi r3, r3, 0x2
	cmpw r0, r3
	ble L_g5_9
	bl DEMOGetRenderModeObj
	lhz r3, 0x6(r3)
	subi r0, r3, 0x2
	sth r0, 0x8(r1)
	L_g5_9:
	lwz r3, 0x0(r30)
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_10
	rlwinm. r0, r3, 0, 29, 29
	beq L_g5_11
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	lhz r0, 0xe(r1)
	srwi r3, r3, 1
	subf r27, r0, r3
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	mr r31, r27
	lhz r0, 0xa(r1)
	srwi r3, r3, 1
	subf r0, r3, r0
	cmpw r27, r0
	bge L_g5_12
	mr r31, r0
	L_g5_12:
	lhz r3, 0xc(r1)
	lis r4, 0x4330
	lhz r0, 0x8(r1)
	xoris r5, r31, 0x8000
	lis r6, double_to_int_802c2df0@ha
	stw r5, 0xa4(r1)
	subf r0, r3, r0
	lfd f3, double_to_int_802c2df0@l(r6)
	xoris r0, r0, 0x8000
	stw r4, 0xa0(r1)
	lfs f4, float_0p5_80419a64(r2)
	lfd f2, 0xa0(r1)
	stw r0, 0x94(r1)
	fsubs f2, f2, f3
	lfs f1, float_0p14881_80419a78(r2)
	stw r4, 0x90(r1)
	lfd f0, 0x90(r1)
	fmuls f2, f4, f2
	fsubs f0, f0, f3
	fmuls f0, f1, f0
	fctiwz f1, f2
	fctiwz f0, f0
	stfd f1, 0x98(r1)
	stfd f0, 0x88(r1)
	lwz r27, 0x9c(r1)
	lwz r28, 0x8c(r1)
	bl DEMOGetRenderModeObj
	lhz r0, 0x4(r3)
	srwi r0, r0, 1
	subf r0, r31, r0
	subf r0, r27, r0
	sth r0, 0x114(r30)
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	lis r0, 0x4330
	lis r4, double_to_int_802c2df0@ha
	lfs f0, float_8_80419a70(r2)
	srwi r5, r3, 1
	lis r3, double_to_int_mask_802c2de0@ha
	add r5, r5, r27
	fdivs f5, f0, f31
	add r5, r31, r5
	lfd f4, double_to_int_802c2df0@l(r4)
	sth r5, 0x116(r30)
	lfd f1, double_to_int_mask_802c2de0@l(r3)
	lhz r4, 0xc(r1)
	subf r4, r28, r4
	stw r0, 0x80(r1)
	lfs f2, float_150_80419a7c(r2)
	sth r4, 0x118(r30)
	lfs f0, float_215_80419a80(r2)
	lhz r4, 0x8(r1)
	stw r0, 0x78(r1)
	add r4, r4, r28
	sth r4, 0x11a(r30)
	lha r4, 0x114(r30)
	lha r3, 0x116(r30)
	stw r0, 0xa8(r1)
	subf r0, r4, r3
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f3, 0x80(r1)
	fsubs f3, f3, f4
	fdivs f2, f3, f2
	fmuls f2, f5, f2
	stfs f2, 0xf8(r30)
	lha r3, 0x118(r30)
	lha r0, 0x11a(r30)
	subf r0, r3, r0
	xoris r0, r0, 0x8000
	stw r0, 0x7c(r1)
	lfd f2, 0x78(r1)
	fsubs f2, f2, f4
	fdivs f0, f2, f0
	fmuls f0, f5, f0
	stfs f0, 0xfc(r30)
	lhz r0, 0x8(r1)
	lfs f2, 0x48(r29)
	stw r0, 0xac(r1)
	lfd f0, 0xa8(r1)
	fsubs f0, f0, f1
	fsubs f0, f30, f0
	fdivs f0, f0, f31
	fadds f0, f2, f0
	stfs f0, 0x100(r30)
	lwz r0, 0x0(r30)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x0(r30)
	b L_g5_11
	L_g5_10:
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	lhz r0, 0xe(r1)
	srwi r3, r3, 1
	subf r27, r0, r3
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	mr r31, r27
	lhz r0, 0xa(r1)
	srwi r3, r3, 1
	subf r0, r3, r0
	cmpw r27, r0
	bge L_g5_13
	mr r31, r0
	L_g5_13:
	lhz r3, 0xc(r1)
	lis r4, 0x4330
	lhz r0, 0x8(r1)
	xoris r5, r31, 0x8000
	lis r6, double_to_int_802c2df0@ha
	stw r5, 0xac(r1)
	subf r0, r3, r0
	lfd f3, double_to_int_802c2df0@l(r6)
	xoris r0, r0, 0x8000
	stw r4, 0xa8(r1)
	lfs f4, float_0p5_80419a64(r2)
	lfd f2, 0xa8(r1)
	stw r0, 0x9c(r1)
	fsubs f2, f2, f3
	lfs f1, float_0p14881_80419a78(r2)
	stw r4, 0x98(r1)
	lfd f0, 0x98(r1)
	fmuls f2, f4, f2
	fsubs f0, f0, f3
	fmuls f0, f1, f0
	fctiwz f1, f2
	fctiwz f0, f0
	stfd f1, 0xa0(r1)
	stfd f0, 0x90(r1)
	lwz r27, 0xa4(r1)
	lwz r28, 0x94(r1)
	bl DEMOGetRenderModeObj
	lhz r0, 0x4(r3)
	srwi r0, r0, 1
	subf r0, r31, r0
	subf r0, r27, r0
	sth r0, 0x114(r30)
	bl DEMOGetRenderModeObj
	lhz r3, 0x4(r3)
	lis r0, 0x4330
	lis r4, double_to_int_802c2df0@ha
	lfs f0, float_8_80419a70(r2)
	srwi r5, r3, 1
	lis r3, double_to_int_mask_802c2de0@ha
	add r5, r5, r27
	fdivs f5, f0, f31
	add r5, r31, r5
	lfd f4, double_to_int_802c2df0@l(r4)
	sth r5, 0x116(r30)
	lfd f1, double_to_int_mask_802c2de0@l(r3)
	lhz r4, 0xc(r1)
	subf r4, r28, r4
	stw r0, 0x88(r1)
	lfs f2, float_150_80419a7c(r2)
	sth r4, 0x118(r30)
	lfs f0, float_215_80419a80(r2)
	lhz r4, 0x8(r1)
	stw r0, 0x80(r1)
	add r4, r4, r28
	sth r4, 0x11a(r30)
	lha r4, 0x114(r30)
	lha r3, 0x116(r30)
	stw r0, 0x78(r1)
	subf r0, r4, r3
	xoris r0, r0, 0x8000
	stw r0, 0x8c(r1)
	lfd f3, 0x88(r1)
	fsubs f3, f3, f4
	fdivs f2, f3, f2
	fmuls f2, f5, f2
	stfs f2, 0xf8(r30)
	lha r3, 0x118(r30)
	lha r0, 0x11a(r30)
	subf r0, r3, r0
	xoris r0, r0, 0x8000
	stw r0, 0x84(r1)
	lfd f2, 0x80(r1)
	fsubs f2, f2, f4
	fdivs f0, f2, f0
	fmuls f0, f5, f0
	stfs f0, 0xfc(r30)
	lhz r0, 0x8(r1)
	lfs f2, 0x48(r29)
	stw r0, 0x7c(r1)
	lfd f0, 0x78(r1)
	fsubs f0, f0, f1
	fsubs f0, f30, f0
	fdivs f0, f0, f31
	fadds f0, f2, f0
	stfs f0, 0x100(r30)
	L_g5_11:
	lhz r3, 0xc(r1)
	lis r7, 0x4330
	lhz r5, 0xe(r1)
	lis r4, double_to_int_mask_802c2de0@ha
	subi r8, r3, 0x2
	lhz r3, 0x8(r1)
	subi r0, r5, 0x2
	lhz r5, 0xa(r1)
	addi r11, r3, 0x2
	sth r0, 0xe(r1)
	addi r6, r5, 0x2
	clrlwi r3, r0, 16
	clrlwi r0, r0, 31
	sth r8, 0xc(r1)
	subf r10, r0, r3
	clrlwi r3, r8, 16
	clrlwi r0, r8, 31
	clrlwi r5, r6, 16
	subf r8, r0, r3
	clrlwi r9, r10, 16
	lis r3, double_to_int_802c2df0@ha
	lfd f4, double_to_int_mask_802c2de0@l(r4)
	clrlwi r0, r6, 31
	sth r6, 0xa(r1)
	add r6, r5, r0
	clrlwi r5, r11, 16
	clrlwi r0, r11, 31
	sth r11, 0x8(r1)
	add r5, r5, r0
	lfd f3, double_to_int_802c2df0@l(r3)
	clrlwi r0, r6, 16
	sth r10, 0xe(r1)
	subf r0, r9, r0
	clrlwi r4, r8, 16
	sth r8, 0xc(r1)
	clrlwi r3, r5, 16
	clrlwi r28, r0, 16
	subf r0, r4, r3
	sth r6, 0xa(r1)
	clrlwi r29, r0, 16
	sth r5, 0x8(r1)
	lha r4, 0x114(r30)
	lha r0, 0x116(r30)
	xoris r3, r4, 0x8000
	stw r9, 0xac(r1)
	subf r0, r4, r0
	stw r7, 0xa8(r1)
	xoris r0, r0, 0x8000
	lfd f0, 0xa8(r1)
	stw r3, 0xa4(r1)
	fsubs f1, f0, f4
	stw r7, 0xa0(r1)
	lfd f0, 0xa0(r1)
	stw r0, 0x9c(r1)
	fsubs f0, f0, f3
	stw r7, 0x98(r1)
	fsubs f1, f1, f0
	lfd f0, 0x98(r1)
	stw r7, 0x90(r1)
	fsubs f0, f0, f3
	fneg f1, f1
	stw r7, 0x88(r1)
	stw r7, 0x80(r1)
	fdivs f0, f1, f0
	stfs f0, 0x104(r30)
	lha r5, 0x118(r30)
	lhz r4, 0xc(r1)
	xoris r3, r5, 0x8000
	lha r0, 0x11a(r30)
	stw r4, 0x94(r1)
	subf r0, r5, r0
	stw r3, 0x8c(r1)
	xoris r0, r0, 0x8000
	lfd f1, 0x90(r1)
	lfd f0, 0x88(r1)
	fsubs f2, f1, f4
	stw r0, 0x84(r1)
	fsubs f1, f0, f3
	lfd f0, 0x80(r1)
	fsubs f1, f2, f1
	fsubs f0, f0, f3
	fneg f1, f1
	fdivs f0, f1, f0
	stfs f0, 0x108(r30)
	lha r3, 0x114(r30)
	mr r5, r28
	lha r0, 0x116(r30)
	mr r6, r29
	stw r7, 0x78(r1)
	subf r0, r3, r0
	xoris r0, r0, 0x8000
	stw r28, 0xb4(r1)
	stw r0, 0x7c(r1)
	stw r7, 0xb0(r1)
	lfd f1, 0x78(r1)
	lfd f0, 0xb0(r1)
	fsubs f1, f1, f3
	stw r7, 0xb8(r1)
	fsubs f0, f0, f4
	stw r29, 0xc4(r1)
	fdivs f1, f1, f0
	stw r7, 0xc0(r1)
	lfd f0, 0xc0(r1)
	stfs f1, 0x10c(r30)
	fsubs f0, f0, f4
	lha r3, 0x118(r30)
	lha r0, 0x11a(r30)
	subf r0, r3, r0
	xoris r0, r0, 0x8000
	stw r0, 0xbc(r1)
	lfd f1, 0xb8(r1)
	fsubs f1, f1, f3
	fdivs f0, f1, f0
	stfs f0, 0x110(r30)
	lhz r3, 0xe(r1)
	lhz r4, 0xc(r1)
	bl GXSetTexCopySrc
	mr r3, r28
	mr r4, r29
	li r5, 0x5
	li r6, 0x0
	bl GXSetTexCopyDst
	mr r3, r28
	mr r4, r29
	li r5, 0x5
	li r6, 0x0
	li r7, 0x0
	bl GXGetTexBufferSize
	li r4, 0x3
	bl smartAlloc
	stw r3, 0x98(r30)
	li r4, 0x1
	lwz r3, 0x98(r30)
	lwz r3, 0x0(r3)
	bl GXCopyTex
	bl GXPixModeSync
	lwz r4, 0x98(r30)
	mr r5, r28
	mr r6, r29
	addi r3, r30, 0xa0
	lwz r4, 0x0(r4)
	li r7, 0x5
	li r8, 0x0
	li r9, 0x0
	li r10, 0x0
	bl GXInitTexObj
	li r0, 0x0
	stw r0, 0x9c(r30)
	L_g5_1:
	psq_l f31, 0xf8(r1), 0, 0
	lfd f31, 0xf0(r1)
	psq_l f30, 0xe8(r1), 0, 0
	lfd f30, 0xe0(r1)
	lmw r27, 0xcc(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void animPaperPoseDisp(CameraId camId, void* param) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	stw r31, 0xc(r1)
	li r31, 0x0
	stw r30, 0x8(r1)
	lwz r3, wp(r13)
	lwz r30, 0x10(r3)
	b L_g5_1
	L_g5_2:
	lwz r0, 0x0(r30)
	clrlwi. r0, r0, 31
	beq L_g5_3
	lwz r0, 0x90(r30)
	cmpwi r0, -0x1
	beq L_g5_3
	mr r4, r30
	li r3, 0x0
	bl animPaperPoseDispSub
	L_g5_3:
	addi r31, r31, 0x1
	addi r30, r30, 0x170
	L_g5_1:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r31, r0
	blt L_g5_2
	lwz r0, 0x14(r1)
	lwz r31, 0xc(r1)
	lwz r30, 0x8(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void animPoseAutoRelease(s32 type) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r26, 0x8(r1)
	mr r28, r3
	li r29, 0x0
	li r31, 0x0
	b L_g5_1
	L_g5_2:
	lwz r0, 0x10(r3)
	add r30, r0, r31
	lwz r3, 0x0(r30)
	clrlwi. r0, r3, 31
	beq L_g5_3
	lwz r0, 0xc(r30)
	cmpw r0, r28
	bne L_g5_3
	lwz r0, 0x4(r30)
	cmplwi r0, 0x0
	beq L_g5_4
	lwz r3, 0x8(r30)
	subi r0, r3, 0x1
	stw r0, 0x8(r30)
	lwz r0, 0x8(r30)
	cmpwi r0, 0x0
	bge L_g5_3
	lwz r3, wp(r13)
	lwz r0, 0x10(r30)
	lwz r3, 0x0(r3)
	slwi r0, r0, 4
	add r27, r3, r0
	lwz r3, 0x4(r27)
	subi r0, r3, 0x1
	stw r0, 0x4(r27)
	lwz r0, 0x4(r27)
	cmpwi r0, 0x0
	bgt L_g5_5
	li r0, 0x0
	stw r0, 0x0(r27)
	lwz r0, 0xc(r27)
	lwz r3, wp(r13)
	mulli r0, r0, 0xc
	lwz r3, 0x8(r3)
	add r26, r3, r0
	lwz r3, 0x4(r26)
	subi r0, r3, 0x1
	stw r0, 0x4(r26)
	lwz r0, 0x4(r26)
	cmpwi r0, 0x0
	bgt L_g5_6
	lwz r3, 0x8(r26)
	bl fileFree
	li r0, 0x0
	stw r0, 0x0(r26)
	L_g5_6:
	lwz r3, 0x8(r27)
	bl fileFree
	L_g5_5:
	li r0, 0x0
	stw r0, 0x0(r30)
	b L_g5_3
	L_g5_4:
	rlwinm. r0, r3, 0, 25, 25
	beq L_g5_7
	lwz r3, 0x15c(r30)
	bl smartFree
	L_g5_7:
	lwz r0, 0x0(r30)
	rlwinm. r0, r0, 0, 24, 24
	beq L_g5_8
	lwz r3, 0x164(r30)
	bl smartFree
	L_g5_8:
	lwz r3, wp(r13)
	lwz r0, 0x10(r30)
	lwz r3, 0x0(r3)
	slwi r0, r0, 4
	add r26, r3, r0
	lwz r3, 0x4(r26)
	subi r0, r3, 0x1
	stw r0, 0x4(r26)
	lwz r0, 0x4(r26)
	cmpwi r0, 0x0
	bgt L_g5_9
	li r0, 0x0
	stw r0, 0x0(r26)
	lwz r0, 0xc(r26)
	lwz r3, wp(r13)
	mulli r0, r0, 0xc
	lwz r3, 0x8(r3)
	add r27, r3, r0
	lwz r3, 0x4(r27)
	subi r0, r3, 0x1
	stw r0, 0x4(r27)
	lwz r0, 0x4(r27)
	cmpwi r0, 0x0
	bgt L_g5_10
	lwz r3, 0x8(r27)
	bl fileFree
	li r0, 0x0
	stw r0, 0x0(r27)
	L_g5_10:
	lwz r3, 0x8(r26)
	bl fileFree
	L_g5_9:
	li r0, 0x0
	stw r0, 0x0(r30)
	L_g5_3:
	addi r31, r31, 0x170
	addi r29, r29, 0x1
	L_g5_1:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r29, r0
	blt L_g5_2
	cmpwi r28, 0x1
	bne L_g5_11
	li r0, 0x0
	stw r0, 0x10c(r3)
	L_g5_11:
	bl animPoseRefresh
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animPaperPoseRelease(s32 poseId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	mulli r0, r3, 0x170
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r4, wp(r13)
	lwz r3, 0x10(r4)
	add r31, r3, r0
	lwz r3, 0x8(r31)
	subi r0, r3, 0x1
	stw r0, 0x8(r31)
	lwz r0, 0x8(r31)
	cmpwi r0, 0x0
	bge L_g5_1
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r3, 0x0(r3)
	slwi r0, r0, 4
	add r29, r3, r0
	lwz r3, 0x4(r29)
	subi r0, r3, 0x1
	stw r0, 0x4(r29)
	lwz r0, 0x4(r29)
	cmpwi r0, 0x0
	bgt L_g5_2
	li r0, 0x0
	stw r0, 0x0(r29)
	lwz r0, 0xc(r29)
	lwz r3, wp(r13)
	mulli r0, r0, 0xc
	lwz r3, 0x8(r3)
	add r30, r3, r0
	lwz r3, 0x4(r30)
	subi r0, r3, 0x1
	stw r0, 0x4(r30)
	lwz r0, 0x4(r30)
	cmpwi r0, 0x0
	bgt L_g5_3
	lwz r3, 0x8(r30)
	bl fileFree
	li r0, 0x0
	stw r0, 0x0(r30)
	L_g5_3:
	lwz r3, 0x8(r29)
	bl fileFree
	L_g5_2:
	li r0, 0x0
	stw r0, 0x0(r31)
	L_g5_1:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animPoseRelease(s32 poseId) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	mulli r0, r3, 0x170
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r4, wp(r13)
	lwz r3, 0x10(r4)
	add r31, r3, r0
	lwz r0, 0x4(r31)
	cmplwi r0, 0x0
	beq L_g5_1
	lwz r3, 0x8(r31)
	subi r0, r3, 0x1
	stw r0, 0x8(r31)
	lwz r0, 0x8(r31)
	cmpwi r0, 0x0
	bge L_g5_2
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r3, 0x0(r3)
	slwi r0, r0, 4
	add r30, r3, r0
	lwz r3, 0x4(r30)
	subi r0, r3, 0x1
	stw r0, 0x4(r30)
	lwz r0, 0x4(r30)
	cmpwi r0, 0x0
	bgt L_g5_3
	li r0, 0x0
	stw r0, 0x0(r30)
	lwz r0, 0xc(r30)
	lwz r3, wp(r13)
	mulli r0, r0, 0xc
	lwz r3, 0x8(r3)
	add r29, r3, r0
	lwz r3, 0x4(r29)
	subi r0, r3, 0x1
	stw r0, 0x4(r29)
	lwz r0, 0x4(r29)
	cmpwi r0, 0x0
	bgt L_g5_4
	lwz r3, 0x8(r29)
	bl fileFree
	li r0, 0x0
	stw r0, 0x0(r29)
	L_g5_4:
	lwz r3, 0x8(r30)
	bl fileFree
	L_g5_3:
	li r0, 0x0
	stw r0, 0x0(r31)
	b L_g5_2
	L_g5_1:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 25, 25
	beq L_g5_5
	lwz r3, 0x15c(r31)
	bl smartFree
	L_g5_5:
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 24, 24
	beq L_g5_6
	lwz r3, 0x164(r31)
	bl smartFree
	L_g5_6:
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r3, 0x0(r3)
	slwi r0, r0, 4
	add r29, r3, r0
	lwz r3, 0x4(r29)
	subi r0, r3, 0x1
	stw r0, 0x4(r29)
	lwz r0, 0x4(r29)
	cmpwi r0, 0x0
	bgt L_g5_7
	li r0, 0x0
	stw r0, 0x0(r29)
	lwz r0, 0xc(r29)
	lwz r3, wp(r13)
	mulli r0, r0, 0xc
	lwz r3, 0x8(r3)
	add r30, r3, r0
	lwz r3, 0x4(r30)
	subi r0, r3, 0x1
	stw r0, 0x4(r30)
	lwz r0, 0x4(r30)
	cmpwi r0, 0x0
	bgt L_g5_8
	lwz r3, 0x8(r30)
	bl fileFree
	li r0, 0x0
	stw r0, 0x0(r30)
	L_g5_8:
	lwz r3, 0x8(r29)
	bl fileFree
	L_g5_7:
	li r0, 0x0
	stw r0, 0x0(r31)
	L_g5_2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animSetPaperTexObj(GXTexObj* obj1, GXTexObj* obj2, GXTexObj* obj3, void* data1, void* data2, void* data3, s32 a7, s32 a8) {
	nofralloc
	cmplwi r6, 0x0
	beq L_g5_1
	b L_g5_2
	L_g5_1:
	li r3, 0x0
	L_g5_2:
	lwz r10, wp(r13)
	cmplwi r7, 0x0
	stw r3, 0x30(r10)
	beq L_g5_3
	b L_g5_4
	L_g5_3:
	li r4, 0x0
	L_g5_4:
	lwz r3, wp(r13)
	cmplwi r8, 0x0
	stw r4, 0x34(r3)
	beq L_g5_5
	b L_g5_6
	L_g5_5:
	li r5, 0x0
	L_g5_6:
	lwz r3, wp(r13)
	stw r5, 0x38(r3)
	lwz r3, wp(r13)
	stw r6, 0x24(r3)
	lwz r3, wp(r13)
	stw r7, 0x28(r3)
	lwz r3, wp(r13)
	stw r8, 0x2c(r3)
	lwz r3, wp(r13)
	stw r9, 0xd8(r3)
	lwz r3, wp(r13)
	stw r9, 0xdc(r3)
	blr
}

asm void animPoseDrawMtx(s32 poseId, Mtx matrix, s32 xluMode, f32 rotY, f32 scale) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stfd f31, 0x130(r1)
	psq_st f31, 0x138(r1), 0, 0
	stfd f30, 0x120(r1)
	psq_st f30, 0x128(r1), 0, 0
	stmw r22, 0xf8(r1)
	lwz r6, wp(r13)
	mulli r0, r3, 0x170
	fmr f30, f1
	mr r27, r4
	lwz r3, 0x10(r6)
	fmr f31, f2
	mr r28, r5
	add r31, r3, r0
	lwz r0, 0x90(r31)
	cmpwi r0, -0x1
	beq L_g5_1
	lwz r4, 0x0(r31)
	rlwinm. r0, r4, 0, 24, 25
	beq L_g5_2
	rlwinm. r0, r4, 0, 28, 28
	lwz r3, 0x10(r31)
	lwz r4, 0x0(r6)
	mr r29, r27
	slwi r0, r3, 4
	add r3, r4, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r26, 0x0(r3)
	bne L_g5_3
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f30, f0
	beq L_g5_3
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x38
	li r4, 0x79
	fmuls f1, f0, f30
	bl PSMTXRotRad
	mr r3, r27
	addi r4, r1, 0x38
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r29, r1, 0x8
	L_g5_3:
	lfs f0, float_1_80419a44(r2)
	fcmpu cr0, f0, f31
	beq L_g5_4
	fmr f1, f31
	addi r3, r1, 0x68
	fmr f2, f31
	fmr f3, f31
	bl PSMTXScale
	mr r3, r29
	addi r4, r1, 0x68
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r29, r1, 0x8
	L_g5_4:
	lis r3, g_modeling_mtx_stack@ha
	li r0, 0x0
	addi r4, r3, g_modeling_mtx_stack@l
	stw r0, g_modeling_mtx_lv(r13)
	mr r3, r29
	stw r4, g_modeling_mtx(r13)
	bl PSMTXCopy
	lwz r4, wp(r13)
	li r3, -0x1
	stw r31, 0x18(r4)
	lwz r4, wp(r13)
	stw r26, 0x20(r4)
	lwz r4, 0x144(r26)
	subi r4, r4, 0x1
	bl evalProc
	L_g5_2:
	lwz r0, 0x90(r31)
	cmpwi r28, 0x2
	lwz r3, wp(r13)
	mulli r0, r0, 0x170
	lwz r5, 0x10(r3)
	lwz r4, 0x0(r3)
	add r30, r5, r0
	lwz r0, 0x10(r30)
	slwi r0, r0, 4
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r5, 0x0(r4)
	bne L_g5_5
	lwz r0, 0xc4(r5)
	clrlwi. r0, r0, 31
	bne L_g5_6
	L_g5_5:
	li r0, 0x1
	lwz r4, 0xc4(r5)
	slw r0, r0, r28
	and. r0, r4, r0
	beq L_g5_7
	L_g5_6:
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	beq L_g5_8
	lwz r6, 0xf0(r5)
	lwz r5, 0xf8(r5)
	lwz r7, 0xf0(r3)
	add r4, r6, r5
	cmpw r4, r7
	bgt L_g5_9
	lwz r0, 0xf4(r3)
	add r0, r0, r4
	cmpw r0, r7
	ble L_g5_10
	li r0, 0x0
	stw r0, 0xf4(r3)
	L_g5_10:
	lwz r3, wp(r13)
	li r0, 0x1
	stw r0, 0xe8(r3)
	lwz r4, wp(r13)
	lwz r0, 0xf4(r4)
	lwz r3, 0xec(r4)
	mulli r0, r0, 0xc
	add r0, r3, r0
	stw r0, 0xf8(r4)
	lwz r3, wp(r13)
	lwz r0, 0xf4(r3)
	add r0, r0, r6
	stw r0, 0xf4(r3)
	lwz r4, wp(r13)
	lwz r0, 0xf4(r4)
	lwz r3, 0xec(r4)
	mulli r0, r0, 0xc
	add r0, r3, r0
	stw r0, 0xfc(r4)
	lwz r3, wp(r13)
	lwz r0, 0xf4(r3)
	add r0, r0, r5
	stw r0, 0xf4(r3)
	L_g5_9:
	lwz r26, 0x94(r31)
	cmpwi r26, -0x1
	beq L_g5_11
	lwz r0, 0x90(r31)
	cmpwi r26, 0x0
	lwz r3, wp(r13)
	mulli r0, r0, 0x170
	lwz r4, 0x10(r3)
	lwz r3, 0x0(r3)
	add r29, r4, r0
	lwz r0, 0x10(r29)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r23, 0x0(r3)
	lwz r25, 0x148(r23)
	bge L_g5_12
	li r24, 0x0
	mr r22, r24
	b L_g5_13
	L_g5_14:
	lwz r0, 0x1ac(r23)
	mr r4, r26
	add r3, r0, r22
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_15
	b L_g5_16
	L_g5_15:
	addi r22, r22, 0x40
	addi r24, r24, 0x1
	L_g5_13:
	cmpw r24, r25
	blt L_g5_14
	b L_g5_17
	L_g5_12:
	cmpw r26, r25
	bge L_g5_17
	mr r24, r26
	b L_g5_16
	L_g5_17:
	li r24, 0x0
	L_g5_16:
	lwz r0, 0x14(r29)
	cmpw r24, r0
	beq L_g5_11
	stw r24, 0x14(r29)
	lwz r0, 0x90(r29)
	cmpwi r0, -0x1
	beq L_g5_18
	lwz r3, 0x0(r29)
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_18
	ori r0, r3, 0x4
	stw r0, 0x0(r29)
	L_g5_18:
	lwz r0, 0xc(r29)
	cmpwi r0, 0x0
	bne L_g5_19
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_20
	L_g5_19:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_20:
	stw r4, 0x1c(r29)
	li r4, -0x1
	lfs f0, float_0_80419a48(r2)
	li r0, 0x0
	stw r3, 0x18(r29)
	stw r4, 0x3c(r29)
	stfs f0, 0x40(r29)
	stw r0, 0x80(r29)
	stfs f0, 0x84(r29)
	L_g5_11:
	lwz r0, 0xc(r30)
	cmpwi r0, 0x0
	bne L_g5_21
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_22
	L_g5_21:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_22:
	stw r4, 0x1c(r30)
	li r4, -0x1
	lfs f0, float_0_80419a48(r2)
	li r0, 0x0
	stw r3, 0x18(r30)
	stw r4, 0x3c(r30)
	stfs f0, 0x40(r30)
	stw r0, 0x80(r30)
	stfs f0, 0x84(r30)
	lwz r0, 0x88(r31)
	lwz r3, 0x8c(r31)
	stw r3, 0x1c(r30)
	stw r0, 0x18(r30)
	lwz r3, 0x90(r31)
	bl animPoseMain
	L_g5_8:
	lwz r6, 0x98(r31)
	lwz r7, 0x9c(r31)
	cmplwi r6, 0x0
	beq L_g5_23
	addi r0, r31, 0xa0
	b L_g5_24
	L_g5_23:
	li r0, 0x0
	L_g5_24:
	lwz r3, wp(r13)
	cmplwi r7, 0x0
	stw r0, 0x30(r3)
	beq L_g5_25
	addi r5, r31, 0xc0
	b L_g5_26
	L_g5_25:
	li r5, 0x0
	L_g5_26:
	lwz r3, wp(r13)
	li r4, 0x0
	li r0, 0x1
	stw r5, 0x34(r3)
	lwz r3, wp(r13)
	stw r4, 0x38(r3)
	lwz r3, wp(r13)
	stw r6, 0x24(r3)
	lwz r3, wp(r13)
	stw r7, 0x28(r3)
	lwz r3, wp(r13)
	stw r4, 0x2c(r3)
	lwz r3, wp(r13)
	stw r0, 0xd8(r3)
	lwz r3, wp(r13)
	stw r0, 0xdc(r3)
	lwz r0, 0xe8(r31)
	stw r0, 0xe8(r30)
	lwz r0, 0xec(r31)
	stw r0, 0xec(r30)
	lwz r0, 0xf0(r31)
	stw r0, 0xf0(r30)
	lwz r0, 0xf4(r31)
	stw r0, 0xf4(r30)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 30, 30
	beq L_g5_27
	lfs f1, 0x10c(r31)
	addi r3, r1, 0xc8
	lfs f2, 0x110(r31)
	lfs f3, float_1_80419a44(r2)
	bl PSMTXScale
	lfs f1, 0x104(r31)
	addi r3, r1, 0x98
	lfs f2, 0x108(r31)
	lfs f3, float_0_80419a48(r2)
	bl PSMTXTrans
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addic. r0, r1, 0xc8
	bne L_g5_28
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xcc(r3)
	b L_g5_29
	L_g5_28:
	lwz r4, wp(r13)
	addi r3, r1, 0xc8
	addi r4, r4, 0x3c
	bl PSMTXCopy
	lwz r3, wp(r13)
	addi r0, r3, 0x3c
	stw r0, 0xcc(r3)
	L_g5_29:
	lwz r4, wp(r13)
	li r0, 0x0
	addi r3, r1, 0xc8
	stw r0, 0xd0(r4)
	lwz r4, wp(r13)
	stw r0, 0xd4(r4)
	lfs f1, 0xf8(r31)
	lfs f2, 0xfc(r31)
	fmr f3, f1
	bl PSMTXScale
	lwz r3, wp(r13)
	lwz r0, 0x10c(r3)
	cmpwi r0, 0x0
	beq L_g5_30
	lfs f1, float_0_80419a48(r2)
	addi r3, r1, 0x98
	lfs f2, float_2_80419a84(r2)
	lfs f0, 0x100(r31)
	fmr f3, f1
	fmuls f2, f2, f0
	bl PSMTXTrans
	b L_g5_31
	L_g5_30:
	lfs f1, float_0_80419a48(r2)
	addi r3, r1, 0x98
	lfs f2, 0x100(r31)
	fmr f3, f1
	bl PSMTXTrans
	L_g5_31:
	addi r4, r1, 0xc8
	addi r3, r1, 0x98
	mr r5, r4
	bl PSMTXConcat
	mr r3, r27
	addi r4, r1, 0xc8
	la r5, g5_mtx_s1454(r13)
	bl PSMTXConcat
	la r27, g5_mtx_s1454(r13)
	b L_g5_32
	L_g5_27:
	lfs f1, 0x10c(r31)
	addi r3, r1, 0xc8
	lfs f2, 0x110(r31)
	lfs f3, float_1_80419a44(r2)
	bl PSMTXScale
	lfs f1, 0x104(r31)
	addi r3, r1, 0x98
	lfs f2, 0x108(r31)
	lfs f3, float_0_80419a48(r2)
	bl PSMTXTrans
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	lfs f1, float_0p5_80419a64(r2)
	addi r3, r1, 0x98
	lfs f2, float_1_80419a44(r2)
	lfs f3, float_0_80419a48(r2)
	bl PSMTXTrans
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	lfs f3, float_1_80419a44(r2)
	addi r3, r1, 0x98
	lfs f1, 0xf8(r31)
	lfs f0, 0xfc(r31)
	fdivs f1, f3, f1
	fdivs f2, f3, f0
	bl PSMTXScale
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	lfs f1, float_neg0p5_80419a88(r2)
	addi r3, r1, 0x98
	lfs f2, float_neg1_80419a8c(r2)
	lfs f3, float_0_80419a48(r2)
	bl PSMTXTrans
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	mr r5, r3
	bl PSMTXConcat
	addic. r0, r1, 0xc8
	bne L_g5_33
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xcc(r3)
	b L_g5_34
	L_g5_33:
	lwz r4, wp(r13)
	addi r3, r1, 0xc8
	addi r4, r4, 0x3c
	bl PSMTXCopy
	lwz r3, wp(r13)
	addi r0, r3, 0x3c
	stw r0, 0xcc(r3)
	L_g5_34:
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xd0(r3)
	lwz r3, wp(r13)
	stw r0, 0xd4(r3)
	b L_g5_32
	L_g5_1:
	lwz r0, 0x10(r31)
	cmpwi r28, 0x2
	lwz r3, 0x0(r6)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bne L_g5_35
	lwz r0, 0xc4(r3)
	clrlwi. r0, r0, 31
	bne L_g5_32
	L_g5_35:
	li r0, 0x1
	lwz r3, 0xc4(r3)
	slw r0, r0, r28
	and. r0, r3, r0
	beq L_g5_7
	L_g5_32:
	lwz r0, 0x90(r31)
	cmpwi r0, -0x1
	beq L_g5_36
	fmr f1, f30
	mr r3, r30
	fmr f2, f31
	mr r4, r27
	mr r5, r28
	bl _animPoseDrawMtx
	lwz r3, wp(r13)
	li r4, 0x0
	stw r4, 0xcc(r3)
	lwz r3, wp(r13)
	stw r4, 0xd0(r3)
	lwz r3, wp(r13)
	stw r4, 0xd4(r3)
	lwz r0, 0x4(r30)
	rlwinm. r0, r0, 0, 30, 30
	beq L_g5_7
	lwz r3, wp(r13)
	stw r4, 0xe8(r3)
	b L_g5_7
	L_g5_36:
	fmr f1, f30
	mr r3, r31
	fmr f2, f31
	mr r4, r27
	mr r5, r28
	bl _animPoseDrawMtx
	L_g5_7:
	psq_l f31, 0x138(r1), 0, 0
	lfd f31, 0x130(r1)
	psq_l f30, 0x128(r1), 0, 0
	lfd f30, 0x120(r1)
	lmw r22, 0xf8(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm void _animPoseDrawMtx(AnimationPose* pose, Mtx matrix, s32 xluMode, f32 rotY, f32 scale) {
	nofralloc
	stwu r1, -0x120(r1)
	mflr r0
	stw r0, 0x124(r1)
	stfd f31, 0x110(r1)
	psq_st f31, 0x118(r1), 0, 0
	stfd f30, 0x100(r1)
	psq_st f30, 0x108(r1), 0, 0
	stfd f29, 0xf0(r1)
	psq_st f29, 0xf8(r1), 0, 0
	stmw r25, 0xd4(r1)
	lwz r7, wp(r13)
	mr r26, r3
	lwz r0, 0x10(r3)
	fmr f29, f1
	lwz r6, 0x0(r7)
	fmr f30, f2
	slwi r3, r0, 4
	lwz r0, 0x14(r26)
	add r3, r6, r3
	lwz r3, 0x8(r3)
	slwi r0, r0, 6
	lwz r29, 0x28(r26)
	mr r27, r4
	lwz r3, 0xa0(r3)
	lwz r28, 0x2c(r26)
	lwz r31, 0x0(r3)
	lfs f31, 0x30(r26)
	lwz r3, 0x1ac(r31)
	add r3, r3, r0
	lwz r30, 0x3c(r3)
	cmplwi r30, 0x0
	beq L_g5_1
	lwz r3, 0x10c(r7)
	cmpwi r3, 0x0
	beq L_g5_2
	lwz r0, 0xc(r26)
	cmpwi r0, 0x0
	beq L_g5_1
	L_g5_2:
	cmpwi r3, 0x0
	bne L_g5_3
	lwz r0, 0xc(r26)
	cmpwi r0, 0x1
	beq L_g5_1
	L_g5_3:
	cmpwi r5, 0x2
	bne L_g5_4
	lwz r0, 0xc4(r31)
	clrlwi. r0, r0, 31
	bne L_g5_5
	L_g5_4:
	li r0, 0x1
	lwz r3, 0xc4(r31)
	slw r0, r0, r5
	and. r0, r3, r0
	beq L_g5_1
	L_g5_5:
	lwz r0, 0xf4(r26)
	mr r25, r5
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	stw r0, 0x8(r1)
	lwz r0, 0xf0(r26)
	stw r0, 0xc(r1)
	lwz r3, 0xe8(r26)
	bl mapTestXLU
	cmpwi r3, 0x0
	beq L_g5_6
	li r25, 0x3
	L_g5_6:
	lwz r12, 0xe0(r26)
	cmplwi r12, 0x0
	beq L_g5_7
	mr r3, r25
	mtctr r12
	bctrl
	b L_g5_8
	L_g5_7:
	cmpwi r25, 0x2
	beq L_g5_9
	bge L_g5_10
	cmpwi r25, 0x0
	beq L_g5_9
	bge L_g5_11
	b L_g5_12
	L_g5_10:
	cmpwi r25, 0x4
	bge L_g5_12
	b L_g5_13
	L_g5_11:
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	b L_g5_12
	L_g5_9:
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	b L_g5_12
	L_g5_13:
	li r3, 0x1
	li r4, 0x3
	li r5, 0x0
	bl GXSetZMode
	li r3, 0x1
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x1
	bl GXSetZCompLoc
	li r3, 0x7
	li r4, 0x0
	li r5, 0x0
	li r6, 0x7
	li r7, 0x0
	bl GXSetAlphaCompare
	L_g5_12:
	lwz r3, wp(r13)
	stw r25, 0xe0(r3)
	L_g5_8:
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_14
	lfs f0, float_neg90_80419a90(r2)
	li r3, 0x4
	fadds f29, f29, f0
	stfs f29, 0x70(r26)
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f3, f1
	lfs f2, float_rad2deg_80419a94(r2)
	lfs f1, float_360_80419a98(r2)
	lfs f0, float_neg360_80419a9c(r2)
	fmuls f2, f2, f3
	b L_g5_15
	L_g5_16:
	fadds f2, f2, f1
	L_g5_15:
	fcmpo cr0, f2, f0
	blt L_g5_16
	lfs f1, float_360_80419a98(r2)
	b L_g5_17
	L_g5_18:
	fsubs f2, f2, f1
	L_g5_17:
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	beq L_g5_18
	lfs f0, float_0_80419a48(r2)
	fcmpo cr0, f2, f0
	bge L_g5_19
	fadds f2, f2, f1
	L_g5_19:
	lfs f0, 0x70(r26)
	lfs f1, float_360_80419a98(r2)
	fsubs f2, f2, f0
	lfs f0, float_neg360_80419a9c(r2)
	b L_g5_20
	L_g5_21:
	fadds f2, f2, f1
	L_g5_20:
	fcmpo cr0, f2, f0
	blt L_g5_21
	lfs f0, float_360_80419a98(r2)
	b L_g5_22
	L_g5_23:
	fsubs f2, f2, f0
	L_g5_22:
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	beq L_g5_23
	lfs f0, float_90_80419aa0(r2)
	fcmpo cr0, f2, f0
	ble L_g5_24
	lfs f0, float_270_80419aa4(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_g5_25
	L_g5_24:
	lfs f0, float_neg90_80419a90(r2)
	fcmpo cr0, f2, f0
	bge L_g5_26
	lfs f0, float_neg270_80419aa8(r2)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne L_g5_26
	L_g5_25:
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f3, f1
	lfs f2, float_rad2deg_80419a94(r2)
	lfs f1, float_360_80419a98(r2)
	lfs f0, float_neg360_80419a9c(r2)
	fmuls f2, f2, f3
	b L_g5_27
	L_g5_28:
	fadds f2, f2, f1
	L_g5_27:
	fcmpo cr0, f2, f0
	blt L_g5_28
	lfs f1, float_360_80419a98(r2)
	b L_g5_29
	L_g5_30:
	fsubs f2, f2, f1
	L_g5_29:
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	beq L_g5_30
	lfs f0, float_0_80419a48(r2)
	fcmpo cr0, f2, f0
	bge L_g5_31
	fadds f2, f2, f1
	L_g5_31:
	lfs f0, float_180_80419aac(r2)
	lfs f1, float_360_80419a98(r2)
	fadds f2, f0, f2
	lfs f0, float_neg360_80419a9c(r2)
	b L_g5_32
	L_g5_33:
	fadds f2, f2, f1
	L_g5_32:
	fcmpo cr0, f2, f0
	blt L_g5_33
	lfs f0, float_360_80419a98(r2)
	b L_g5_34
	L_g5_35:
	fsubs f2, f2, f0
	L_g5_34:
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	beq L_g5_35
	stfs f2, 0x7c(r26)
	b L_g5_36
	L_g5_26:
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f3, f1
	lfs f2, float_rad2deg_80419a94(r2)
	lfs f1, float_360_80419a98(r2)
	lfs f0, float_neg360_80419a9c(r2)
	fmuls f2, f2, f3
	b L_g5_37
	L_g5_38:
	fadds f2, f2, f1
	L_g5_37:
	fcmpo cr0, f2, f0
	blt L_g5_38
	lfs f1, float_360_80419a98(r2)
	b L_g5_39
	L_g5_40:
	fsubs f2, f2, f1
	L_g5_39:
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	beq L_g5_40
	lfs f0, float_0_80419a48(r2)
	fcmpo cr0, f2, f0
	bge L_g5_41
	fadds f2, f2, f1
	L_g5_41:
	stfs f2, 0x7c(r26)
	L_g5_36:
	lfs f3, float_360_80419a98(r2)
	lfs f0, float_180_80419aac(r2)
	b L_g5_42
	L_g5_43:
	lfs f1, 0x74(r26)
	fadds f1, f1, f3
	stfs f1, 0x74(r26)
	L_g5_42:
	lfs f2, 0x7c(r26)
	lfs f1, 0x74(r26)
	fsubs f1, f2, f1
	fcmpo cr0, f1, f0
	bgt L_g5_43
	lfs f2, float_360_80419a98(r2)
	lfs f0, float_neg180_80419ab0(r2)
	b L_g5_44
	L_g5_45:
	lfs f1, 0x74(r26)
	fsubs f1, f1, f2
	stfs f1, 0x74(r26)
	L_g5_44:
	lfs f3, 0x7c(r26)
	lfs f1, 0x74(r26)
	fsubs f4, f3, f1
	fcmpo cr0, f4, f0
	blt L_g5_45
	lwz r0, 0x0(r26)
	rlwinm. r0, r0, 0, 23, 23
	beq L_g5_46
	stfs f3, 0x74(r26)
	b L_g5_47
	L_g5_46:
	lfs f0, float_0p1_80419ab4(r2)
	fmadds f0, f0, f4, f1
	stfs f0, 0x74(r26)
	L_g5_47:
	lfs f29, 0x74(r26)
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f0, f29
	beq L_g5_48
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x70
	li r4, 0x79
	fmuls f1, f0, f29
	bl PSMTXRotRad
	mr r3, r27
	addi r4, r1, 0x70
	addi r5, r1, 0xa0
	bl PSMTXConcat
	addi r27, r1, 0xa0
	L_g5_48:
	lfs f3, float_neg1_80419a8c(r2)
	lfs f0, 0x78(r26)
	fcmpu cr0, f3, f0
	bne L_g5_49
	lfs f1, float_1_80419a44(r2)
	addi r3, r1, 0x70
	fmr f2, f1
	bl PSMTXScale
	mr r3, r27
	addi r4, r1, 0x70
	addi r5, r1, 0xa0
	bl PSMTXConcat
	addi r27, r1, 0xa0
	b L_g5_49
	L_g5_14:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f29, f0
	beq L_g5_49
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x40
	li r4, 0x79
	fmuls f1, f0, f29
	bl PSMTXRotRad
	mr r3, r27
	addi r4, r1, 0x40
	addi r5, r1, 0xa0
	bl PSMTXConcat
	addi r27, r1, 0xa0
	L_g5_49:
	lfs f0, float_1_80419a44(r2)
	fcmpu cr0, f0, f30
	beq L_g5_50
	fmr f1, f30
	addi r3, r1, 0x10
	fmr f2, f30
	fmr f3, f30
	bl PSMTXScale
	mr r3, r27
	addi r4, r1, 0x10
	addi r5, r1, 0xa0
	bl PSMTXConcat
	addi r27, r1, 0xa0
	L_g5_50:
	lwz r0, 0x3c(r26)
	cmpwi r0, -0x1
	bne L_g5_51
	lwz r7, wp(r13)
	lis r3, 0xb216
	addi r4, r3, 0x42c9
	lwz r0, 0x4(r26)
	lwz r3, 0x10(r7)
	rlwinm. r0, r0, 0, 30, 30
	subf r3, r3, r26
	mulhwu r3, r4, r3
	srwi r3, r3, 8
	beq L_g5_52
	lwz r0, 0x10(r26)
	lwz r4, 0x0(r7)
	slwi r0, r0, 4
	lwz r8, 0xf0(r7)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r6, 0xf0(r4)
	lwz r5, 0xf8(r4)
	add r4, r6, r5
	cmpw r4, r8
	bgt L_g5_53
	lwz r0, 0xf4(r7)
	add r0, r0, r4
	cmpw r0, r8
	ble L_g5_54
	li r0, 0x0
	stw r0, 0xf4(r7)
	L_g5_54:
	lwz r4, wp(r13)
	li r0, 0x1
	stw r0, 0xe8(r4)
	lwz r7, wp(r13)
	lwz r0, 0xf4(r7)
	lwz r4, 0xec(r7)
	mulli r0, r0, 0xc
	add r0, r4, r0
	stw r0, 0xf8(r7)
	lwz r4, wp(r13)
	lwz r0, 0xf4(r4)
	add r0, r0, r6
	stw r0, 0xf4(r4)
	lwz r6, wp(r13)
	lwz r0, 0xf4(r6)
	lwz r4, 0xec(r6)
	mulli r0, r0, 0xc
	add r0, r4, r0
	stw r0, 0xfc(r6)
	lwz r4, wp(r13)
	lwz r0, 0xf4(r4)
	add r0, r0, r5
	stw r0, 0xf4(r4)
	L_g5_53:
	bl animPoseMain
	lwz r3, wp(r13)
	li r0, 0x0
	stw r0, 0xe8(r3)
	b L_g5_51
	L_g5_52:
	bl animPoseMain
	L_g5_51:
	lis r3, g_modeling_mtx_stack@ha
	li r0, 0x0
	addi r4, r3, g_modeling_mtx_stack@l
	stw r0, g_modeling_mtx_lv(r13)
	mr r3, r27
	stw r4, g_modeling_mtx(r13)
	bl PSMTXCopy
	lwz r3, wp(r13)
	stw r26, 0x18(r3)
	lwz r3, wp(r13)
	stw r30, 0x1c(r3)
	lwz r3, wp(r13)
	stw r31, 0x20(r3)
	lwz r3, wp(r13)
	lwz r0, 0xe8(r3)
	cmpwi r0, 0x0
	beq L_g5_55
	lwz r0, 0x10(r26)
	lwz r4, 0x0(r3)
	slwi r0, r0, 4
	lwz r3, 0xf8(r3)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf0(r4)
	mulli r4, r0, 0xc
	bl DCFlushRange
	lwz r3, wp(r13)
	lwz r0, 0x10(r26)
	lwz r4, 0x0(r3)
	slwi r0, r0, 4
	lwz r3, 0xfc(r3)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf8(r4)
	mulli r4, r0, 0xc
	bl DCFlushRange
	b L_g5_56
	L_g5_55:
	lwz r0, 0x10(r26)
	lwz r4, 0x0(r3)
	slwi r0, r0, 4
	lwz r3, 0x4c(r26)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf0(r4)
	mulli r4, r0, 0xc
	bl DCFlushRange
	lwz r3, wp(r13)
	lwz r0, 0x10(r26)
	lwz r4, 0x0(r3)
	slwi r0, r0, 4
	lwz r3, 0x54(r26)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf8(r4)
	mulli r4, r0, 0xc
	bl DCFlushRange
	L_g5_56:
	bl GXInvalidateVtxCache
	lwz r3, 0x144(r31)
	fmr f1, f31
	mr r5, r29
	mr r6, r28
	subi r4, r3, 0x1
	li r3, -0x1
	bl dispProc
	L_g5_1:
	psq_l f31, 0x118(r1), 0, 0
	lfd f31, 0x110(r1)
	psq_l f30, 0x108(r1), 0, 0
	lfd f30, 0x100(r1)
	psq_l f29, 0xf8(r1), 0, 0
	lfd f29, 0xf0(r1)
	lmw r25, 0xd4(r1)
	lwz r0, 0x124(r1)
	mtlr r0
	addi r1, r1, 0x120
	blr
}

asm void animPoseDraw(s32 poseId, f32 x, f32 y, f32 z, f32 rotY, f32 scale, s32 xluMode) {
	nofralloc
	stwu r1, -0x50(r1)
	mflr r0
	stw r0, 0x54(r1)
	stfd f31, 0x48(r1)
	fmr f31, f5
	stfd f30, 0x40(r1)
	fmr f30, f4
	stw r31, 0x3c(r1)
	mr r31, r4
	stw r30, 0x38(r1)
	mr r30, r3
	addi r3, r1, 0x8
	bl PSMTXTrans
	fmr f1, f30
	mr r3, r30
	fmr f2, f31
	mr r5, r31
	addi r4, r1, 0x8
	bl animPoseDrawMtx
	lwz r0, 0x54(r1)
	lfd f31, 0x48(r1)
	lfd f30, 0x40(r1)
	lwz r31, 0x3c(r1)
	lwz r30, 0x38(r1)
	mtlr r0
	addi r1, r1, 0x50
	blr
}

asm void dispProc(s32 parentId, s32 groupId, s32 xluStage, s32 arg3, f32 arg4) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stfd f29, 0x40(r1)
	psq_st f29, 0x48(r1), 0, 0
	stmw r25, 0x24(r1)
	mr r28, r4
	fmr f31, f1
	cmpwi r28, -0x1
	mr r29, r5
	mr r30, r6
	beq L_g5_1
	lwz r5, wp(r13)
	mulli r0, r28, 0x58
	lwz r4, 0x20(r5)
	lwz r5, 0x18(r5)
	lwz r6, 0x1a8(r4)
	lwz r4, 0x5c(r5)
	add r31, r6, r0
	lwz r0, 0x4c(r31)
	lbzx r0, r4, r0
	extsb. r0, r0
	beq L_g5_2
	lwz r0, 0x54(r31)
	lwz r4, 0x50(r31)
	cmpwi r0, 0x0
	lwz r5, 0x64(r5)
	slwi r0, r4, 2
	add r4, r5, r0
	beq L_g5_3
	cmpwi r3, -0x1
	bne L_g5_4
	lfs f3, float_1_80419a44(r2)
	fmr f2, f3
	fmr f1, f3
	b L_g5_5
	L_g5_4:
	mulli r0, r3, 0x58
	add r3, r6, r0
	lwz r0, 0x54(r3)
	cmpwi r0, 0x0
	bne L_g5_6
	lfs f3, float_1_80419a44(r2)
	fmr f2, f3
	fmr f1, f3
	b L_g5_5
	L_g5_6:
	lwz r0, 0x50(r3)
	slwi r0, r0, 2
	add r3, r5, r0
	lfs f1, 0xc(r3)
	lfs f2, 0x10(r3)
	lfs f3, 0x14(r3)
	L_g5_5:
	mr r3, r4
	bl pushGXModelMtx_JointNode__
	b L_g5_7
	L_g5_3:
	mr r3, r4
	bl pushGXModelMtx_TransformNode__
	L_g5_7:
	lwz r3, wp(r13)
	lwz r4, 0x18(r3)
	lwz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 25, 25
	beq L_g5_8
	lis r3, vec3_802c2dc8@ha
	lwz r7, g_modeling_mtx(r13)
	addi r6, r3, vec3_802c2dc8@l
	lwz r3, 0x15c(r4)
	lwz r5, 0x0(r6)
	mulli r0, r28, 0xc
	lwz r4, 0x4(r6)
	stw r5, 0x8(r1)
	lfs f0, 0xc(r7)
	lwz r5, 0x8(r6)
	stfs f0, 0x8(r1)
	lwz r3, 0x0(r3)
	stw r4, 0xc(r1)
	lfs f1, 0x1c(r7)
	add r4, r3, r0
	stw r5, 0x10(r1)
	lfs f0, 0x2c(r7)
	stfs f1, 0xc(r1)
	lwz r0, 0x8(r1)
	stfs f0, 0x10(r1)
	lwz r3, 0xc(r1)
	stw r0, 0x0(r4)
	lwz r0, 0x10(r1)
	stw r3, 0x4(r4)
	stw r0, 0x8(r4)
	L_g5_8:
	lwz r3, wp(r13)
	lwz r3, 0x18(r3)
	lwz r0, 0x0(r3)
	rlwinm. r0, r0, 0, 24, 24
	beq L_g5_9
	lwz r4, 0x164(r3)
	mulli r0, r28, 0x30
	lwz r3, g_modeling_mtx(r13)
	lwz r4, 0x0(r4)
	add r4, r4, r0
	bl PSMTXCopy
	L_g5_9:
	lwz r3, wp(r13)
	lwz r5, 0x18(r3)
	lwz r0, 0x0(r5)
	rlwinm. r0, r0, 0, 26, 26
	beq L_g5_10
	lwz r3, 0x120(r5)
	lwz r0, 0x0(r3)
	cmpw r28, r0
	bne L_g5_10
	lwz r6, 0x11c(r5)
	la r3, vivihimoData(r13)
	lfs f30, float_0_80419a48(r2)
	addi r26, r5, 0x124
	slwi r4, r6, 2
	lwz r0, 0x14(r5)
	fmr f29, f30
	cmpwi r6, 0x2
	lwzx r3, r3, r4
	slwi r0, r0, 3
	lwz r27, g_modeling_mtx(r13)
	add r25, r3, r0
	beq L_g5_11
	bge L_g5_12
	cmpwi r6, 0x1
	bge L_g5_13
	b L_g5_14
	L_g5_12:
	cmpwi r6, 0x4
	bge L_g5_14
	b L_g5_15
	L_g5_13:
	lfs f30, float_neg2_80419ab8(r2)
	lfs f29, float_0p5_80419a64(r2)
	b L_g5_14
	L_g5_11:
	lfs f30, float_neg3_80419abc(r2)
	lfs f29, float_0p5_80419a64(r2)
	b L_g5_14
	L_g5_15:
	lfs f30, float_neg1_80419a8c(r2)
	lfs f29, float_0p5_80419a64(r2)
	L_g5_14:
	lwz r3, 0x48(r31)
	mr r4, r29
	bl materialProc
	fmr f3, f30
	lfs f1, 0x0(r25)
	fmr f4, f29
	lfs f2, 0x4(r25)
	mr r3, r27
	mr r4, r26
	bl vivihimo
	lwz r3, wp(r13)
	lfs f2, float_0p04_80419ac0(r2)
	lwz r3, 0x18(r3)
	lwz r0, 0x0(r3)
	rlwinm r0, r0, 0, 27, 25
	stw r0, 0x0(r3)
	lfs f0, 0x0(r27)
	lfs f1, 0x0(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x0(r26)
	lfs f0, 0x4(r27)
	lfs f1, 0x4(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x4(r26)
	lfs f0, 0x8(r27)
	lfs f1, 0x8(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x8(r26)
	lfs f0, 0x10(r27)
	lfs f1, 0x10(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x10(r26)
	lfs f0, 0x14(r27)
	lfs f1, 0x14(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x14(r26)
	lfs f0, 0x18(r27)
	lfs f1, 0x18(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x18(r26)
	lfs f0, 0x20(r27)
	lfs f1, 0x20(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x20(r26)
	lfs f0, 0x24(r27)
	lfs f1, 0x24(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x24(r26)
	lfs f0, 0x28(r27)
	lfs f1, 0x28(r26)
	fsubs f0, f0, f1
	fmadds f0, f2, f0, f1
	stfs f0, 0x28(r26)
	b L_g5_16
	L_g5_10:
	lwz r12, 0x154(r5)
	cmplwi r12, 0x0
	beq L_g5_17
	lwz r3, 0x158(r5)
	mr r4, r28
	lwz r5, g_modeling_mtx(r13)
	mtctr r12
	bctrl
	L_g5_17:
	lwz r3, 0x48(r31)
	mr r4, r29
	bl renderProc
	fmr f1, f31
	lwz r4, 0x44(r31)
	mr r3, r28
	mr r5, r29
	mr r6, r30
	bl dispProc
	L_g5_16:
	lwz r4, g_modeling_mtx_lv(r13)
	lis r3, g_modeling_mtx_stack@ha
	addi r0, r3, g_modeling_mtx_stack@l
	subi r4, r4, 0x1
	mulli r3, r4, 0x30
	stw r4, g_modeling_mtx_lv(r13)
	add r0, r0, r3
	stw r0, g_modeling_mtx(r13)
	L_g5_2:
	fmr f1, f31
	lwz r4, 0x40(r31)
	mr r3, r28
	mr r5, r29
	mr r6, r30
	bl dispProc
	L_g5_1:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	psq_l f29, 0x48(r1), 0, 0
	lfd f29, 0x40(r1)
	lmw r25, 0x24(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm void renderProc(s32 shapeId, s32 unused) {
	nofralloc
	stwu r1, -0x100(r1)
	mflr r0
	stw r0, 0x104(r1)
	stmw r14, 0xb8(r1)
	mr r14, r3
	cmpwi r14, -0x1
	beq L_g5_1
	bl camGetCurPtr
	lwz r4, g_modeling_mtx(r13)
	addi r5, r1, 0x78
	addi r3, r3, 0x11c
	bl PSMTXConcat
	addi r3, r1, 0x78
	li r4, 0x0
	bl GXLoadPosMtxImm
	addi r3, r1, 0x78
	addi r4, r1, 0x48
	bl PSMTXInvXpose
	addi r3, r1, 0x48
	li r4, 0x0
	bl GXLoadNrmMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r5, wp(r13)
	mulli r0, r14, 0xa8
	lwz r4, 0x20(r5)
	lwz r3, 0x14c(r4)
	lwz r4, 0x19c(r4)
	add r14, r3, r0
	lwz r0, 0x98(r14)
	lwz r6, 0xa0(r14)
	mulli r3, r0, 0x6c
	lwz r0, 0x9c(r14)
	cmpwi r6, 0x0
	lwz r15, 0x40(r14)
	lwz r16, 0x48(r14)
	lwz r17, 0x50(r14)
	stw r0, 0xa8(r1)
	add r28, r4, r3
	bne L_g5_2
	lwz r0, 0xe0(r5)
	cmpwi r0, 0x2
	beq L_g5_3
	L_g5_2:
	lwz r0, 0xe0(r5)
	cmpw r6, r0
	beq L_g5_3
	lwz r3, 0x18(r5)
	lbz r0, 0xf3(r3)
	cmplwi r0, 0xff
	bne L_g5_3
	lbz r0, 0xf7(r3)
	cmplwi r0, 0xff
	beq L_g5_1
	L_g5_3:
	lwz r0, 0xa4(r14)
	la r3, g5_tbl_s1109(r13)
	slwi r0, r0, 2
	lwzx r3, r3, r0
	bl GXSetCullMode
	mulli r0, r15, 0xc
	lwz r4, wp(r13)
	lwz r3, 0x58(r14)
	li r29, 0x0
	lwz r6, 0x20(r4)
	stw r0, 0xac(r1)
	slwi r0, r17, 2
	lwz r4, 0x60(r14)
	stw r0, 0xb0(r1)
	slwi r5, r3, 3
	lwz r0, 0x68(r14)
	slwi r8, r4, 3
	lwz r10, 0x18c(r6)
	slwi r7, r0, 3
	lwz r3, 0x70(r14)
	lwz r4, 0x80(r14)
	add r9, r10, r5
	slwi r6, r3, 3
	lwz r0, 0x78(r14)
	lwz r3, 0x88(r14)
	slwi r4, r4, 3
	slwi r5, r0, 3
	lwz r0, 0x90(r14)
	slwi r3, r3, 3
	add r8, r10, r8
	slwi r0, r0, 3
	add r7, r10, r7
	add r6, r10, r6
	add r5, r10, r5
	add r4, r10, r4
	add r3, r10, r3
	add r0, r10, r0
	stw r9, 0x28(r1)
	mulli r14, r16, 0xc
	stw r8, 0x2c(r1)
	stw r7, 0x30(r1)
	stw r6, 0x34(r1)
	stw r5, 0x38(r1)
	stw r4, 0x3c(r1)
	stw r3, 0x40(r1)
	stw r0, 0x44(r1)
	b L_g5_4
	L_g5_5:
	lwz r3, wp(r13)
	lwz r15, 0x0(r28)
	lwz r3, 0x18(r3)
	lwz r0, 0xe4(r3)
	cmplwi r0, 0x0
	bne L_g5_6
	lis r3, vec3_802c2dbc@ha
	addi r4, r1, 0x1c
	addi r8, r3, vec3_802c2dbc@l
	lwz r3, g_modeling_mtx(r13)
	lwz r7, 0x0(r8)
	mr r5, r4
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x1c(r1)
	stw r6, 0x20(r1)
	stw r0, 0x24(r1)
	bl PSMTXMultVec
	lwz r3, 0x1c(r1)
	addi r4, r1, 0x10
	lwz r5, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r3, 0x10(r1)
	lwz r3, wp(r13)
	stw r5, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r3, 0x18(r3)
	lwz r3, 0xec(r3)
	bl mapSetMaterialLight
	lwz r7, wp(r13)
	addi r4, r28, 0x10
	lwz r3, 0x0(r28)
	lwz r10, 0x18(r7)
	lwz r8, 0x20(r7)
	lwz r0, 0x10(r10)
	lwz r6, 0x0(r7)
	slwi r5, r0, 4
	lwz r9, 0x8(r7)
	addi r0, r5, 0xc
	lwz r5, 0x194(r8)
	lwzx r0, r6, r0
	lwz r6, 0x6c(r10)
	mulli r0, r0, 0xc
	lwz r7, 0x134(r8)
	lwz r8, 0x198(r8)
	add r9, r9, r0
	bl animSetMaterial_Texture
	lwz r6, wp(r13)
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	lwz r3, 0x18(r6)
	lwz r0, 0xf4(r3)
	stw r0, 0x8(r1)
	lwz r3, 0x18(r6)
	lwz r0, 0xf0(r3)
	stw r0, 0xc(r1)
	lwz r3, 0x18(r6)
	lwz r3, 0xe8(r3)
	bl mapSetMaterialLastStageBlend
	li r3, 0x4
	bl camGetPtr
	mr r16, r3
	bl camGetCurPtr
	cmplw r3, r16
	bne L_g5_7
	bl mapSetMaterialFog
	L_g5_7:
	lwz r5, wp(r13)
	mr r3, r15
	lwz r4, 0x8(r28)
	lwz r5, 0x18(r5)
	lwz r6, g_modeling_mtx(r13)
	lwz r5, 0xe8(r5)
	bl mapSetMaterialTev
	L_g5_6:
	lwz r3, wp(r13)
	lwz r5, 0x18(r3)
	lwz r0, 0x4(r5)
	cmplwi r0, 0x0
	beq L_g5_8
	lwz r4, 0x20(r3)
	li r15, 0x0
	lwz r23, 0xcc(r3)
	lwz r22, 0x24(r3)
	lwz r21, 0x30(r3)
	lwz r20, 0x198(r4)
	lwz r19, 0x134(r4)
	lwz r18, 0x6c(r5)
	lwz r17, 0x194(r4)
	lwz r16, 0x0(r28)
	b L_g5_9
	L_g5_10:
	subf r3, r15, r16
	subi r0, r3, 0x1
	slwi r3, r0, 2
	addi r0, r3, 0x10
	lwzx r0, r28, r0
	mulli r3, r0, 0x18
	slwi r0, r0, 3
	lwzx r0, r17, r0
	lbzx r4, r18, r3
	add. r24, r0, r4
	blt L_g5_11
	cmpw r24, r19
	blt L_g5_12
	L_g5_11:
	lis r3, str_802C2DF8@ha
	li r24, 0x0
	addi r3, r3, str_802C2DF8@l
	crclr 6
	bl printf
	L_g5_12:
	slwi r3, r24, 6
	addi r0, r3, 0x8
	lwzx r0, r20, r0
	cmpwi r0, 0x1
	bne L_g5_13
	cmplwi r21, 0x0
	beq L_g5_14
	mr r3, r21
	mr r4, r22
	bl smartTexObj
	mr r4, r15
	bl GXLoadTexObj
	cmplwi r23, 0x0
	beq L_g5_15
	mulli r4, r15, 0x3
	mr r3, r23
	li r5, 0x1
	addi r16, r4, 0x1e
	mr r4, r16
	bl GXLoadTexMtxImm
	mr r3, r15
	mr r6, r16
	addi r5, r15, 0x4
	li r4, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_14
	L_g5_15:
	mr r3, r15
	addi r5, r15, 0x4
	li r4, 0x1
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	L_g5_14:
	li r15, 0x1
	b L_g5_16
	L_g5_13:
	addi r15, r15, 0x1
	L_g5_9:
	cmpw r15, r16
	blt L_g5_10
	li r15, 0x0
	L_g5_16:
	cmpwi r15, 0x0
	mr r16, r15
	bne L_g5_17
	lwz r4, wp(r13)
	li r16, 0x0
	lwz r17, 0x0(r28)
	lwz r5, 0x20(r4)
	lwz r3, 0x18(r4)
	lwz r24, 0xd0(r4)
	lwz r23, 0x28(r4)
	lwz r22, 0x34(r4)
	lwz r21, 0x198(r5)
	lwz r20, 0x134(r5)
	lwz r19, 0x6c(r3)
	lwz r18, 0x194(r5)
	b L_g5_18
	L_g5_19:
	subf r3, r16, r17
	subi r0, r3, 0x1
	slwi r3, r0, 2
	addi r0, r3, 0x10
	lwzx r0, r28, r0
	mulli r3, r0, 0x18
	slwi r0, r0, 3
	lwzx r0, r18, r0
	lbzx r4, r19, r3
	add. r25, r0, r4
	blt L_g5_20
	cmpw r25, r20
	blt L_g5_21
	L_g5_20:
	lis r3, str_802C2DF8@ha
	li r25, 0x0
	addi r3, r3, str_802C2DF8@l
	crclr 6
	bl printf
	L_g5_21:
	slwi r3, r25, 6
	addi r0, r3, 0x8
	lwzx r0, r21, r0
	cmpwi r0, 0x2
	bne L_g5_22
	cmplwi r22, 0x0
	beq L_g5_23
	mr r3, r22
	mr r4, r23
	bl smartTexObj
	mr r4, r16
	bl GXLoadTexObj
	cmplwi r24, 0x0
	beq L_g5_24
	mulli r4, r16, 0x3
	mr r3, r24
	li r5, 0x1
	addi r17, r4, 0x1e
	mr r4, r17
	bl GXLoadTexMtxImm
	mr r3, r16
	mr r6, r17
	addi r5, r16, 0x4
	li r4, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_23
	L_g5_24:
	mr r3, r16
	addi r5, r16, 0x4
	li r4, 0x1
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	L_g5_23:
	li r0, 0x1
	b L_g5_25
	L_g5_22:
	addi r16, r16, 0x1
	L_g5_18:
	cmpw r16, r17
	blt L_g5_19
	li r0, 0x0
	L_g5_25:
	mr r16, r0
	mr r4, r0
	b L_g5_26
	L_g5_17:
	li r4, 0x0
	L_g5_26:
	cmpwi r16, 0x0
	beq L_g5_27
	cmpwi r15, 0x0
	beq L_g5_28
	lwz r3, wp(r13)
	lwz r0, 0xd8(r3)
	cmpwi r0, 0x0
	beq L_g5_29
	L_g5_28:
	cmpwi r4, 0x0
	beq L_g5_27
	lwz r3, wp(r13)
	lwz r0, 0xdc(r3)
	cmpwi r0, 0x0
	bne L_g5_27
	L_g5_29:
	lwz r0, 0x8(r28)
	cmpwi r0, 0x0
	bne L_g5_27
	li r3, 0x0
	li r4, 0x7
	li r5, 0x7
	li r6, 0x7
	li r7, 0x5
	bl GXSetTevAlphaIn
	L_g5_27:
	cmpwi r16, 0x0
	beq L_g5_8
	lwz r0, 0x8(r28)
	cmpwi r0, 0x0
	bne L_g5_8
	lwz r3, wp(r13)
	lwz r16, 0x38(r3)
	cmplwi r16, 0x0
	beq L_g5_8
	lwz r4, 0x2c(r3)
	mr r3, r16
	bl smartTexObj
	lwz r3, wp(r13)
	lwz r0, 0xe0(r3)
	cmpwi r0, 0x3
	beq L_g5_30
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	L_g5_30:
	cntlzw r0, r15
	lwz r4, wp(r13)
	rlwinm r3, r0, 29, 3, 29
	addi r0, r3, 0x30
	lwzx r3, r4, r0
	cmplwi r3, 0x0
	beq L_g5_31
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	cntlzw r0, r15
	lwz r5, wp(r13)
	rlwinm r3, r0, 29, 3, 29
	li r4, 0x1e
	addi r0, r3, 0xcc
	lwzx r3, r5, r0
	li r5, 0x1
	bl GXLoadTexMtxImm
	L_g5_31:
	mr r3, r16
	li r4, 0x1
	bl GXLoadTexObj
	li r3, 0x1
	li r4, 0x1
	li r5, 0x4
	li r6, 0x21
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwz r3, wp(r13)
	li r4, 0x21
	li r5, 0x1
	lwz r3, 0xd4(r3)
	bl GXLoadTexMtxImm
	lwz r5, wp(r13)
	li r3, 0x2
	lwz r6, g_modeling_mtx(r13)
	li r4, 0xc
	lwz r5, 0x18(r5)
	lwz r5, 0xe8(r5)
	bl mapSetMaterialTev
	L_g5_8:
	lwz r3, wp(r13)
	lwz r5, 0x18(r3)
	lwz r0, 0x0(r5)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_32
	lwz r23, 0x30(r3)
	cmplwi r23, 0x0
	beq L_g5_32
	lwz r22, 0xcc(r3)
	cmplwi r22, 0x0
	beq L_g5_32
	lwz r4, 0x20(r3)
	li r15, 0x0
	lwz r21, 0x24(r3)
	lwz r20, 0x198(r4)
	lwz r19, 0x134(r4)
	lwz r18, 0x6c(r5)
	lwz r17, 0x194(r4)
	lwz r16, 0x0(r28)
	b L_g5_33
	L_g5_34:
	subf r3, r15, r16
	subi r0, r3, 0x1
	slwi r3, r0, 2
	addi r0, r3, 0x10
	lwzx r0, r28, r0
	mulli r3, r0, 0x18
	slwi r0, r0, 3
	lwzx r0, r17, r0
	lbzx r4, r18, r3
	add. r24, r0, r4
	blt L_g5_35
	cmpw r24, r19
	blt L_g5_36
	L_g5_35:
	lis r3, str_802C2DF8@ha
	li r24, 0x0
	addi r3, r3, str_802C2DF8@l
	crclr 6
	bl printf
	L_g5_36:
	slwi r3, r24, 6
	addi r0, r3, 0x8
	lwzx r0, r20, r0
	cmpwi r0, 0x1
	bne L_g5_37
	cmplwi r23, 0x0
	beq L_g5_32
	mr r3, r23
	mr r4, r21
	bl smartTexObj
	mr r4, r15
	bl GXLoadTexObj
	cmplwi r22, 0x0
	beq L_g5_38
	mulli r4, r15, 0x3
	mr r3, r22
	li r5, 0x1
	addi r16, r4, 0x1e
	mr r4, r16
	bl GXLoadTexMtxImm
	mr r3, r15
	mr r6, r16
	addi r5, r15, 0x4
	li r4, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_32
	L_g5_38:
	mr r3, r15
	addi r5, r15, 0x4
	li r4, 0x1
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_32
	L_g5_37:
	addi r15, r15, 0x1
	L_g5_33:
	cmpw r15, r16
	blt L_g5_34
	L_g5_32:
	lwz r7, wp(r13)
	addi r26, r28, 0x30
	lwz r3, 0x38(r28)
	addi r21, r28, 0x4c
	lwz r6, 0x20(r7)
	lwz r0, 0xe8(r7)
	slwi r4, r3, 3
	lwz r5, 0x150(r6)
	cmpwi r0, 0x0
	lwz r3, 0x164(r6)
	lwz r0, 0xb0(r1)
	add r20, r5, r4
	lwz r27, 0x0(r28)
	lwz r25, 0x3c(r28)
	add r15, r3, r0
	lwz r24, 0x40(r28)
	lwz r23, 0x44(r28)
	lwz r22, 0x48(r28)
	beq L_g5_39
	lwz r3, 0xfc(r7)
	lwz r4, 0xf8(r7)
	lwz r0, 0xac(r1)
	add r17, r3, r14
	add r16, r4, r0
	b L_g5_40
	L_g5_39:
	lwz r3, 0x18(r7)
	lwz r0, 0xac(r1)
	lwz r4, 0x4c(r3)
	lwz r3, 0x54(r3)
	add r16, r4, r0
	add r17, r3, r14
	L_g5_40:
	bl GXClearVtxDesc
	li r3, 0x9
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0x9
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	mr r4, r16
	li r3, 0x9
	li r5, 0xc
	bl GXSetArray
	li r3, 0xa
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xa
	li r5, 0x0
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	mr r4, r17
	li r3, 0xa
	li r5, 0xc
	bl GXSetArray
	li r3, 0xb
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xb
	li r5, 0x1
	li r6, 0x5
	li r7, 0x0
	bl GXSetVtxAttrFmt
	mr r4, r15
	li r3, 0xb
	li r5, 0x4
	bl GXSetArray
	cmpwi r27, 0x1
	bne L_g5_41
	li r3, 0xd
	li r4, 0x3
	bl GXSetVtxDesc
	li r3, 0x0
	li r4, 0xd
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	lbz r0, 0x0(r26)
	addi r4, r1, 0x28
	li r3, 0xd
	li r5, 0x8
	extsb r0, r0
	slwi r0, r0, 2
	lwzx r4, r4, r0
	bl GXSetArray
	li r15, 0x0
	lis r30, 0xcc01
	b L_g5_42
	L_g5_43:
	lbz r0, 0x0(r26)
	li r3, 0xa0
	lwz r10, 0x0(r20)
	li r4, 0x0
	extsb r0, r0
	lwz r5, wp(r13)
	slwi r8, r0, 2
	add r9, r10, r24
	lwzx r0, r21, r8
	add r7, r10, r23
	lwz r5, 0x20(r5)
	add r6, r10, r22
	addi r8, r8, 0x16c
	add r0, r10, r0
	lwz r12, 0x4(r20)
	slwi r11, r9, 2
	slwi r10, r7, 2
	slwi r9, r6, 2
	slwi r7, r0, 2
	clrlwi r16, r12, 16
	lwz r6, 0x158(r5)
	addi r17, r11, 0x2
	lwz r0, 0x160(r5)
	addi r18, r10, 0x2
	lwz r10, 0x168(r5)
	addi r19, r9, 0x2
	lwzx r8, r5, r8
	addi r27, r7, 0x2
	mr r5, r16
	add r17, r6, r17
	add r18, r0, r18
	add r19, r10, r19
	add r27, r8, r27
	bl GXBegin
	cmpwi r16, 0x0
	mr r3, r16
	ble L_g5_44
	srwi. r0, r16, 2
	mtctr r0
	beq L_g5_45
	L_g5_46:
	lhz r0, 0x0(r17)
	sth r0, -0x8000(r30)
	lhz r0, 0x0(r18)
	sth r0, -0x8000(r30)
	lhz r0, 0x0(r19)
	sth r0, -0x8000(r30)
	lhz r0, 0x0(r27)
	sth r0, -0x8000(r30)
	lhz r0, 0x4(r17)
	sth r0, -0x8000(r30)
	lhz r0, 0x4(r18)
	sth r0, -0x8000(r30)
	lhz r0, 0x4(r19)
	sth r0, -0x8000(r30)
	lhz r0, 0x4(r27)
	sth r0, -0x8000(r30)
	lhz r0, 0x8(r17)
	sth r0, -0x8000(r30)
	lhz r0, 0x8(r18)
	sth r0, -0x8000(r30)
	lhz r0, 0x8(r19)
	sth r0, -0x8000(r30)
	lhz r0, 0x8(r27)
	sth r0, -0x8000(r30)
	lhz r0, 0xc(r17)
	addi r17, r17, 0x10
	sth r0, -0x8000(r30)
	lhz r0, 0xc(r18)
	addi r18, r18, 0x10
	sth r0, -0x8000(r30)
	lhz r0, 0xc(r19)
	addi r19, r19, 0x10
	sth r0, -0x8000(r30)
	lhz r0, 0xc(r27)
	addi r27, r27, 0x10
	sth r0, -0x8000(r30)
	bdnz L_g5_46
	andi. r3, r3, 0x3
	beq L_g5_44
	L_g5_45:
	mtctr r3
	L_g5_47:
	lhz r0, 0x0(r17)
	addi r17, r17, 0x4
	sth r0, -0x8000(r30)
	lhz r0, 0x0(r18)
	addi r18, r18, 0x4
	sth r0, -0x8000(r30)
	lhz r0, 0x0(r19)
	addi r19, r19, 0x4
	sth r0, -0x8000(r30)
	lhz r0, 0x0(r27)
	addi r27, r27, 0x4
	sth r0, -0x8000(r30)
	bdnz L_g5_47
	L_g5_44:
	addi r15, r15, 0x1
	addi r20, r20, 0x8
	L_g5_42:
	cmpw r15, r25
	blt L_g5_43
	b L_g5_48
	L_g5_41:
	addi r16, r1, 0x28
	li r15, 0x0
	b L_g5_49
	L_g5_50:
	addi r3, r15, 0xd
	li r4, 0x3
	bl GXSetVtxDesc
	addi r4, r15, 0xd
	li r3, 0x0
	li r5, 0x1
	li r6, 0x4
	li r7, 0x0
	bl GXSetVtxAttrFmt
	subf r4, r15, r27
	addi r3, r15, 0xd
	subi r0, r4, 0x1
	li r5, 0x8
	lbzx r0, r26, r0
	extsb r0, r0
	slwi r0, r0, 2
	lwzx r4, r16, r0
	bl GXSetArray
	addi r15, r15, 0x1
	L_g5_49:
	cmpw r15, r27
	blt L_g5_50
	li r30, 0x0
	lis r31, 0xcc01
	b L_g5_51
	L_g5_52:
	lwz r5, wp(r13)
	li r3, 0xa0
	lwz r19, 0x0(r20)
	li r4, 0x0
	lwz r5, 0x20(r5)
	add r7, r19, r24
	add r6, r19, r23
	add r0, r19, r22
	lwz r9, 0x4(r20)
	slwi r8, r7, 2
	slwi r7, r6, 2
	slwi r6, r0, 2
	clrlwi r18, r9, 16
	lwz r9, 0x158(r5)
	addi r17, r8, 0x2
	lwz r8, 0x160(r5)
	addi r16, r7, 0x2
	lwz r0, 0x168(r5)
	addi r15, r6, 0x2
	mr r5, r18
	add r17, r9, r17
	add r16, r8, r16
	add r15, r0, r15
	bl GXBegin
	lwz r5, wp(r13)
	li r8, 0x0
	li r6, 0x0
	b L_g5_53
	L_g5_54:
	lhz r0, 0x0(r17)
	cmpwi r27, 0x0
	mr r10, r27
	li r9, 0x0
	sth r0, -0x8000(r31)
	lhz r0, 0x0(r16)
	sth r0, -0x8000(r31)
	lhz r0, 0x0(r15)
	sth r0, -0x8000(r31)
	ble L_g5_55
	srwi. r0, r27, 2
	mtctr r0
	beq L_g5_56
	L_g5_57:
	subf r0, r9, r27
	lwz r3, 0x20(r5)
	add r4, r0, r26
	addi r9, r9, 0x1
	lbz r7, -0x1(r4)
	subf r0, r9, r27
	add r4, r0, r26
	addi r9, r9, 0x1
	extsb r7, r7
	slwi r7, r7, 2
	subf r0, r9, r27
	lwzx r11, r21, r7
	addi r7, r7, 0x16c
	lwzx r3, r3, r7
	addi r9, r9, 0x1
	add r7, r19, r11
	slwi r7, r7, 2
	add r3, r3, r7
	lwzx r3, r6, r3
	sth r3, -0x8000(r31)
	lbz r7, -0x1(r4)
	add r4, r0, r26
	subf r0, r9, r27
	lwz r3, 0x20(r5)
	extsb r7, r7
	addi r9, r9, 0x1
	slwi r7, r7, 2
	lwzx r11, r21, r7
	addi r7, r7, 0x16c
	lwzx r3, r3, r7
	add r7, r19, r11
	slwi r7, r7, 2
	add r3, r3, r7
	lwzx r3, r6, r3
	sth r3, -0x8000(r31)
	lbz r7, -0x1(r4)
	add r4, r0, r26
	lwz r3, 0x20(r5)
	extsb r7, r7
	slwi r7, r7, 2
	lwzx r11, r21, r7
	addi r7, r7, 0x16c
	lwzx r3, r3, r7
	add r7, r19, r11
	slwi r7, r7, 2
	add r3, r3, r7
	lwzx r3, r6, r3
	sth r3, -0x8000(r31)
	lbz r7, -0x1(r4)
	lwz r3, 0x20(r5)
	extsb r7, r7
	slwi r7, r7, 2
	lwzx r11, r21, r7
	addi r7, r7, 0x16c
	lwzx r3, r3, r7
	add r7, r19, r11
	slwi r7, r7, 2
	add r3, r3, r7
	lwzx r3, r6, r3
	sth r3, -0x8000(r31)
	bdnz L_g5_57
	andi. r10, r10, 0x3
	beq L_g5_55
	L_g5_56:
	mtctr r10
	L_g5_58:
	subf r0, r9, r27
	lwz r3, 0x20(r5)
	add r4, r0, r26
	addi r9, r9, 0x1
	lbz r7, -0x1(r4)
	extsb r7, r7
	slwi r7, r7, 2
	lwzx r11, r21, r7
	addi r7, r7, 0x16c
	lwzx r3, r3, r7
	add r7, r19, r11
	slwi r7, r7, 2
	add r3, r3, r7
	lwzx r3, r6, r3
	sth r3, -0x8000(r31)
	bdnz L_g5_58
	L_g5_55:
	addi r6, r6, 0x4
	addi r8, r8, 0x1
	addi r17, r17, 0x4
	addi r16, r16, 0x4
	addi r15, r15, 0x4
	L_g5_53:
	cmpw r8, r18
	blt L_g5_54
	addi r30, r30, 0x1
	addi r20, r20, 0x8
	L_g5_51:
	cmpw r30, r25
	blt L_g5_52
	L_g5_48:
	addi r29, r29, 0x1
	addi r28, r28, 0x6c
	L_g5_4:
	lwz r0, 0xa8(r1)
	cmpw r29, r0
	blt L_g5_5
	L_g5_1:
	lmw r14, 0xb8(r1)
	lwz r0, 0x104(r1)
	mtlr r0
	addi r1, r1, 0x100
	blr
}

asm void materialProc(s32 shapeId, s32 xluStage) {
	nofralloc
	stwu r1, -0xc0(r1)
	mflr r0
	stw r0, 0xc4(r1)
	stmw r18, 0x88(r1)
	mr r18, r3
	cmpwi r18, -0x1
	beq L_g5_1
	bl camGetCurPtr
	lwz r4, g_modeling_mtx(r13)
	addi r5, r1, 0x58
	addi r3, r3, 0x11c
	bl PSMTXConcat
	addi r3, r1, 0x58
	li r4, 0x0
	bl GXLoadPosMtxImm
	addi r3, r1, 0x58
	addi r4, r1, 0x28
	bl PSMTXInvXpose
	addi r3, r1, 0x28
	li r4, 0x0
	bl GXLoadNrmMtxImm
	li r3, 0x0
	bl GXSetCurrentMtx
	lwz r5, wp(r13)
	mulli r0, r18, 0xa8
	lwz r3, 0x20(r5)
	lwz r4, 0x14c(r3)
	lwz r3, 0x19c(r3)
	add r6, r4, r0
	lwz r0, 0x98(r6)
	lwz r4, 0xa0(r6)
	mulli r0, r0, 0x6c
	lwz r30, 0x9c(r6)
	cmpwi r4, 0x0
	add r29, r3, r0
	bne L_g5_2
	lwz r0, 0xe0(r5)
	cmpwi r0, 0x2
	beq L_g5_3
	L_g5_2:
	lwz r0, 0xe0(r5)
	cmpw r4, r0
	beq L_g5_3
	lwz r3, 0x18(r5)
	lbz r0, 0xf3(r3)
	cmplwi r0, 0xff
	bne L_g5_3
	lbz r0, 0xf7(r3)
	cmplwi r0, 0xff
	beq L_g5_1
	L_g5_3:
	lwz r0, 0xa4(r6)
	la r3, g5_tbl_s1109(r13)
	slwi r0, r0, 2
	lwzx r3, r3, r0
	bl GXSetCullMode
	li r31, 0x0
	b L_g5_4
	L_g5_5:
	lwz r3, wp(r13)
	lwz r19, 0x0(r29)
	lwz r3, 0x18(r3)
	lwz r0, 0xe4(r3)
	cmplwi r0, 0x0
	bne L_g5_6
	lis r3, vec3_802c2db0@ha
	addi r4, r1, 0x1c
	addi r8, r3, vec3_802c2db0@l
	lwz r3, g_modeling_mtx(r13)
	lwz r7, 0x0(r8)
	mr r5, r4
	lwz r6, 0x4(r8)
	lwz r0, 0x8(r8)
	stw r7, 0x1c(r1)
	stw r6, 0x20(r1)
	stw r0, 0x24(r1)
	bl PSMTXMultVec
	lwz r3, 0x1c(r1)
	addi r4, r1, 0x10
	lwz r5, 0x20(r1)
	lwz r0, 0x24(r1)
	stw r3, 0x10(r1)
	lwz r3, wp(r13)
	stw r5, 0x14(r1)
	stw r0, 0x18(r1)
	lwz r3, 0x18(r3)
	lwz r3, 0xec(r3)
	bl mapSetMaterialLight
	lwz r7, wp(r13)
	addi r4, r29, 0x10
	lwz r3, 0x0(r29)
	lwz r10, 0x18(r7)
	lwz r8, 0x20(r7)
	lwz r0, 0x10(r10)
	lwz r6, 0x0(r7)
	slwi r5, r0, 4
	lwz r9, 0x8(r7)
	addi r0, r5, 0xc
	lwz r5, 0x194(r8)
	lwzx r0, r6, r0
	lwz r6, 0x6c(r10)
	mulli r0, r0, 0xc
	lwz r7, 0x134(r8)
	lwz r8, 0x198(r8)
	add r9, r9, r0
	bl animSetMaterial_Texture
	lwz r6, wp(r13)
	addi r4, r1, 0xc
	addi r5, r1, 0x8
	lwz r3, 0x18(r6)
	lwz r0, 0xf4(r3)
	stw r0, 0x8(r1)
	lwz r3, 0x18(r6)
	lwz r0, 0xf0(r3)
	stw r0, 0xc(r1)
	lwz r3, 0x18(r6)
	lwz r3, 0xe8(r3)
	bl mapSetMaterialLastStageBlend
	li r3, 0x4
	bl camGetPtr
	mr r20, r3
	bl camGetCurPtr
	cmplw r3, r20
	bne L_g5_7
	bl mapSetMaterialFog
	L_g5_7:
	lwz r5, wp(r13)
	mr r3, r19
	lwz r4, 0x8(r29)
	lwz r5, 0x18(r5)
	lwz r6, g_modeling_mtx(r13)
	lwz r5, 0xe8(r5)
	bl mapSetMaterialTev
	L_g5_6:
	lwz r3, wp(r13)
	lwz r5, 0x18(r3)
	lwz r0, 0x4(r5)
	cmplwi r0, 0x0
	beq L_g5_8
	lwz r4, 0x20(r3)
	li r28, 0x0
	lwz r20, 0xcc(r3)
	lwz r21, 0x24(r3)
	lwz r22, 0x30(r3)
	lwz r23, 0x198(r4)
	lwz r24, 0x134(r4)
	lwz r25, 0x6c(r5)
	lwz r26, 0x194(r4)
	lwz r27, 0x0(r29)
	b L_g5_9
	L_g5_10:
	subf r3, r28, r27
	subi r0, r3, 0x1
	slwi r3, r0, 2
	addi r0, r3, 0x10
	lwzx r0, r29, r0
	mulli r3, r0, 0x18
	slwi r0, r0, 3
	lwzx r0, r26, r0
	lbzx r4, r25, r3
	add. r19, r0, r4
	blt L_g5_11
	cmpw r19, r24
	blt L_g5_12
	L_g5_11:
	lis r3, str_802C2DF8@ha
	li r19, 0x0
	addi r3, r3, str_802C2DF8@l
	crclr 6
	bl printf
	L_g5_12:
	slwi r3, r19, 6
	addi r0, r3, 0x8
	lwzx r0, r23, r0
	cmpwi r0, 0x1
	bne L_g5_13
	cmplwi r22, 0x0
	beq L_g5_14
	mr r3, r22
	mr r4, r21
	bl smartTexObj
	mr r4, r28
	bl GXLoadTexObj
	cmplwi r20, 0x0
	beq L_g5_15
	mulli r4, r28, 0x3
	mr r3, r20
	li r5, 0x1
	addi r18, r4, 0x1e
	mr r4, r18
	bl GXLoadTexMtxImm
	mr r3, r28
	mr r6, r18
	addi r5, r28, 0x4
	li r4, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_14
	L_g5_15:
	mr r3, r28
	addi r5, r28, 0x4
	li r4, 0x1
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	L_g5_14:
	li r28, 0x1
	b L_g5_16
	L_g5_13:
	addi r28, r28, 0x1
	L_g5_9:
	cmpw r28, r27
	blt L_g5_10
	li r28, 0x0
	L_g5_16:
	cmpwi r28, 0x0
	mr r0, r28
	bne L_g5_17
	lwz r4, wp(r13)
	li r20, 0x0
	lwz r21, 0x0(r29)
	lwz r5, 0x20(r4)
	lwz r3, 0x18(r4)
	lwz r19, 0xd0(r4)
	lwz r27, 0x28(r4)
	lwz r26, 0x34(r4)
	lwz r25, 0x198(r5)
	lwz r24, 0x134(r5)
	lwz r23, 0x6c(r3)
	lwz r22, 0x194(r5)
	b L_g5_18
	L_g5_19:
	subf r3, r20, r21
	subi r0, r3, 0x1
	slwi r3, r0, 2
	addi r0, r3, 0x10
	lwzx r0, r29, r0
	mulli r3, r0, 0x18
	slwi r0, r0, 3
	lwzx r0, r22, r0
	lbzx r4, r23, r3
	add. r18, r0, r4
	blt L_g5_20
	cmpw r18, r24
	blt L_g5_21
	L_g5_20:
	lis r3, str_802C2DF8@ha
	li r18, 0x0
	addi r3, r3, str_802C2DF8@l
	crclr 6
	bl printf
	L_g5_21:
	slwi r3, r18, 6
	addi r0, r3, 0x8
	lwzx r0, r25, r0
	cmpwi r0, 0x2
	bne L_g5_22
	cmplwi r26, 0x0
	beq L_g5_23
	mr r3, r26
	mr r4, r27
	bl smartTexObj
	mr r4, r20
	bl GXLoadTexObj
	cmplwi r19, 0x0
	beq L_g5_24
	mulli r4, r20, 0x3
	mr r3, r19
	li r5, 0x1
	addi r18, r4, 0x1e
	mr r4, r18
	bl GXLoadTexMtxImm
	mr r3, r20
	mr r6, r18
	addi r5, r20, 0x4
	li r4, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_23
	L_g5_24:
	mr r3, r20
	addi r5, r20, 0x4
	li r4, 0x1
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	L_g5_23:
	li r0, 0x1
	b L_g5_17
	L_g5_22:
	addi r20, r20, 0x1
	L_g5_18:
	cmpw r20, r21
	blt L_g5_19
	li r0, 0x0
	L_g5_17:
	cmpwi r0, 0x0
	beq L_g5_8
	lwz r0, 0x8(r29)
	cmpwi r0, 0x0
	bne L_g5_8
	lwz r3, wp(r13)
	lwz r18, 0x38(r3)
	cmplwi r18, 0x0
	beq L_g5_8
	lwz r4, 0x2c(r3)
	mr r3, r18
	bl smartTexObj
	lwz r3, wp(r13)
	lwz r0, 0xe0(r3)
	cmpwi r0, 0x3
	beq L_g5_25
	li r3, 0x1
	li r4, 0x3
	li r5, 0x1
	bl GXSetZMode
	li r3, 0x0
	li r4, 0x4
	li r5, 0x5
	li r6, 0x0
	bl GXSetBlendMode
	li r3, 0x0
	bl GXSetZCompLoc
	li r3, 0x6
	li r4, 0x80
	li r5, 0x1
	li r6, 0x0
	li r7, 0x0
	bl GXSetAlphaCompare
	L_g5_25:
	cntlzw r0, r28
	lwz r4, wp(r13)
	rlwinm r3, r0, 29, 3, 29
	addi r0, r3, 0x30
	lwzx r3, r4, r0
	cmplwi r3, 0x0
	beq L_g5_26
	li r4, 0x0
	bl GXLoadTexObj
	li r3, 0x0
	li r4, 0x1
	li r5, 0x4
	li r6, 0x1e
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	cntlzw r0, r28
	lwz r5, wp(r13)
	rlwinm r3, r0, 29, 3, 29
	li r4, 0x1e
	addi r0, r3, 0xcc
	lwzx r3, r5, r0
	li r5, 0x1
	bl GXLoadTexMtxImm
	L_g5_26:
	mr r3, r18
	li r4, 0x1
	bl GXLoadTexObj
	li r3, 0x1
	li r4, 0x1
	li r5, 0x4
	li r6, 0x21
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	lwz r3, wp(r13)
	li r4, 0x21
	li r5, 0x1
	lwz r3, 0xd4(r3)
	bl GXLoadTexMtxImm
	lwz r5, wp(r13)
	li r3, 0x2
	lwz r6, g_modeling_mtx(r13)
	li r4, 0xc
	lwz r5, 0x18(r5)
	lwz r5, 0xe8(r5)
	bl mapSetMaterialTev
	L_g5_8:
	lwz r3, wp(r13)
	lwz r5, 0x18(r3)
	lwz r0, 0x0(r5)
	rlwinm. r0, r0, 0, 27, 27
	beq L_g5_27
	lwz r27, 0x30(r3)
	cmplwi r27, 0x0
	beq L_g5_27
	lwz r26, 0xcc(r3)
	cmplwi r26, 0x0
	beq L_g5_27
	lwz r4, 0x20(r3)
	li r19, 0x0
	lwz r25, 0x24(r3)
	lwz r24, 0x198(r4)
	lwz r23, 0x134(r4)
	lwz r22, 0x6c(r5)
	lwz r21, 0x194(r4)
	lwz r20, 0x0(r29)
	b L_g5_28
	L_g5_29:
	subf r3, r19, r20
	subi r0, r3, 0x1
	slwi r3, r0, 2
	addi r0, r3, 0x10
	lwzx r0, r29, r0
	mulli r3, r0, 0x18
	slwi r0, r0, 3
	lwzx r0, r21, r0
	lbzx r4, r22, r3
	add. r18, r0, r4
	blt L_g5_30
	cmpw r18, r23
	blt L_g5_31
	L_g5_30:
	lis r3, str_802C2DF8@ha
	li r18, 0x0
	addi r3, r3, str_802C2DF8@l
	crclr 6
	bl printf
	L_g5_31:
	slwi r3, r18, 6
	addi r0, r3, 0x8
	lwzx r0, r24, r0
	cmpwi r0, 0x1
	bne L_g5_32
	cmplwi r27, 0x0
	beq L_g5_27
	mr r3, r27
	mr r4, r25
	bl smartTexObj
	mr r4, r19
	bl GXLoadTexObj
	cmplwi r26, 0x0
	beq L_g5_33
	mulli r4, r19, 0x3
	mr r3, r26
	li r5, 0x1
	addi r18, r4, 0x1e
	mr r4, r18
	bl GXLoadTexMtxImm
	mr r3, r19
	mr r6, r18
	addi r5, r19, 0x4
	li r4, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_27
	L_g5_33:
	mr r3, r19
	addi r5, r19, 0x4
	li r4, 0x1
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_27
	L_g5_32:
	addi r19, r19, 0x1
	L_g5_28:
	cmpw r19, r20
	blt L_g5_29
	L_g5_27:
	addi r31, r31, 0x1
	addi r29, r29, 0x6c
	L_g5_4:
	cmpw r31, r30
	blt L_g5_5
	L_g5_1:
	lmw r18, 0x88(r1)
	lwz r0, 0xc4(r1)
	mtlr r0
	addi r1, r1, 0xc0
	blr
}

asm void animSetMaterial_Texture(s32 texCount, s32 *texIdRemap, AnimPoseTexEntry *pTexEntries, AnimTexMtx *animEntries, s32 texBindsCapacity, AnimTexBind *texBinds, AnimationTextureFile *texFile) {
	nofralloc
	stwu r1, -0x1c0(r1)
	mflr r0
	stw r0, 0x1c4(r1)
	stfd f31, 0x1b0(r1)
	psq_st f31, 0x1b8(r1), 0, 0
	stfd f30, 0x1a0(r1)
	psq_st f30, 0x1a8(r1), 0, 0
	stfd f29, 0x190(r1)
	psq_st f29, 0x198(r1), 0, 0
	stfd f28, 0x180(r1)
	psq_st f28, 0x188(r1), 0, 0
	stfd f27, 0x170(r1)
	psq_st f27, 0x178(r1), 0, 0
	stfd f26, 0x160(r1)
	psq_st f26, 0x168(r1), 0, 0
	stfd f25, 0x150(r1)
	psq_st f25, 0x158(r1), 0, 0
	stmw r19, 0x11c(r1)
	mr r24, r3
	mr r25, r4
	mr r26, r5
	mr r27, r6
	mr r28, r7
	mr r29, r8
	mr r30, r9
	li r23, 0x0
	b L_g5_1
	L_g5_2:
	subf r3, r23, r24
	subi r0, r3, 0x1
	slwi r0, r0, 2
	lwzx r3, r25, r0
	mulli r0, r3, 0x18
	slwi r3, r3, 3
	add r19, r26, r3
	lwz r7, 0x0(r19)
	lbzx r6, r27, r0
	add. r20, r7, r6
	blt L_g5_3
	cmpw r20, r28
	blt L_g5_4
	L_g5_3:
	lwz r4, wp(r13)
	lis r3, str_802C2E44@ha
	addi r3, r3, str_802C2E44@l
	li r20, 0x0
	lwz r8, 0x18(r4)
	lwz r5, 0x0(r4)
	lwz r4, 0x10(r8)
	lwz r0, 0x14(r8)
	slwi r4, r4, 4
	addi r4, r4, 0x8
	slwi r0, r0, 6
	lwzx r4, r5, r4
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r5, 0x1ac(r4)
	addi r4, r4, 0x4
	add r5, r5, r0
	crclr 6
	bl printf
	L_g5_4:
	slwi r0, r20, 6
	lwz r22, 0x4(r19)
	add r3, r29, r0
	lwz r0, 0x8(r3)
	lwz r4, 0x4(r3)
	cmpwi r0, 0x0
	bne L_g5_5
	lwz r3, 0x8(r30)
	mr r19, r4
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGet
	lwz r0, 0x4(r3)
	cmplwi r0, 0x0
	beq L_g5_6
	lwz r3, 0x8(r30)
	mr r4, r19
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGet
	mr r21, r3
	cmpwi r22, 0x0
	lwz r4, 0x0(r3)
	lwz r19, 0xc(r4)
	lwz r20, 0x10(r4)
	blt L_g5_7
	rlwinm. r0, r22, 0, 29, 29
	beq L_g5_8
	li r19, 0x2
	b L_g5_9
	L_g5_8:
	clrlwi r19, r22, 31
	L_g5_9:
	rlwinm. r0, r22, 0, 28, 28
	beq L_g5_10
	li r20, 0x2
	b L_g5_7
	L_g5_10:
	extrwi r20, r22, 1, 30
	L_g5_7:
	lbz r6, 0x21(r4)
	addi r3, r1, 0x10
	lwz r7, 0x4(r21)
	lbz r0, 0x22(r4)
	lwz r4, 0x8(r7)
	subf r5, r6, r0
	subf r0, r0, r6
	or r0, r5, r0
	lwz r5, 0x4(r7)
	lhz r6, 0x0(r7)
	srwi r22, r0, 31
	bl GXInitTlutObj
	lwz r7, 0x0(r21)
	li r0, 0x0
	mr r8, r19
	mr r9, r20
	stw r0, 0x8(r1)
	mr r10, r22
	addi r3, r1, 0x1c
	lwz r4, 0x8(r7)
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	lwz r7, 0x4(r7)
	bl GXInitTexObjCI
	lwz r7, 0x0(r21)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802c2de0@ha
	stw r5, 0x100(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802c2de0@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x1c
	stw r6, 0x104(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x100(r1)
	stw r0, 0x10c(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x108(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x108(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	addi r3, r1, 0x10
	li r4, 0x0
	bl GXLoadTlut
	mr r4, r23
	addi r3, r1, 0x1c
	bl GXLoadTexObj
	b L_g5_5
	L_g5_6:
	lwz r3, 0x8(r30)
	mr r4, r19
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	bl TEXGet
	mr r21, r3
	cmpwi r22, 0x0
	lwz r7, 0x0(r3)
	lwz r8, 0xc(r7)
	lwz r9, 0x10(r7)
	blt L_g5_11
	rlwinm. r0, r22, 0, 29, 29
	beq L_g5_12
	li r8, 0x2
	b L_g5_13
	L_g5_12:
	clrlwi r8, r22, 31
	L_g5_13:
	rlwinm. r0, r22, 0, 28, 28
	beq L_g5_14
	li r9, 0x2
	b L_g5_11
	L_g5_14:
	extrwi r9, r22, 1, 30
	L_g5_11:
	lbz r6, 0x21(r7)
	addi r3, r1, 0x1c
	lbz r0, 0x22(r7)
	lwz r4, 0x8(r7)
	subf r5, r6, r0
	subf r0, r0, r6
	or r0, r5, r0
	lhz r5, 0x2(r7)
	lhz r6, 0x0(r7)
	srwi r10, r0, 31
	lwz r7, 0x4(r7)
	bl GXInitTexObj
	lwz r7, 0x0(r21)
	lis r5, 0x4330
	lis r3, double_to_int_mask_802c2de0@ha
	stw r5, 0x108(r1)
	lbz r6, 0x21(r7)
	addi r4, r3, double_to_int_mask_802c2de0@l
	lbz r0, 0x22(r7)
	addi r3, r1, 0x1c
	stw r6, 0x10c(r1)
	li r6, 0x0
	lfd f2, 0x0(r4)
	li r8, 0x0
	lfd f0, 0x108(r1)
	stw r0, 0x104(r1)
	fsubs f1, f0, f2
	lwz r4, 0x14(r7)
	stw r5, 0x100(r1)
	lwz r5, 0x18(r7)
	lfd f0, 0x100(r1)
	lfs f3, 0x1c(r7)
	fsubs f2, f0, f2
	lbz r7, 0x20(r7)
	bl GXInitTexObjLOD
	mr r4, r23
	addi r3, r1, 0x1c
	bl GXLoadTexObj
	L_g5_5:
	addi r23, r23, 0x1
	L_g5_1:
	cmpw r23, r24
	blt L_g5_2
	li r21, 0x0
	lfs f30, float_0_80419a48(r2)
	lfs f31, float_1_80419a44(r2)
	mr r19, r21
	b L_g5_15
	L_g5_16:
	subf r3, r21, r24
	li r20, 0x0
	subi r0, r3, 0x1
	slwi r0, r0, 2
	lwzx r0, r25, r0
	mulli r0, r0, 0x18
	add r3, r27, r0
	lfs f25, 0x14(r3)
	lfs f29, 0xc(r3)
	fcmpu cr0, f30, f25
	lfs f28, 0x10(r3)
	lfs f27, 0x4(r3)
	lfs f26, 0x8(r3)
	beq L_g5_17
	lfs f1, float_0p5_80419a64(r2)
	fmr f3, f30
	ori r20, r20, 0x1
	addi r3, r1, 0x3c
	fmr f2, f1
	bl PSMTXTrans
	fneg f0, f25
	lfs f1, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0xcc
	li r4, 0x7a
	fmuls f1, f1, f0
	bl PSMTXRotRad
	addi r3, r1, 0x3c
	addi r4, r1, 0xcc
	addi r5, r1, 0x9c
	bl PSMTXConcat
	lfs f1, float_neg0p5_80419a88(r2)
	addi r3, r1, 0x3c
	lfs f3, float_0_80419a48(r2)
	fmr f2, f1
	bl PSMTXTrans
	addi r3, r1, 0x9c
	addi r4, r1, 0x3c
	addi r5, r1, 0xcc
	bl PSMTXConcat
	L_g5_17:
	fcmpu cr0, f30, f27
	bne L_g5_18
	fcmpu cr0, f30, f26
	bne L_g5_18
	fcmpu cr0, f30, f28
	beq L_g5_19
	L_g5_18:
	lfs f0, float_1_80419a44(r2)
	fmr f1, f27
	lfs f3, float_0_80419a48(r2)
	ori r20, r20, 0x2
	fsubs f0, f0, f26
	addi r3, r1, 0x9c
	fsubs f2, f0, f28
	bl PSMTXTrans
	L_g5_19:
	fcmpu cr0, f31, f29
	bne L_g5_20
	fcmpu cr0, f31, f28
	beq L_g5_21
	L_g5_20:
	fmr f1, f29
	lfs f3, float_1_80419a44(r2)
	fmr f2, f28
	ori r20, r20, 0x4
	addi r3, r1, 0x6c
	bl PSMTXScale
	L_g5_21:
	cmplwi r20, 0x7
	bgt L_g5_22
	lis r3, jumptable_803050B8@ha
	slwi r0, r20, 2
	addi r3, r3, jumptable_803050B8@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_23:
	mr r3, r21
	addi r5, r21, 0x4
	li r4, 0x1
	li r6, 0x3c
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	b L_g5_24
	L_g5_25:
	addi r31, r1, 0xcc
	b L_g5_22
	L_g5_26:
	addi r31, r1, 0x9c
	b L_g5_22
	L_g5_27:
	addi r3, r1, 0xcc
	addi r4, r1, 0x9c
	addi r5, r1, 0x3c
	bl PSMTXConcat
	addi r31, r1, 0x3c
	b L_g5_22
	L_g5_28:
	addi r31, r1, 0x6c
	b L_g5_22
	L_g5_29:
	addi r3, r1, 0xcc
	addi r4, r1, 0x6c
	addi r5, r1, 0x3c
	bl PSMTXConcat
	addi r31, r1, 0x3c
	b L_g5_22
	L_g5_30:
	addi r3, r1, 0x9c
	addi r4, r1, 0x6c
	addi r5, r1, 0x3c
	bl PSMTXConcat
	addi r31, r1, 0x3c
	b L_g5_22
	L_g5_31:
	addi r3, r1, 0xcc
	addi r4, r1, 0x9c
	addi r5, r1, 0x3c
	bl PSMTXConcat
	addi r3, r1, 0x3c
	addi r4, r1, 0x6c
	addi r5, r1, 0x9c
	bl PSMTXConcat
	addi r31, r1, 0x9c
	L_g5_22:
	addi r20, r19, 0x1e
	mr r3, r21
	mr r6, r20
	addi r5, r21, 0x4
	li r4, 0x1
	li r7, 0x0
	li r8, 0x7d
	bl GXSetTexCoordGen2
	mr r3, r31
	mr r4, r20
	li r5, 0x1
	bl GXLoadTexMtxImm
	L_g5_24:
	addi r21, r21, 0x1
	addi r19, r19, 0x3
	L_g5_15:
	cmpw r21, r24
	blt L_g5_16
	psq_l f31, 0x1b8(r1), 0, 0
	lfd f31, 0x1b0(r1)
	psq_l f30, 0x1a8(r1), 0, 0
	lfd f30, 0x1a0(r1)
	psq_l f29, 0x198(r1), 0, 0
	lfd f29, 0x190(r1)
	psq_l f28, 0x188(r1), 0, 0
	lfd f28, 0x180(r1)
	psq_l f27, 0x178(r1), 0, 0
	lfd f27, 0x170(r1)
	psq_l f26, 0x168(r1), 0, 0
	lfd f26, 0x160(r1)
	psq_l f25, 0x158(r1), 0, 0
	lfd f25, 0x150(r1)
	lmw r19, 0x11c(r1)
	lwz r0, 0x1c4(r1)
	mtlr r0
	addi r1, r1, 0x1c0
	blr
}

asm void pushGXModelMtx_JointNode__(AnimPoseNode* node, f32 sx, f32 sy, f32 sz) {
	nofralloc
	stwu r1, -0x1c0(r1)
	mflr r0
	stw r0, 0x1c4(r1)
	stfd f31, 0x1b0(r1)
	psq_st f31, 0x1b8(r1), 0, 0
	stfd f30, 0x1a0(r1)
	psq_st f30, 0x1a8(r1), 0, 0
	stfd f29, 0x190(r1)
	psq_st f29, 0x198(r1), 0, 0
	stfd f28, 0x180(r1)
	psq_st f28, 0x188(r1), 0, 0
	stfd f27, 0x170(r1)
	psq_st f27, 0x178(r1), 0, 0
	stfd f26, 0x160(r1)
	psq_st f26, 0x168(r1), 0, 0
	stfd f25, 0x150(r1)
	psq_st f25, 0x158(r1), 0, 0
	stfd f24, 0x140(r1)
	psq_st f24, 0x148(r1), 0, 0
	stfd f23, 0x130(r1)
	psq_st f23, 0x138(r1), 0, 0
	stfd f22, 0x120(r1)
	psq_st f22, 0x128(r1), 0, 0
	stfd f21, 0x110(r1)
	psq_st f21, 0x118(r1), 0, 0
	stfd f20, 0x100(r1)
	psq_st f20, 0x108(r1), 0, 0
	stw r31, 0xfc(r1)
	stw r30, 0xf8(r1)
	lfs f5, 0x0(r3)
	fmr f20, f1
	lfs f0, float_0_80419a48(r2)
	fmr f21, f2
	lfs f4, float_2_80419a84(r2)
	fmr f22, f3
	lfs f3, 0x18(r3)
	lfs f2, 0x1c(r3)
	fcmpu cr0, f5, f0
	lfs f1, 0x20(r3)
	fmuls f28, f4, f3
	fmuls f27, f4, f2
	lfs f2, 0x4(r3)
	fmuls f26, f4, f1
	lfs f3, 0x8(r3)
	li r30, 0x0
	lfs f31, 0xc(r3)
	lfs f30, 0x10(r3)
	lfs f29, 0x14(r3)
	lfs f25, 0x24(r3)
	lfs f24, 0x28(r3)
	lfs f23, 0x2c(r3)
	bne L_g5_1
	fcmpu cr0, f2, f0
	bne L_g5_1
	fcmpu cr0, f3, f0
	beq L_g5_2
	L_g5_1:
	fmr f1, f5
	addi r3, r1, 0xc8
	bl PSMTXTrans
	ori r30, r30, 0x1
	L_g5_2:
	lfs f0, float_1_80419a44(r2)
	fcmpu cr0, f0, f20
	bne L_g5_3
	fcmpu cr0, f0, f21
	bne L_g5_3
	fcmpu cr0, f0, f22
	bne L_g5_4
	L_g5_3:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f20, f0
	beq L_g5_5
	fcmpu cr0, f21, f0
	beq L_g5_5
	fcmpu cr0, f22, f0
	beq L_g5_5
	lfs f0, float_1_80419a44(r2)
	addi r3, r1, 0x68
	fdivs f1, f0, f20
	fdivs f2, f0, f21
	fdivs f3, f0, f22
	bl PSMTXScale
	b L_g5_6
	L_g5_5:
	lfs f1, float_1_80419a44(r2)
	addi r3, r1, 0x68
	fmr f2, f1
	fmr f3, f1
	bl PSMTXScale
	L_g5_6:
	ori r30, r30, 0x2
	L_g5_4:
	lfs f0, float_1_80419a44(r2)
	fcmpu cr0, f0, f31
	bne L_g5_7
	fcmpu cr0, f0, f30
	bne L_g5_7
	fcmpu cr0, f0, f29
	bne L_g5_8
	L_g5_7:
	fmr f1, f31
	addi r3, r1, 0x98
	fmr f2, f30
	fmr f3, f29
	bl PSMTXScale
	ori r30, r30, 0x4
	L_g5_8:
	addi r3, r1, 0x38
	bl PSMTXIdentity
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f23, f0
	beq L_g5_9
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x8
	li r4, 0x7a
	fmuls f1, f0, f23
	bl PSMTXRotRad
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x8
	L_g5_9:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f24, f0
	beq L_g5_10
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x8
	li r4, 0x79
	fmuls f1, f0, f24
	bl PSMTXRotRad
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x8
	L_g5_10:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f25, f0
	beq L_g5_11
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x8
	li r4, 0x78
	fmuls f1, f0, f25
	bl PSMTXRotRad
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x8
	L_g5_11:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f26, f0
	beq L_g5_12
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x8
	li r4, 0x7a
	fmuls f1, f0, f26
	bl PSMTXRotRad
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x8
	L_g5_12:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f27, f0
	beq L_g5_13
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x8
	li r4, 0x79
	fmuls f1, f0, f27
	bl PSMTXRotRad
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x8
	L_g5_13:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f28, f0
	beq L_g5_14
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x8
	li r4, 0x78
	fmuls f1, f0, f28
	bl PSMTXRotRad
	addi r3, r1, 0x38
	addi r4, r1, 0x8
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x8
	L_g5_14:
	lwz r4, g_modeling_mtx_lv(r13)
	lis r3, g_modeling_mtx_stack@ha
	addi r0, r3, g_modeling_mtx_stack@l
	cmplwi r30, 0xf
	addi r4, r4, 0x1
	mulli r3, r4, 0x30
	stw r4, g_modeling_mtx_lv(r13)
	add r0, r0, r3
	stw r0, g_modeling_mtx(r13)
	bgt L_g5_15
	lis r3, jumptable_803050D8@ha
	slwi r0, r30, 2
	addi r3, r3, jumptable_803050D8@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_16:
	addi r3, r1, 0x8
	bl PSMTXIdentity
	addi r31, r1, 0x8
	b L_g5_15
	L_g5_17:
	addi r31, r1, 0xc8
	b L_g5_15
	L_g5_18:
	addi r31, r1, 0x68
	b L_g5_15
	L_g5_19:
	addi r3, r1, 0xc8
	addi r4, r1, 0x68
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r31, r1, 0x8
	b L_g5_15
	L_g5_20:
	addi r31, r1, 0x98
	b L_g5_15
	L_g5_21:
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r31, r1, 0x8
	b L_g5_15
	L_g5_22:
	addi r3, r1, 0x68
	addi r4, r1, 0x98
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r31, r1, 0x8
	b L_g5_15
	L_g5_23:
	addi r3, r1, 0xc8
	addi r4, r1, 0x68
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x98
	addi r5, r1, 0xc8
	bl PSMTXConcat
	addi r31, r1, 0xc8
	b L_g5_15
	L_g5_24:
	addi r31, r1, 0x38
	b L_g5_15
	L_g5_25:
	addi r3, r1, 0xc8
	addi r4, r1, 0x38
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r31, r1, 0x8
	b L_g5_15
	L_g5_26:
	addi r3, r1, 0x68
	addi r4, r1, 0x38
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r31, r1, 0x8
	b L_g5_15
	L_g5_27:
	addi r3, r1, 0xc8
	addi r4, r1, 0x68
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x38
	addi r5, r1, 0xc8
	bl PSMTXConcat
	addi r31, r1, 0xc8
	b L_g5_15
	L_g5_28:
	addi r3, r1, 0x38
	addi r4, r1, 0x98
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r31, r1, 0x8
	b L_g5_15
	L_g5_29:
	addi r3, r1, 0xc8
	addi r4, r1, 0x38
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x98
	addi r5, r1, 0xc8
	bl PSMTXConcat
	addi r31, r1, 0xc8
	b L_g5_15
	L_g5_30:
	addi r3, r1, 0x68
	addi r4, r1, 0x38
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x98
	addi r5, r1, 0xc8
	bl PSMTXConcat
	addi r31, r1, 0xc8
	b L_g5_15
	L_g5_31:
	addi r3, r1, 0xc8
	addi r4, r1, 0x68
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r3, r1, 0x8
	addi r4, r1, 0x38
	addi r5, r1, 0xc8
	bl PSMTXConcat
	addi r3, r1, 0xc8
	addi r4, r1, 0x98
	addi r5, r1, 0x8
	bl PSMTXConcat
	addi r31, r1, 0x8
	L_g5_15:
	lwz r6, g_modeling_mtx_lv(r13)
	lis r3, g_modeling_mtx_stack@ha
	addi r5, r3, g_modeling_mtx_stack@l
	mr r4, r31
	subi r0, r6, 0x1
	mulli r3, r0, 0x30
	mulli r0, r6, 0x30
	add r3, r5, r3
	add r5, r5, r0
	bl PSMTXConcat
	psq_l f31, 0x1b8(r1), 0, 0
	lfd f31, 0x1b0(r1)
	psq_l f30, 0x1a8(r1), 0, 0
	lfd f30, 0x1a0(r1)
	psq_l f29, 0x198(r1), 0, 0
	lfd f29, 0x190(r1)
	psq_l f28, 0x188(r1), 0, 0
	lfd f28, 0x180(r1)
	psq_l f27, 0x178(r1), 0, 0
	lfd f27, 0x170(r1)
	psq_l f26, 0x168(r1), 0, 0
	lfd f26, 0x160(r1)
	psq_l f25, 0x158(r1), 0, 0
	lfd f25, 0x150(r1)
	psq_l f24, 0x148(r1), 0, 0
	lfd f24, 0x140(r1)
	psq_l f23, 0x138(r1), 0, 0
	lfd f23, 0x130(r1)
	psq_l f22, 0x128(r1), 0, 0
	lfd f22, 0x120(r1)
	psq_l f21, 0x118(r1), 0, 0
	lfd f21, 0x110(r1)
	psq_l f20, 0x108(r1), 0, 0
	lfd f20, 0x100(r1)
	lwz r31, 0xfc(r1)
	lwz r0, 0x1c4(r1)
	lwz r30, 0xf8(r1)
	mtlr r0
	addi r1, r1, 0x1c0
	blr
}

asm void pushGXModelMtx_TransformNode__(AnimPoseNode* node) {
	nofralloc
	stwu r1, -0x310(r1)
	mflr r0
	stw r0, 0x314(r1)
	stfd f31, 0x300(r1)
	psq_st f31, 0x308(r1), 0, 0
	stfd f30, 0x2f0(r1)
	psq_st f30, 0x2f8(r1), 0, 0
	stfd f29, 0x2e0(r1)
	psq_st f29, 0x2e8(r1), 0, 0
	stfd f28, 0x2d0(r1)
	psq_st f28, 0x2d8(r1), 0, 0
	stfd f27, 0x2c0(r1)
	psq_st f27, 0x2c8(r1), 0, 0
	stfd f26, 0x2b0(r1)
	psq_st f26, 0x2b8(r1), 0, 0
	stfd f25, 0x2a0(r1)
	psq_st f25, 0x2a8(r1), 0, 0
	stfd f24, 0x290(r1)
	psq_st f24, 0x298(r1), 0, 0
	stfd f23, 0x280(r1)
	psq_st f23, 0x288(r1), 0, 0
	stfd f22, 0x270(r1)
	psq_st f22, 0x278(r1), 0, 0
	stfd f21, 0x260(r1)
	psq_st f21, 0x268(r1), 0, 0
	stfd f20, 0x250(r1)
	psq_st f20, 0x258(r1), 0, 0
	stfd f19, 0x240(r1)
	psq_st f19, 0x248(r1), 0, 0
	stfd f18, 0x230(r1)
	psq_st f18, 0x238(r1), 0, 0
	stfd f17, 0x220(r1)
	psq_st f17, 0x228(r1), 0, 0
	stfd f16, 0x210(r1)
	psq_st f16, 0x218(r1), 0, 0
	stfd f15, 0x200(r1)
	psq_st f15, 0x208(r1), 0, 0
	stfd f14, 0x1f0(r1)
	psq_st f14, 0x1f8(r1), 0, 0
	stw r31, 0x1ec(r1)
	stw r30, 0x1e8(r1)
	lfs f1, 0x0(r3)
	li r30, 0x0
	lfs f0, float_0_80419a48(r2)
	lfs f5, float_2_80419a84(r2)
	lfs f4, 0x18(r3)
	fcmpu cr0, f1, f0
	lfs f2, 0x1c(r3)
	lfs f3, 0x20(r3)
	fmuls f31, f5, f4
	fmuls f30, f5, f2
	lfs f2, 0x4(r3)
	fmuls f29, f5, f3
	lfs f3, 0x8(r3)
	lfs f14, 0xc(r3)
	lfs f15, 0x10(r3)
	lfs f16, 0x14(r3)
	lfs f28, 0x30(r3)
	lfs f27, 0x34(r3)
	lfs f26, 0x38(r3)
	lfs f25, 0x3c(r3)
	lfs f24, 0x40(r3)
	lfs f23, 0x44(r3)
	lfs f22, 0x48(r3)
	lfs f21, 0x4c(r3)
	lfs f20, 0x50(r3)
	lfs f19, 0x54(r3)
	lfs f18, 0x58(r3)
	lfs f17, 0x5c(r3)
	bne L_g5_1
	fcmpu cr0, f2, f0
	bne L_g5_1
	fcmpu cr0, f3, f0
	beq L_g5_2
	L_g5_1:
	addi r3, r1, 0x1b8
	bl PSMTXTrans
	ori r30, r30, 0x1
	L_g5_2:
	lfs f0, float_1_80419a44(r2)
	fcmpu cr0, f0, f14
	bne L_g5_3
	fcmpu cr0, f0, f15
	bne L_g5_3
	fcmpu cr0, f0, f16
	beq L_g5_4
	L_g5_3:
	fmr f1, f14
	addi r3, r1, 0x188
	fmr f2, f15
	fmr f3, f16
	bl PSMTXScale
	ori r30, r30, 0x2
	L_g5_4:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f0, f25
	bne L_g5_5
	fcmpu cr0, f0, f24
	bne L_g5_5
	fcmpu cr0, f0, f23
	beq L_g5_6
	L_g5_5:
	rlwinm. r0, r30, 0, 30, 30
	beq L_g5_7
	fneg f1, f25
	addi r3, r1, 0xc8
	fneg f2, f24
	fneg f3, f23
	bl PSMTXTrans
	fmr f1, f25
	addi r3, r1, 0xf8
	fmr f2, f24
	fmr f3, f23
	bl PSMTXTrans
	fmr f1, f19
	addi r3, r1, 0x98
	fmr f2, f18
	fmr f3, f17
	bl PSMTXTrans
	addi r3, r1, 0x98
	addi r4, r1, 0xf8
	addi r5, r1, 0x128
	bl PSMTXConcat
	addi r3, r1, 0x128
	addi r4, r1, 0x188
	mr r5, r3
	bl PSMTXConcat
	addi r3, r1, 0x128
	addi r4, r1, 0xc8
	addi r5, r1, 0x188
	bl PSMTXConcat
	b L_g5_6
	L_g5_7:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f19, f0
	bne L_g5_8
	fcmpu cr0, f18, f0
	bne L_g5_8
	fcmpu cr0, f17, f0
	beq L_g5_6
	L_g5_8:
	fmr f1, f19
	addi r3, r1, 0x188
	fmr f2, f18
	fmr f3, f17
	bl PSMTXTrans
	ori r30, r30, 0x2
	L_g5_6:
	addi r3, r1, 0x158
	bl PSMTXIdentity
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f29, f0
	beq L_g5_9
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x128
	li r4, 0x7a
	fmuls f1, f0, f29
	bl PSMTXRotRad
	addi r3, r1, 0x158
	addi r4, r1, 0x128
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x4
	L_g5_9:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f30, f0
	beq L_g5_10
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x128
	li r4, 0x79
	fmuls f1, f0, f30
	bl PSMTXRotRad
	addi r3, r1, 0x158
	addi r4, r1, 0x128
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x4
	L_g5_10:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f31, f0
	beq L_g5_11
	lfs f0, float_deg2rad_80419a4c(r2)
	addi r3, r1, 0x128
	li r4, 0x78
	fmuls f1, f0, f31
	bl PSMTXRotRad
	addi r3, r1, 0x158
	addi r4, r1, 0x128
	mr r5, r3
	bl PSMTXConcat
	ori r30, r30, 0x4
	L_g5_11:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f0, f28
	bne L_g5_12
	fcmpu cr0, f0, f27
	bne L_g5_12
	fcmpu cr0, f0, f26
	beq L_g5_13
	L_g5_12:
	rlwinm. r0, r30, 0, 29, 29
	beq L_g5_14
	fneg f1, f28
	addi r3, r1, 0x38
	fneg f2, f27
	fneg f3, f26
	bl PSMTXTrans
	fmr f1, f28
	addi r3, r1, 0x68
	fmr f2, f27
	fmr f3, f26
	bl PSMTXTrans
	fmr f1, f22
	addi r3, r1, 0x8
	fmr f2, f21
	fmr f3, f20
	bl PSMTXTrans
	addi r3, r1, 0x8
	addi r4, r1, 0x68
	addi r5, r1, 0x128
	bl PSMTXConcat
	addi r4, r1, 0x158
	addi r3, r1, 0x128
	mr r5, r4
	bl PSMTXConcat
	addi r3, r1, 0x158
	addi r4, r1, 0x38
	mr r5, r3
	bl PSMTXConcat
	b L_g5_13
	L_g5_14:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f22, f0
	bne L_g5_15
	fcmpu cr0, f21, f0
	bne L_g5_15
	fcmpu cr0, f20, f0
	beq L_g5_13
	L_g5_15:
	fmr f1, f22
	addi r3, r1, 0x158
	fmr f2, f21
	fmr f3, f20
	bl PSMTXTrans
	ori r30, r30, 0x4
	L_g5_13:
	lwz r4, g_modeling_mtx_lv(r13)
	lis r3, g_modeling_mtx_stack@ha
	addi r0, r3, g_modeling_mtx_stack@l
	cmplwi r30, 0x7
	addi r4, r4, 0x1
	mulli r3, r4, 0x30
	stw r4, g_modeling_mtx_lv(r13)
	add r0, r0, r3
	stw r0, g_modeling_mtx(r13)
	bgt L_g5_16
	lis r3, jumptable_80305118@ha
	slwi r0, r30, 2
	addi r3, r3, jumptable_80305118@l
	lwzx r0, r3, r0
	mtctr r0
	bctr
	L_g5_17:
	addi r3, r1, 0x128
	bl PSMTXIdentity
	addi r31, r1, 0x128
	b L_g5_16
	L_g5_18:
	addi r31, r1, 0x1b8
	b L_g5_16
	L_g5_19:
	addi r31, r1, 0x188
	b L_g5_16
	L_g5_20:
	addi r3, r1, 0x1b8
	addi r4, r1, 0x188
	addi r5, r1, 0x128
	bl PSMTXConcat
	addi r31, r1, 0x128
	b L_g5_16
	L_g5_21:
	addi r31, r1, 0x158
	b L_g5_16
	L_g5_22:
	addi r3, r1, 0x1b8
	addi r4, r1, 0x158
	addi r5, r1, 0x128
	bl PSMTXConcat
	addi r31, r1, 0x128
	b L_g5_16
	L_g5_23:
	addi r3, r1, 0x158
	addi r4, r1, 0x188
	addi r5, r1, 0x128
	bl PSMTXConcat
	addi r31, r1, 0x128
	b L_g5_16
	L_g5_24:
	addi r3, r1, 0x1b8
	addi r4, r1, 0x158
	addi r5, r1, 0x128
	bl PSMTXConcat
	addi r3, r1, 0x128
	addi r4, r1, 0x188
	addi r5, r1, 0x1b8
	bl PSMTXConcat
	addi r31, r1, 0x1b8
	L_g5_16:
	lwz r6, g_modeling_mtx_lv(r13)
	lis r3, g_modeling_mtx_stack@ha
	addi r5, r3, g_modeling_mtx_stack@l
	mr r4, r31
	subi r0, r6, 0x1
	mulli r3, r0, 0x30
	mulli r0, r6, 0x30
	add r3, r5, r3
	add r5, r5, r0
	bl PSMTXConcat
	psq_l f31, 0x308(r1), 0, 0
	lfd f31, 0x300(r1)
	psq_l f30, 0x2f8(r1), 0, 0
	lfd f30, 0x2f0(r1)
	psq_l f29, 0x2e8(r1), 0, 0
	lfd f29, 0x2e0(r1)
	psq_l f28, 0x2d8(r1), 0, 0
	lfd f28, 0x2d0(r1)
	psq_l f27, 0x2c8(r1), 0, 0
	lfd f27, 0x2c0(r1)
	psq_l f26, 0x2b8(r1), 0, 0
	lfd f26, 0x2b0(r1)
	psq_l f25, 0x2a8(r1), 0, 0
	lfd f25, 0x2a0(r1)
	psq_l f24, 0x298(r1), 0, 0
	lfd f24, 0x290(r1)
	psq_l f23, 0x288(r1), 0, 0
	lfd f23, 0x280(r1)
	psq_l f22, 0x278(r1), 0, 0
	lfd f22, 0x270(r1)
	psq_l f21, 0x268(r1), 0, 0
	lfd f21, 0x260(r1)
	psq_l f20, 0x258(r1), 0, 0
	lfd f20, 0x250(r1)
	psq_l f19, 0x248(r1), 0, 0
	lfd f19, 0x240(r1)
	psq_l f18, 0x238(r1), 0, 0
	lfd f18, 0x230(r1)
	psq_l f17, 0x228(r1), 0, 0
	lfd f17, 0x220(r1)
	psq_l f16, 0x218(r1), 0, 0
	lfd f16, 0x210(r1)
	psq_l f15, 0x208(r1), 0, 0
	lfd f15, 0x200(r1)
	psq_l f14, 0x1f8(r1), 0, 0
	lfd f14, 0x1f0(r1)
	lwz r31, 0x1ec(r1)
	lwz r0, 0x314(r1)
	lwz r30, 0x1e8(r1)
	mtlr r0
	addi r1, r1, 0x310
	blr
}

asm void animPoseMain(s32 poseId) {
	nofralloc
	stwu r1, -0x70(r1)
	mflr r0
	stw r0, 0x74(r1)
	stfd f31, 0x60(r1)
	psq_st f31, 0x68(r1), 0, 0
	stfd f30, 0x50(r1)
	psq_st f30, 0x58(r1), 0, 0
	stmw r18, 0x18(r1)
	lwz r6, wp(r13)
	mulli r0, r3, 0x170
	li r3, 0x4
	lwz r7, 0x10(r6)
	lwz r5, 0x0(r6)
	oris r3, r3, 0x4
	add r31, r7, r0
	lwz r4, 0x10(r31)
	lwz r0, 0x14(r31)
	slwi r4, r4, 4
	add r4, r5, r4
	slwi r0, r0, 6
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r29, 0x0(r4)
	lwz r4, 0x1ac(r29)
	add r4, r4, r0
	lwz r30, 0x3c(r4)
	mtspr GQR2, r3
	li r3, 0x5
	oris r3, r3, 0x5
	mtspr GQR3, r3
	li r3, 0x6
	oris r3, r3, 0x6
	mtspr GQR4, r3
	li r3, 0x7
	oris r3, r3, 0x7
	mtspr GQR5, r3
	lwz r0, 0xe8(r6)
	cmpwi r0, 0x0
	beq L_g5_1
	lwz r28, 0xf8(r6)
	lwz r27, 0xfc(r6)
	b L_g5_2
	L_g5_1:
	lwz r28, 0x4c(r31)
	lwz r27, 0x54(r31)
	L_g5_2:
	lwz r3, 0x90(r31)
	cmpwi r3, -0x1
	beq L_g5_3
	mulli r4, r3, 0x170
	addi r0, r4, 0x4
	lwzx r0, r7, r0
	rlwinm. r0, r0, 0, 30, 30
	bne L_g5_3
	bl animPoseMain
	L_g5_3:
	cmplwi r30, 0x0
	beq L_g5_4
	lwz r0, 0xc(r31)
	lwz r4, 0x24(r30)
	cmpwi r0, 0x0
	lwz r26, 0x0(r4)
	bne L_g5_5
	lis r4, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r4)
	lis r4, 0x1062
	addi r5, r4, 0x4dd3
	lwz r3, 0x40(r6)
	srwi r0, r0, 2
	lwz r4, 0x44(r6)
	mulhwu r0, r5, r0
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_6
	L_g5_5:
	lis r4, 0x8000
	lwz r6, gp(r13)
	lwz r0, 0xf8(r4)
	lis r4, 0x1062
	addi r5, r4, 0x4dd3
	lwz r3, 0x38(r6)
	srwi r0, r0, 2
	lwz r4, 0x3c(r6)
	mulhwu r0, r5, r0
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_6:
	lwz r5, 0x1c(r31)
	lwz r0, 0x18(r31)
	subfc r4, r5, r4
	subfe r3, r0, r3
	bl __cvt_ull_flt
	lfs f0, float_60_80419ac4(r2)
	lfs f2, float_1000_80419ac8(r2)
	fmuls f1, f0, f1
	lfs f0, float_0_80419a48(r2)
	fdivs f1, f1, f2
	stfs f1, 0x20(r31)
	lfs f2, 0x20(r31)
	lfs f1, 0x44(r31)
	fmuls f1, f2, f1
	stfs f1, 0x20(r31)
	lwz r4, 0x24(r30)
	lfs f2, 0x20(r31)
	lfs f1, 0x8(r4)
	lfs f3, 0x4(r4)
	fsubs f4, f1, f3
	fcmpu cr0, f0, f4
	bne L_g5_7
	fsubs f0, f2, f3
	stfs f0, 0x84(r31)
	b L_g5_8
	L_g5_7:
	cmpwi r26, 0x0
	beq L_g5_9
	fsubs f1, f2, f3
	fcmpo cr0, f1, f0
	bge L_g5_10
	stfs f0, 0x84(r31)
	b L_g5_8
	L_g5_10:
	fdivs f0, f1, f4
	lis r0, 0x4330
	lis r4, double_to_int_802c2df0@ha
	stw r0, 0x10(r1)
	lfd f1, double_to_int_802c2df0@l(r4)
	stfs f0, 0x84(r31)
	lfs f0, 0x84(r31)
	fctiwz f0, f0
	stfd f0, 0x8(r1)
	lwz r0, 0xc(r1)
	xoris r0, r0, 0x8000
	stw r0, 0x14(r1)
	lfd f0, 0x10(r1)
	fsubs f0, f0, f1
	fnmsubs f3, f0, f4, f2
	b L_g5_8
	L_g5_9:
	fcmpo cr0, f2, f3
	bge L_g5_11
	stfs f0, 0x84(r31)
	b L_g5_8
	L_g5_11:
	fcmpo cr0, f2, f1
	ble L_g5_12
	fsubs f0, f2, f3
	fmr f3, f1
	fdivs f0, f0, f4
	stfs f0, 0x84(r31)
	b L_g5_8
	L_g5_12:
	fsubs f0, f2, f3
	fmr f3, f2
	fdivs f0, f0, f4
	stfs f0, 0x84(r31)
	L_g5_8:
	stfs f3, 0x24(r31)
	li r4, 0x0
	lwz r0, 0x8(r30)
	lfs f1, 0x24(r31)
	lwz r5, 0x28(r30)
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_13
	L_g5_14:
	lfs f0, 0x0(r5)
	fcmpo cr0, f0, f1
	bgt L_g5_13
	addi r5, r5, 0x2c
	addi r4, r4, 0x1
	bdnz L_g5_14
	L_g5_13:
	subi r0, r4, 0x1
	li r5, 0x0
	stw r0, 0x28(r31)
	lwz r4, 0x28(r31)
	addi r0, r4, 0x1
	stw r0, 0x2c(r31)
	lwz r0, 0x20(r30)
	lfs f1, 0x24(r31)
	lwz r4, 0x40(r30)
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_15
	L_g5_16:
	lfs f0, 0x0(r4)
	fcmpo cr0, f0, f1
	bgt L_g5_15
	addi r4, r4, 0x8
	addi r5, r5, 0x1
	bdnz L_g5_16
	L_g5_15:
	subi r0, r5, 0x1
	cmpwi r26, 0x0
	stw r0, 0x34(r31)
	lwz r4, 0x34(r31)
	addi r0, r4, 0x1
	stw r0, 0x38(r31)
	bne L_g5_17
	lwz r4, 0x2c(r31)
	lwz r0, 0x8(r30)
	cmpw r4, r0
	blt L_g5_18
	lwz r0, 0x28(r31)
	stw r0, 0x2c(r31)
	L_g5_18:
	lwz r4, 0x38(r31)
	lwz r0, 0x20(r30)
	cmpw r4, r0
	blt L_g5_17
	lwz r0, 0x34(r31)
	stw r0, 0x38(r31)
	L_g5_17:
	lwz r0, 0x34(r31)
	cmpwi r26, 0x0
	lwz r4, 0x40(r30)
	slwi r0, r0, 3
	add r4, r4, r0
	lwz r0, 0x4(r4)
	stw r0, 0x80(r31)
	lwz r0, 0x28(r31)
	lwz r5, 0x28(r30)
	mulli r0, r0, 0x2c
	lfs f0, 0x24(r31)
	lfsx f1, r5, r0
	fsubs f2, f0, f1
	beq L_g5_19
	lwz r4, 0x2c(r31)
	lwz r0, 0x8(r30)
	cmpw r4, r0
	blt L_g5_20
	li r0, 0x0
	stw r0, 0x2c(r31)
	lwz r0, 0x28(r31)
	lwz r5, 0x24(r30)
	mulli r0, r0, 0x2c
	lwz r4, 0x28(r30)
	lfs f1, 0x8(r5)
	lfsx f0, r4, r0
	fsubs f1, f1, f0
	b L_g5_21
	L_g5_20:
	mulli r0, r4, 0x2c
	lfsx f0, r5, r0
	fsubs f1, f0, f1
	b L_g5_21
	L_g5_19:
	lwz r0, 0x2c(r31)
	mulli r0, r0, 0x2c
	lfsx f0, r5, r0
	fsubs f1, f0, f1
	L_g5_21:
	lfs f0, float_0_80419a48(r2)
	fcmpu cr0, f0, f1
	bne L_g5_22
	stfs f0, 0x30(r31)
	b L_g5_23
	L_g5_22:
	fdivs f0, f2, f1
	stfs f0, 0x30(r31)
	L_g5_23:
	lwz r25, 0x28(r31)
	lwz r4, 0x3c(r31)
	lwz r26, 0x2c(r31)
	cmpw r4, r25
	lfs f31, 0x30(r31)
	lwz r24, 0xf0(r29)
	lwz r23, 0xf8(r29)
	lwz r19, 0x13c(r29)
	lwz r22, 0x140(r29)
	lwz r18, 0x12c(r29)
	beq L_g5_24
	cmpwi r4, -0x1
	beq L_g5_25
	cmpw r4, r25
	ble L_g5_26
	L_g5_25:
	mulli r4, r25, 0x2c
	lwz r0, 0x28(r30)
	cmpwi r24, 0x0
	mr r21, r0
	addi r20, r4, 0x2c
	add r20, r0, r20
	beq L_g5_27
	mulli r5, r24, 0xc
	lwz r3, 0x48(r31)
	lwz r4, 0x154(r29)
	bl memcpy_as4
	L_g5_27:
	cmpwi r23, 0x0
	beq L_g5_28
	mulli r5, r23, 0xc
	lwz r3, 0x50(r31)
	lwz r4, 0x15c(r29)
	bl memcpy_as4
	L_g5_28:
	cmpwi r19, 0x0
	beq L_g5_29
	lwz r3, 0x58(r31)
	mr r5, r19
	lwz r4, 0x1a0(r29)
	bl memcpy
	L_g5_29:
	cmpwi r22, 0x0
	beq L_g5_30
	lwz r3, 0x60(r31)
	slwi r5, r22, 2
	lwz r4, 0x1a4(r29)
	bl memcpy_as4
	L_g5_30:
	cmpwi r18, 0x0
	beq L_g5_31
	mulli r5, r18, 0x18
	lwz r3, 0x68(r31)
	lwz r4, 0x190(r29)
	bl memcpy_as4
	L_g5_31:
	lwz r0, 0x3c(r31)
	cmpwi r0, -0x1
	bne L_g5_32
	li r0, 0x0
	stw r0, 0x3c(r31)
	L_g5_32:
	lfs f2, float_0p0625_80419acc(r2)
	b L_g5_33
	L_g5_34:
	lwz r4, 0x4(r21)
	lwz r0, 0x8(r21)
	lwz r5, 0x2c(r30)
	slwi r4, r4, 2
	slwi r0, r0, 2
	lwz r6, 0x48(r31)
	add r5, r5, r4
	add r7, r5, r0
	addi r4, r7, 0x3
	subf r4, r5, r4
	cmplw r5, r7
	srwi r4, r4, 2
	bge L_g5_35
	srwi. r0, r4, 2
	mtctr r0
	beq L_g5_36
	L_g5_37:
	lbz r0, 0x0(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x1(r5), 1, 4
	psq_l f3, 0x2(r5), 1, 4
	psq_l f4, 0x3(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	lbz r0, 0x4(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x5(r5), 1, 4
	psq_l f3, 0x6(r5), 1, 4
	psq_l f4, 0x7(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	lbz r0, 0x8(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x9(r5), 1, 4
	psq_l f3, 0xa(r5), 1, 4
	psq_l f4, 0xb(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	lbz r0, 0xc(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0xd(r5), 1, 4
	psq_l f3, 0xe(r5), 1, 4
	psq_l f4, 0xf(r5), 1, 4
	addi r5, r5, 0x10
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	bdnz L_g5_37
	andi. r4, r4, 0x3
	beq L_g5_35
	L_g5_36:
	mtctr r4
	L_g5_38:
	lbz r0, 0x0(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x1(r5), 1, 4
	psq_l f3, 0x2(r5), 1, 4
	psq_l f4, 0x3(r5), 1, 4
	addi r5, r5, 0x4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	bdnz L_g5_38
	L_g5_35:
	lwz r4, 0xc(r21)
	lwz r0, 0x10(r21)
	lwz r5, 0x30(r30)
	slwi r4, r4, 2
	slwi r0, r0, 2
	lwz r6, 0x50(r31)
	add r5, r5, r4
	add r7, r5, r0
	addi r4, r7, 0x3
	subf r4, r5, r4
	cmplw r5, r7
	srwi r4, r4, 2
	bge L_g5_39
	srwi. r0, r4, 2
	mtctr r0
	beq L_g5_40
	L_g5_41:
	lbz r0, 0x0(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x1(r5), 1, 4
	psq_l f3, 0x2(r5), 1, 4
	psq_l f4, 0x3(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	lbz r0, 0x4(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x5(r5), 1, 4
	psq_l f3, 0x6(r5), 1, 4
	psq_l f4, 0x7(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	lbz r0, 0x8(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x9(r5), 1, 4
	psq_l f3, 0xa(r5), 1, 4
	psq_l f4, 0xb(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	lbz r0, 0xc(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0xd(r5), 1, 4
	psq_l f3, 0xe(r5), 1, 4
	psq_l f4, 0xf(r5), 1, 4
	addi r5, r5, 0x10
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	bdnz L_g5_41
	andi. r4, r4, 0x3
	beq L_g5_39
	L_g5_40:
	mtctr r4
	L_g5_42:
	lbz r0, 0x0(r5)
	mulli r0, r0, 0xc
	add r6, r6, r0
	psq_l f1, 0x1(r5), 1, 4
	psq_l f3, 0x2(r5), 1, 4
	psq_l f4, 0x3(r5), 1, 4
	addi r5, r5, 0x4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lfs f0, 0x4(r6)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r6)
	lfs f0, 0x8(r6)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r6)
	bdnz L_g5_42
	L_g5_39:
	lwz r4, 0x1c(r21)
	lwz r0, 0x20(r21)
	lwz r5, 0x38(r30)
	slwi r4, r4, 1
	slwi r0, r0, 1
	lwz r7, 0x58(r31)
	add r6, r5, r4
	add r5, r6, r0
	addi r4, r5, 0x1
	subf r4, r6, r4
	cmplw r6, r5
	srwi r4, r4, 1
	bge L_g5_43
	srwi. r0, r4, 3
	mtctr r0
	beq L_g5_44
	L_g5_45:
	lbz r5, 0x0(r6)
	lbz r0, 0x1(r6)
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lbz r5, 0x2(r6)
	lbz r0, 0x3(r6)
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lbz r5, 0x4(r6)
	lbz r0, 0x5(r6)
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lbz r5, 0x6(r6)
	lbz r0, 0x7(r6)
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lbz r5, 0x8(r6)
	lbz r0, 0x9(r6)
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lbz r5, 0xa(r6)
	lbz r0, 0xb(r6)
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lbz r5, 0xc(r6)
	lbz r0, 0xd(r6)
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lbz r5, 0xe(r6)
	lbz r0, 0xf(r6)
	addi r6, r6, 0x10
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	bdnz L_g5_45
	andi. r4, r4, 0x7
	beq L_g5_43
	L_g5_44:
	mtctr r4
	L_g5_46:
	lbz r5, 0x0(r6)
	lbz r0, 0x1(r6)
	addi r6, r6, 0x2
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	bdnz L_g5_46
	L_g5_43:
	lwz r4, 0x24(r21)
	lwz r0, 0x28(r21)
	lwz r5, 0x3c(r30)
	slwi r4, r4, 2
	slwi r0, r0, 2
	lwz r6, 0x60(r31)
	add r5, r5, r4
	add r7, r5, r0
	addi r4, r7, 0x3
	subf r4, r5, r4
	cmplw r5, r7
	srwi r4, r4, 2
	bge L_g5_47
	srwi. r0, r4, 3
	mtctr r0
	beq L_g5_48
	L_g5_49:
	lbz r0, 0x0(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x1(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lbz r0, 0x4(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x5(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lbz r0, 0x8(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x9(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lbz r0, 0xc(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0xd(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lbz r0, 0x10(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x11(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lbz r0, 0x14(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x15(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lbz r0, 0x18(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x19(r5), 1, 4
	lfs f0, 0x0(r6)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	lbz r0, 0x1c(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x1d(r5), 1, 4
	lfs f0, 0x0(r6)
	addi r5, r5, 0x20
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	bdnz L_g5_49
	andi. r4, r4, 0x7
	beq L_g5_47
	L_g5_48:
	mtctr r4
	L_g5_50:
	lbz r0, 0x0(r5)
	slwi r0, r0, 2
	add r6, r6, r0
	psq_l f1, 0x1(r5), 1, 4
	lfs f0, 0x0(r6)
	addi r5, r5, 0x4
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r6)
	bdnz L_g5_50
	L_g5_47:
	lwz r5, 0x14(r21)
	li r0, 0xc
	lwz r4, 0x18(r21)
	mulli r5, r5, 0xc
	lwz r6, 0x34(r30)
	lwz r7, 0x68(r31)
	mulli r4, r4, 0xc
	add r6, r6, r5
	add r5, r6, r4
	addi r4, r5, 0xb
	subf r4, r6, r4
	cmplw r6, r5
	divwu r4, r4, r0
	bge L_g5_51
	srwi. r0, r4, 2
	mtctr r0
	beq L_g5_52
	L_g5_53:
	lbz r5, 0x0(r6)
	lbz r0, 0x1(r6)
	mulli r5, r5, 0x18
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lfs f1, 0x4(r7)
	lfs f0, 0x4(r6)
	fadds f0, f1, f0
	stfs f0, 0x4(r7)
	lfs f1, 0x8(r7)
	lfs f0, 0x8(r6)
	fadds f0, f1, f0
	stfs f0, 0x8(r7)
	lbz r5, 0xc(r6)
	lbz r0, 0xd(r6)
	mulli r5, r5, 0x18
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lfs f1, 0x4(r7)
	lfs f0, 0x10(r6)
	fadds f0, f1, f0
	stfs f0, 0x4(r7)
	lfs f1, 0x8(r7)
	lfs f0, 0x14(r6)
	fadds f0, f1, f0
	stfs f0, 0x8(r7)
	lbz r5, 0x18(r6)
	lbz r0, 0x19(r6)
	mulli r5, r5, 0x18
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lfs f1, 0x4(r7)
	lfs f0, 0x1c(r6)
	fadds f0, f1, f0
	stfs f0, 0x4(r7)
	lfs f1, 0x8(r7)
	lfs f0, 0x20(r6)
	fadds f0, f1, f0
	stfs f0, 0x8(r7)
	lbz r5, 0x24(r6)
	lbz r0, 0x25(r6)
	mulli r5, r5, 0x18
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lfs f1, 0x4(r7)
	lfs f0, 0x28(r6)
	fadds f0, f1, f0
	stfs f0, 0x4(r7)
	lfs f0, 0x2c(r6)
	addi r6, r6, 0x30
	lfs f1, 0x8(r7)
	fadds f0, f1, f0
	stfs f0, 0x8(r7)
	bdnz L_g5_53
	andi. r4, r4, 0x3
	beq L_g5_51
	L_g5_52:
	mtctr r4
	L_g5_54:
	lbz r5, 0x0(r6)
	lbz r0, 0x1(r6)
	mulli r5, r5, 0x18
	add r7, r7, r5
	lbz r5, 0x0(r7)
	add r0, r5, r0
	stb r0, 0x0(r7)
	lfs f1, 0x4(r7)
	lfs f0, 0x4(r6)
	fadds f0, f1, f0
	stfs f0, 0x4(r7)
	lfs f0, 0x8(r6)
	addi r6, r6, 0xc
	lfs f1, 0x8(r7)
	fadds f0, f1, f0
	stfs f0, 0x8(r7)
	bdnz L_g5_54
	L_g5_51:
	addi r21, r21, 0x2c
	L_g5_33:
	cmplw r21, r20
	blt L_g5_34
	b L_g5_55
	L_g5_26:
	bge L_g5_55
	addi r4, r4, 0x1
	addi r0, r25, 0x1
	mulli r4, r4, 0x2c
	lwz r5, 0x28(r30)
	lfs f2, float_0p0625_80419acc(r2)
	mulli r0, r0, 0x2c
	add r4, r5, r4
	add r0, r5, r0
	b L_g5_56
	L_g5_57:
	lwz r6, 0x4(r4)
	lwz r5, 0x8(r4)
	lwz r7, 0x2c(r30)
	slwi r6, r6, 2
	slwi r5, r5, 2
	lwz r8, 0x48(r31)
	add r7, r7, r6
	add r5, r7, r5
	addi r6, r5, 0x3
	subf r6, r7, r6
	cmplw r7, r5
	srwi r6, r6, 2
	bge L_g5_58
	srwi. r5, r6, 2
	mtctr r5
	beq L_g5_59
	L_g5_60:
	lbz r5, 0x0(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x1(r7), 1, 4
	psq_l f3, 0x2(r7), 1, 4
	psq_l f4, 0x3(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	lbz r5, 0x4(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x5(r7), 1, 4
	psq_l f3, 0x6(r7), 1, 4
	psq_l f4, 0x7(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	lbz r5, 0x8(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x9(r7), 1, 4
	psq_l f3, 0xa(r7), 1, 4
	psq_l f4, 0xb(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	lbz r5, 0xc(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0xd(r7), 1, 4
	psq_l f3, 0xe(r7), 1, 4
	psq_l f4, 0xf(r7), 1, 4
	addi r7, r7, 0x10
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	bdnz L_g5_60
	andi. r6, r6, 0x3
	beq L_g5_58
	L_g5_59:
	mtctr r6
	L_g5_61:
	lbz r5, 0x0(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x1(r7), 1, 4
	psq_l f3, 0x2(r7), 1, 4
	psq_l f4, 0x3(r7), 1, 4
	addi r7, r7, 0x4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	bdnz L_g5_61
	L_g5_58:
	lwz r6, 0xc(r4)
	lwz r5, 0x10(r4)
	lwz r7, 0x30(r30)
	slwi r6, r6, 2
	slwi r5, r5, 2
	lwz r8, 0x50(r31)
	add r7, r7, r6
	add r5, r7, r5
	addi r6, r5, 0x3
	subf r6, r7, r6
	cmplw r7, r5
	srwi r6, r6, 2
	bge L_g5_62
	srwi. r5, r6, 2
	mtctr r5
	beq L_g5_63
	L_g5_64:
	lbz r5, 0x0(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x1(r7), 1, 4
	psq_l f3, 0x2(r7), 1, 4
	psq_l f4, 0x3(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	lbz r5, 0x4(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x5(r7), 1, 4
	psq_l f3, 0x6(r7), 1, 4
	psq_l f4, 0x7(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	lbz r5, 0x8(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x9(r7), 1, 4
	psq_l f3, 0xa(r7), 1, 4
	psq_l f4, 0xb(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	lbz r5, 0xc(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0xd(r7), 1, 4
	psq_l f3, 0xe(r7), 1, 4
	psq_l f4, 0xf(r7), 1, 4
	addi r7, r7, 0x10
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	bdnz L_g5_64
	andi. r6, r6, 0x3
	beq L_g5_62
	L_g5_63:
	mtctr r6
	L_g5_65:
	lbz r5, 0x0(r7)
	mulli r5, r5, 0xc
	add r8, r8, r5
	psq_l f1, 0x1(r7), 1, 4
	psq_l f3, 0x2(r7), 1, 4
	psq_l f4, 0x3(r7), 1, 4
	addi r7, r7, 0x4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lfs f0, 0x4(r8)
	fmadds f0, f2, f3, f0
	stfs f0, 0x4(r8)
	lfs f0, 0x8(r8)
	fmadds f0, f2, f4, f0
	stfs f0, 0x8(r8)
	bdnz L_g5_65
	L_g5_62:
	lwz r6, 0x1c(r4)
	lwz r5, 0x20(r4)
	lwz r7, 0x38(r30)
	slwi r6, r6, 1
	slwi r5, r5, 1
	lwz r9, 0x58(r31)
	add r8, r7, r6
	add r5, r8, r5
	addi r6, r5, 0x1
	subf r6, r8, r6
	cmplw r8, r5
	srwi r6, r6, 1
	bge L_g5_66
	srwi. r5, r6, 3
	mtctr r5
	beq L_g5_67
	L_g5_68:
	lbz r7, 0x0(r8)
	lbz r5, 0x1(r8)
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lbz r7, 0x2(r8)
	lbz r5, 0x3(r8)
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lbz r7, 0x4(r8)
	lbz r5, 0x5(r8)
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lbz r7, 0x6(r8)
	lbz r5, 0x7(r8)
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lbz r7, 0x8(r8)
	lbz r5, 0x9(r8)
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lbz r7, 0xa(r8)
	lbz r5, 0xb(r8)
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lbz r7, 0xc(r8)
	lbz r5, 0xd(r8)
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lbz r7, 0xe(r8)
	lbz r5, 0xf(r8)
	addi r8, r8, 0x10
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	bdnz L_g5_68
	andi. r6, r6, 0x7
	beq L_g5_66
	L_g5_67:
	mtctr r6
	L_g5_69:
	lbz r7, 0x0(r8)
	lbz r5, 0x1(r8)
	addi r8, r8, 0x2
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	bdnz L_g5_69
	L_g5_66:
	lwz r6, 0x24(r4)
	lwz r5, 0x28(r4)
	lwz r7, 0x3c(r30)
	slwi r6, r6, 2
	slwi r5, r5, 2
	lwz r8, 0x60(r31)
	add r7, r7, r6
	add r5, r7, r5
	addi r6, r5, 0x3
	subf r6, r7, r6
	cmplw r7, r5
	srwi r6, r6, 2
	bge L_g5_70
	srwi. r5, r6, 3
	mtctr r5
	beq L_g5_71
	L_g5_72:
	lbz r5, 0x0(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x1(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lbz r5, 0x4(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x5(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lbz r5, 0x8(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x9(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lbz r5, 0xc(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0xd(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lbz r5, 0x10(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x11(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lbz r5, 0x14(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x15(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lbz r5, 0x18(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x19(r7), 1, 4
	lfs f0, 0x0(r8)
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	lbz r5, 0x1c(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x1d(r7), 1, 4
	lfs f0, 0x0(r8)
	addi r7, r7, 0x20
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	bdnz L_g5_72
	andi. r6, r6, 0x7
	beq L_g5_70
	L_g5_71:
	mtctr r6
	L_g5_73:
	lbz r5, 0x0(r7)
	slwi r5, r5, 2
	add r8, r8, r5
	psq_l f1, 0x1(r7), 1, 4
	lfs f0, 0x0(r8)
	addi r7, r7, 0x4
	fmadds f0, f2, f1, f0
	stfs f0, 0x0(r8)
	bdnz L_g5_73
	L_g5_70:
	lwz r7, 0x14(r4)
	li r5, 0xc
	lwz r6, 0x18(r4)
	mulli r7, r7, 0xc
	lwz r8, 0x34(r30)
	lwz r9, 0x68(r31)
	mulli r6, r6, 0xc
	add r8, r8, r7
	add r7, r8, r6
	addi r6, r7, 0xb
	subf r6, r8, r6
	cmplw r8, r7
	divwu r6, r6, r5
	bge L_g5_74
	srwi. r5, r6, 2
	mtctr r5
	beq L_g5_75
	L_g5_76:
	lbz r7, 0x0(r8)
	lbz r5, 0x1(r8)
	mulli r7, r7, 0x18
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lfs f1, 0x4(r9)
	lfs f0, 0x4(r8)
	fadds f0, f1, f0
	stfs f0, 0x4(r9)
	lfs f1, 0x8(r9)
	lfs f0, 0x8(r8)
	fadds f0, f1, f0
	stfs f0, 0x8(r9)
	lbz r7, 0xc(r8)
	lbz r5, 0xd(r8)
	mulli r7, r7, 0x18
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lfs f1, 0x4(r9)
	lfs f0, 0x10(r8)
	fadds f0, f1, f0
	stfs f0, 0x4(r9)
	lfs f1, 0x8(r9)
	lfs f0, 0x14(r8)
	fadds f0, f1, f0
	stfs f0, 0x8(r9)
	lbz r7, 0x18(r8)
	lbz r5, 0x19(r8)
	mulli r7, r7, 0x18
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lfs f1, 0x4(r9)
	lfs f0, 0x1c(r8)
	fadds f0, f1, f0
	stfs f0, 0x4(r9)
	lfs f1, 0x8(r9)
	lfs f0, 0x20(r8)
	fadds f0, f1, f0
	stfs f0, 0x8(r9)
	lbz r7, 0x24(r8)
	lbz r5, 0x25(r8)
	mulli r7, r7, 0x18
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lfs f1, 0x4(r9)
	lfs f0, 0x28(r8)
	fadds f0, f1, f0
	stfs f0, 0x4(r9)
	lfs f0, 0x2c(r8)
	addi r8, r8, 0x30
	lfs f1, 0x8(r9)
	fadds f0, f1, f0
	stfs f0, 0x8(r9)
	bdnz L_g5_76
	andi. r6, r6, 0x3
	beq L_g5_74
	L_g5_75:
	mtctr r6
	L_g5_77:
	lbz r7, 0x0(r8)
	lbz r5, 0x1(r8)
	mulli r7, r7, 0x18
	add r9, r9, r7
	lbz r7, 0x0(r9)
	add r5, r7, r5
	stb r5, 0x0(r9)
	lfs f1, 0x4(r9)
	lfs f0, 0x4(r8)
	fadds f0, f1, f0
	stfs f0, 0x4(r9)
	lfs f0, 0x8(r8)
	addi r8, r8, 0xc
	lfs f1, 0x8(r9)
	fadds f0, f1, f0
	stfs f0, 0x8(r9)
	bdnz L_g5_77
	L_g5_74:
	addi r4, r4, 0x2c
	L_g5_56:
	cmplw r4, r0
	blt L_g5_57
	b L_g5_55
	L_g5_24:
	lfs f0, 0x40(r31)
	fcmpo cr0, f0, f31
	ble L_g5_55
	lfs f0, float_0_80419a48(r2)
	stfs f0, 0x40(r31)
	L_g5_55:
	cmpw r25, r26
	bne L_g5_78
	cmpwi r24, 0x0
	beq L_g5_79
	mulli r5, r24, 0xc
	lwz r4, 0x48(r31)
	mr r3, r28
	bl memcpy_as4
	L_g5_79:
	cmpwi r23, 0x0
	beq L_g5_80
	mulli r5, r23, 0xc
	lwz r4, 0x50(r31)
	mr r3, r27
	bl memcpy_as4
	L_g5_80:
	cmpwi r22, 0x0
	beq L_g5_81
	lwz r3, 0x64(r31)
	slwi r5, r22, 2
	lwz r4, 0x60(r31)
	bl memcpy_as4
	b L_g5_81
	L_g5_78:
	bgt L_g5_81
	mulli r26, r26, 0x2c
	lwz r0, 0x28(r30)
	lfs f0, float_0p0625_80419acc(r2)
	cmpwi r24, 0x0
	lwz r6, 0x2c(r30)
	add r20, r0, r26
	lwz r4, 0x4(r20)
	fmuls f30, f0, f31
	lwz r0, 0x8(r20)
	slwi r5, r4, 2
	lwz r4, 0x48(r31)
	add r21, r6, r5
	slwi r0, r0, 2
	add r18, r21, r0
	beq L_g5_82
	mulli r5, r24, 0xc
	mr r3, r28
	bl memcpy_as4
	L_g5_82:
	addi r4, r18, 0x3
	cmplw r21, r18
	subf r4, r21, r4
	srwi r4, r4, 2
	bge L_g5_83
	srwi. r0, r4, 2
	mtctr r0
	beq L_g5_84
	L_g5_85:
	lbz r0, 0x0(r21)
	mulli r0, r0, 0xc
	add r28, r28, r0
	psq_l f1, 0x1(r21), 1, 4
	psq_l f2, 0x2(r21), 1, 4
	psq_l f3, 0x3(r21), 1, 4
	lfs f0, 0x0(r28)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r28)
	lfs f0, 0x4(r28)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r28)
	lfs f0, 0x8(r28)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r28)
	lbz r0, 0x4(r21)
	mulli r0, r0, 0xc
	add r28, r28, r0
	psq_l f1, 0x5(r21), 1, 4
	psq_l f2, 0x6(r21), 1, 4
	psq_l f3, 0x7(r21), 1, 4
	lfs f0, 0x0(r28)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r28)
	lfs f0, 0x4(r28)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r28)
	lfs f0, 0x8(r28)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r28)
	lbz r0, 0x8(r21)
	mulli r0, r0, 0xc
	add r28, r28, r0
	psq_l f1, 0x9(r21), 1, 4
	psq_l f2, 0xa(r21), 1, 4
	psq_l f3, 0xb(r21), 1, 4
	lfs f0, 0x0(r28)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r28)
	lfs f0, 0x4(r28)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r28)
	lfs f0, 0x8(r28)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r28)
	lbz r0, 0xc(r21)
	mulli r0, r0, 0xc
	add r28, r28, r0
	psq_l f1, 0xd(r21), 1, 4
	psq_l f2, 0xe(r21), 1, 4
	psq_l f3, 0xf(r21), 1, 4
	addi r21, r21, 0x10
	lfs f0, 0x0(r28)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r28)
	lfs f0, 0x4(r28)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r28)
	lfs f0, 0x8(r28)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r28)
	bdnz L_g5_85
	andi. r4, r4, 0x3
	beq L_g5_83
	L_g5_84:
	mtctr r4
	L_g5_86:
	lbz r0, 0x0(r21)
	mulli r0, r0, 0xc
	add r28, r28, r0
	psq_l f1, 0x1(r21), 1, 4
	psq_l f2, 0x2(r21), 1, 4
	psq_l f3, 0x3(r21), 1, 4
	addi r21, r21, 0x4
	lfs f0, 0x0(r28)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r28)
	lfs f0, 0x4(r28)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r28)
	lfs f0, 0x8(r28)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r28)
	bdnz L_g5_86
	L_g5_83:
	lwz r4, 0xc(r20)
	cmpwi r23, 0x0
	lwz r0, 0x10(r20)
	mr r21, r27
	lwz r6, 0x30(r30)
	slwi r5, r4, 2
	slwi r0, r0, 2
	lwz r4, 0x50(r31)
	add r18, r6, r5
	add r19, r18, r0
	beq L_g5_87
	mulli r5, r23, 0xc
	mr r3, r27
	bl memcpy_as4
	L_g5_87:
	addi r4, r19, 0x3
	cmplw r18, r19
	subf r4, r18, r4
	srwi r4, r4, 2
	bge L_g5_88
	srwi. r0, r4, 2
	mtctr r0
	beq L_g5_89
	L_g5_90:
	lbz r0, 0x0(r18)
	mulli r0, r0, 0xc
	add r21, r21, r0
	psq_l f1, 0x1(r18), 1, 4
	psq_l f2, 0x2(r18), 1, 4
	psq_l f3, 0x3(r18), 1, 4
	lfs f0, 0x0(r21)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r21)
	lfs f0, 0x4(r21)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r21)
	lfs f0, 0x8(r21)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r21)
	lbz r0, 0x4(r18)
	mulli r0, r0, 0xc
	add r21, r21, r0
	psq_l f1, 0x5(r18), 1, 4
	psq_l f2, 0x6(r18), 1, 4
	psq_l f3, 0x7(r18), 1, 4
	lfs f0, 0x0(r21)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r21)
	lfs f0, 0x4(r21)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r21)
	lfs f0, 0x8(r21)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r21)
	lbz r0, 0x8(r18)
	mulli r0, r0, 0xc
	add r21, r21, r0
	psq_l f1, 0x9(r18), 1, 4
	psq_l f2, 0xa(r18), 1, 4
	psq_l f3, 0xb(r18), 1, 4
	lfs f0, 0x0(r21)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r21)
	lfs f0, 0x4(r21)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r21)
	lfs f0, 0x8(r21)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r21)
	lbz r0, 0xc(r18)
	mulli r0, r0, 0xc
	add r21, r21, r0
	psq_l f1, 0xd(r18), 1, 4
	psq_l f2, 0xe(r18), 1, 4
	psq_l f3, 0xf(r18), 1, 4
	addi r18, r18, 0x10
	lfs f0, 0x0(r21)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r21)
	lfs f0, 0x4(r21)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r21)
	lfs f0, 0x8(r21)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r21)
	bdnz L_g5_90
	andi. r4, r4, 0x3
	beq L_g5_88
	L_g5_89:
	mtctr r4
	L_g5_91:
	lbz r0, 0x0(r18)
	mulli r0, r0, 0xc
	add r21, r21, r0
	psq_l f1, 0x1(r18), 1, 4
	psq_l f2, 0x2(r18), 1, 4
	psq_l f3, 0x3(r18), 1, 4
	addi r18, r18, 0x4
	lfs f0, 0x0(r21)
	fmadds f0, f1, f30, f0
	stfs f0, 0x0(r21)
	lfs f0, 0x4(r21)
	fmadds f0, f2, f30, f0
	stfs f0, 0x4(r21)
	lfs f0, 0x8(r21)
	fmadds f0, f3, f30, f0
	stfs f0, 0x8(r21)
	bdnz L_g5_91
	L_g5_88:
	mulli r0, r25, 0x2c
	lwz r6, 0x28(r30)
	lwz r5, 0x24(r20)
	cmpwi r22, 0x0
	lwz r4, 0x28(r20)
	lfsx f1, r6, r26
	lfsx f0, r6, r0
	slwi r5, r5, 2
	lwz r6, 0x3c(r30)
	slwi r0, r4, 2
	fsubs f30, f1, f0
	lwz r4, 0x60(r31)
	add r20, r6, r5
	lwz r21, 0x64(r31)
	add r18, r20, r0
	beq L_g5_92
	mr r3, r21
	slwi r5, r22, 2
	bl memcpy_as4
	L_g5_92:
	addi r0, r18, 0x3
	fmuls f8, f31, f31
	subf r0, r20, r0
	srwi r0, r0, 2
	mtctr r0
	cmplw r20, r18
	bge L_g5_81
	L_g5_93:
	lbz r4, 0x3(r20)
	lbz r0, 0x0(r20)
	extsb r6, r4
	cmpwi r6, 0x59
	slwi r0, r0, 2
	add r21, r21, r0
	bge L_g5_94
	cmpwi r6, -0x59
	ble L_g5_94
	psq_l f6, 0x1(r20), 1, 4
	fmuls f7, f31, f8
	lbz r0, 0x2(r20)
	lis r4, (work+0x110)@ha
	lfs f0, float_2_80419a84(r2)
	addi r5, r4, (work+0x110)@l
	extsb r0, r0
	slwi r0, r0, 2
	fnmsubs f1, f0, f8, f7
	add r4, r5, r0
	lfs f2, float_3_80419ad0(r2)
	lfs f0, 0x164(r4)
	slwi r0, r6, 2
	fmuls f3, f2, f8
	lfs f4, float_neg2_80419ab8(r2)
	fadds f1, f31, f1
	fmuls f0, f30, f0
	lfs f2, float_0p0625_80419acc(r2)
	add r4, r5, r0
	lfs f5, 0x164(r4)
	fmadds f3, f4, f7, f3
	fmuls f2, f2, f6
	fmuls f0, f1, f0
	lfs f6, 0x0(r21)
	fsubs f4, f7, f8
	fmuls f1, f30, f5
	fmadds f0, f3, f2, f0
	fmadds f0, f4, f1, f0
	fadds f0, f6, f0
	stfs f0, 0x0(r21)
	L_g5_94:
	addi r20, r20, 0x4
	bdnz L_g5_93
	L_g5_81:
	stw r25, 0x3c(r31)
	stfs f31, 0x40(r31)
	lwz r0, 0x0(r31)
	rlwinm. r0, r0, 0, 28, 28
	beq L_g5_4
	li r3, 0x4
	bl camGetPtr
	lfs f3, 0x18(r3)
	lfs f2, 0xc(r3)
	lfs f1, 0x20(r3)
	lfs f0, 0x14(r3)
	fsubs f2, f3, f2
	fsubs f0, f1, f0
	fneg f1, f2
	fneg f2, f0
	bl atan2
	frsp f3, f1
	lfs f2, float_rad2deg_80419a94(r2)
	lfs f1, float_360_80419a98(r2)
	lfs f0, float_neg360_80419a9c(r2)
	fmuls f2, f2, f3
	b L_g5_95
	L_g5_96:
	fadds f2, f2, f1
	L_g5_95:
	fcmpo cr0, f2, f0
	blt L_g5_96
	lfs f1, float_360_80419a98(r2)
	b L_g5_97
	L_g5_98:
	fsubs f2, f2, f1
	L_g5_97:
	fcmpo cr0, f2, f1
	cror eq, gt, eq
	beq L_g5_98
	lfs f0, float_0_80419a48(r2)
	fcmpo cr0, f2, f0
	bge L_g5_99
	fadds f2, f2, f1
	L_g5_99:
	lfs f0, 0x74(r31)
	lfs f1, float_360_80419a98(r2)
	fsubs f2, f2, f0
	lfs f0, float_neg360_80419a9c(r2)
	b L_g5_100
	L_g5_101:
	fadds f2, f2, f1
	L_g5_100:
	fcmpo cr0, f2, f0
	blt L_g5_101
	lfs f0, float_360_80419a98(r2)
	b L_g5_102
	L_g5_103:
	fsubs f2, f2, f0
	L_g5_102:
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	beq L_g5_103
	lfs f0, float_90_80419aa0(r2)
	fcmpo cr0, f2, f0
	ble L_g5_104
	lfs f0, float_270_80419aa4(r2)
	fcmpo cr0, f2, f0
	cror eq, lt, eq
	beq L_g5_105
	L_g5_104:
	lfs f0, float_neg90_80419a90(r2)
	fcmpo cr0, f2, f0
	bge L_g5_106
	lfs f0, float_neg270_80419aa8(r2)
	fcmpo cr0, f2, f0
	cror eq, gt, eq
	bne L_g5_106
	L_g5_105:
	lfs f0, float_neg1_80419a8c(r2)
	stfs f0, 0x78(r31)
	b L_g5_4
	L_g5_106:
	lfs f0, float_1_80419a44(r2)
	stfs f0, 0x78(r31)
	L_g5_4:
	psq_l f31, 0x68(r1), 0, 0
	lfd f31, 0x60(r1)
	psq_l f30, 0x58(r1), 0, 0
	lfd f30, 0x50(r1)
	lmw r18, 0x18(r1)
	lwz r0, 0x74(r1)
	mtlr r0
	addi r1, r1, 0x70
	blr
}

asm GXColor animPoseGetMaterialEvtColor(s32 poseId) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	addi r0, r3, 0xf0
	lwzx r3, r4, r0
	blr
}

asm u32 animPoseGetMaterialLightFlag(s32 poseId) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	addi r0, r3, 0xec
	lwzx r3, r4, r0
	blr
}

asm u32 animPoseGetMaterialFlag(s32 poseId) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	addi r0, r3, 0xe8
	lwzx r3, r4, r0
	blr
}

asm void animPoseSetMaterialEvtColor(s32 poseId, GXColor color) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r5, wp(r13)
	lwz r0, 0x0(r4)
	lwz r4, 0x10(r5)
	addi r3, r3, 0xf0
	stwx r0, r4, r3
	blr
}

asm void animPoseSetMaterialLightFlagOff(s32 poseId, u32 mask) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r5, wp(r13)
	lwz r5, 0x10(r5)
	addi r3, r3, 0xec
	lwzx r0, r5, r3
	andc r0, r0, r4
	stwx r0, r5, r3
	blr
}

asm void animPoseSetMaterialLightFlagOn(s32 poseId, u32 mask) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r5, wp(r13)
	lwz r5, 0x10(r5)
	addi r3, r3, 0xec
	lwzx r0, r5, r3
	or r0, r0, r4
	stwx r0, r5, r3
	blr
}

asm void animPoseSetMaterialFlagOff(s32 poseId, u32 mask) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r5, wp(r13)
	lwz r5, 0x10(r5)
	addi r3, r3, 0xe8
	lwzx r0, r5, r3
	andc r0, r0, r4
	stwx r0, r5, r3
	blr
}

asm void animPoseSetMaterialFlagOn(s32 poseId, u32 mask) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r5, wp(r13)
	lwz r5, 0x10(r5)
	addi r3, r3, 0xe8
	lwzx r0, r5, r3
	or r0, r0, r4
	stwx r0, r5, r3
	blr
}

asm BOOL animPoseGetPeraEnd(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r0, r3, 0x170
	lwz r3, 0x10(r4)
	add r4, r3, r0
	lwz r0, 0x0(r4)
	rlwinm. r0, r0, 0, 28, 28
	bne L_g5_1
	li r3, 0x1
	blr
	L_g5_1:
	lfs f2, 0x7c(r4)
	lis r3, double_10_802c2f20@ha
	lfs f1, 0x74(r4)
	lfd f0, double_10_802c2f20@l(r3)
	fsubs f1, f2, f1
	fabs f1, f1
	fcmpo cr0, f1, f0
	mfcr r0
	srwi r3, r0, 31
	blr
}

asm f32 animPoseGetLoopTimes(s32 id) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	addi r0, r3, 0x84
	lfsx f1, r4, r0
	blr
}

asm f32 animPoseGetHeight(s32 poseId) {
	nofralloc
	stwu r1, -0x10(r1)
	mulli r4, r3, 0x170
	lis r0, 0x4330
	lfs f2, float_2_80419a84(r2)
	lwz r5, wp(r13)
	lis r3, double_to_int_802c2df0@ha
	stw r0, 0x8(r1)
	lwz r6, 0x10(r5)
	lwz r5, 0x0(r5)
	add r4, r6, r4
	lfd f1, double_to_int_802c2df0@l(r3)
	lwz r4, 0x10(r4)
	slwi r0, r4, 4
	add r3, r5, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xcc(r3)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f1
	fmuls f1, f2, f0
	addi r1, r1, 0x10
	blr
}

asm f32 animPoseGetRadius(s32 poseId) {
	nofralloc
	stwu r1, -0x10(r1)
	mulli r4, r3, 0x170
	lis r0, 0x4330
	lfs f2, float_2_80419a84(r2)
	lwz r5, wp(r13)
	lis r3, double_to_int_802c2df0@ha
	stw r0, 0x8(r1)
	lwz r6, 0x10(r5)
	lwz r5, 0x0(r5)
	add r4, r6, r4
	lfd f1, double_to_int_802c2df0@l(r3)
	lwz r4, 0x10(r4)
	slwi r0, r4, 4
	add r3, r5, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xc8(r3)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f1
	fmuls f1, f2, f0
	addi r1, r1, 0x10
	blr
}

asm void animPoseSetGXFunc(s32 poseId, void (*callback)(s32 wXluStage), BOOL disableDraw) {
	nofralloc
	lwz r6, wp(r13)
	mulli r0, r3, 0x170
	lwz r3, 0x10(r6)
	add r3, r3, r0
	stw r4, 0xe0(r3)
	stw r5, 0xe4(r3)
	blr
}

asm void animPoseSetEffectAnim(s32 poseId, const char* animName, BOOL reset) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	mulli r0, r3, 0x170
	stmw r25, 0x14(r1)
	mr r29, r4
	mr r30, r5
	lwz r6, wp(r13)
	lwz r4, 0x10(r6)
	add r3, r4, r0
	lwz r0, 0x90(r3)
	cmpwi r0, -0x1
	beq L_g5_1
	mulli r0, r0, 0x170
	lwz r3, 0x0(r6)
	mr. r25, r29
	add r31, r4, r0
	lwz r0, 0x10(r31)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r27, 0x0(r3)
	lwz r28, 0x148(r27)
	bge L_g5_2
	li r25, 0x0
	mr r26, r25
	b L_g5_3
	L_g5_4:
	lwz r0, 0x1ac(r27)
	mr r4, r29
	add r3, r0, r26
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_5
	b L_g5_6
	L_g5_5:
	addi r26, r26, 0x40
	addi r25, r25, 0x1
	L_g5_3:
	cmpw r25, r28
	blt L_g5_4
	b L_g5_7
	L_g5_2:
	cmpw r25, r28
	bge L_g5_7
	b L_g5_6
	L_g5_7:
	li r25, 0x0
	L_g5_6:
	cmpwi r30, 0x0
	bne L_g5_8
	lwz r0, 0x14(r31)
	cmpw r25, r0
	beq L_g5_1
	L_g5_8:
	stw r25, 0x14(r31)
	lwz r0, 0x90(r31)
	cmpwi r0, -0x1
	beq L_g5_9
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_9
	ori r0, r3, 0x4
	stw r0, 0x0(r31)
	L_g5_9:
	lwz r0, 0xc(r31)
	cmpwi r0, 0x0
	bne L_g5_10
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_11
	L_g5_10:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_11:
	stw r4, 0x1c(r31)
	li r4, -0x1
	lfs f0, float_0_80419a48(r2)
	li r0, 0x0
	stw r3, 0x18(r31)
	stw r4, 0x3c(r31)
	stfs f0, 0x40(r31)
	stw r0, 0x80(r31)
	stfs f0, 0x84(r31)
	L_g5_1:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void animPoseSetEffect(s32 poseId, const char* animName, BOOL someflag) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mulli r30, r3, 0x170
	mr r26, r4
	mr r29, r5
	lwz r7, wp(r13)
	lwz r6, 0x10(r7)
	add r31, r6, r30
	lwz r0, 0x90(r31)
	cmpwi r0, -0x1
	beq L_g5_1
	cmplwi r26, 0x0
	beq L_g5_2
	mulli r3, r0, 0x170
	lwz r5, 0x0(r7)
	addi r0, r3, 0x10
	lwzx r0, r6, r0
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r5, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_2
	lwz r0, 0x0(r31)
	extrwi r0, r0, 1, 30
	cmpw r0, r29
	beq L_g5_3
	L_g5_2:
	lwz r0, 0x90(r31)
	lwz r3, wp(r13)
	mulli r0, r0, 0x170
	lwz r3, 0x10(r3)
	add r27, r3, r0
	lwz r3, 0x8(r27)
	subi r0, r3, 0x1
	stw r0, 0x8(r27)
	lwz r0, 0x8(r27)
	cmpwi r0, 0x0
	bge L_g5_1
	lwz r3, wp(r13)
	lwz r0, 0x10(r27)
	lwz r3, 0x0(r3)
	slwi r0, r0, 4
	add r28, r3, r0
	lwz r3, 0x4(r28)
	subi r0, r3, 0x1
	stw r0, 0x4(r28)
	lwz r0, 0x4(r28)
	cmpwi r0, 0x0
	bgt L_g5_4
	li r0, 0x0
	stw r0, 0x0(r28)
	lwz r0, 0xc(r28)
	lwz r3, wp(r13)
	mulli r0, r0, 0xc
	lwz r3, 0x8(r3)
	add r25, r3, r0
	lwz r3, 0x4(r25)
	subi r0, r3, 0x1
	stw r0, 0x4(r25)
	lwz r0, 0x4(r25)
	cmpwi r0, 0x0
	bgt L_g5_5
	lwz r3, 0x8(r25)
	bl fileFree
	li r0, 0x0
	stw r0, 0x0(r25)
	L_g5_5:
	lwz r3, 0x8(r28)
	bl fileFree
	L_g5_4:
	li r0, 0x0
	stw r0, 0x0(r27)
	L_g5_1:
	cmplwi r26, 0x0
	bne L_g5_6
	li r0, -0x1
	addi r3, r30, 0xec
	stw r0, 0x90(r31)
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	lwzx r0, r4, r3
	clrrwi r0, r0, 1
	stwx r0, r4, r3
	b L_g5_3
	L_g5_6:
	lwz r4, 0xc(r31)
	mr r3, r26
	bl animPoseEntry
	cmpwi r3, -0x2
	bne L_g5_7
	b L_g5_8
	L_g5_7:
	lwz r6, wp(r13)
	mulli r5, r3, 0x170
	li r4, 0x1
	lwz r6, 0x10(r6)
	li r0, 0x0
	add r5, r6, r5
	stw r4, 0x4(r5)
	stw r0, 0x8(r5)
	lwz r0, 0x0(r5)
	ori r0, r0, 0x1
	stw r0, 0x0(r5)
	L_g5_8:
	stw r3, 0x90(r31)
	li r0, -0x1
	stw r0, 0x94(r31)
	lwz r0, 0xc(r31)
	cmpwi r0, 0x0
	bne L_g5_9
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_10
	L_g5_9:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_10:
	stw r4, 0x8c(r31)
	cmpwi r29, 0x0
	stw r3, 0x88(r31)
	beq L_g5_11
	lwz r0, 0x0(r31)
	ori r0, r0, 0x2
	stw r0, 0x0(r31)
	lwz r0, 0x0(r31)
	ori r0, r0, 0x4
	stw r0, 0x0(r31)
	b L_g5_12
	L_g5_11:
	lwz r0, 0x0(r31)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r31)
	L_g5_12:
	lwz r4, wp(r13)
	addi r3, r30, 0xec
	lwz r4, 0x10(r4)
	lwzx r0, r4, r3
	ori r0, r0, 0x1
	stwx r0, r4, r3
	L_g5_3:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void animPoseSetPaperAnim(s32 poseId, const char* animName, BOOL reset) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	mulli r0, r3, 0x170
	stmw r26, 0x8(r1)
	mr r29, r4
	mr. r30, r29
	lwz r6, wp(r13)
	lwz r5, 0x10(r6)
	lwz r4, 0x0(r6)
	add r31, r5, r0
	lwz r0, 0x90(r31)
	mulli r3, r0, 0x170
	addi r0, r3, 0x10
	lwzx r0, r5, r0
	slwi r0, r0, 4
	add r3, r4, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r27, 0x0(r3)
	lwz r28, 0x148(r27)
	bge L_g5_1
	li r30, 0x0
	mr r26, r30
	b L_g5_2
	L_g5_3:
	lwz r0, 0x1ac(r27)
	mr r4, r29
	add r3, r0, r26
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_4
	b L_g5_5
	L_g5_4:
	addi r26, r26, 0x40
	addi r30, r30, 0x1
	L_g5_2:
	cmpw r30, r28
	blt L_g5_3
	b L_g5_6
	L_g5_1:
	cmpw r30, r28
	bge L_g5_6
	b L_g5_5
	L_g5_6:
	li r30, 0x0
	L_g5_5:
	stw r30, 0x94(r31)
	lwz r0, 0xc(r31)
	cmpwi r0, 0x0
	bne L_g5_7
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_8
	L_g5_7:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_8:
	stw r4, 0x8c(r31)
	stw r3, 0x88(r31)
	lwz r3, 0x90(r31)
	cmpwi r3, -0x1
	beq L_g5_9
	mulli r4, r3, 0x170
	lwz r5, wp(r13)
	lwz r5, 0x10(r5)
	addi r0, r4, 0x4
	lwzx r0, r5, r0
	rlwinm. r0, r0, 0, 30, 30
	bne L_g5_9
	bl animPoseMain
	L_g5_9:
	lmw r26, 0x8(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animPoseSetPaperAnimGroup(s32 poseId, const char* animName, BOOL someflag) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	stmw r25, 0x14(r1)
	mulli r31, r3, 0x170
	mr. r25, r4
	mr r30, r5
	lwz r6, wp(r13)
	lwz r0, 0x10(r6)
	add r27, r0, r31
	bne L_g5_1
	li r0, -0x1
	addi r3, r31, 0xec
	stw r0, 0x90(r27)
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	lwzx r0, r4, r3
	clrrwi r0, r0, 1
	stwx r0, r4, r3
	b L_g5_2
	L_g5_1:
	li r29, 0x0
	lwz r28, 0xc(r27)
	mr r26, r29
	b L_g5_3
	L_g5_4:
	lwz r0, 0x10(r5)
	add r3, r0, r26
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_g5_5
	lwz r4, 0x4(r3)
	clrlwi. r0, r4, 31
	beq L_g5_5
	rlwinm. r0, r4, 0, 30, 30
	beq L_g5_5
	lwz r0, 0xc(r3)
	cmpw r0, r28
	bne L_g5_5
	lwz r0, 0x10(r3)
	mr r4, r25
	lwz r5, 0x0(r5)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r5, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	beq L_g5_6
	L_g5_5:
	addi r26, r26, 0x170
	addi r29, r29, 0x1
	L_g5_3:
	lwz r5, wp(r13)
	lwz r0, 0x14(r5)
	cmpw r29, r0
	blt L_g5_4
	L_g5_6:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r29, r0
	bne L_g5_7
	li r29, -0x1
	L_g5_7:
	stw r29, 0x90(r27)
	lwz r0, 0x90(r27)
	cmpwi r0, 0x0
	bge L_g5_8
	li r28, 0x0
	mr r26, r28
	b L_g5_9
	L_g5_10:
	lwz r0, 0x10(r5)
	add r3, r0, r26
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_g5_11
	lwz r4, 0x4(r3)
	clrlwi. r0, r4, 31
	beq L_g5_11
	rlwinm. r0, r4, 0, 30, 30
	beq L_g5_11
	lwz r0, 0xc(r3)
	cmpwi r0, 0x2
	bne L_g5_11
	lwz r0, 0x10(r3)
	mr r4, r25
	lwz r5, 0x0(r5)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r5, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	beq L_g5_12
	L_g5_11:
	addi r26, r26, 0x170
	addi r28, r28, 0x1
	L_g5_9:
	lwz r5, wp(r13)
	lwz r0, 0x14(r5)
	cmpw r28, r0
	blt L_g5_10
	L_g5_12:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r28, r0
	bne L_g5_13
	li r28, -0x1
	L_g5_13:
	stw r28, 0x90(r27)
	L_g5_8:
	li r0, -0x1
	stw r0, 0x94(r27)
	lwz r0, 0xc(r27)
	cmpwi r0, 0x0
	bne L_g5_14
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_15
	L_g5_14:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_15:
	stw r4, 0x8c(r27)
	cmpwi r30, 0x0
	stw r3, 0x88(r27)
	beq L_g5_16
	lwz r0, 0x0(r27)
	ori r0, r0, 0x2
	stw r0, 0x0(r27)
	lwz r0, 0x0(r27)
	ori r0, r0, 0x4
	stw r0, 0x0(r27)
	b L_g5_17
	L_g5_16:
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 31, 29
	stw r0, 0x0(r27)
	lwz r0, 0x0(r27)
	rlwinm r0, r0, 0, 30, 28
	stw r0, 0x0(r27)
	L_g5_17:
	lwz r4, wp(r13)
	addi r3, r31, 0xec
	lwz r4, 0x10(r4)
	lwzx r0, r4, r3
	ori r0, r0, 0x1
	stwx r0, r4, r3
	L_g5_2:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm s32 animPaperPoseGetId(const char* animName, s32 group) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	mr r30, r4
	stw r29, 0x14(r1)
	mr r29, r3
	stw r28, 0x10(r1)
	li r28, 0x0
	b L_g5_1
	L_g5_2:
	lwz r0, 0x10(r3)
	add r5, r0, r28
	lwz r0, 0x0(r5)
	clrlwi. r0, r0, 31
	beq L_g5_3
	lwz r4, 0x4(r5)
	clrlwi. r0, r4, 31
	beq L_g5_3
	rlwinm. r0, r4, 0, 30, 30
	beq L_g5_3
	lwz r0, 0xc(r5)
	cmpw r0, r30
	bne L_g5_3
	lwz r0, 0x10(r5)
	mr r4, r29
	lwz r5, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r5, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	beq L_g5_4
	L_g5_3:
	addi r28, r28, 0x170
	addi r31, r31, 0x1
	L_g5_1:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r31, r0
	blt L_g5_2
	L_g5_4:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r31, r0
	bne L_g5_5
	li r31, -0x1
	L_g5_5:
	lwz r0, 0x24(r1)
	mr r3, r31
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animPoseSetAnim(s32 poseId, const char* animName, BOOL reset) {
	nofralloc
	stwu r1, -0x30(r1)
	mflr r0
	stw r0, 0x34(r1)
	mulli r0, r3, 0x170
	stmw r25, 0x14(r1)
	mr r25, r4
	mr. r27, r25
	mr r26, r5
	lwz r6, wp(r13)
	lwz r4, 0x10(r6)
	lwz r3, 0x0(r6)
	add r31, r4, r0
	lwz r0, 0x10(r31)
	slwi r0, r0, 4
	add r3, r3, r0
	lwz r3, 0x8(r3)
	lwz r3, 0xa0(r3)
	lwz r29, 0x0(r3)
	lwz r30, 0x148(r29)
	bge L_g5_1
	li r27, 0x0
	mr r28, r27
	b L_g5_2
	L_g5_3:
	lwz r0, 0x1ac(r29)
	mr r4, r25
	add r3, r0, r28
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_4
	b L_g5_5
	L_g5_4:
	addi r28, r28, 0x40
	addi r27, r27, 0x1
	L_g5_2:
	cmpw r27, r30
	blt L_g5_3
	b L_g5_6
	L_g5_1:
	cmpw r27, r30
	bge L_g5_6
	b L_g5_5
	L_g5_6:
	li r27, 0x0
	L_g5_5:
	cmpwi r26, 0x0
	bne L_g5_7
	lwz r0, 0x14(r31)
	cmpw r27, r0
	beq L_g5_8
	L_g5_7:
	stw r27, 0x14(r31)
	lwz r0, 0x90(r31)
	cmpwi r0, -0x1
	beq L_g5_9
	lwz r3, 0x0(r31)
	rlwinm. r0, r3, 0, 30, 30
	beq L_g5_9
	ori r0, r3, 0x4
	stw r0, 0x0(r31)
	L_g5_9:
	lwz r0, 0xc(r31)
	cmpwi r0, 0x0
	bne L_g5_10
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_11
	L_g5_10:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_11:
	stw r4, 0x1c(r31)
	li r4, -0x1
	lfs f0, float_0_80419a48(r2)
	li r0, 0x0
	stw r3, 0x18(r31)
	stw r4, 0x3c(r31)
	stfs f0, 0x40(r31)
	stw r0, 0x80(r31)
	stfs f0, 0x84(r31)
	L_g5_8:
	lmw r25, 0x14(r1)
	lwz r0, 0x34(r1)
	mtlr r0
	addi r1, r1, 0x30
	blr
}

asm void animPoseSetStartTime(s32 poseId, OSTime startTime) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	addi r0, r3, 0x18
	add r3, r4, r0
	stw r6, 0x4(r3)
	stw r5, 0x0(r3)
	blr
}

asm void animPoseSetLocalTime(s32 poseId, f32 localTimeFrames) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	lfs f0, float_16p667_80419a60(r2)
	stw r0, 0x24(r1)
	mulli r0, r3, 0x170
	fmuls f1, f0, f1
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, wp(r13)
	lwz r3, 0x10(r3)
	add r29, r3, r0
	bl __cvt_dbl_usll
	lwz r0, 0xc(r29)
	mr r30, r4
	mr r31, r3
	cmpwi r0, 0x0
	bne L_g5_1
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_2
	L_g5_1:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_2:
	subfc r0, r30, r4
	stw r0, 0x1c(r29)
	subfe r0, r31, r3
	stw r0, 0x18(r29)
	lwz r0, 0x18(r29)
	lwz r3, 0x1c(r29)
	stw r3, 0x8c(r29)
	stw r0, 0x88(r29)
	lwz r0, 0x90(r29)
	cmpwi r0, -0x1
	beq L_g5_3
	lwz r3, wp(r13)
	mulli r0, r0, 0x170
	lwz r3, 0x10(r3)
	add r4, r3, r0
	lwz r0, 0x4(r4)
	rlwinm. r0, r0, 0, 30, 30
	bne L_g5_3
	lwz r0, 0x18(r29)
	lwz r3, 0x1c(r29)
	stw r3, 0x1c(r4)
	stw r0, 0x18(r4)
	L_g5_3:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animPoseSetLocalTimeRate(s32 poseId, f32 localTimeRate) {
	nofralloc
	mulli r3, r3, 0x170
	lwz r4, wp(r13)
	lwz r4, 0x10(r4)
	addi r0, r3, 0x44
	stfsx f1, r4, r0
	blr
}

asm void animPosePaperPeraOff(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r0, r3, 0x170
	lwz r4, 0x10(r4)
	add r3, r4, r0
	lwz r0, 0x90(r3)
	mulli r3, r0, 0x170
	lwzx r0, r4, r3
	rlwinm r0, r0, 0, 29, 27
	stwx r0, r4, r3
	blr
}

asm void animPosePaperPeraOn(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r0, r3, 0x170
	lwz r4, 0x10(r4)
	add r3, r4, r0
	lwz r0, 0x90(r3)
	mulli r0, r0, 0x170
	add r4, r4, r0
	lwz r0, 0x0(r4)
	ori r0, r0, 0x8
	stw r0, 0x0(r4)
	lfs f0, 0x70(r3)
	stfs f0, 0x70(r4)
	lfs f0, 0x74(r3)
	stfs f0, 0x74(r4)
	lfs f0, 0x7c(r3)
	stfs f0, 0x7c(r4)
	blr
}

asm void animPosePeraOff(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r3, r3, 0x170
	lwz r4, 0x10(r4)
	lwzx r0, r4, r3
	rlwinm r0, r0, 0, 29, 27
	stwx r0, r4, r3
	blr
}

asm void animPosePeraOn(s32 poseId) {
	nofralloc
	lwz r4, wp(r13)
	mulli r3, r3, 0x170
	lwz r4, 0x10(r4)
	lwzx r0, r4, r3
	ori r0, r0, 0x8
	stwx r0, r4, r3
	blr
}

asm BOOL animEffectAsync(const char* animName, u32 group) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	cmpwi r4, 0x1
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r27, r3
	beq L_g5_1
	bge L_g5_2
	cmpwi r4, 0x0
	bge L_g5_3
	b L_g5_4
	L_g5_2:
	cmpwi r4, 0x3
	bge L_g5_4
	b L_g5_5
	L_g5_3:
	li r3, 0x1
	bl fileSetCurrentArchiveType
	b L_g5_4
	L_g5_1:
	li r3, 0x2
	bl fileSetCurrentArchiveType
	b L_g5_4
	L_g5_5:
	li r3, 0x0
	bl fileSetCurrentArchiveType
	L_g5_4:
	mr r7, r27
	li r3, 0x5
	li r4, 0x0
	la r5, str_80419A54(r2)
	la r6, str_80419A5C(r2)
	crclr 6
	bl fileAsyncf
	lwz r4, wp(r13)
	mr r31, r3
	li r29, 0x0
	lwz r3, 0x100(r4)
	lwz r3, 0xa0(r3)
	lwz r28, 0x4(r3)
	lwz r30, 0x0(r3)
	b L_g5_6
	L_g5_7:
	mr r3, r30
	mr r4, r27
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_8
	addi r7, r30, 0x20
	b L_g5_9
	L_g5_8:
	addi r30, r30, 0x20
	addi r29, r29, 0x20
	L_g5_6:
	cmpw r29, r28
	blt L_g5_7
	la r7, zero_80419a50(r2)
	L_g5_9:
	lis r3, str_802C2DE8@ha
	li r4, 0x0
	addi r5, r3, str_802C2DE8@l
	la r6, str_80419A5C(r2)
	li r3, 0x4
	crclr 6
	bl fileAsyncf
	cmpwi r31, -0x1
	bne L_g5_10
	li r3, 0x1
	b L_g5_11
	L_g5_10:
	cmplwi r31, 0x0
	bne L_g5_12
	li r3, 0x0
	b L_g5_11
	L_g5_12:
	cmpwi r3, -0x1
	bne L_g5_13
	li r3, 0x1
	b L_g5_11
	L_g5_13:
	cmplwi r3, 0x0
	bne L_g5_14
	li r3, 0x0
	b L_g5_11
	L_g5_14:
	li r3, 0x1
	L_g5_11:
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 animPaperPoseEntry(const char* animName, s32 group) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	li r31, 0x0
	stw r30, 0x18(r1)
	mr r30, r31
	stw r29, 0x14(r1)
	mr r29, r4
	stw r28, 0x10(r1)
	mr r28, r3
	b L_g5_1
	L_g5_2:
	lwz r0, 0x10(r5)
	add r3, r0, r30
	lwz r0, 0x0(r3)
	clrlwi. r0, r0, 31
	beq L_g5_3
	lwz r4, 0x4(r3)
	clrlwi. r0, r4, 31
	beq L_g5_3
	rlwinm. r0, r4, 0, 30, 30
	beq L_g5_3
	lwz r0, 0xc(r3)
	cmpw r0, r29
	bne L_g5_3
	lwz r0, 0x10(r3)
	mr r4, r28
	lwz r5, 0x0(r5)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r5, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	beq L_g5_4
	L_g5_3:
	addi r30, r30, 0x170
	addi r31, r31, 0x1
	L_g5_1:
	lwz r5, wp(r13)
	lwz r0, 0x14(r5)
	cmpw r31, r0
	blt L_g5_2
	L_g5_4:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r31, r0
	bne L_g5_5
	li r31, -0x1
	L_g5_5:
	cmpwi r31, 0x0
	blt L_g5_6
	mulli r4, r31, 0x170
	lwz r6, 0x10(r3)
	mr r3, r31
	addi r5, r4, 0x8
	lwzx r4, r6, r5
	addi r0, r4, 0x1
	stwx r0, r6, r5
	b L_g5_7
	L_g5_6:
	mr r3, r28
	mr r4, r29
	bl animPoseEntry
	cmpwi r3, -0x2
	bne L_g5_8
	b L_g5_7
	L_g5_8:
	lwz r6, wp(r13)
	mulli r5, r3, 0x170
	li r4, 0x3
	lwz r6, 0x10(r6)
	li r0, 0x0
	add r5, r6, r5
	stw r4, 0x4(r5)
	stw r0, 0x8(r5)
	lwz r0, 0x0(r5)
	ori r0, r0, 0x1
	stw r0, 0x0(r5)
	L_g5_7:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm s32 animPoseEntry(const char *animName, s32 type) {
	nofralloc
	stwu r1, -0x140(r1)
	mflr r0
	stw r0, 0x144(r1)
	stmw r21, 0x114(r1)
	mr r28, r4
	lis r4, str_802C2A98@ha
	mr r29, r3
	cmpwi r28, 0x1
	addi r27, r4, str_802C2A98@l
	beq L_g5_1
	bge L_g5_2
	cmpwi r28, 0x0
	bge L_g5_3
	b L_g5_4
	L_g5_2:
	cmpwi r28, 0x3
	bge L_g5_4
	b L_g5_5
	L_g5_3:
	li r3, 0x1
	bl fileSetCurrentArchiveType
	b L_g5_4
	L_g5_1:
	li r3, 0x2
	bl fileSetCurrentArchiveType
	b L_g5_4
	L_g5_5:
	li r3, 0x0
	bl fileSetCurrentArchiveType
	L_g5_4:
	lwz r5, wp(r13)
	li r30, 0x0
	mr r4, r30
	lwz r0, 0x14(r5)
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_6
	L_g5_7:
	lwz r0, 0x10(r5)
	add r3, r0, r4
	lwz r0, 0x0(r3)
	cmplwi r0, 0x0
	bne L_g5_8
	mr r31, r3
	b L_g5_9
	L_g5_8:
	addi r4, r4, 0x170
	addi r30, r30, 0x1
	bdnz L_g5_7
	L_g5_6:
	li r31, 0x0
	li r30, -0x1
	L_g5_9:
	lwz r0, 0x0(r31)
	li r25, 0x0
	mr r22, r25
	ori r0, r0, 0x1
	stw r0, 0x0(r31)
	stw r25, 0x4(r31)
	stw r25, 0x8(r31)
	lwz r3, wp(r13)
	lwz r23, 0x4(r3)
	b L_g5_10
	L_g5_11:
	lwz r3, wp(r13)
	lwz r0, 0x0(r3)
	add r21, r0, r22
	lwz r0, 0x0(r21)
	cmplwi r0, 0x0
	beq L_g5_12
	lwz r3, 0x8(r21)
	mr r4, r29
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	addi r3, r3, 0x4
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_12
	lwz r3, 0x4(r21)
	addi r0, r3, 0x1
	stw r0, 0x4(r21)
	b L_g5_13
	L_g5_12:
	addi r22, r22, 0x10
	addi r25, r25, 0x1
	L_g5_10:
	cmpw r25, r23
	blt L_g5_11
	lwz r4, wp(r13)
	li r25, 0x0
	mr r3, r25
	lwz r0, 0x4(r4)
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_14
	L_g5_15:
	lwz r0, 0x0(r4)
	add r26, r0, r3
	lwz r0, 0x0(r26)
	cmplwi r0, 0x0
	bne L_g5_16
	b L_g5_17
	L_g5_16:
	addi r3, r3, 0x10
	addi r25, r25, 0x1
	bdnz L_g5_15
	L_g5_14:
	li r26, 0x0
	li r25, -0x1
	L_g5_17:
	li r0, 0x1
	mr r6, r29
	stw r0, 0x0(r26)
	li r3, 0x5
	la r4, str_80419A54(r2)
	la r5, str_80419A5C(r2)
	lwz r7, 0x4(r26)
	addi r0, r7, 0x1
	stw r0, 0x4(r26)
	crclr 6
	bl fileAllocf
	stw r3, 0x8(r26)
	lwz r3, 0x8(r26)
	cmplwi r3, 0x0
	bne L_g5_18
	li r0, 0x0
	li r25, -0x2
	stw r0, 0x0(r26)
	lwz r3, 0x4(r26)
	subi r0, r3, 0x1
	stw r0, 0x4(r26)
	b L_g5_13
	L_g5_18:
	lwz r4, 0xa0(r3)
	lwz r5, 0x0(r4)
	cmplwi r5, 0x0
	bne L_g5_19
	bl fileFree
	li r0, 0x0
	li r25, -0x2
	stw r0, 0x0(r26)
	lwz r3, 0x4(r26)
	subi r0, r3, 0x1
	stw r0, 0x4(r26)
	b L_g5_13
	L_g5_19:
	addi r3, r1, 0x8
	addi r4, r27, 0x350
	addi r6, r5, 0x44
	la r5, str_80419A5C(r2)
	crclr 6
	bl sprintf
	lwz r3, wp(r13)
	li r22, 0x0
	mr r21, r22
	lwz r23, 0xc(r3)
	b L_g5_20
	L_g5_21:
	lwz r3, wp(r13)
	lwz r0, 0x8(r3)
	add r24, r0, r21
	lwz r0, 0x0(r24)
	cmplwi r0, 0x0
	beq L_g5_22
	lwz r3, 0x8(r24)
	cmplwi r3, 0x0
	beq L_g5_22
	addi r3, r3, 0x20
	addi r4, r1, 0x8
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_22
	lwz r3, 0x4(r24)
	addi r0, r3, 0x1
	stw r0, 0x4(r24)
	b L_g5_23
	L_g5_22:
	addi r21, r21, 0xc
	addi r22, r22, 0x1
	L_g5_20:
	cmpw r22, r23
	blt L_g5_21
	lwz r4, wp(r13)
	li r22, 0x0
	mr r3, r22
	lwz r0, 0xc(r4)
	mtctr r0
	cmpwi r0, 0x0
	ble L_g5_24
	L_g5_25:
	lwz r0, 0x8(r4)
	add r21, r0, r3
	lwz r0, 0x0(r21)
	cmplwi r0, 0x0
	bne L_g5_26
	b L_g5_27
	L_g5_26:
	addi r3, r3, 0xc
	addi r22, r22, 0x1
	bdnz L_g5_25
	L_g5_24:
	li r21, 0x0
	li r22, -0x1
	L_g5_27:
	li r0, 0x1
	addi r3, r1, 0x8
	stw r0, 0x0(r21)
	li r4, 0x4
	lwz r5, 0x4(r21)
	addi r0, r5, 0x1
	stw r0, 0x4(r21)
	bl fileAlloc
	stw r3, 0x8(r21)
	L_g5_23:
	stw r22, 0xc(r26)
	L_g5_13:
	stw r25, 0x10(r31)
	lwz r0, 0x10(r31)
	cmpwi r0, -0x2
	bne L_g5_28
	li r0, 0x0
	li r3, -0x2
	stw r0, 0x0(r31)
	b L_g5_29
	L_g5_28:
	li r0, 0x0
	cmpwi r28, 0x0
	stw r0, 0x14(r31)
	bne L_g5_30
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_31
	L_g5_30:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_31:
	stw r4, 0x1c(r31)
	li r4, -0x1
	lfs f0, float_0_80419a48(r2)
	li r0, 0x0
	stw r3, 0x18(r31)
	mr r3, r31
	stw r4, 0x3c(r31)
	stfs f0, 0x40(r31)
	stw r0, 0x80(r31)
	stfs f0, 0x84(r31)
	stfs f0, 0x70(r31)
	stfs f0, 0x74(r31)
	stfs f0, 0x7c(r31)
	stw r28, 0xc(r31)
	stw r4, 0x90(r31)
	bl animPose_AllocBuffer
	li r0, 0x0
	lfs f1, float_1_80419a44(r2)
	stw r0, 0xe0(r31)
	addi r3, r31, 0x124
	lfs f0, float_0_80419a48(r2)
	stw r0, 0xe4(r31)
	stw r0, 0xe8(r31)
	stw r0, 0xec(r31)
	lwz r0, dat_80419a2c(r2)
	stw r0, 0xf0(r31)
	lwz r0, dat_80419a30(r2)
	stw r0, 0xf4(r31)
	stfs f1, 0xfc(r31)
	stfs f1, 0xf8(r31)
	stfs f0, 0x100(r31)
	stfs f1, 0x44(r31)
	bl PSMTXIdentity
	mr r3, r29
	addi r4, r27, 0x490
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_32
	li r3, 0x1
	la r0, vivihimoTailGroupNo(r13)
	stw r3, 0x11c(r31)
	stw r0, 0x120(r31)
	b L_g5_33
	L_g5_32:
	mr r3, r29
	addi r4, r27, 0x49c
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_34
	li r0, 0x1
	la r3, vivihimoTailGroupNo(r13)
	stw r0, 0x11c(r31)
	addi r0, r3, 0x4
	stw r0, 0x120(r31)
	b L_g5_33
	L_g5_34:
	mr r3, r29
	addi r4, r27, 0x4a8
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_35
	li r0, 0x2
	la r3, vivihimoTailGroupNo(r13)
	stw r0, 0x11c(r31)
	addi r0, r3, 0x8
	stw r0, 0x120(r31)
	b L_g5_33
	L_g5_35:
	mr r3, r29
	addi r4, r27, 0x4b4
	bl strcmp
	cmpwi r3, 0x0
	bne L_g5_36
	li r0, 0x3
	la r3, vivihimoTailGroupNo(r13)
	stw r0, 0x11c(r31)
	addi r0, r3, 0xc
	stw r0, 0x120(r31)
	b L_g5_33
	L_g5_36:
	li r3, 0x0
	la r0, g5__dummy_s614(r13)
	stw r3, 0x11c(r31)
	stw r0, 0x120(r31)
	L_g5_33:
	li r0, 0x0
	mr r3, r30
	stw r0, 0x154(r31)
	stw r0, 0x158(r31)
	L_g5_29:
	lmw r21, 0x114(r1)
	lwz r0, 0x144(r1)
	mtlr r0
	addi r1, r1, 0x140
	blr
}

asm void animPoseBattleInit(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	li r0, 0x1
	lwz r3, wp(r13)
	stw r0, 0x10c(r3)
	bl animPoseRefresh
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void animPoseRefresh(void) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, wp(r13)
	lwz r0, 0x104(r3)
	cmplwi r0, 0x0
	bne L_g5_1
	li r3, 0x0
	lis r4, 0x18
	bl __memAlloc
	lwz r4, wp(r13)
	stw r3, 0x104(r4)
	L_g5_1:
	lwz r3, wp(r13)
	li r30, 0x0
	li r31, 0x0
	lwz r0, 0x104(r3)
	stw r0, 0x108(r3)
	b L_g5_2
	L_g5_3:
	lwz r0, 0x10(r3)
	add r29, r0, r31
	lwz r0, 0x0(r29)
	cmplwi r0, 0x0
	beq L_g5_4
	lwz r4, 0x10c(r3)
	cmpwi r4, 0x0
	beq L_g5_5
	lwz r0, 0xc(r29)
	cmpwi r0, 0x0
	beq L_g5_4
	L_g5_5:
	cmpwi r4, 0x0
	bne L_g5_6
	lwz r0, 0xc(r29)
	cmpwi r0, 0x1
	beq L_g5_4
	L_g5_6:
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf0(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x48(r29)
	lwz r3, wp(r13)
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf0(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x4c(r29)
	lwz r3, wp(r13)
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf8(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x50(r29)
	lwz r3, wp(r13)
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf8(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x54(r29)
	lwz r3, wp(r13)
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0x13c(r3)
	bl testAlloc
	stw r3, 0x58(r29)
	lwz r0, 0x58(r29)
	stw r0, 0x5c(r29)
	lwz r3, wp(r13)
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0x140(r3)
	slwi r3, r0, 2
	bl testAlloc
	stw r3, 0x60(r29)
	lwz r3, wp(r13)
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0x140(r3)
	slwi r3, r0, 2
	bl testAlloc
	stw r3, 0x64(r29)
	lwz r3, wp(r13)
	lwz r0, 0x10(r29)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0x12c(r3)
	mulli r3, r0, 0x18
	bl testAlloc
	stw r3, 0x68(r29)
	li r0, -0x1
	lwz r3, 0x68(r29)
	stw r3, 0x6c(r29)
	stw r0, 0x3c(r29)
	stw r0, 0x3c(r29)
	L_g5_4:
	addi r31, r31, 0x170
	addi r30, r30, 0x1
	L_g5_2:
	lwz r3, wp(r13)
	lwz r0, 0x14(r3)
	cmpw r30, r0
	blt L_g5_3
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animPose_AllocBuffer(AnimationPose* pose) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	stmw r27, 0xc(r1)
	mr r31, r3
	lwz r5, wp(r13)
	lwz r0, 0x10(r3)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf0(r4)
	mulli r30, r0, 0xc
	clrlwi. r0, r30, 27
	beq L_g5_1
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_1:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_2
	bl initTestHeap
	li r28, 0x0
	mr r27, r28
	b L_g5_3
	L_g5_4:
	lwz r0, 0x10(r4)
	add r29, r0, r27
	lwz r0, 0x0(r29)
	cmplwi r0, 0x0
	beq L_g5_5
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_6
	lwz r0, 0xc(r29)
	cmpwi r0, 0x0
	beq L_g5_5
	L_g5_6:
	cmpwi r3, 0x0
	bne L_g5_7
	lwz r0, 0xc(r29)
	cmpwi r0, 0x1
	beq L_g5_5
	L_g5_7:
	mr r3, r29
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r29)
	L_g5_5:
	addi r27, r27, 0x170
	addi r28, r28, 0x1
	L_g5_3:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r28, r0
	blt L_g5_4
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_8
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_8:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_2
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_2:
	stw r3, 0x48(r31)
	lwz r5, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf0(r4)
	mulli r30, r0, 0xc
	clrlwi. r0, r30, 27
	beq L_g5_9
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_9:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_10
	bl initTestHeap
	li r29, 0x0
	mr r27, r29
	b L_g5_11
	L_g5_12:
	lwz r0, 0x10(r4)
	add r28, r0, r27
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_13
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_14
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_13
	L_g5_14:
	cmpwi r3, 0x0
	bne L_g5_15
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_13
	L_g5_15:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_13:
	addi r27, r27, 0x170
	addi r29, r29, 0x1
	L_g5_11:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_12
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_16
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_16:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_10
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_10:
	stw r3, 0x4c(r31)
	lwz r5, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf8(r4)
	mulli r30, r0, 0xc
	clrlwi. r0, r30, 27
	beq L_g5_17
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_17:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_18
	bl initTestHeap
	li r29, 0x0
	mr r27, r29
	b L_g5_19
	L_g5_20:
	lwz r0, 0x10(r4)
	add r28, r0, r27
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_21
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_22
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_21
	L_g5_22:
	cmpwi r3, 0x0
	bne L_g5_23
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_21
	L_g5_23:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_21:
	addi r27, r27, 0x170
	addi r29, r29, 0x1
	L_g5_19:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_20
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_24
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_24:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_18
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_18:
	stw r3, 0x50(r31)
	lwz r5, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0xf8(r4)
	mulli r30, r0, 0xc
	clrlwi. r0, r30, 27
	beq L_g5_25
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_25:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_26
	bl initTestHeap
	li r29, 0x0
	mr r27, r29
	b L_g5_27
	L_g5_28:
	lwz r0, 0x10(r4)
	add r28, r0, r27
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_29
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_30
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_29
	L_g5_30:
	cmpwi r3, 0x0
	bne L_g5_31
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_29
	L_g5_31:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_29:
	addi r27, r27, 0x170
	addi r29, r29, 0x1
	L_g5_27:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_28
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_32
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_32:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_26
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_26:
	stw r3, 0x54(r31)
	lwz r5, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r30, 0x13c(r4)
	clrlwi. r0, r30, 27
	beq L_g5_33
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_33:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_34
	bl initTestHeap
	li r29, 0x0
	mr r27, r29
	b L_g5_35
	L_g5_36:
	lwz r0, 0x10(r4)
	add r28, r0, r27
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_37
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_38
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_37
	L_g5_38:
	cmpwi r3, 0x0
	bne L_g5_39
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_37
	L_g5_39:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_37:
	addi r27, r27, 0x170
	addi r29, r29, 0x1
	L_g5_35:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_36
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_40
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_40:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_34
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_34:
	stw r3, 0x58(r31)
	lwz r0, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r5, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0x140(r4)
	clrlslwi. r4, r0, 29, 2
	slwi r30, r0, 2
	beq L_g5_41
	subfic r0, r4, 0x20
	add r30, r30, r0
	L_g5_41:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_42
	bl initTestHeap
	li r29, 0x0
	mr r27, r29
	b L_g5_43
	L_g5_44:
	lwz r0, 0x10(r4)
	add r28, r0, r27
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_45
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_46
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_45
	L_g5_46:
	cmpwi r3, 0x0
	bne L_g5_47
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_45
	L_g5_47:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_45:
	addi r27, r27, 0x170
	addi r29, r29, 0x1
	L_g5_43:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_44
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_48
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_48:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_42
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_42:
	stw r3, 0x60(r31)
	lwz r5, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0x140(r4)
	clrlslwi. r4, r0, 29, 2
	slwi r30, r0, 2
	beq L_g5_49
	subfic r0, r4, 0x20
	add r30, r30, r0
	L_g5_49:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_50
	bl initTestHeap
	li r29, 0x0
	mr r27, r29
	b L_g5_51
	L_g5_52:
	lwz r0, 0x10(r4)
	add r28, r0, r27
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_53
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_54
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_53
	L_g5_54:
	cmpwi r3, 0x0
	bne L_g5_55
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_53
	L_g5_55:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_53:
	addi r27, r27, 0x170
	addi r29, r29, 0x1
	L_g5_51:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_52
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_56
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_56:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_50
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_50:
	stw r3, 0x64(r31)
	lwz r5, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r5)
	slwi r0, r0, 4
	lwz r3, 0x108(r5)
	add r4, r4, r0
	lwz r4, 0x8(r4)
	lwz r4, 0xa0(r4)
	lwz r4, 0x0(r4)
	lwz r0, 0x12c(r4)
	mulli r30, r0, 0x18
	clrlwi. r0, r30, 27
	beq L_g5_57
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_57:
	lwz r0, 0x108(r5)
	add r0, r0, r30
	stw r0, 0x108(r5)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_58
	bl initTestHeap
	li r29, 0x0
	mr r27, r29
	b L_g5_59
	L_g5_60:
	lwz r0, 0x10(r4)
	add r28, r0, r27
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_61
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_62
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_61
	L_g5_62:
	cmpwi r3, 0x0
	bne L_g5_63
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_61
	L_g5_63:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_61:
	addi r27, r27, 0x170
	addi r29, r29, 0x1
	L_g5_59:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_60
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_64
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_64:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_58
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_58:
	stw r3, 0x68(r31)
	li r0, -0x1
	lwz r3, 0x68(r31)
	stw r3, 0x6c(r31)
	stw r0, 0x3c(r31)
	lmw r27, 0xc(r1)
	lwz r0, 0x24(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void animMain(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	lis r3, animPaperPoseDisp@ha
	lfs f1, float_0_80419a48(r2)
	stw r0, 0x14(r1)
	addi r5, r3, animPaperPoseDisp@l
	li r3, 0x0
	li r4, 0x1
	li r6, 0x0
	bl dispEntry
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm void animInit(void) {
	nofralloc
	stwu r1, -0x40(r1)
	mflr r0
	stw r0, 0x44(r1)
	stfd f31, 0x30(r1)
	psq_st f31, 0x38(r1), 0, 0
	stfd f30, 0x20(r1)
	psq_st f30, 0x28(r1), 0, 0
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	lwz r3, wp(r13)
	li r7, 0x40
	li r6, 0x100
	li r5, 0x400
	stw r7, 0x4(r3)
	li r0, 0x0
	li r3, 0x0
	lwz r4, wp(r13)
	stw r7, 0xc(r4)
	lwz r4, wp(r13)
	stw r6, 0x14(r4)
	lwz r4, wp(r13)
	stw r5, 0xf0(r4)
	lwz r4, wp(r13)
	stw r0, 0xf4(r4)
	lwz r4, wp(r13)
	lwz r0, 0x4(r4)
	slwi r4, r0, 4
	bl __memAlloc
	lwz r4, wp(r13)
	stw r3, 0x0(r4)
	li r3, 0x0
	lwz r4, wp(r13)
	lwz r0, 0xc(r4)
	mulli r4, r0, 0xc
	bl __memAlloc
	lwz r4, wp(r13)
	stw r3, 0x8(r4)
	li r3, 0x0
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	mulli r4, r0, 0x170
	bl __memAlloc
	lwz r4, wp(r13)
	li r0, 0x0
	stw r3, 0x10(r4)
	li r3, 0x0
	lwz r4, wp(r13)
	stw r0, 0xe8(r4)
	lwz r4, wp(r13)
	lwz r0, 0xf0(r4)
	mulli r4, r0, 0xc
	bl __memAlloc
	lwz r5, wp(r13)
	li r4, 0x0
	li r0, 0x1
	stw r3, 0xec(r5)
	lwz r3, wp(r13)
	stw r4, 0x30(r3)
	lwz r3, wp(r13)
	stw r4, 0x34(r3)
	lwz r3, wp(r13)
	stw r4, 0x38(r3)
	lwz r3, wp(r13)
	stw r4, 0x24(r3)
	lwz r3, wp(r13)
	stw r4, 0x28(r3)
	lwz r3, wp(r13)
	stw r4, 0x2c(r3)
	lwz r3, wp(r13)
	stw r4, 0xcc(r3)
	lwz r3, wp(r13)
	stw r4, 0xd0(r3)
	lwz r3, wp(r13)
	stw r4, 0xd4(r3)
	lwz r3, wp(r13)
	stw r0, 0xd8(r3)
	lwz r3, wp(r13)
	stw r0, 0xdc(r3)
	lwz r3, wp(r13)
	stw r4, 0x104(r3)
	lwz r3, wp(r13)
	stw r4, 0x10c(r3)
	lwz r3, wp(r13)
	lwz r0, 0x104(r3)
	cmplwi r0, 0x0
	bne L_g5_1
	li r3, 0x0
	lis r4, 0x18
	bl __memAlloc
	lwz r4, wp(r13)
	stw r3, 0x104(r4)
	L_g5_1:
	lwz r5, wp(r13)
	lis r3, double_to_int_802c2df0@ha
	lis r4, (work+0x110)@ha
	lfs f30, float_deg2rad_80419ad4(r2)
	lwz r0, 0x104(r5)
	addi r30, r4, (work+0x110)@l
	lfd f31, double_to_int_802c2df0@l(r3)
	li r29, 0x0
	stw r0, 0x108(r5)
	lis r31, 0x4330
	L_g5_2:
	subi r0, r29, 0x59
	stw r31, 0x8(r1)
	xoris r0, r0, 0x8000
	stw r0, 0xc(r1)
	lfd f0, 0x8(r1)
	fsubs f0, f0, f31
	fmuls f1, f30, f0
	bl tan
	frsp f0, f1
	addi r29, r29, 0x1
	cmpwi r29, 0xb2
	stfs f0, 0x0(r30)
	addi r30, r30, 0x4
	blt L_g5_2
	lis r4, str_802C2F58@ha
	li r3, 0x0
	addi r4, r4, str_802C2F58@l
	crclr 6
	bl fileAllocf
	mr. r29, r3
	beq L_g5_3
	lwz r4, 0xa0(r29)
	la r3, vivihimoData(r13)
	lwz r3, 0x4(r3)
	li r5, 0xc00
	lwz r4, 0x0(r4)
	bl memcpy_as4
	lwz r4, 0xa0(r29)
	la r3, vivihimoTailGroupNo(r13)
	li r5, 0x10
	lwz r4, 0x0(r4)
	addi r4, r4, 0xc00
	bl memcpy_as4
	mr r3, r29
	bl fileFree
	L_g5_3:
	li r3, 0x0
	bl fileSetCurrentArchiveType
	lis r4, str_802C2F68@ha
	li r3, 0x0
	addi r4, r4, str_802C2F68@l
	crclr 6
	bl fileAllocf
	lwz r4, wp(r13)
	stw r3, 0x100(r4)
	psq_l f31, 0x38(r1), 0, 0
	lfd f31, 0x30(r1)
	psq_l f30, 0x28(r1), 0, 0
	lfd f30, 0x20(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r0, 0x44(r1)
	lwz r29, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x40
	blr
}

asm void* testAlloc(u32 size) {
	nofralloc
	stwu r1, -0x20(r1)
	mflr r0
	stw r0, 0x24(r1)
	clrlwi. r0, r3, 27
	stw r31, 0x1c(r1)
	stw r30, 0x18(r1)
	stw r29, 0x14(r1)
	stw r28, 0x10(r1)
	mr r28, r3
	lwz r4, wp(r13)
	lwz r3, 0x108(r4)
	beq L_g5_1
	subfic r0, r0, 0x20
	add r28, r28, r0
	L_g5_1:
	lwz r0, 0x108(r4)
	add r0, r0, r28
	stw r0, 0x108(r4)
	lwz r4, wp(r13)
	lwz r5, 0x104(r4)
	lwz r4, 0x108(r4)
	addis r0, r5, 0x18
	cmplw r4, r0
	blt L_g5_2
	cmplwi r5, 0x0
	bne L_g5_3
	li r3, 0x0
	lis r4, 0x18
	bl __memAlloc
	lwz r4, wp(r13)
	stw r3, 0x104(r4)
	L_g5_3:
	lwz r3, wp(r13)
	li r30, 0x0
	mr r29, r30
	lwz r0, 0x104(r3)
	stw r0, 0x108(r3)
	b L_g5_4
	L_g5_5:
	lwz r0, 0x10(r4)
	add r31, r0, r29
	lwz r0, 0x0(r31)
	cmplwi r0, 0x0
	beq L_g5_6
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_7
	lwz r0, 0xc(r31)
	cmpwi r0, 0x0
	beq L_g5_6
	L_g5_7:
	cmpwi r3, 0x0
	bne L_g5_8
	lwz r0, 0xc(r31)
	cmpwi r0, 0x1
	beq L_g5_6
	L_g5_8:
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r4)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf0(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x48(r31)
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf0(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x4c(r31)
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf8(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x50(r31)
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0xf8(r3)
	mulli r3, r0, 0xc
	bl testAlloc
	stw r3, 0x54(r31)
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r3, 0x13c(r3)
	bl testAlloc
	stw r3, 0x58(r31)
	lwz r0, 0x58(r31)
	stw r0, 0x5c(r31)
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0x140(r3)
	slwi r3, r0, 2
	bl testAlloc
	stw r3, 0x60(r31)
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0x140(r3)
	slwi r3, r0, 2
	bl testAlloc
	stw r3, 0x64(r31)
	lwz r3, wp(r13)
	lwz r0, 0x10(r31)
	lwz r4, 0x0(r3)
	slwi r3, r0, 4
	addi r0, r3, 0x8
	lwzx r3, r4, r0
	lwz r3, 0xa0(r3)
	lwz r3, 0x0(r3)
	lwz r0, 0x12c(r3)
	mulli r3, r0, 0x18
	bl testAlloc
	stw r3, 0x68(r31)
	li r0, -0x1
	lwz r3, 0x68(r31)
	stw r3, 0x6c(r31)
	stw r0, 0x3c(r31)
	stw r0, 0x3c(r31)
	L_g5_6:
	addi r29, r29, 0x170
	addi r30, r30, 0x1
	L_g5_4:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r30, r0
	blt L_g5_5
	clrlwi. r0, r28, 27
	lwz r3, 0x108(r4)
	mr r30, r28
	beq L_g5_9
	subfic r0, r0, 0x20
	add r30, r28, r0
	L_g5_9:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_2
	bl initTestHeap
	li r29, 0x0
	mr r31, r29
	b L_g5_10
	L_g5_11:
	lwz r0, 0x10(r4)
	add r28, r0, r31
	lwz r0, 0x0(r28)
	cmplwi r0, 0x0
	beq L_g5_12
	lwz r3, 0x10c(r4)
	cmpwi r3, 0x0
	beq L_g5_13
	lwz r0, 0xc(r28)
	cmpwi r0, 0x0
	beq L_g5_12
	L_g5_13:
	cmpwi r3, 0x0
	bne L_g5_14
	lwz r0, 0xc(r28)
	cmpwi r0, 0x1
	beq L_g5_12
	L_g5_14:
	mr r3, r28
	bl animPose_AllocBuffer
	li r0, -0x1
	stw r0, 0x3c(r28)
	L_g5_12:
	addi r31, r31, 0x170
	addi r29, r29, 0x1
	L_g5_10:
	lwz r4, wp(r13)
	lwz r0, 0x14(r4)
	cmpw r29, r0
	blt L_g5_11
	clrlwi. r0, r30, 27
	lwz r3, 0x108(r4)
	beq L_g5_15
	subfic r0, r0, 0x20
	add r30, r30, r0
	L_g5_15:
	lwz r0, 0x108(r4)
	add r0, r0, r30
	stw r0, 0x108(r4)
	lwz r5, wp(r13)
	lwz r4, 0x104(r5)
	lwz r5, 0x108(r5)
	addis r0, r4, 0x18
	cmplw r5, r0
	blt L_g5_2
	bl animPoseRefresh
	mr r3, r30
	bl testAlloc
	L_g5_2:
	lwz r0, 0x24(r1)
	lwz r31, 0x1c(r1)
	lwz r30, 0x18(r1)
	lwz r29, 0x14(r1)
	lwz r28, 0x10(r1)
	mtlr r0
	addi r1, r1, 0x20
	blr
}

asm void initTestHeap(void) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	stw r0, 0x14(r1)
	lwz r3, wp(r13)
	lwz r0, 0x104(r3)
	cmplwi r0, 0x0
	bne L_g5_1
	li r3, 0x0
	lis r4, 0x18
	bl __memAlloc
	lwz r4, wp(r13)
	stw r3, 0x104(r4)
	L_g5_1:
	lwz r3, wp(r13)
	lwz r0, 0x104(r3)
	stw r0, 0x108(r3)
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm OSTime animTimeGetTime(BOOL globalTime) {
	nofralloc
	stwu r1, -0x10(r1)
	mflr r0
	cmpwi r3, 0x0
	stw r0, 0x14(r1)
	bne L_g5_1
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x40(r6)
	lwz r4, 0x44(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	b L_g5_2
	L_g5_1:
	lis r3, 0x8000
	lis r4, 0x1062
	lwz r0, 0xf8(r3)
	addi r5, r4, 0x4dd3
	lwz r6, gp(r13)
	srwi r0, r0, 2
	mulhwu r0, r5, r0
	lwz r3, 0x38(r6)
	lwz r4, 0x3c(r6)
	li r5, 0x0
	srwi r6, r0, 6
	bl __div2i
	L_g5_2:
	lwz r0, 0x14(r1)
	mtlr r0
	addi r1, r1, 0x10
	blr
}

asm AnimationWork* animGetPtr(void) {
	nofralloc
	lwz r3, wp(r13)
	blr
}
// clang-format on
#endif
