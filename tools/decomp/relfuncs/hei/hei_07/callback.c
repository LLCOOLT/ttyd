// include: driver/mapdrv.h
// include: pmario_sound.h
// include: string.h
// proto: void callback(s32 type, void** work);
void mapPlayAnimationLv(const char* animName, s32 arg1, s32 arg2);

void callback(s32 type, void** work) {
    EventEntry* evt = *(EventEntry**)((u8*)*work + 0x7A00);
    BOOL valid;
    f32 frame;

    if (strcmp(*(const char**)*work, "stg1_hei_23") == 0 && type == 3) {
        evt->lwData[14]++;
        if (evt->lwData[14] == 3) {
            psndSFXOn("SFX_QUIZ_START1");
        }
    }
    switch (evt->lwData[15]) {
        case 0:
            switch (type) {
                case 5:
                    mapCheckAnimation("anm_kuti_1", &valid, &frame);
                    if (valid) {
                        mapPlayAnimationLv("anm_kuti_1", 0, 0);
                    }
                    break;
            }
            break;
        case 1:
            switch (type) {
                case 5:
                    mapCheckAnimation("anm_egao", &valid, &frame);
                    if (valid) {
                        mapPlayAnimationLv("anm_egao", 0, 0);
                        evt->lwData[14]++;
                        if (evt->lwData[14] > 1) {
                            evt->lwData[15] = 0;
                        }
                    }
                    break;
            }
            break;
        case 2:
            switch (type) {
                case 5:
                    mapCheckAnimation("anm_kuti_1", &valid, &frame);
                    if (valid) {
                        mapPlayAnimationLv("anm_kuti_1", 0, 0);
                    }
                    break;
                case 3:
                    evt->lwData[14]++;
                    if (evt->lwData[14] >= 2) {
                        mapPlayAnimationLv("anm_egao", 0, 0);
                        evt->lwData[14] = 0;
                        evt->lwData[15] = 1;
                    }
                    break;
            }
            break;
    }
}
