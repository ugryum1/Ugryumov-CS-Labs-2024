#include "SolvingFunction.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const double kTwo = 2.;
const double kAccuracy = 0.1;
const int kMaxSteps = 1e5;

[[nodiscard]] double CalculateFunction(double x, double coefficient) {
    return x - coefficient * std::cos(x);
}

[[nodiscard]] double CalculateFunctionDerivative(double x, double coefficient) {
    return 1 + coefficient * std::sin(x);
}

[[nodiscard]] double AccuracyEntering() {
    std::cout << "С какой погрешностью считать? Введите число с плавающей точкой в интервале от 0 до 1, "
                 "либо в виде 1e-n, где n - желаемое количество знаков ответа после запятой."
              << std::endl;

    double accuracy{};
    std::cin >> accuracy;

    return accuracy;
}

[[nodiscard]] double CoefficientEntering() {
    std::cout << "Задать коэффициент a уравнения x - a*cos(x) = 0? (y/n)" << std::endl;

    char input{};
    std::cin >> input;

    if (input == 'y') {
        std::cout << "Введите коэффициент a уравнения x - a*cos(x) = 0." << std::endl;

        double coefficient{};
        std::cin >> coefficient;

        return coefficient;
    }

    return 1.;
}

void PrintAnswer(double x, double accuracy, double coefficient, int steps, SolvingFunction::Method method) {
    int precision = int(std::log10(1 / accuracy));

    std::cout << "\nКорень уравнения x ";

    if (coefficient == 1.) {
        std::cout << "- ";
    } else if (coefficient < 0) {
        std::cout << "+ " << std::fabs(coefficient);
    } else {
        std::cout << "- " << coefficient;
    }

    std::cout << "cos(x) = 0:\tx = ";
    if (std::fabs(CalculateFunction(x, coefficient)) > kAccuracy) {
        std::cout << "не существует в заданном диапазоне." << std::endl;
        return;
    }
    std::cout << std::fixed << std::setprecision(precision) << x;
    std::cout << "\nНайдено с погреностью 10^-" << precision << " методом ";

    if (method == SolvingFunction::Method::IterativeMethod) {
        std::cout << "простых итераций.";
    } else if (method == SolvingFunction::Method::HalfDivisionMethod) {
        std::cout << "половинного деления.";
    } else {
        std::cout << "Ньютона.";
    }

    std::cout << "\nКоличество шагов: " << steps << ".\n\n";
}
}  // namespace

void SolvingFunction::CalculateIterativeMethod(double accuracy, double coefficient, int& steps, double& x) {
    steps = 0;
    while (std::fabs(CalculateFunction(x, coefficient)) > accuracy && steps != kMaxSteps) {
        ++steps;
        x -= CalculateFunction(x, coefficient);
    }
}

void SolvingFunction::InputOutputIterativeMethod() {
    double coefficient = CoefficientEntering();
    double accuracy = AccuracyEntering();
    int steps{};
    double x = coefficient;

    SolvingFunction::CalculateIterativeMethod(accuracy, coefficient, steps, x);

    PrintAnswer(x, accuracy, coefficient, steps, SolvingFunction::Method::IterativeMethod);
}

void SolvingFunction::CalculateHalfDivisionMethod(double accuracy, double coefficient, int& steps, double& left, double& right) {
    double middle{};

    while (right - left > accuracy && steps != kMaxSteps) {
        ++steps;
        middle = (left + right) / kTwo;

        if (CalculateFunction(middle, coefficient) < 0) {
            left = middle;
        } else {
            right = middle;
        }
    }
}

void SolvingFunction::InputOutputHalfDivisionMethod() {
    double coefficient = CoefficientEntering();
    double accuracy = AccuracyEntering();

    int steps{};

    std::cout << "Введите через пробел два числа - диапазон, в котором искать ответ." << std::endl;
    double left{};
    double right{};
    std::cin >> left >> right;

    SolvingFunction::CalculateHalfDivisionMethod(accuracy, coefficient, steps, left, right);

    PrintAnswer(left, accuracy, coefficient, steps, SolvingFunction::Method::HalfDivisionMethod);
}

void SolvingFunction::CalculateNewtonMethod(double accuracy, double coefficient, int& steps, double& x) {
    while (std::fabs(CalculateFunction(x, coefficient)) > accuracy  && steps != kMaxSteps) {
        ++steps;
        x -= CalculateFunction(x, coefficient) / CalculateFunctionDerivative(x, coefficient);
    }
}

void SolvingFunction::InputOutputNewtonMethod() {
    double coefficient = CoefficientEntering();
    double accuracy = AccuracyEntering();

    double x = coefficient;
    int steps{};

    SolvingFunction::CalculateNewtonMethod(accuracy, coefficient, steps, x);

    PrintAnswer(x, accuracy, coefficient, steps, SolvingFunction::Method::NewtonsMethod);
}

void SolvingFunction::SelectMethod(Method task) {
    switch (task) {
        case SolvingFunction::Method::IterativeMethod:
            SolvingFunction::InputOutputIterativeMethod();
            break;
        case SolvingFunction::Method::HalfDivisionMethod:
            SolvingFunction::InputOutputHalfDivisionMethod();
            break;
        case SolvingFunction::Method::NewtonsMethod:
            SolvingFunction::InputOutputNewtonMethod();
            break;
        default:
            std::cout << "Неверный ввод." << std::endl;
            break;
    }
}

void SolvingFunction::TaskApp() {
    char continueEcecution = 'y';
    while (continueEcecution == 'y') {
        std::cout << "Введите номер метода (число от 1 до 3), которым хотите решить задачу."
                     "\n\t1. Итерационный метод\n\t2. Метод половинного деления\n\t3. Метод Ньютона"
                  << std::endl;
        int input{};
        std::cin >> input;

SolvingFunction::SelectMethod(static_cast<Method>(input));

        std::cout << "Продолжить работу? (y/n)" << std::endl;
        std::cin >> continueEcecution;
        if (continueEcecution == 'y') {
            std::cout << std::endl;
        }
    }
}
