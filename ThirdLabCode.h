#ifndef THIRD_LAB_CODE_H
#define THIRD_LAB_CODE_H

namespace lab3 {
enum class Symbols : char {
    IterativeMethod = '1',
    HalfDivisionMethod = '2',
    NewtonsMethod = '3',
};

void CalculateIterativeMethod(double precision, double coefficient);
void CalculateHalfDivisionMethod(double precision, double coefficient);
void CalculateNewtonsMethod(double precision, double coefficient);

[[nodiscard]] bool ContinueInput(char symbol);

void PrintMenu();
}  // namespace lab3

#endif
