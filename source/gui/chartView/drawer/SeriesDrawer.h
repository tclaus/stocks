//
// Created by Thorsten Claus on 19.07.23.
//

#ifndef STOCKS_SERIESDRAWER_H
#define STOCKS_SERIESDRAWER_H

#include "TimeRange.h"
#include "HistoricalPriceList.h"
#include <View.h>

class SeriesDrawer {

public:
    explicit SeriesDrawer(BView *view);

    /**
     * Draws the plot line for a timeframe with the given series data.
     * If a time range has no data e.g. the market exchange did not open today - data is provided for the day before.
     * @param timeRange The range to draw the line (day, week, month)
     * @param seriesData
     */
    void DrawSeries(TimeRange timeRange, HistoricalPriceList *historicalPriceList);

private:
    BView *fView;

    float calculateXNew(float maxDataPoints, int dataPointNumber) const;

    float calculateYNew(float priceRange, float maxPrice, HistoricalPrice *const &item) const;

    void DrawSeriesWithState(TimeRange &timeRange, HistoricalPriceList *historicalPriceList);
};


#endif //STOCKS_SERIESDRAWER_H
