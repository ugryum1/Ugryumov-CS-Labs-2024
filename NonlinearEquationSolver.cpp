#include "NonlinearEquationSolver.h"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <limits>

namespace {
const int kMaxSteps = 1e5;
const double kMaxDifferenceX = 0.01;

[[nodiscard]] double CalculateFunction(double x, double coefficient) {
    return x - coefficient * std::cos(x);
}

[[nodiscard]] double CalculateFunctionDerivative(double x, double coefficient) {
    return 1 + coefficient * std::sin(x);
}

[[nodiscard]] double ReadAccuracyFromStdin() {
    std::cout << "С какой погрешностью считать? Введите число с плавающей точкой в интервале от 0 до 1, "
                 "либо в виде 1e-n, где n - желаемое количество знаков ответа после запятой."
              << std::endl;

    double accuracy{};
    std::cin >> accuracy;

    return accuracy;
}

[[nodiscard]] double ReadCoefficientFromStdin() {
    std::cout << "Введите коэффициент a уравнения x - a*cos(x) = 0." << std::endl;

    double coefficient{};
    std::cin >> coefficient;

    return coefficient;
}

void PrintAnswer(double x, double coefficient, double accuracy, int iterations, NonlinearEquationSolver::EquationMethod method) {
    if (x == std::numeric_limits<double>::infinity()) {
        std::cout << "Не получилось найти корень данным методом за 1e5 операций." << std::endl;
        return;
    }

    int precision = static_cast<int>(-std::log10(accuracy));

    std::cout << "\nКорень уравнения x " << (coefficient < 0 ? "+ " : "- ") << std::resetiosflags(std::ios::fixed) << std::fabs(coefficient)
              << "cos(x) = 0";

    std::cout << ":\tx = " << std::fixed << std::setprecision(precision) << x;
    std::cout << "\nНайдено с погреностью 10^-" << precision << " методом ";

    switch (method) {
        case NonlinearEquationSolver::EquationMethod::Iterative:
            std::cout << "простых итераций.";
            break;
        case NonlinearEquationSolver::EquationMethod::HalfDivision:
            std::cout << "половинного деления.";
            break;
        case NonlinearEquationSolver::EquationMethod::Newton:
            std::cout << "Ньютона.";
            break;
    }

    std::cout << "\nКоличество шагов: " << iterations << ".\n\n";
}
}  // namespace

namespace NonlinearEquationSolver {
void SolveIterativeMethod() {
    double coefficient = ReadCoefficientFromStdin();
    double accuracy = ReadAccuracyFromStdin();
    int iterations{};
    double x = CalculateIterativeMethod(coefficient, accuracy, iterations);

    PrintAnswer(x, coefficient, accuracy, iterations, EquationMethod::Iterative);
}

void SolveHalfDivisionMethod() {
    double coefficient = ReadCoefficientFromStdin();
    double accuracy = ReadAccuracyFromStdin();

    int iterations{};

    std::cout << "Введите через пробел два числа - диапазон, в котором искать ответ." << std::endl;
    double left{};
    double right{};
    std::cin >> left >> right;

    if (left >= right) {
        std::cout << "Неверный ввод. Левая граница диапазона должна быть меньше правой.\n\n";
        return;
    }

    if ((CalculateFunction(left, coefficient) < 0. && CalculateFunction(right, coefficient) < 0.) ||
        (CalculateFunction(left, coefficient) > 0. && CalculateFunction(right, coefficient) > 0.)) {
        std::cout << "В данном диапазоне нет корней или они не могут быть найдены данным методом.\n\n";
        return;
    }

    double x = CalculateHalfDivisionMethod(coefficient, accuracy, left, right, iterations);

    if (x == std::numeric_limits<double>::infinity()) {
        std::cout << "Левая граница должна быть меньше правой.\n\n";
        return;
    }

    PrintAnswer(x, coefficient, accuracy, iterations, EquationMethod::HalfDivision);
}

void SolveNewtonMethod() {
    double coefficient = ReadCoefficientFromStdin();
    double accuracy = ReadAccuracyFromStdin();
    int iterations{};
    double x = CalculateNewtonMethod(coefficient, accuracy, iterations);

    PrintAnswer(x, coefficient, accuracy, iterations, EquationMethod::Newton);
}

[[nodiscard]] double CalculateIterativeMethod(double coefficient, double accuracy, int& iterations) {
    double x = coefficient;
    double previousX{};
    iterations = 0;

    while (std::fabs(CalculateFunction(x, coefficient)) > accuracy && iterations < kMaxSteps) {
        ++iterations;
        previousX = x;
        x -= CalculateFunction(x, coefficient);
    }

    if (std::fabs(x - previousX) > kMaxDifferenceX) {
        x = std::numeric_limits<double>::infinity();
    }

    return x;
}

[[nodiscard]] double CalculateHalfDivisionMethod(double coefficient, double accuracy, double left, double right, int& iterations) {
    if (left >= right) {
        return std::numeric_limits<double>::infinity();
    }

    double middle{};
    iterations = 0;

    while (right - left > accuracy) {
        ++iterations;
        middle = (left + right) / 2;

        if ((CalculateFunction(right, coefficient) > 0 && CalculateFunction(middle, coefficient) < 0) ||
            (CalculateFunction(right, coefficient) < 0 && CalculateFunction(middle, coefficient) > 0)) {
            left = middle;
        } else {
            right = middle;
        }
    }

    return (left + right) / 2;
}

[[nodiscard]] double CalculateNewtonMethod(double coefficient, double accuracy, int& iterations) {
    double x = coefficient;
    double previousX{};
    iterations = 0;

    while (std::fabs(CalculateFunction(x, coefficient)) > accuracy && iterations != kMaxSteps) {
        ++iterations;
        previousX = x;
        x -= CalculateFunction(x, coefficient) / CalculateFunctionDerivative(x, coefficient);
    }

    if (std::fabs(x - previousX) > kMaxDifferenceX) {
        x = std::numeric_limits<double>::infinity();
    }

    return x;
}

void SelectMethod(EquationMethod task) {
    switch (task) {
        case EquationMethod::Iterative:
            SolveIterativeMethod();
            break;
        case EquationMethod::HalfDivision:
            SolveHalfDivisionMethod();
            break;
        case EquationMethod::Newton:
            SolveNewtonMethod();
            break;
        default:
            std::cout << "Неверный ввод метода." << std::endl;
            break;
    }
}

void ExecuteApp() {
    char continueExecution = 'y';
    while (continueExecution == 'y') {
        std::cout << "Введите номер метода (число от 1 до 3), которым хотите решить задачу."
                     "\n\t1. Итерационный метод\n\t2. Метод половинного деления\n\t3. Метод Ньютона"
                  << std::endl;
        int methodNumber{};
        std::cin >> methodNumber;

        SelectMethod(static_cast<EquationMethod>(methodNumber));

        std::cout << "Продолжить работу? (y/n)" << std::endl;
        std::cin >> continueExecution;
        if (continueExecution == 'y') {
            std::cout << std::endl;
        }
    }
}
}  // namespace NonlinearEquationSolver
