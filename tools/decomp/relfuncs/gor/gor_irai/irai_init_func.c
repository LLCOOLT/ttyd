// include: manager/evtmgr_cmd.h
// include: memory.h
// include: string.h
// include: driver/swdrv.h
// include: driver/msgdrv.h
// decl: typedef struct IraiWork { s32 state; s32 count; s32 list[30]; s32 cursor; s32 last; s32 top; s32 yubiX; s32 yubiY; s32 field_0x94; f32 scroll; char client[30][21]; char contents[30][31]; u8 field_0x6B4[0x416C - 0x6B4]; } IraiWork;
// decl: void irai_flag_disp(void);
// decl: extern s32 irai_msg_client[];
// decl: extern s32 irai_msg_contents[];
// proto: USER_FUNC(irai_init_func);
USER_FUNC(irai_init_func) {
    IraiWork* wp;
    s32 seq;
    s32 n;
    s32 i;
    const char* msg;

    irai_flag_disp();
    wp = _mapAlloc(sizeof(IraiWork));
    memset(wp, 0, sizeof(IraiWork));
    wp->state = 0;
    seq = swByteGet(0);
    wp->list[0] = 1;
    wp->list[1] = 2;
    wp->list[2] = 3;
    wp->list[3] = 4;
    wp->list[4] = 5;
    wp->list[5] = 6;
    if (seq >= 56) {
        wp->list[6] = 7;
        wp->list[7] = 8;
        wp->list[8] = 9;
    }
    if (seq >= 112) {
        wp->list[9] = 10;
        wp->list[10] = 11;
        wp->list[11] = 12;
    }
    if (seq >= 164) {
        wp->list[12] = 13;
        wp->list[13] = 14;
        wp->list[14] = 15;
    }
    if (seq >= 215) {
        wp->list[15] = 16;
        wp->list[16] = 17;
        wp->list[17] = 18;
    }
    if (seq >= 261) {
        wp->list[18] = 20;
        wp->list[19] = 21;
    }
    if (seq >= 281) {
        wp->list[20] = 19;
    }
    if (seq >= 339) {
        wp->list[21] = 22;
        wp->list[22] = 23;
        wp->list[23] = 24;
    }
    if (seq >= 373) {
        wp->list[24] = 25;
        wp->list[25] = 26;
        wp->list[26] = 27;
    }
    if (seq >= 401) {
        wp->list[27] = 28;
        wp->list[28] = 29;
        wp->list[29] = 30;
    }
    n = 0;
    for (i = 0; i < 30; i++) {
        if (wp->list[i] != 0) {
            n++;
        }
    }
    wp->count = n;
    for (i = 0; i < 30; i++) {
    }
    for (i = 0; i < 30; i++) {
        msg = msgSearch((const char*)irai_msg_client[i]);
        strcpy(wp->client[i], msg);
        msg = msgSearch((const char*)irai_msg_contents[i]);
        strcpy(wp->contents[i], msg);
    }
    wp->cursor = 0;
    wp->last = wp->cursor;
    wp->top = 0;
    wp->field_0x94 = 0;
    wp->scroll = 0.0f;
    event->lwData[10] = (s32)wp;
    return EVT_RETURN_DONE;
}
