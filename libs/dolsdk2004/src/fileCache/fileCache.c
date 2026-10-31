#include <dolphin/os.h>
#include <charPipeline/fileCache.h>

DSCache DODisplayCache;
u8 DOCacheInitialized;

static u8 AllocCacheNode(DSCacheNodePtr* cacheNode, char* name);
static void FreeCacheNode(DSCacheNodePtr* cacheNode);

/**
 * Adds an entry to a cache's node list: copies the name,
 * stores the data pointer and the function used to free it, and starts the reference count at 0.
 * Returns NULL if memory ran out.
 */
DSCacheNodePtr DSAddCacheNode(DSCachePtr cache, char* name, Ptr data, Ptr OSFreeFunc) {
    DSCacheNodePtr cacheNode;

    cacheNode = NULL;
    if (!AllocCacheNode(&cacheNode, name)) {
        return NULL;
    }
    Strcpy(cacheNode->Name, name);
    cacheNode->Data = data;
    cacheNode->Free = (void (*)(Ptr *))OSFreeFunc;
    cacheNode->ReferenceCount = 0;
    DSInsertListObject(&cache->CacheNodeList, NULL, (Ptr)cacheNode);
    return cacheNode;
}

/**
 * Allocates a cache node and a buffer for its name (OSAlloc). Frees any node already held in *cacheNode first.
 * Returns false if either allocation fails.
 */
static u8 AllocCacheNode(DSCacheNodePtr* cacheNode, char* name) {
    if (*cacheNode) {
        FreeCacheNode(cacheNode);
    }

    *cacheNode = OSAlloc(sizeof(DSCacheNode));
    if (!*cacheNode) {
        return FALSE;
    }

    (*cacheNode)->Name = OSAlloc(Strlen(name) + 1);
    if (!(*cacheNode)->Name) {
        return FALSE;
    }

    return TRUE;
}

/** Removes every node from a cache and frees them, whatever their reference count. */
void DSEmptyCache(DSCachePtr cache) {
    DSCacheNodePtr cursor;
    DSCacheNodePtr cacheNode;

    cursor = (DSCacheNodePtr)cache->CacheNodeList.Head;
    while (cursor) {
        cacheNode = cursor;
        cursor = (DSCacheNodePtr)cursor->Link.Next;
        DSRemoveListObject(&cache->CacheNodeList, (Ptr)cacheNode);
        FreeCacheNode(&cacheNode);
    }
}

/** Finds a node by its data pointer if data is given, otherwise by name. Returns NULL when none matches. */
static DSCacheNodePtr FindCacheNode(DSCachePtr cache, char* name, Ptr data) {
    DSCacheNodePtr cacheNode;

    cacheNode = (DSCacheNodePtr)cache->CacheNodeList.Head;
    if (data) {
        while (cacheNode) {
            if (data == cacheNode->Data) {
                return cacheNode;
            }
            cacheNode = (DSCacheNodePtr)cacheNode->Link.Next;
        }
    } else if (name) {
        while (cacheNode) {
            if (Strcmp(name, cacheNode->Name) == 0) {
                return cacheNode;
            }
            cacheNode = (DSCacheNodePtr)cacheNode->Link.Next;
        }
    }
    return NULL;
}

/** Finds a cached object by name, adds one reference to it and returns its data, or NULL if it is not cached. */
Ptr DSGetCacheObj(DSCachePtr cache, char* name) {
    DSCacheNodePtr cacheNode;

    cacheNode = FindCacheNode(cache, name, NULL);
    if (cacheNode) {
        cacheNode->ReferenceCount++;
        return cacheNode->Data;
    }
    return NULL;
}

/** Calls the node's free function on its data (if it has one), frees the name and the node, and clears the pointer. */
static void FreeCacheNode(DSCacheNodePtr* cacheNode) {
    if (*cacheNode) {
        if ((*cacheNode)->Free) {
            (*cacheNode)->Free(&(*cacheNode)->Data);
        }
        OSFree((*cacheNode)->Name);
        OSFree(*cacheNode);
        *cacheNode = NULL;
    }
}

/** Prepares an empty cache with automatic purging turned on. */
void DSInitCache(DSCachePtr cache) {
    DSCacheNode cacheNode;

    cache->PurgeFlag = DS_AUTO_PURGE;
    DSInitList(&cache->CacheNodeList, (Ptr)&cacheNode, &cacheNode.Link);
}

/** Frees every node whose reference count is 0 and keeps the ones still in use. */
void DSPurgeCache(DSCachePtr cache) {
    DSCacheNodePtr cursor;
    DSCacheNodePtr cacheNode;

    cursor = (DSCacheNodePtr)cache->CacheNodeList.Head;
    while (cursor) {
        cacheNode = cursor;
        cursor = (DSCacheNodePtr)cursor->Link.Next;
        if (cacheNode->ReferenceCount == 0) {
            DSRemoveListObject(&cache->CacheNodeList, (Ptr)cacheNode);
            FreeCacheNode(&cacheNode);
        }
    }
}

/**
 * Drops one reference on the node holding this data.
 * When the count reaches 0 and the cache is set to auto purge, the node is freed.
 */
void DSReleaseCacheObj(DSCachePtr cache, Ptr data) {
    DSCacheNodePtr cacheNode;

    cacheNode = FindCacheNode(cache, NULL, data);
    if (cacheNode) {
        if (cacheNode->ReferenceCount != 0) {
            cacheNode->ReferenceCount--;
        }

        if (cacheNode->ReferenceCount == 0 && cache->PurgeFlag == DS_AUTO_PURGE) {
            DSRemoveListObject(&cache->CacheNodeList, (Ptr)cacheNode);
            FreeCacheNode(&cacheNode);
        }
    }
}

/** Sets whether DSReleaseCacheObj frees a node when its last reference is released. */
void DSSetCachePurgeFlag(DSCachePtr cache, u8 purgeFlag) {
    cache->PurgeFlag = purgeFlag;
}

/** Initializes the global display cache (DODisplayCache) and marks it initialized. */
void CSHInitDisplayCache(void) {
    DSInitCache(&DODisplayCache);
    DOCacheInitialized = TRUE;
}
