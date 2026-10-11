// include: manager/evtmgr_cmd.h
// decl: typedef struct LectButtonDisp { s32 unk0; Vec pos; } LectButtonDisp;
// decl: typedef struct LectButton { u8 flags; u8 seq; u8 pad_2[0x8 - 0x2]; LectButtonDisp disp; u8 pad_18[0x40 - 0x18]; s16 iconId; s16 alpha; } LectButton;
// decl: static LectButton lbtn[2];
// proto: static USER_FUNC(lecture_button_set_pos);
static USER_FUNC(lecture_button_set_pos) {
    s32* args = event->args;
    s32 index = evtGetValue(event, args[0]);
    f32 x = evtGetFloat(event, args[1]);
    f32 y = evtGetFloat(event, args[2]);
    f32 z = evtGetFloat(event, args[3]);
    LectButton* btn = &lbtn[index];

    btn->disp.pos = (Vec){x, y, z};
    return EVT_RETURN_DONE;
}
