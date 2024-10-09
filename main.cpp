#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const char kFirstTask = '1';
const char kSecondTask = '2';
const char kThirdTask = '3';
const char kFourthTask = '4';
const char kExitProgram = 'e';

const int kTwo = 2;
const int kThree = 3;
const int kFive = 5;
const int kTen = 10;

const int kLoopNonNegativeABegin = 2;
const int kLoopNonNegativeAEnd = 8;
const int kLoopStepNonNegativeA = 2;
const int kLoopNegativeABegin = 3;
const int kLoopNegativeAEnd = 9;
const int kLoopStepNegativeA = 3;

const int kColumnWidth = 12;
const int kPrecision = 6;

const double kXStep = 0.2;

const double kEpsilon = 1e-6;
}  // namespace

void DoFirstTask() {
    int n{};
    int m{};
    std::cout << "\nВведите натуральные числа n и m (m < n) через проблел." << std::endl;
    std::cin >> n >> m;

    if (n <= 0) {
        std::cout << "Неверный ввод. Число n должно быть натуральным." << std::endl;
        return;
    }
    if (m <= 0) {
        std::cout << "Неверный ввод. Число m должно быть натуральным." << std::endl;
        return;
    }
    if (m >= n) {
        std::cout << "Неверный ввод. Число m должно быть меньше числа n." << std::endl;
        return;
    }

    int answer = 0;

    for (int i = 0; i <= n; i += kFive) {
        if (i % m != 0) {
            answer += i;
        }
    }

    std::cout << "\nСумма натуральных чисел, делящихся на 5 и не делящихся на " << m << " одновременно, на отрезке от 1 до " << n << " равна "
              << answer << "." << std::endl;
}

void DoSecondTask() {
    double a{};
    std::cout << "\nВведите число a." << std::endl;
    std::cin >> a;

    double answer = 1.0;

    if (a >= 0) {
        for (int i = kLoopNonNegativeABegin; i <= kLoopNonNegativeAEnd; i += kLoopStepNonNegativeA) {
            answer *= std::pow(i, 2);
        }
        answer -= a;
    } else {
        for (int i = kLoopNegativeABegin; i <= kLoopNegativeAEnd; i += kLoopStepNegativeA) {
            answer *= (i - kTwo);
        }
    }

    std::cout << "S = " << std::setprecision(kTen) << answer << std::endl;
}

void DoThirdTask() {
    std::cout << std::setw(kColumnWidth) << "x" << std::setw(kColumnWidth) << "Y(x)" << std::setw(kColumnWidth) << "S(x)" << std::setw(kColumnWidth)
              << "N" << std::endl;

    double x = 0.;
    while (x <= 1.) {
        int n = 0;
        double y = std::pow(x, 2) * std::atan(x);

        double currentSummand = std::pow(x, 3);
        double s = currentSummand;

        while (std::fabs(currentSummand) >= kEpsilon) {
            currentSummand *= (-std::pow(x, 2) * (2 * n + 1) / (2 * n + 3));
            s += currentSummand;
            ++n;
        }

        std::cout << std::fixed << std::setw(kColumnWidth) << x << std::fixed << std::setw(kColumnWidth) << std::setprecision(kPrecision) << y
                  << std::fixed << std::setw(kColumnWidth) << std::setprecision(kPrecision) << s << std::setw(kColumnWidth) << n << std::endl;

        x += kXStep;
    }
}

double SolveFourthTaskFunction(int n) {
    int k = 2 * n + 1;
    double y = std::sqrt(k);
    while (k > 1) {
        k -= 2;
        y = std::sqrt(k + y);
    }
    return y;
}

void DoFourthTask() {
    int n{};
    std::cout << "\nВведите натуральное число n." << std::endl;
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Неверный ввод. Число n должно быть натуральным" << std::endl;
        exit(1);
    }

    for (int i = 1; i < n; ++i) {
        if (i == kThree || i == kFive || i == kTen) {
            std::cout << "y(" << i << ") = " << SolveFourthTaskFunction(i) << std::endl;
        }
    }

    std::cout << "y(" << n << ") = " << SolveFourthTaskFunction(n) << std::endl;
}

int main(int, char**) {
    char continueExecution = 'y';
    char taskNumber{};
    bool flag = false;

    while (true) {
        if (!flag) {
            std::cout << "\nВведите номер задания (цифру от 1 до 4 включительно), которое хотите решить.\n"
                         "Чтобы завершить программу, напишите 'e'.\nСписок заданий:\n\t1. Находит сумму натуральных чисел от 1 до n,"
                         " которые делятся на 5 и не делятся на m.\n\t2. Вычисляет S - произведение всех i от i = 2 до i = 8 с шагом 2 за вычетом"
                         " параметра а, ели а >= 0,\n\t   иначе S - произведение всех (i - 2) начиная с i = 3 до i = 9 с шагом 3.\n\t"
                         "3. Вычисляет значение S(x) = x^3 - x^5/3 + ... + (-1)^n * x^(2n+3)/(2n + 1), где 0 <= x <= 1 с шагом 0.2.\n\t"
                         "4. Вычисляет значение у по формуле у = sqrt(1 + sqrt(3 + sqrt(5 + ... + sqrt(2n + 1))))."
                      << std::endl;

            std::cin >> taskNumber;
        }

        switch (taskNumber) {
            case kFirstTask:
                DoFirstTask();
                break;
            case kSecondTask:
                DoSecondTask();
                break;
            case kThirdTask:
                DoThirdTask();
                break;
            case kFourthTask:
                DoFourthTask();
                break;
            case kExitProgram:
                return 0;
            default:
                std::cout << "\nНеверный ввод." << std::endl;
                return 1;
        }

        std::cout << "\nПродолжить работу? (y/n)" << std::endl;
        std::cin >> continueExecution;

        if (continueExecution == 'y') {
            flag = true;
        } else if (continueExecution == 'n') {
            flag = false;
        } else {
            std::cout << "\nНеверный ввод." << std::endl;
            return 1;
        }
    }

    return 0;
}
