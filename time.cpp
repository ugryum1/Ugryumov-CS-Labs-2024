#include <iostream>

namespace {
const int kMorning = 1;
const int kDay = 2;
const int kEvening = 3;
const int kNight = 4;
const int kHoursLimitL = 0;
const int kHoursLimitR = 23;
const int kMinutesLimitL = 0;
const int kMinutesLimitR = 59;
const int kMorningL = 5;
const int kMorningR = 12;
const int kDayL = 12;
const int kDayR = 18;
const int kEveningL = 18;
const int kEveningR = 23;
const int kHourCase1 = 1;
const int kHourCase2 = 2;
const int kHourCase3 = 3;
const int kHourCase4 = 4;
const int kMinuteCase1 = 1;
const int kMinuteCase2 = 2;
const int kMinuteCase3 = 3;
const int kMinuteCase4 = 4;
const int kException = 10;
const int kMidday = 12;
const int kTen = 10;
}  // namespace

bool is_correct_time(int hours, int minutes) {
    if (hours >= kHoursLimitL && hours <= kHoursLimitR && minutes >= kMinutesLimitL && minutes <= kMinutesLimitR) {
        return true;
    }
    return false;
}

int time_of_day(int hours) {
    if (hours >= kMorningL && hours < kMorningR) {
        return kMorning;
    } else if (hours >= kDayL && hours < kDayR) {
        return kDay;
    } else if (hours >= kEveningL && hours <= kEveningR) {
        return kEvening;
    }
    return kNight;
}

void hours_case(int hours) {
    if (hours == kHourCase1) {
        std::cout << "час ";
    } else if (hours == kHourCase2 || hours == kHourCase3 || hours == kHourCase4) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }
}

void there_are_minutes(int minutes) {
    if (minutes % kTen == kMinuteCase1 && minutes - minutes % kTen != kException) {
        std::cout << "минута ";
    } else if ((minutes % kTen == kMinuteCase2 || minutes % kTen == kMinuteCase3 || minutes % kTen == kMinuteCase4) &&
               minutes - minutes % kTen != kException) {
        std::cout << "минуты ";
    } else {
        std::cout << "минут ";
    }
}

void type_of_day_2(int time) {
    if (time == kMorning) {
        std::cout << "утра" << std::endl;
    } else if (time == kDay) {
        std::cout << "дня" << std::endl;
    } else if (time == kEvening) {
        std::cout << "вечера" << std::endl;
    } else {
        std::cout << "ночи" << std::endl;
    }
}

void type_of_day_3(int time) {
    if (time == kMorning) {
        std::cout << "утра";
    } else if (time == kDay) {
        std::cout << "дня";
    } else if (time == kEvening) {
        std::cout << "вечера";
    } else {
        std::cout << "ночи";
    }
}

int main(int, char**) {
    int hours = 0;
    int minutes = 0;
    int time = kMorning;
    std::cin >> hours >> minutes;

    if (!is_correct_time(hours, minutes)) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 0;
    }

    if (hours == kMidday && minutes == 0) {
        std::cout << "полдень" << std::endl;
        return 0;
    }

    if (hours == 0 && minutes == 0) {
        std::cout << "полночь" << std::endl;
        return 0;
    }

    time = time_of_day(hours);
    if (hours > kMidday) {
        hours -= kMidday;
    }
    std::cout << hours << " ";
    hours_case(hours);

    if (minutes != 0) {
        std::cout << minutes << " ";
        there_are_minutes(minutes);
        type_of_day_2(time);
    } else {
        type_of_day_3(time);
        std::cout << " ровно" << std::endl;
    }

    return 0;
}
