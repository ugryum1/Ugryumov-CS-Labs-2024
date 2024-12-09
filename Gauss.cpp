#include "Gauss.hpp"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

std::vector<std::vector<double>> create_unit_matrix(int n) {
    std::vector<std::vector<double>> unit_matrix(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        unit_matrix[i][i] = 1.0;
    }

    return unit_matrix;
}

std::vector<std::vector<double>> merging_matrices(std::vector<std::vector<double>> &matrix, std::vector<std::vector<double>> &inverse_matrix, int n) {
    std::vector<std::vector<double>> result(n, std::vector<double>(2 * n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < 2 * n; ++j) {
            if (j < n) {
                result[i][j] = matrix[i][j];
            } else {
                result[i][j] = inverse_matrix[i][j - n];
            }
        }
    }

    return result;
}

void print_matrix(std::vector<std::vector<double>> &matrix, int n, int m) {
    int k = 0;
    int precision = 6;
    int columnWidth = precision + 6;
    int columnNumber = 80 / columnWidth;
    while (k < m) {
        for (int i = 0; i < n; ++i) {
            for (int j = k; j < k + columnNumber; ++j) {
                if (j < m) {
                    std::cout << std::fixed << std::setw(columnWidth) << std::setprecision(precision) << matrix[i][j];
                } else {
                    break;
                }
            }
            std::cout << std::endl;
        }

        k += columnNumber;

        if (k < m) {
            for (int i = 0; i < 80; ++i) {
                std::cout << "-";
            }
            std::cout << std::endl;
        }
    }

    std::cout.unsetf(std::ios_base::fixed);
}

std::vector<std::vector<double>> multiply_matrices(std::vector<std::vector<double>> &matrix, std::vector<std::vector<double>> &inverse_matrix, int n)
{
    std::vector<std::vector<double>> result(n, std::vector<double>(n, 0.0));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            for (int k = 0; k < n; ++k) {
                result[i][j] += matrix[i][k] * inverse_matrix[k][j];
            }
        }
    }

    return result;
}

void straignt_step(std::vector<std::vector<double>> &matrix, std::vector<std::vector<double>> &inverse_matrix, std::vector<double> &x, int n) {
    for (int i = 0; i < n; ++i) {
        if (matrix[i][i] == 0) {
            bool foundNonZeroRow = false;
            for (int k = i + 1; k < n; ++k) {
                if (matrix[k][i] != 0) {
                    std::swap(matrix[i], matrix[k]);
                    foundNonZeroRow = true;
                    break;
                }
            }
            if (!foundNonZeroRow) {
                std::cout << "\nОбратная матрица не существует." << std::endl;
                exit(0);
            }
        }
    }

    for (int i = 0; i < n - 1; ++i) {
        double coeff = matrix[i][i];
        for (int j = 0; j < n; ++j) {
            matrix[i][j] /= coeff;
            inverse_matrix[i][j] /= coeff;
        }
        x[i] /= coeff;

        for (int j = i + 1; j < n; ++j) {
            coeff = matrix[j][i];
            for (int k = 0; k < n; ++k) {
                matrix[j][k] -= coeff * matrix[i][k];
                inverse_matrix[j][k] -= coeff * inverse_matrix[i][k];
            }
            x[j] -= coeff * x[i];
        }
    }

    for (int i = 0; i < n; ++i) {
        inverse_matrix[n - 1][i] /= matrix[n - 1][n - 1];
    }
    x[n - 1] /= matrix[n - 1][n - 1];
    matrix[n - 1][n - 1] = 1.0;
}

void reverse_step(std::vector<std::vector<double>> &matrix, std::vector<std::vector<double>> &inverse_matrix, std::vector<double> &x, int n) {
    for (int i = n - 1; i > 0; --i) {
        for (int j = i - 1; j >= 0; --j) {
            double coeff = matrix[j][i];
            for (int k = 0; k < n; ++k) {
                matrix[j][k] -= coeff * matrix[i][k];
                inverse_matrix[j][k] -= coeff * inverse_matrix[i][k];
            }
            x[j] -= coeff * x[i];
        }
    }
}

int main() {
    std::cout << "Введите целое число - размер матрицы." << std::endl;
    int n{};
    std::cin >> n;

    std::cout << "Введите матрицу размером " << n << "*" << n << "." << std::endl;
    std::vector<std::vector<double>> matrix(n, std::vector<double>(n, 0.0));
    std::vector<std::vector<double>> original_matrix(n, std::vector<double>(n, 0.0));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            std::cin >> matrix[i][j];
            original_matrix[i][j] = matrix[i][j];
        }
    }

    std::cout << "\nВведите n чисел - правые части матричных уравнений." <<std::endl;
    std::vector<double> x(n, 0);
    for (int i = 0; i < n; ++i) {
        std::cin >> x[i];
    }

    std::vector<std::vector<double>> inverse_matrix = create_unit_matrix(n);

    std::cout << "\nИсходная матрица:" << std::endl;
    std::vector<std::vector<double>> extended_matrix = merging_matrices(matrix, inverse_matrix, n);
    print_matrix(extended_matrix, n, 2 * n);

    straignt_step(matrix, inverse_matrix, x, n);
    std::cout << "\nМатрица после прямого хода:" << std::endl;
    extended_matrix = merging_matrices(matrix, inverse_matrix, n);
    print_matrix(extended_matrix, n, 2 * n);

    reverse_step(matrix, inverse_matrix, x, n);
    std::cout << "\nМатрица после обратного хода:" << std::endl;
    extended_matrix = merging_matrices(matrix, inverse_matrix, n);
    print_matrix(extended_matrix, n, 2 * n);

    std::cout << "\nМатрица, обратная исходной:" << std::endl;
    print_matrix(inverse_matrix, n, n);

    std::cout << "\nРезультат умножения прямой матрицы на обратную:" << std::endl;
    std::vector<std::vector<double>> multyply_matrix = multiply_matrices(original_matrix, inverse_matrix, n);
    print_matrix(multyply_matrix, n, n);

    std::cout << "\nРешение системы линейных алгебраических уравнений:" << std::endl;
    for (int i = 0; i < n; ++i) {
        std::cout << "x" << i + 1 << " = " << std::fixed << std::setprecision(6) << x[i] << std::endl;
    }

    return 0;
}
