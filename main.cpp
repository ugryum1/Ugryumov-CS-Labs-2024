#include <cmath>
#include <iostream>
#include <iomanip>

namespace {
const char kFirstTaskSymbol = '1';
const char kSecondTaskSymbol = '2';
const char kThirdTaskSymbol = '3';
const char kFourthTaskSymbol = '4';
const char kExitProgramSymbol = 'e';
const char kContinueProgramSymbol = 'y';

const int kBeginingCycleInFirstTask = 0;
const int kCycleStepInFirstTask = 5;
const int kNotDivisionRemainder = 0;

const int kPositiveNumbersBegin = 0;

const int kBeginingCycleIfPositiveA = 2;
const int kEndingCycleIfPositiveA = 8;
const int kStepCycleIfPositiveA = 2;
const int kBeginingCycleIfNegativeA = 3;
const int kEndingCycleIfNegativeA = 9;
const int kStepCycleIfNegativeA = 3;
}  // namespace

void TaskSelection();

bool SolveAgain() {
    std::cout << "\nЕсли хотите ещё раз решить это задание, напишите 'y', "
                 "иначе напишите 'n', вы перейдёте к выбору заданий."
              << std::endl;
    char choice{};
    std::cin >> choice;

    if (choice == kContinueProgramSymbol) {
        return true;
    }

    TaskSelection();
    return false;
}

void DoFirstTask() {
    int n{};
    int m{};
    std::cout << "\nВведите натуральные числа n и m (m < n) через проблел." << std::endl;
    std::cin >> n >> m;

    int answer = 0;

    for (int i = kBeginingCycleInFirstTask; i <= n; i += kCycleStepInFirstTask) {
        if (i % m != kNotDivisionRemainder) {
            answer += i;
        }
    }

    std::cout << "\nСумма натуральных чисел, делящихся на 5 и не делящихся на " << m
              << " одновременно, "
                 "на отрезке от 1 до "
              << n << " равна " << answer << "." << std::endl;

    if (SolveAgain()) {
        DoFirstTask();
    }
}

void DoSecondTask() {
    double a{};
    std::cout << "\nВведите число a." << std::endl;
    std::cin >> a;

    double answer = 1;

    if (a >= kPositiveNumbersBegin) {
        for (int i = kBeginingCycleIfPositiveA; i <= kEndingCycleIfPositiveA; i += kStepCycleIfPositiveA) {
            answer *= i * i - a;
        }
    } else {
        for (int i = kBeginingCycleIfNegativeA; i <= kEndingCycleIfNegativeA; i += kStepCycleIfNegativeA) {
            answer *= i * i - kStepCycleIfNegativeA;
        }
    }

    std::cout << "S = " << answer << std::endl;

    if (SolveAgain()) {
        DoSecondTask();
    }
}

void DoThirdTask() {
    if (SolveAgain()) {
        DoThirdTask();
    }
}

void DoFourthTask() {
    if (SolveAgain()) {
        DoFourthTask();
    }
}

void TaskSelection() {
    std::cout << "\nВведите номер задания (цифру от 1 до 4 включительно), которое хотите решить.\n"
                 "Чтобы завершить программу, напишите 'e'."
              << std::endl;

    char taskNumber{};
    std::cin >> taskNumber;

    if (taskNumber == kFirstTaskSymbol) {
        DoFirstTask();
    } else if (taskNumber == kSecondTaskSymbol) {
        DoSecondTask();
    } else if (taskNumber == kThirdTaskSymbol) {
        DoThirdTask();
    } else if (taskNumber == kFourthTaskSymbol) {
        DoFourthTask();
    } else if (taskNumber == kExitProgramSymbol) {
        return;
    } else {
        std::cout << "\nНеверный ввод, попробуйте заново.\n" << std::endl;
        TaskSelection();
    }
}

int main(int, char**) {
    TaskSelection();

    return 0;
}
