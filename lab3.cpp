#include <iostream>
#include <cmath>
#include <iomanip>

enum class Symbols: char {
    IterativeMethod = '1',
    HalfDivisionMethod = '2',
    NewtonsMethod = '3',
    Exit = 'e'
};

[[nodiscard]] int SetPrecision() {
    std::cout << "\nС какой погрешностью считать? Введите натуральное число - "
                    "это будет количество знаков числа-ответа после запятой."
                << std::endl;

    int n{};
    std::cin >> n;

    if (n <= 0) {
        std::cout << "Неверный ввод, число должно быть натуральным." << std::endl;
        //return 1;
        exit(1);
    } else {
        return n;
    }
}

[[nodiscard]] double SetCoefficient() {
    std::cout << "\nЗадать коэффициент a уравнения x - a*cos(x) = 0? (y/n)" << std::endl;

    char choice{};
    std::cin >> choice;

    if (choice == 'y') {
        std::cout << "\nВведите коэффициент a уравнения x - a*cos(x) = 0." << std::endl;

        double coefficient{};
        std::cin >> coefficient;

        return coefficient;
    } else if (choice != 'n') {
        std::cout << "Неверный ввод." <<std::endl;
        exit(1);
    }

    return 1.;
}

void PrintAnswer(double x, int precision, double coefficient) {
    std::cout << "\nКорень уравнения x ";
    if (coefficient == 1.) {
        std::cout << "- ";
    } else if (coefficient < 0) {
        std::cout << "+ " << std::abs(coefficient);
    } else {
        std::cout << "- " << coefficient;
    }
    std::cout << "cos(x) = 0:\tx = " << std::setprecision(precision) << x  << "\n\n";
}

void CalculateIterativeMethod() {
    int precision{};
    double coefficient{};
    double answer{};
    answer = 0.2532362362362343;
    precision = SetPrecision();
    coefficient = SetCoefficient();

    PrintAnswer(answer, precision, coefficient);
}

void CalculateHalfDivisionMethod() {
    int precision{};
    double coefficient{};
    double answer{};
    answer = 0.2532362362362343;
    precision = SetPrecision();
    coefficient = SetCoefficient();

    PrintAnswer(answer, precision, coefficient);
}

void CalculateNewtonsMethod() {
    int precision{};
    double coefficient{};
    double answer{};
    answer = 0.2532362362362343;
    precision = SetPrecision();
    coefficient = SetCoefficient();

    PrintAnswer(answer, precision, coefficient);
}

[[nodiscard]] bool ContinueInput(char symbol) {
    switch (symbol) {
        case static_cast<char>(Symbols::IterativeMethod):
            CalculateIterativeMethod();
            break;
        case static_cast<char>(Symbols::HalfDivisionMethod):
            CalculateHalfDivisionMethod();
            break;
        case static_cast<char>(Symbols::NewtonsMethod):
            CalculateNewtonsMethod();
            break;
        case static_cast<char>(Symbols::Exit):
            return false;
            break;
        default:
            std::cout << "Неверный ввод." << std::endl;
            exit(1);
    }
    return true;
}

void PrintMenu() {
    while (true) {
        std::cout << "Введите номер метода (число от 1 до 3), которым хотите решить задачу."
                     "\n\t1. Итерационный метод\n\t2. Метод половинного деления\n\t3. Метод Ньютона\n"
                     "Чтобы завершить программу, напишите 'e'."
                  << std::endl;
        char input{};
        std::cin >> input;

        if (!ContinueInput(input)) {
            return;
        }
    }
}
