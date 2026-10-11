// include: driver/effdrv.h
// include: driver/camdrv.h
// decl: void effStarStoneDraw(CameraId camera, void* param);
// decl: typedef struct MahojinStone { EffectEntry* eff; void* draw; u8 field_0x8[0x30 - 0x8]; } MahojinStone;
// decl: typedef struct MahojinWork { u8 field_0x0[0x88]; MahojinStone stones[7]; } MahojinWork;
// proto: USER_FUNC(starstone_setting);
USER_FUNC(starstone_setting) {
    s32* args = event->args;
    const char* name = (const char*)evtGetValue(event, args[0]);
    s32 idx = evtGetValue(event, args[1]);
    EffectEntry* eff = effNameToPtr(name);
    EffectEntry* mahojin = effNameToPtr("mahojin");

    *(u16*)((u8*)eff->userdata + 4) |= 0x20;
    ((MahojinWork*)mahojin->userdata)->stones[idx].eff = eff;
    ((MahojinWork*)mahojin->userdata)->stones[idx].draw = effStarStoneDraw;
    return EVT_RETURN_DONE;
}
