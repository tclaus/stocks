//
// Created by Thorsten Claus on 23.07.23.
//

#ifndef STOCKS_DATASERIESLIMITER_H
#define STOCKS_DATASERIESLIMITER_H

#include <ctime>
#include "HistoricalPriceList.h"
#include "TimeRange.h"

/**
 * Limits the data series for a specific time range.
 * Data from the API has a certain amount of data not matching the exact time range which is requested.
 * Data for one day can include more than one day and should not necessarily start with the current day when today is
 * sunday (no opening day of the stock exchange) or no trade today in the morning.
 */
class DataSeriesLimiter {
public:
    /**
     * Creates a new {@link HistoricalPriceList} based on the time frame.
     * The data sent from the API may contain more than the requested timeframe.
     * This functions takes ownership over {@link HistoricalPriceList} and removes it from memory. A new list is generated and returned.
     * @param historicalPriceList
     * @return a new price list
     */
    HistoricalPriceList *LimitForRange(TimeRange timeRange, HistoricalPriceList *historicalPriceList);

private:
    HistoricalPriceList *LimitForRangeForADay(HistoricalPriceList *historicalPriceList);

    /**
     * Creates a new object containing only the count of days since today provided in the parameter.
     * @param historicalPriceList
     * @param rangeInDays
     * @return
     */
    HistoricalPriceList *LimitForTimeRangeInDays(HistoricalPriceList *historicalPriceList, int rangeInDays);

    time_t CalculateTimeForItem(HistoricalPrice *const &item);

};

#endif //STOCKS_DATASERIESLIMITER_H
