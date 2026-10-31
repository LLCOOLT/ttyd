// tou: Glitz Pit REL shared code and prolog/epilog; also the fighter ranking tables (init, reset, sort).
// Registers the init events of tou_00..tou_20 (the arena tou_03 lives in the tou2 REL).

#include "version.h"
#include "mario/mariost.h"
#include "battle/battle_unit.h"
#include "evt/evt_cmd.h"

#include "data/mapdata.h"
#include "driver/swdrv.h"
#include "memory.h"
#include "manager/evtmgr_cmd.h"
#include "string.h"
#include "mario/mario_pouch.h"
#include "driver/msgdrv.h"
#include "stdlib.h"
#include "manager/fontmgr.h"
#include "driver/windowdrv.h"
#include "driver/icondrv.h"
#include "driver/camdrv.h"
#include "dolphin/gx.h"
#include "dolphin/pad.h"
#include "dolphin/mtx.h"
#include "stdio.h"
#include "system.h"
#include "pmario_sound.h"
#include "driver/dispdrv.h"
#include "driver/npcdrv.h"
#include "driver/animdrv.h"
#include "driver/mapdrv.h"
#include "mario/mario.h"
#include "manager/evtmgr.h"
#include "driver/effdrv.h"
#include "driver/itemdrv.h"
#include "icon_ids.h"
#include "evt/evt_bero.h"
#include "evt/evt_sub.h"
#include "eff/eff_starstone.h"
#include "evt/evt_cam.h"
#include "evt/evt_case.h"
#include "evt/evt_eff.h"
#include "evt/evt_hit.h"
#include "evt/evt_item.h"
#include "evt/evt_map.h"
#include "evt/evt_mario.h"
#include "evt/evt_msg.h"
#include "evt/evt_npc.h"
#include "evt/evt_party.h"
#include "party.h"
#include "evt/evt_pouch.h"
#include "evt/evt_seq.h"
#include "evt/evt_snd.h"
#include "tou.h"
#include "map/tou_ranking.h"
#include "mario/mario_party.h"
#include "libc_decls.h"
#include "evt/evt_story.h"
#include "rel_module.h"
#include "driver/casedrv.h"

static void rankingInit(void);
void rankingInit(void);
static RankData* rank_wp;
static void rankingExit(void);
static RankDispWork* dwp;
static FighterData fighterDt[23];
static FighterData fighterDt_re[21];
static void rankingControll(void);
#define GET_RANK(rank, i)                        \
    rank = 0;                                    \
    for (i = 0; i < rank_wp->count; i++) {       \
        if (!(rank_wp->entries[i].flags & 2)) {  \
            if (rank_wp->entries[i].flags & 4) { \
                break;                           \
            }                                    \
            rank++;                              \
        }                                        \
    }
static void insert(s32* list, s32 num, s32 from, s32 to);
#define SORT_SCORE(list, n)                                                                        \
    for (i = 0; i < n - 1; i++) {                                                                  \
        for (j = i + 1; j < n; j++) {                                                              \
            if (rank_wp->entries[list[i]].points.total < rank_wp->entries[list[j]].points.total) { \
                tmp = list[i];                                                                     \
                list[i] = list[j];                                                                 \
                list[j] = tmp;                                                                     \
            }                                                                                      \
        }                                                                                          \
    }
#define SORT_FLAG(list, n)                                                                \
    for (i = 0; i < n - 1; i++) {                                                         \
        for (j = i + 1; j < n; j++) {                                                     \
            pb = &fighterDt[rank_wp->entries[list[i]].id];                                \
            if ((fighterDt[rank_wp->entries[list[j]].id].flags & 5) && (pb->flags & 2)) { \
                tmp = list[i];                                                            \
                list[i] = list[j];                                                        \
                list[j] = tmp;                                                            \
            }                                                                             \
        }                                                                                 \
    }
#define FIND_FLAG(k, list, n, flag)                                 \
    for (k = 0; k < n; k++) {                                       \
        if (fighterDt[rank_wp->entries[list[k]].id].flags & flag) { \
            break;                                                  \
        }                                                           \
    }
#define MOVE_FLAG(list, n, flag, pos) \
    FIND_FLAG(k, list, n, flag);      \
    if (k < n) {                      \
        insert(list, n, k, pos);      \
    }
static void printRanking(void);
static RuleData ruleDt_2bu[10];
static RuleData ruleDt_1bu[14];
static RuleData ruleDt_re[14];
static s32 tou_bss_1C;
static RankData rank_work;
static RankDispWork disp_work;
typedef struct GansWork {
    smartEntry* buf;
    GXTexObj tex;
    s32 onoff;
    s32 alpha;
    s32 ready;
} GansWork;
GansWork* gans_wp;
typedef struct StarStoneWork {
    u8 typeFlags[8];
    Vec pos;
    u8 scaleParams[8];
    f32 rot;
} StarStoneWork; /* mirrors EffStarStoneWork: type + flags, then scale + f18 */
static s32 champion_belt_onoff;

static USER_FUNC(chk);
static USER_FUNC(evt_rankingReInit);
static USER_FUNC(evt_tou_get_fighter_rank);
static USER_FUNC(evt_tou_get_next_match);
static USER_FUNC(evt_tou_get_rule_info);
static USER_FUNC(evt_tou_print_ranking);
static USER_FUNC(getYoshiColor);
static USER_FUNC(make_monitor);
static USER_FUNC(onoff);
#if VERSION >= VERSION_JP
USER_FUNC(tou_mario_keyoff_check);
USER_FUNC(tou_mario_free_wait);
#endif
#if VERSION >= VERSION_US
USER_FUNC(tou_mario_talk_end_wait);
#endif
static USER_FUNC(tou_champion_belt_onoff);
static void monitor_tev(MapTevCallbackInfo* info);
static USER_FUNC(evt_tou_set_rule_result);
static USER_FUNC(evt_tou_set_ranking_win_lose);
static USER_FUNC(evt_tou_get_fighter_battle_msg);
static USER_FUNC(evt_tou_get_fighter_name2);

const char* lockerDt[46];
static EvtWord evt_open[VERSION_PICK(165, 173)];
extern EvtWord evt_doku_cake[];
extern EvtWord evt_michel_1[];

/**
 * Glitz Pit REL prolog: runs the static constructors,
 * registers the init scripts of tou_00 to tou_20 with the map loader (tou_03, the ring, is in the tou2 REL)
 * and builds the fighter ranking from the saved story flags.
 */
void _prolog(void) {
    voidfunctionptr* ctor;

    for (ctor = _ctors; *ctor != NULL; ctor++) {
        (*ctor)();
    }
    relSetEvtAddr("tou_00", tou_00_init_evt);
    relSetEvtAddr("tou_01", tou_01_init_evt);
    relSetEvtAddr("tou_02", tou_02_init_evt);
    relSetEvtAddr("tou_04", tou_04_init_evt);
    relSetEvtAddr("tou_05", tou_05_init_evt);
    relSetEvtAddr("tou_06", tou_06_init_evt);
    relSetEvtAddr("tou_07", tou_07_init_evt);
    relSetEvtAddr("tou_08", tou_08_init_evt);
    relSetEvtAddr("tou_09", tou_09_init_evt);
    relSetEvtAddr("tou_10", tou_10_init_evt);
    relSetEvtAddr("tou_11", tou_11_init_evt);
    relSetEvtAddr("tou_12", tou_12_init_evt);
    relSetEvtAddr("tou_13", tou_13_init_evt);
    relSetEvtAddr("tou_20", tou_20_init_evt);
    rankingInit();
}

/** Glitz Pit REL epilog: writes the ranking back into the saved flags, then runs the static destructors. */
void _epilog(void) {
    voidfunctionptr* dtor;

    rankingExit();
    for (dtor = _dtors; *dtor != NULL; dtor++) {
        (*dtor)();
    }
}

/** Unresolved-import stub for the REL linker; does nothing. */
void _unresolved(void) {
}

/**
 * Builds rank_wp, the Glitz Pit fighter ranking:
 * 23 entries before Chapter 3 ends (Return to Rogueport), 21 afterwards.
 * Restores each fighter's lost-flag and score from saved flags (or the initial points of fighterDt),
 * hides Swoops and Spinia until the story reaches them, and sorts the board via rankingControll.
 */
static void rankingInit(void) {
    s32 i;
    s32 j;
    RankEntry* entry;

    memset(rank_wp, 0, sizeof(RankData));
    rank_wp->count = evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT ? 23 : 21;
    rank_wp->entries = _mapAlloc(rank_wp->count * sizeof(RankEntry));
    memset(rank_wp->entries, 0, rank_wp->count * sizeof(RankEntry));
    entry = rank_wp->entries;
    for (i = 0; i < rank_wp->count; i++, entry++) {
        entry->flags = 0;
        entry->id = i;
        if (swGet(entry->id + GSWF_TOU_FIGHTER_BELOW_BASE)) {
            entry->flags |= 1;
        }
        if (swGet(GSWF_TOU_RANKING_SAVED)) {
            for (j = 0; j < 2; j++) {
                entry->points.bytes[j] = swByteGet(j + (entry->id * 2 + GSW_TOU_FIGHTER_POINTS_BASE));
            }
        } else {
            entry->points.total = fighterDt[entry->id].initPoints;
        }
        if (entry->id == 20) {
            entry->flags |= 4;
        }
    }
    swSet(GSWF_TOU_RANKING_SAVED);
    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT) {
        rank_wp->entries[21].flags |= 2;
        rank_wp->entries[22].flags |= 2;
        if (evtGetValue(NULL, GSWF(GSWF_TOU_RANK12_KING_K_GONE))) {
            rank_wp->entries[18].flags |= 2;
        }
        if (evtGetValue(NULL, GSWF(GSWF_TOU_RANK11_SWOOPS_JOINS))) {
            rank_wp->entries[21].flags &= ~2;
            if (!evtGetValue(NULL, GSWF(GSWF_TOU_SWOOPS_ADDED))) {
                rank_wp->entries[21].flags |= 1;
            }
            evtSetValue(NULL, GSWF(GSWF_TOU_SWOOPS_ADDED), 1);
        }
#if VERSION <= VERSION_DEMO_US
        if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) >= STORY_STG3_20_06_RAWK_HAWKS_WARNING) {
#else
        if (evtGetValue(NULL, GSWF(GSWF_TOU_MAIL4_RECEIVED))) {
#endif
            rank_wp->entries[11].flags |= 2;
            rank_wp->entries[22].flags &= ~2;
            if (!evtGetValue(NULL, GSWF(GSWF_TOU_SPINIA_ADDED))) {
                rank_wp->entries[22].flags |= 1;
            }
            evtSetValue(NULL, GSWF(GSWF_TOU_SPINIA_ADDED), 1);
        }
    }
    rankingControll();
}

/**
 * Saves the ranking back to the game state: each fighter's "has fallen below" flag and two score bytes,
 * then frees the entry array.
 */
static void rankingExit(void) {
    s32 i;
    s32 j;
    RankEntry* entry = rank_wp->entries;

    for (i = 0; i < rank_wp->count; i++, entry++) {
        if (entry->flags & 1) {
            swSet(entry->id + GSWF_TOU_FIGHTER_BELOW_BASE);
        } else {
            swClear(entry->id + GSWF_TOU_FIGHTER_BELOW_BASE);
        }
        for (j = 0; j < 2; j++) {
            swByteSet(j + (entry->id * 2 + GSW_TOU_FIGHTER_POINTS_BASE), entry->points.bytes[j]);
        }
    }
    _mapFree(rank_wp->entries);
}

/** Script helper (no arguments): saves and rebuilds the ranking, so story-flag changes made by a script take effect. */
static USER_FUNC(evt_rankingReInit) {
    rankingExit();
    rankingInit();
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/**
 * Script helper (no arguments): resets the Glitz Pit to its starting state.
 * Removes item 0x41 from the pouch, clears every fighter's lost flag
 * and the first-match/champion/title-match/last-opponent flags, then rebuilds the ranking.
 */
USER_FUNC(evt_rankingReset) {
    s32 i;

    rankingExit();
    pouchRemoveItem(0x41);
    for (i = 0; i < 20; i++) {
        swClear(i + GSWF_TOU_FIGHTER_BELOW_BASE);
    }
    swClear(GSWF_TOU10_FIRST_MATCH_AFTER_SEEN);
    swClear(GSWF_TOU_CHAMP_OPENING_SEEN);
    swClear(GSWF_TOU_CHAMP_WIN_SEEN);
    swClear(GSWF_TOU_TITLE_MATCH_RESERVED);
    swClear(GSWF_TOU_RANKING_SAVED);
    swClear(GSWF_TOU_LAST_OPPONENT_VALID);
    swClear(GSWF_TOU02_LOBBY_CROWD_CHAMP_SEEN);
    rankingInit();
    return EVT_RETURN_DONE;
}
#endif

/** Moves list[from] to position `to`, shifting the entries in between by one (the ranking's reorder primitive). */
static void insert(s32* list, s32 num, s32 from, s32 to) {
    s32 i;

    if (from < to) {
        s32 tmp = list[from];
        for (i = from; i < to; i++) {
            list[i] = list[i + 1];
        }
        list[to] = tmp;
    } else {
        s32 tmp = list[from];
        for (i = from; i > to; i--) {
            list[i] = list[i - 1];
        }
        list[to] = tmp;
    }
}

/**
 * Re-sorts the ranking.
 * Fighters who are still above Mario ("win" group) are ordered by score
 * and some are pinned to fixed slots (the champion first, then slots 1, 10, 14, 18,
 * 19 for the flagged fighters); the last opponent is pushed to the end of its group.
 * Mario's marker (id 20) sits between the two groups and his rank goes to GSW_TOU_PLAYER_RANK.
 */
static void rankingControll(void) {
    s32 win[32];
    s32 lose[32];
    s32 nwin = 0;
    s32 nlose = 0;
    s32 i;
    s32 j;
    s32 m;
    s32 k;
    s32 tmp;
    FighterData* pb;
    RankEntry* entry;
    RankEntry* work;

    entry = rank_wp->entries;
    for (i = 0; i < rank_wp->count; i++, entry++) {
        if (!(entry->flags & 4)) {
            if (entry->flags & 1) {
                lose[nlose++] = i;
            } else {
                win[nwin++] = i;
            }
        }
    }
    if (nwin > 0) {
        SORT_SCORE(win, nwin);
        SORT_FLAG(win, nwin);
        if (nwin > 0) {
            MOVE_FLAG(win, nwin, 0x4, 0);
        }
        if (nwin > 1) {
            MOVE_FLAG(win, nwin, 0x1000, 1);
        }
        if (nwin > 10) {
            MOVE_FLAG(win, nwin, 0x800, 10);
        }
        if (nwin > 18) {
            MOVE_FLAG(win, nwin, 0x200, 18);
        }
        if (nwin > 19) {
            MOVE_FLAG(win, nwin, 0x400, 19);
        }
        if (nwin > 16) {
            MOVE_FLAG(win, nwin, 0x100, 14);
        }
        if (swGet(GSWF_TOU_LAST_OPPONENT_VALID)) {
            for (i = 0; i < nwin; i++) {
                if (win[i] == swByteGet(GSW_TOU_LAST_OPPONENT_ID)) {
                    break;
                }
            }
            if (i < nwin) {
                insert(win, nwin, i, nwin - 1);
            }
        }
    }
    if (nlose > 0) {
        SORT_SCORE(lose, nlose);
        SORT_FLAG(lose, nlose);
        if (nlose > 0) {
            MOVE_FLAG(lose, nlose, 0x4, 0);
        }
        if (nlose > 0) {
            FIND_FLAG(m, lose, nlose, 0x800);
            if (m < nlose) {
                FIND_FLAG(k, lose, nlose, 0x2);
                if (k < nlose && k > 0) {
                    insert(lose, nlose, m, k - 1);
                }
            }
        }
        if (swGet(GSWF_TOU_LAST_OPPONENT_VALID)) {
            for (i = 0; i < nlose; i++) {
                if (lose[i] == swByteGet(GSW_TOU_LAST_OPPONENT_ID)) {
                    break;
                }
            }
            if (i < nlose) {
                insert(lose, nlose, i, 0);
            }
        }
    }
    work = __memAlloc(HEAP_DEFAULT, rank_wp->count * sizeof(RankEntry));
    for (i = 0; i < nwin; i++) {
        work[i] = rank_wp->entries[win[i]];
    }
    work[nwin].flags = 4;
    work[nwin].id = 20;
    work[nwin].points.total = 0;
    for (i = 0; i < nlose; i++) {
        work[nwin + 1 + i] = rank_wp->entries[lose[i]];
    }
    memcpy(rank_wp->entries, work, rank_wp->count * sizeof(RankEntry));
    __memFree(HEAP_DEFAULT, work);
    GET_RANK(j, i);
    swByteSet(GSW_TOU_PLAYER_RANK, j);
}

/** Script helper: args[0] receives Mario's current rank (0 = the champion's seat). */
USER_FUNC(evt_tou_get_ranking) {
    EvtWord* args = event->args;
    s32 rank;
    s32 i;

    GET_RANK(rank, i);
    evtSetValue(event, args[0], rank);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] receives the id of the fighter Mario fights next:
 * the one ranked just above him, or the one just below
 * after the last rule was not met (GSWF_TOU_LAST_RULE_MET clear). Mario at rank 0 gets the second fighter.
 */
static USER_FUNC(evt_tou_get_next_match) {
    EvtWord* args = event->args;
    s32 flag = evtGetValue(event, GSWF(GSWF_TOU_LAST_RULE_MET));
    s32 rank;
    RankEntry* entry;
    s32 i;
    s32 n = 0;
    s32 list[32];

    for (i = 0; i < rank_wp->count; i++) {
        entry = &rank_wp->entries[i];
        if (!(entry->flags & 2)) {
            list[n++] = entry->id;
        }
    }
    GET_RANK(rank, i);
    if (rank > 0) {
        if (flag) {
            evtSetValue(event, args[0], list[rank - 1]);
#if VERSION <= VERSION_DEMO_US
        } else if (rank != n - 1) {
#else
        } else if (rank + 1 < n) {
#endif
            evtSetValue(event, args[0], list[rank + 1]);
        } else {
            evtSetValue(event, args[0], list[rank - 1]);
        }
    } else {
        evtSetValue(event, args[0], list[1]);
    }
    printRanking();
    return EVT_RETURN_DONE;
}

/** Script helper: args[0] = fighter id; args[1] receives the fighter's name string, args[2] its battle setup id. */
USER_FUNC(evt_tou_get_fighter_info) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    FighterData* dt;

    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT) {
        dt = fighterDt;
    } else {
        dt = fighterDt_re;
    }
    evtSetValue(event, args[1], (EvtWord)msgSearch(dt[id].name));
    evtSetValue(event, args[2], fighterDt[id].setupId);
    return EVT_RETURN_DONE;
}

/** Script helper: args[0] = fighter id; args[1] receives the fighter's title (second name string). */
static USER_FUNC(evt_tou_get_fighter_name2) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    FighterData* dt;

    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT) {
        dt = fighterDt;
    } else {
        dt = fighterDt_re;
    }
    evtSetValue(event, args[1], (EvtWord)msgSearch(dt[id].title));
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] = fighter id; args[1] receives that fighter's current position on the board (hidden
 * fighters are skipped).
 */
static USER_FUNC(evt_tou_get_fighter_rank) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 rank = 0;
    s32 i;
    RankEntry* entry;

    for (i = 0; i < rank_wp->count; i++) {
        entry = &rank_wp->entries[i];
        if (!(entry->flags & 2)) {
            if (id == entry->id) {
                break;
            }
            rank++;
        }
    }
    evtSetValue(event, args[1], rank);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] = fighter id; args[1] and args[2] receive the fighter's pre-match taunt
 * and victory message ids.
 */
static USER_FUNC(evt_tou_get_fighter_battle_msg) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    FighterData* dt;

    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT) {
        dt = fighterDt;
    } else {
        dt = fighterDt_re;
    }
    evtSetValue(event, args[1], (EvtWord)dt[id].taunt);
    evtSetValue(event, args[2], (EvtWord)dt[id].victory);
    return EVT_RETURN_DONE;
}

/**
 * Script helper: picks a match rule for the registration.
 * args[0] = mode (0 forces the rule with id 6, 10 excludes the special ids 0x20/0x30/0x40,
 * anything else is random); returns name (args[1]),
 * rule id (args[2]) and the two rule parameters (args[3], args[4]).
 * The table depends on Mario's rank and the story.
 */
static USER_FUNC(evt_tou_get_rule_info) {
    EvtWord* args = event->args;
    s32 mode = evtGetValue(event, args[0]);
    s32 num;
    RuleData* dt;
    s32 i;
    s32 rank;

    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT) {
#if VERSION <= VERSION_DEMO_US
        // the demo also counts the fighters taken out of the ranking
        for (i = 0; i < rank_wp->count; i++) {
            if (rank_wp->entries[i].flags & 4) {
                break;
            }
        }
        rank = i;
#else
        GET_RANK(rank, i);
#endif
        if (rank > 10) {
            num = 10;
            dt = ruleDt_2bu;
        } else {
            num = 14;
            dt = ruleDt_1bu;
        }
    } else {
        num = 14;
        dt = ruleDt_re;
    }
    if (mode == 0) {
        for (i = 0; i < num; i++) {
            if (dt[i].id == 6) {
                break;
            }
        }
    } else if (mode == 10) {
        while (TRUE) {
            i = rand() % num;
            if (dt[i].id != 0x30 && dt[i].id != 0x20 && dt[i].id != 0x40) {
                break;
            }
        }
    } else {
        i = rand() % num;
    }
    evtSetValue(event, args[1], (EvtWord)dt[i].name);
    evtSetValue(event, args[2], dt[i].id);
    evtSetValue(event, args[3], dt[i].param);
    evtSetValue(event, args[4], dt[i].param2);
    return EVT_RETURN_DONE;
}

/** Script helper: args[0] = rule id; args[1] receives the message string describing that rule's conditions. */
USER_FUNC(evt_tou_get_rule_msg2) {
    EvtWord* args = event->args;
    s32 id = evtGetValue(event, args[0]);
    s32 num;
    RuleData* dt;
    s32 i;
    s32 rank;

    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT) {
#if VERSION <= VERSION_DEMO_US
        // the demo also counts the fighters taken out of the ranking
        for (i = 0; i < rank_wp->count; i++) {
            if (rank_wp->entries[i].flags & 4) {
                break;
            }
        }
        rank = i;
#else
        GET_RANK(rank, i);
#endif
        if (rank > 10) {
            num = 10;
            dt = ruleDt_2bu;
        } else {
            num = 14;
            dt = ruleDt_1bu;
        }
    } else {
        num = 14;
        dt = ruleDt_re;
    }
    for (i = 0; i < num; i++) {
        if (id == dt[i].id) {
            break;
        }
    }
    if (i == num) {
        i = num - 1;
    }
    evtSetValue(event, args[1], (EvtWord)msgSearch(dt[i].desc));
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] = 0 if Mario won the match, else lost; args[1] = opponent id.
 * Updates the opponent's lost flag and GSWF_TOU_LAST_MATCH_WON,
 * jitters every fighter's score by a random amount,
 * records the opponent in GSW_TOU_LAST_OPPONENT_ID and re-sorts the board.
 */
static USER_FUNC(evt_tou_set_ranking_win_lose) {
    EvtWord* args = event->args;
    s32 lose = evtGetValue(event, args[0]);
    s32 id = evtGetValue(event, args[1]);
    s32 i;
    s16 min;
    s16 max;

    if (lose == 0) {
        for (i = 0; i < rank_wp->count; i++) {
            if (id == rank_wp->entries[i].id) {
                rank_wp->entries[i].flags |= 1;
                break;
            }
        }
        swSet(GSWF_TOU_LAST_MATCH_WON);
    } else {
        for (i = 0; i < rank_wp->count; i++) {
            if (id == rank_wp->entries[i].id) {
                rank_wp->entries[i].flags &= ~1;
                break;
            }
        }
        swClear(GSWF_TOU_LAST_MATCH_WON);
    }
    min = 1000;
    max = -1000;
    for (i = 0; i < rank_wp->count; i++) {
        if (!(rank_wp->entries[i].flags & 2)) {
            rank_wp->entries[i].points.total += rand() % 4 + (rand() % 4 - 3);
            if (rank_wp->entries[i].points.total < min) {
                min = rank_wp->entries[i].points.total;
            }
            if (rank_wp->entries[i].points.total > max) {
                max = rank_wp->entries[i].points.total;
            }
        }
    }
    swByteSet(GSW_TOU_LAST_OPPONENT_ID, id);
    swSet(GSWF_TOU_LAST_OPPONENT_VALID);
    rankingControll();
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] = rule result bits from the match (bit 2 = rule met);
 * sets or clears GSWF_TOU_LAST_RULE_MET.
 */
static USER_FUNC(evt_tou_set_rule_result) {
    s32 result = evtGetValue(event, event->args[0]);

    if (result & 4) {
        swSet(GSWF_TOU_LAST_RULE_MET);
    } else if (result & 2) {
        swClear(GSWF_TOU_LAST_RULE_MET);
    } else if (result & 1) {
        swClear(GSWF_TOU_LAST_RULE_MET);
    }
    return EVT_RETURN_DONE;
}

/** Debug stub left from the original build: reads the story progress and loops over the entries; prints nothing. */
static void printRanking(void) {
    s32 i;

    evtGetValue(NULL, GSW(GSW_STORY_PROGRESS));
    for (i = 0; i < rank_wp->count; i++) {
    }
}

static FighterData fighterDt[] = {
    {4, "stg3_tou_sensyu_00", "stg3_tou_sensyu2_00", 22, "stg3_tou_400_02", "stg3_tou_400_03", 250},
    {4097, "stg3_tou_sensyu_01", "stg3_tou_sensyu2_01", 19, "stg3_tou_118_00", "stg3_tou_118_01", 200},
    {1, "stg3_tou_sensyu_02", "stg3_tou_sensyu2_02", 18, "stg3_tou_118_02", "stg3_tou_118_03", 180},
    {1, "stg3_tou_sensyu_03", "stg3_tou_sensyu2_03", 17, "stg3_tou_118_04", "stg3_tou_118_05", 170},
    {1, "stg3_tou_sensyu_04", "stg3_tou_sensyu2_04", 16, "stg3_tou_118_06", "stg3_tou_118_07", 160},
    {1, "stg3_tou_sensyu_05", "stg3_tou_sensyu2_05", 15, "stg3_tou_118_08", "stg3_tou_118_09", 150},
    {1, "stg3_tou_sensyu_06", "stg3_tou_sensyu2_06", 14, "stg3_tou_118_10", "stg3_tou_118_11", 140},
    {1, "stg3_tou_sensyu_07", "stg3_tou_sensyu2_07", 13, "stg3_tou_118_12", "stg3_tou_118_13", 130},
    {1, "stg3_tou_sensyu_08", "stg3_tou_sensyu2_08", 12, "stg3_tou_118_14", "stg3_tou_118_15", 120},
    {1, "stg3_tou_sensyu_09", "stg3_tou_sensyu2_09", 11, "stg3_tou_118_16", "stg3_tou_118_17", 110},
    {2049, "stg3_tou_sensyu_10", "stg3_tou_sensyu2_10", 10, "stg3_tou_118_18", "stg3_tou_118_19", 100},
    {258, "stg3_tou_sensyu_11", "stg3_tou_sensyu2_11", 9, "stg3_tou_118_20", "stg3_tou_118_21", 90},
    {2, "stg3_tou_sensyu_12", "stg3_tou_sensyu2_12", 8, "stg3_tou_118_22", "stg3_tou_118_23", 80},
    {2, "stg3_tou_sensyu_13", "stg3_tou_sensyu2_13", 7, "stg3_tou_118_24", "stg3_tou_118_25", 70},
    {2, "stg3_tou_sensyu_14", "stg3_tou_sensyu2_14", 6, "stg3_tou_118_26", "stg3_tou_118_27", 60},
    {2, "stg3_tou_sensyu_15", "stg3_tou_sensyu2_15", 5, "stg3_tou_118_28", "stg3_tou_118_29", 50},
    {2, "stg3_tou_sensyu_16", "stg3_tou_sensyu2_16", 4, "stg3_tou_118_30", "stg3_tou_118_31", 40},
    {2, "stg3_tou_sensyu_17", "stg3_tou_sensyu2_17", 3, "stg3_tou_118_32", "stg3_tou_118_33", 30},
    {514, "stg3_tou_sensyu_18", "stg3_tou_sensyu2_18", 2, "stg3_tou_118_34", "stg3_tou_118_35", 20},
    {1026, "stg3_tou_sensyu_19", "stg3_tou_sensyu2_19", 1, "stg3_tou_118_36", "stg3_tou_118_36_01", 10},
    {8, "stg3_tou_sensyu_20", "stg3_tou_sensyu2_20", 1, 0, 0, 0},
    {2, "stg3_tou_sensyu_21", "stg3_tou_sensyu2_21", 20, "stg3_tou_118_36_02", "stg3_tou_118_36_03", 5},
    {2, "stg3_tou_sensyu_22", "stg3_tou_sensyu2_22", 21, "stg3_tou_118_36_04", "stg3_tou_118_36_05", 0},
};

static FighterData fighterDt_re[] = {
    {4, "stg3_tou_re_315", "stg3_tou_re_338", 22, "stg3_tou_re_289", "stg3_tou_re_290", 250},
    {4097, "stg3_tou_re_316", "stg3_tou_re_339", 19, "stg3_tou_re_179", "stg3_tou_re_180", 200},
    {1, "stg3_tou_re_317", "stg3_tou_re_340", 18, "stg3_tou_re_181", "stg3_tou_re_182", 180},
    {1, "stg3_tou_re_318", "stg3_tou_re_341", 17, "stg3_tou_re_183", "stg3_tou_re_184", 170},
    {1, "stg3_tou_re_319", "stg3_tou_re_342", 16, "stg3_tou_re_185", "stg3_tou_re_186", 160},
    {1, "stg3_tou_re_320", "stg3_tou_re_343", 15, "stg3_tou_re_187", "stg3_tou_re_188", 150},
    {1, "stg3_tou_re_321", "stg3_tou_re_344", 14, "stg3_tou_re_189", "stg3_tou_re_190", 140},
    {1, "stg3_tou_re_322", "stg3_tou_re_345", 13, "stg3_tou_re_191", "stg3_tou_re_192", 130},
    {1, "stg3_tou_re_323", "stg3_tou_re_346", 12, "stg3_tou_re_193", "stg3_tou_re_194", 120},
    {1, "stg3_tou_re_324", "stg3_tou_re_347", 11, "stg3_tou_re_195", "stg3_tou_re_196", 110},
    {2049, "stg3_tou_re_325", "stg3_tou_re_348", 10, "stg3_tou_re_197", "stg3_tou_re_198", 100},
    {258, "stg3_tou_re_326", "stg3_tou_re_349", 9, "stg3_tou_re_199", "stg3_tou_re_200", 90},
    {2, "stg3_tou_re_327", "stg3_tou_re_350", 8, "stg3_tou_re_201", "stg3_tou_re_202", 80},
    {2, "stg3_tou_re_328", "stg3_tou_re_351", 7, "stg3_tou_re_203", "stg3_tou_re_204", 70},
    {2, "stg3_tou_re_329", "stg3_tou_re_352", 6, "stg3_tou_re_205", "stg3_tou_re_206", 60},
    {2, "stg3_tou_re_330", "stg3_tou_re_353", 5, "stg3_tou_re_207", "stg3_tou_re_208", 50},
    {2, "stg3_tou_re_331", "stg3_tou_re_354", 4, "stg3_tou_re_209", "stg3_tou_re_210", 40},
    {2, "stg3_tou_re_332", "stg3_tou_re_355", 3, "stg3_tou_re_211", "stg3_tou_re_212", 30},
    {514, "stg3_tou_re_333", "stg3_tou_re_356", 2, "stg3_tou_re_213", "stg3_tou_re_214", 20},
    {1026, "stg3_tou_re_334", "stg3_tou_re_357", 1, "stg3_tou_re_215", "stg3_tou_re_216", 10},
    {8, "stg3_tou_re_335", "stg3_tou_re_358", 1, 0, 0, 0},
};

static RuleData ruleDt_2bu[] = {
    {"stg3_tou_107_01", "stg3_tou_cp_000", 18, 3, 3},
    {"stg3_tou_107_02", "stg3_tou_cp_001", 1, 1, 1},
    {"stg3_tou_107_03", "stg3_tou_cp_002", 3, 1, 1},
    {"stg3_tou_107_04", "stg3_tou_cp_003", 48, 1, 1},
    {"stg3_tou_107_05", "stg3_tou_cp_004", 5, 1, 1},
    {"stg3_tou_107_06", "stg3_tou_cp_005", 26, 1, 1},
    {"stg3_tou_107_07", "stg3_tou_cp_006", 32, 1, 1},
    {"stg3_tou_107_08", "stg3_tou_cp_007", 59, 5, 5},
    {"stg3_tou_107_12", "stg3_tou_cp_008", 6, 1, 1},
    {"stg3_tou_107_16", "stg3_tou_cp_009", 43, 1, 1},
};

static RuleData ruleDt_1bu[] = {
    {"stg3_tou_107_01", "stg3_tou_cp_010", 18, 5, 5},
    {"stg3_tou_107_02", "stg3_tou_cp_011", 1, 1, 1},
    {"stg3_tou_107_03", "stg3_tou_cp_012", 3, 1, 1},
    {"stg3_tou_107_04", "stg3_tou_cp_013", 48, 1, 1},
    {"stg3_tou_107_05", "stg3_tou_cp_014", 5, 1, 1},
    {"stg3_tou_107_06", "stg3_tou_cp_015", 26, 1, 1},
    {"stg3_tou_107_07", "stg3_tou_cp_016", 32, 1, 1},
    {"stg3_tou_107_08", "stg3_tou_cp_017", 59, 5, 5},
    {"stg3_tou_107_12", "stg3_tou_cp_019", 6, 1, 1},
    {"stg3_tou_107_13", "stg3_tou_cp_020", 11, 20, 20},
    {"stg3_tou_107_16", "stg3_tou_cp_021", 43, 3, 3},
    {"stg3_tou_107_17", "stg3_tou_cp_022", 65, 3, 3},
    {"stg3_tou_107_19", "stg3_tou_cp_023", 64, 255, 255},
    {"stg3_tou_107_20", "stg3_tou_cp_024", 63, 255, 255},
};

static RuleData ruleDt_re[] = {
    {"stg3_tou_re_362", "stg3_tou_cp_040", 18, 5, 5},
    {"stg3_tou_re_363", "stg3_tou_cp_041", 1, 1, 1},
    {"stg3_tou_re_364", "stg3_tou_cp_042", 3, 1, 1},
    {"stg3_tou_re_365", "stg3_tou_cp_043", 48, 1, 1},
    {"stg3_tou_re_366", "stg3_tou_cp_044", 5, 1, 1},
    {"stg3_tou_re_367", "stg3_tou_cp_045", 26, 1, 1},
    {"stg3_tou_re_368", "stg3_tou_cp_046", 32, 1, 1},
    {"stg3_tou_re_369", "stg3_tou_cp_047", 59, 5, 5},
    {"stg3_tou_re_371", "stg3_tou_cp_049", 6, 1, 1},
    {"stg3_tou_re_372", "stg3_tou_cp_050", 11, 20, 20},
    {"stg3_tou_re_373", "stg3_tou_cp_051", 43, 3, 3},
    {"stg3_tou_re_374", "stg3_tou_cp_052", 65, 3, 3},
    {"stg3_tou_re_375", "stg3_tou_cp_053", 64, 255, 255},
    {"stg3_tou_re_376", "stg3_tou_cp_054", 63, 255, 255},
};

static RankData* rank_wp = &rank_work;

static RankDispWork* dwp = &disp_work;

static const char* suuji[] = {
    "０", "１", "２", "３", "４", "５", "６", "７",
    "８", "９",
};

/**
 * Draws the ranking window: a "Ranking" title and the scrolling two-page list of fighter names with rank numbers
 * (the champion's seat in red), clipped by a scissor box.
 * Runs as a display entry queued by evt_tou_print_ranking.
 */
static void disp_proc(CameraId cameraId, void* param) {
#if VERSION >= VERSION_US
    const char* title;
#endif
    FighterData* dt;
    f32 x;
    f32 tx;
    f32 y;
    u16 sx;
    u16 sw;
    s32 i;
    s32 rank;
#if VERSION >= VERSION_US
    const char* name;
#endif
    s32 yoff;
    s32 w;
    f32 winW;
    f32 top;
    Mtx scale;
    Mtx mtx;
    char buf[0x100];

    if (evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT) {
        dt = fighterDt;
    } else {
        dt = fighterDt_re;
    }
    winW = 250.0f;
    x = 0.5f;
    x = -winW * x;
    windowDispGX_System(0, 0xFF, x - 30.0f, 165.0f, 310.0f, 330.0f);
#if VERSION >= VERSION_US
    if ((u32)gp->language == 0) {
        title = "ランキング";
    } else {
        title = msgSearch("stg3_ranking");
    }
    FontDrawStart();
    FontDrawScale(1.0f);
    w = FontGetMessageWidth(title);
#else
    FontDrawStart();
    FontDrawScale(1.0f);
    w = (u16)FontGetMessageWidth("ランキング");
#endif
    {
        GXColor color = {0xDC, 0xC8, 0xDC, 0xFF};
        FontDrawColor(color);
    }
    top = 135.0f;
#if VERSION >= VERSION_US
    FontDrawMessage(-w / 2, top, title);
#else
    FontDrawMessage(-w / 2, top, "ランキング");
#endif
    sx = 304.0f + x;
    sw = winW;
    {
        f32 sy = 145.0f;
        f32 sh = 220.0f;
        GXSetScissor(sx, (u16)sy, sw, (u16)sh);
    }
    rank = 0;
    yoff = 0;
    for (i = 0; i < rank_wp->count; i++) {
        tx = 10.0f + x;
        y = dwp->scroll + (top - yoff - 40.0f);
        if (!(rank_wp->entries[i].flags & 2)) {
            PSMTXScale(scale, 0.8f, 0.8f, 0.8f);
            if (rank != 0) {
#if VERSION >= VERSION_US
                if ((u32)gp->language == 0) {
                    sprintf(buf, "%s%s", rank / 10 ? suuji[rank / 10] : "", suuji[rank % 10]);
                } else {
                    sprintf(buf, "%2d", rank);
                }
#else
                sprintf(buf, "%s%s", rank / 10 ? suuji[rank / 10] : "", suuji[rank % 10]);
#endif
                FontDrawStart();
                {
                    GXColor color = {0xDC, 0xC8, 0xDC, 0xFF};
                    FontDrawColor(color);
                }
                PSMTXTrans(mtx, tx, y, 0.0f);
                PSMTXConcat(mtx, scale, mtx);
                FontDrawMessageMtx(mtx, buf);
            }
            FontDrawStart();
            if (rank_wp->entries[i].flags & 4) {
                GXColor color = {0xFF, 0x00, 0x00, 0xFF};
                FontDrawColor(color);
            } else {
                GXColor color = {0xDC, 0xC8, 0xDC, 0xFF};
                FontDrawColor(color);
            }
#if VERSION >= VERSION_US
            {
                f32 nw;
                name = msgSearch(dt[rank_wp->entries[i].id].name);
                nw = FontGetMessageWidth(name);

                tx = 40.0f + tx;
                PSMTXTrans(mtx, tx, y, 0.0f);
                PSMTXConcat(mtx, scale, mtx);
                if (nw > 220.0f) {
                    PSMTXScale(scale, 220.0f / nw, 1.0f, 1.0f);
                    PSMTXConcat(mtx, scale, mtx);
                }
                FontDrawMessageMtx(mtx, name);
            }
#else
            tx = 40.0f + tx;
            PSMTXTrans(mtx, tx, y, 0.0f);
            PSMTXConcat(mtx, scale, mtx);
            FontDrawMessageMtx(mtx, msgSearch(dt[rank_wp->entries[i].id].name));
#endif
            rank++;
            yoff += 20;
        }
    }
    {
        f32 sy = 137.0f;
        f32 sh = 228.0f;
        GXSetScissor(sx, (u16)sy, sw, (u16)sh);
    }
    {
        f32 yy = 95.0f + dwp->scroll;
        Vec pos = {0.0f, 0.0f, 0.0f};
        pos.x = 15.0f + x;
        pos.y = yy - 24.0f;
        iconDispGx(&pos, ICON_FLAG_2D, ICON_123, 0.8f);
    }
    GXSetScissor(0, 0, 0x260, 0x1E0);
    if (dwp->page > 0) {
        {
            Vec pos = {0.0f, 125.0f, 0.0f};
            pos.x = x + winW;
            iconDispGx(&pos, ICON_FLAG_2D, ICON_205, -1.0f);
        }
        {
            Vec pos = {0.0f, 75.0f, 0.0f};
            pos.x = x + winW;
            iconDispGx(&pos, ICON_FLAG_2D, ICON_07E, 0.6f);
        }
    }
    if (dwp->page < 1) {
        {
            Vec pos = {0.0f, -140.0f, 0.0f};
            pos.x = x + winW;
            iconDispGx(&pos, ICON_FLAG_2D, ICON_205, 1.0f);
        }
        {
            Vec pos = {0.0f, -125.0f, 0.0f};
            pos.x = x + winW;
            iconDispGx(&pos, ICON_FLAG_2D, ICON_080, 0.6f);
        }
    }
}

const char* lockerDt[] = {
    "R_door_1",
    "a_door_1",
    "a_door_1_omote",
    "a_door_1_ura",
    "a_R_1_asi",
    "R_door_2",
    "a_door_2",
    "a_door_2_omote",
    "a_door_2_ura",
    "a_R_2_asi",
    "R_door_3",
    "a_door_3",
    "a_door_3_omote",
    "a_door_3_ura",
    "a_R_3_asi",
    "R_door_5",
    "a_door_5",
    "a_door_5_omote",
    "a_door_5_ura",
    "a_R_5_asi",
    "R_door_6",
    "a_door_6",
    "a_door_6_omote",
    "a_door_6_ura",
    "a_R_6_asi",
    "R_door_7",
    "a_door_7",
    "a_door_7_omote",
    "a_door_7_ura",
    "a_R_7_asi",
    "R_door_8",
    "a_door_8",
    "a_door_8_omote",
    "a_door_8_ura",
    "a_R_8_asi",
    "R_door_9",
    "a_door_9",
    "a_door_9_omote",
    "a_door_9_ura",
    "a_R_9_asi",
    "R_door_10",
    "a_door_10",
    "a_door_10_omote",
    "a_door_10_ura",
    "a_R_10_asi",
    NULL,
};

/**
 * Locker door close script.
 * Triggered by pushing at or standing on an open locker;
 * plays the close sound, swings the door shut over 40 or 20 frames,
 * then re-registers evt_open so the door can be opened again.
 */
EVT_BEGIN(evt_close)
    SET_VALUE(LF(0), 0)
    IF_INT_EQUAL(LW(10), 0)
        CALL(evt_del_case_evt, 0, LW(12))
        SET_VALUE(LW(5), LW(0))
        SET_VALUE(LW(6), LW(1))
        SET_VALUE(LW(7), LW(2))
        SET_VALUE(LW(8), LW(3))
        SET_VALUE(LW(9), LW(4))
        CALL(evt_mapobj_get_position, LW(5), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_LOCKER_CLOSE1"), LW(10), LW(11), LW(12), 0)
        CALL(evt_sub_intpl_init, 12, 120, 0, 40)
        LOOP(41)
            CALL(evt_sub_intpl_get_value)
            IF_INT_EQUAL(LF(0), 1)
                MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
            END_IF
            CALL(evt_mapobj_rotate, 1, LW(5), 0, LW(0), 0)
            CALL(evt_hit_bind_update, LW(6))
            WAIT_FRAMES(1)
        END_LOOP
        SET_VALUE(LW(0), LW(5))
        SET_VALUE(LW(1), LW(6))
        SET_VALUE(LW(2), LW(7))
        SET_VALUE(LW(3), LW(8))
        SET_VALUE(LW(4), LW(9))
        CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(2), 0, PTR(evt_open), 0)
    ELSE
#if VERSION >= VERSION_JP
        CALL(evt_mario_key_onoff, 0)
#endif
        CALL(evt_del_case_evt, 0, LW(11))
        SET_VALUE(LW(5), LW(0))
        SET_VALUE(LW(6), LW(1))
        SET_VALUE(LW(7), LW(2))
        SET_VALUE(LW(8), LW(3))
        SET_VALUE(LW(9), LW(4))
        CALL(evt_mapobj_get_position, LW(5), LW(10), LW(11), LW(12))
        CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_LOCKER_CLOSE1"), LW(10), LW(11), LW(12), 0)
        CALL(evt_sub_intpl_init, 12, 120, 0, 20)
        LOOP(21)
            CALL(evt_sub_intpl_get_value)
            IF_INT_EQUAL(LF(0), 1)
                MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
            END_IF
            CALL(evt_mapobj_rotate, 1, LW(5), 0, LW(0), 0)
            CALL(evt_hit_bind_update, LW(6))
            WAIT_FRAMES(1)
        END_LOOP
#if VERSION >= VERSION_JP
        CALL(evt_mario_key_onoff, 1)
#endif
        SET_VALUE(LW(0), LW(5))
        SET_VALUE(LW(1), LW(6))
        SET_VALUE(LW(2), LW(7))
        SET_VALUE(LW(3), LW(8))
        SET_VALUE(LW(4), LW(9))
        CALL(evt_run_case_evt, CASE_COND_PUSH, 1, LW(3), 0, PTR(evt_open), 0)
    END_IF
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

/**
 * Locker door open script, run when Mario pushes on a locker (registered by the locker setup script;
 * evt_close is its counterpart).
 * Before STORY_STG3_05_MATCH in tou_10, with no match reserved yet,
 * the locker stays shut and a staff member says stg3_tou_67 (the US and later versions skip the line if Mario's
 * input is already locked).
 * Otherwise it plays the locker-open sound at the door,
 * swings the door open 120 degrees over 40 frames (mirrored when LF(0) is 1),
 * and registers evt_close for pushing at or standing on it.
 */
static EVT_BEGIN(evt_open)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_05_MATCH)
        CALL(evt_sub_get_mapname, LW(5))
        IF_STR_EQUAL(LW(5), STRING("tou_10"))
            IF_INT_EQUAL(GSWF(GSWF_TOU_MATCH_RESERVED), 0)
#if VERSION >= VERSION_US
                CALL(tou_mario_keyoff_check, LW(0))
                IF_INT_EQUAL(LW(0), 1)
                    RETURN
                END_IF
#endif
                CALL(evt_mario_key_onoff, 0)
                CALL(evt_msg_print, 0, STRING("stg3_tou_67"), 0, STRING("キノシコワ"))
                CALL(evt_mario_key_onoff, 1)
                RETURN
            END_IF
        END_IF
    END_IF
    SET_VALUE(LF(0), 0)
    SET_VALUE(LW(5), LW(0))
    SET_VALUE(LW(6), LW(1))
    SET_VALUE(LW(7), LW(2))
    SET_VALUE(LW(8), LW(3))
    SET_VALUE(LW(9), LW(4))
    CALL(evt_mapobj_get_position, LW(5), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_LOCKER_OPEN1"), LW(10), LW(11), LW(12), 0)
    CALL(evt_sub_intpl_init, 12, 0, 120, 40)
    LOOP(41)
        CALL(evt_sub_intpl_get_value)
        IF_INT_EQUAL(LF(0), 1)
            MULTIPLY_FLOAT(LW(0), FLOAT(-1.0f))
        END_IF
        CALL(evt_mapobj_rotate, 1, LW(5), 0, LW(0), 0)
        CALL(evt_hit_bind_update, LW(6))
        WAIT_FRAMES(1)
    END_LOOP
    SET_VALUE(LW(0), LW(5))
    SET_VALUE(LW(1), LW(6))
    SET_VALUE(LW(2), LW(7))
    SET_VALUE(LW(3), LW(8))
    SET_VALUE(LW(4), LW(9))
    SET_VALUE(LW(10), 0)
    CALL(evt_run_case_evt, CASE_COND_PUSH, 1, LW(2), 0, PTR(evt_close), LW(11))
    SET_VALUE(LW(0), LW(5))
    SET_VALUE(LW(1), LW(6))
    SET_VALUE(LW(2), LW(7))
    SET_VALUE(LW(3), LW(8))
    SET_VALUE(LW(4), LW(9))
    SET_VALUE(LW(10), 1)
    CALL(evt_run_case_evt, CASE_COND_STAND_ON, 1, LW(4), 0, PTR(evt_close), LW(12))
    CALL(evt_set_case_wrk, LW(11), 11, LW(11))
    CALL(evt_set_case_wrk, LW(11), 12, LW(12))
    CALL(evt_set_case_wrk, LW(12), 11, LW(11))
    CALL(evt_set_case_wrk, LW(12), 12, LW(12))
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

/**
 * Map-init helper: binds every locker in lockerDt to its collision and an evt_open case script,
 * except the doors that are scenery on the current map (a few door objects in tou_10, tou_09 and tou_08).
 */
EVT_BEGIN(evt_tou_locker_init)
    SET_INT_READ_ADDR(PTR(&lockerDt))
    LOOP(0)
        READ_INT3(LW(0), LW(1), LW(2))
        READ_INT2(LW(3), LW(4))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        SET_VALUE(LF(0), 0)
        CALL(evt_sub_get_mapname, LW(10))
        IF_STR_EQUAL(LW(10), STRING("tou_10"))
            IF_STR_EQUAL(LW(2), STRING("a_door_1_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_STR_EQUAL(LW(2), STRING("a_door_7_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_STR_EQUAL(LW(2), STRING("a_door_8_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_STR_EQUAL(LW(2), STRING("a_door_9_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_STR_EQUAL(LW(2), STRING("a_door_10_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
        IF_STR_EQUAL(LW(10), STRING("tou_09"))
            IF_STR_EQUAL(LW(2), STRING("a_door_9_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
        IF_STR_EQUAL(LW(10), STRING("tou_08"))
            IF_STR_EQUAL(LW(2), STRING("a_door_9_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
            IF_STR_EQUAL(LW(2), STRING("a_door_10_omote"))
                SET_VALUE(LF(0), 1)
            END_IF
        END_IF
        IF_INT_EQUAL(LF(0), 0)
            CALL(evt_hit_bind_mapobj, LW(1), LW(0))
            CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, LW(2), 0, PTR(evt_open), 0)
        END_IF
    END_LOOP
    RETURN
EVT_END()

/** Script helper: shows the ranking window (disp_proc) and blocks while it is open; L/R switch pages, B closes it. */
static USER_FUNC(evt_tou_print_ranking) {
    s32 rank;
    s32 i;

    if (isFirstCall) {
        memset(dwp, 0, sizeof(RankDispWork));
        GET_RANK(rank, i);
        dwp->page = rank / 11;
        dwp->scroll = dwp->target = dwp->page * 220;
        printRanking();
        return EVT_RETURN_BLOCK;
    }
    if (keyGetButtonTrg(0) & PAD_BUTTON_B) {
        psndSFXOn((const char*)0x13);
        return EVT_RETURN_YIELD;
    }
    if (dwp->page > 0 && (keyGetButtonTrg(0) & PAD_TRIGGER_L)) {
        psndSFXOn((const char*)5);
        dwp->page--;
    }
    if (dwp->page < 1 && (keyGetButtonTrg(0) & PAD_TRIGGER_R)) {
        dwp->page++;
        psndSFXOn((const char*)5);
    }
    dwp->target = dwp->page * 220;
    dwp->scroll += (dwp->target - dwp->scroll) / 8.0f;
    dispEntry(CAMERA_2D, 300.0f, 0, disp_proc, NULL);
    return EVT_RETURN_BLOCK;
}

#if VERSION >= VERSION_US
/** Script helper: args[0] receives 1 if Mario's key input or control is currently disabled, else 0. */
USER_FUNC(tou_mario_keyoff_check) {
    EvtWord* args = event->args;

    if (marioKeyOffChk() || marioCtrlOffChk()) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
#endif

/**
 * Display callback for the in-world monitor: renders Grubba (ガンス),
 * or Jolene (キノシコワ) after Chapter 3's story point, into a 128x128 texture with its own camera,
 * so the screen mesh can show him.
 */
static void gans_tex(CameraId cameraId, void* param) {
    GansWork* wp = param;
    CameraEntry saved;
    Mtx44 projMtx;
    Mtx lookAt;
    Mtx ident;
    f32 viewport[6];
    f32 proj[7];
    u32 sx, sy, sw, sh;
    NpcEntry* npc;

    GXGetViewportv(viewport);
    GXGetProjectionv(proj);
    GXGetScissor(&sx, &sy, &sw, &sh);
    GXSetViewport(0.0f, 0.0f, 128.0f, 128.0f, 0.0f, 1.0f);
    GXSetScissor(1, 1, 126, 126);
    C_MTXPerspective(projMtx, 25.0f, 1.0f, 1.0f, 1000.0f);
    GXSetProjection(projMtx, GX_PERSPECTIVE);
    {
        static const Vec gans_pos = {0.0f, 20.0f, 130.0f};
        static const Vec gans_up = {0.0f, 1.0f, 0.0f};
        static const Vec gans_target = {0.0f, 20.0f, 0.0f};
        Vec pos;
        Vec up;
        Vec target;

        target = gans_target;
        up = gans_up;
        pos = gans_pos;

        C_MTXLookAt(lookAt, &pos, &up, &target);
    }
    saved = *camGetPtr(cameraId);
    npc = npcNameToPtr(evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT ? "ガンス" : "キノシコワ");
    PSMTXCopy(lookAt, camGetCurPtr()->view);
    animPosePeraOff(npc->poseId);
    PSMTXIdentity(ident);
    animPoseMain(npc->poseId);
    animPoseDrawMtx(npc->poseId, ident, 1, 0.0f, 2.0f);
    animPoseDrawMtx(npc->poseId, ident, 2, 0.0f, 2.0f);
    animPoseDrawMtx(npc->poseId, ident, 3, 0.0f, 2.0f);
    animPosePeraOn(npc->poseId);
    PSMTXCopy(saved.view, camGetCurPtr()->view);
    GXSetTexCopySrc(0, 0, 0x80, 0x80);
    GXSetTexCopyDst(0x80, 0x80, GX_TF_RGB5A3, GX_FALSE);
    GXCopyTex(wp->buf->address, GX_TRUE);
    GXPixModeSync();
    GXSetViewport(viewport[0], viewport[1], viewport[2], viewport[3], viewport[4], viewport[5]);
    GXSetProjectionv(proj);
    GXSetScissor(sx, sy, sw, sh);
    wp->ready = 1;
}

/** Returns a white color with the given alpha (used for the monitor's fade). */
static inline GXColor tou_mkcolor(u8 a) {
    GXColor c = {0xFF, 0xFF, 0xFF, 0x00};
    c.a = a;
    return c;
}

/** Turns the registration monitor on, with the computer sound at the "M_make" console. */
EVT_BEGIN(evt_tou_monitor_on)
    CALL(evt_hit_get_position, STRING("M_make"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_TOUROKU_COM2"), LW(0), LW(1), LW(2), 0)
    CALL(onoff, 1)
    RETURN
EVT_END()

/** Turns the registration monitor off, with the computer sound at the "M_make" console. */
EVT_BEGIN(evt_tou_monitor_off)
    CALL(evt_hit_get_position, STRING("M_make"), LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_TOUROKU_COM2"), LW(0), LW(1), LW(2), 0)
    CALL(onoff, 0)
    RETURN
EVT_END()

/**
 * Map-init helper for tou_10, tou_08 and tou_07:
 * starts the monitor renderer and hooks the screen mesh onto monitor_tev so it shows the live texture.
 */
EVT_BEGIN(evt_tou_monitor_init)
    BEGIN_INLINE_EVENT
        CALL(make_monitor)
    END_INLINE_EVENT
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("tou_10"))
        CALL(evt_map_set_tevcallback, 1, PTR(monitor_tev))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("gamen"), MAPOBJ_TEV_CALLBACK(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("gamen"), MAPOBJ_FLAG_DISPLAY_LIST)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_08"))
        CALL(evt_map_set_tevcallback, 1, PTR(monitor_tev))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("gamenn"), MAPOBJ_TEV_CALLBACK(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("gamenn"), MAPOBJ_FLAG_DISPLAY_LIST)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_07"))
        CALL(evt_map_set_tevcallback, 1, PTR(monitor_tev))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 1, STRING("gamenn"), MAPOBJ_TEV_CALLBACK(1))
        CALL(evt_mapobj_flag_onoff, MAPOBJ_GROUP, 0, STRING("gamenn"), MAPOBJ_FLAG_DISPLAY_LIST)
    END_IF
    RETURN
EVT_END()

/**
 * Guess: the guard's remark during the poison cake event;
 * only plays when the guard is more than 100 units away in z.
 */
EVT_BEGIN(talk_gardman_doku)
    CALL(evt_npc_get_position, STRING("ガードマン"), LW(0), LW(1), LW(2))
    IF_INT_GREATER(LW(2), 100)
        CALL(evt_msg_print, 0, STRING("stg3_tou_304"), 0, STRING("ガードマン"))
    END_IF
    RETURN
EVT_END()

/** Talk script of Goombella's stand-in NPC: her line, then the guard's remark. */
EVT_BEGIN(dummy_party_msg_pkr)
    CALL(evt_msg_print, 0, STRING("stg3_tou_303_kur"), 0, STRING("me"))
    CALL_CHILD(talk_gardman_doku)
    RETURN
EVT_END()

/** Talk script of Koops' stand-in NPC: his line, then the guard's remark. */
EVT_BEGIN(dummy_party_msg_pnk)
    CALL(evt_msg_print, 0, STRING("stg3_tou_303_nok"), 0, STRING("me"))
    CALL_CHILD(talk_gardman_doku)
    RETURN
EVT_END()

/** Talk script of Yoshi's stand-in NPC: his line, then the guard's remark. */
EVT_BEGIN(dummy_party_msg_yos)
    CALL(evt_msg_print, 0, STRING("stg3_tou_303_yos"), 0, STRING("me"))
    CALL_CHILD(talk_gardman_doku)
    RETURN
EVT_END()

/** Talk script of Flurrie's stand-in NPC (Windy in the data names): her line, then the guard's remark. */
EVT_BEGIN(dummy_party_msg_win)
    CALL(evt_msg_print, 0, STRING("stg3_tou_303_win"), 0, STRING("me"))
    CALL_CHILD(talk_gardman_doku)
    RETURN
EVT_END()

/**
 * Swaps the partner for a stand-in NPC ("dummy_party") at the partner's position,
 * matching the current partner (Goombella, Koops, Yoshi in its color, Flurrie),
 * and parks the real partner offscreen.
 */
EVT_BEGIN(party_npc_replace)
    CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_mario_get_party, LW(3))
    SWITCH(LW(3))
        CASE_EQUAL(PARTY_MEMBER_GOOMBELLA)
        CALL(evt_npc_entry, STRING("dummy_party"), STRING("c_pkr"))
        CALL(evt_npc_set_anim, STRING("dummy_party"), STRING("PKR_D_3"))
        CALL(evt_npc_change_interrupt, STRING("dummy_party"), 6, PTR(dummy_party_msg_pkr))
        CASE_EQUAL(PARTY_MEMBER_KOOPS)
        CALL(evt_npc_entry, STRING("dummy_party"), STRING("c_pnk"))
        CALL(evt_npc_set_anim, STRING("dummy_party"), STRING("PNK_D_3"))
        CALL(evt_npc_change_interrupt, STRING("dummy_party"), 6, PTR(dummy_party_msg_pnk))
        CASE_EQUAL(PARTY_MEMBER_YOSHI)
        CALL(getYoshiColor, LW(5))
        SWITCH(LW(5))
            CASE_EQUAL(0)
            SET_VALUE(LW(5), STRING("c_babyyoshi"))
            CASE_EQUAL(1)
            SET_VALUE(LW(5), STRING("c_babyyoshi2"))
            CASE_EQUAL(2)
            SET_VALUE(LW(5), STRING("c_babyyoshi3"))
            CASE_EQUAL(3)
            SET_VALUE(LW(5), STRING("c_babyyoshi4"))
            CASE_EQUAL(4)
            SET_VALUE(LW(5), STRING("c_babyyoshi5"))
            CASE_EQUAL(5)
            SET_VALUE(LW(5), STRING("c_babyyoshi6"))
            CASE_EQUAL(6)
            SET_VALUE(LW(5), STRING("c_babyyoshi7"))
        END_SWITCH
        CALL(evt_npc_entry, STRING("dummy_party"), LW(5))
        CALL(evt_npc_set_anim, STRING("dummy_party"), STRING("PYS_D_3"))
        CALL(evt_npc_change_interrupt, STRING("dummy_party"), 6, PTR(dummy_party_msg_yos))
        CASE_EQUAL(5)
        CALL(evt_npc_entry, STRING("dummy_party"), STRING("c_windy"))
        CALL(evt_npc_set_anim, STRING("dummy_party"), STRING("PWD_D_3"))
        CALL(evt_npc_change_interrupt, STRING("dummy_party"), 6, PTR(dummy_party_msg_win))
    END_SWITCH
    CALL(evt_npc_flag_onoff, 1, STRING("dummy_party"), NPC_FLAG_NO_TURN_TO_MARIO)
    CALL(evt_npc_set_position, STRING("dummy_party"), LW(0), LW(1), LW(2))
    CALL(evt_party_set_pos, 0, 0, -1000, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_party_cont_onoff, 0, 0)
    RETURN
EVT_END()

/**
 * Squash-and-stretch of the egg NPC ("たまご") over a hop of LW(3) milliseconds:
 * the width scale eases from 1.2 down to 0.9 and the height scale from 0.9 up to 1.1 (two inline events),
 * while the loop applies both scales to the egg every frame.
 */
static EVT_BEGIN(evt_tamago_scale)
    SET_VALUE(GW(10), FLOAT(1.1992188f))
    SET_VALUE(GW(11), FLOAT(0.89941406f))
    BEGIN_INLINE_EVENT
        DIVIDE(LW(3), 2)
        ADD(LW(3), 1)
        CALL(evt_sub_intpl_msec_init, 11, 120, 90, LW(3))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(10), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        DIVIDE(LW(3), 2)
        ADD(LW(3), 1)
        CALL(evt_sub_intpl_msec_init, 11, 90, 110, LW(3))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(11), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    CONVERT_FRAME_TO_MS(LW(3), LW(4))
    ADD(LW(4), 1)
    LOOP(LW(4))
        CALL(evt_npc_set_scale, STRING("たまご"), GW(10), GW(11), FLOAT(1.0f))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Second squash-and-stretch step for the egg NPC ("たまご"), over LW(3) milliseconds:
 * the width eases from 0.9 back to 1.0 and the height from 1.1 back to 1.0,
 * and the loop applies the scales every frame (the settle after the hops of evt_tamago_scale).
 */
static EVT_BEGIN(evt_tamago_scale2)
    BEGIN_INLINE_EVENT
        DIVIDE(LW(3), 2)
        ADD(LW(3), 1)
        CALL(evt_sub_intpl_msec_init, 4, 90, 100, LW(3))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(10), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        DIVIDE(LW(3), 2)
        ADD(LW(3), 1)
        CALL(evt_sub_intpl_msec_init, 4, 110, 100, LW(3))
        LABEL(0)
        CALL(evt_sub_intpl_msec_get_value)
        DIVIDE_FLOAT(LW(0), FLOAT(100.0f))
        SET_FLOAT_VALUE(GW(11), LW(0))
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 1)
            GOTO(0)
        END_IF
    END_INLINE_EVENT
    CONVERT_FRAME_TO_MS(LW(3), LW(4))
    ADD(LW(4), 1)
    LOOP(LW(4))
        CALL(evt_npc_set_scale, STRING("たまご"), GW(10), GW(11), FLOAT(1.0f))
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/**
 * Mini-Yoshi egg scene (story stage 12 to 19): the egg Yoshi NPC takes the partner's place,
 * Yoshi leaves the party, and the egg hops away in squashing jumps.
 */
EVT_BEGIN(evt_tamago_byebye)
    CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_npc_check, STRING("たまご"), LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(evt_npc_entry, STRING("たまご"), STRING("c_babyyoshi"))
    END_IF
    CALL(evt_npc_set_tribe, STRING("たまご"), STRING("たまご"))
    CALL(evt_npc_set_anim, STRING("たまご"), STRING("PYS_E_2"))
    CALL(evt_npc_set_position, STRING("たまご"), LW(0), LW(1), LW(2))
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    CALL(evt_mario_kill_party, 1)
    CALL(evt_mario_set_dir_npc, STRING("たまご"))
    CALL(evt_party_set_dir_npc, 0, STRING("たまご"))
    BEGIN_INLINE_EVENT
        LOOP(3)
            CALL(evt_npc_get_position, STRING("たまご"), LW(0), LW(1), LW(2))
            CALL(evt_sub_random, 200, LW(3))
            ADD(LW(3), 200)
            CALL(evt_sub_random, 20, LW(4))
            ADD(LW(4), 20)
            SPAWN_EVENT(evt_tamago_scale)
            CALL(evt_npc_jump_position_nohit, STRING("たまご"), LW(0), LW(1), LW(2), LW(3), LW(4))
        END_LOOP
        IF_INT_GREATER(LW(0), 0)
            SET_VALUE(LW(3), 400)
            SPAWN_EVENT(evt_tamago_scale)
            CALL(evt_npc_jump_position_nohit, STRING("たまご"), 45, 20, 8, 400, 50)
            SET_VALUE(LW(3), 400)
            SPAWN_EVENT(evt_tamago_scale)
            CALL(evt_npc_jump_position_nohit, STRING("たまご"), 10, 20, 15, 400, 50)
            SET_VALUE(LW(3), 400)
            SPAWN_EVENT(evt_tamago_scale)
            CALL(evt_npc_jump_position_nohit, STRING("たまご"), -30, 20, 30, 400, 50)
        ELSE
            SET_VALUE(LW(3), 400)
            SPAWN_EVENT(evt_tamago_scale)
            CALL(evt_npc_jump_position_nohit, STRING("たまご"), -80, 20, 15, 400, 50)
            SET_VALUE(LW(3), 400)
            SPAWN_EVENT(evt_tamago_scale)
            CALL(evt_npc_jump_position_nohit, STRING("たまご"), -30, 20, 30, 400, 50)
        END_IF
        SET_VALUE(LW(3), 400)
        SPAWN_EVENT(evt_tamago_scale2)
    END_INLINE_EVENT
    RETURN
EVT_END()

/**
 * Guard's talk script: after the poison remark or the egg scene,
 * he steps out and swings the door of the current map (tou_10, tou_08 or tou_07) open and closed for Mario.
 */
EVT_BEGIN(talk_gardman)
    IF_INT_EQUAL(GSWF(GSWF_TOU_PARTNER_POISON_CURED), 0)
        IF_INT_EQUAL(GSWF(GSWF_TOU_PARTNER_POISONED), 1)
            CALL(evt_msg_print, 0, STRING("stg3_tou_304_01"), 0, STRING("ガードマン"))
        END_IF
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_12_MINI_YOSHI_EGG)
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_MAJORS_10TH)
            CALL(chk, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL_CHILD(evt_tamago_byebye)
            END_IF
        END_IF
    END_IF
    SET_VALUE(LF(0), 0)
    SET_VALUE(LF(1), 0)
    SET_VALUE(LF(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("tou_10"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_08"))
        SET_VALUE(LF(1), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_07"))
        SET_VALUE(LF(2), 1)
    END_IF
    CALL(evt_npc_flag_onoff, 1, STRING("ガードマン"), NPC_FLAG_INTANGIBLE)
    WAIT_FRAMES(1)
    CALL(evt_npc_move_position, STRING("ガードマン"), 0, -130, 0, FLOAT(80.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(1), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ガードマン"), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, STRING("ガードマン"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 0, -200, 60)
    END_INLINE_EVENT
    WAIT_MS(500)
    IF_INT_EQUAL(LF(1), 1)
        SET_VALUE(GSWF(GSWF_TOU08_GUARD_LET_THROUGH), 1)
    END_IF
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
        IF_INT_EQUAL(GSWF(GSWF_TOU_TITLE_MATCH_RESERVED), 1)
            CALL(evt_bero_mapchange, STRING("tou_04"), 0)
            RETURN
        END_IF
    END_IF
    CALL(evt_bero_mapchange, STRING("tou_03"), 0)
    RETURN
EVT_END()

/**
 * Guess: the guard escort scene.
 * The guard (ガードマン) is the NPC of the map; LF(0),
 * LF(1) and LF(2) tell which map it is (tou_10, tou_08 or tou_07)
 * and select the door message (stg3_tou_74, 327 or 453).
 * It waits for Mario to be free; if Mario stands near the door (x within 35, z at or below -60) he is bounced
 * back to (40, 0, -120), and the guard opens the door_1 map object (with the door sounds), steps out,
 * closes it and speaks. It then gives the guard his talk event (talk_gardman) back and returns control to Mario.
 * The versions before the US release wait 240 frames of free movement first.
 */
static EVT_BEGIN(evt_gardman)
    SET_VALUE(LF(0), 0)
    SET_VALUE(LF(1), 0)
    SET_VALUE(LF(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("tou_10"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_08"))
        SET_VALUE(LF(1), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_07"))
        SET_VALUE(LF(2), 1)
    END_IF
#if VERSION <= VERSION_DEMO_US
    SET_VALUE(LW(0), 0)
    LOOP(0)
        ADD(LW(0), 1)
        WAIT_FRAMES(1)
        CALL(evt_mario_wait_movable)
        IF_INT_GREATER(LW(0), 240)
            BREAK_LOOP
        END_IF
    END_LOOP
    LOOP(0)
        CALL(evt_mario_get_motion, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            BREAK_LOOP
        END_IF
        IF_INT_EQUAL(LW(0), 1)
            BREAK_LOOP
        END_IF
        IF_INT_EQUAL(LW(0), 2)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
#else
    CALL(tou_mario_free_wait)
#endif
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_mario_wait_landon)
#if VERSION >= VERSION_US
    WAIT_FRAMES(10)
    CALL(tou_mario_talk_end_wait)
    WAIT_FRAMES(10)
#else
    WAIT_FRAMES(1)
#endif
    BEGIN_INLINE_EVENT
        WAIT_MS(200)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        IF_INT_GREATER(LW(2), -60)
            RETURN
        END_IF
        IF_INT_LESS(LW(0), -35)
            RETURN
        END_IF
        IF_INT_GREATER(LW(0), 35)
            RETURN
        END_IF
        CALL(evt_mario_normalize)
        CALL(evt_mario_dispflag_onoff, 1, MARIO_DISP_FLAG_POSE_LOCK)
#if VERSION >= VERSION_US
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_SURPRISED1"), LW(0), LW(1), LW(2), 0)
#endif
        CALL(evt_mario_set_pose, STRING("M_N_7"))
        CALL(evt_npc_flag_onoff, 1, STRING("ガードマン"), NPC_FLAG_INTANGIBLE)
        CALL(evt_mario_jump_pos, 40, 0, -120, 400, 1, -1000)
        CALL(evt_mario_set_pos, 40, 0, -120)
        CALL(evt_npc_flag_onoff, 0, STRING("ガードマン"), NPC_FLAG_INTANGIBLE)
        WAIT_MS(500)
        CALL(evt_mario_set_pose, STRING("M_S_1"))
        CALL(evt_mario_dispflag_onoff, 0, MARIO_DISP_FLAG_POSE_LOCK)
        CALL(evt_mario_set_dir_npc, STRING("ガードマン"))
    END_INLINE_EVENT
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(1), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_status_onoff, 0, STRING("ガードマン"), 2)
    CALL(evt_npc_flag_onoff, 1, STRING("ガードマン"), NPC_FLAG_INSTANT_TURN)
    CALL(evt_set_dir_to_target, STRING("ガードマン"), STRING("mario"))
    CALL(evt_npc_set_position, STRING("ガードマン"), 0, 0, -170)
    CALL(evt_npc_move_position, STRING("ガードマン"), 0, -90, 0, FLOAT(80.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(1), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_set_dir_to_target, STRING("ガードマン"), STRING("mario"))
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_74"), 0, STRING("ガードマン"))
    END_IF
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_327"), 0, STRING("ガードマン"))
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_msg_print, 0, STRING("stg3_tou_453"), 0, STRING("ガードマン"))
    END_IF
    WAIT_MS(300)
    CALL(evt_npc_change_interrupt, STRING("ガードマン"), 6, PTR(talk_gardman))
    CALL(evt_npc_status_onoff, 1, STRING("ガードマン"), 2)
    CALL(evt_npc_flag_onoff, 0, STRING("ガードマン"), NPC_FLAG_INSTANT_TURN)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(bero_case_switch_off)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

#if VERSION >= VERSION_JP
/** Spawns the guard's walk-through script (evt_gardman). */
EVT_BEGIN(evt_gardman_spawn)
    CALL_CHILD(evt_gardman)
    RETURN
EVT_END()
#endif

/**
 * Shared part of the match registration console:
 * sets which map (tou_10, tou_08 or tou_07) is running and prepares the registration prompts.
 */
EVT_BEGIN(evt_tou_match_make_default_sub)
    SET_VALUE(LF(0), 0)
    SET_VALUE(LF(1), 0)
    SET_VALUE(LF(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("tou_10"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_08"))
        SET_VALUE(LF(1), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_07"))
        SET_VALUE(LF(2), 1)
    END_IF
#if VERSION == VERSION_EU
    SET_VALUE(LF(3), 0)
    CALL(evt_sub_get_language, LW(0))
    IF_INT_EQUAL(LW(0), 3)
        SET_VALUE(LF(3), 1) // French: the two inserted values are swapped
    END_IF
#endif
    CALL(evt_party_stop, 0)
    WAIT_FRAMES(1)
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_cam3d_evt_set, 35, 91, 188, 35, 57, -1, 1000, 11)
        BEGIN_INLINE_EVENT
            CALL(evt_party_move_pos2, 0, 75, -96, FLOAT(80.0f))
            CALL(evt_party_set_dir, 0, 270, 100)
        END_INLINE_EVENT
        CALL(evt_mario_mov_pos2, 35, -96, FLOAT(80.0f))
        CALL(evt_mario_mov_pos2, 38, -99, FLOAT(80.0f))
    ELSE
        CALL(evt_cam3d_evt_set, -75, 91, 188, -75, 57, -1, 1000, 11)
        BEGIN_INLINE_EVENT
            CALL(evt_party_move_pos2, 0, -50, -96, FLOAT(80.0f))
            CALL(evt_party_set_dir, 0, 270, 100)
        END_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -90, -96, FLOAT(80.0f))
        CALL(evt_mario_mov_pos2, -87, -99, FLOAT(80.0f))
    END_IF
    CALL_CHILD(evt_tou_monitor_on)
    WAIT_MS(800)
    CALL(evt_party_run, 0)
    IF_INT_EQUAL(LF(0), 1)
        CALL(evt_mapobj_get_position, STRING("gamen"), LW(0), LW(1), LW(2))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_tou_get_next_match, LW(0))
        SET_VALUE(GSW(GSW_TOU_OPPONENT_ID), LW(0))
        CALL(evt_tou_get_fighter_info, LW(0), LW(1), LW(2))
        CALL(evt_tou_get_fighter_rank, LW(0), LW(3))
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
            IF_INT_EQUAL(LW(3), 10)
                IF_INT_EQUAL(GSWF(GSWF_TOU_IRON_CLEFTS_OPENING_SEEN), 0)
#if VERSION == VERSION_EU
                    IF_INT_EQUAL(LF(3), 0)
                        CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00_01"), 0, STRING("ガンス"), LW(3), LW(1))
                    ELSE
                        CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00_01"), 0, STRING("ガンス"), LW(1), LW(3))
                    END_IF
#else
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00_01"), 0, STRING("ガンス"), LW(3), LW(1))
#endif
                ELSE
#if VERSION == VERSION_EU
                    IF_INT_EQUAL(LF(3), 0)
                        CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
                    ELSE
                        CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(1), LW(3))
                    END_IF
#else
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
#endif
                END_IF
            ELSE
#if VERSION == VERSION_EU
                IF_INT_EQUAL(LF(3), 0)
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
                ELSE
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(1), LW(3))
                END_IF
#else
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
#endif
            END_IF
        ELSE
#if VERSION == VERSION_EU
            IF_INT_EQUAL(LF(3), 0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(3), LW(1))
            ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(1), LW(3))
            END_IF
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(3), LW(1))
#endif
        END_IF
    END_IF
    IF_INT_EQUAL(LF(1), 1)
        CALL(evt_mapobj_get_position, STRING("gamenn"), LW(0), LW(1), LW(2))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_tou_get_next_match, LW(0))
        SET_VALUE(GSW(GSW_TOU_OPPONENT_ID), LW(0))
        CALL(evt_tou_get_fighter_info, LW(0), LW(1), LW(2))
        CALL(evt_tou_get_fighter_rank, LW(0), LW(3))
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
            IF_INT_EQUAL(LW(3), 0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00_01"), 0, STRING("ガンス"), LW(1))
            ELSE
#if VERSION == VERSION_EU
                IF_INT_EQUAL(LF(3), 0)
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
                ELSE
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(1), LW(3))
                END_IF
#else
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
#endif
            END_IF
        ELSE
            IF_INT_EQUAL(LW(3), 0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361_01"), 0, STRING("キノシコワ"), LW(1))
            ELSE
#if VERSION == VERSION_EU
                IF_INT_EQUAL(LF(3), 0)
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(3), LW(1))
                ELSE
                    CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(1), LW(3))
                END_IF
#else
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(3), LW(1))
#endif
            END_IF
        END_IF
        IF_INT_EQUAL(GSW(GSW_TOU_OPPONENT_ID), 0)
            IF_INT_EQUAL(GSWF(GSWF_TOU_CHAMP_OPENING_SEEN), 0)
                SET_VALUE(GSWF(GSWF_TOU_TITLE_MATCH_RESERVED), 1)
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_mapobj_get_position, STRING("gamenn"), LW(0), LW(1), LW(2))
        CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
        CALL(evt_tou_get_next_match, LW(0))
        SET_VALUE(GSW(GSW_TOU_OPPONENT_ID), LW(0))
        CALL(evt_tou_get_fighter_info, LW(0), LW(1), LW(2))
        CALL(evt_tou_get_fighter_rank, LW(0), LW(3))
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
#if VERSION == VERSION_EU
            IF_INT_EQUAL(LF(3), 0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
            ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(1), LW(3))
            END_IF
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_107_00"), 0, STRING("ガンス"), LW(3), LW(1))
#endif
        ELSE
#if VERSION == VERSION_EU
            IF_INT_EQUAL(LF(3), 0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(3), LW(1))
            ELSE
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(1), LW(3))
            END_IF
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_re_361"), 0, STRING("キノシコワ"), LW(3), LW(1))
#endif
        END_IF
    END_IF
    CALL(evt_tou_get_rule_info, GSW(GSW_TOU_OPPONENT_ID), LW(10), LW(13), LW(14), LW(15))
    SET_VALUE(GSW(GSW_TOU_MATCH_RULE), LW(13))
    SET_VALUE(GSW(GSW_TOU_MATCH_RULE_PARAM1), LW(14))
    SET_VALUE(GSW(GSW_TOU_MATCH_RULE_PARAM2), LW(15))
    CALL(evt_msg_print_add, 0, LW(10))
    CALL_CHILD(evt_tou_monitor_off)
    WAIT_MS(500)
    SET_VALUE(LW(0), 0)
    CALL_CHILD(bero_case_switch_off)
#if VERSION <= VERSION_DEMO_US
    IF_INT_EQUAL(LF(2), 1)
        SET_VALUE(LW(0), 1)
        CALL_CHILD(bero_case_switch_off)
    END_IF
#endif
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_tou_get_ranking, LW(0))
    IF_INT_EQUAL(LW(0), 3)
        IF_INT_EQUAL(GSWF(GSWF_TOU_POISON_CAKE_EVENT), 0)
            SET_VALUE(GSWF(GSWF_TOU_POISON_CAKE_EVENT), 1)
            CALL_CHILD(evt_doku_cake)
        END_IF
    END_IF
    SPAWN_EVENT(evt_gardman)
    SET_VALUE(GSWF(GSWF_TOU_MATCH_RESERVED), 1)
    IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
        IF_INT_EQUAL(GSW(GSW_TOU_OPPONENT_ID), 18)
            IF_INT_EQUAL(GSWF(GSWF_TOU_KING_K_MATCH_SCENE), 0)
                SET_VALUE(GSWF(GSWF_TOU_KING_K_MATCH_SCENE), 1)
                CALL_CHILD(evt_michel_1)
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Interaction with the match registration console ("M_make"):
 * prints the registration prompt and lets Mario reserve a match, picking the opponent and rule.
 * Returns without effect if Mario's controls are disabled.
 */
EVT_BEGIN(evt_tou_match_make_default)
#if VERSION >= VERSION_JP
    CALL(tou_mario_keyoff_check, LW(0))
    IF_INT_EQUAL(LW(0), 1)
        RETURN
    END_IF
#endif
    CALL(evt_hit_get_position, STRING("M_make"), LW(10), LW(11), LW(12))
    CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_TOUROKU_COM1"), LW(10), LW(11), LW(12), 0)
    SET_VALUE(LF(0), 0)
    SET_VALUE(LF(1), 0)
    SET_VALUE(LF(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("tou_10"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_08"))
        SET_VALUE(LF(1), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_07"))
        SET_VALUE(LF(2), 1)
    END_IF
    CALL(evt_mario_key_onoff, 0)
    IF_INT_EQUAL(LF(0), 1)
        SET_VALUE(LW(10), STRING("stg3_tou_103"))
        SET_VALUE(LW(11), STRING("stg3_tou_103_yn"))
        SET_VALUE(LW(12), STRING("stg3_tou_104_01"))
    END_IF
    IF_INT_EQUAL(LF(1), 1)
        SET_VALUE(LW(10), STRING("stg3_tou_105"))
        SET_VALUE(LW(11), STRING("stg3_tou_105_yn"))
        SET_VALUE(LW(12), STRING("stg3_tou_106_01"))
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        SET_VALUE(LW(10), STRING("stg3_tou_476"))
        SET_VALUE(LW(11), STRING("stg3_tou_476_yn"))
        SET_VALUE(LW(12), STRING("stg3_tou_477_01"))
    END_IF
    CALL(evt_msg_print, 0, LW(10), 0, 0)
    CALL(evt_msg_select, 0, LW(11))
    SWITCH(LW(0))
        CASE_EQUAL(0)
        SET_VALUE(LF(10), 0)
        SET_VALUE(LF(11), 0)
        SWITCH(GSW(GSW_STORY_PROGRESS))
            CASE_BETWEEN(STORY_STG3_20_00_MAJORS_8TH_PLACE, STORY_STG3_20_03_THE_YELLOW_BLOCK)
            SET_VALUE(LF(10), 1)
            IF_INT_EQUAL(LF(0), 1)
                CALL(evt_tou_get_ranking, LW(0))
                IF_INT_LESS(LW(0), 11)
                    SET_VALUE(LF(10), 0)
                    SET_VALUE(LF(11), 1)
                END_IF
            END_IF
            CASE_EQUAL(STORY_STG3_20_04_CONFISCATED)
            IF_INT_EQUAL(LF(0), 1)
                CALL(evt_tou_get_ranking, LW(0))
                IF_INT_LESS(LW(0), 11)
                    SET_VALUE(LF(11), 1)
                END_IF
            END_IF
            CASE_BETWEEN(STORY_STG3_20_05_MAJORS_4TH_PL, STORY_STG3_20_11_HOLE_IN_THE_FLOOR)
            SET_VALUE(LF(10), 1)
            CASE_BETWEEN(STORY_STG3_20_13_MAJORS_1ST_PL, STORY_STG3_20_15_UNLOCKING_THE_DOOR)
            SET_VALUE(LF(10), 1)
#if VERSION <= VERSION_DEMO_US
            CASE_EQUAL(STORY_STG3_31_GRUBBAS_PLANS)
#else
            CASE_BETWEEN(STORY_STG3_30_NEW_CHAMPION, STORY_STG3_31_GRUBBAS_PLANS)
#endif
            SET_VALUE(LF(10), 1)
            CASE_GREATER_OR_EQUAL(STORY_STG3_34_RETURN_TO_ROGUEPORT)
            IF_INT_EQUAL(LF(0), 1)
                CALL(evt_tou_get_ranking, LW(0))
                IF_INT_EQUAL(LW(0), 10)
                    SET_VALUE(LF(11), 1)
                END_IF
            END_IF
        END_SWITCH
        IF_INT_EQUAL(LF(10), 1)
            CALL(evt_party_stop, 0)
            CALL(evt_msg_print_add, 1, STRING("<scrl_auto><once_stop>"))
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_106_02"))
            CALL(evt_party_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_mario_get_pos, 0, LW(3), LW(4), LW(5))
            IF_INT_LESS(LW(0), LW(3))
                CALL(evt_mario_set_dir, 270, 300, 0)
            ELSE
                CALL(evt_mario_set_dir, 90, 300, 0)
            END_IF
            CALL(evt_msg_print_party, STRING("stg3_tou_106_03"))
            CALL(evt_party_run, 0)
            CALL(evt_mario_key_onoff, 1)
            RETURN
        END_IF
        IF_INT_EQUAL(LF(11), 1)
            CALL(evt_msg_print_add, 1, STRING("<scrl_auto><once_stop>"))
            CALL(evt_msg_print_add, 0, STRING("stg3_tou_104_01_1"))
            CALL(evt_mario_key_onoff, 1)
            RETURN
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU_MATCH_RESERVED), 1)
            CALL(evt_tou_get_fighter_info, GSW(GSW_TOU_OPPONENT_ID), LW(0), LW(1))
            CALL(evt_tou_get_rule_msg2, GSW(GSW_TOU_MATCH_RULE), LW(2))
            CALL(evt_msg_print_add, 1, STRING("<scrl_auto><once_stop>"))
            CALL(evt_msg_print_add_insert, 0, LW(12), LW(0), LW(2))
        ELSE
            CALL(evt_msg_continue)
            CALL_CHILD(evt_tou_match_make_default_sub)
        END_IF
        CASE_EQUAL(1)
        CALL(evt_msg_continue)
        CALL(evt_tou_print_ranking)
        CASE_DEFAULT
        CALL(evt_msg_continue)
    END_SWITCH
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Talk script of the poison cake: Mario gets a message (stg3_tou_307_04). */
EVT_BEGIN(evt_talk_doku_cake)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_307_04"), 0, STRING("me"))
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Mario's decision to eat the poison cake: partner remark, a yes/no prompt and, on yes, the eating sequence. */
EVT_BEGIN(evt_eat_doku_cake)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
#if VERSION >= VERSION_JP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_party_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(10))
    IF_INT_GREATER(LW(10), 100)
        CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_party_set_dir_pos, 0, 20, -20)
    END_IF
#endif
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg3_tou_296_doku"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_297_doku"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg3_tou_297_yn_doku"))
    CALL(evt_msg_continue)
    IF_INT_NOT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_party, STRING("stg3_tou_298_doku"))
        CALL(evt_mario_key_onoff, 1)
        CALL(evt_party_run, 0)
        RETURN
    END_IF
#if VERSION >= VERSION_JP
    CALL(evt_party_flg_onoff, 0, 16777216, 1)
#endif
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    BEGIN_INLINE_EVENT
        SUBTRACT(LW(2), 30)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(50.0f))
#else
        CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(80.0f))
#endif
        CALL(evt_mario_adjust_dir)
    END_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
    CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(50.0f))
#else
    CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(80.0f))
#endif
    CALL(evt_msg_print_party, STRING("stg3_tou_299_doku"))
    CALL(evt_item_delete, STRING("doku_cake"))
    CALL(evt_party_set_breed_pose, 0, 7)
    BEGIN_INLINE_EVENT_GET_ID(LW(0))
        LOOP(0)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_EAT_CAKE1"), LW(0), LW(1), LW(2), 0)
            WAIT_MS(500)
        END_LOOP
    END_INLINE_EVENT
    WAIT_MS(1000)
    DELETE_EVENT(LW(0))
    CALL(evt_msg_print_party, STRING("stg3_tou_300"))
    WAIT_MS(300)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT)
    CALL(evt_snd_envoff, PSND_FADE_OUT)
    CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
        CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_ENV_SURPRISED2"))
        WAIT_MS(1000)
        CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
        CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    END_INLINE_EVENT
    CALL_CHILD(party_npc_replace)
    WAIT_MS(300)
    CALL(evt_mario_get_party, LW(3))
    SWITCH(LW(3))
        CASE_EQUAL(PARTY_MEMBER_GOOMBELLA)
        CALL(evt_msg_print, 0, STRING("stg3_tou_301_kur"), 0, STRING("dummy_party"))
        CASE_EQUAL(PARTY_MEMBER_KOOPS)
        CALL(evt_msg_print, 0, STRING("stg3_tou_301_nok"), 0, STRING("dummy_party"))
        CASE_EQUAL(PARTY_MEMBER_FLURRIE)
        CALL(evt_msg_print, 0, STRING("stg3_tou_301_win"), 0, STRING("dummy_party"))
        CASE_EQUAL(PARTY_MEMBER_YOSHI)
        CALL(evt_msg_print, 0, STRING("stg3_tou_301_yos"), 0, STRING("dummy_party"))
    END_SWITCH
    WAIT_MS(300)
    SET_VALUE(GSWF(GSWF_TOU_POISON_CAKE_ON_TABLE), 0)
    SET_VALUE(GSWF(GSWF_TOU_PARTNER_POISONED), 1)
#if VERSION >= VERSION_JP
    CALL(evt_party_flg_onoff, 0, 16777216, 0)
#endif
    CALL(evt_party_stop, 0)
    CALL(evt_mario_kill_party, 0)
    CALL(evt_pouch_party_left, 1)
    CALL(evt_pouch_party_left, 2)
    CALL(evt_pouch_party_left, 5)
    CALL(evt_pouch_party_left, 4)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
    CALL(evt_snd_bgmoff, PSND_FADE_DIP_TO(70))
    CALL(evt_snd_envon, PSND_FADE_RESTART | PSND_FADE_IN, STRING("ENV_STG3_TOU6"))
    CALL(evt_mario_key_onoff, 1)
    CALL(evt_exit_case_evt)
    RETURN
EVT_END()

/** Guess: poison cake delivery scene; a character comes in through the door of the room and sets the cake down. */
EVT_BEGIN(evt_doku_cake)
    WAIT_MS(2000)
    CALL(evt_npc_set_position, STRING("キノシコワ"), 0, 0, -180)
    CALL(evt_npc_set_ry, STRING("キノシコワ"), 270)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        SET_VALUE(LW(1), 0)
        SPAWN_EVENT(bero_close_door_play_se)
        CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
        LOOP(0)
            CALL(evt_sub_intpl_msec_get_value)
            MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
            IF_INT_EQUAL(LW(1), 0)
                BREAK_LOOP
            END_IF
            WAIT_FRAMES(1)
        END_LOOP
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(500)
        CALL(evt_mario_set_dir_npc, STRING("キノシコワ"))
        CALL(evt_party_set_dir_npc, 0, STRING("キノシコワ"))
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("キノシコワ"), -1, -25, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_295_doku"), 0, STRING("キノシコワ"))
    CALL(evt_npc_set_ry, STRING("キノシコワ"), 90)
    WAIT_MS(300)
    CALL(evt_item_entry, STRING("doku_cake"), ITEM_POISONED_CAKE, 20, 25, -25, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
#if VERSION >= VERSION_JP
    CALL(evt_item_status_on, STRING("doku_cake"), ITEM_STATUS_NO_KOOPS)
#endif
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("a_cake"), 0, PTR(evt_eat_doku_cake), 0)
    WAIT_MS(500)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -130, 0, FLOAT(80.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -200, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_set_position, STRING("キノシコワ"), 0, -1000, 0)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    SET_VALUE(GSWF(GSWF_TOU_POISON_CAKE_ON_TABLE), 1)
    RETURN
EVT_END()

/** Guess: Michel's first scene; Mario and the partner turn to him, the camera pans and he talks (stg3_npc_10_01_01). */
EVT_BEGIN(evt_michel_1)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir_npc, STRING("マイケル"))
        CALL(evt_party_set_dir_npc, 0, STRING("マイケル"))
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, -20, 93, 290, -20, 57, -8, 1000, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 40, -80, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_npc_10_01_01"), 0, STRING("マイケル"))
    CALL(evt_cam3d_evt_off, 500, 11)
    RETURN
EVT_END()

/** Guess: Michel's second line (stg3_npc_10_01_02) with a camera zoom, then he walks away. */
EVT_BEGIN(evt_michel_2)
    CALL(evt_cam3d_evt_set, -45, 105, 288, -45, 60, -9, 2000, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 0, -80, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_npc_10_01_02"), 0, STRING("マイケル"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 90, -90, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_set_ry, STRING("マイケル"), 270)
    RETURN
EVT_END()

/** Door helper: the NPC named in LW(0) walks out through door_1 and is hidden at y = -1000 once the door has closed. */
EVT_BEGIN(evt_michel_3_sub)
    SET_VALUE(LW(3), LW(0))
    CALL(evt_npc_move_position, LW(3), 0, -130, 0, FLOAT(80.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, LW(3), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, LW(3), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    RETURN
EVT_END()

/** Guess: Michel scene; he turns to Mario and talks with a camera move (stg3_tou_93_17 and following). */
EVT_BEGIN(evt_michel_3)
    CALL(evt_set_dir_to_target, STRING("マイケル"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_17"), 0, STRING("マイケル"))
    CALL(evt_cam3d_evt_set, 100, 93, 290, 100, 57, -8, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_18"), 0, STRING("マイケル"))
    CALL(evt_npc_set_position, STRING("ブロッツ"), 0, 0, -200)
    CALL(evt_npc_set_position, STRING("キノシコワ"), 0, 0, -170)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_19"), 0, STRING("キノシコワ"))
    CALL(evt_cam3d_evt_set, 0, 112, 287, 0, 60, -8, 1000, 11)
    WAIT_MS(1000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_npc_status_onoff, 1, STRING("ブロッツ"), 2)
        CALL(evt_npc_move_position, STRING("ブロッツ"), 1, -75, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING("ブロッツ"), -25, -75, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING("ブロッツ"), STRING("キノシコワ"))
    END_INLINE_EVENT
    CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 1, -75, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 25, -75, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ブロッツ"))
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(-0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_20"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(600)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
    SET_VALUE(LW(0), STRING("キノシコワ"))
    CALL_CHILD(evt_michel_3_sub)
    CALL(evt_npc_move_position, STRING("マイケル"), 25, -75, 0, FLOAT(80.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_21"), 0, STRING("マイケル"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_22"), 0, STRING("ブロッツ"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_23"), 0, STRING("マイケル"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_23_01"), 0, STRING("ブロッツ"))
    SET_VALUE(LW(0), STRING("ブロッツ"))
    CALL_CHILD(evt_michel_3_sub)
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 90, -90, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_set_ry, STRING("マイケル"), 270)
    RETURN
EVT_END()

/**
 * Guess: Michel scene with a startled-Mario reaction (surprised voice and "!" bubble),
 * then dialogue (stg3_tou_93_24).
 */
EVT_BEGIN(evt_michel_4)
    CALL(evt_cam3d_evt_set, -45, 105, 288, -45, 60, -9, 2000, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 0, -80, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24"), 0, STRING("マイケル"))
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_2"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff_fukidashi, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        CALL(evt_eff_fukidashi, 1, 0, STRING("マイケル"), 0, 0, 0, 0, 0, 0, 0, 0)
    END_INLINE_EVENT
    CALL(evt_msg_toge, 1, 0, 0, 0)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_01"), 0, 0)
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_mario_set_dir, 270, 300, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        WAIT_MS(1000)
        CALL(evt_party_set_dir, 0, 270, 300)
    END_INLINE_EVENT
    CALL(evt_cam3d_evt_set, -165, 105, 288, -165, 60, -9, 2000, 11)
    WAIT_MS(2000)
    CALL(evt_cam3d_evt_set, 185, 105, 288, 185, 60, -9, 15000, 11)
    CALL(evt_msg_toge, 2, -165, 50, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_02"), 0, 0)
    CALL(evt_msg_toge, 2, -125, 40, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_03"), 0, 0)
    BEGIN_INLINE_EVENT
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    BEGIN_INLINE_EVENT
        CALL(evt_party_set_dir, 0, 90, 300)
    END_INLINE_EVENT
    CALL(evt_msg_toge, 2, -85, 20, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_04"), 0, 0)
    CALL(evt_msg_toge, 2, -45, 50, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_05"), 0, 0)
    CALL(evt_msg_toge, 2, 0, 40, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_06"), 0, 0)
    CALL(evt_npc_set_ry, STRING("マイケル"), 90)
    CALL(evt_msg_toge, 2, 45, 10, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_07"), 0, 0)
    CALL(evt_msg_toge, 2, 85, 30, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_08"), 0, 0)
    CALL(evt_msg_toge, 2, 125, 40, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_09"), 0, 0)
    CALL(evt_msg_toge, 2, 165, 50, -200)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_10"), 0, 0)
    CALL(evt_cam3d_evt_set, -45, 105, 288, -45, 60, -9, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_11"), 0, STRING("マイケル"))
    WAIT_MS(200)
    CALL(evt_npc_set_ry, STRING("マイケル"), 270)
    WAIT_MS(200)
    CALL(evt_set_dir_to_target, STRING("マイケル"), STRING("mario"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_24_12"), 0, STRING("マイケル"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 90, -90, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_set_ry, STRING("マイケル"), 270)
    RETURN
EVT_END()

/** Guess: Michel's next line (stg3_tou_93_25) with the same camera framing as the previous scenes. */
EVT_BEGIN(evt_michel_5)
    CALL(evt_cam3d_evt_set, -45, 105, 288, -45, 60, -9, 2000, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 0, -80, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_25"), 0, STRING("マイケル"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 90, -90, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_set_ry, STRING("マイケル"), 270)
    RETURN
EVT_END()

/** Guess: Michel's next line (stg3_tou_93_26) with the same camera framing. */
EVT_BEGIN(evt_michel_6)
    CALL(evt_cam3d_evt_set, -45, 105, 288, -45, 60, -9, 2000, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 0, -80, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_26"), 0, STRING("マイケル"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 90, -90, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_set_ry, STRING("マイケル"), 270)
    RETURN
EVT_END()

/** Guess: Michel's next line (stg3_tou_93_27) with the same camera framing. */
EVT_BEGIN(evt_michel_7)
    CALL(evt_cam3d_evt_set, -45, 105, 288, -45, 60, -9, 2000, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 0, -80, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_27"), 0, STRING("マイケル"))
    CALL(evt_cam3d_evt_off, 500, 11)
    CALL(evt_npc_move_position, STRING("マイケル"), 90, -90, 0, FLOAT(60.0f), 1)
    CALL(evt_npc_set_ry, STRING("マイケル"), 270)
    RETURN
EVT_END()

/**
 * Script helper: sets up and renders the monitor texture each frame.
 * Allocates the work area and a 128x128 texture, fades the screen alpha toward on/off, and queues gans_tex.
 * Blocks forever as the owning script.
 */
static USER_FUNC(make_monitor) {
    NpcEntry* npc = npcNameToPtr_NoAssert(evtGetValue(NULL, GSW(GSW_STORY_PROGRESS)) < STORY_STG3_34_RETURN_TO_ROGUEPORT ? "ガンス" : "キノシコワ");
    GansWork* wp;

    if (isFirstCall) {
        wp = _mapAlloc(sizeof(GansWork));
        event->userdatap[0] = wp;
        wp->onoff = 0;
        wp->ready = 0;
    }
    if (npc == NULL) {
        return EVT_RETURN_BLOCK;
    }
    wp = event->userdatap[0];
    gans_wp = wp;
    wp->buf = smartAlloc(GXGetTexBufferSize(0x80, 0x80, GX_TF_RGB5A3, GX_FALSE, 0), 3);
    GXInitTexObj(&wp->tex, wp->buf->address, 0x80, 0x80, GX_TF_RGB5A3, GX_CLAMP, GX_CLAMP, GX_FALSE);
    GXInitTexObjLOD(&wp->tex, GX_LINEAR, GX_LINEAR, 0.0f, 0.0f, 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
    if (gans_wp->onoff) {
        gans_wp->alpha += 4;
        if (gans_wp->alpha > 0x80) {
            gans_wp->alpha = 0x80;
        }
    } else {
        gans_wp->alpha -= 4;
        if (gans_wp->alpha < 0) {
            gans_wp->alpha = 0;
        }
    }
    dispEntry(CAMERA_SHADOW, 0.0f, 3, gans_tex, wp);
    return EVT_RETURN_BLOCK;
}

/**
 * TEV callback for the monitor screen: replaces the screen's color stages with the live texture,
 * blended by the work alpha, once the texture has been rendered at least once.
 */
static void monitor_tev(MapTevCallbackInfo* info) {
    if (gans_wp->ready) {
        GXSetTexCoordGen2(GX_TEXCOORD1, GX_TG_MTX2x4, GX_TG_TEX0, 60, GX_FALSE, GX_PTIDENTITY);
        GXLoadTexObj(smartTexObj(&gans_wp->tex, &gans_wp->buf->address), GX_TEXMAP1);
        GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD1, GX_TEXMAP1, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_TEXC);
        GXSetTevAlphaIn(GX_TEVSTAGE0, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
        GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);
        GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_TEXC, GX_CC_CPREV, GX_CC_A0, GX_CC_ZERO);
        GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_ZERO, GX_CA_ZERO, GX_CA_TEXA);
        GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
        {
            GXSetTevColor(GX_TEVREG0, tou_mkcolor(gans_wp->alpha));
        }
        info->tevStage = 2;
        info->texMap = 2;
        info->texCoord = 2;
    }
}

/** Script helper: args[0] = 1/0 to fade the registration monitor in or out. */
static USER_FUNC(onoff) {
    gans_wp->onoff = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

/** Script helper: args[0] receives Yoshi's color (0-6) from the pouch. */
static USER_FUNC(getYoshiColor) {
    EvtWord* args = event->args;
    evtSetValue(event, args[0], pouchGetPartyColor(4));
    return EVT_RETURN_DONE;
}

/** Script helper: args[0] receives 1 if Yoshi is currently in the party, else 0. */
static USER_FUNC(chk) {
    EvtWord* args = event->args;
    evtSetValue(event, args[0], partyChkJoin(4) != 0);
    return EVT_RETURN_DONE;
}

#if VERSION >= VERSION_JP
/** Script helper: waits until Mario has been idle, walking or dashing (and not locked out) for 240 frames in total. */
USER_FUNC(tou_mario_free_wait) {
    MarioWork* mario = marioGetPtr();

    if (isFirstCall) {
        event->userdata[0] = 0;
    }
    if (!marioKeyOffChk() && !marioCtrlOffChk() && (mario->currMotionId == MARIO_MOTION_STAY || mario->currMotionId == MARIO_MOTION_WALK || mario->currMotionId == MARIO_MOTION_DASH)) {
        event->userdata[0]++;
        if (event->userdata[0] > 240) {
            event->userdata[0] = 240;
            return EVT_RETURN_DONE;
        }
    }
    return EVT_RETURN_BLOCK;
}
#endif

#if VERSION >= VERSION_US
/** Script helper: blocks until Mario leaves his talking motion. */
USER_FUNC(tou_mario_talk_end_wait) {
    return marioGetPtr()->currMotionId != MARIO_MOTION_TALK ? EVT_RETURN_DONE : EVT_RETURN_BLOCK;
}
#elif VERSION >= VERSION_JP
/** Script helper: args[0] receives 1 if Mario's key input or control is currently disabled, else 0. */
USER_FUNC(tou_mario_keyoff_check) {
    EvtWord* args = event->args;

    if (marioKeyOffChk() || marioCtrlOffChk()) {
        evtSetValue(event, args[0], 1);
    } else {
        evtSetValue(event, args[0], 0);
    }
    return EVT_RETURN_DONE;
}
#endif

/** Script helper: stops Octor's regular script and parks him at (80, 0, 85) facing 270 degrees. */
static USER_FUNC(octo_stop) {
    NpcEntry* npc = npcNameToPtr_NoAssert("オクトール");

    if (npc != NULL) {
        evtStopID(npc->regularEvtId);
        npc->prevPosition = (Vec){80.0f, 0.0f, 85.0f};
        npc->position = npc->prevPosition;
        npc->direction = 270.0f;
    }
    return EVT_RETURN_DONE;
}

/** Script helper: restarts Octor's regular script. */
static USER_FUNC(octo_start) {
    NpcEntry* npc = npcNameToPtr_NoAssert("オクトール");

    if (npc != NULL) {
        evtStartID(npc->regularEvtId);
    }
    return EVT_RETURN_DONE;
}

/**
 * Script helper: args[0] = Mario's rank, args[1] = won?, args[2] receives the coin payout:
 * 1 on a loss, 20 for the title match, and otherwise a payout growing as the opponent's rank rises.
 */
static USER_FUNC(fight_money) {
    EvtWord* args = event->args;
    s32 rank = evtGetValue(event, args[0]);
    s32 win = evtGetValue(event, args[1]);
    s32 money;

    if (win) {
        if (rank > 10) {
            money = (s32)(0.99f + (2.0f + (21 - rank) / 2.0f));
        } else if (rank > 0) {
            money = (s32)(0.99f + (5.0f + (21 - rank) / 2.0f));
        } else {
            money = 20;
        }
    } else {
        money = 1;
    }
    evtSetValue(event, args[2], money);
    return EVT_RETURN_DONE;
}

/** Returns the 3D camera's yaw (0-360 degrees), computed from its position and look-at point. */
static f32 camGetRy(void) {
    CameraEntry* cam = camGetPtr(CAMERA_3D);
    f32 ry = reviseAngle(57.29579f * (f32)atan2(-(cam->cameraAt.x - cam->cameraPos.x), -(cam->cameraAt.z - cam->cameraPos.z)));

    if (ry < 0.0f) {
        ry += 360.0f;
    }
    return ry;
}

/**
 * Script helper (args[0] = NPC name): draws the Champion's Belt (a star-stone effect) at the NPC's "locator8"
 * joint, following its rotation and the camera;
 * hides it when the NPC is below the floor or the belt is switched off.
 */
USER_FUNC(tou_champion_belt) {
    void** udPtr; // FAKE: alias of &eff->userdata; a typed StarStoneWork* local or direct eff->userdata changes codegen
    EffectEntry* eff;
    s32 idx;
    Vec* positions;
    NpcEntry* npc;
    f32 angle;
    AnimationPose* pose;

    npc = npcNameToPtr((const char*)evtGetValue(event, event->args[0]));
    if (isFirstCall) {
        EffectEntry* entry = effStarStoneEntry(9, 0.0f, 0.0f, 0.0f, 0.6f);
        animPoseWorldPositionEvalOn(npc->poseId);
        event->userdatap[0] = entry;
        champion_belt_onoff = 0;
    }
    pose = animPoseGetAnimPosePtr(npc->poseId);
    positions = *pose->worldPositions;
    idx = animPoseGetGroupIdx(npc->poseId, "locator8");
    angle = reviseAngle(camGetRy() - pose->rotationY);
    eff = event->userdatap[0];
    udPtr = &eff->userdata;
    ((StarStoneWork*)(*udPtr))->pos.x = positions[idx].x;
    ((StarStoneWork*)(*udPtr))->pos.y = positions[idx].y;
    ((StarStoneWork*)(*udPtr))->pos.z = positions[idx].z;
    if ((angle > 90.0f && angle <= 270.0f) || (angle < -90.0f && angle >= -270.0f)) {
        ((StarStoneWork*)(*udPtr))->rot = 8.0f - (angle + camGetPtr(CAMERA_3D)->viewYaw);
    } else {
        ((StarStoneWork*)(*udPtr))->rot = -(angle + camGetPtr(CAMERA_3D)->viewYaw) - 8.0f;
    }
    if (npc->position.y <= -1000.0f) {
        ((StarStoneWork*)(*udPtr))->pos.x = 0.0f;
        ((StarStoneWork*)(*udPtr))->pos.y = -1000.0f;
        ((StarStoneWork*)(*udPtr))->pos.z = 0.0f;
    }
    if (champion_belt_onoff) {
        ((StarStoneWork*)(*udPtr))->pos.x = 0.0f;
        ((StarStoneWork*)(*udPtr))->pos.y = -1000.0f;
        ((StarStoneWork*)(*udPtr))->pos.z = 0.0f;
    }
    return EVT_RETURN_BLOCK;
}

/** Script helper: args[0] = 1 hides the Champion's Belt effect, 0 shows it. */
static USER_FUNC(tou_champion_belt_onoff) {
    champion_belt_onoff = evtGetValue(event, event->args[0]);
    return EVT_RETURN_DONE;
}

/**
 * Guess: scene where Octor and Gangan are at the door and the next visitors enter (Pogo, Jolene);
 * camera cuts and dialogue stg3_tou_93_28 to 30.
 */
EVT_BEGIN(evt_michel_8)
    CALL(evt_npc_set_position, STRING("オクトール"), 145, 0, 50)
    CALL(evt_npc_set_position, STRING("ガンガン"), 95, 0, 50)
    CALL(evt_cam3d_evt_set, 95, 109, 419, 95, 45, -6, 1000, 11)
    WAIT_MS(1000)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_28"), 0, STRING("オクトール"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_29"), 0, STRING("ガンガン"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_30"), 0, STRING("オクトール"))
    CALL(evt_cam3d_evt_set, 0, 112, 287, 0, 60, -8, 1000, 11)
    WAIT_MS(1000)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_npc_set_position, STRING("ポグ"), 0, 0, -200)
#else
    CALL(evt_npc_set_position, STRING("ポグ"), -1, 0, -200)
#endif
    CALL(evt_npc_set_position, STRING("キノシコワ"), 0, 0, -180)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        WAIT_MS(400)
#if VERSION <= VERSION_DEMO_US
        CALL(evt_npc_move_position, STRING("ポグ"), 0, -85, 0, FLOAT(80.0f), 1)
#else
        CALL(evt_npc_move_position, STRING("ポグ"), 0, -80, 0, FLOAT(80.0f), 1)
#endif
        CALL(evt_set_dir_to_target, STRING("ポグ"), STRING("キノシコワ"))
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -120, 0, FLOAT(80.0f), 1)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 40, -100, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ポグ"))
#if VERSION >= VERSION_JP
    WAIT_MS(500)
#endif
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
#if VERSION <= VERSION_DEMO_US
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
#else
        MULTIPLY_FLOAT(LW(0), FLOAT(0.4716797f))
#endif
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_31"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(600)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_32"), 0, STRING("キノシコワ"))
    CALL(evt_cam3d_evt_set, -70, 112, 287, -70, 60, -8, 1000, 11)
    CALL(evt_npc_move_position, STRING("キノシコワ"), -40, -100, 0, FLOAT(80.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_33"), 0, STRING("キノシコワ"))
    BEGIN_INLINE_EVENT
        CALL(evt_mario_mov_pos2, -110, -70, FLOAT(60.0f))
        CALL(evt_mario_set_dir, 90, 300, 0)
    END_INLINE_EVENT
    CALL(evt_npc_move_position, STRING("ポグ"), -70, -95, 0, FLOAT(80.0f), 1)
#if VERSION >= VERSION_JP
    CALL(evt_npc_move_position, STRING("ポグ"), -70, -120, 0, FLOAT(80.0f), 1)
    WAIT_MS(1000)
#endif
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_34"), 0, STRING("キノシコワ"))
    CALL(evt_npc_get_position, STRING("ポグ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_jump_position_nohit, STRING("ポグ"), LW(0), LW(1), LW(2), 500, 30)
    CALL_CHILD(evt_tou_monitor_on)
    WAIT_MS(800)
    CALL(evt_mapobj_get_position, STRING("gamen"), LW(0), LW(1), LW(2))
    CALL(evt_msg_toge, 2, LW(0), LW(1), LW(2))
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_35"), 0, STRING("ガンス"))
    CALL_CHILD(evt_tou_monitor_off)
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_36"), 0, STRING("キノシコワ"))
    CALL(evt_npc_get_position, STRING("ポグ"), LW(0), LW(1), LW(2))
    CALL(evt_npc_jump_position_nohit, STRING("ポグ"), LW(0), LW(1), LW(2), 500, 30)
#if VERSION >= VERSION_US
    CALL(evt_msg_print_add, 0, STRING("stg3_tou_93_37"))
#else
    CALL(evt_msg_continue)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_37"), 0, STRING("キノシコワ"))
#endif
    WAIT_MS(300)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
    WAIT_MS(600)
    CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
#if VERSION >= VERSION_JP
    CALL(evt_npc_move_position, STRING("ポグ"), -70, -95, 0, FLOAT(80.0f), 1)
#endif
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_38"), 0, STRING("ポグ"))
    WAIT_MS(2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, -180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
#if VERSION <= VERSION_DEMO_US
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
#else
        MULTIPLY_FLOAT(LW(0), FLOAT(0.4716797f))
#endif
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
#if VERSION <= VERSION_DEMO_US
    CALL(evt_npc_set_position, STRING("ガードマン"), 0, 0, -170)
    CALL(evt_npc_move_position, STRING("ガードマン"), 0, -120, 0, FLOAT(80.0f), 1)
#else
    CALL(evt_npc_set_position, STRING("ガードマン"), -1, 0, -170)
    CALL(evt_npc_move_position, STRING("ガードマン"), 0, -100, 0, FLOAT(80.0f), 1)
#endif
    CALL(evt_set_dir_to_target, STRING("ガードマン"), STRING("mario"))
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, -180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
#if VERSION <= VERSION_DEMO_US
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
#else
        MULTIPLY_FLOAT(LW(0), FLOAT(0.4716797f))
#endif
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_38_00"), 0, STRING("ガードマン"))
    WAIT_MS(300)
    CALL(evt_msg_print, 0, STRING("stg3_tou_93_39"), 0, STRING("キノシコワ"))
    WAIT_MS(300)
#if VERSION <= VERSION_DEMO_US
    CALL(evt_npc_move_position, STRING("キノシコワ"), 30, -100, 0, FLOAT(80.0f), 1)
    CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ポグ"))
#else
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノシコワ"), 30, -100, 0, FLOAT(80.0f), 1)
        CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("ポグ"))
    END_INLINE_EVENT
#endif
    CALL(evt_npc_move_position, STRING("ガードマン"), 0, -130, 0, FLOAT(80.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
#if VERSION <= VERSION_DEMO_US
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
#else
        MULTIPLY_FLOAT(LW(0), FLOAT(0.4716797f))
#endif
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    BEGIN_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
        CALL(evt_npc_move_position, STRING("ガードマン"), 0, -120, 0, FLOAT(80.0f), 1)
#endif
        CALL(evt_npc_move_position, STRING("ガードマン"), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, STRING("ガードマン"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(300)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ポグ"), 0, -120, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING("ポグ"), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, STRING("ポグ"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -120, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, STRING("キノシコワ"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(2000)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        WAIT_FRAMES(1)
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
    END_LOOP
    CALL(evt_npc_set_position, STRING("ガンガン"), -75, 0, 90)
    CALL(evt_npc_set_ry, STRING("ガンガン"), 90)
    CALL(evt_cam3d_evt_off, 500, 11)
    RETURN
EVT_END()

/** Pogo's line (stg3_tou_255_01) with a camera move, then he walks off. */
EVT_BEGIN(evt_michel_9)
    CALL(evt_cam3d_evt_set, -45, 105, 288, -45, 60, -9, 2000, 11)
    CALL(evt_npc_move_position, STRING("ポグ"), 0, -80, 0, FLOAT(60.0f), 1)
    CALL(evt_msg_print, 0, STRING("stg3_tou_255_01"), 0, STRING("ポグ"))
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("ポグ"), 90, -90, 0, FLOAT(60.0f), 1)
        CALL(evt_npc_set_ry, STRING("ポグ"), 270)
    END_INLINE_EVENT
    RETURN
EVT_END()

/** Mail scene: Mario notices a notification (bubble, mail jingle, vibration) and the party reads stg3_tou_297_03. */
EVT_BEGIN(evt_mail_1)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_MAIL_RECEPTION2"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg3_tou_297_03"))
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION1"), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING("M_N_9"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_10"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_297_04"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg3_tou_297_05"))
    CALL(evt_pouch_receive_mail, 7)
    CALL(evt_pouch_open_mail, 7)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_00_MAJORS_8TH_PLACE)
    RETURN
EVT_END()

/** Mail scene: the same notification with message stg3_tou_297_22. */
EVT_BEGIN(evt_mail_2)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_MAIL_RECEPTION2"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg3_tou_297_22"))
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION1"), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING("M_N_9"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_10"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_297_23"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg3_tou_297_24"))
    CALL(evt_pouch_receive_mail, 9)
    CALL(evt_pouch_open_mail, 9)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
    RETURN
EVT_END()

/** Mario eats the Glitz Pit cake: partner warning, a yes/no prompt and the eating sequence. */
EVT_BEGIN(evt_eat_cake)
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
#if VERSION >= VERSION_JP
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_party_get_pos, 0, LW(3), LW(4), LW(5))
    CALL(evt_sub_get_dist, LW(0), LW(2), LW(3), LW(5), LW(10))
    IF_INT_GREATER(LW(10), 100)
        CALL(evt_party_set_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_party_set_dir_pos, 0, 20, -20)
    END_IF
#endif
    WAIT_MS(200)
    CALL(evt_msg_print_party, STRING("stg3_tou_296"))
    CALL(evt_msg_print, 0, STRING("stg3_tou_297"), 0, 0)
    CALL(evt_msg_select, 0, STRING("stg3_tou_297_yn"))
    CALL(evt_msg_continue)
    IF_INT_EQUAL(LW(0), 0)
#if VERSION >= VERSION_JP
        CALL(evt_party_flg_onoff, 0, 16777216, 1)
#endif
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        BEGIN_INLINE_EVENT
            SUBTRACT(LW(2), 30)
#if VERSION <= VERSION_DEMO_US
            CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(50.0f))
#else
            CALL(evt_mario_mov_pos2, LW(0), LW(2), FLOAT(80.0f))
#endif
            CALL(evt_mario_adjust_dir)
        END_INLINE_EVENT
#if VERSION <= VERSION_DEMO_US
        CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(50.0f))
#else
        CALL(evt_party_move_pos2, 0, LW(0), LW(2), FLOAT(80.0f))
#endif
        CALL(evt_msg_print_party, STRING("stg3_tou_299"))
        CALL(evt_msg_print, 0, STRING("stg3_tou_297_1"), 0, 0)
        CALL(evt_item_delete, STRING("cake"))
        CALL(evt_party_set_breed_pose, 0, 7)
        BEGIN_INLINE_EVENT_GET_ID(LW(0))
            LOOP(0)
                CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
                CALL(evt_snd_sfxon_3d, STRING("SFX_STG3_EAT_CAKE1"), LW(0), LW(1), LW(2), 0)
                WAIT_MS(500)
            END_LOOP
        END_INLINE_EVENT
        WAIT_MS(1000)
        DELETE_EVENT(LW(0))
        CALL(evt_pouch_mario_recovery)
        CALL(evt_pouch_all_party_recovery)
        SET_VALUE(GSWF(GSWF_TOU_CAKE_WAITING), 0)
#if VERSION >= VERSION_JP
        CALL(evt_party_flg_onoff, 0, 16777216, 0)
#endif
        CALL(evt_exit_case_evt)
    ELSE
        CALL(evt_msg_print_party, STRING("stg3_tou_298"))
    END_IF
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()

/** Map-init helper: places the cake item when Mario is ranked 6th and the cake event is not done yet. */
EVT_BEGIN(evt_cake_init)
    CALL(evt_tou_get_ranking, LW(0))
    IF_INT_EQUAL(LW(0), 6)
        IF_INT_EQUAL(GSWF(GSWF_TOU_CAKE_EVENT_DONE), 0)
            IF_INT_EQUAL(GSWF(GSWF_TOU_CAKE_WAITING), 0)
                CALL(evt_item_entry, STRING("cake"), ITEM_CAKE, 20, 25, -25, ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
#if VERSION >= VERSION_JP
                CALL(evt_item_status_on, STRING("cake"), ITEM_STATUS_NO_KOOPS)
#endif
            END_IF
        END_IF
    END_IF
    RETURN
EVT_END()

/**
 * Guess: cake scene; a camera move to the cake and the トゲノコエース NPC's announcement (stg3_tou_295),
 * then it waits for Mario.
 */
EVT_BEGIN(evt_cake)
    CALL(evt_run_case_evt, CASE_COND_FRONT_A, 1, STRING("a_cake"), 0, PTR(evt_eat_cake), 0)
    CALL(evt_cam3d_evt_set, 55, 102, 362, 55, 45, -9, 1000, 11)
    WAIT_MS(1100)
    CALL(evt_msg_print, 0, STRING("stg3_tou_295"), 0, STRING("トゲノコエース"))
    WAIT_MS(300)
    CALL(evt_cam3d_evt_off, 500, 11)
    SET_VALUE(GSWF(GSWF_TOU_CAKE_WAITING), 1)
    RETURN
EVT_END()

/**
 * Partner remark after Bowser's visit to the Glitz Pit (GSWF_TOU_BOWSER_RAID_DONE):
 * the party partner says stg3_tou_403_11.
 */
static EVT_BEGIN(evt_koopa_after)
    CALL(evt_msg_print_party, STRING("stg3_tou_403_11"))
    RETURN
EVT_END()

/** Mail scene: the same notification with message stg3_tou_297_25. */
EVT_BEGIN(evt_mail_3)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_MAIL_RECEPTION2"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg3_tou_297_25"))
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION1"), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING("M_N_9"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_10"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_297_26"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg3_tou_297_27"))
    CALL(evt_pouch_receive_mail, 10)
    CALL(evt_pouch_open_mail, 10)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_05_MAJORS_4TH_PL)
    RETURN
EVT_END()

/** Mail scene: the same notification, with its own message. */
EVT_BEGIN(evt_mail_4)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_MAIL_RECEPTION2"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION1"), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING("M_N_9"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_10"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_326_01"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg3_tou_326_02"))
    CALL(evt_pouch_receive_mail, 13)
    CALL(evt_pouch_open_mail, 13)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
    RETURN
EVT_END()

/** Mail scene: the same notification with message stg3_tou_307_05. */
EVT_BEGIN(evt_mail_5)
    WAIT_MS(1000)
    BEGIN_INLINE_EVENT_GET_ID(LW(11))
        CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
        CALL(evt_snd_sfxon_3d, STRING("SFX_VOICE_MARIO_FIND1_3"), LW(0), LW(1), LW(2), 0)
        CALL(evt_eff_fukidashi, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
        WAIT_MS(1500)
    END_INLINE_EVENT
    CALL(evt_snd_bgmoff, PSND_FADE_HOLD)
    CALL(evt_snd_bgmon, PSND_CH(1), STRING("BGM_FF_MAIL_RECEPTION2"))
    SPAWN_EVENT_GET_ID(PTR(evt_sub_mail_vibration), LW(10))
    WAIT_MS(500)
    CALL(evt_msg_print_party, STRING("stg3_tou_307_05"))
    LOOP(0)
        IS_EVENT_RUNNING(LW(11), LW(12))
        IF_INT_EQUAL(LW(12), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_bikkuri)
    LOOP(0)
        CALL(evt_key_get_buttontrg, 0, LW(0))
        IF_INT_EQUAL(LW(0), 256)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    CALL(evt_mario_balloon_off)
    CALL(evt_snd_bgmoff, PSND_FADE_OUT | PSND_CH(1))
    CALL(evt_snd_bgmon, PSND_FADE_RESUME | PSND_FADE_IN, 0)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION1"), LW(0), LW(1), LW(2), 0)
    DELETE_EVENT(LW(10))
    WAIT_FRAMES(1)
    CALL(evt_sub_rumble_onoff, 1, 0)
    CALL(evt_mario_set_pose, STRING("M_N_9"))
    WAIT_MS(500)
    CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
    CALL(evt_snd_sfxon_3d, STRING("SFX_MAIL_RECEPTION2"), LW(0), LW(1), LW(2), 0)
    CALL(evt_mario_set_pose, STRING("M_N_10"))
    WAIT_MS(500)
    CALL(evt_msg_print, 0, STRING("stg3_tou_307_06"), 0, 0)
    CALL(evt_mario_set_pose, STRING("M_S_1"))
    CALL(evt_msg_print_party, STRING("stg3_tou_307_07"))
    CALL(evt_pouch_receive_mail, 14)
    CALL(evt_pouch_open_mail, 14)
    CALL(evt_snd_bgmon, PSND_FADE_OUT, STRING("BGM_STG3_TOU1"))
    SET_VALUE(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_13_MAJORS_1ST_PL)
    RETURN
EVT_END()

/** Mini-Yoshi egg arrives: spawns the egg NPC near Mario and takes the Yoshi partner off the field. */
EVT_BEGIN(evt_tamago_hello)
    CALL(evt_npc_check, STRING("たまご"), LW(10))
    IF_INT_EQUAL(LW(10), 0)
        CALL(evt_npc_entry, STRING("たまご"), STRING("c_babyyoshi"))
    END_IF
    CALL(evt_npc_set_tribe, STRING("たまご"), STRING("たまご"))
    CALL(evt_npc_set_anim, STRING("たまご"), STRING("PYS_E_2"))
    CALL(evt_npc_set_position, STRING("たまご"), -30, 20, 30)
    CALL(evt_party_set_pos, 1, 0, -1000, 0)
    CALL(evt_party_stop, 1)
    CALL(evt_party_cont_onoff, 1, 0)
    RETURN
EVT_END()

/** Mini-Yoshi egg hops three times and then hatches back into the Yoshi partner. */
EVT_BEGIN(evt_tamago_hello2)
    LOOP(3)
        CALL(evt_npc_get_position, STRING("たまご"), LW(0), LW(1), LW(2))
        CALL(evt_sub_random, 200, LW(3))
        ADD(LW(3), 200)
        CALL(evt_sub_random, 20, LW(4))
        ADD(LW(4), 20)
        SPAWN_EVENT(evt_tamago_scale)
        CALL(evt_npc_jump_position_nohit, STRING("たまご"), LW(0), LW(1), LW(2), LW(3), LW(4))
    END_LOOP
    CALL(evt_npc_get_position, STRING("たまご"), LW(0), LW(1), LW(2))
    CALL(evt_npc_set_position, STRING("たまご"), 0, -1000, 0)
    CALL(evt_mario_get_exparty, LW(3))
    IF_INT_NOT_EQUAL(LW(3), 0)
        CALL(evt_party_set_pos, 1, LW(0), LW(1), LW(2))
    ELSE
        CALL(evt_mario_set_party_pos, 1, 8, LW(0), LW(1), LW(2))
    END_IF
    CALL(evt_party_run, 1)
    CALL(evt_party_cont_onoff, 1, 1)
    RETURN
EVT_END()

/** Prints the rank-change message after a match: champion, moved up, moved down or unchanged (stg3_rank_01 to 06). */
EVT_BEGIN(evt_tou_ranking_msg)
    CALL(evt_tou_get_ranking, LW(0))
    IF_INT_LESS(LW(0), GSW(GSW_TOU_RANK_BEFORE_MATCH))
        IF_INT_EQUAL(LW(0), 0)
            CALL(evt_msg_print_add, 0, STRING("stg3_rank_05"))
        ELSE
            CALL(evt_msg_print_add_insert, 0, STRING("stg3_rank_01"), LW(0))
        END_IF
        RETURN
    END_IF
    IF_INT_GREATER(LW(0), GSW(GSW_TOU_RANK_BEFORE_MATCH))
        CALL(evt_msg_print_add_insert, 0, STRING("stg3_rank_04"), LW(0))
        RETURN
    END_IF
    IF_INT_EQUAL(LW(0), 0)
        CALL(evt_msg_print_add, 0, STRING("stg3_rank_06"))
        RETURN
    END_IF
    CALL(evt_tou_get_fighter_rank, GSW(GSW_TOU_LAST_OPPONENT_ID), LW(1))
    IF_INT_LESS(LW(0), LW(1))
        CALL(evt_msg_print_add_insert, 0, STRING("stg3_rank_03"), LW(0))
    ELSE
        CALL(evt_msg_print_add_insert, 0, STRING("stg3_rank_02"), LW(0))
    END_IF
    RETURN
EVT_END()

/**
 * Script run after a match: story follow-ups (Yoshi egg, poison cake, Swoops joining),
 * ranking announcements and cleanup.
 */
EVT_BEGIN(evt_tou_match_after_default)
    SET_VALUE(LF(0), 0)
    IF_INT_EQUAL(GSW(GSW_TOU_OPPONENT_ID), 10)
        CALL(chk, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            SET_VALUE(LF(0), 1)
            CALL(evt_party_set_pos, 1, 0, -1000, 0)
            CALL(evt_party_stop, 1)
            CALL(evt_party_cont_onoff, 1, 0)
        END_IF
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_12_MINI_YOSHI_EGG)
        IF_INT_LESS(GSW(GSW_STORY_PROGRESS), STORY_STG3_20_MAJORS_10TH)
            IF_INT_EQUAL(LF(0), 0)
                CALL(chk, LW(0))
                IF_INT_EQUAL(LW(0), 0)
                    CALL_CHILD(evt_tamago_hello)
                END_IF
            END_IF
        END_IF
    END_IF
    IF_INT_EQUAL(GSWF(GSWF_TOU_POISON_CAKE_EVENT), 1)
        IF_INT_EQUAL(GSWF(GSWF_TOU_PARTNER_POISON_CURED), 0)
            IF_INT_EQUAL(GSWF(GSWF_TOU_PARTNER_POISONED), 0)
                CALL(evt_npc_flag_onoff, 0, STRING("ウラノコ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
                CALL(evt_npc_set_anim, STRING("ウラノコ"), STRING("NKT_K_2"))
            ELSE
                WAIT_MS(100)
            END_IF
        END_IF
    END_IF
    CALL(evt_tou_get_ranking, LW(0))
    IF_INT_EQUAL(LW(0), 11)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK11_SWOOPS_JOINS), 0)
            CALL(evt_npc_check, STRING("ガンガン"), LW(0))
            IF_INT_EQUAL(LW(0), 1)
                CALL(evt_npc_set_position, STRING("ガンガン"), 95, 0, 50)
            END_IF
        END_IF
    END_IF
    SET_VALUE(LF(0), 0)
    SET_VALUE(LF(1), 0)
    SET_VALUE(LF(2), 0)
    CALL(evt_sub_get_mapname, LW(0))
    IF_STR_EQUAL(LW(0), STRING("tou_10"))
        SET_VALUE(LF(0), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_08"))
        SET_VALUE(LF(1), 1)
    END_IF
    IF_STR_EQUAL(LW(0), STRING("tou_07"))
        SET_VALUE(LF(2), 1)
    END_IF
    CALL(evt_mario_key_onoff, 0)
    CALL(evt_party_stop, 0)
    CALL(evt_npc_flag_onoff, 1, STRING("キノシコワ"), NPC_FLAG_INTANGIBLE)
    IF_INT_EQUAL(LF(2), 1)
        CALL(evt_mario_set_pos, 65, 0, -95)
        CALL(evt_party_set_pos, 0, 95, 0, -105)
        CALL(evt_npc_set_position, STRING("キノシコワ"), 30, 0, -95)
        CALL(evt_cam3d_evt_set, 45, 91, 266, 45, 57, -11, 0, 11)
        CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("mario"))
        CALL(evt_mario_set_dir, 270, 0, 0)
        CALL(evt_party_set_dir, 0, 270, 0)
    ELSE
        CALL(evt_mario_set_pos, -90, 0, -95)
        CALL(evt_party_set_pos, 0, -120, 0, -105)
        CALL(evt_npc_set_position, STRING("キノシコワ"), -55, 0, -95)
        CALL(evt_cam3d_evt_set, -75, 91, 266, -75, 57, -11, 0, 11)
        CALL(evt_set_dir_to_target, STRING("キノシコワ"), STRING("mario"))
        CALL(evt_mario_set_dir, 90, 0, 0)
        CALL(evt_party_set_dir, 0, 90, 0)
    END_IF
    CALL(evt_seq_wait, 2)
    CALL(octo_stop)
    WAIT_MS(1000)
    CALL(evt_tou_get_ranking, LW(0))
    IF_INT_EQUAL(GSWF(GSWF_TOU_LAST_MATCH_WON), 1)
        CALL(fight_money, LW(0), 1, LW(10))
    ELSE
        CALL(fight_money, LW(0), 0, LW(10))
    END_IF
    SET_VALUE(LF(10), 0)
    SET_VALUE(LF(11), 0)
    SET_VALUE(LF(12), 0)
    SET_VALUE(LF(13), 0)
    IF_INT_EQUAL(LF(0), 1)
        IF_INT_LESS(GSW(GSW_TOU_RANK_BEFORE_MATCH), 11)
            CALL(evt_msg_print, 0, STRING("stg3_tou_114_00"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("A_1"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            ADD(LW(0), 20)
            ADD(LW(1), 20)
            CALL(evt_item_entry, STRING("fmoney"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_item_delete, STRING("fmoney"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION >= VERSION_US
            CALL(evt_sub_get_language, LW(15))
            SWITCH(LW(15))
                CASE_EQUAL(0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_114_01"), 0, STRING("キノシコワ"), LW(10))
                CASE_DEFAULT
                CALL(evt_msg_fmt_int, 0, LW(14), STRING("stg3_tou_114_01"), LW(10))
                CALL(evt_msg_print, 1, LW(14), 0, STRING("キノシコワ"))
            END_SWITCH
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_114_01"), 0, STRING("キノシコワ"), LW(10))
#endif
            CALL_CHILD(evt_tou_ranking_msg)
            CALL(evt_pouch_add_coin, LW(10))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg3_tou_114_02"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
            WAIT_MS(600)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
            SET_VALUE(LF(10), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg3_tou_179_00"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("A_1"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            ADD(LW(0), 20)
            ADD(LW(1), 20)
            CALL(evt_item_entry, STRING("fmoney"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_item_delete, STRING("fmoney"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION >= VERSION_US
            CALL(evt_sub_get_language, LW(15))
            SWITCH(LW(15))
                CASE_EQUAL(0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_179_01"), 0, STRING("キノシコワ"), LW(10))
                CASE_DEFAULT
                CALL(evt_msg_fmt_int, 0, LW(14), STRING("stg3_tou_179_01"), LW(10))
                CALL(evt_msg_print, 1, LW(14), 0, STRING("キノシコワ"))
            END_SWITCH
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_179_01"), 0, STRING("キノシコワ"), LW(10))
#endif
            CALL_CHILD(evt_tou_ranking_msg)
            CALL(evt_pouch_add_coin, LW(10))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg3_tou_179_02"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
            WAIT_MS(600)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
        END_IF
    END_IF
    IF_INT_EQUAL(LF(1), 1)
        SWITCH(GSW(GSW_TOU_RANK_BEFORE_MATCH))
            CASE_LESS(1)
            CALL(evt_msg_print, 0, STRING("stg3_tou_365_00"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("A_1"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            ADD(LW(0), 20)
            ADD(LW(1), 20)
            CALL(evt_item_entry, STRING("fmoney"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_item_delete, STRING("fmoney"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION >= VERSION_US
            CALL(evt_sub_get_language, LW(15))
            SWITCH(LW(15))
                CASE_EQUAL(0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_365_01"), 0, STRING("キノシコワ"), LW(10))
                CASE_DEFAULT
                CALL(evt_msg_fmt_int, 0, LW(14), STRING("stg3_tou_365_01"), LW(10))
                CALL(evt_msg_print, 1, LW(14), 0, STRING("キノシコワ"))
            END_SWITCH
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_365_01"), 0, STRING("キノシコワ"), LW(10))
#endif
            CALL_CHILD(evt_tou_ranking_msg)
            CALL(evt_pouch_add_coin, LW(10))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg3_tou_365_02"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
            WAIT_MS(600)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
            SET_VALUE(LF(11), 1)
            SET_VALUE(GSWF(GSWF_TOU_REMATCH_MAJORS_LEFT), 0)
            CASE_GREATER(10)
            CALL(evt_msg_print, 0, STRING("stg3_tou_365_03_00"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("A_1"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            ADD(LW(0), 20)
            ADD(LW(1), 20)
            CALL(evt_item_entry, STRING("fmoney"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_item_delete, STRING("fmoney"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION >= VERSION_US
            CALL(evt_sub_get_language, LW(15))
            SWITCH(LW(15))
                CASE_EQUAL(0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_365_03_01"), 0, STRING("キノシコワ"), LW(10))
                CASE_DEFAULT
                CALL(evt_msg_fmt_int, 0, LW(14), STRING("stg3_tou_365_03_01"), LW(10))
                CALL(evt_msg_print, 1, LW(14), 0, STRING("キノシコワ"))
            END_SWITCH
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_365_03_01"), 0, STRING("キノシコワ"), LW(10))
#endif
            CALL_CHILD(evt_tou_ranking_msg)
            CALL(evt_pouch_add_coin, LW(10))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg3_tou_365_03_02"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
            WAIT_MS(600)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
            SET_VALUE(LF(12), 1)
            CASE_DEFAULT
            CALL(evt_msg_print, 0, STRING("stg3_tou_180_00"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("A_1"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            ADD(LW(0), 20)
            ADD(LW(1), 20)
            CALL(evt_item_entry, STRING("fmoney"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_item_delete, STRING("fmoney"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION >= VERSION_US
            CALL(evt_sub_get_language, LW(15))
            SWITCH(LW(15))
                CASE_EQUAL(0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_180_01"), 0, STRING("キノシコワ"), LW(10))
                CASE_DEFAULT
                CALL(evt_msg_fmt_int, 0, LW(14), STRING("stg3_tou_180_01"), LW(10))
                CALL(evt_msg_print, 1, LW(14), 0, STRING("キノシコワ"))
            END_SWITCH
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_180_01"), 0, STRING("キノシコワ"), LW(10))
#endif
            CALL_CHILD(evt_tou_ranking_msg)
            CALL(evt_pouch_add_coin, LW(10))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg3_tou_180_02"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
            WAIT_MS(600)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
        END_SWITCH
    END_IF
    IF_INT_EQUAL(LF(2), 1)
        IF_INT_GREATER(GSW(GSW_TOU_RANK_BEFORE_MATCH), 0)
            CALL(evt_msg_print, 0, STRING("stg3_tou_365_04_00"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("A_1"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 20)
            ADD(LW(1), 20)
            CALL(evt_item_entry, STRING("fmoney"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_item_delete, STRING("fmoney"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION >= VERSION_US
            CALL(evt_sub_get_language, LW(15))
            SWITCH(LW(15))
                CASE_EQUAL(0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_365_04_01"), 0, STRING("キノシコワ"), LW(10))
                CASE_DEFAULT
                CALL(evt_msg_fmt_int, 0, LW(14), STRING("stg3_tou_365_04_01"), LW(10))
                CALL(evt_msg_print, 1, LW(14), 0, STRING("キノシコワ"))
            END_SWITCH
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_365_04_01"), 0, STRING("キノシコワ"), LW(10))
#endif
            CALL_CHILD(evt_tou_ranking_msg)
            CALL(evt_pouch_add_coin, LW(10))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg3_tou_365_04_02"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
            WAIT_MS(600)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
            SET_VALUE(LF(13), 1)
        ELSE
            CALL(evt_msg_print, 0, STRING("stg3_tou_181_00"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("A_1"))
            WAIT_MS(300)
            CALL(evt_mario_get_pos, 0, LW(0), LW(1), LW(2))
            SUBTRACT(LW(0), 20)
            ADD(LW(1), 20)
            CALL(evt_item_entry, STRING("fmoney"), ITEM_COIN, LW(0), LW(1), LW(2), ITEM_ENTRY_FIXED_NO_TOUCH, -1, 0)
            CALL(evt_mario_set_pose, STRING("M_C_3"))
            WAIT_MS(1000)
            CALL(evt_item_delete, STRING("fmoney"))
            CALL(evt_mario_set_pose, STRING("M_S_1"))
#if VERSION >= VERSION_US
            CALL(evt_sub_get_language, LW(15))
            SWITCH(LW(15))
                CASE_EQUAL(0)
                CALL(evt_msg_print_insert, 0, STRING("stg3_tou_181_01"), 0, STRING("キノシコワ"), LW(10))
                CASE_DEFAULT
                CALL(evt_msg_fmt_int, 0, LW(14), STRING("stg3_tou_181_01"), LW(10))
                CALL(evt_msg_print, 1, LW(14), 0, STRING("キノシコワ"))
            END_SWITCH
#else
            CALL(evt_msg_print_insert, 0, STRING("stg3_tou_181_01"), 0, STRING("キノシコワ"), LW(10))
#endif
            CALL_CHILD(evt_tou_ranking_msg)
            CALL(evt_pouch_add_coin, LW(10))
            WAIT_MS(300)
            CALL(evt_msg_print, 0, STRING("stg3_tou_181_02"), 0, STRING("キノシコワ"))
            WAIT_MS(300)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("M_1"))
            WAIT_MS(600)
            CALL(evt_npc_set_anim, STRING("キノシコワ"), STRING("S_1"))
        END_IF
    END_IF
    CALL(evt_npc_status_onoff, 1, STRING("キノシコワ"), 2)
    CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -130, 0, FLOAT(80.0f), 1)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_open_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 0, 180, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(1), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    BEGIN_INLINE_EVENT
        CALL(evt_npc_move_position, STRING("キノシコワ"), 0, -200, 0, FLOAT(80.0f), 1)
        CALL(evt_npc_set_position, STRING("キノシコワ"), 0, -1000, 0)
    END_INLINE_EVENT
    WAIT_MS(800)
    SET_VALUE(LW(1), 0)
    SPAWN_EVENT(bero_close_door_play_se)
    CALL(evt_sub_intpl_msec_init, 11, 180, 0, 500)
    LOOP(0)
        CALL(evt_sub_intpl_msec_get_value)
        MULTIPLY_FLOAT(LW(0), FLOAT(0.44433594f))
        IF_INT_EQUAL(LF(0), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(1), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LF(2), 1)
            CALL(evt_mapobj_rotate, 1, STRING("door_1"), 0, LW(0), 0)
        END_IF
        IF_INT_EQUAL(LW(1), 0)
            BREAK_LOOP
        END_IF
        WAIT_FRAMES(1)
    END_LOOP
    IF_INT_EQUAL(GSWF(GSWF_TOU_POISON_CAKE_EVENT), 1)
        IF_INT_EQUAL(GSWF(GSWF_TOU_PARTNER_POISON_CURED), 0)
            IF_INT_EQUAL(GSWF(GSWF_TOU_PARTNER_POISONED), 1)
                CALL(evt_mario_set_dir, 270, 300, 0)
                CALL(evt_party_stop, 0)
                WAIT_MS(300)
                IF_INT_EQUAL(GSWF(GSWF_TOU_LAST_MATCH_WON), 1)
                    CALL(evt_msg_print_party, STRING("stg3_tou_306"))
                ELSE
                    CALL(evt_msg_print_party, STRING("stg3_tou_307"))
                END_IF
                CALL(evt_pouch_party_join, 1)
                CALL(evt_pouch_party_join, 2)
                CALL(evt_pouch_party_join, 5)
                CALL(evt_pouch_party_join, 4)
                CALL(evt_party_run, 0)
            ELSE
                CALL(evt_npc_flag_onoff, 0, STRING("ウラノコ"), NPC_FLAG_MOVE_ANIM | NPC_FLAG_TALK_ANIM)
                CALL(evt_npc_set_anim, STRING("ウラノコ"), STRING("NKT_K_2"))
                CALL(evt_mario_set_dir, 270, 300, 0)
                CALL(evt_party_stop, 0)
                WAIT_MS(300)
                CALL(evt_msg_print_party, STRING("stg3_tou_307_01"))
                CALL(evt_npc_get_position, STRING("ウラノコ"), LW(0), LW(1), LW(2))
                CALL(evt_cam3d_evt_set, LW(0), 90, 283, LW(0), 45, -9, 1000, 11)
                BEGIN_INLINE_EVENT
                    CALL(evt_mario_set_dir_npc, STRING("ウラノコ"))
                END_INLINE_EVENT
                BEGIN_INLINE_EVENT
                    CALL(evt_party_set_dir_npc, 0, STRING("ウラノコ"))
                END_INLINE_EVENT
                WAIT_MS(1000)
                CALL(evt_msg_print, 0, STRING("stg3_tou_307_02"), 0, STRING("ウラノコ"))
                CALL(evt_npc_change_interrupt, STRING("ウラノコ"), 6, PTR(evt_talk_doku_cake))
                CALL(evt_cam3d_evt_set, -75, 91, 266, -75, 57, -11, 500, 11)
                CALL(evt_mario_set_dir, 270, 300, 0)
                CALL(evt_party_set_dir, 0, 90, 300)
                WAIT_MS(500)
                CALL(evt_msg_print_party, STRING("stg3_tou_307_03"))
                CALL(evt_party_run, 0)
            END_IF
            SET_VALUE(GSWF(GSWF_TOU_PARTNER_POISON_CURED), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(10), 1)
        CALL(evt_mario_set_dir, 270, 300, 0)
        CALL(evt_msg_print_party, STRING("stg3_tou_114"))
        IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_34_RETURN_TO_ROGUEPORT)
            SET_VALUE(GSWF(GSWF_TOU_REMATCH_MAJORS_LEFT), 1)
        END_IF
    END_IF
    IF_INT_EQUAL(LF(11), 1)
        CALL(evt_mario_set_dir, 270, 300, 0)
        CALL(evt_msg_print_party, STRING("stg3_tou_365"))
        CALL(evt_pouch_remove_item, ITEM_CHAMPS_BELT, LW(0))
    END_IF
    IF_INT_EQUAL(LF(12), 1)
        CALL(evt_mario_set_dir, 270, 300, 0)
        CALL(evt_msg_print_party, STRING("stg3_tou_365_03_03"))
    END_IF
    IF_INT_EQUAL(LF(13), 1)
        CALL(evt_mario_set_dir, 270, 300, 0)
        CALL(evt_msg_print_party, STRING("stg3_tou_365_04_03"))
        CALL(evt_pouch_add_item, ITEM_CHAMPS_BELT, LW(0))
    END_IF
    SET_VALUE(LF(0), 0)
    IF_INT_EQUAL(GSW(GSW_TOU_OPPONENT_ID), 10)
        CALL(chk, LW(0))
        IF_INT_EQUAL(LW(0), 0)
            IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_12_MINI_YOSHI_EGG)
                CALL_CHILD(evt_tou_chibi_yoshi)
            ELSE
                CALL_CHILD(evt_michel_9)
            END_IF
            SET_VALUE(LF(0), 1)
        END_IF
    END_IF
    IF_INT_GREATER_OR_EQUAL(GSW(GSW_STORY_PROGRESS), STORY_STG3_12_MINI_YOSHI_EGG)
        IF_INT_EQUAL(LF(0), 0)
            CALL(chk, LW(0))
            IF_INT_EQUAL(LW(0), 0)
                CALL_CHILD(evt_tamago_hello2)
            END_IF
        END_IF
    END_IF
    CALL_CHILD(evt_cake_init)
    CALL(evt_cam3d_evt_off, 500, 11)
    WAIT_MS(500)
    CALL(evt_tou_get_ranking, LW(0))
    SWITCH(LW(0))
        CASE_EQUAL(18)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK18_SCENE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK18_SCENE), 1)
            CALL_CHILD(evt_michel_2)
        END_IF
        CASE_EQUAL(17)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK17_SCENE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK17_SCENE), 1)
            CALL_CHILD(evt_michel_3)
        END_IF
        CASE_EQUAL(16)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK16_SCENE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK16_SCENE), 1)
            CALL_CHILD(evt_michel_4)
        END_IF
        CASE_EQUAL(15)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK15_SCENE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK15_SCENE), 1)
            CALL_CHILD(evt_michel_5)
        END_IF
        CASE_EQUAL(14)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK14_SCENE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK14_SCENE), 1)
            CALL_CHILD(evt_michel_6)
        END_IF
        CASE_EQUAL(13)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK13_SCENE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK13_SCENE), 1)
            CALL_CHILD(evt_michel_7)
        END_IF
        CASE_EQUAL(12)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK12_KING_K_GONE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK12_KING_K_GONE), 1)
            CALL(evt_npc_set_position, STRING("マイケル"), 0, -1000, 0)
            CALL(evt_rankingReInit)
        END_IF
        CASE_EQUAL(11)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK11_SWOOPS_JOINS), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK11_SWOOPS_JOINS), 1)
            CALL_CHILD(evt_michel_8)
            CALL(evt_rankingReInit)
        END_IF
        CASE_EQUAL(10)
        CASE_EQUAL(9)
        CASE_EQUAL(8)
        IF_INT_EQUAL(GSWF(GSWF_TOU_MAIL1_RECEIVED), 0)
            SET_VALUE(GSWF(GSWF_TOU_MAIL1_RECEIVED), 1)
            CALL_CHILD(evt_mail_1)
        END_IF
        CASE_EQUAL(7)
        IF_INT_EQUAL(GSWF(GSWF_TOU_MAIL2_RECEIVED), 0)
            SET_VALUE(GSWF(GSWF_TOU_MAIL2_RECEIVED), 1)
            CALL_CHILD(evt_mail_2)
        END_IF
        CASE_EQUAL(6)
        IF_INT_EQUAL(GSWF(GSWF_TOU_CAKE_EVENT_DONE), 0)
            SET_VALUE(GSWF(GSWF_TOU_CAKE_EVENT_DONE), 1)
            CALL_CHILD(evt_cake)
        END_IF
        CASE_EQUAL(5)
        IF_INT_EQUAL(GSWF(GSWF_TOU_BOWSER_RAID_DONE), 0)
            SET_VALUE(GSWF(GSWF_TOU_BOWSER_RAID_DONE), 1)
            CALL_CHILD(evt_koopa_after)
        END_IF
        IF_INT_EQUAL(GSWF(GSWF_TOU_CAKE_WAITING), 1)
            CALL_CHILD(evt_tou_08_cake)
        END_IF
        CASE_EQUAL(4)
        IF_INT_EQUAL(GSWF(GSWF_TOU_MAIL3_RECEIVED), 0)
            SET_VALUE(GSWF(GSWF_TOU_MAIL3_RECEIVED), 1)
            CALL_CHILD(evt_mail_3)
        END_IF
        CASE_EQUAL(3)
        IF_INT_EQUAL(GSWF(GSWF_TOU_MAIL4_RECEIVED), 0)
            SET_VALUE(GSWF(GSWF_TOU_MAIL4_RECEIVED), 1)
            CALL_CHILD(evt_mail_4)
#if VERSION >= VERSION_JP
            CALL(evt_rankingReInit)
#endif
        END_IF
        CASE_EQUAL(2)
        CASE_EQUAL(1)
        IF_INT_EQUAL(GSWF(GSWF_TOU_RANK1_SCENE), 0)
            SET_VALUE(GSWF(GSWF_TOU_RANK1_SCENE), 1)
            CALL_CHILD(evt_mail_5)
        END_IF
    END_SWITCH
    CALL(octo_start)
    CALL(evt_party_run, 0)
    CALL(evt_mario_key_onoff, 1)
    RETURN
EVT_END()
