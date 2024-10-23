#ifndef NOLINEAR_EQUATION_SOLVER_H
#define NOLINEAR_EQUATION_SOLVER_H

namespace NonlinearEquationSolver {
enum class EquationMethod : int {
    Iterative = 1,
    HalfDivision = 2,
    Newton = 3,
};

void SolveIterativeMethod();
void SolveHalfDivisionMethod();
void SolveNewtonMethod();

[[nodiscard]] double CalculateIterativeMethod(double coefficient, double accuracy, int& iterations);
[[nodiscard]] double CalculateHalfDivisionMethod(double coefficient, double accuracy, double left, double right, int& iterations);
[[nodiscard]] double CalculateNewtonMethod(double coefficient, double accuracy, int& iterations);

void SelectMethod(EquationMethod task);

void ExecuteApp();
}  // namespace NonlinearEquationSolver

#endif  // NOLINEAR_EQUATION_SOLVER_H
