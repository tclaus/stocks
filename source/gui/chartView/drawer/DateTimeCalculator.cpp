//
// Created by Thorsten Claus on 30.07.23.
//

#include <ctime>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <sstream>
#include "DateTimeCalculator.h"

std::tm *
DateTimeCalculator::CalculateStartOfSeries(int minusDays) {
    std::time_t time_in_seconds = LocalTime();
    time_in_seconds = time_in_seconds - (minusDays * HOURS_PER_DAY * MINUTES_PER_HOUR * SECONDS_PER_MINUTE);
    return std::localtime(&time_in_seconds);
}

BString *
DateTimeCalculator::ExtractDateFromTimestamp(BString *dateTimeString) {
    auto *dateString = new BString();
    dateTimeString->CopyInto(*dateString, 0, 10);
    return dateString;
}

BString *
DateTimeCalculator::ExtractTimeFromTimestamp(BString *dateTimeString) {
    auto *timeString = new BString();
    // Format: yyy-MM-dd hh:mm:ss
    if (dateTimeString->Length() > 10) {
        dateTimeString->CopyInto(*timeString, 10, 9);
    }
    return timeString;
}

std::time_t
DateTimeCalculator::MakeTMFromTimestamp(const char *dateTimeString) {
    std::tm t = {};
    std::istringstream ss{dateTimeString};

    ss >> std::get_time(&t, "%Y-%m-%d %H:%M:%S");
    return std::mktime(&t);
}

std::tm *
DateTimeCalculator::MakeTm(int year, int month, int day) {
    return MakeTm(year, month, day, 0, 0, 0);
}

std::tm *
DateTimeCalculator::MakeTm(int year, int month, int day, int hour, int minute, int second) {
    auto *tm = new std::tm();
    tm->tm_year = year - 1900; // years count from 1900
    tm->tm_mon = month - 1;    // months count from January=0
    tm->tm_mday = day;         // days count from 1
    tm->tm_hour = hour;
    tm->tm_min = minute;
    tm->tm_sec = second;
    return tm;
}
// Calculate seconds from TM

time_t
DateTimeCalculator::MakeEpoch(std::tm &time) {
    return std::mktime(&time);
}

std::time_t
DateTimeCalculator::LocalTime() {
    auto now = std::chrono::system_clock::now();
    return std::chrono::system_clock::to_time_t(now);
}

