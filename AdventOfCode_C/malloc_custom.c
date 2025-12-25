#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "malloc_custom.h"

/// @brief Prints an error and exits the program if there was an allocation failure aka. the given pointer is null.
/// @param block The resulting pointer of a memory allocation to check.
static void HandleAllocationFailure(void *block)
{
    if (!block)
    {
        perror("Memory allocation failed.");
        exit(EXIT_FAILURE);
    }
}

void *SafeMalloc(size_t size)
{
    void *allocatedMemory = malloc(size);
    HandleAllocationFailure(allocatedMemory);
    return allocatedMemory;
}

void *SafeCalloc(size_t count, size_t size)
{
    void *allocatedMemory = calloc(count, size);
    HandleAllocationFailure(allocatedMemory);
    return allocatedMemory;
}

void *SafeRealloc(void *block, size_t size)
{
    void *allocatedMemory = realloc(block, size);
    HandleAllocationFailure(allocatedMemory);
    return allocatedMemory;
}