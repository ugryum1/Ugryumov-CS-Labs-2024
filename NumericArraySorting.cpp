#include "NumericArraySorting.h"

#include <iomanip>
#include <iostream>
#include <random>

namespace {
const size_t kColumnWidth = 16;
const int kTwo = 2;
const size_t kStaticArrayLength = 8;

const int kMinRandomValue = 1;
const int kMaxRandomValue = 99;

const bool kReversed = true;
const bool kNonReversed = false;

void PrintArray(int* array, size_t arrayLength) {
    for (size_t i = 0; i < arrayLength; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

void PrintTable(size_t permutationsSelection, size_t comparisonsSelection, size_t permutationsBubble, size_t comparisonsBubble) {
    std::cout << std::endl;
    std::cout << "      Сортировка" << "    Перестановки" << "       Сравнения" << std::endl;
    std::cout << "         Выбором" << std::setw(kColumnWidth) << permutationsSelection << std::setw(kColumnWidth) << comparisonsSelection
              << std::endl;
    std::cout << "       Пузырьком" << std::setw(kColumnWidth) << permutationsBubble << std::setw(kColumnWidth) << comparisonsBubble << std::endl
              << std::endl;
    std::cout << "Сортировка " << (permutationsSelection + comparisonsSelection < permutationsBubble + comparisonsBubble ? "выбором" : "пузырьком")
              << " прошла быстрее.\n\n";
}

void PrintSortedArray(int* array, int* arrayClone, size_t arrayLength, bool reversed) {
    size_t permutationsSelection{};
    size_t comparisonsSelection{};
    size_t permutationsBubble{};
    size_t comparisonsBubble{};

    std::cout << "Массив:\t";
    PrintArray(array, arrayLength);

    std::cout << "Отсортированный выбором" << (reversed == kReversed ? " по невозрастанию" : "") << ":\t";
    if (reversed == kNonReversed) {
        NumericArraySorting::SelectionSorting(array, arrayLength, permutationsSelection, comparisonsSelection, kNonReversed);
    } else {
        NumericArraySorting::SelectionSorting(array, arrayLength, permutationsSelection, comparisonsSelection, kReversed);
    }

    PrintArray(array, arrayLength);

    std::cout << "Отсортированный пузырьком" << (reversed == kReversed ? " по невозрастанию" : "") << ":\t";
    if (reversed == kNonReversed) {
        NumericArraySorting::BubbleSorting(arrayClone, arrayLength, permutationsBubble, comparisonsBubble, kNonReversed);
    } else {
        NumericArraySorting::BubbleSorting(arrayClone, arrayLength, permutationsBubble, comparisonsBubble, kReversed);
    }
    PrintArray(arrayClone, arrayLength);

    PrintTable(permutationsSelection, comparisonsSelection, permutationsBubble, comparisonsBubble);
}
}  // namespace

void NumericArraySorting::SelectionSorting(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool reversed) {
    if (arrayLength <= 1) {
        return;
    }

    for (size_t i = 0; i < arrayLength - 1; ++i) {
        size_t minIndex = i;
        for (size_t j = i + 1; j < arrayLength; ++j) {
            if ((reversed == kNonReversed && array[j] < array[minIndex]) || (reversed == kReversed && array[j] > array[minIndex])) {
                minIndex = j;
            }
            ++comparisons;
        }

        int temp = array[i];
        array[i] = array[minIndex];
        array[minIndex] = temp;
        permutations += kTwo;
    }
}

void NumericArraySorting::BubbleSorting(int* array, size_t arrayLength, size_t& permutations, size_t& comparisons, bool reversed) {
    for (size_t i = 0; i < arrayLength - 1; ++i) {
        for (size_t j = 0; j < arrayLength - i - 1; ++j) {
            if ((reversed == kNonReversed && array[j] > array[j + 1]) || (reversed == kReversed && array[j] < array[j + 1])) {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                permutations += kTwo;
            }
            ++comparisons;
        }
    }
}

void NumericArraySorting::DoStaticArray() {
    int* array = new int[kStaticArrayLength];
    int* arrayClone = new int[kStaticArrayLength];

    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinRandomValue, kMaxRandomValue);
    for (size_t i = 0; i < kStaticArrayLength; ++i) {
        array[i] = distribution(randomEngine);
        arrayClone[i] = array[i];
    }

    PrintSortedArray(array, arrayClone, kStaticArrayLength, kNonReversed);
    PrintSortedArray(array, arrayClone, kStaticArrayLength, kNonReversed);
    PrintSortedArray(array, arrayClone, kStaticArrayLength, kReversed);

    delete[] array;
    delete[] arrayClone;
}

void NumericArraySorting::DoDynamicArray() {
    std::cout << "Введите целое натуральное число - длину массива." << std::endl;

    size_t arrayLength{};
    std::cin >> arrayLength;

    if (arrayLength <= 0) {
        std::cout << "Ошибка ввода, число должно быть натуральным.\n" << std::endl;
        return;
    }

    int* array = new int[arrayLength];
    int* arrayClone = new int[arrayLength];

    std::random_device r{};
    std::default_random_engine randomEngine(r());
    std::uniform_int_distribution distribution(kMinRandomValue, kMaxRandomValue);
    for (size_t i = 0; i < arrayLength; ++i) {
        array[i] = distribution(randomEngine);
        arrayClone[i] = array[i];
    }

    PrintSortedArray(array, arrayClone, arrayLength, kNonReversed);

    delete[] array;
    delete[] arrayClone;
}

void NumericArraySorting::SelectTask(ArrayType task) {
    switch (task) {
        case NumericArraySorting::ArrayType::Static:
            NumericArraySorting::DoStaticArray();
            break;
        case NumericArraySorting::ArrayType::Dynamic:
            NumericArraySorting::DoDynamicArray();
            break;
        default:
            std::cout << "Неверный ввод.\n" << std::endl;
            break;
    }
}

void NumericArraySorting::TaskApp() {
    char continueEcecution = 'y';
    while (continueEcecution == 'y') {
        std::cout << "Введите тип массива (число от 1 до 2), который хотите отсортировать."
                     "\n\t1. Статический массив\n\t2. Динамический массив"
                  << std::endl;
        int input{};
        std::cin >> input;

        NumericArraySorting::SelectTask(static_cast<ArrayType>(input));

        std::cout << "Продолжить работу? (y/n)" << std::endl;
        std::cin >> continueEcecution;
        if (continueEcecution == 'y') {
            std::cout << std::endl;
        }
    }
}
