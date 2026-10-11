// include: driver/mapdrv.h
// proto: void test_tev2(MapTevCallbackInfo* info);
void envAddTev(s32 type, MapTevCallbackInfo* info);

void test_tev2(MapTevCallbackInfo* info) {
    envAddTev(7, info);
}
