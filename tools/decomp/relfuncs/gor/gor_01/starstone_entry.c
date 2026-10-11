// include: manager/evtmgr_cmd.h
// include: driver/effdrv.h
// include: stdio.h
// include: driver/camdrv.h
// decl: double sin(double);
// decl: double cos(double);
// decl: EffectEntry* effStarStoneEntry(s32 type, f32 x, f32 y, f32 z, f32 scale);
// decl: void effStarStoneDraw(CameraId camera, void* param);
// decl: typedef struct MahojinStone { EffectEntry* eff; void* draw; u8 field_0x8[0x30 - 0x8]; } MahojinStone;
// decl: typedef struct MahojinWork { u8 field_0x0[0x88]; MahojinStone stones[7]; } MahojinWork;
// proto: static USER_FUNC(starstone_entry);
static USER_FUNC(starstone_entry) {
    char name[16];
    s32* args = event->args;
    f32 x;
    f32 s;
    f32 z;
    f32 angle;
    f32 y;
    f32 c;
    EffectEntry* eff;
    s32 i;

    x = evtGetFloat(event, args[0]);
    y = evtGetFloat(event, args[1]);
    z = evtGetFloat(event, args[2]);
    for (i = 0; i < 7; i++) {
        angle = 6.2831855f * i / 7.0f;
        s = sin(angle);
        c = cos(angle);
        sprintf(name, "starstone%d", i);
        eff = effStarStoneEntry(i, 140.0f * s + x, y, z - 140.0f * c, 1.0f);
        effSetName(eff, name);
        *(u16*)((u8*)eff->userdata + 4) &= ~4;
        *(u16*)((u8*)eff->userdata + 4) |= 0x20;
        ((MahojinWork*)effNameToPtr("mahojin")->userdata)->stones[i].eff = eff;
        ((MahojinWork*)effNameToPtr("mahojin")->userdata)->stones[i].draw = effStarStoneDraw;
    }
    return EVT_RETURN_DONE;
}
