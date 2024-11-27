#include "matrix.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <random>

namespace {
const int columnWidth = 16;

double **AllocateMatrix(int n, int m) {
  double **matrix = new double *[n];

  for (int i = 0; i < n; ++i) {
    matrix[i] = new double[m];
  }

  return matrix;
}

void DeleteMatrix(double **matrix, int n, int m) {
  if (matrix != nullptr) {
    for (int i = 0; i < n; ++i) {
      if (matrix[i] != nullptr) {
        delete[] matrix[i];
      }
    }
    delete[] matrix;
    matrix = nullptr;
  }
}

void PrintMatrix(double **matrix, int n, int m, int precision, int format) {
  if (format == 1) {
    std::cout << std::fixed;
  } else if (format == 2) {
    std::cout << std::scientific;
  }

  int k = 0;
  while (k < m) {
    for (int i = 0; i < n; ++i) {
      for (int j = k; j < k + 5; ++j) {
        if (j < m) {
          if (format == 1) {
            std::cout << std::setw(columnWidth) << std::setprecision(precision)
                      << matrix[i][j];
          } else {
            std::cout << std::setw(columnWidth) << matrix[i][j];
          }
        } else {
          break;
        }
      }
      std::cout << std::endl;
    }

    k += 5;

    std::cout << std::endl;
    for (int i = 0; i < 85; ++i) {
      if (k < m) {
        std::cout << "-";
      } else {
        std::cout << "=";
      }
    }
    std::cout << std::endl << std::endl;
  }

  if (format == 1) {
    std::cout.unsetf(std::ios_base::fixed);
  } else if (format == 2) {
    std::cout.unsetf(std::ios_base::scientific);
  }
}

void PrintMatrix(int *pointerB[], int size) {
  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      std::cout << std::fixed << std::setw(6) << *(pointerB[i] + j);
    }
    std::cout << std::endl;
  }

  std::cout.unsetf(std::ios_base::fixed);
  std::cout << std::endl;
}

} // namespace

namespace matrix {
using namespace matrix;

void FillMatrixA(double **A, int n, int m) {
  double x = 1.0;

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < m; ++j) {
      if (i == j) {
        A[i][j] = 1;
      } else if (i > j) {
        A[i][j] = std::pow(-x, i) / std::pow(std::tgamma(j + 1), i);
      } else {
        A[i][j] = std::pow(x, i) / std::pow(std::tgamma(j + 1), i);
      }
    }
  }
}

void FillMatrixB(int B[][10], int *pointerB[]) {
  for (int i = 0; i < 10; ++i) {
    for (int j = 0; j < 10; ++j) {
      B[i][j] = i * 10 + j;
    }
    pointerB[i] = B[i];
  }
}

void StartProgram() {
  std::cout << "В каком формате выводить матрицу? (1/2)\n\t1. С точностью "
               "precision (например, 0.0025)\n\t"
               "2. В экспоненциальном формате (например, 1.23E+10)\n";
  int format = 0;
  std::cin >> format;

  std::mt19937 gen(std::random_device{}());
  std::uniform_int_distribution<int> dist_n(8, 15);
  std::uniform_int_distribution<int> dist_m(8, 15);
  std::uniform_int_distribution<int> dist_precision(3, 8);

  int n = dist_n(gen);
  int m = dist_m(gen);
  int precision = dist_precision(gen);
  std::cout << "Количество строк матрицы N: " << n << std::endl
            << "Количество столбцов матрицы M: " << m << std::endl
            << "Точность вычисления (кол-во знаков после запятой): "
            << precision << std::endl
            << std::endl;

  double **A = AllocateMatrix(n, m);

  FillMatrixA(A, n, m);
  std::cout << "Матрица A:\n\n";
  PrintMatrix(A, n, m, precision, format);

  DeleteMatrix(A, n, m);

  int B[10][10];
  int *pointerB[10];
  FillMatrixB(B, pointerB);

  std::cout << "Матрица B:\n\n";
  PrintMatrix(pointerB, 10);

  std::cout
      << B << "  " << B[0] << "  " << B[2]
      << std::endl; // 1) Адрес матрицы  2) Адрес 0 строки  3) Адрес 2 строки
  std::cout << B[0][0] << "  " << **B << "  " << *B[0]
            << std::endl; // 1) B[0][0]        2) B[0][0]         3) B[0][0]
  std::cout << *(*(B + 1)) << "  " << *B[1]
            << std::endl; // 1) B[1][0]        2) B[1][0]
  std::cout << *(B[0] + 1) << "  " << *(*B + 1)
            << std::endl; // 1) B[0][1]        2) B[0][1]
  std::cout << B[0][20] << "  " << *(B[0] + 20) << "  " << *B[2]
            << std::endl; // 1) B[2][0]        2) B[2][0]         3) B[2][0]
}
} // namespace matrix
