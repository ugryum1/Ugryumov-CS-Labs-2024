#include "lab3.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>

namespace {
const int kTen = 10;
const double kHalf = 0.5;

[[nodiscard]] double ConditionFunction(double x, double coefficient) {
    return x - coefficient * std::cos(x);
}

[[nodiscard]] double FunctionDerivative(double x, double coefficient) {
    return 1 + coefficient * std::sin(x);
}
}  // namespace

enum class lab3::Symbols : char {
    IterativeMethod = '1',
    HalfDivisionMethod = '2',
    NewtonsMethod = '3',
    Exit = 'e'
};

[[nodiscard]] int lab3::SetPrecision() {
    std::cout << "\nС какой погрешностью считать? Введите натуральное число - "
                 "это будет количество знаков числа-ответа после запятой."
              << std::endl;

    int n{};
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Неверный ввод, число должно быть натуральным." << std::endl;
        exit(1);
    } else {
        return n;
    }
}

[[nodiscard]] double lab3::SetCoefficient() {
    std::cout << "\nЗадать коэффициент a уравнения x - a*cos(x) = 0? (y/n)" << std::endl;

    char choice{};
    std::cin >> choice;

    if (choice == 'y') {
        std::cout << "\nВведите коэффициент a уравнения x - a*cos(x) = 0." << std::endl;

        double coefficient{};
        std::cin >> coefficient;

        return coefficient;
    } else if (choice != 'n') {
        std::cout << "Неверный ввод." << std::endl;
        exit(1);
    }

    return 1.;
}

void lab3::PrintAnswer(double x, int precision, double coefficient, int steps) {
    std::cout << "\nКорень уравнения x ";
    if (coefficient == 1.) {
        std::cout << "- ";
    } else if (coefficient < 0) {
        std::cout << "+ " << std::abs(coefficient);
    } else {
        std::cout << "- " << coefficient;
    }
    std::cout << "cos(x) = 0:\tx = " << std::fixed << std::setprecision(precision) << x << "\nНайдено с погреностью 10^-" << precision << " за "
              << steps << " шагов.\n\n";
}

void lab3::CalculateIterativeMethod(int precision, double coefficient) {
    int steps{};
    double x{};
    x = coefficient;

    while (std::fabs(ConditionFunction(x, coefficient)) > kHalf * std::pow(kTen, -precision)) {
        ++steps;
        x -= ConditionFunction(x, coefficient);
    }

    lab3::PrintAnswer(x, precision, coefficient, steps);
}

void lab3::CalculateHalfDivisionMethod(int precision, double coefficient) {
    int steps{};
    double left = -coefficient;
    double right = coefficient;
    double middle{};

    while (right - left > kHalf * std::pow(kTen, -precision)) {
        ++steps;
        middle = (left + right) * kHalf;

        if (ConditionFunction(middle, coefficient) < 0) {
            left = middle;
        } else {
            right = middle;
        }
    }

    lab3::PrintAnswer(left, precision, coefficient, steps);
}

void lab3::CalculateNewtonsMethod(int precision, double coefficient) {
    double x{};
    int steps{};
    x = coefficient;

    while (std::fabs(ConditionFunction(x, coefficient)) > kHalf * std::pow(kTen, -precision)) {
        ++steps;
        x -= ConditionFunction(x, coefficient) / FunctionDerivative(x, coefficient);
    }

    lab3::PrintAnswer(x, precision, coefficient, steps);
}

[[nodiscard]] bool lab3::ContinueInput(char symbol) {
    switch (symbol) {
        case static_cast<char>(lab3::Symbols::IterativeMethod):
            lab3::CalculateIterativeMethod(lab3::SetPrecision(), lab3::SetCoefficient());
            break;
        case static_cast<char>(lab3::Symbols::HalfDivisionMethod):
            lab3::CalculateHalfDivisionMethod(lab3::SetPrecision(), lab3::SetCoefficient());
            break;
        case static_cast<char>(lab3::Symbols::NewtonsMethod):
            lab3::CalculateNewtonsMethod(lab3::SetPrecision(), lab3::SetCoefficient());
            break;
        case static_cast<char>(lab3::Symbols::Exit):
            return false;
            break;
        default:
            std::cout << "Неверный ввод." << std::endl;
            exit(1);
    }
    return true;
}

void lab3::PrintMenu() {
    while (true) {
        std::cout << "Введите номер метода (число от 1 до 3), которым хотите решить задачу."
                     "\n\t1. Итерационный метод\n\t2. Метод половинного деления\n\t3. Метод Ньютона\n"
                     "Чтобы завершить программу, напишите 'e'."
                  << std::endl;
        char input{};
        std::cin >> input;

        if (!lab3::ContinueInput(input)) {
            return;
        }
    }
}
