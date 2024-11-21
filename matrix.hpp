#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <cstddef>

namespace integral {
struct I_print {
    const char* name;
    double i_sum;
    double i_toch;
    int n;
};

double IntRect(double f, int a, int b, double eps, int *n);
double IntTrap(double f, int a, int b, double eps, int *n);

void StartProgram();
}  // namespace integral


#endif  // MATRIX_HPP
