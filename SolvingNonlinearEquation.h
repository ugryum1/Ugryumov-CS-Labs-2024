#ifndef SOLVING_NOLINEAR_EQUATION
#define SOLVING_NOLINEAR_EQUATION

namespace NonlinearEquationSolver {
enum class EquationMethod : int {
    Iterative = 1,
    HalfDivision = 2,
    Newton = 3,
};

[[nodiscard]] double CalculateIterativeMethod(double coefficient, double accuracy, int& iterations);
void DoIterativeMethod();

[[nodiscard]] double CalculateHalfDivisionMethod(double coefficient, double accuracy, double left, double right, int& iterations);
void DoHalfDivisionMethod();

[[nodiscard]] double CalculateNewtonMethod(double coefficient, double accuracy, int& iterations);
void DoNewtonMethod();

void SelectMethod(EquationMethod task);

void ExecuteApp();
}  // namespace NonlinearEquationSolver

#endif  // SOLVING_NOLINEAR_EQUATION
