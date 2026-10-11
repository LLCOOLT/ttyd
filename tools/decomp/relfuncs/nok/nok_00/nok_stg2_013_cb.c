// proto: void nok_stg2_013_cb(s32 type, void** work);
void nok_stg2_013_cb(s32 type, void** work) {
    s32* msg = *work;

    switch (type) {
        case 5:
            if (msg[4] > 0x31) {
                evtSetValue(NULL, LSWF(2), 1);
            }
            break;
    }
}
