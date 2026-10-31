/*
 * libtess (SGI OpenGL Sample Implementation GLU): memory allocation.
 * Author: Eric Veach, July 1994.
 */

#include <string.h>
#include "glu/memalloc.h"

int __gl_memInit(size_t maxFast) {
    return 1;
}

/* realloc on the map heap: the sorted priority queue (priorityq.c) grows its arrays with it. */
void* __gl_memRealloc(void* ptr, size_t size) {
    if (ptr == NULL) {
        return memAlloc(size);
    } else if (size == 0) {
        memFree(ptr);
        return NULL;
    } else {
        int newSize = size;
        void* newPtr = memAlloc(newSize);
        if (newPtr == NULL) {
            return NULL;
        }
        memcpy(newPtr, ptr, newSize);
        memFree(ptr);
        return newPtr;
    }
}
