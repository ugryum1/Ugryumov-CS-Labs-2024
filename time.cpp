#include <iostream>

namespace {
const int kHoursLimitMin = 0;
const int kHoursLimitMax = 23;
const int kMinutesLimitMin = 0;
const int kMinutesLimitMax = 59;

const int kMorningBegin = 5;
const int kMorningEnd = 11;
const int kAfternoonBegin = 12;
const int kAfternoonEnd = 17;
const int kEveningBegin = 18;
const int kEveningEnd = 23;
const int kNightBegin = 0;
const int kNightEnd = 4;

const int kNominativeSingularHours = 1;
const int kGenitiveSingularHoursBegin = 2;
const int kGenitiveSingularHoursEnd = 4;

const int kGenitivePluralMinutesBegin = 11;
const int kGenitivePluralMinutesEnd = 14;
const int kNominativeSingularMinutes = 1;
const int kGenitiveSingularMinutesBegin = 2;
const int kGenitiveSingularMinutesEnd = 4;

const int kMiddayHours = 12;
const int kMidnightHours = 0;
const int kMiddayMinutes = 0;
const int kMidnightMinutes = 0;

const int kHourBeginMinutes = 0;

const int kDecimalBase = 10;
}  // namespace

bool IsCorrectInput(int hours, int minutes) {
    return hours >= kHoursLimitMin && hours <= kHoursLimitMax && minutes >= kMinutesLimitMin && minutes <= kMinutesLimitMax;
}

void PrintHours(int hours) {
    if (hours > kMiddayHours) {
        hours -= kMiddayHours;
    }
    std::cout << hours;

    if (hours != kNominativeSingularHours && (hours < kGenitiveSingularHoursBegin || hours > kGenitiveSingularHoursEnd)) {
        std::cout << " часов";
    } else if (hours == kNominativeSingularHours) {
        std::cout << " час";
    } else if (hours >= kGenitiveSingularHoursBegin && hours <= kGenitiveSingularHoursEnd) {
        std::cout << " часа";
    }
}

void PrintMinutes(int minutes) {
    std::cout << " " << minutes;

    int lastDigitMinutes = minutes % kDecimalBase;

    if ((minutes >= kGenitivePluralMinutesBegin && minutes <= kGenitivePluralMinutesEnd) ||
        (lastDigitMinutes != kNominativeSingularMinutes &&
         (lastDigitMinutes < kGenitiveSingularMinutesBegin || lastDigitMinutes > kGenitiveSingularMinutesEnd))) {
        std::cout << " минут";
    } else if (lastDigitMinutes == kNominativeSingularMinutes) {
        std::cout << " минута";
    } else if (lastDigitMinutes >= kGenitiveSingularMinutesBegin && lastDigitMinutes <= kGenitiveSingularMinutesEnd) {
        std::cout << " минуты";
    }
}

void PrintPartOfDay(int hours) {
    if (hours >= kMorningBegin && hours <= kMorningEnd) {
        std::cout << " утра";
    } else if (hours >= kAfternoonBegin && hours <= kAfternoonEnd) {
        std::cout << " дня";
    } else if (hours >= kEveningBegin && hours <= kEveningEnd) {
        std::cout << " вечера";
    } else if (hours >= kNightBegin && hours <= kNightEnd) {
        std::cout << " ночи";
    }
}

int main(int, char**) {
    std::cout << "Введите время (количество часов от 0 до 23 включительно и "
                 "количество минут от 0 до 59 включительно через пробел)"
              << std::endl;
    int hours = 0;
    int minutes = 0;
    std::cin >> hours >> minutes;

    if (!IsCorrectInput(hours, minutes)) {
        std::cout << "введены недопустимые данные, количество часов должно быть от 0 до 23 включительно, "
                     "количество минут должно быть от 0 до 59 включительно"
                  << std::endl;
        return 1;
    }

    if (hours == kMiddayHours && minutes == kMiddayMinutes) {
        std::cout << "полдень" << std::endl;
        return 0;
    }

    if (hours == kMidnightHours && minutes == kMidnightMinutes) {
        std::cout << "полночь" << std::endl;
        return 0;
    }

    PrintHours(hours);

    if (minutes == kHourBeginMinutes) {
        PrintPartOfDay(hours);
        std::cout << " ровно";
    } else {
        PrintMinutes(minutes);
        PrintPartOfDay(hours);
    }

    std::cout << std::endl;

    return 0;
}
