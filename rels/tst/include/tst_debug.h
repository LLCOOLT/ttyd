#pragma once

#include "dolphin/types.h"

// system.c's assert handler; tst's units call it directly, with their source file name and line.
BOOL __assert2(const char* filename, s32 line, const char* assertion, const char* message, ...);
