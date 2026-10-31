// Script commands for Mario's pouch: coins, star pieces, items, badges, HP/FP, partners and mail.
#include "evt/evt_pouch.h"
#include "evt/evt_cmd.h"
#include "mario/mario_party.h"
#include "mario/mario_pouch.h"
#include "manager/evtmgr_cmd.h"
#include "version.h"

typedef s32 (*GetFn)(void);
typedef s32 (*SetFn)(s32);
#define RAW_GET(fn) ((GetFn)fn)
#define RAW_SET(fn) ((SetFn)fn)

#define GET_ARG0 evtGetValue(event, event->args[0])

#define SETTER(name, fn)        \
    USER_FUNC(name) {           \
        fn(GET_ARG0);           \
        return EVT_RETURN_DONE; \
    }

#define GETTER(name, fn)                   \
    USER_FUNC(name) {                      \
        EvtWord* args = event->args;       \
        evtSetValue(event, args[0], fn()); \
        return EVT_RETURN_DONE;            \
    }

// Simple pouch accessors: each GETTER writes the pouch value to args[0], each SETTER passes args[0] on.
// Super coins are Shine Sprites. evt_pouch_get_starstone is a setter despite its name: it gives Crystal Star args[0].
GETTER(evt_pouch_get_coin, pouchGetCoin)
SETTER(evt_pouch_add_coin, RAW_SET(pouchAddCoin))
SETTER(evt_pouch_set_coin, pouchSetCoin)
GETTER(evt_pouch_get_supercoin, RAW_GET(pouchGetSuperCoin))
SETTER(evt_pouch_set_supercoin, RAW_SET(pouchSetSuperCoin))
GETTER(evt_pouch_get_starpiece, RAW_GET(pouchGetStarPiece))
SETTER(evt_pouch_add_starpiece, RAW_SET(pouchAddStarPiece))
SETTER(evt_pouch_get_starstone, pouchGetStarStone)

/**
 * Gives Mario item, key item or badge args[0] through pouchGetItem;
 * args[1] gets 0 if it was added and -1 if there was no room.
 */
USER_FUNC(evt_pouch_add_item) {
    EvtWord* args = event->args;
    if (pouchGetItem(evtGetValue(event, args[0])) == 1) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], -1);
    }
    return EVT_RETURN_DONE;
}

/**
 * Takes one of item args[0] from the pouch and re-clamps Mario's
 * and the partners' stats (a removed badge can lower max HP/FP);
 * args[1] gets 0 on success or -1 if Mario had none.
 */
USER_FUNC(evt_pouch_remove_item) {
    EvtWord* args = event->args;
    if (pouchRemoveItem(evtGetValue(event, args[0])) == 1) {
        pouchReviseMarioParam();
        pouchRevisePartyParam();
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], -1);
    }
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/**
 * Retail only: removes item args[0] from slot args[1] of the held list (the slot the shop's sell menu picked)
 * and re-clamps stats; args[2] gets 0 on success or -1 if that slot holds something else.
 */
USER_FUNC(N_evt_pouch_remove_item_index) {
    EvtWord* args = event->args;
    s32 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    if (pouchRemoveItemIndex(a, b) == 1) {
        pouchReviseMarioParam();
        pouchRevisePartyParam();
        evtSetValue(event, args[2], 0);
    } else {
        evtSetValue(event, args[2], -1);
    }
    return EVT_RETURN_DONE;
}
#endif

/**
 * Puts item args[0] into storage (the items kept at the Rogueport item storage);
 * args[1] gets 0 if it fit or -1 if storage is full.
 */
USER_FUNC(evt_pouch_add_keepitem) {
    EvtWord* args = event->args;
    if (RAW_SET(pouchAddKeepItem)(evtGetValue(event, args[0]))) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], -1);
    }
    return EVT_RETURN_DONE;
}

/**
 * Takes item args[0] out of storage; args[1] (US demo and older: the result) gets 0 on success or -1.
 * Later versions take the storage slot in args[1], close the gap in the list, and return the result in args[2].
 */
USER_FUNC(evt_pouch_remove_keepitem) {
    EvtWord* args = event->args;
#if VERSION <= VERSION_DEMO_JP
    if (pouchRemoveKeepItem(evtGetValue(event, args[0]))) {
        evtSetValue(event, args[1], 0);
    } else {
        evtSetValue(event, args[1], -1);
    }
#else
    s32 a = evtGetValue(event, args[0]);
    s32 b = evtGetValue(event, args[1]);
    if (pouchRemoveKeepItem(a, b)) {
        evtSetValue(event, args[2], 0);
    } else {
        evtSetValue(event, args[2], -1);
    }
#endif
    return EVT_RETURN_DONE;
}

/** Counts how many of item args[0] Mario carries (held items, or whether he has a key item/badge) into args[1]. */
USER_FUNC(evt_pouch_check_item) {
    EvtWord* args = event->args;
    evtSetValue(event, args[1], pouchCheckItem(evtGetValue(event, args[0])));
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
GETTER(L_evt_pouch_get_hp, RAW_GET(pouchGetHP))
SETTER(L_evt_pouch_set_hp, RAW_SET(pouchSetHP))
#endif
GETTER(evt_pouch_get_max_ap, RAW_GET(pouchGetMaxAP))
SETTER(evt_pouch_set_ap, RAW_SET(pouchSetAP))
SETTER(evt_pouch_party_join, partyJoin)
SETTER(evt_pouch_party_left, partyLeft)

/** Refills Mario's HP, FP and star power (AP) to their maximums, as an inn or a heart block does. */
USER_FUNC(evt_pouch_mario_recovery) {
    pouchSetHP(pouchGetMaxHP());
    pouchSetFP(pouchGetMaxFP());
    pouchSetAP(pouchGetMaxAP());
    return EVT_RETURN_DONE;
}

/** Refills the HP of all eight partner slots to their maximums. */
USER_FUNC(evt_pouch_all_party_recovery) {
    PouchData* pouch = pouchGetPtr();
    int i;
    for (i = 0; i < 8; i++) {
        pouch->partyData[i].currentHP = pouch->partyData[i].maximumHP;
    }
    return EVT_RETURN_DONE;
}

GETTER(evt_pouch_get_haveitemcnt, pouchGetHaveItemCnt)
GETTER(evt_pouch_get_havebadgecnt, pouchGetHaveBadgeCnt)
GETTER(evt_pouch_get_equipbadgecnt, pouchGetEquipBadgeCnt)
SETTER(evt_pouch_majinai_set, pouchMajinaiInit)
SETTER(evt_pouch_receive_mail, pouchReceiveMail)
SETTER(evt_pouch_open_mail, pouchOpenMail)
/** Stores the name string args[0] as the Yoshi partner's name, after the player names him at the hatching. */
USER_FUNC(evt_pouch_set_yoshiname) {
    pouchSetYoshiName((char*)GET_ARG0);
    return EVT_RETURN_DONE;
}
/** Returns a pointer to the Yoshi partner's name string in args[0], for messages that print it. */
USER_FUNC(evt_pouch_get_yoshiname) {
    EvtWord* args = event->args;
    evtSetValue(event, args[0], (EvtWord)pouchGetYoshiName());
    return EVT_RETURN_DONE;
}
