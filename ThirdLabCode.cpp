#include "ThirdLabCode.h"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kTen = 10;
const double kHalf = 0.5;

[[nodiscard]] double FunctionCondition(double x, double coefficient) {
    return x - coefficient * std::cos(x);
}

[[nodiscard]] double FunctionDerivative(double x, double coefficient) {
    return 1 + coefficient * std::sin(x);
}

[[nodiscard]] double SetPrecision() {
    std::cout << "С какой погрешностью считать? Введите число с плавающей точкой в интервале от 0 до 1, "
                 "либо в виде 1e-n, где n - желаемое количество знаков ответа после запятой."
              << std::endl;

    double precision{};
    std::cin >> precision;

    if (precision <= 0 || precision >= 1) {
        std::cout << "Неверный ввод." << std::endl;
        exit(1);
    }
    return precision;
}

[[nodiscard]] double SetCoefficient() {
    std::cout << "Задать коэффициент a уравнения x - a*cos(x) = 0? (y/n)" << std::endl;

    char choice{};
    std::cin >> choice;

    if (choice == 'y') {
        std::cout << "Введите коэффициент a уравнения x - a*cos(x) = 0." << std::endl;

        double coefficient{};
        std::cin >> coefficient;

        return coefficient;
    } else if (choice != 'n') {
        std::cout << "Неверный ввод." << std::endl;
        exit(1);
    }

    return 1.;
}

void PrintAnswer(double x, double precision, double coefficient, int steps, char method) {
    int accuracy = int(std::log10(1 / precision));

    std::cout << "\nКорень уравнения x ";

    if (coefficient == 1.) {
        std::cout << "- ";
    } else if (coefficient < 0) {
        std::cout << "+ " << std::fabs(coefficient);
    } else {
        std::cout << "- " << coefficient;
    }

    std::cout << "cos(x) = 0:\tx = " << std::fixed << std::setprecision(accuracy) << x << "\nНайдено с погреностью 10^-" << accuracy << " методом ";

    if (method == static_cast<char>(lab3::Symbols::IterativeMethod)) {
        std::cout << "простых итераций.";
    } else if (method == static_cast<char>(lab3::Symbols::HalfDivisionMethod)) {
        std::cout << "половинного деления.";
    } else {
        std::cout << "Ньютона.";
    }

    std::cout << "\nКоличество шагов: " << steps << ".\n\n";
}
}  // namespace

void lab3::CalculateIterativeMethod(double precision, double coefficient) {
    int steps{};
    double x = coefficient;

    while (std::fabs(FunctionCondition(x, coefficient)) > kHalf * precision) {
        ++steps;
        x -= FunctionCondition(x, coefficient);
    }

    PrintAnswer(x, precision, coefficient, steps, static_cast<char>(lab3::Symbols::IterativeMethod));
}

void lab3::CalculateHalfDivisionMethod(double precision, double coefficient) {
    int steps{};
    double left = -coefficient;
    double right = coefficient;
    double middle{};

    while (right - left > kHalf * precision) {
        ++steps;
        middle = (left + right) * kHalf;

        if (FunctionCondition(middle, coefficient) < 0) {
            left = middle;
        } else {
            right = middle;
        }
    }

    PrintAnswer(left, precision, coefficient, steps, static_cast<char>(lab3::Symbols::HalfDivisionMethod));
}

void lab3::CalculateNewtonsMethod(double precision, double coefficient) {
    double x = coefficient;
    int steps{};

    while (std::fabs(FunctionCondition(x, coefficient)) > kHalf * precision) {
        ++steps;
        x -= FunctionCondition(x, coefficient) / FunctionDerivative(x, coefficient);
    }

    PrintAnswer(x, precision, coefficient, steps, static_cast<char>(lab3::Symbols::NewtonsMethod));
}

[[nodiscard]] bool lab3::ContinueInput(char symbol) {
    switch (symbol) {
        case static_cast<char>(lab3::Symbols::IterativeMethod):
            lab3::CalculateIterativeMethod(SetPrecision(), SetCoefficient());
            break;
        case static_cast<char>(lab3::Symbols::HalfDivisionMethod):
            lab3::CalculateHalfDivisionMethod(SetPrecision(), SetCoefficient());
            break;
        case static_cast<char>(lab3::Symbols::NewtonsMethod):
            lab3::CalculateNewtonsMethod(SetPrecision(), SetCoefficient());
            break;
        default:
            std::cout << "Неверный ввод." << std::endl;
            return false;
    }
    return true;
}

void lab3::PrintMenu() {
    char continueEcecution = 'y';
    while (continueEcecution == 'y') {
        std::cout << "Введите номер метода (число от 1 до 3), которым хотите решить задачу."
                     "\n\t1. Итерационный метод\n\t2. Метод половинного деления\n\t3. Метод Ньютона"
                  << std::endl;
        char input{};
        std::cin >> input;

        if (!lab3::ContinueInput(input)) {
            return;
        }

        std::cout << "Продолжить работу? (y/n)" << std::endl;
        std::cin >> continueEcecution;
        if (continueEcecution == 'y') {
            std::cout << std::endl;
        } else if (continueEcecution != 'n') {
            std::cout << "Неверный ввод." << std::endl;
        }
    }
}
