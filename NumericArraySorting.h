#ifndef NUMERIC_ARRAY_SORTING_H
#define NUMERIC_ARRAY_SORTING_H

#include <cstddef>

namespace NumericArraySorting {
enum class ArrayType : int {
    Static = 1,
    Dynamic = 2,
};

void SelectionSort(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool ascending = true);
void BubbleSort(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool ascending = true);

void RunSortStaticArray();
void RunSortDynamicArray();

void SelectTask(ArrayType task);

void ExecuteApp();
}  // namespace NumericArraySorting

#endif  // NUMERIC_ARRAY_SORTING_H
