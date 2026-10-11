// include: driver/mapdrv.h
// proto: void test_tev(MapTevCallbackInfo* info);
void envAddTev(s32 type, MapTevCallbackInfo* info);

void test_tev(MapTevCallbackInfo* info) {
    envAddTev(4, info);
}
