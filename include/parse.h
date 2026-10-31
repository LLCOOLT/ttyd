// parse.c: the text data parser for nested tagged blocks (ParseWork, parsePush/parsePop, parseTagGet1).
#pragma once

#include <dolphin/types.h>

// The type argument of parseGet1Next and parseTagGet1: what is read and what data points to.
enum ParseValueType {
    PARSE_STRING = 0, // a quoted string, copied without the quotes (char*)
    PARSE_INT = 1,    // a decimal integer (s32*)
    PARSE_FLOAT = 2,  // a float (f32*)
    PARSE_VEC = 3,    // three floats (Vec*)
};

typedef struct ParseWork {
    char* ptr;   // 0x0
    s32 pos[10]; // 0x4
    s32 end[10]; // 0x2C
    s32 depth;   // 0x54
} ParseWork;

void parseInit(void* ptr, u32 size);
BOOL parsePush(const char* tag);
void parsePop(void);
void parsePopNext(void);
BOOL parseGet1Next(s32 type, void* data);
BOOL parseTagGet1(const char* tag, s32 type, void* data);
