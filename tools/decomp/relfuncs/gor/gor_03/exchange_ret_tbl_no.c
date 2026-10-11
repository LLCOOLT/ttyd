// proto: s32 exchange_ret_tbl_no(void);
s32 exchange_ret_tbl_no(void) {
    s32 n = evtGetValue(NULL, GSW(0));
    s32 no = 0;

    if (n >= 402) {
        no = 8;
    } else if (n >= 375) {
        no = 7;
    } else if (n >= 344) {
        no = 6;
    } else if (n >= 267) {
        no = 5;
    } else if (n >= 218) {
        no = 4;
    } else if (n >= 171) {
        no = 3;
    } else if (n >= 117) {
        no = 2;
    } else if (n >= 61) {
        no = 1;
    }
    return no;
}
