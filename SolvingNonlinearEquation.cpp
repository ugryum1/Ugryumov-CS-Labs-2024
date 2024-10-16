#include "SolvingNonlinearEquation.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const double kTwo = 2.;
const double kAccuracy = 0.1;
const int kMaxSteps = 1e8;

[[nodiscard]] double CalculateFunction(double x, double coefficient) {
    return x - coefficient * std::cos(x);
}

[[nodiscard]] double CalculateFunctionDerivative(double x, double coefficient) {
    return 1 + coefficient * std::sin(x);
}

[[nodiscard]] double GetAccuracy() {
    std::cout << "С какой погрешностью считать? Введите число с плавающей точкой в интервале от 0 до 1, "
                 "либо в виде 1e-n, где n - желаемое количество знаков ответа после запятой."
              << std::endl;

    double accuracy{};
    std::cin >> accuracy;

    return accuracy;
}

[[nodiscard]] double GetCoefficient() {
    std::cout << "Введите коэффициент a уравнения x - a*cos(x) = 0." << std::endl;

    double coefficient{};
    std::cin >> coefficient;

    return coefficient;
}

void PrintAnswer(double x, double coefficient, double accuracy, int steps, SolvingNonlinearEquation::Method method) {
    int precision = int(std::log10(1 / accuracy));

    std::cout << "\nКорень уравнения x " << (coefficient < 0 ? "+ " : "- ");

    if (std::fabs(coefficient) != 1.) {
        std::cout << std::resetiosflags(std::ios::fixed) << std::fabs(coefficient);
    }
    std::cout << "cos(x) = 0";

    if (std::fabs(CalculateFunction(x, coefficient)) > kAccuracy) {
        if (method == SolvingNonlinearEquation::Method::HalfDivisionMethod) {
            std::cout << " не существует в заданном диапазоне или";
        }
        std::cout << " не найден за 10^8 операций." << std::endl;
        return;
    }

    std::cout << ":\tx = " << std::fixed << std::setprecision(precision) << x;
    std::cout << "\nНайдено с погреностью 10^-" << precision << " методом ";

    switch (method) {
        case SolvingNonlinearEquation::Method::IterativeMethod:
            std::cout << "простых итераций.";
            break;
        case SolvingNonlinearEquation::Method::HalfDivisionMethod:
            std::cout << "половинного деления.";
            break;
        default:
            std::cout << "Ньютона.";
            break;
    }

    std::cout << "\nКоличество шагов: " << steps << ".\n\n";
}
}  // namespace

[[nodiscard]] double SolvingNonlinearEquation::CalculateIterativeMethod(double coefficient, double accuracy, int& steps) {
    double x = coefficient;
    steps = 0;

    while (std::fabs(CalculateFunction(x, coefficient)) > accuracy && steps != kMaxSteps) {
        ++steps;
        x -= CalculateFunction(x, coefficient);
    }

    return x;
}

void SolvingNonlinearEquation::DoIterativeMethod() {
    double coefficient = GetCoefficient();
    double accuracy = GetAccuracy();
    int steps{};
    double x = SolvingNonlinearEquation::CalculateIterativeMethod(coefficient, accuracy, steps);

    PrintAnswer(x, coefficient, accuracy, steps, SolvingNonlinearEquation::Method::IterativeMethod);
}

[[nodiscard]] double SolvingNonlinearEquation::CalculateHalfDivisionMethod(double coefficient, double accuracy, int& steps, double left,
                                                                           double right) {
    double middle{};
    steps = 0;

    while (right - left > accuracy && steps != kMaxSteps) {
        ++steps;
        middle = (left + right) / kTwo;

        if (CalculateFunction(middle, coefficient) < 0) {
            left = middle;
        } else {
            right = middle;
        }
    }

    return left;
}

void SolvingNonlinearEquation::DoHalfDivisionMethod() {
    double coefficient = GetCoefficient();
    double accuracy = GetAccuracy();

    int steps{};

    std::cout << "Введите через пробел два числа - диапазон, в котором искать ответ." << std::endl;
    double left{};
    double right{};
    std::cin >> left >> right;

    if (left >= right) {
        std::cout << "Неверный ввод. Левая граница диапазона должна быть меньше правой.\n\n";
        return;
    }

    left = SolvingNonlinearEquation::CalculateHalfDivisionMethod(coefficient, accuracy, steps, left, right);

    PrintAnswer(left, coefficient, accuracy, steps, SolvingNonlinearEquation::Method::HalfDivisionMethod);
}

[[nodiscard]] double SolvingNonlinearEquation::CalculateNewtonMethod(double coefficient, double accuracy, int& steps) {
    double x = coefficient;
    steps = 0;

    while (std::fabs(CalculateFunction(x, coefficient)) > accuracy && steps != kMaxSteps) {
        ++steps;
        x -= CalculateFunction(x, coefficient) / CalculateFunctionDerivative(x, coefficient);
    }

    return x;
}

void SolvingNonlinearEquation::DoNewtonMethod() {
    double coefficient = GetCoefficient();
    double accuracy = GetAccuracy();
    int steps{};
    double x = SolvingNonlinearEquation::CalculateNewtonMethod(coefficient, accuracy, steps);

    PrintAnswer(x, coefficient, accuracy, steps, SolvingNonlinearEquation::Method::NewtonsMethod);
}

void SolvingNonlinearEquation::SelectMethod(Method task) {
    switch (task) {
        case SolvingNonlinearEquation::Method::IterativeMethod:
            SolvingNonlinearEquation::DoIterativeMethod();
            break;
        case SolvingNonlinearEquation::Method::HalfDivisionMethod:
            SolvingNonlinearEquation::DoHalfDivisionMethod();
            break;
        case SolvingNonlinearEquation::Method::NewtonsMethod:
            SolvingNonlinearEquation::DoNewtonMethod();
            break;
        default:
            std::cout << "Неверный ввод." << std::endl;
            break;
    }
}

void SolvingNonlinearEquation::TaskApp() {
    char continueEcecution = 'y';
    while (continueEcecution == 'y') {
        std::cout << "Введите номер метода (число от 1 до 3), которым хотите решить задачу."
                     "\n\t1. Итерационный метод\n\t2. Метод половинного деления\n\t3. Метод Ньютона"
                  << std::endl;
        int input{};
        std::cin >> input;

        SolvingNonlinearEquation::SelectMethod(static_cast<Method>(input));

        std::cout << "Продолжить работу? (y/n)" << std::endl;
        std::cin >> continueEcecution;
        if (continueEcecution == 'y') {
            std::cout << std::endl;
        }
    }
}
