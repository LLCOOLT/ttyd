// include: driver/camdrv.h
// decl: void iconDispGx(f32 scale, Vec* position, s16 flags, u16 iconId);
// include: mario/mariost.h
// include: mario/mario_pouch.h
// decl: typedef struct KpaWork { u8 stage; u8 lives; u8 time; } KpaWork;
// decl: KpaWork* kwp;
// decl: #define NUMERIC_ID ((u16*)numeric_id)
// proto: void kpa_status_disp(CameraId camera, void* param);
void kpa_status_disp(CameraId camera, void* param) {
    Vec pos;
    s32 digit[6];
    s32 i;
    s32 n;

    pos.x = -210.0f;
    pos.y = 160.0f;
    iconDispGx(1.0f, &pos, 0x10, (u32)gp->language ? 0x210 : 0x206);
    pos.x = 50.0f;
    pos.y = 160.0f;
    iconDispGx(1.0f, &pos, 0x10, 0x208);
    pos.x = 220.0f;
    pos.y = 160.0f;
    iconDispGx(1.0f, &pos, 0x10, 0x207);

    n = pouchGetKpaScore();
    digit[0] = n / 100000;
    pos.x = -250.0f;
    pos.y = 130.0f;
    n %= 100000;
    digit[1] = n / 10000;
    n %= 10000;
    digit[2] = n / 1000;
    n %= 1000;
    digit[3] = n / 100;
    n %= 100;
    digit[4] = n / 10;
    digit[5] = n % 10;
    for (i = 0; i < 6; i++) {
        iconDispGx(1.0f, &pos, 0x10, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }
    pos.x += 20.0f;
    iconDispGx(0.7f, &pos, 0x10, 0x18B);
    pos.x += 30.0f;
    iconDispGx(1.0f, &pos, 0x10, 0x1D5);

    n = pouchGetKpaCoin();
    digit[0] = n / 10;
    digit[1] = n % 10;
    pos.x += 20.0f;
    for (i = 0; i < 2; i++) {
        iconDispGx(1.0f, &pos, 0x10, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }

    pos.x = 50.0f;
    iconDispGx(1.0f, &pos, 0x10, NUMERIC_ID[kwp->stage]);
    pos.x += 20.0f;
    iconDispGx(1.0f, &pos, 0x10, 0x1EE);

    n = kwp->lives;
    digit[0] = n / 10;
    digit[1] = n % 10;
    pos.x += 20.0f;
    for (i = digit[0] == 0; i < 2; i++) {
        iconDispGx(1.0f, &pos, 0x10, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }

    n = kwp->time;
    pos.x = 212.0f;
    digit[0] = n / 100;
    n %= 100;
    digit[1] = n / 10;
    digit[2] = n % 10;
    for (i = 0; i < 3; i++) {
        iconDispGx(1.0f, &pos, 0x10, NUMERIC_ID[digit[i]]);
        pos.x += 20.0f;
    }
}
