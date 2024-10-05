#ifndef LAB3_HPP
#define LAB3_HPP

namespace lab3 {
enum class Symbols : char;

[[nodiscard]] int SetPrecision();
[[nodiscard]] double SetCoefficient();

void PrintAnswer(double x, int precision, double coefficient, int steps);

void CalculateIterativeMethod(int precision, double coefficient);
void CalculateHalfDivisionMethod(int precision, double coefficient);
void CalculateNewtonsMethod(int precision, double coefficient);

[[nodiscard]] bool ContinueInput(char symbol);

void PrintMenu();
}  // namespace lab3

#endif
