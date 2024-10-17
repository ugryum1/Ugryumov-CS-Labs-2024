#ifndef NUMERIC_ARRAY_SORTING
#define NUMERIC_ARRAY_SORTING

namespace NumericArraySorting {
enum class ArrayType : int {
    Static = 1,
    Dynamic = 2,
};

void SelectionSorting(int* array, int arrayLength, int& permutations, int& comparisons);
void BubbleSorting(int* array, int arrayLength, int& permutations, int& comparisons);

void DoStaticArray();
void DoDynamicArray();

void SelectTask(ArrayType task);

void TaskApp();
}  // namespace NumericArraySorting

#endif
