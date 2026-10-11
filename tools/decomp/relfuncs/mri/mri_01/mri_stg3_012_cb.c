// proto: void mri_stg3_012_cb(s32 type, void* param);
void mri_stg3_012_cb(s32 type, void* param) {
    u16* work = *(u16**)param;

    switch (type) {
        case 3:
            if (work[4] == 1) {
                evtSetValue(NULL, LSWF(2), TRUE);
            }
            break;
    }
}
