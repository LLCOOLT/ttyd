// msgdrv.c: the message driver (MsgChar, MsgGlyphCode): message lookup by tag, markup parsing and speech windows.
#pragma once

#include <dolphin/os.h>
#include "driver/windowdrv.h"
#include "memory.h"
#include "version.h"

// MsgChar.value of a letter entry: the text effects of the tags around it
enum MsgCharFlags {
    MSG_CHAR_DYNAMIC = 0x1,    // <dynamic>: the letter grows into place (rot holds its current scale)
    MSG_CHAR_SHAKE = 0x2,      // <shake>
    MSG_CHAR_WAVE = 0x4,       // <wave>
    MSG_CHAR_OPTION_0 = 0x100, // <select> lists: the letter belongs to option n (MSG_CHAR_OPTION_0 << n)
    MSG_CHAR_OPTIONS = 0xFF00,
    MSG_CHAR_SCALE_X = 0x10000, // US <scaleX>: the letter is stretched on x only
};

// MsgChar.glyph values above the font's glyphs: control entries made from the message tags
enum MsgGlyphCode {
    MSG_GLYPH_PAPER_END = 0xFFF2, // </paper>
    MSG_GLYPH_PAPER = 0xFFF3,     // <paper>: the speaker's paper pose (npc)
    MSG_GLYPH_ANIM = 0xFFF4,      // <anim>
    MSG_GLYPH_DKEY = 0xFFF5,      // <dkey> and </dkey>
    MSG_GLYPH_NOISE = 0xFFF6,     // <noise> and </noise>
    MSG_GLYPH_COLOR = 0xFFF7,     // <col>, </col>, <system>, <tec> (value holds the colour)
    MSG_GLYPH_ICON = 0xFFF8,      // <icon>
    MSG_GLYPH_VOL = 0xFFF9,       // <vol>
    MSG_GLYPH_SE = 0xFFFA,        // <se>
    MSG_GLYPH_NEWLINE = 0xFFFB,   // a line break
    MSG_GLYPH_ONCE_STOP = 0xFFFC, // <o>, <once_stop>
    MSG_GLYPH_SCROLL = 0xFFFD,    // <p>, <scrl_auto>: scroll by y
    MSG_GLYPH_KEY = 0xFFFE,       // <k>, <key>: wait for a button (x holds the page)
    MSG_GLYPH_END = 0xFFFF,       // the end of the message
};

typedef struct MsgChar {
    union {
        u32 value;            // 0x0, letters: MsgCharFlags
        GXColor color;        // 0x0, colour-change entries
        struct NpcEntry* npc; // 0x0, paper entries (NULL = the speaker)
    };
    u16 glyph; // 0x4, a font glyph or a MsgGlyphCode
    s16 x;     // 0x6 (page-break entries: page number)
    s16 y;     // 0x8 (page-scroll entries: scroll amount)
    s16 iconY; // 0xA, icon entries: extra y offset
    u32 time;  // 0xC
    f32 scale; // 0x10
    f32 rot;   // 0x14, animation entries: rotation; dynamic-scale entries: current scale
} MsgChar;

typedef struct MsgWinData {
    const char* tag;        // 0x0
    u32 flags;              // 0x4
    u16 curPage;            // 0x8, page being shown (page-break entries carry their page number)
    u16 pageState;          // 0xA, 1: waiting for the key, 2: advance to the next page
    u16 pageAdvanced;       // 0xC
    u8 pad_0E[0x10 - 0xE];  // 0xE
    s32 nextEntry;          // 0x10, index into entries
    u8 pad_14[0x18 - 0x14]; // 0x14
    OSTime openTime;        // 0x18, time base for the wave and selected-option character wobble (msgDisp); reset when the window opens or pages
    s32 playTime;           // 0x20, playback clock (ms) compared with entries[].time
    s32 scrollTarget;       // 0x24
    s32 scrollPos;          // 0x28, eases toward scrollTarget
    u8 pad_2C[0x30 - 0x2C]; // 0x2C
    OSTime lastUpdateTime;  // 0x30, reset every msgMain; the delta advances the scroll
    s32 charCount;          // 0x38, MsgChar entries in use
#if VERSION >= VERSION_US
    MsgChar entries[0xA00]; // 0x3C (US: twice as many, so every field below moves by 0x7800)
#else
    MsgChar entries[0x500]; // 0x3C
#endif
    s32 page;                         // 0x783C
    s32 pageCount;                    // 0x7840, number of pageY entries
    s32 pageY[(0x79FC - 0x7844) / 4]; // 0x7844
    s32 callback;                     // 0x79FC, void (*)(s32 event, smartEntry*), see MSG_CB
    struct EventEntry* event;         // 0x7A00 (US 0xF200), event that opened the window; read by map msg callbacks
    char speakerName[0x20];           // 0x7A04, speaker NPC name, passed to npcNameToPtr (SPM npcName)
    s32 unitId;                       // 0x7A24
    s32 talkSfxGroup;                 // 0x7A28, <se n> tag value (0xFFFA entry); not read in C
    u8 talkVolume;                    // 0x7A2C, default 0x7F
    u8 pad_7A2D[0x7A30 - 0x7A2D];     // 0x7A2D
    s32 parseTime;                    // 0x7A30, msgAnalize state
    s16 parseX;                       // 0x7A34
    s16 parseY;                       // 0x7A36
    s16 parsePage;                    // 0x7A38, msgAnalize: key-wait counter stored in 0xFFFE entries' x
    s16 parseScroll;                  // 0x7A3A, msgAnalize: pending scroll stored in 0xFFFD entries' y
    s32 parseSpeed;                   // 0x7A3C, text speed (default 25)
    s8 numSel;                        // 0x7A40
    s8 defSel;                        // 0x7A41
    s8 cancel;                        // 0x7A42
    s8 sel;                           // 0x7A43
    s16 selWidth;                     // 0x7A44
    s16 selY;                         // 0x7A46
    f32 cursorY;                      // 0x7A48
    WindowEntry* window;              // 0x7A4C
    s32 talkTimer;                    // 0x7A50, frames until the talk pose is set
    s32 talkPoseSet;                  // 0x7A54
} MsgWinData;

// MsgWinData.flags
#define MSG_WIN_FLAG_OPEN 0x1        // set when the window is created (msgWindow_Entry); no reader in C
#define MSG_WIN_FLAG_FIRST_FRAME 0x2 // msgMain's first update: run the callback with event 0, then clear
#define MSG_WIN_FLAG_FAST 0x4        // A or B held to speed the text up (cleared at each key wait)
#define MSG_WIN_FLAG_BATTLE_UNIT 0x8 // the speaker is the battle unit unitId (else the NPC speakerName)
#define MSG_WIN_FLAG_SMALL 0x10      // <small>: no speed-up; US: tighter line spacing
#define MSG_WIN_FLAG_SELECT 0x20     // <select>: the text ends in a choice (numSel options)
#define MSG_WIN_FLAG_PAGE_BACK 0x40  // showing an earlier page (Z pressed at a key wait)
#define MSG_WIN_FLAG_NO_FAST 0x80    // <dkey>: speed-up disabled until <dkey 0>
#define MSG_WIN_FLAG_KEY_X 0x100     // <keyxon>: X also advances the text
#define MSG_WIN_FLAG_NO_PAGES 0x200  // small windows (type 1) keep no page list

typedef struct MessageEntry {
    u32 length; // 0x0
#if VERSION == VERSION_DEMO
    smartEntry* address; // 0x4, the demo keeps the text in a smart heap block
#else
    void* address; // 0x4
#endif
    s32 count;          // 0x8
    smartEntry* lookup; // 0xC
} MessageEntry;

typedef struct MessageWork {
    MessageEntry entries[2]; // 0x0
    s32 poseId;              // 0x20
} MessageWork;

void msgInit(void);
void msgLoad(const char* filename, s32 index);
void msgAnalize(smartEntry* smart, const char* msg);

MessageWork* L_msgGetWork(void);

const char* msgSearch(const char* tag);
BOOL _ismbblead(u32 c);

const char* msgGetCommand(const char* msg, char* cmd, char* arg);
s32 msgIconStr2ID(const char* str);

extern const char R_no_messages_JP[];
extern const char R_no_messages_US[];

extern const char R_no_messages_DE[];
extern const char R_no_messages_DU[];
extern const char R_no_messages_ES[];
extern const char R_no_messages_FR[];
extern const char R_no_messages_IT[];

void msgWindow_Continue(s32 id);
void msgWindow_Repeat(s32 id);
void msgWindow_Add(const char* msg, s32 id);
s32 msgWindow_Entry(const char* msg, s32 callback, u16 priority);
void msgWindow_ForceClose(const char* name);
