// error_handler.c: installs the OS error handler (setupErrorHandler, N_setupErrorHandler) that reports crashes.
#pragma once

#include <dolphin/types.h>

void setupErrorHandler(void);

void N_setupErrorHandler(void);
