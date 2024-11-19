#include "integralCalculation.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>

namespace {
double f1(double x) {
    return x;
}

double f2(double x) {
    return std::sin(22 * x);
}

double f3(double x) {
    return std::pow(x, 4);
}

double f4(double x) {
    return std::atan(x);
}

void PrintTabl(integral::I_print (&i_prn)[4], double eps) {
    std::cout << std::setw(12) << "Function" << std::setw(12) << "Integral" << std::setw(12) << "IntSum" << std::setw(12) << "N" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(12) << std::fixed << std::setprecision(6) << i_prn[i].name << std::setw(12) << std::fixed << std::setprecision(6)
                  << i_prn[i].i_toch << std::setw(12) << i_prn[i].i_sum << std::setw(12) << i_prn[i].n << std::endl;
    }
    std::cout << std::endl;
}
}  // namespace

namespace integral {
using namespace integral;

double IntRect(double (*f)(double), double a, double b, double eps, int& n) {
    double integral = 0.0;      // Начальное значение интеграла
    double prevIntegral = 0.0;  // Предыдущее значение интеграла
    n = 1;                      // Начинаем с одного шага
    double dx = b - a;          // Начальная ширина шага

    do {
        prevIntegral = integral;  // Сохраняем предыдущее значение интеграла

        integral = 0.0;  // Обнуляем текущий интеграл
        for (int i = 0; i < n; ++i) {
            double x = a + i * dx;  // Левая граница текущего прямоугольника
            integral += f(x) * dx;  // Добавляем площадь прямоугольника
        }

        n *= 2;   // Удваиваем количество шагов
        dx /= 2;  // Уменьшаем ширину шага вдвое
    } while (std::abs(integral - prevIntegral) > eps);

    return integral;
}

double IntTrap(double (*f)(double), double a, double b, double eps, int& n) {
    double integral = 0.0;
    double prevIntegral = 0.0;
    n = 1;
    double dx = b - a;

    do {
        prevIntegral = integral;

        integral = 0.0;
        for (int i = 0; i < n; ++i) {
            double x = a + i * dx;
            integral += (f(x) + f(x + dx)) * dx / 2;
        }

        n *= 2;
        dx /= 2;
    } while (std::abs(integral - prevIntegral) > eps);

    return integral;
}

void StartProgram() {
    std::mt19937 gen(std::random_device{}());
    std::uniform_real_distribution<double> dist_a(0.0, 1.0);
    std::uniform_real_distribution<double> dist_b(2.0, 3.0);

    double a = dist_a(gen);
    double b = dist_b(gen);
    std::cout << "Значение a: " << a << std::endl << "Значение b: " << b << std::endl << std::endl;

    double eps = 0.01;
    int n = 1;
    for (int i = 0; i < 5; ++i) {
        I_print i_prn[4];

        i_prn[0].name = "x";
        i_prn[0].i_toch = (b * b - a * a) / 2.0;
        i_prn[0].i_sum = IntRect(f1, a, b, eps, n);
        i_prn[0].n = n;

        i_prn[1].name = "sin(22x)";
        i_prn[1].i_toch = (std::cos(a * 22.0) - std::cos(b * 22.0)) / 22.0;
        i_prn[1].i_sum = IntRect(f2, a, b, eps, n);
        i_prn[1].n = n;

        i_prn[2].name = "x^4";
        i_prn[2].i_toch = (std::pow(b, 5) - std::pow(a, 5)) / 5.0;
        i_prn[2].i_sum = IntRect(f3, a, b, eps, n);
        i_prn[2].n = n;

        i_prn[3].name = "arctan(x)";
        i_prn[3].i_toch = b * std::atan(b) - a * std::atan(a) - (std::log(b * b + 1) - std::log(a * a + 1)) / 2.0;
        i_prn[3].i_sum = IntRect(f4, a, b, eps, n);
        i_prn[3].n = n;

        std::cout << "Метод прямоугольников. eps = " << std::resetiosflags(std::ios::fixed) << eps << std::endl;
        PrintTabl(i_prn, eps);

        i_prn[0].i_sum = IntTrap(f1, a, b, eps, n);
        i_prn[1].i_sum = IntTrap(f2, a, b, eps, n);
        i_prn[2].i_sum = IntTrap(f3, a, b, eps, n);
        i_prn[3].i_sum = IntTrap(f4, a, b, eps, n);

        std::cout << "Метод трапеций. eps = " << std::resetiosflags(std::ios::fixed) << eps << std::endl;
        PrintTabl(i_prn, eps);

        eps /= 10;
    }
}
}  // namespace integral
