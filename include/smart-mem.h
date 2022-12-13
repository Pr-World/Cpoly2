#if !defined(SMART_MEM_H_INCL)
#define SMART_MEM_H_INCL

#include <stdlib.h>
#include <stdbool.h>

typedef struct smart_mem
{
    struct smart_mem* nxt;
    void * point;
} smart_mem;

/// @brief Smartly allocate memory which is freed when called sm_free_all()
/// @param size size to allocate ( in BYTES )
/// @return pointer of the memory
void* sm_malloc(size_t size);

/// @brief Smartly allocate memory [All initialized to 0] which is freed when called sm_free_all()
/// @param memb no of membors
/// @param size size of one member
/// @return pointer of the memory
void* sm_calloc(size_t memb, size_t size);

/// @brief Smartly re-allocate smart memory!
/// @param size size to re-allocate ( in BYTES )
/// @return pointer of the re-allocated memory
void* sm_realloc(void* sm_m, size_t size);

/// @brief Smartly remove smartly allocated memory through `sm_malloc` `sm_calloc`, etc.
/// @param ptr memory pointer to free
void sm_free(void* ptr);

/// @brief Free all memory allocated by sm_* functions
void sm_free_all();

#endif // SMART_MEM_H_INCL
