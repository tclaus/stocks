//
// Created by Thorsten Claus on 23.07.23.
//

#include "DataSeriesLimiter.h"
#include "DateTimeCalculator.h"

#include <StringList.h>

HistoricalPriceList *
DataSeriesLimiter::LimitForRange(TimeRange timeRange, HistoricalPriceList *historicalPriceList) {
    switch (timeRange) {
        case TimeRange::M_DAY : {
            return LimitForRangeForADay(historicalPriceList);
        }
        case TimeRange::M_WEEK: {
            return LimitForTimeRangeInDays(historicalPriceList, 7);
        }
        case TimeRange::M_MONTH: {
            return LimitForTimeRangeInDays(historicalPriceList, 30);
        }
        case TimeRange::M_THREE_MONTH: {
            return LimitForTimeRangeInDays(historicalPriceList, 90);
        }
        case TimeRange::M_SIX_MONTH: {
            return LimitForTimeRangeInDays(historicalPriceList, 180);
        }
        case TimeRange::M_YEAR: {
            return LimitForTimeRangeInDays(historicalPriceList, 360);
        }
        case TimeRange::M_TWO_YEARS: {
            return LimitForTimeRangeInDays(historicalPriceList, 720);
        }
        case TimeRange::M_FIVE_YEARS: {
            return LimitForTimeRangeInDays(historicalPriceList, 1800);
        }
        default: {
            return new HistoricalPriceList(*historicalPriceList);
        }
    }
}

/**
 * Get only the last day in series of data.
 * @param historicalPriceList
 * @return
 */
HistoricalPriceList *
DataSeriesLimiter::LimitForRangeForADay(HistoricalPriceList *historicalPriceList) {
    auto *limitedHistoricalPriceList = new HistoricalPriceList();
    if (!historicalPriceList->List()->empty()) {
        BString *lastDate = DateTimeCalculator::ExtractDateFromTimestamp(
                historicalPriceList->List()->front()->GetDate());
        for (const auto &item: *historicalPriceList->List()) {
            BString *dateToCheck = DateTimeCalculator::ExtractDateFromTimestamp(item->GetDate());
            if (lastDate->Compare(*dateToCheck) == 0) {
                limitedHistoricalPriceList->List()->push_front(item);
            }
        }
    }

    return limitedHistoricalPriceList;
}

HistoricalPriceList *
DataSeriesLimiter::LimitForTimeRangeInDays(HistoricalPriceList *historicalPriceList, int rangeInDays) {
    auto *limitedHistoricalPriceList = new HistoricalPriceList();
    if (!historicalPriceList->List()->empty()) {

        std::tm *startOfSeries = DateTimeCalculator::CalculateStartOfSeries(rangeInDays);
        time_t startOfSeriesInSeconds = std::mktime(startOfSeries);

        for (const auto &item: *historicalPriceList->List()) {
            time_t dateToCheckInSeconds = CalculateTimeForItem(item);

            if (dateToCheckInSeconds > startOfSeriesInSeconds) {
                limitedHistoricalPriceList->List()->push_front(item);
            }
        }
    }
    return limitedHistoricalPriceList;
}

time_t
DataSeriesLimiter::CalculateTimeForItem(HistoricalPrice *const &item) {
    BString *dateStringToCheck = DateTimeCalculator::ExtractDateFromTimestamp(item->GetDate());
    return DateTimeCalculator::MakeTMFromTimestamp(dateStringToCheck->String());
}
