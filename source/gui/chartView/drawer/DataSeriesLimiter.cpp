//
// Created by Thorsten Claus on 23.07.23.
//

#include "DataSeriesLimiter.h"
#include <chrono>

HistoricalPriceList *
DataSeriesLimiter::LimitForRange(TimeRange timeRange, HistoricalPriceList *historicalPriceList) {
    switch (timeRange) {
        case TimeRange::M_DAY : {
            return LimitForRangeForADay(historicalPriceList);
        }
        default: {
            return new HistoricalPriceList(*historicalPriceList);
        }
    }
}

HistoricalPriceList *
DataSeriesLimiter::LimitForRangeForADay(HistoricalPriceList *historicalPriceList) {
    auto *limitedHistoricalPriceList = new HistoricalPriceList();
    if (!historicalPriceList->List()->empty()) {
        BString *lastDate = DateForString(historicalPriceList->List()->front()->GetDate());
        for (const auto &item: *historicalPriceList->List()) {
            BString *dateToCheck = DateForString(item->GetDate());
            if (lastDate->Compare(*dateToCheck) == 0) {
                limitedHistoricalPriceList->List()->push_back(item);
            }
        }
    }

    return limitedHistoricalPriceList;
}

BString *
DataSeriesLimiter::DateForString(BString *dateTimeString) {
    auto *dateString = new BString();
    dateTimeString->CopyInto(*dateString, 0, 10);
    return dateString;
}

std::tm *DataSeriesLimiter::LocalTime() {
    std::time_t *time = new std::time_t;
    tm *tm = localtime(time);
    return tm;
}

