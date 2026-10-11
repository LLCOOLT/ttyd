// include: data/item_data.h
// decl: extern ItemData itemDataTable[];
// include: string.h
// proto: s32 itemNameToID(const char* name);
s32 itemNameToID(const char* name) {
    s32 i;

    for (i = 0; i < 339; i++) {
        if (strcmp(name, itemDataTable[i].id) == 0) {
            break;
        }
    }
    if (i >= 339) {
        return 0;
    }
    return i;
}
