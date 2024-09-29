#include <cmath>
#include <iomanip>
#include <iostream>

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

const double kBeginingCycleInThirdTask = 0;
const double kEndingCycleInThirdTask = 1;
const double kCycleStepInThirdTask = 0.2;

const int kColumnWidth = 10;   // ширина столбцов
const int kNumbersLength = 4;  // длина чисел

const double kErrorRate = 0.000001;  // погрешность

const int kThreeSummands = 3;
const int kFiveSummands = 5;
const int kTenSummands = 10;
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
    std::cout << std::setw(kColumnWidth) << "x" << std::setw(kColumnWidth) << "Y(x)" << std::setw(kColumnWidth) << "S(x)" << std::setw(kColumnWidth)
              << "N" << std::endl;

    for (double x = kBeginingCycleInThirdTask; x <= kEndingCycleInThirdTask; x += kCycleStepInThirdTask) {
        int n = 0;
        double y = pow(x, 2) * atan(x);
        double s{};
        /*double currentSummand{};*/
        double currentSummand = kErrorRate;  // величина текущего слагаемого

        while (currentSummand >= kErrorRate) {
            currentSummand = pow(-1, n) * pow(x, 2 * n + 3) / (2 * n + 1);
            s += currentSummand;
            ++n;
        }
        /*do {
            currentSummand = pow(-1, n) * pow(x, 2 * n + 3) / (2 * n + 1);
            s += currentSummand;
            ++n;
        } while (currentSummand >= kErrorRate);*/

        std::cout << std::setw(kColumnWidth) << x << std::setw(kColumnWidth) << std::setprecision(kNumbersLength) << y << std::setw(kColumnWidth)
                  << std::setprecision(kNumbersLength) << s << std::setw(kColumnWidth) << n << std::endl;
    }

    if (SolveAgain()) {
        DoThirdTask();
    }
}

void DoFourthTask() {
    int n{};
    std::cout << "\nВведите натуральное число n." << std::endl;
    std::cin >> n;
    n = n * 2 + 1;

    double y = sqrt(n);
    int summandsCounter = 1;

    while (n > 1) {
        n -= 2;
        ++summandsCounter;
        y = sqrt(n + y);

        if (summandsCounter == kThreeSummands) {
            std::cout << "Промежуточный результат при 3 слагаемых: y = " << y << std::endl;
        } else if (summandsCounter == kFiveSummands) {
            std::cout << "Промежуточный результат при 5 слагаемых: y = " << y << std::endl;
        } else if (summandsCounter == kTenSummands) {
            std::cout << "Промежуточный результат при 10 слагаемых: y = " << y << std::endl;
        }
    }

    std::cout << "Итоговый результат:\ny = " << y << std::endl;

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
