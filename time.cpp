#include <iostream>

const int morning = 1;
const int day = 2;
const int evening = 3;
const int hours_limit_l = 0;
const int hours_limit_r = 23;
const int minutes_limit_l = 0;
const int minutes_limit_r = 59;
const int morning_l = 5;
const int morning_r = 12;
const int day_l = 12;
const int day_r = 18;
const int evening_l = 18;
const int evening_r = 23;
const int hour_case_1 = 1;
const int hour_case_2 = 2;
const int hour_case_3 = 3;
const int hour_case_4 = 4;
const int minute_case_1 = 1;
const int minute_case_2 = 2;
const int minute_case_3 = 3;
const int minute_case_4 = 4;
const int exception = 11;
const int midday = 12;
const int ten = 10;

bool is_correct_time(int hours, int minutes) {
    if (hours >= hours_limit_l && hours <= hours_limit_r && minutes >= minutes_limit_l && minutes <= minutes_limit_r) {
        return true;
    }
    return false;
}

int time_of_day(int hours) {
    if (hours >= morning_l && hours < morning_r) {
        return 1;
    } else if (hours >= day_l && hours < day_r) {
        return 2;
    } else if (hours >= evening_l && hours <= evening_r) {
        return 3;
    }
    return 4;
}

void hours_case(int hours) {
    if (hours == hour_case_1) {
        std::cout << "час ";
    } else if (hours == hour_case_2 || hours == hour_case_3 || hours == hour_case_4) {
        std::cout << "часа ";
    } else {
        std::cout << "часов ";
    }
}

void there_are_minutes(int minutes) {
    if (minutes % ten == minute_case_1 && minutes != exception) {
        std::cout << "минута ";
    } else if (minutes % ten == minute_case_2 || minutes % ten == minute_case_3 || minutes % ten == minute_case_4) {
        std::cout << "минуты ";
    } else {
        std::cout << "минут ";
    }
}

void type_of_day_2(int time) {
    if (time == morning) {
        std::cout << "утра" << std::endl;
    } else if (time == day) {
        std::cout << "дня" << std::endl;
    } else if (time == evening) {
        std::cout << "вечера" << std::endl;
    } else {
        std::cout << "ночи" << std::endl;
    }
}

void type_of_day_3(int time) {
    if (time == morning) {
        std::cout << "утра";
    } else if (time == day) {
        std::cout << "дня";
    } else if (time == evening) {
        std::cout << "вечера";
    } else {
        std::cout << "ночи";
    }
}

int main(int, char**) {
    int hours = 0;
    int minutes = 0;
    int time = 4;
    std::cin >> hours >> minutes;

    if (!is_correct_time(hours, minutes)) {
        std::cout << "введены недопустимые данные" << std::endl;
        return 0;
    }

    if (hours == midday && minutes == 0) {
        std::cout << "полдень" << std::endl;
        return 0;
    }

    if (hours == 0 && minutes == 0) {
        std::cout << "полночь" << std::endl;
        return 0;
    }

    time = time_of_day(hours);
    if (hours > midday) {
        hours -= midday;
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
