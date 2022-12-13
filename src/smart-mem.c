#include <smart-mem.h>

smart_mem SMART_M_COUNT = {NULL, NULL};
bool SMART_M_IMMEDIATE = false;


/// @brief Smartly allocate memory which is freed when called sm_free_all()
/// @param size size to allocate ( in BYTES )
/// @return pointer of the memory
void* sm_malloc(size_t size) {
    void * mp = malloc(size);
    
    if( SMART_M_IMMEDIATE ) {
        SMART_M_IMMEDIATE = false;
        SMART_M_COUNT.point = mp;
    }
    
    smart_mem* m = &SMART_M_COUNT;
    while(m->nxt) { m = m -> nxt; }
    if(m -> point) {
        m -> nxt = (smart_mem*)calloc(1, sizeof(smart_mem));
        m = m -> nxt;
    }
    m -> nxt = NULL;
    m -> point = mp;
    return mp;
}

/// @brief Smartly re-allocate smart memory
/// @param sm_m smart memory pointer
/// @param size size to re-allocate ( in BYTES )
/// @return pointer of the re-allocated memory
void* sm_realloc(void* sm_m, size_t size) {
    smart_mem* m = &SMART_M_COUNT;
    while(m->point) {
        if ( m -> point == sm_m) {
            m -> point = realloc(sm_m, size);
            return m -> point;
        }
        m = m -> nxt;
    }
    return NULL; // not a smartly allocated memory
}

/// @brief Smartly allocate memory [All initialized to 0] which is freed when called sm_free_all()
/// @param memb no of membors
/// @param size size of one member
/// @return pointer of the memory
void* sm_calloc(size_t memb, size_t size) {
    void * mp = calloc(memb, size);
    
    if( SMART_M_IMMEDIATE ) {
        SMART_M_IMMEDIATE = false;
        SMART_M_COUNT.point = mp;
    }
    
    smart_mem* m = &SMART_M_COUNT;
    while(m->nxt) { m = m -> nxt; }
    if(m -> point) {
        m -> nxt = (smart_mem*)calloc(1, sizeof(smart_mem));
        m = m -> nxt;
    }
    m -> nxt = NULL;
    m -> point = mp;
    return mp;
}

/// @brief Smartly remove smartly allocated memory through `sm_malloc` `sm_calloc`, etc.
/// @param ptr memory pointer to free
void sm_free(void* ptr) {
    smart_mem* m = &SMART_M_COUNT;
    if(ptr == SMART_M_COUNT.point) {
        free(SMART_M_COUNT.point);
        SMART_M_COUNT.point = NULL;
        SMART_M_IMMEDIATE = true;
        return;
    }
    while(m -> nxt && m -> nxt -> point != ptr ) { m = m -> nxt; }
    if(m -> nxt -> point != ptr) { return; }
    free(m -> nxt -> point);
    smart_mem* tmp = m -> nxt;
    m -> nxt = m -> nxt -> nxt;
    free(tmp);
}

/// @brief Free all memory allocated by sm_* functions
void sm_free_all() {
    // free all smart_mem
    smart_mem* m = SMART_M_COUNT.nxt;
    while(m && m -> point) {
        smart_mem* x = m -> nxt;
        m -> nxt = NULL;
        free(m -> point);
        free(m);
        m = x;
    }
    if(SMART_M_COUNT.point) {
        free(SMART_M_COUNT.point);
    }
}