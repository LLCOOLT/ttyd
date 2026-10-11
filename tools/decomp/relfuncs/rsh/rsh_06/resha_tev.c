// include: driver/mapdrv.h
// proto: static void resha_tev(MapTevCallbackInfo* info);
void envAddTev(s32 type, MapTevCallbackInfo* info);

static void resha_tev(MapTevCallbackInfo* info) {
    envAddTev(7, info);
}
