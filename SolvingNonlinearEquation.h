#ifndef THIRD_LAB_CODE_H
#define THIRD_LAB_CODE_H

namespace SolvingNonlinearEquation {
enum class Method : int {
    IterativeMethod = 1,
    HalfDivisionMethod = 2,
    NewtonsMethod = 3,
};

void DoIterativeMethod();
void DoHalfDivisionMethod();
void DoNewtonMethod();

[[nodiscard]] double CalculateIterativeMethod(double coefficient, double accuracy, int& steps);
[[nodiscard]] double CalculateHalfDivisionMethod(double coefficient, double accuracy, int& steps, double left, double right);
[[nodiscard]] double CalculateNewtonMethod(double coefficient, double accuracy, int& steps);

void SelectMethod(Method task);

void TaskApp();
}  // namespace SolvingNonlinearEquation

#endif
