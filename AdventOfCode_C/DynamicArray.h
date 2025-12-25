#ifndef DynamicArray_h
#define DynamicArray_h

#include <malloc.h>
#include <stdbool.h>
#include "malloc_custom.h"
#include "stdint_custom.h"

#pragma region Dynamic Array Definitions
#pragma region Integer Dynamic Arrays
typedef struct Int8DynamicArray {
	i8 *items;
	u32 count;
	u32 capacity;
} i8DA;

typedef struct Uint8DynamicArray {
	u8 *items;
	u32 count;
	u32 capacity;
} u8DA;

typedef struct Int16DynamicArray {
	i16 *items;
	u32 count;
	u32 capacity;
} i16DA;

typedef struct Uint16DynamicArray {
	u16 *items;
	u32 count;
	u32 capacity;
} u16DA;

typedef struct Int32DynamicArray {
	i32 *items;
	u32 count;
	u32 capacity;
} i32DA;

typedef struct Uint32DynamicArray {
	u32 *items;
	u32 count;
	u32 capacity;
} u32DA;

typedef struct Int64DynamicArray {
	i64 *items;
	u32 count;
	u32 capacity;
} i64DA;

typedef struct Uint64DynamicArray {
	u64 *items;
	u32 count;
	u32 capacity;
} u64DA;
#pragma endregion

typedef struct BoolDynamicArray {
	bool *items;
	u32 count;
	u32 capacity;
} bDA;

typedef struct CharDynamicArray {
	char *items;
	u32 count;
	u32 capacity;
} cDA;

typedef struct StringDynamicArray {
	char **items;
	u32 count;
	u32 capacity;
} sDA;

typedef struct FloatDynamicArray {
	float *items;
	u32 count;
	u32 capacity;
} fDA;

typedef struct DoubleDynamicArray {
	double *items;
	u32 count;
	u32 capacity;
} dDA;

typedef struct LongDoubleDynamicArray {
	long double *items;
	u32 count;
	u32 capacity;
} ldDA;
#pragma endregion

#pragma region Macros / Functions
#define DYNAMIC_ARRAY_DEFAULT_LENGTH 8

/// @brief Appends the given value to the given dynamic array.\n
/// Based on: https://youtu.be/95M6V3mZgrI
#define daAppend(array, value)\
	do {\
		if (array.count >= array.capacity)\
		{\
			if (array.capacity == 0)  array.capacity = DYNAMIC_ARRAY_DEFAULT_LENGTH;\
			else  array.capacity *= 2;\
			array.items = SafeRealloc(array.items, array.capacity * sizeof(*array.items));\
		}\
		array.items[array.count++] = value;\
	}\
	while (false)

/// @brief Shortens the dynamic array to array.count elements.
#define daCrop(array)\
	do {\
		array.capacity = array.count;\
		array.items = SafeRealloc(array.items, array.capacity * sizeof(*array.items));\
	}\
	while (false)

/// @brief Frees the dynamic arrays items and the array itself.
#define daFree(array)\
	do {\
		free(array.items);\
	}\
	while (false)

//// Maybe add more dynamic array macros for stuff like removing items, popping items, inserting items, etc. ?
//// Might be excessive, though . . .
#pragma endregion

#endif
