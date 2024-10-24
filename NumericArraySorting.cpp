#include "NumericArraySorting.h"

#include <iomanip>
#include <iostream>
#include <random>

namespace {
const size_t kColumnWidth = 16;
const size_t kStaticArrayLength = 8;

const int kMinRandomValue = 0;
const int kMaxRandomValue = 99;

void FillArrayWithRandomValues(int* array, size_t arrayLength) {
    if (!array) {
        return;
    }

    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinRandomValue, kMaxRandomValue);
    for (size_t i = 0; i < arrayLength; ++i) {
        array[i] = distribution(randomEngine);
    }
}

void CopyArray(const int* source, int* destination, size_t arrayLength) {
    if (!source || !destination) {
        return;
    }

    for (size_t i = 0; i < arrayLength; ++i) {
        destination[i] = source[i];
    }
}

void PrintArray(const int* array, size_t arrayLength) {
    if (!array) {
        return;
    }

    for (size_t i = 0; i < arrayLength; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

void PrintTable(size_t permutationsSelection, size_t comparisonsSelection, size_t permutationsBubble, size_t comparisonsBubble) {
    std::cout << std::endl;
    std::cout << std::left << std::setw(kColumnWidth) << "Sorting" << std::left << std::setw(kColumnWidth) << std::left << "Permutations"
              << std::setw(kColumnWidth) << "Comparisons" << std::endl;
    std::cout << std::left << std::setw(kColumnWidth) << "Selection" << std::left << std::setw(kColumnWidth) << permutationsSelection << std::left
              << std::setw(kColumnWidth) << comparisonsSelection << std::endl;
    std::cout << std::left << std::setw(kColumnWidth) << "Bubble" << std::left << std::setw(kColumnWidth) << permutationsBubble << std::left
              << std::setw(kColumnWidth) << comparisonsBubble << std::endl
              << std::endl;
}
}  // namespace

namespace NumericArraySorting {
void SelectionSort(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool ascending) {
    if (!array) {
        return;
    }

    permutations = 0;
    comparisons = 0;

    for (size_t i = 0; i < arrayLength - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arrayLength; ++j) {
            if ((ascending && array[j] < array[minIndex]) || (!ascending && array[j] > array[minIndex])) {
                minIndex = j;
            }
            ++comparisons;
        }

        if (array[i] != array[minIndex]) {
            std::swap(array[i], array[minIndex]);
            ++permutations;
        }
    }
}

void BubbleSort(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool ascending) {
    if (!array) {
        return;
    }

    permutations = 0;
    comparisons = 0;
    size_t permutationsPerLoop = 1;

    for (size_t i = 0; i < arrayLength - 1 && permutationsPerLoop != 0; ++i) {
        permutationsPerLoop = 0;
        for (size_t j = 0; j < arrayLength - i - 1; ++j) {
            if ((ascending && array[j] > array[j + 1]) || (!ascending && array[j] < array[j + 1])) {
                std::swap(array[j], array[j + 1]);
                ++permutationsPerLoop;
            }
            ++comparisons;
        }

        permutations += permutationsPerLoop;
    }
}

void RunSortStaticArray() {
    int arraySelectionSort[kStaticArrayLength]{};
    int arrayBubbleSort[kStaticArrayLength]{};

    FillArrayWithRandomValues(arraySelectionSort, kStaticArrayLength);
    CopyArray(arraySelectionSort, arrayBubbleSort, kStaticArrayLength);

    size_t permutationsSelection{};
    size_t comparisonsSelection{};
    size_t permutationsBubble{};
    size_t comparisonsBubble{};

    std::cout << "Массив: ";
    PrintArray(arraySelectionSort, kStaticArrayLength);

    SelectionSort(arraySelectionSort, kStaticArrayLength, permutationsSelection, comparisonsSelection);
    BubbleSort(arrayBubbleSort, kStaticArrayLength, permutationsBubble, comparisonsBubble);

    std::cout << "Отсортированный выбором по возрастанию: ";
    PrintArray(arraySelectionSort, kStaticArrayLength);
    std::cout << "Отсортированный пузырьком по возрастанию: ";
    PrintArray(arrayBubbleSort, kStaticArrayLength);
    PrintTable(permutationsSelection, comparisonsSelection, permutationsBubble, comparisonsBubble);

    std::cout << "Массив: ";
    PrintArray(arraySelectionSort, kStaticArrayLength);

    SelectionSort(arraySelectionSort, kStaticArrayLength, permutationsSelection, comparisonsSelection);
    BubbleSort(arrayBubbleSort, kStaticArrayLength, permutationsBubble, comparisonsBubble);

    std::cout << "Отсортированный выбором по возрастанию: ";
    PrintArray(arraySelectionSort, kStaticArrayLength);
    std::cout << "Отсортированный пузырьком по возрастанию: ";
    PrintArray(arrayBubbleSort, kStaticArrayLength);
    PrintTable(permutationsSelection, comparisonsSelection, permutationsBubble, comparisonsBubble);

    std::cout << "Массив: ";
    PrintArray(arraySelectionSort, kStaticArrayLength);

    SelectionSort(arraySelectionSort, kStaticArrayLength, permutationsSelection, comparisonsSelection, false);
    BubbleSort(arrayBubbleSort, kStaticArrayLength, permutationsBubble, comparisonsBubble, false);

    std::cout << "Отсортированный выбором по убыванию: ";
    PrintArray(arraySelectionSort, kStaticArrayLength);
    std::cout << "Отсортированный пузырьком по убыванию: ";
    PrintArray(arrayBubbleSort, kStaticArrayLength);
    PrintTable(permutationsSelection, comparisonsSelection, permutationsBubble, comparisonsBubble);
}

void RunSortDynamicArray() {
    std::cout << "Введите целое натуральное число - длину массива." << std::endl;

    size_t arrayLength{};
    std::cin >> arrayLength;

    if (arrayLength <= 0) {
        std::cout << "Ошибка ввода, число должно быть натуральным.\n" << std::endl;
        return;
    }

    int* arraySelectionSort = new int[arrayLength];
    int* arrayBubbleSort = new int[arrayLength];

    FillArrayWithRandomValues(arraySelectionSort, arrayLength);
    CopyArray(arraySelectionSort, arrayBubbleSort, arrayLength);

    size_t permutationsSelection{};
    size_t comparisonsSelection{};
    size_t permutationsBubble{};
    size_t comparisonsBubble{};

    SelectionSort(arraySelectionSort, arrayLength, permutationsSelection, comparisonsSelection, true);
    BubbleSort(arrayBubbleSort, arrayLength, permutationsBubble, comparisonsBubble, true);

    PrintTable(permutationsSelection, comparisonsSelection, permutationsBubble, comparisonsBubble);

    delete[] arraySelectionSort;
    delete[] arrayBubbleSort;
}

void SelectTask(ArrayType task) {
    switch (task) {
        case ArrayType::Static:
            RunSortStaticArray();
            break;
        case ArrayType::Dynamic:
            RunSortDynamicArray();
            break;
        default:
            std::cout << "Такого типа массива не существует.\n" << std::endl;
            break;
    }
}

void ExecuteApp() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        std::cout << "Введите тип массива (число от 1 до 2), который хотите отсортировать."
                     "\n\t1. Статический массив\n\t2. Динамический массив"
                  << std::endl;
        int arrayType{};
        std::cin >> arrayType;

        SelectTask(static_cast<ArrayType>(arrayType));

        std::cout << "Продолжить работу? (y/n)" << std::endl;
        std::cin >> continueExecution;
        if (continueExecution == 'y') {
            std::cout << std::endl;
        }
    }
}
}  // namespace NumericArraySorting
