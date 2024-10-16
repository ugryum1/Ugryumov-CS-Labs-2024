#ifndef THIRD_LAB_CODE_H
#define THIRD_LAB_CODE_H

namespace SolvingFunction {
enum class Method : int {
    IterativeMethod = 1,
    HalfDivisionMethod = 2,
    NewtonsMethod = 3,
};

void InputOutputIterativeMethod();
void InputOutputHalfDivisionMethod();
void InputOutputNewtonMethod();

void CalculateIterativeMethod(double accuracy, double coefficient, int& steps, double& x);
void CalculateHalfDivisionMethod(double accuracy, double coefficient, int& steps, double& left, double& right);
void CalculateNewtonMethod(double accuracy, double coefficient, int& steps, double& x);

void SelectMethod(Method task);

void TaskApp();
}  // namespace SolvingFunction

#endif
