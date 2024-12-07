#ifndef GAUSS_HPP
#define GAUSS_HPP

#include <vector>

void print_matrix(std::vector<std::vector<double>> &matrix, int n, int m);

void straignt_step(std::vector<std::vector<double>> &matrix, std::vector<std::vector<double>> &inverse_matrix, std::vector<double> &x, int n);
void reverse_step(std::vector<std::vector<double>> &matrix, std::vector<std::vector<double>> &inverse_matrix, std::vector<double> &x, int n);

#endif // GAUSS_HPP
