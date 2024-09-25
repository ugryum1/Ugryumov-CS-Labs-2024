#include <cmath>
#include <iostream>

namespace {
const char kFirstTaskNumber = '1';
const char kSecondTaskNumber = '2';
const char kThirdTaskNumber = '3';
const char kFourthTaskNumber = '4';
const char kExitProgramSymbol = 'e';
const char kContinueProgramSymbol = 'y';
}  // namespace

void TaskSelection();

bool SolveAgain() {
    std::cout << "\nЕсли хотите ещё раз решить это задание, напишите 'y', "
                 "иначе напишите 'n', вы перейдёте к выбору заданий."
              << std::endl;
    char choice{};
    std::cin >> choice;
    std::cout << std::endl;

    if (choice == kContinueProgramSymbol) {
        return true;
    }

    std::cout << std::endl;
    TaskSelection();
    return false;
}

void DoFirstTask() {
    int n{};
    int m{};
    std::cout << "Введите натуральные числа n и m (m < n) через проблел." << std::endl;
    std::cin >> n >> m;

    int answer = 0;
    for (int i = 0; i <= n; i += 5) {
        if (i % m != 0) {
            answer += i;
        }
    }

    std::cout << "Сумма натуральных чисел, делящихся на 5 и не делящихся на " << m
              << " одновременно, "
                 "на отрезке от 1 до "
              << n << " равна " << answer << "." << std::endl;

    if (SolveAgain()) {
        DoFirstTask();
    }
}

void DoSecondTask() {
    if (SolveAgain()) {
        DoSecondTask();
    }
}

void DoThirdTask() {
    if (SolveAgain()) {
        DoThirdTask();
    }
}

void DoFourthTask() {
    if (SolveAgain()) {
        DoFourthTask();
    }
}

void TaskSelection() {
    std::cout << "Введите номер задания (цифру от 1 до 4 включительно), которое хотите решить.\n"
                 "Чтобы завершить программу, напишите 'e'."
              << std::endl;

    char taskNumber{};
    std::cin >> taskNumber;

    if (taskNumber == kFirstTaskNumber) {
        DoFirstTask();
    } else if (taskNumber == kSecondTaskNumber) {
        DoSecondTask();
    } else if (taskNumber == kThirdTaskNumber) {
        DoThirdTask();
    } else if (taskNumber == kFourthTaskNumber) {
        DoFourthTask();
    } else if (taskNumber == kExitProgramSymbol) {
        return;
    } else {
        std::cout << "Вы неправильно ввели номер задания, попробуйте заново.\n" << std::endl;
        TaskSelection();
    }
}

int main(int, char**) {
    TaskSelection();

    return 0;
}
