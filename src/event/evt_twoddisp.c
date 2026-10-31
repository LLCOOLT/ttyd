// Script commands for 2D icon and text overlays.
#include "evt/evt_cmd.h"
#include "driver/dispdrv.h"
#include "driver/icondrv.h"
#include "manager/evtmgr.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "memory.h"
#include <dolphin/gx.h>
#include <string.h>
#include "evt/evt_twoddisp.h"
#include "libc_decls.h"
#include "version.h"

typedef struct TwodEntry {
    char name[0x10]; // 0x0
    u16 flags;       // 0x10
    u16 flags2;      // 0x12, cleared with flags, never read
    f32 x;           // 0x14
    f32 y;           // 0x18
    f32 baseX;       // 0x1C
    f32 baseY;       // 0x20
    EvtWord id;      // 0x24, icon id, or a text pointer (top bit set)
    f32 scale;       // 0x28
    u8 pad[0x34 - 0x2C];
} TwodEntry;

TwodEntry* twodPtr;
s32 twodID;

static void twoddisp_disp(CameraId camera, void* param) {
    char buf[0x100];
    Vec pos;
    GXColor fogi;
    GXColor fogt;
    GXColor col;
    GXColor col2;
    s32 i;
    TwodEntry* p;

    for (i = 0; i < 100; i++) {
        p = &twodPtr[i];
        if ((s8)p->name[0] != 0 && (p->flags & 1)) {
            if (!(p->id & 0x80000000)) {
                fogi = twod_icon_fog_color;
                pos.x = p->baseX + p->x;
                pos.y = p->baseY + p->y;
                pos.z = 0.0f;
                GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogi);
#if VERSION == VERSION_DEMO
                iconDispGx(&pos, 4, (u16)p->id, p->scale);
#else
                iconDispGx(&pos, 0x10, (u16)p->id, p->scale);
#endif
            } else {
                FontDrawStart();
                FontDrawScale(p->scale);
                fogt = twod_text_fog_color;
                GXSetFog(GX_FOG_NONE, 0.0f, 0.0f, 0.0f, 0.0f, fogt);
                sprintf(buf, (const char*)p->id);
                col = (GXColor){0, 0, 0, 255};
                FontDrawColor(col);
                FontDrawString(p->baseX + p->x, p->baseY + p->y, buf);
                col2 = (GXColor){255, 255, 255, 255};
                FontDrawColor(col2);
                FontDrawString(1.0f + (p->baseX + p->x), (p->baseY + p->y) - 1.0f, buf);
            }
        }
    }
}

USER_FUNC(twoddisp_main) {
    u32 i;
    for (i = 0; (s32)i < 100; i++) {
    }
    dispEntry((CameraId)8, 1000.0f, 0, twoddisp_disp, NULL);
    return 2;
}

USER_FUNC(evt_twoddisp_init) {
    EventEntry* e;
    TwodEntry* p;
    u32 i;

    e = evtEntryType(twoddisp_main_event, event->priority, 0, event->type);
    e->unitId = event->unitId;
    e->ownerNPC = event->ownerNPC;
    for (i = 0; i < 16; i++) {
        e->lwData[i] = event->lwData[i];
    }
    for (i = 0; i < 3; i++) {
        e->lfData[i] = event->lfData[i];
    }
    e->uwBase = event->uwBase;
    e->ufBase = event->ufBase;
    twodID = e->eventId;
    twodPtr = (TwodEntry*)_mapAlloc(100 * sizeof(TwodEntry));
    for (i = 0; (s32)i < 100; i++) {
        p = &twodPtr[i];
        p->name[0] = 0;
        p->flags = 0;
        p->flags2 = 0;
        p->x = 0.0f;
        p->baseX = 0.0f;
        p->y = 0.0f;
        p->baseY = 0.0f;
        p->id = 0;
        p->scale = 1.0f;
    }
    return 2;
}

USER_FUNC(evt_twoddisp_entry) {
    s32 id;
    s32 i;
    EvtWord* args;
    char* name;
    TwodEntry* p;

    args = event->args;
    name = (char*)evtGetValue(event, args[0]);
    id = evtGetValue(event, args[1]);

    for (i = 0; i < 100; i++) {
        p = &twodPtr[i];
        strcmp(p->name, name);
        if ((s8)p->name[0] == 0) {
            strcpy(p->name, name);
            p->flags = 1;
            p->flags2 = 0;
            p->x = 0.0f;
            p->baseX = 0.0f;
            p->y = 0.0f;
            p->baseY = 0.0f;
            p->id = id;
            p->scale = 1.0f;
            break;
        }
    }
    return 2;
}

static inline TwodEntry* twod_find(const char* name) {
    s32 i;
    TwodEntry* p;

    for (i = 0; i < 100; i++) {
        p = &twodPtr[i];
        if (strcmp(p->name, name) == 0) {
            return p;
        }
    }
    return NULL;
}

USER_FUNC(evt_twoddisp_set_position) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    TwodEntry* p;

    p = twod_find(name);
    p->x = evtGetFloat(event, args[1]);
    p->y = evtGetFloat(event, args[2]);
    return 2;
}

USER_FUNC(evt_twoddisp_set_base_position) {
    EvtWord* args = event->args;
    char* name = (char*)evtGetValue(event, args[0]);
    TwodEntry* p;

    p = twod_find(name);
    p->baseX = evtGetFloat(event, args[1]);
    p->baseY = evtGetFloat(event, args[2]);
    return 2;
}

USER_FUNC(evt_twoddisp_flag_onoff) {
    s32 onoff;
    TwodEntry* p;
    EvtWord* args;
    char* name;

    args = event->args;
    onoff = evtGetValue(event, args[0]);
    name = (char*)evtGetValue(event, args[1]);

    p = twod_find(name);
    if (onoff) {
        p->flags |= evtGetValue(event, args[2]);
    } else {
        p->flags &= ~evtGetValue(event, args[2]);
    }
    return 2;
}

EVT_BEGIN(twoddisp_main_event)
    LOOP(0)
        CALL(twoddisp_main)
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

__declspec(section ".sdata2") const GXColor twod_text_fog_color;
__declspec(section ".sdata2") const GXColor twod_icon_fog_color;
