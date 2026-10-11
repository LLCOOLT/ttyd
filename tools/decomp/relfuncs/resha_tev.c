// include: driver/mapdrv.h
// proto: void resha_tev(MapTevCallbackInfo* info);
void envAddTev(s32 type, MapTevCallbackInfo* info);

void resha_tev(MapTevCallbackInfo* info) {
    envAddTev(7, info);
}
