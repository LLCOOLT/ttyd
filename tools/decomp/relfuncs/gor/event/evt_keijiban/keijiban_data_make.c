// include: driver/msgdrv.h
// include: evt/evt_johoya.h
// include: stdio.h
// include: string.h
// decl: typedef struct KeijibanEntry { s16 unk0; s16 evtNo; s16 index; } KeijibanEntry;
// decl: typedef struct KeijibanData { KeijibanEntry* entries; s32 count; const char* prefix; char* label; s32 current; s32 maxEvtNo; } KeijibanData;
// decl: #define KJDT ((KeijibanData*)_kjdt)
// proto: s32 keijiban_data_make(const char* prefix, BOOL fill);
s32 keijiban_data_make(const char* prefix, BOOL fill) {
    char name[64];
    char buf[64];
    KeijibanData* kj = KJDT;
    s32 gsw = evtGetValue(NULL, GSW(0));
    s32 i;
    s32 len;
    s32 field;
    BOOL end;
    const s8* p;
    s32 count;
    s32 no;

    if (fill & 1) {
        if (kj->maxEvtNo == -1) {
            return 0;
        }
    } else {
        kj->maxEvtNo = -1;
    }
    count = 0;
    for (i = 0; ; i++) {
        sprintf(name, "%s_%04d", prefix, i);
        p = (const s8*)msgSearch(name);
        if (*p++ != '<' || *p++ != '!') {
            break;
        }
        field = 0;
        len = 0;
        end = FALSE;
        while (!end) {
            if (_ismbblead(*p)) {
                if (field == 0) {
                    buf[len++] = (char)*p++;
                    buf[len++] = (char)*p++;
                } else {
                    len += 2;
                    p += 2;
                }
            } else {
                switch (*p) {
                    case '>':
                        end = TRUE;
                    case ',':
                        p++;
                        if (field == 0) {
                            buf[len] = '\0';
                        }
                        len = 0;
                        field++;
                        break;
                    default:
                        if (field == 0) {
                            buf[len++] = (char)*p++;
                        } else {
                            len++;
                            p++;
                        }
                        break;
                }
            }
        }
        if (strcmp(buf, "enddata") == 0) {
            break;
        }
        if (strcmp(buf, "") == 0) {
            continue;
        }
        no = search_evt_no(buf);
        if (no == -1) {
            continue;
        }
        if (fill & 1) {
            if (no != kj->maxEvtNo) {
                continue;
            }
            kj->entries[count].evtNo = no;
            kj->entries[count].index = i;
        } else {
            if (no > gsw || no < kj->maxEvtNo) {
                continue;
            }
            if (no > kj->maxEvtNo) {
                kj->maxEvtNo = no;
                count = 0;
            }
        }
        count++;
    }
    return count;
}
