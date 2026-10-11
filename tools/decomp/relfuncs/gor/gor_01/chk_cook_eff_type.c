// proto: s32 chk_cook_eff_type(s32 item);
s32 chk_cook_eff_type(s32 item) {
    if (item < 148) {
        return 1;
    }
    if (item < 161) {
        return 0;
    }
    if (item < 179) {
        switch (item) {
            case 161:
            case 162:
            case 163:
            case 164:
            case 177:
            case 178:
                return 1;
            default:
                return 0;
        }
    }
    if (item < 236) {
        switch (item) {
            case 196:
            case 202:
            case 203:
            case 209:
                return 1;
            default:
                return 0;
        }
    }
    return 0;
}
