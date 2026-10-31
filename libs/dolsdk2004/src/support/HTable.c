#include <charPipeline/structures/HTable.h>
#include <charPipeline/structures/List.h>

/**
 * Initialises a hash table of size buckets, held in listArray, with hashFunc mapping an object to a bucket;
 * every bucket is an empty list whose link offset is taken from obj and link.
 */
void DSInitHTable(DSHashTable* hTable, u16 size, DSList* listArray, DSHashFunc* hashFunc, Ptr obj, DSLinkPtr link) {
    u16 i;

    hTable->table = listArray;
    hTable->tableSize = size;
    hTable->hash = hashFunc;
    for (i = 0; i < size; i++) {
        DSInitList(&listArray[i], obj, link);
    }
}

/** Hashes obj and inserts it at the tail of its bucket's list. */
void DSInsertHTableObj(DSHashTable* hTable, Ptr obj) {
    DSList* list = &hTable->table[hTable->hash(obj)];
    DSInsertListObject(list, 0, obj);
}

/** Joins all bucket lists of the table, in bucket order, onto list. */
void DSHTableToList(DSHashTable* hTable, DSList* list) {
    DSLink* link = NULL;
    u16 i = 0;

    list->Offset = hTable->table[i].Offset;
    for (i = 0; i < hTable->tableSize; i++) {
        DSAttachList(list, &hTable->table[i]);
    }
}

/**
 * Iterates over the whole table: returns the object after obj in its bucket,
 * or the first object of the next non-empty bucket; with obj NULL it starts from the first bucket.
 * Returns NULL at the end.
 */
void* DSNextHTableObj(DSHashTable* hTable, Ptr obj) {
    s32 currentIndex;
    void* cursor;

    if (!hTable) {
        return NULL;
    }

    if (!obj) {
        currentIndex = 0;
        cursor = DSNextListObj(&hTable->table[currentIndex], NULL);
    } else {
        currentIndex = DSHTableIndex(hTable, obj);
        if (currentIndex == -1) {
            return NULL;
        }
        cursor = DSNextListObj(&hTable->table[currentIndex], obj);
    }

    while (cursor == NULL && currentIndex < hTable->tableSize - 1) {
        currentIndex++;
        cursor = DSNextListObj(&hTable->table[currentIndex], NULL);
    }
    return cursor;
}

/** Returns the bucket number obj hashes to, or -1 if the table or obj is NULL. */
s32 DSHTableIndex(DSHashTable* hTable, Ptr obj) {
    if (!hTable || !obj) {
        return -1;
    }
    return hTable->hash(obj);
}

/** Returns the first object in bucket index, or NULL if the bucket is empty or index is out of range. */
void* DSHTableHead(DSHashTable* hTable, s32 index) {
    if (index < 0 || index >= hTable->tableSize) {
        return NULL;
    }
    return DSNextListObj(&hTable->table[index], NULL);
}
