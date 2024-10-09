#ifndef THIRD_LAB_CODE_H
#define THIRD_LAB_CODE_H

namespace lab3 {
enum class Symbols : char {
    IterativeMethod = '1',
    HalfDivisionMethod = '2',
    NewtonsMethod = '3',
    Exit = 'e'
};

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
