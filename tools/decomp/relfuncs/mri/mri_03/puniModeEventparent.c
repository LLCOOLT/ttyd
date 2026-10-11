// decl: typedef struct PuniData { u8 field_0x0[0x4]; u32 flags; u8 field_0x8[0xC - 0x8]; s16 field_0xC; u8 field_0xE[0x114 - 0xE]; u16 field_0x114; u8 field_0x116[0x118 - 0x116]; s16 field_0x118; u8 field_0x11A[0x11E - 0x11A]; s16 field_0x11E; u8 field_0x120[0x12C - 0x120]; Vec position; u8 field_0x138[0x15C - 0x138]; Vec field_0x15C; u8 field_0x168[0x174 - 0x168]; f32 field_0x174; u8 field_0x178[0x180 - 0x178]; f32 field_0x180; u8 field_0x184[0x1E0 - 0x184]; s32 field_0x1E0; s32 field_0x1E4; u8 field_0x1E8[0x56C - 0x1E8]; void* field_0x56C; void* field_0x570; u8 field_0x574[0x5A8 - 0x574]; } PuniData;
// include: dolphin/mtx.h
// decl: extern s32 JailAwayTable_New[];
// decl: void puniMoveAtari(PuniData* puni, Vec pos, Vec dir, s32 flag, f32 speed);
// proto: void puniModeEventparent(PuniData* puni);
void puniModeEventparent(PuniData* puni) {
    s32* tbl = JailAwayTable_New;
    s32 i;
    s32 bestIdx;
    f32 best;
    f32 d;
    Vec dir;
    Vec p;
    Vec pos;
    f32 mag;

    switch (puni->field_0x114) {
        case 0:
            best = 1000000.0f;
            bestIdx = -1;
            for (i = 0; i < 4; i++) {
                p.x = tbl[i * 2];
                p.y = 0.0f;
                p.z = tbl[i * 2 + 1];
                d = PSVECSquareDistance(&p, &puni->position);
                if (best > d) {
                    best = d;
                    bestIdx = i;
                }
            }
            puni->field_0x1E0 = bestIdx;
            puni->field_0x11E = 2;
            puni->field_0x114 = 1;
        case 1:
            p.x = tbl[puni->field_0x1E0 * 2];
            p.y = 0.0f;
            p.z = tbl[puni->field_0x1E0 * 2 + 1];
            if (PSVECSquareDistance(&p, &puni->position) > 100.0f) {
                PSVECSubtract(&p, &puni->position, &dir);
                PSVECNormalize(&dir, &dir);
                dir.y = 0.0f;
                PSVECScale(&dir, &dir, 1.5f);
                PSVECAdd(&puni->field_0x15C, &dir, &puni->field_0x15C);
            } else if (puni->field_0x1E0 == puni->field_0x1E4 + 5) {
                puni->field_0x15C = (Vec){0.0f, 0.0f, 0.0f};
                puni->field_0x114 = 2;
            } else if (tbl[puni->field_0x1E0 * 2 + 2] != 10000) {
                puni->field_0x1E0++;
            } else {
                puni->field_0x15C = (Vec){0.0f, 0.0f, 0.0f};
                puni->field_0x114 = 2;
            }
            break;
        case 2:
            puni->field_0x11E = 0;
            puni->field_0x114 = 3;
            break;
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
            break;
        case 10:
            p = (Vec){-160.0f, 0.0f, 40.0f};
            if (PSVECSquareDistance(&p, &puni->position) < 4900.0f) {
                PSVECSubtract(&puni->position, &p, &dir);
                PSVECNormalize(&dir, &dir);
                dir.y = 0.0f;
                PSVECScale(&dir, &dir, 0.7f);
                PSVECAdd(&puni->field_0x15C, &dir, &puni->field_0x15C);
                puni->field_0x174 = 2.1f;
                mag = PSVECMag(&puni->field_0x15C);
                pos = puni->position;
                pos.y += 1.0f;
                if (mag != 0.0f) {
                    PSVECNormalize(&puni->field_0x15C, &dir);
                } else {
                    dir = (Vec){0.0f, 0.0f, 0.0f};
                }
                puniMoveAtari(puni, pos, dir, 0, mag);
            } else {
                puni->field_0x114 = 11;
            }
            break;
        case 11:
            puni->field_0x15C = (Vec){0.0f, 0.0f, 0.0f};
            if (puni->position.x < -160.0f) {
                puni->field_0x180 = 90.0f;
            } else {
                puni->field_0x180 = 270.0f;
            }
            puni->field_0x114 = 12;
            break;
        case 12:
            break;
    }
}
