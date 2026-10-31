typedef struct DestructorChain {
    struct DestructorChain* next;
    void* destructor;
    void* object;
} DestructorChain;

DestructorChain* __global_destructor_chain;

/**
 * Runs at exit through the .dtors table: pops each registered global object off the destructor chain
 * and calls its destructor (with the delete-flag argument -1), most recently registered first.
 */
void __destroy_global_chain(void) {
    DestructorChain* gdc;

    while ((gdc = __global_destructor_chain) != 0) {
        __global_destructor_chain = gdc->next;
        ((void (*)(void*, short))gdc->destructor)(gdc->object, -1);
    }
}

__declspec(section ".dtors") static void* const __destroy_global_chain_reference = __destroy_global_chain;
