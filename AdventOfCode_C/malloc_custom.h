#ifndef malloc_custom_h
#define malloc_custom_h

#include <stddef.h>  // Do I need this for size_t? Surely I have to include something, right?

/// @brief A 'safe' version of malloc() which prints an error and exits the program when malloc() fails.
/// @param size The size (in bytes) to allocate.
/// @return A pointer to the allocated block of memory.
void *SafeMalloc(size_t size);

/// @brief A 'safe' version of calloc() which prints an error and exits the program when calloc() fails.
/// @param count The number of elements to allocate memory for.
/// @param size The size (in bytes) of each element.
/// @return A pointer to the allocated block of memory.
void *SafeCalloc(size_t count, size_t size);

/// @brief A 'safe' version of realloc() which prints an error and exits the program when realloc() fails.
/// @param block A pointer to the block of memory to re-allocate.
/// @param size The size (in bytes) to re-allocate to the given block.
/// @return A pointer to the allocated block of memory.
void *SafeRealloc(void *block, size_t size);

#endif
