#include "musyx/txwin.h"
#include "dolphin/gx.h"
#include "dolphin/os.h"
#include "musyx/assert.h"

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

/* DEMO library functions, declared here instead of through the DEMO headers. */
extern GXRenderModeObj* DEMOGetRenderModeObj();
extern void DEMOPrintf(s16, s16, s16, char*, ...);

static void __win_log_refresh(sWIN* handle);
static void __win_add_node(sWIN* handle);
static void __win_delete_node(sWIN* handle);

static unsigned short __X_Res = 0;
static unsigned short __Y_Res = 0;
/** Render mode of the display, fetched from the DEMO library in winInit. */
GXRenderModeObj* __rmp = NULL;
/** The text window most recently made current; set when the first window is added, cleared by winInit. */
sWIN* __CurrNode = NULL;
/** Last window of the linked list of text windows; new windows are appended after it. */
sWIN* __LastNode = NULL;  // size: 0x4
/** First window of the linked list of text windows; winRefresh walks the list from here. */
sWIN* __FirstNode = NULL; // size: 0x4

/** Initializes the text window system (a debug overlay drawn with the DEMO library): empties the window list, sets the
 * 8 pixel font and fetches the render mode. */
void winInit() {
  __FirstNode = NULL;
  __LastNode = NULL;
  __CurrNode = NULL;
  winSetFontSize(8);
  __rmp = DEMOGetRenderModeObj();
  GXSetCopyClear((GXColor){0x0A, 0x10, 0x19, 0xFF}, 0xFFFFFF);
}

/** Creates a text window with the given pixel rectangle, caption and refresh function and adds it to the window list;
 * the character grid is 8x8 pixels per cell. */
sWIN* winOpenWindow(s32 x1, s32 y1, s32 x2, s32 y2, char* caption, void* func, u32 flags) {
  sWIN* handle; // r31
#line 109
  MUSY_ASSERT_MSG(x1 < x2, "TXWIN: Illegal X coords for window\n");
  MUSY_ASSERT_MSG(y1 < y2, "TXWIN: Illegal y coords for window\n");

  handle = OSAlloc(sizeof(sWIN));

  MUSY_ASSERT_MSG(handle != NULL, "TXWIN: FAILED TO ALLOCATE WINDOW!\n");
  __win_add_node(handle);
  handle->x1 = x1;
  handle->y1 = y1;
  handle->x2 = x2;
  handle->y2 = y2;
  handle->pixel_width = (x2 - x1) + 1;
  handle->pixel_height = (y2 - y1) + 1;
  handle->curr_x = 0;
  handle->curr_y = 0;
  handle->caption = caption;
  handle->char_width = handle->pixel_width / 8;
  handle->char_height = handle->pixel_height / 8;
  handle->refresh = func;
  handle->flags = flags;
  return handle;
}

/** Creates a scrolling log window, which also keeps num_lines extra lines of history, with its own line buffers. */
sWIN* winOpenLogWindow(s32 x1, s32 y1, s32 x2, s32 y2, char* caption, u16 num_lines, u32 flags) {
  sWIN* handle; // r31
  u16 i;        // r30

  handle = winOpenWindow(x1, y1, x2, y2, caption, NULL, 0);
  handle->refresh = __win_log_refresh;
  handle->flags = 1;
  handle->curr_output_line = 0;
  handle->curr_view_line = 0;
  handle->total_lines = (u16)handle->char_height + num_lines;
  handle->buffer = OSAlloc(handle->total_lines * 4);
#line 192

  MUSY_ASSERT_MSG(handle->buffer != NULL, "TXWIN: Unable to allocate log window buffer.\n");

  for (i = 0; i < handle->total_lines; ++i) {

    handle->buffer[i] = OSAlloc(handle->char_width + 1);

    memset(handle->buffer[i], 0, handle->char_width + 1);

    MUSY_ASSERT_MSG(handle->buffer[i] != NULL, "TXWIN: Failed to allocate buffer element\n");
  }

  return handle;
}

/** Formats text and draws it at character cell (char_x, char_y) inside the window, cut to the window width. */
void winPrintfXY(sWIN* handle, s16 char_x, s16 char_y, char* fmt, ...) {
  va_list args;
  char buffer[128];
  s16 x;
  s16 y;

  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  if (strlen(buffer) > (u32)handle->char_width) {
    buffer[handle->char_width] = '\0';
  }
  x = handle->x1 + (char_x * 8);
  y = handle->y1 + (char_y * 8);
  DEMOPrintf(x, y, 0, "%s", buffer);
}

/** Formats a line, cuts it to the window width and appends it to the log window's circular line buffer. */
void winLogPrintf(sWIN* handle, char* fmt, ...) {
  va_list args;
  char buffer[128];
  va_start(args, fmt);
  vsprintf(buffer, fmt, args);
  va_end(args);

  if (strlen(buffer) > (u32)handle->char_width) {
    buffer[handle->char_width] = '\0';
  }

  strcpy(handle->buffer[handle->curr_output_line], buffer);
  handle->curr_output_line = (handle->curr_output_line + 1) % handle->total_lines;
}

/** Empties all lines of a log window and resets its output and view positions. */
void winClearLogWindow(sWIN* handle) {
  u16 i;
  for (i = 0; i < handle->total_lines; ++i) {
    memset(handle->buffer[i], 0, handle->char_width + 1);
  }

  handle->curr_output_line = 0;
  handle->curr_view_line = 0;
}

/** Sets the overlay resolution for a font size between 8 and 40 (smaller values give a larger screen area); other sizes
 * give 640x480. */
void winSetFontSize(u16 size) {

  if (size >= 8 && size <= 40) {

    __X_Res = (8.0 / (float)size) * 640.0;

    __Y_Res = (float)__X_Res * 0.75;
  } else {

    __X_Res = 640;

    __Y_Res = 480;
  }
}

/** Draws every open window by calling its refresh function (asserts the list is not empty). */
void winRefresh() {
  sWIN* ptr;
#line 338
  MUSY_ASSERT_MSG(__FirstNode != NULL, ">> winRefresh(): window list is empty!\n");

  ptr = __FirstNode;
  DEMOInitCaption(2, __X_Res, __Y_Res);

  while (ptr != NULL) {
    if (ptr->refresh) {
      ptr->refresh(ptr);
    }

    ptr = ptr->next;
  }
}
/** Appends a window to the end of the window list. */
void __win_add_node(sWIN* handle) {
#line 390
  MUSY_ASSERT_MSG(handle != NULL, "__add_node(): you're adding a NULL node!\n");

  if ((sWIN*)NULL == __LastNode) {

    __CurrNode = handle;

    __LastNode = handle;

    __FirstNode = handle;

    handle->next = NULL;

    handle->prev = NULL;

    MUSY_ASSERT_MSG(__FirstNode != NULL, "  > __FirstNode: NULL HANDLE!\n");
  } else {
    __LastNode->next = handle;
    handle->next = NULL;
    handle->prev = __LastNode;
    __LastNode = handle;
  }
}

/** Unlinks a window from the list and frees it. */
void __win_delete_node(sWIN* handle) {
#line 434
  MUSY_ASSERT_MSG(handle != NULL, "__delete_node(): you're deleting a NULL node!\n");

  if (__FirstNode == handle) {
    if (handle->next != NULL) {
      __FirstNode = handle->next;
      handle->next->prev = NULL;
      OSFree(handle);
    } else {
      __FirstNode = __LastNode = NULL;
      OSFree(handle);
    }
  } else if (__LastNode == handle) {
    if (handle->prev != NULL) {
      __LastNode = handle->prev;
      handle->prev->next = NULL;
      OSFree(handle);
    } else {
      __FirstNode = __LastNode = NULL;
      OSFree(handle);
    }
  } else {
    handle->prev->next = handle->next;
    handle->next->prev = handle->prev;
    OSFree(handle);
  }
}

/** Refresh function of log windows: draws the newest lines from the bottom up, one per 8 pixel row. */
static void __win_log_refresh(struct STRUCT_WIN* handle /* r31 */) {
  // Local variables
  u16 n;     // r30
  u16 i;     // r29
  u16 x;     // r27
  u16 y;     // r26
  u16 index; // r1+0x8
#line 506
  MUSY_ASSERT_MSG(handle != NULL, "OHMYGAWD\n");
  n = (u16)handle->curr_output_line;
  x = handle->x1;
  for (i = 0; i < handle->char_height; ++i) {
    n = ((u16)n + (u16)handle->total_lines - 1) % (u16)handle->total_lines;
    y = (u16)handle->y2 - i * 8;
    index = n * (u16)handle->char_width;
    DEMOPrintf(x, y, 0, "%s", handle->buffer[n]);
  }
}
