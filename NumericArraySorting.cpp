#include "NumericArraySorting.h"

#include <iomanip>
#include <iostream>
#include <random>

namespace {
const int kColumnWidth = 16;
const int kTwo = 2;
const int kStaticArrayLength = 8;
const int kMinRandomValue = 1;
const int kMaxRandomValue = 99;

void PrintArray(int* array, int arrayLength) {
    for (int i = 0; i < arrayLength; ++i) {
        std::cout << array[i] << ' ';
    }
    std::cout << std::endl;
}

void PrintTable(int permutationsSelection, int comparisonsSelection, int permutationsBubble, int comparisonsBubble) {
    std::cout << std::endl;
    std::cout << "      Сортировка" << "    Перестановки" << "       Сравнения" << std::endl;
    std::cout << "         Выбором" << std::setw(kColumnWidth) << permutationsSelection << std::setw(kColumnWidth)
              << comparisonsSelection << std::endl;
    std::cout << "       Пузырьком" << std::setw(kColumnWidth) << permutationsBubble << std::setw(kColumnWidth)
              << comparisonsBubble << std::endl << std::endl;
}

void PrintSortedArray(int* array, int* arrayClone, int arrayLength) {
    int permutationsSelection{};
    int comparisonsSelection{};
    int permutationsBubble{};
    int comparisonsBubble{};

    std::cout << "Массив:\t";
    PrintArray(array, arrayLength);

    std::cout << "Отсортированный выбором:\t";
    NumericArraySorting::SelectionSorting(array, arrayLength, permutationsSelection, comparisonsSelection);
    PrintArray(array, arrayLength);

    std::cout << "Отсортированный пузырьком:\t";
    NumericArraySorting::BubbleSorting(arrayClone, arrayLength, permutationsBubble, comparisonsBubble);
    PrintArray(arrayClone, arrayLength);

    PrintTable(permutationsSelection, comparisonsSelection, permutationsBubble, comparisonsBubble);
}
}  // namespace

void NumericArraySorting::SelectionSorting(int* array, int arrayLength, int& permutations, int& comparisons) {
    if (arrayLength <= 1) {
        return;
    }

    for (int i = 0; i < arrayLength - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < arrayLength; ++j) {
            if (array[j] < array[minIndex]) {
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

void NumericArraySorting::BubbleSorting(int* array, int arrayLength, int& permutations, int& comparisons) {
    for (int i = 0; i < arrayLength - 1; ++i) {
        for (int j = 0; j < arrayLength - i - 1; ++j) {
            if (array[j] > array[j + 1]) {
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
    for (int i = 0; i < kStaticArrayLength; ++i) {
        array[i] = distribution(randomEngine);
        arrayClone[i] = array[i];
    }

    PrintSortedArray(array, arrayClone, kStaticArrayLength);
    PrintSortedArray(array, arrayClone, kStaticArrayLength);

    delete[] array;
    delete[] arrayClone;
}

void NumericArraySorting::DoDynamicArray() {
    std::cout << "Введите целое натуральное число - длину массива." << std::endl;

    int arrayLength{};
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
    for (int i = 0; i < arrayLength; ++i) {
        array[i] = distribution(randomEngine);
        arrayClone[i] = array[i];
    }

    PrintSortedArray(array, arrayClone, arrayLength);

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
