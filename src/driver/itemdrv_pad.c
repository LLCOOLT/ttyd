// 24 bytes of zeroed, force-active .rodata padding for the item driver (itemdrv_rodata_pad).
#pragma force_active on
const unsigned char itemdrv_rodata_pad[24] = {0};
#pragma force_active reset
