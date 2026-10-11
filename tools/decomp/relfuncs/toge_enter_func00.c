// decl: void togeMakeRetsu(Vec* pos, s32 arg1, s32 arg2, s32 arg3);
// proto: USER_FUNC(toge_enter_func00);
USER_FUNC(toge_enter_func00) {
    Vec pos = {450.0f, 0.0f, 0.0f};

    togeMakeRetsu(&pos, 0x6E, 0x6F, 0x70);
    togeMakeRetsu(&pos, 0x71, 0x72, 0x73);
    togeMakeRetsu(&pos, 0x74, 0x75, 0x77);
    return EVT_RETURN_DONE;
}
