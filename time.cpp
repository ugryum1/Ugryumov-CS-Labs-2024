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

const int kHourInSingular = 1;
const int kHoursInPluralMin = 2;
const int kHoursInPluralMax = 4;

const int kGenitiveMinutesMin = 11;
const int kGenitiveMinutesMax = 14;

const int kMiddayHours = 12;
const int kMidnightHours = 0;
const int kMiddayMinutes = 0;
const int kMidnightMinutes = 0;

const int kDecimalBase = 10;
}  // namespace

bool IsCorrectInput(int hours, int minutes) {
    return hours >= kHoursLimitMin && hours <= kHoursLimitMax && minutes >= kMinutesLimitMin && minutes <= kMinutesLimitMax;
}

void TheFormOfTheWorldHour(int hours) {
    if (hours == kHourInSingular) {
        std::cout << " час";
    } else if (hours >= kHoursInPluralMin && hours <= kHoursInPluralMax) {
        std::cout << " часа";
    } else {
        std::cout << " часов";
    }
}

void PartOfDay(int hours) {
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

void TheFormOfTheWorldMinute(int minutes) {
    if (minutes % kDecimalBase == 1 && minutes != kGenitiveMinutesMin) {
        std::cout << " минута";
    } else if ((minutes % kDecimalBase == 2 || minutes % kDecimalBase == 3 || minutes % kDecimalBase == 4) &&
               (minutes <= kGenitiveMinutesMin || minutes > kGenitiveMinutesMax)) {
        std::cout << " минуты";
    } else {
        std::cout << " минут";
    }
}

int main(int, char**) {
    std::cout << "Введите часы и минуты через пробел" << std::endl;
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

    int HoursInFormatFrom1To12 = hours;
    if (hours > kMiddayHours) {
        HoursInFormatFrom1To12 -= kMiddayHours;
    }
    std::cout << HoursInFormatFrom1To12;

    TheFormOfTheWorldHour(HoursInFormatFrom1To12);

    if (minutes == 0) {
        PartOfDay(hours);
        std::cout << " ровно" << std::endl;
    } else if (minutes >= kMinutesLimitMin && minutes <= kMinutesLimitMax) {
        std::cout << " " << minutes;
        TheFormOfTheWorldMinute(minutes);
        PartOfDay(hours);
        std::cout << std::endl;
    }

    return 0;
}
