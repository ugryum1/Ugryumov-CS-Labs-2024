#ifndef NUMERIC_ARRAY_SORTING
#define NUMERIC_ARRAY_SORTING

#include <stddef.h>

namespace NumericArraySorting {
enum class ArrayType : int {
    Static = 1,
    Dynamic = 2,
};

void SelectionSorting(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool reversed);
void BubbleSorting(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool reversed);

void DoStaticArray();
void DoDynamicArray();

void SelectTask(ArrayType task);

void TaskApp();
}  // namespace NumericArraySorting

#endif
