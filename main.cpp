#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const char kFirstTask = '1';
const char kSecondTask = '2';
const char kThirdTask = '3';
const char kFourthTask = '4';
const char kExitProgram = 'e';
const char kContinueProgram = 'y';

const int kFive = 5;
const int kTwo = 2;

const int kLoopNotNegativeABegin = 2;
const int kLoopNotNegativeAEnd = 8;
const int kLoopStepNotNegativeA = 2;
const int kLoopNegativeABegin = 3;
const int kLoopNegativeAEnd = 9;
const int kLoopStepNegativeA = 3;

const int kColumnWidth = 12;
const int kPrecision = 6;

const double kXStep = 0.2;

const double kEpsilon = 1e-6;

const int kThreeSummands = 3;
const int kFiveSummands = 5;
const int kTenSummands = 10;
}  // namespace

void DoFirstTask() {
    int n{};
    int m{};
    std::cout << "\nВведите натуральные числа n и m (m < n) через проблел." << std::endl;
    std::cin >> n >> m;

    if (m >= n || n <= 0 || m <= 0) {
        std::cout << "Неверный ввод. Число m должно быть маньше числа n. Также оба числа дожны быть натуральными." << std::endl;
        return;
    }

    int answer = 0;

    for (int i = 0; i <= n; i += kFive) {
        if (i % m != 0) {
            answer += i;
        }
    }

    std::cout << "\nСумма натуральных чисел, делящихся на 5 и не делящихся на " << m
              << " одновременно, "
                 "на отрезке от 1 до "
              << n << " равна " << answer << "." << std::endl;
}

void DoSecondTask() {
    double a{};
    std::cout << "\nВведите число a." << std::endl;
    std::cin >> a;

    double answer = 1;

    if (a >= 0) {
        for (int i = kLoopNotNegativeABegin; i <= kLoopNotNegativeAEnd; i += kLoopStepNotNegativeA) {
            answer *= std::pow(i, 2);
        }
        answer -= a;
    } else {
        for (int i = kLoopNegativeABegin; i <= kLoopNegativeAEnd; i += kLoopStepNegativeA) {
            answer *= (i - kTwo);
        }
    }

    std::cout << "S = " << answer << std::endl;
}

void DoThirdTask() {
    std::cout << std::setw(kColumnWidth) << "x" << std::setw(kColumnWidth) << "Y(x)" << std::setw(kColumnWidth) << "S(x)" << std::setw(kColumnWidth)
              << "N" << std::endl;

    double x = 0;
    while (x <= 1.) {
        int n = 0;
        double y = std::pow(x, 2) * std::atan(x);

        double currentSummand = std::pow(x, 3);
        double s = currentSummand;

        while (std::abs(currentSummand) >= kEpsilon) {
            currentSummand *= (-std::pow(x, 2) * (2 * n + 1) / (2 * n + 3));
            s += currentSummand;
            ++n;
        }

        std::cout << std::setw(kColumnWidth) << x << std::setw(kColumnWidth) << std::setprecision(kPrecision) << y << std::setw(kColumnWidth)
                  << std::setprecision(kPrecision) << s << std::setw(kColumnWidth) << n << std::endl;

        x += kXStep;
    }
}

void DoFourthTask() {
    int n{};
    std::cout << "\nВведите натуральное число n." << std::endl;
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Неверный ввод. Число n должно быть натуральным." << std::endl;
        return;
    }

    int k = n * 2 + 1;
    double y = std::sqrt(k * 1.0);
    int summandsCounter = 1;
    std::cout << y << std::endl;

    while (k > 1) {
        /*if (n + 1 - summandsCounter == 3) {
            std::cout << "Промежуточный результат при 3 слагаемых:\ny = " << y << std::endl;
        } else if (summandsCounter == kFiveSummands) {
            std::cout << "Промежуточный результат при 5 слагаемых:\ny = " << y << std::endl;
        } else if (summandsCounter == kTenSummands) {
            std::cout << "Промежуточный результат при 10 слагаемых:\ny = " << y << std::endl;
        }*/

        k -= 2;
        ++summandsCounter;
        y = std::sqrt(k + y);
        std::cout << y << std::endl;
    }

    std::cout << "Итоговый результат:\ny = " << y << std::endl;
}

int main(int, char**) {
    while (true) {
        std::cout << "\nВведите номер задания (цифру от 1 до 4 включительно), которое хотите решить.\n"
                     "Чтобы завершить программу, напишите 'e'."
                  << std::endl;

        char taskNumber{};
        std::cin >> taskNumber;

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
    }

    return 0;
}
