// Item driver: items on the field (drops, coins, pickups): spawning, bouncing, pickup and display.
#include "driver/itemdrv.h"
#include "eff/eff_itemget.h"
#include "driver/swdrv.h"
#include "driver/icondrv.h"
#include "driver/windowdrv.h"
#include "manager/evtmgr.h"
#include "driver/camdrv.h"
#include "driver/mobjdrv.h"
#include "eff/eff_stardust.h"
#include "pmario_sound.h"
#include "driver/effdrv.h"
#include "driver/hitdrv.h"
#include "driver/msgdrv.h"
#include "driver/seqdrv.h"
#include "data/item_data.h"
#include "evt/evt_cmd.h"
#include "manager/evtmgr_cmd.h"
#include "manager/fontmgr.h"
#include "manager/winmgr.h"
#include "mario/mario.h"
#include "mario/mario_party.h"
#include "mario/mario_pouch.h"
#include "mario/mariost.h"
#include "party.h"
#include "party/party_vivian.h"
#include "memory.h"
#include "system.h"
#include <string.h>
#include "evt/evt_lecture.h"
#include "libc_decls.h"
#include "mario/mario_cam.h"
#include "eff/eff_splash.h"
#include "eff/eff_starstone.h"
#include "mario/mario_motion.h"
#include "mot/mot_jabara.h"
#include "party/party_nokonoko.h"
#include <math.h>
#include "eff/n64/eff_hagetaka_flush_n64.h"
#include "version.h"
#include "evt/evt_story.h"
#include <dolphin/pad.h>
#include "evt/evt_msg.h"

/** Returns the zero vector. */
inline Vec unknownVec0(void) {
    return (Vec){0.0f, 0.0f, 0.0f};
}

/** Builds a Vec from x, y, z (a twin of makeVecByValue that compiles the same). */
inline Vec makeVecByValue2(f32 x, f32 y, f32 z) {
    Vec v = (Vec){0.0f, 0.0f, 0.0f};
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

/** Builds a Vec from x, y, z. */
inline Vec makeVecByValue(f32 x, f32 y, f32 z) {
    Vec v = (Vec){0.0f, 0.0f, 0.0f};
    v.x = x;
    v.y = y;
    v.z = z;
    return v;
}

static BOOL itemGetNokoCheck(ItemEntry* entry);
static void winNameDisp(WinMgrEntry* win);
static void winNameDisp2(WinMgrEntry* win);
static void winHelpMain(WinMgrEntry* win);
static void winHelpDisp(WinMgrEntry* win);
static void winFullDisp(WinMgrEntry* win);

HitEntry* itemHitCheckY(ItemEntry* entry, f32 z, f32 y, f32 x, f32 vy);
HitEntry* itemHitCheckUp(ItemEntry* entry, f32 vy);

static HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle);
static void itemseq_GetItem(ItemEntry* entry);

//.bss
static ItemWork work[2];

//.data
WinMgrDesc itemdrv_window_desc[4] = {
    { 0, 0, 8, -175, 120, 350, 42, { 0xE1, 0xD7, 0x9B, 0xFF }, NULL, winNameDisp },
    { 0, 0, 8, -240, -130, 500, 80, { 0xF0, 0xF0, 0xF0, 0xFF }, winHelpMain, winHelpDisp },
    { 0, 0, 8, -175, 200, 350, 75, { 0x2B, 0xA4, 0xFF, 0xFF }, NULL, winFullDisp },
    { 0, 0, 8, -175, 120, 350, 42, { 0xE1, 0xD7, 0x9B, 0xFF }, NULL, winNameDisp2 },
};

// A macro: the symbol map has no itemGetWork function.
#define itemGetWork() (gp->inBattle ? &work[1] : &work[0])

#if VERSION <= VERSION_DEMO_US
/**
 * The demo puts a removed badge item on sale at the badge shop (pouchArriveBadge, the bargain table)
 * when its ITEM_FLAG_BADGE_RETURN bit (0x100) is clear, in or out of battle.
 */
inline void itemCheckBadge(ItemEntry* entry) {
    if (BADGE_MIN <= entry->itemId && entry->itemId < BADGE_MAX && !(entry->flags & ITEM_FLAG_BADGE_RETURN)) {
        pouchArriveBadge(entry->itemId);
    }
}
#else
/**
 * On the field, when a badge item carrying ITEM_FLAG_BADGE_RETURN (a dropped badge) is removed uncollected,
 * puts the badge on sale at the badge shop (pouchArriveBadge, the special table) so it is not lost.
 */
inline void itemCheckBadge(ItemEntry* entry) {
    if (!gp->inBattle) {
        if (BADGE_MIN <= entry->itemId && entry->itemId < BADGE_MAX) {
            if (entry->flags & ITEM_FLAG_BADGE_RETURN) {
                pouchArriveBadge(entry->itemId);
            }
        }
    }
}
#endif

static void itemseq_Bound(ItemEntry* entry);
/**
 * Puts the item into the pouch; FALSE if the pouch is full.
 * On success sets its collect flag (GSWF or LSWF) and starts its pickup script.
 */
static inline BOOL itemGetPouch(ItemEntry* entry) {
    EventEntry* evt;

    if (!pouchGetItem(entry->itemId)) {
        return FALSE;
    }
    if (entry->flags & ITEM_FLAG_COLLECT_GSWF) {
        swSet(entry->collectFlag);
    } else if (entry->flags & ITEM_FLAG_COLLECT_LSWF) {
        _swSet(entry->collectFlag);
    }
    if ((u32)entry->evtCode != 0) {
        evt = evtEntry((EvtWord*)entry->evtCode, 0, 0x20);
        evt->lwData[0] = FLOAT(entry->position.x);
        evt->lwData[1] = FLOAT(entry->position.y);
        evt->lwData[2] = FLOAT(entry->position.z);
    }
    entry->status |= ITEM_STATUS_IN_POUCH;
    return TRUE;
}

/**
 * Ends an item get sequence: gives Mario back his controls and keys and unmutes the sound effects.
 * Later versions also undo the control lock if the get set it.
 */
static inline void itemGetEnd(ItemEntry* entry) {
    marioStSystemLevel(0);
    psndClearFlag(PSND_FLAG_MUTE_SFX);
#if VERSION >= VERSION_JP
    if (entry->status & ITEM_STATUS_CTRL_OFF) {
        entry->status &= ~ITEM_STATUS_CTRL_OFF;
        marioCtrlOn();
    }
#endif
    marioKeyOn();
    marioChgStayMotion();
    camGetPtr(CAMERA_2D)->flags &= ~CAM_FLAG_LETTER_BOX_DISABLE;
}

void itemGetSound(ItemEntry* entry);

/** Allocates the 32-entry field and battle item tables; called once at boot. */
void itemInit(void) { // 1:1
    ItemWork* wp;

    wp = &work[0];
    wp->count = 32;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->currId = 0;

    wp = &work[1];
    wp->count = 32;
    wp->entries = __memAlloc(HEAP_DEFAULT, sizeof(ItemEntry) * wp->count);
    memset(wp->entries, 0, sizeof(ItemEntry) * wp->count);
    wp->currId = 0;
}

/**
 * Clears the current item table on map change; on the field it first puts dropped badges
 * (ITEM_FLAG_BADGE_RETURN) on sale at the badge shop (itemCheckBadge).
 */
void itemReInit(void) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    int i;

    if (!gp->inBattle) {
        for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
            if (entry->flags & ITEM_FLAG_USED) { // flush all current badges
                itemCheckBadge(entry);
            }
        }
    }

    // clear all existing entries
    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        iconDelete(entry->name);
        entry->flags &= ~ITEM_FLAG_USED;
        memset(entry->name, 0, sizeof(entry->name));
    }
}

/**
 * Takes one coin from Mario and drops it as a coin item that scatters and vanishes after 8 seconds;
 * mario.c calls it when Mario loses coins.
 */
void itemCoinDrop(Vec* position) {
    ItemEntry* entry;

    if (pouchGetCoin() > 0) {
        pouchAddCoin(-1);
        entry = itemEntry(position->x, position->y, position->z, NULL, 0x79, ITEM_ENTRY_DROP_8S, -1, 0);
        if (entry) {
            entry->status |= ITEM_STATUS_SCATTER;
        }
    }
}

/**
 * Returns whether Mario may pick up this item now:
 * not in water or lava, Mario has control (later versions skip that for Bowser when his stage flag bit 0 is
 * set), no map event or other sequence runs, Mario is not on the boat or plane panel, hiding with Vivian,
 * taking damage or holding Koops's item, no other get is in progress, and field battle state allows it.
 */
static BOOL itemGetCheck(ItemEntry* entry) {
#if VERSION <= VERSION_DEMO_US
    // the demo has no N_fbatPreventMarioEventChk: only field battle modes 0 and 1 allow pick-ups
    s32 fbatMode = fbatGetPointer()->mode;
#endif
    MarioWork* mario = marioGetPtr();

    if (!entry)
        return FALSE;
    if (entry->status & ITEM_STATUS_IN_WATER)
        return FALSE;
#if VERSION <= VERSION_DEMO_US
    if (marioStGetSystemLevel() != 0U)
        return FALSE;
    if (mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_KEY_OFF))
        return FALSE;
#else
    if (mario->characterId == 2) {
        if (!(mario->stageFlags & MARIO_STAGE_FLAG_SIDE_VIEW)) {
            if (marioStGetSystemLevel() != 0U)
                return FALSE;
            if (mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_KEY_OFF))
                return FALSE;
        }
    } else {
        if (marioStGetSystemLevel() != 0U)
            return FALSE;
        if (mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_KEY_OFF))
            return FALSE;
    }
#endif
    if (gp->mapEventId)
        return FALSE;
    if (seqGetSeq() != SEQ_GAME)
        return FALSE;
    if (mario->currMotionId == MARIO_MOTION_SHIP)
        return FALSE;
#if VERSION >= VERSION_JP
    if (mario->currMotionId == MARIO_MOTION_PLANE)
        return FALSE;
#endif
    if (vivianGetStatus())
        return FALSE;
    if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_DAMAGE_TOGE)
        return FALSE;
    if (nokonoko_holdItem())
        return FALSE;
    {
        ItemWork* wp = itemGetWork();
        ItemEntry* item;
        int i;
        for (item = wp->entries, i = 0; i < wp->count; i++, item++) {
            if (item->flags & ITEM_FLAG_USED && item->mode == 2) {
                return FALSE;
            }
        }
    }
#if VERSION <= VERSION_DEMO_US
    if (fbatMode != 0 && fbatMode != 1)
        return FALSE;
#else
    if (N_fbatPreventMarioEventChk())
        return FALSE;
#endif
    switch (entry->mode) {
        case 5:
        case 6:
            if (!entry->subState)
                break;
            if (entry->status & ITEM_STATUS_LAUNCH)
                break;
            if (entry->status & ITEM_STATUS_THROWN)
                break;
            return TRUE;
        case 3:
        case 4:
            if (entry->status & ITEM_STATUS_THROWN)
                break;
            return TRUE;
        case 1:
        case 7:
            return TRUE;
    }
    return FALSE;
}

/** Like itemGetCheck for an item fetched by Koops's shell: whether the item may be collected for Mario now. */
static BOOL itemGetNokoCheck(ItemEntry* entry) {
#if VERSION <= VERSION_DEMO_US
    s32 fbatMode = fbatGetPointer()->mode;
#endif
    MarioWork* mario = marioGetPtr();

    if (!entry)
        return FALSE;
    if (entry->status & ITEM_STATUS_IN_WATER)
        return FALSE;
    if (marioStGetSystemLevel() != 0U)
        return FALSE;
    if (mario->flags & (MARIO_FLAG_CTRL_OFF | MARIO_FLAG_KEY_OFF))
        return FALSE;
#if VERSION >= VERSION_JP
    if (entry->status & ITEM_STATUS_NO_KOOPS)
        return FALSE;
#endif
    if (gp->mapEventId)
        return FALSE;
    if (seqGetSeq() != SEQ_GAME)
        return FALSE;
    if (mario->currMotionId == MARIO_MOTION_SHIP)
        return FALSE;
    if (vivianGetStatus())
        return FALSE;
    if (mario->currMotionId == MARIO_MOTION_DAMAGE || mario->currMotionId == MARIO_MOTION_DAMAGE_TOGE)
        return FALSE;
    if ((u16)(mario->currMotionId - 5) <= 3 || mario->currMotionId == MARIO_MOTION_GET_ITEM || mario->currMotionId == MARIO_MOTION_TALK)
        return FALSE;
    {
        ItemWork* wp = itemGetWork();
        ItemEntry* item;
        int i;
        for (item = wp->entries, i = 0; i < wp->count; i++, item++) {
            if (item->flags & ITEM_FLAG_USED && item->mode == 2) {
                return FALSE;
            }
        }
    }
#if VERSION <= VERSION_DEMO_US
    if (fbatMode != 0 && fbatMode != 1)
        return FALSE;
    return TRUE;
#else
    return !N_fbatPreventMarioEventChk();
#endif
}

/** Returns TRUE while any item is in its get sequence (mode 2); NPC updates, shops and menus wait on it. */
BOOL N_itemPickUpFromFieldCheck(void) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    int i;

    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (entry->flags & ITEM_FLAG_USED && entry->mode == 2) {
            return TRUE;
        }
    }
    return FALSE;
}

typedef struct ItemEffPos {
    u8 pad[8];
    Vec position;
} ItemEffPos;

/**
 * Per-frame update of the field items: despawn timers and blinking before an item vanishes, then per mode:
 * resting on the floor (1), falling (3, 4), bouncing (5, 6, 10),
 * being collected (2) or carried by a partner (8); checks Mario touching items, queues drawing and shadows.
 */
void itemMain(void) {
    ItemWork* wp = itemGetWork();
    MarioWork* mario;
    ItemEntry* entry;
    PartyEntry* party;
    HitEntry* hit;
    BOOL active;
    u16 mode;
    int i;
    f32 newY;
    f32 y;
    s32 dx, dy;

    mario = marioGetPtr();
    entry = itemHitCheck(mario->position.x, mario->position.y, mario->position.z, mario->wPlayerCollisionBox.x * 0.5f + 12.0f);
    if (itemGetCheck(entry)) {
        itemModeChange(entry, 2);
    }

    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (!(entry->flags & ITEM_FLAG_USED))
            continue;
        mode = entry->mode;
        active = TRUE;
        switch (mode) {
            case 2:
            case 7:
            case 8:
            case 10:
                break;
            default:
                if (gp->systemLevelFlags & 0xF) {
                    active = FALSE;
                }
                break;
        }
        if (!active) {
            entry->baseTime = gp->renderTime;
            continue;
        }
        if (mode != 2) {
            if (entry->timer == 0) {
                entry->status &= ~ITEM_STATUS_BLINK_HIDDEN;
            } else if (entry->status & ITEM_STATUS_TIMER_HOLD) {
                entry->status &= ~ITEM_STATUS_BLINK_HIDDEN;
            } else {
                entry->timer -= (f32)OSTicksToMicroseconds(gp->renderTime - entry->baseTime) / 1000.0f;
                if (entry->timer <= 0) {
                    itemModeChange(entry, 9);
                } else if (entry->timer <= 3000) {
                    if ((entry->timer >> 4) & 1) {
                        entry->status ^= ITEM_STATUS_BLINK_HIDDEN;
                    }
                }
            }
        } else {
            entry->status &= ~ITEM_STATUS_BLINK_HIDDEN;
        }

        switch (entry->mode) {
            case 5:
            case 6:
            case 10:
                itemseq_Bound(entry);
                break;
            case 3:
            case 4:
                itemseq_Bound(entry);
                break;
            case 1:
                y = entry->position.y;
                {
                    f32 dirY = -1.0f;
                    if (entry->status & ITEM_STATUS_IN_WATER) {
                        hit = NULL;
                        newY = y + dirY;
                    } else {
                        f32 hitNZ, hitNY, hitNX, hitDist, hitZ, hitY, hitX;
                        f32 px = entry->position.x, py = entry->position.y + 20.0f, pz = entry->position.z;
                        {
                            f64 d = __fabs(-1.0);
                            hitDist = 20.0 + d;
                        }
                        hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, px, py, pz, 0.0f, -1.0f, 0.0f);
#if VERSION <= VERSION_DEMO_US
                        hit = hit ? hit : NULL;
#else
                        if (hit) {
                            newY = hitY;
                        } else {
                            hit = NULL;
                            newY = y + dirY;
                        }
#endif
                    }
                }
                if (!hit) {
                    itemModeChange(entry, 3);
                }
#if VERSION >= VERSION_JP
                else {
                    entry->position.y = newY;
                }
#endif
                break;
            case 2:
                itemseq_GetItem(entry);
                break;
            case 8:
                party = partyGetPtr(marioGetPartyId());
                if (party) {
                    f32 px = party->position.x, py = 15.0f + party->position.y, pz = party->position.z;
                    entry->position.x = px;
                    entry->position.y = py;
                    entry->position.z = pz;
                } else {
                    itemModeChange(entry, 3);
                    entry->status &= ~ITEM_STATUS_PARTY_HOLD;
                }
                break;
            case 9:
#if VERSION <= VERSION_DEMO_US
                itemCheckBadge(entry);
#endif
                itemDelete(entry->name);
                break;
        }

        if (entry->flags & ITEM_FLAG_USED) {
            switch (entry->itemId) {
                case ITEM_DIAMOND_STAR:
                case ITEM_EMERALD_STAR:
                case ITEM_GOLD_STAR:
                case ITEM_RUBY_STAR:
                case ITEM_SAPPHIRE_STAR:
                case ITEM_GARNET_STAR:
                case ITEM_CRYSTAL_STAR:
                    if (!(entry->status & ITEM_STATUS_BLINK_HIDDEN)) {
                        ((ItemEffPos*)entry->effect->userdata)->position.x = entry->position.x;
                        ((ItemEffPos*)entry->effect->userdata)->position.y = 16.0f + entry->position.y;
                        ((ItemEffPos*)entry->effect->userdata)->position.z = entry->position.z;
                    } else {
                        ((ItemEffPos*)entry->effect->userdata)->position.x = entry->position.x;
                        ((ItemEffPos*)entry->effect->userdata)->position.y = -1000.0f;
                        ((ItemEffPos*)entry->effect->userdata)->position.z = entry->position.z;
                    }
                    break;
                default:
                    if (!(entry->status & ITEM_STATUS_BLINK_HIDDEN)) {
                        iconSetPos(entry->name, entry->position.x, entry->position.y, entry->position.z);
                        iconSetScale(entry->name, entry->scale);
                        iconSetAlpha(entry->name, entry->alpha);
                    } else {
                        iconSetPos(entry->name, entry->position.x, -1000.0f, entry->position.z);
                    }
                    break;
            }
            entry->baseTime = gp->renderTime;
            if (entry->itemId == ITEM_COIN || entry->itemId == ITEM_PIANTA_TOKEN) {
                if (irand(1000) < 30) {
                    dx = 10 - irand(20);
                    dy = irand(20) + 10;
                    effHagetakaFlushN64Entry(0, 10, entry->position.x + dx, entry->position.y + dy, entry->position.z, 1.0f);
                }
            }
        }
    }

    wp = gp->inBattle ? &work[0] : &work[1];
    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (entry->flags & ITEM_FLAG_USED) {
            entry->baseTime = gp->renderTime;
        }
    }
}

/** Puts an item into mode (resting, collecting, falling, bouncing, carried, ...) and restarts that mode's sub-state. */
void itemModeChange(ItemEntry* entry, s32 mode) {
    entry->mode = mode;
    entry->subState = 0;
}

#if VERSION >= VERSION_US
/**
 * Returns the first replaceable dropped item (coin, heart, flower) with this item id,
 * so itemEntry can reuse its slot when the table is full; NULL if none.
 */
static inline ItemEntry* itemFindDeletable(ItemWork* wp, s32 itemId) {
    ItemEntry* entry;
    ItemEntry* found;
    int i;

    found = NULL;
    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (entry->flags & ITEM_FLAG_USED && entry->itemId == itemId && entry->flags & ITEM_FLAG_REPLACEABLE) {
            found = entry;
            break;
        }
    }
    return found;
}
#endif

/**
 * Spawns field item itemId at (x, y, z) named name (generated if NULL);
 * type (ItemEntryType) picks how it appears and how long it stays,
 * collectFlag is the GSWF or LSWF that marks it taken (-1 none), pickupEvt runs on collection.
 * When the table is full a dropped coin, heart or flower is replaced. Returns the entry or NULL.
 */
ItemEntry* itemEntry(f32 x, f32 y, f32 z, const char* name, s32 itemId, u16 type, s32 collectFlag, EvtWord* pickupEvt) {
    ItemWork* wp = itemGetWork();
    int i;
    ItemEntry* entry;
#if VERSION >= VERSION_US
    // FAKE: e/base and the explicit 0x79/0x7C search loops (0x7B uses the helper) steer register
    // numbering: the search pointer must be a named local and the entries base a named web.
    ItemEntry* e;
    ItemEntry* base;
#endif
    BOOL isGswf, isLswf;
    char itemName[8];

    isGswf = FALSE;
    isLswf = FALSE;
    if (collectFlag != -1) {
        if (collectFlag >= GSWF(0) && collectFlag <= EVTDAT_GSWF_MAX) {
            collectFlag += EVTDAT_GSWF_BASE;
            isGswf = TRUE;
            if (swGet(collectFlag)) {
                return NULL;
            }
        } else if (collectFlag >= LSWF(0) && collectFlag <= EVTDAT_LSWF_MAX) {
            collectFlag += EVTDAT_LSWF_BASE;
            isLswf = TRUE;
            if (_swGet(collectFlag)) {
                return NULL;
            }
        }
    }

    if (name == NULL) {
        wp->currId++;
        if (wp->currId >= 0xFFFFF) {
            wp->currId = 1;
        }
        sprintf(itemName, "_i%05x", wp->currId);
        name = itemName;
    }

    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (entry->flags & ITEM_FLAG_USED && !strcmp(entry->name, name)) {
            break;
        }
    }

#if VERSION >= VERSION_US
    base = wp->entries;
    for (entry = base, i = 0; i < wp->count; i++, entry++) {
#else
    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
#endif
        if (!(entry->flags & ITEM_FLAG_USED)) {
            break;
        }
    }

#if VERSION >= VERSION_US
    if (i >= wp->count) {
        entry = NULL;
        for (e = base, i = 0; i < wp->count; i++, e++) {
            if (e->flags & ITEM_FLAG_USED && e->itemId == ITEM_COIN && e->flags & ITEM_FLAG_REPLACEABLE) {
                entry = e;
                break;
            }
        }
        if (entry) {
            itemDelete(entry->name);
        } else {
            entry = NULL;
            for (e = base, i = 0; i < wp->count; i++, e++) {
                if (e->flags & ITEM_FLAG_USED && e->itemId == ITEM_FLOWER && e->flags & ITEM_FLAG_REPLACEABLE) {
                    entry = e;
                    break;
                }
            }
            if (entry) {
                itemDelete(entry->name);
            } else {
                entry = itemFindDeletable(wp, 0x7B);
                entry = NULL;
            }
        }
#else
    if (i >= wp->count) {
        entry = wp->entries;
        if (entry->flags & ITEM_FLAG_USED && entry->itemId == ITEM_COIN && entry->flags & ITEM_FLAG_REPLACEABLE) {
            itemDelete(entry->name);
        } else {
            entry = wp->entries;
            if (entry->flags & ITEM_FLAG_USED && entry->itemId == ITEM_FLOWER && entry->flags & ITEM_FLAG_REPLACEABLE) {
                itemDelete(entry->name);
            } else {
                entry = wp->entries;
                if (entry->flags & ITEM_FLAG_USED && entry->itemId == ITEM_HEART && entry->flags & ITEM_FLAG_REPLACEABLE) {
                    itemDelete(entry->name);
                } else {
                    entry = NULL;
                }
            }
        }
#endif
        if (entry == NULL) {
            return NULL;
        }
    }

    memset(entry, 0, sizeof(ItemEntry));
    strcpy(entry->name, name);
    entry->position.x = x;
    entry->position.y = y;
    entry->position.z = z;
    entry->itemId = itemId;
    entry->type = type;
    entry->evtCode = (EvtWord)pickupEvt;
    entry->flags |= ITEM_FLAG_USED;
    entry->scale = 1.0f;
    entry->alpha = 0xFF;
    if (collectFlag != -1) {
        if (isGswf) {
            entry->collectFlag = collectFlag;
            entry->flags |= ITEM_FLAG_COLLECT_GSWF;
        } else if (isLswf) {
            entry->collectFlag = collectFlag;
            entry->flags |= ITEM_FLAG_COLLECT_LSWF;
        }
    } else {
        entry->collectFlag = -1;
    }

    switch (entry->itemId) {
        case ITEM_DIAMOND_STAR:
        case ITEM_EMERALD_STAR:
        case ITEM_GOLD_STAR:
        case ITEM_RUBY_STAR:
        case ITEM_SAPPHIRE_STAR:
        case ITEM_GARNET_STAR:
        case ITEM_CRYSTAL_STAR:
            entry->effect = effStarStoneEntry(entry->itemId - ITEM_DIAMOND_STAR, x, 16.0f + y, z, 1.0f);
            break;
        default:
#if VERSION >= VERSION_JP
            entry->effect = NULL;
#endif
            iconEntry(entry->name, itemDataTable[itemId].icon_id);
            {
                char* nm = entry->name;
                iconSetPos(nm, x, y, z);
            }
            iconSetScale(entry->name, entry->scale);
            iconSetAlpha(entry->name, entry->alpha);
            break;
    }
    entry->bounceFactor = entry->gravityScale = 1.0f;
    entry->baseTime = gp->renderTime;
    switch (entry->itemId) {
        case ITEM_COIN:
        case ITEM_PIANTA_TOKEN:
        case ITEM_HEART:
        case ITEM_FLOWER:
            entry->flags |= ITEM_FLAG_INSTANT_GET;
            break;
    }

    switch (type) {
        case ITEM_ENTRY_FIXED_NO_TOUCH:
            entry->flags |= ITEM_FLAG_NO_TOUCH;
        case ITEM_ENTRY_FIXED:
            itemModeChange(entry, 7);
            break;
        case ITEM_ENTRY_STAY:
            itemModeChange(entry, 1);
            break;
        case ITEM_ENTRY_STAY_NO_TOUCH:
            itemModeChange(entry, 1);
            entry->flags |= ITEM_FLAG_NO_TOUCH;
            break;
        case ITEM_ENTRY_LAUNCH:
            itemModeChange(entry, 6);
            break;
        case ITEM_ENTRY_BOUNCE_5S:
            entry->timer = 5000;
            itemModeChange(entry, 5);
            break;
        case ITEM_ENTRY_DROP_20S:
            entry->status |= ITEM_STATUS_TIMER_HOLD;
            entry->timer = 20000;
            itemModeChange(entry, 6);
            break;
        case ITEM_ENTRY_DROP_20S_REPLACEABLE:
            entry->status |= ITEM_STATUS_TIMER_HOLD;
            entry->timer = 20000;
            itemModeChange(entry, 6);
            entry->flags |= ITEM_FLAG_REPLACEABLE;
            break;
#if VERSION >= VERSION_JP
        case ITEM_ENTRY_DROP_8S_BADGE_RETURN:
            entry->flags |= ITEM_FLAG_BADGE_RETURN;
#endif
        case ITEM_ENTRY_DROP_8S:
            entry->status |= ITEM_STATUS_TIMER_HOLD;
            entry->timer = 8000;
            itemModeChange(entry, 6);
            break;
        case ITEM_ENTRY_DROP_8S_REPLACEABLE:
            entry->status |= ITEM_STATUS_TIMER_HOLD;
            entry->timer = 8000;
            itemModeChange(entry, 6);
            entry->flags |= ITEM_FLAG_REPLACEABLE;
            break;
        case ITEM_ENTRY_DROP_5S:
            entry->status |= ITEM_STATUS_TIMER_HOLD;
        case ITEM_ENTRY_LAUNCH_5S:
            entry->timer = 5000;
            itemModeChange(entry, 6);
            break;
        case ITEM_ENTRY_LAUNCH_5S_SCATTER:
            entry->timer = 5000;
            entry->status |= ITEM_STATUS_SCATTER;
            itemModeChange(entry, 6);
            break;
        case ITEM_ENTRY_BOUNCE:
            itemModeChange(entry, 5);
            break;
        case ITEM_ENTRY_FALL:
            itemModeChange(entry, 3);
            break;
        case ITEM_ENTRY_FALL_THROWN:
            itemModeChange(entry, 4);
            break;
        case ITEM_ENTRY_POP_VANISH:
            itemModeChange(entry, 10);
            break;
    }
    return entry;
}

/**
 * Removes the named field item (and its name windows);
 * JP, US and PAL first put a dropped badge on sale at the badge shop (itemCheckBadge).
 */
void itemDelete(const char* name) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    int i;

    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (!strcmp(entry->name, name)) {
#if VERSION >= VERSION_JP
            itemCheckBadge(entry);
#endif
            switch (entry->itemId) {
                case ITEM_DIAMOND_STAR:
                case ITEM_EMERALD_STAR:
                case ITEM_GOLD_STAR:
                case ITEM_RUBY_STAR:
                case ITEM_SAPPHIRE_STAR:
                case ITEM_GARNET_STAR:
                case ITEM_CRYSTAL_STAR:
                    effSoftDelete(entry->effect);
                    break;
                default:
                    iconDelete(entry->name);
                    break;
            }
            entry->flags &= ~ITEM_FLAG_USED;
        }
    }
}

/** Returns the field item with this name, or NULL. */
ItemEntry* itemNameToPtr(char* name) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    int i;

    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (!strcmp(entry->name, name)) {
            return entry;
        }
    }
    return NULL;
}

/**
 * Returns an item that is within range of (x, y, z)
 * and not cut off from it by a wall (checked with a collision ray), or NULL;
 * evt_mobj uses it to see whether an item sits on a block.
 */
ItemEntry* itemHitCheck(f32 x, f32 y, f32 z, f32 range) {
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    int i;
    MarioWork* mario;
    ItemEntry* found;
    f32 dx, dy, dz, xzdist, dist;
    f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
    HitEntry* hit;

    mario = marioGetPtr();
    found = NULL;
    for (entry = wp->entries, i = 0; i < wp->count; i++, entry++) {
        if (!(entry->flags & ITEM_FLAG_USED))
            continue;
        if (entry->flags & ITEM_FLAG_NO_TOUCH) {
            do {
            } while (0);
            continue;
        }
        if (entry->status & ITEM_STATUS_PARTY_HOLD)
            continue;
        if (entry->mode == 2)
            continue;
        dx = x - entry->position.x;
        dy = y - entry->position.y;
        dz = z - entry->position.z;
        xzdist = sqrtf(dx * dx + dz * dz);
        dist = sqrtf(dx * dx + dy * dy + dz * dz);
        if (xzdist < range && marioItemGetOk() && marioGetJabaraState() != 1 &&
            marioGetJabaraState() != 4 && marioGetJabaraState() != 5) {
            if (__fabs((y + mario->wPlayerCollisionBox.y * 0.5f) - entry->position.y) < mario->wPlayerCollisionBox.y * 0.5f + 10.0f) {
                hit = NULL;
                if (y < entry->position.y) {
                    hitDist = 10.0f + (entry->position.y - y);
                    if (hitDist > 0.0f) {
                        hit = hitCheckAttr(0x80000000, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f);
                    }
                }
                if (!hit) {
                    found = entry;
                    range = dist;
                }
            }
        }
    }
    return found;
}

/**
 * Returns the nearest collectable item within range of (x, y, z), skipping items Koops's shell must ignore;
 * Ms. Mowz and evt_mobj use it.
 */
ItemEntry* itemNearDistCheck(f32 x, f32 y, f32 z, f32 range) {
    MarioWork* mario = marioGetPtr();
    ItemWork* wp = itemGetWork();
    ItemEntry* entry;
    ItemEntry* found;
    int i;
    Vec itemPos, diff, pos;
    f32 dist;

    entry = wp->entries;
    found = NULL;
    i = 0;
    pos = makeVecByValue2(x, y, z);
    for (; i < wp->count; i++, entry++) {
        if (!(entry->flags & ITEM_FLAG_USED))
            continue;
#if VERSION <= VERSION_DEMO_US
        if (entry->flags & ITEM_FLAG_NO_TOUCH)
            continue;
        if (entry->status & ITEM_STATUS_PARTY_HOLD)
            continue;
        if (entry->mode == 2)
            continue;
#else
        if (entry->status & ITEM_STATUS_PARTY_HOLD)
            continue;
        if (entry->status & ITEM_STATUS_IN_WATER)
            continue;
        if (entry->mode == 2)
            continue;
        if (entry->status & ITEM_STATUS_NO_KOOPS)
            continue;
#endif
        {
            f32 iz, iy, ix;
            ix = entry->position.x;
            iy = entry->position.y;
            iz = entry->position.z;
            itemPos = makeVecByValue(ix, iy, iz);
        }
        PSVECSubtract(&itemPos, &pos, &diff);
        dist = PSVECMag(&diff);
        if (dist < range) {
            found = entry;
            range = dist;
        }
    }
    return found;
}

// US and PAL format the message per language and size the window by its line count
#if VERSION >= VERSION_US

/**
 * Draws the "You got X!" box during an item get, with "badge" wording for badges;
 * this version formats the message per language and sizes the box by its line count.
 */
static void winNameDisp(WinMgrEntry* win) {
    ItemEntry* entry = win->param;
    const char* name;
    u16 width;
    u16 lines;
    char buffer[1024];

    name = msgSearch(itemDataTable[entry->itemId].name);
    if ((u32)gp->language == 0) {
        if (entry->itemId >= BADGE_MIN && entry->itemId < BADGE_MAX) {
            sprintf(buffer, msgSearch("msg_window_badge_get"), name);
        } else {
            sprintf(buffer, msgSearch("msg_window_item_get"), name);
        }
    } else {
        if (entry->itemId >= BADGE_MIN && entry->itemId < BADGE_MAX) {
            strcpy(buffer, msgSearch("msg_window_badge_get"));
        } else {
            strcpy(buffer, msgSearch("msg_window_item_get"));
        }
        evtMsgFmtStr(buffer, name);
    }
    width = FontGetMessageWidthLine(buffer, &lines);
    if (width + 20 > win->width) {
        win->width = width + 20;
        win->x = -win->width / 2;
    }
    win->height = win->description->height + lines * 24;
    if (!winMgrAction(entry->winId[0])) {
        FontDrawStart();
        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
        FontDrawMessage(-width / 2, win->y - 8, buffer);
    }
}

#else
/** Draws the "You got X!" box during an item get, with "badge" wording for badges (JP and demo layout). */
static void winNameDisp(WinMgrEntry* win) {
    ItemEntry* entry = win->param;
    const char* name;
    u16 width;
    char buffer[1024];

    name = msgSearch(itemDataTable[entry->itemId].name);
    if (entry->itemId >= BADGE_MIN && entry->itemId < BADGE_MAX) {
        sprintf(buffer, msgSearch("msg_window_badge_get"), name);
    } else {
        sprintf(buffer, msgSearch("msg_window_item_get"), name);
    }
    width = FontGetMessageWidth(buffer);
    if (width + 20 > win->width) {
        win->width = width + 20;
        win->x = -win->width / 2;
    }
    if (!winMgrAction(entry->winId[0])) {
        FontDrawStart();
        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
        FontDrawMessage(-width / 2, win->y - 8, buffer);
    }
}

#endif

/** US and PAL format the message per language and size the window by its line count */
#if VERSION >= VERSION_US
static void winNameDisp2(WinMgrEntry* win) {
    ItemEntry* entry = win->param;
    const char* name;
    u16 width;
    u16 lines;
    char buffer[1024];

    name = msgSearch(itemDataTable[entry->itemId].name);
    if ((u32)gp->language == 0) {
        sprintf(buffer, msgSearch("msg_window_item_release"), name);
    } else {
        strcpy(buffer, msgSearch("msg_window_item_release"));
        evtMsgFmtStr(buffer, name);
    }
    width = FontGetMessageWidthLine(buffer, &lines);
    if (width + 20 > win->width) {
        win->width = width + 20;
        win->x = -win->width / 2;
    }
    win->height = win->description->height + lines * 24;
    if (!winMgrAction(entry->winId[0])) {
        FontDrawStart();
        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
        FontDrawMessage(-width / 2, win->y - 8, buffer);
    }
}

#else
/** Draws the box that names an item Mario let go of (msg_window_item_release) when his pouch was full. */
static void winNameDisp2(WinMgrEntry* win) {
    ItemEntry* entry = win->param;
    const char* name;
    u16 width;
    char buffer[1024];

    name = msgSearch(itemDataTable[entry->itemId].name);
    sprintf(buffer, msgSearch("msg_window_item_release"), name);
    width = FontGetMessageWidth(buffer);
    if (width + 20 > win->width) {
        win->width = width + 20;
        win->x = -win->width / 2;
    }
    if (!winMgrAction(entry->winId[0])) {
        FontDrawStart();
        FontDrawColor((GXColor){0x00, 0x00, 0x00, 0xFF});
        FontDrawMessage(-width / 2, win->y - 8, buffer);
    }
}

#endif

/** Per-frame update of the item description box shown under the get box. */
static void winHelpMain(WinMgrEntry* win) {
    winMgrHelpMain(win);
}

/** Draws the got item's description in the help box, once the name box has finished opening. */
static void winHelpDisp(WinMgrEntry* win) {
    ItemEntry* entry = win->param;

    if (!winMgrAction(entry->winId[1])) {
        win->msg = msgSearch(itemDataTable[entry->itemId].description);
        winMgrHelpDraw(win);
    }
}

#if VERSION <= VERSION_DEMO_US
/** the demo has no badge-full message */
static void winFullDisp(WinMgrEntry* win) {
    ItemEntry* entry;
    const char* msg;
    u16 width;

    entry = win->param;
    msg = msgSearch("msg_window_item_full");
    width = (u16)FontGetMessageWidth(msg);

    if (width + 20 > win->width) {
        win->width = width + 20;
        win->x = -win->width / 2;
    }
    if (!winMgrAction(entry->winId[2])) {
        FontDrawStart();
        FontDrawEdge();
        FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        FontDrawMessage(-width / 2, win->y - 10, msg);
        FontDrawEdgeOff();
    }
}
#else
/** Draws the "you can't carry any more items/badges" box when the pouch is full. */
static void winFullDisp(WinMgrEntry* win) {
    ItemEntry* entry = win->param;
    BOOL isBadge = FALSE;
    u16 width;
    const char* msg;

    if (entry->itemId >= BADGE_MIN && entry->itemId < BADGE_MAX) {
        isBadge = TRUE;
    }
    msg = isBadge ? msgSearch("msg_window_badge_full") : msgSearch("msg_window_item_full");
    width = FontGetMessageWidth(msg);
    if (width + 20 > win->width) {
        win->width = width + 20;
        win->x = -win->width / 2;
    }
    if (!winMgrAction(entry->winId[2])) {
        FontDrawStart();
        FontDrawEdge();
        FontDrawColor((GXColor){0xFF, 0xFF, 0xFF, 0xFF});
        FontDrawMessage(-width / 2, win->y - 10, msg);
        FontDrawEdgeOff();
    }
}
#endif

#if VERSION <= VERSION_DEMO_US
/**
 * The demo's item-get sequence: no retail sub-states 2 (control off) and 8 (motion abort),
 * so retail 3-7 and 9 are 2-7 here; no badge flag bookkeeping, no item renaming after a swap,
 * and the icon flags are 0x40/0x100 where retail has 0x100/0x200.
 */
static void itemseq_GetItem(ItemEntry* entry) {
    ItemWork* wp = itemGetWork();
    MarioWork* mario;
    s32 type, bgm;
    s32 select;

    mario = marioGetPtr();
    switch (entry->subState) {
        case 0:
            entry->status &= ~ITEM_STATUS_GET_ENDED;
            if (entry->flags & ITEM_FLAG_INSTANT_GET) {
                if (itemGetPouch(entry)) {
                    entry->timer = 0;
                    itemGetSound(entry);
                    itemDelete(entry->name);
                } else {
                    itemModeChange(entry, 4);
                }
                break;
            }
            entry->subState = 1;
            entry->timer = 0;
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
            marioKeyOff();
            marioStSystemLevel(2);
            psndSetFlag(PSND_FLAG_MUTE_SFX);
            if (entry->itemId == ITEM_SUPER_BOOTS || entry->itemId == ITEM_ULTRA_BOOTS || entry->itemId == ITEM_SUPER_HAMMER || entry->itemId == ITEM_ULTRA_HAMMER) {
                entry->status |= ITEM_STATUS_IMPORTANT;
            }
        case 1:
            if (!(entry->flags & ITEM_FLAG_FORCE_GET) || entry->flags & ITEM_FLAG_KOOPS_GET) {
                if (!marioChkItemGetMotion()) {
                    break;
                }
            }
            entry->subState = 2;
            marioChgGetItemMotion();
            {
                f32 y = 50.0f + mario->position.y, z = mario->position.z;
                entry->position.x = mario->position.x;
                entry->position.y = y;
                entry->position.z = z;
            }
            type = 7;
            bgm = -1;
            if (entry->itemId == ITEM_SHINE_SPRITE) {
                type = 4;
                bgm = -1;
            } else if (entry->itemId == ITEM_STAR_PIECE) {
                type = 8;
                bgm = 0;
            } else if (entry->itemId < 0xC) {
                type = 3;
                bgm = 3;
            } else if (entry->itemId < ITEM_DIAMOND_STAR) {
                type = 6;
                bgm = 1;
            } else if (entry->itemId < KEY_ITEM_MAX) {
                type = 0;
                bgm = -1;
            } else if (entry->itemId < ITEM_MAX) {
                type = 7;
                bgm = -1;
            } else if (entry->itemId < BADGE_MAX) {
                type = 5;
                bgm = 2;
            }
            wp->effect = effItemGetEntry(type, mario->position.x, 62.0f + mario->position.y, mario->position.z);
            if (type == 0 || type == 3) {
                if (entry->status & ITEM_STATUS_IMPORTANT) {
                    ((ItemGetWork*)wp->effect->userdata)->camera = 5;
                    marioSetCamId(CAMERA_3D_EFFECTB);
                    iconFlagOn(entry->name, 0x100);
                } else {
                    ((ItemGetWork*)wp->effect->userdata)->camera = 5;
                    marioSetCamId(CAMERA_3D_EFFECTA);
                    iconFlagOn(entry->name, 0x40);
                }
            }
            if (!(entry->flags & ITEM_FLAG_NO_JINGLE)) {
                if (psndBGMChkSilent(0)) {
                    entry->flags |= ITEM_FLAG_BGM_SILENT;
                }
                switch (bgm) {
                    case 0:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_STARPIECE1");
                        break;
                    case 1:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_KEYITEM1");
                        break;
                    case 2:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_BADGE1");
                        break;
                    case 3:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_IMPORTANT_ITEM1");
                        break;
                    default:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_ITEM1");
                        break;
                }
            }
            if (type == 8) {
                evtSetValue(NULL, 0xF5DE01A2, evtGetValue(NULL, 0xF5DE01A2) + 1);
            }
            entry->flags &= ~ITEM_FLAG_JINGLE_DONE;
            itemGetSound(entry);
            entry->winId[0] = winMgrEntry(&itemdrv_window_desc[0]);
            winMgrOpen(entry->winId[0]);
            winMgrSetParam(entry->winId[0], entry);
            if (!(entry->status & ITEM_STATUS_IMPORTANT)) {
                entry->winId[1] = winMgrEntry(&itemdrv_window_desc[1]);
                winMgrOpen(entry->winId[1]);
                winMgrSetParam(entry->winId[1], entry);
            }
            if (!itemGetPouch(entry)) {
                entry->winId[2] = winMgrEntry(&itemdrv_window_desc[2]);
                winMgrOpen(entry->winId[2]);
                winMgrSetParam(entry->winId[2], entry);
            }
            if (entry->itemId == ITEM_WEDDING_RING) {
                iconChange(entry->name, 0x114);
            }
            break;
        case 2:
            if (!(entry->flags & ITEM_FLAG_NO_JINGLE) && !(entry->flags & ITEM_FLAG_JINGLE_DONE)) {
                if (psndBGMChk(1)) {
                    entry->flags |= ITEM_FLAG_JINGLE_DONE;
                    psndBGMOff(PSND_FADE_OUT | PSND_CH(1));
                    if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                        psndBGMOn(PSND_FADE_RESUME | PSND_FADE_UNDIP, NULL);
                    }
                }
            }
            if (winMgrAction(entry->winId[0])) {
                break;
            }
            if (!(keyGetButtonTrg(0) & (PAD_BUTTON_A | PAD_BUTTON_B))) {
                break;
            }
            winMgrCloseAutoDelete(entry->winId[0]);
            if (!(entry->status & ITEM_STATUS_IMPORTANT)) {
                winMgrCloseAutoDelete(entry->winId[1]);
            }
            if (!(entry->flags & ITEM_FLAG_NO_JINGLE) && !(entry->flags & ITEM_FLAG_JINGLE_DONE)) {
                psndBGMOff(PSND_FADE_OUT | PSND_CH(1));
                if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                    psndBGMOn(PSND_FADE_RESUME | PSND_FADE_UNDIP, NULL);
                }
            }
            if (entry->status & ITEM_STATUS_IMPORTANT) {
                entry->subState = 5;
                break;
            }
            if (entry->itemId >= ITEM_MIN && entry->itemId < ITEM_MAX && entry->itemId != ITEM_STAR_PIECE && !swGet(GSWF_ITEM_TUTORIAL_SEEN) && !(gp->flags & GLOBAL_FLAG_KIOSK)) {
                swSet(GSWF_ITEM_TUTORIAL_SEEN);
                entry->subState = 3;
                wp->msgWindowId = msgWindow_Entry(msgSearch("item_first_hit"), 0, 0);
                break;
            }
            effSoftDelete(wp->effect);
            marioSetCamId(4);
            iconFlagOff(entry->name, 0x40);
            if (entry->itemId == ITEM_WEDDING_RING) {
                iconChange(entry->name, 0x115);
            }
            if (entry->status & ITEM_STATUS_IN_POUCH) {
                itemGetEnd(entry);
                itemDelete(entry->name);
                break;
            }
            entry->subState = 4;
            winMgrCloseAutoDelete(entry->winId[2]);
            marioChgStayMotion();
            iconFlagOn(entry->name, 2);
            {
                s32 id = entry->itemId;
                if (id >= 0xF0 && id < 0x153) {
                    wp->select = winMgrSelectEntry(2, id, 1);
                } else {
                    wp->select = winMgrSelectEntry(1, id, 1);
                }
            }
            break;
        case 3:
            if (windowCheckID(wp->msgWindowId)) {
                break;
            }
            effSoftDelete(wp->effect);
            marioSetCamId(4);
            iconFlagOff(entry->name, 0x40);
            itemGetEnd(entry);
            itemDelete(entry->name);
            break;
        case 4:
            select = winMgrSelect(wp->select);
            if (!select) {
                break;
            }
            winMgrSelectDelete(wp->select);
            if (select >= 0) {
                pouchRemoveItem(select);
                itemGetPouch(entry);
                entry->status &= ~ITEM_STATUS_IN_POUCH;
                entry->itemId = select;
                entry->evtCode = 0;
                entry->flags &= ~(ITEM_FLAG_COLLECT_GSWF | ITEM_FLAG_COLLECT_LSWF);
                iconChange(entry->name, itemDataTable[entry->itemId].icon_id);
            }
            entry->speed = 85.0f;
            entry->velocityY = 120.0f;
            entry->bounceFactor = 0.7f;
            entry->gravityScale = 1.0f;
            entry->winId[0] = winMgrEntry(&itemdrv_window_desc[3]);
            winMgrOpen(entry->winId[0]);
            winMgrSetParam(entry->winId[0], entry);
            marioChgGetItemMotion();
            iconFlagOff(entry->name, 2);
            if (mario->flags & MARIO_FLAG_BG_MODE) {
                entry->status |= ITEM_STATUS_NO_Z_MOVE;
            }
            entry->subState = 7;
            break;
        case 5:
            wp->lectureEvt = evtEntryType(all_juyoitem_lecture, 0, 0, 0);
            wp->lectureEvt->lwData[8] = (EvtWord)entry;
            wp->lectureEvt->lwData[9] = (EvtWord)wp->effect;
            psndClearFlag(PSND_FLAG_MUTE_SFX);
            entry->subState = 6;
            break;
        case 6:
            if (evtCheckID(wp->lectureEvt->eventId)) {
                break;
            }
            itemGetEnd(entry);
            itemDelete(entry->name);
            break;
        case 7:
            if (!(keyGetButtonTrg(0) & PAD_BUTTON_A)) {
                break;
            }
            winMgrCloseAutoDelete(entry->winId[0]);
            entry->status |= ITEM_STATUS_THROWN;
            itemModeChange(entry, 6);
            entry->flags &= ~ITEM_FLAG_CUSTOM_BOUNCE;
            if (entry->itemId >= KEY_ITEM_MIN && entry->itemId < KEY_ITEM_MAX) {
                entry->timer = 0;
            } else if (entry->itemId >= BADGE_MIN && entry->itemId < BADGE_MAX) {
                entry->timer = 0;
            } else {
                entry->timer = 20000;
            }
            entry->status |= ITEM_STATUS_GET_ENDED;
            entry->status &= ~ITEM_STATUS_PARTY_HOLD;
            entry->flags &= ~ITEM_FLAG_NO_TOUCH;
            itemGetEnd(entry);
            break;
    }
}
#else
/**
 * The item get sequence, one sub-state per frame:
 * freezes the field, plays Mario's get pose and the get jingle (or the coin/heart sound),
 * shows the name and description boxes, puts the item in the pouch,
 * and when the pouch is full asks which item to throw away; important items end with the key-item explanation.
 */
static void itemseq_GetItem(ItemEntry* entry) {
    ItemWork* wp = itemGetWork();
    MarioWork* mario;
    s32 type, bgm;
    s32 select;

    mario = marioGetPtr();
    switch (entry->subState) {
        case 0:
            entry->status &= ~ITEM_STATUS_GET_ENDED;
            if (entry->flags & ITEM_FLAG_BADGE_RETURN) {
                entry->status |= ITEM_STATUS_SAVED_BADGE_RETURN;
            } else {
                entry->status &= ~ITEM_STATUS_SAVED_BADGE_RETURN;
            }
            entry->flags &= ~ITEM_FLAG_BADGE_RETURN;
            if (entry->flags & ITEM_FLAG_INSTANT_GET) {
                if (itemGetPouch(entry)) {
                    entry->timer = 0;
                    itemGetSound(entry);
                    itemDelete(entry->name);
                } else {
                    itemModeChange(entry, 4);
                }
                break;
            }
            entry->subState = 1;
            entry->timer = 0;
            camGetPtr(CAMERA_2D)->flags |= CAM_FLAG_LETTER_BOX_DISABLE;
            marioKeyOff();
            marioStSystemLevel(2);
            psndSetFlag(PSND_FLAG_MUTE_SFX);
            mario->floorMove.x = 0.0f;
            mario->floorMove.z = 0.0f;
            mario->baseSpeed = 0.0f;
            mario->moveDist = 0.0f;
            if (entry->itemId == ITEM_SUPER_BOOTS || entry->itemId == ITEM_ULTRA_BOOTS || entry->itemId == ITEM_SUPER_HAMMER || entry->itemId == ITEM_ULTRA_HAMMER) {
                entry->status |= ITEM_STATUS_IMPORTANT;
            }
        case 1:
            if (!(entry->flags & ITEM_FLAG_FORCE_GET) || entry->flags & ITEM_FLAG_KOOPS_GET) {
                if (!marioChkItemGetMotion()) {
                    if (mario->currMotionId == MARIO_MOTION_JUMP_SW || (u16)(mario->currMotionId - 6) <= 2 ||
                        mario->currMotionId == MARIO_MOTION_GET_ITEM || mario->currMotionId == MARIO_MOTION_TALK) {
                        entry->subState = 8;
                    }
                    break;
                }
            }
            entry->subState = 2;
            marioChgGetItemMotion();
            {
                f32 y = 50.0f + mario->position.y, z = mario->position.z;
                entry->position.x = mario->position.x;
                entry->position.y = y;
                entry->position.z = z;
            }
            type = 7;
            bgm = -1;
            if (entry->itemId == ITEM_SHINE_SPRITE) {
                type = 4;
                bgm = -1;
            } else if (entry->itemId == ITEM_STAR_PIECE) {
                type = 8;
                bgm = 0;
            } else if (entry->itemId < 0xC) {
                type = 3;
                bgm = 3;
            } else if (entry->itemId < ITEM_DIAMOND_STAR) {
                type = 6;
                bgm = 1;
            } else if (entry->itemId < KEY_ITEM_MAX) {
                type = 0;
                bgm = -1;
            } else if (entry->itemId < ITEM_MAX) {
                type = 7;
                bgm = -1;
            } else if (entry->itemId < BADGE_MAX) {
                type = 5;
                bgm = 2;
            }
            wp->effect = effItemGetEntry(type, mario->position.x, 62.0f + mario->position.y, mario->position.z);
            if (entry->status & ITEM_STATUS_IMPORTANT) {
                ((ItemGetWork*)wp->effect->userdata)->camera = 5;
                iconFlagOn(entry->name, 0x200);
                marioSetCamId(CAMERA_3D_EFFECTB);
            } else {
                ((ItemGetWork*)wp->effect->userdata)->camera = 5;
                iconFlagOn(entry->name, 0x100);
                if (type == 0 || type == 3) {
                    marioSetCamId(CAMERA_3D_EFFECTA);
                }
            }
            if (!(entry->flags & ITEM_FLAG_NO_JINGLE)) {
                if (psndBGMChkSilent(0)) {
                    entry->flags |= ITEM_FLAG_BGM_SILENT;
                }
                switch (bgm) {
                    case 0:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_STARPIECE1");
                        break;
                    case 1:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_KEYITEM1");
                        break;
                    case 2:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_BADGE1");
                        break;
                    case 3:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_IMPORTANT_ITEM1");
                        break;
                    default:
                        if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                            psndBGMOff(PSND_FADE_DIP_TO(40));
                        }
                        psndBGMOn(PSND_FADE_RESTART | PSND_FADE_OUT | PSND_CH(1), "BGM_FF_GET_ITEM1");
                        break;
                }
            }
            if (type == 8) {
                evtSetValue(NULL, 0xF5DE01A2, evtGetValue(NULL, 0xF5DE01A2) + 1);
            }
            entry->flags &= ~ITEM_FLAG_JINGLE_DONE;
            itemGetSound(entry);
            entry->winId[0] = winMgrEntry(&itemdrv_window_desc[0]);
            winMgrOpen(entry->winId[0]);
            winMgrSetParam(entry->winId[0], entry);
            if (!(entry->status & ITEM_STATUS_IMPORTANT)) {
                entry->winId[1] = winMgrEntry(&itemdrv_window_desc[1]);
                winMgrOpen(entry->winId[1]);
                winMgrSetParam(entry->winId[1], entry);
            }
            if (!itemGetPouch(entry)) {
                entry->winId[2] = winMgrEntry(&itemdrv_window_desc[2]);
                winMgrOpen(entry->winId[2]);
                winMgrSetParam(entry->winId[2], entry);
            }
            if (entry->itemId == ITEM_WEDDING_RING) {
#if VERSION >= VERSION_US
                iconChange(entry->name, 0x11B);
#else
                iconChange(entry->name, 0x114);
#endif
            }
            if (!entry->effect) {
                iconNameToPtr(entry->name)->uflags |= ICON_FLAG_ITEM_NO_BLEND;
            }
            break;
        case 2:
            if (!(entry->status & ITEM_STATUS_IMPORTANT)) {
                marioCtrlOff();
                entry->status |= ITEM_STATUS_CTRL_OFF;
            }
            entry->subState = 3;
        case 3:
            if (!(entry->flags & ITEM_FLAG_NO_JINGLE) && !(entry->flags & ITEM_FLAG_JINGLE_DONE)) {
                if (psndBGMChk(1)) {
                    entry->flags |= ITEM_FLAG_JINGLE_DONE;
                    psndBGMOff(PSND_FADE_OUT | PSND_CH(1));
                    if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                        psndBGMOn(PSND_FADE_RESUME | PSND_FADE_UNDIP, NULL);
                    }
                }
            }
            if (winMgrAction(entry->winId[0])) {
                break;
            }
            if (!(keyGetButtonTrg(0) & (PAD_BUTTON_A | PAD_BUTTON_B))) {
                break;
            }
            winMgrCloseAutoDelete(entry->winId[0]);
            if (!(entry->status & ITEM_STATUS_IMPORTANT)) {
                winMgrCloseAutoDelete(entry->winId[1]);
            }
            if (!(entry->flags & ITEM_FLAG_NO_JINGLE) && !(entry->flags & ITEM_FLAG_JINGLE_DONE)) {
                psndBGMOff(PSND_FADE_OUT | PSND_CH(1));
                if (!(entry->flags & ITEM_FLAG_BGM_SILENT)) {
                    psndBGMOn(PSND_FADE_RESUME | PSND_FADE_UNDIP, NULL);
                }
            }
            if (entry->status & ITEM_STATUS_IMPORTANT) {
                entry->subState = 6;
                break;
            }
            if (entry->itemId >= ITEM_MIN && entry->itemId < ITEM_MAX && entry->itemId != ITEM_STAR_PIECE && !swGet(GSWF_ITEM_TUTORIAL_SEEN) && !(gp->flags & GLOBAL_FLAG_KIOSK)) {
                swSet(GSWF_ITEM_TUTORIAL_SEEN);
                entry->subState = 4;
                wp->msgWindowId = msgWindow_Entry(msgSearch("item_first_hit"), 0, 0);
                break;
            }
            effSoftDelete(wp->effect);
            marioSetCamId(4);
            iconFlagOff(entry->name, 0x100);
            if (entry->itemId == ITEM_WEDDING_RING) {
#if VERSION >= VERSION_US
                iconChange(entry->name, 0x11C);
#else
                iconChange(entry->name, 0x115);
#endif
            }
            if (!entry->effect) {
                iconNameToPtr(entry->name)->uflags &= ~ICON_FLAG_ITEM_NO_BLEND;
            }
            if (entry->status & ITEM_STATUS_IN_POUCH) {
                itemGetEnd(entry);
                itemDelete(entry->name);
                break;
            }
            entry->subState = 5;
            winMgrCloseAutoDelete(entry->winId[2]);
            marioChgStayMotion();
            iconFlagOn(entry->name, 2);
            {
                s32 id = entry->itemId;
                if (id >= 0xF0 && id < 0x153) {
                    wp->select = winMgrSelectEntry(2, id, 1);
                } else {
                    wp->select = winMgrSelectEntry(1, id, 1);
                }
            }
            break;
        case 4:
            if (windowCheckID(wp->msgWindowId)) {
                break;
            }
            effSoftDelete(wp->effect);
            marioSetCamId(4);
            iconFlagOff(entry->name, 0x100);
            itemGetEnd(entry);
            itemDelete(entry->name);
            break;
        case 5:
            select = winMgrSelect(wp->select);
            if (!select) {
                break;
            }
            winMgrSelectDelete(wp->select);
            if (select < 0) {
                if (entry->status & ITEM_STATUS_SAVED_BADGE_RETURN) {
                    entry->flags |= ITEM_FLAG_BADGE_RETURN;
                }
            } else {
                pouchRemoveItem(select);
                itemGetPouch(entry);
                entry->status &= ~ITEM_STATUS_IN_POUCH;
                entry->itemId = select;
                entry->evtCode = 0;
                entry->collectFlag = 0;
                entry->flags &= ~(ITEM_FLAG_COLLECT_GSWF | ITEM_FLAG_COLLECT_LSWF);
                iconChange(entry->name, itemDataTable[entry->itemId].icon_id);
                wp->currId++;
                sprintf(iconNameToPtr(entry->name)->name, "_i%05x", wp->currId);
                sprintf(entry->name, "_i%05x", wp->currId);
                entry->flags |= ITEM_FLAG_BADGE_RETURN;
            }
            entry->flags &= ~ITEM_FLAG_FORCE_GET;
            entry->speed = 85.0f;
            entry->velocityY = 120.0f;
            entry->bounceFactor = 0.7f;
            entry->gravityScale = 1.0f;
            entry->winId[0] = winMgrEntry(&itemdrv_window_desc[3]);
            winMgrOpen(entry->winId[0]);
            winMgrSetParam(entry->winId[0], entry);
            marioChgGetItemMotion();
            iconFlagOff(entry->name, 2);
            if (mario->flags & MARIO_FLAG_BG_MODE) {
                entry->status |= ITEM_STATUS_NO_Z_MOVE;
            }
            entry->subState = 9;
            break;
        case 6:
            wp->lectureEvt = evtEntryType(all_juyoitem_lecture, 0, 0, 0);
            wp->lectureEvt->lwData[8] = (EvtWord)entry;
            wp->lectureEvt->lwData[9] = (EvtWord)wp->effect;
            psndClearFlag(PSND_FLAG_MUTE_SFX);
            entry->subState = 7;
            break;
        case 7:
            if (evtCheckID(wp->lectureEvt->eventId)) {
                break;
            }
            itemGetEnd(entry);
            itemDelete(entry->name);
            break;
        case 9:
            if (!(keyGetButtonTrg(0) & PAD_BUTTON_A)) {
                break;
            }
            winMgrCloseAutoDelete(entry->winId[0]);
            entry->status |= ITEM_STATUS_THROWN;
            itemModeChange(entry, 6);
            entry->flags &= ~ITEM_FLAG_CUSTOM_BOUNCE;
            if (entry->itemId >= KEY_ITEM_MIN && entry->itemId < KEY_ITEM_MAX) {
                entry->timer = 0;
            } else if (entry->itemId >= BADGE_MIN && entry->itemId < BADGE_MAX) {
                entry->timer = 0;
            } else {
                entry->timer = 20000;
            }
            entry->status |= ITEM_STATUS_GET_ENDED;
            entry->status &= ~ITEM_STATUS_PARTY_HOLD;
            entry->flags &= ~ITEM_FLAG_NO_TOUCH;
            itemGetEnd(entry);
            break;
        case 8:
            if (mario->flags & MARIO_FLAG_BG_MODE) {
                entry->status |= ITEM_STATUS_NO_Z_MOVE;
            }
            entry->timer = 0;
            if (entry->status & ITEM_STATUS_PARTY_HOLD) {
                itemModeChange(entry, 1);
                entry->status &= ~ITEM_STATUS_LAUNCH;
                entry->status &= ~ITEM_STATUS_THROWN;
                entry->status &= ~ITEM_STATUS_TIMER_HOLD;
                entry->status &= ~ITEM_STATUS_PARTY_HOLD;
                entry->flags &= ~ITEM_FLAG_FORCE_GET;
            } else {
                entry->speed = 85.0f;
                entry->velocityY = 120.0f;
                entry->bounceFactor = 0.7f;
                entry->gravityScale = 1.0f;
                entry->status |= ITEM_STATUS_THROWN;
                itemModeChange(entry, 6);
                entry->flags &= ~ITEM_FLAG_CUSTOM_BOUNCE;
                entry->status &= ~ITEM_STATUS_PARTY_HOLD;
                entry->flags &= ~ITEM_FLAG_NO_TOUCH;
                entry->flags &= ~ITEM_FLAG_FORCE_GET;
            }
            marioStSystemLevel(0);
            psndClearFlag(PSND_FLAG_MUTE_SFX);
            if (entry->status & ITEM_STATUS_CTRL_OFF) {
                entry->status &= ~ITEM_STATUS_CTRL_OFF;
                marioCtrlOn();
            }
            marioKeyOn();
            break;
    }
}
#endif

static s32 _move_dir_1090;
/**
 * Moves a bouncing or falling item: gravity, bouncing off floors (with fewer, lower bounces each time),
 * walls and ceilings, landing on map objects, water and lava, and despawning where needed;
 * becomes resting when it stops.
 */
static void itemseq_Bound(ItemEntry* entry) {
    static s32 _move_dir;
    MarioWork* mario;
    CameraEntry* camera;
    HitEntry* hit;
    MapObjectEntry* mobj;
    BOOL isFloor, bounce;
    s64 delta;
    f32 t2sq, dt, dy, t2, dx, t1;
    f32 dz, v, peak, height;
    f32 newX, newZ;
    s32 newDir;
    Vec pos;
    s32 itemId;

    mario = marioGetPtr();
    camera = camGetPtr(CAMERA_3D);
    switch (entry->subState) {
        case 0:
            entry->subState = 1;
            entry->airTime = 0;
            entry->baseTime = gp->renderTime;
            entry->curTime = gp->renderTime;
            entry->bounceCount = 0;
            if (entry->status & ITEM_STATUS_CUSTOM_LAUNCH) {
                break;
            }
            switch (entry->mode) {
                case 6:
                    entry->status |= ITEM_STATUS_LAUNCH;
                case 5:
                    if (!(entry->flags & ITEM_FLAG_CUSTOM_BOUNCE)) {
                        entry->bounceFactor = 1.0f;
                        entry->gravityScale = 1.0f;
                        entry->maxBounces = 0;
                        entry->velocityY = 500.0f;
                    }
                    if (!(entry->status & ITEM_STATUS_SCATTER)) {
                        switch (entry->itemId) {
                            case ITEM_COIN:
                            case ITEM_HEART:
                            case ITEM_FLOWER:
                                entry->speed = irand(30) + 45;
                                if (irand(100) < 50) {
                                    entry->direction = 90.0f + camera->viewYaw + irand(60) - 30.0f;
                                } else {
                                    entry->direction = camera->viewYaw - 90.0f + irand(60) - 30.0f;
                                }
                                break;
                            default:
                                entry->speed = 100.0f;
                                if (irand(100) < 50) {
                                    entry->direction = 90.0f + camera->viewYaw + irand(30) - 15.0f;
                                } else {
                                    entry->direction = camera->viewYaw - 90.0f + irand(30) - 15.0f;
                                }
                                break;
                        }
#if VERSION >= VERSION_US
                        if (!strcmp(gp->currentMapName, "aji_03")) {
                            entry->direction = irand(90);
                        }
#endif
                    } else {
                        entry->direction = _move_dir;
                        _move_dir += 132;
                        if (_move_dir >= 360) {
                            _move_dir -= 360;
                        }
                        entry->speed = 0.67f * (irand(30) + 65);
                    }
                    break;
                case 4:
                    entry->status |= ITEM_STATUS_THROWN;
                case 3:
                    if (!(entry->flags & ITEM_FLAG_CUSTOM_BOUNCE)) {
                        entry->bounceFactor = 1.0f;
                        entry->gravityScale = 1.0f;
                        entry->maxBounces = 0;
                    }
                    entry->speed = 0.0f;
                    entry->direction = 0;
                    entry->velocityY = 0.0f;
                    break;
                case 10:
                    entry->bounceFactor = 1.0f;
                    entry->gravityScale = 1.0f;
                    entry->maxBounces = 0;
                    entry->velocityY = 500.0f;
                    entry->speed = 0.0f;
                    entry->direction = 0;
                    entry->status |= ITEM_STATUS_VANISH_ON_FALL;
                    entry->status |= ITEM_STATUS_LAUNCH;
                    break;
            }
            break;
        case 1:
            entry->curTime = gp->renderTime;
            delta = entry->curTime - entry->baseTime;
            dt = OSTicksToMicroseconds(delta) / 1000000.0f;
            t1 = OSTicksToMicroseconds(entry->airTime) / 1000000.0f;
            t2 = OSTicksToMicroseconds(entry->airTime + delta) / 1000000.0f;
            dx = dt * (entry->speed * (f32)sin(6.2831855f * entry->direction / 360.0f));
            dz = (f32)cos(6.2831855f * entry->direction / 360.0f);
            dz = dt * (entry->speed * -dz);
            if (entry->status & ITEM_STATUS_NO_Z_MOVE) {
                dz = 0.0f;
            }
            t2sq = t2 * t2;
            dy = entry->velocityY * dt + (-980.0f * entry->gravityScale) * (t2sq - t1 * t1);
            if (entry->status & ITEM_STATUS_LAUNCH) {
                if (entry->bounceCount != 0 || dy < 0.0f) {
                    entry->status &= ~ITEM_STATUS_LAUNCH;
                }
            }
            if (entry->status & ITEM_STATUS_THROWN && entry->bounceCount != 0) {
                entry->status &= ~ITEM_STATUS_THROWN;
            }
            if (entry->status & ITEM_STATUS_VANISH_ON_FALL && dy < 0.0f) {
                effStardustEntry(1, 3, 30, entry->position.x, entry->position.y, entry->position.z, 16.0f, 16.0f);
                itemDelete(entry->name);
                return;
            }
            newDir = entry->direction;
            hit = itemHitCheckSide(entry, &newX, dx, &newZ, dz, &newDir);
            entry->position.x = newX;
            entry->position.z = newZ;
            entry->direction = newDir;
            if (hit) {
                entry->speed *= 0.25f;
            }
            if (!(entry->status & ITEM_STATUS_VANISH_ON_FALL) && !(entry->flags & ITEM_FLAG_NO_CEILING)) {
                {
                    // FAKE: itemHitCheckUp written out here (inlining it leaves the Y block below in the wrong stack order);
                    // h/r are the inline's result copies and keep the same register pressure. hit* declared in reverse for ascending slots.
                    HitEntry* h;
                    HitEntry* r;
                    f32 hitNZ, hitNY, hitNX, hitDist, hitZ, hitY, hitX;
                    f32 x, y, z;

                    if (dy <= 0.0f) {
                        r = NULL;
                    } else {
                        x = entry->position.x;
                        y = 20.0f + entry->position.y;
                        z = entry->position.z;
                        hitDist = 20.0 + fabs(dy);
                        if (h = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
                            entry->position.y = hitY - 20.0f - 4.0f;
                            r = h;
                        } else {
                            x = entry->position.x;
                            y = entry->position.y;
                            z = entry->position.z;
                            hitDist = 20.0 + fabs(dy);
                            if (h = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
                                entry->position.y = hitY - 20.0f;
                                r = h;
                            } else {
                                r = NULL;
                            }
                        }
                    }
                    hit = r;
                }
                if (hit) {
                    entry->velocityY = -entry->velocityY / 4.0f;
                    dy = 0.0f;
                    entry->airTime = 0;
                    entry->baseTime = entry->curTime;
                }
            }
            if (entry->status & ITEM_STATUS_IN_WATER && entry->position.y <= -1000.0f) {
                itemModeChange(entry, 7);
                entry->status &= ~ITEM_STATUS_LAUNCH;
                entry->status &= ~ITEM_STATUS_THROWN;
                entry->status &= ~ITEM_STATUS_TIMER_HOLD;
                if (entry->itemId >= KEY_ITEM_MIN && entry->itemId < KEY_ITEM_MAX) {
                    entry->timer = 0;
                } else if (entry->itemId >= BADGE_MIN && entry->itemId < BADGE_MAX) {
                    entry->timer = 0;
                } else {
                    entry->timer = 20000;
                }
                entry->status |= ITEM_STATUS_GET_ENDED;
                entry->status &= ~ITEM_STATUS_PARTY_HOLD;
#if VERSION >= VERSION_JP
                entry->flags |= ITEM_FLAG_BADGE_RETURN;
#endif
                break;
            }
            if (dy >= 0.0f) {
                hit = NULL;
                entry->position.y += dy;
            }
            // FAKE: no-op u32 cast so the earlier masked status value is not reused (target reloads status here)
            else if (*(u32*)&entry->status & ITEM_STATUS_IN_WATER) {
                hit = NULL;
                entry->position.y += dy;
            } else {
                // FAKE: itemHitCheckY written out here; the result goes through h so the caller's hit is set in each arm
                // (coalesces into r26 like the target). hit* declared in reverse for ascending stack slots.
                f32 hitNZ, hitNY, hitNX, hitDist, hitZ, hitY, hitX;
                HitEntry* h;
                f32 x = entry->position.x, y = 20.0f + entry->position.y, z = entry->position.z;
                hitDist = 20.0 + fabs(dy);
                h = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, -1.0f, 0.0f);
                if (h) {
                    entry->position.y = hitY;
                    hit = h;
                } else {
                    hit = NULL;
                    entry->position.y += dy;
                }
            }
            if (hit) {
                if (hitGetAttr(hit) & (HIT_ATTR_DEEP_WATER | HIT_ATTR_DAMAGE_LIQUID)) {
                    entry->status |= ITEM_STATUS_IN_WATER;
                    {
                        Vec sndPos = (Vec){0.0f, 0.0f, 0.0f};
                        sndPos.x = entry->position.x;
                        sndPos.y = entry->position.y;
                        sndPos.z = entry->position.z;
                        psndSFXOn_3D((const char*)0x194, &sndPos);
                    }
                    effSplashEntry(0, entry->position.x, entry->position.y, entry->position.z, 0.7f);
                    entry->flags |= ITEM_FLAG_NO_TOUCH;
                } else {
                    entry->bounceCount++;
                    if (!(hitGetAttr(hit) & HIT_ATTR_MOBJ) && entry->maxBounces != 0 && entry->bounceCount >= entry->maxBounces) {
                        itemModeChange(entry, 1);
                        entry->status &= ~ITEM_STATUS_LAUNCH;
                        entry->status &= ~ITEM_STATUS_THROWN;
                        entry->status &= ~ITEM_STATUS_TIMER_HOLD;
                        break;
                    }
                    {
                        pos = (Vec){entry->position.x, entry->position.y, entry->position.z};
                        switch (itemId = entry->itemId) {
                            case ITEM_COIN:
                                psndSFXOn_3D("SFX_COIN_LEAPED1", &pos);
                                break;
                            case ITEM_PIANTA_TOKEN:
                                psndSFXOn_3D("SFX_EVT_GAME_MONTE_LEAPED1", &pos);
                                break;
                            case ITEM_HEART:
                                psndSFXOn_3D("SFX_HEART_LEAPED1", &pos);
                                break;
                            case ITEM_FLOWER:
                                psndSFXOn_3D("SFX_FLOWER_LEAPED1", &pos);
                                break;
                            case ITEM_STAR_PIECE:
                                psndSFXOn_3D("SFX_STAR_PIECE_LEAPED1", &pos);
                                break;
                            case ITEM_DIAMOND_STAR:
                            case ITEM_EMERALD_STAR:
                            case ITEM_GOLD_STAR:
                            case ITEM_RUBY_STAR:
                            case ITEM_SAPPHIRE_STAR:
                            case ITEM_GARNET_STAR:
                            case ITEM_CRYSTAL_STAR:
                                psndSFXOn_3D("SFX_EVT_STARSTONE_JUMP1", &pos);
                                break;
                            default:
                                if (itemId >= BADGE_MIN && itemId < BADGE_MAX) {
                                    psndSFXOn_3D("SFX_BADGE_LEAPED1", &pos);
                                } else {
                                    psndSFXOn_3D("SFX_ITEM_LEAPED1", &pos);
                                }
                                break;
                        }
                    }
                    isFloor = FALSE;
                    if (entry->flags & ITEM_FLAG_ELASTIC && entry->velocityY != 0.0f) {
                        bounce = TRUE;
                    } else if (hitGetAttr(hit) & HIT_ATTR_MOBJ && entry->velocityY != 0.0f) {
                        mobj = mobjHitObjPtrToPtr(hit);
                        if (mario->characterId == 2) {
                            bounce = FALSE;
                        } else if (mobj && strcmp(mobj->animName, "MOBJ_KururinFloor")) {
                            bounce = TRUE;
                            isFloor = TRUE;
                        } else {
                            goto no_bounce;
                        }
                    } else {
                    no_bounce:
                        bounce = FALSE;
                    }
                    if (!bounce) {
                        v = entry->velocityY * dt + (-980.0f * entry->gravityScale) * ((t2 + dt) * (t2 + dt) - t2sq);
                        entry->velocityY = 0.7f * (entry->bounceFactor * (-v / dt));
                    }
                    peak = fabs(0.5f * (entry->velocityY / (-980.0f * entry->gravityScale)));
                    height = entry->velocityY * peak + peak * ((-980.0f * entry->gravityScale) * peak);
                    if (!isFloor && height <= 8.0f) {
                        itemModeChange(entry, 1);
                        entry->status &= ~ITEM_STATUS_LAUNCH;
                        entry->status &= ~ITEM_STATUS_THROWN;
                        entry->status &= ~ITEM_STATUS_TIMER_HOLD;
                    }
                    if (entry->flags & ITEM_FLAG_RESTORE_MOTION && entry->bounceCount <= 1) {
                        entry->direction = entry->savedDirection;
                        entry->speed = entry->savedSpeed;
                        entry->flags &= ~ITEM_FLAG_RESTORE_MOTION;
                    }
                    entry->airTime = 0;
                    entry->baseTime = gp->renderTime;
                    break;
                }
            }
            entry->airTime += delta;
            entry->baseTime = entry->curTime;
            break;
    }
    entry->status &= ~ITEM_STATUS_CUSTOM_LAUNCH;
}

/** Moves an item to (x, y, z). */
void itemSetPosition(ItemEntry* entry, f32 x, f32 y, f32 z) {
    entry->position.x = x;
    entry->position.y = y;
    entry->position.z = z;
}

/**
 * Plays an item's pickup sound and sparkle: coins, hearts and flowers have their own sounds;
 * others use the default get sound.
 */
void itemGetSound(ItemEntry* entry) {
    Vec pos;

    pos = (Vec){entry->position.x, entry->position.y, entry->position.z};
    switch (entry->itemId) {
        case ITEM_COIN:
            effStardustEntry(1, 3, 30, entry->position.x, 35.0f + entry->position.y, entry->position.z, 16.0f, 16.0f);
            psndSFXOn_3D("SFX_COIN_GET1", &pos);
            break;
        case ITEM_PIANTA_TOKEN:
            effStardustEntry(1, 3, 30, entry->position.x, 35.0f + entry->position.y, entry->position.z, 16.0f, 16.0f);
            psndSFXOn_3D("SFX_EVT_GAME_MONTE_COUNT1", &pos);
            break;
        case ITEM_HEART:
            psndSFXOn_3D("SFX_HEART_GET1", &pos);
            break;
        case ITEM_FLOWER:
            psndSFXOn_3D("SFX_FLOWER_GET1", &pos);
            break;
        case ITEM_STAR_PIECE:
            break;
    }
}

/**
 * Wall check for a moving item: casts a ray along its motion (dx, dz) and, on a wall,
 * returns the hit and the corrected position and reflected direction (degrees) in outX, outZ and angle.
 */
static HitEntry* itemHitCheckSide(ItemEntry* entry, f32* outX, f32 dx, f32* outZ, f32 dz, s32* angle) {
    HitEntry* hit;
    f32 a, b;
    f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
    f32 sin, cos;
    f32 dot, ox, oz;
    f32 h = 15.0f;

    *outX = entry->position.x;
    *outZ = entry->position.z;
    if (dx == 0.0f && dz == 0.0f) {
        return NULL;
    }
    sincosf(&sin, &cos, angleABf(0.0f, 0.0f, dx, dz));
    hitDist = 10.0f + sqrtf(dx * dx + dz * dz);
    hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ,
                         entry->position.x, entry->position.y + h, entry->position.z, sin, 0.0f, cos);
    if (hit) {
        dot = dx * hitNX + dz * hitNZ;
        ox = 0.5f * (dx - dot * hitNX);
        oz = 0.5f * (dz - dot * hitNZ);
        *outX += ox;
        *outZ += oz;
        a = reviseAngle(180.0f + *angle);
        b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * hitNX, 100.0f * hitNZ));
        *angle = reviseAngle(b + reviseAngle(b - a));
        return hit;
    }
    hitDist = 10.0f + sqrtf(dx * dx + dz * dz);
    hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ,
                         entry->position.x, entry->position.y + h, entry->position.z, sin, 0.0f, cos);
    if (hit) {
        dot = dx * hitNX + dz * hitNZ;
        ox = 0.5f * (dx - dot * hitNX);
        oz = 0.5f * (dz - dot * hitNZ);
        *outX += ox;
        *outZ += oz;
        a = reviseAngle(180.0f + *angle);
        b = reviseAngle(angleABf(0.0f, 0.0f, 100.0f * hitNX, 100.0f * hitNZ));
        *angle = reviseAngle(b + reviseAngle(b - a));
        return hit;
    }
    *outX += dx;
    *outZ += dz;
    return NULL;
}

HitEntry*
itemHitCheckY(ItemEntry* entry, f32 z, f32 y, f32 x, f32 vy) {
    HitEntry* hit;
    f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;

    hitDist = 20.0 + __fabs(vy);
    if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, -1.0f, 0.0f)) {
        entry->position.y = hitY;
    } else {
        hit = NULL;
        entry->position.y += vy;
    }
    return hit;
}

HitEntry*
itemHitCheckUp(ItemEntry* entry, f32 vy) {
    HitEntry* hit;
    f32 hitX, hitY, hitZ, hitDist, hitNX, hitNY, hitNZ;
    f32 x, y, z;

    if (vy <= 0.0f) {
        return NULL;
    }
    x = entry->position.x;
    y = 20.0f + entry->position.y;
    z = entry->position.z;
    hitDist = 20.0 + __fabs(vy);
    if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
        entry->position.y = hitY - 20.0f - 4.0f;
        return hit;
    }
    x = entry->position.x;
    y = entry->position.y;
    z = entry->position.z;
    hitDist = 20.0 + __fabs(vy);
    if (hit = hitCheckFilter(NULL, &hitX, &hitY, &hitZ, &hitDist, &hitNX, &hitNY, &hitNZ, x, y, z, 0.0f, 1.0f, 0.0f)) {
        entry->position.y = hitY - 20.0f;
        return hit;
    }
    return NULL;
}

/**
 * Starts the get sequence for an item at once (collected by a script or partner),
 * without waiting for Mario's get motion.
 */
void itemForceGet(ItemEntry* entry) {
    entry->timer = 0;
    itemModeChange(entry, 2);
    entry->flags |= ITEM_FLAG_FORCE_GET;
    entry->status &= ~ITEM_STATUS_GET_ENDED;
}

/**
 * Koops's shell has fetched the item: starts the get sequence if Mario may collect now,
 * else drops the item back to rest where it is.
 */
void itemNokoForceGet(ItemEntry* entry) {
    if (itemGetNokoCheck(entry)) {
        entry->timer = 0;
        itemModeChange(entry, 2);
        entry->flags |= ITEM_FLAG_FORCE_GET | ITEM_FLAG_KOOPS_GET;
        entry->status &= ~ITEM_STATUS_GET_ENDED;
    } else {
        entry->timer = 0;
        itemModeChange(entry, 1);
        entry->status &= ~ITEM_STATUS_LAUNCH;
        entry->status &= ~ITEM_STATUS_THROWN;
        entry->status &= ~ITEM_STATUS_TIMER_HOLD;
        entry->status &= ~ITEM_STATUS_PARTY_HOLD;
    }
}

/** Sets ITEM_FLAG_* bits on an item. */
void itemFlagOn(ItemEntry* entry, u16 flags) {
    entry->flags |= flags;
}

/** Clears ITEM_FLAG_* bits on an item. */
void itemFlagOff(ItemEntry* entry, u16 flags) {
    entry->flags &= ~flags;
}

/** Returns which of the given ITEM_FLAG_* bits are set on an item. */
u16 itemFlag(ItemEntry* entry, u16 flags) {
    return entry->flags & flags;
}

/** Sets ITEM_STATUS_* bits on an item. */
void itemStatusOn(ItemEntry* entry, u32 flags) {
    entry->status |= flags;
}

/** Returns which of the given ITEM_STATUS_* bits are set on an item. */
u32 itemStatus(ItemEntry* entry, u32 flags) {
    return entry->status & flags;
}

/** A partner picks up the item and carries it (mode 8, following above the partner); it stops blinking. */
void itemPickUp(ItemEntry* entry) {
    entry->status |= ITEM_STATUS_PARTY_HOLD;
    itemModeChange(entry, 8);
    entry->timer = 0;
    entry->status &= ~ITEM_STATUS_BLINK_HIDDEN;
}
