//
// Created by Thorsten Claus on 30.07.23.
//

#ifndef STOCKS_DATETIMECALCULATOR_H
#define STOCKS_DATETIMECALCULATOR_H

#include "String.h"

static const int HOURS_PER_DAY = 24;

static const int MINUTES_PER_HOUR = 60;

static const int SECONDS_PER_MINUTE = 60;

class DateTimeCalculator {
public:

    /**
     * Extracts the date part (2023-10-01) from a timestamp string.
     * @param dateTimeString a timestamp with day and time (yyyy-MM-dd hh:mm:ss)
     * @return A ten character long string representing a single day
     */
    static BString *ExtractDateFromTimestamp(BString *dateTimeString);

    /**
     * Extracts the time part (hh:mm:ss) from a timestamp string if exist.
     * @param dateTimeString  timestamp with day and time parts (yyyy-MM-dd hh:mm:ss)
     * @return a eight character string containing a local time (24h format)
     */
    static BString *ExtractTimeFromTimestamp(BString *dateTimeString);

    static tm *MakeTm(int year, int month, int day);

    static tm *MakeTm(int year, int month, int day, int hour, int min, int sec);

    static time_t MakeEpoch(tm &time);

    /**
     * Calculates a date with the count of days before today to mark the beginning of a time range.
     * @param minusDays count of days to subtract from today
     * @return a standard time structure with the date n days before today
     */
    static tm *CalculateStartOfSeries(int minusDays);

    static std::time_t LocalTime();

    static time_t MakeTMFromTimestamp(const char *dateTimeString);
};


#endif //STOCKS_DATETIMECALCULATOR_H
