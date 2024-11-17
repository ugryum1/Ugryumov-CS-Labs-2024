#include "integralCalculation.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdlib>
#include <fstream>
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

void PrintTabl(integral::I_print (&i_prn)[4]) {
    std::cout << std::setw(12) << "Function" << std::setw(12) << "Integral" << std::setw(12) << "IntSum" << std::setw(12) << "N" << std::endl;
    for (int i = 0; i < 4; ++i) {
        std::cout << std::setw(12) << i_prn[i].name << std::setw(12) << i_prn[i].i_toch << std::setw(12) << i_prn[i].i_sum << std::setw(12)
                  << i_prn[i].n << std::endl;
    }
    std::cout << std::endl;
}
}  // namespace

namespace integral {
using namespace integral;

double IntRect(double (*f)(double), double a, double b, double eps, int& n) {
    n = 1;
    double dx, sumNew, sum, x;
    sum = 1000;
    sumNew = 1005;
    while (std::abs(sumNew - sum) > eps) {
        sumNew = sum;
        x = a;
        dx = (b - a) / n;
        sum = 0;
        for (long long i = 0; i < n; i++) {
            sum += f(x + dx / 2);
            x += dx;
        }
        sum *= dx;
        n *= 2;
    }
    n = n / 4;
    return sum;
}

double IntTrap(double (*f)(double), double a, double b, double eps, int& n) {
    n = 2;
    double dx = (b - a) / n;
    double sum = 0, sumNew = 0;
    do {
        sumNew = sum;
        sum = 0;
        n *= 2;
        dx = (b - a) / n;
        for (size_t step = 0; step < n; step++) {
            double x1 = a + step * dx;
            double x2 = a + (step + 1) * dx;
            sum += 0.5 * (x2 - x1) * (f(x1) + f(x2));
        }
    } while (fabs(sumNew - sum) > eps);
    return sum;
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

        std::cout << "Метод прямоугольников. eps = " << eps << std::endl;
        PrintTabl(i_prn);

        i_prn[0].i_sum = IntTrap(f1, a, b, eps, n);
        i_prn[1].i_sum = IntTrap(f2, a, b, eps, n);
        i_prn[2].i_sum = IntTrap(f3, a, b, eps, n);
        i_prn[3].i_sum = IntTrap(f4, a, b, eps, n);

        std::cout << "Метод трапеций. eps = " << eps << std::endl;
        PrintTabl(i_prn);

        eps /= 10;
    }
}
}  // namespace integral
