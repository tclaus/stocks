//
// Created by Thorsten Claus on 19.07.23.
//

#include <cstdio>
#include "SeriesDrawer.h"
#include "DataSeriesLimiter.h"

SeriesDrawer::SeriesDrawer(BView *view) :
        fView(view) {
}

void
SeriesDrawer::DrawSeries(TimeRange timeRange, HistoricalPriceList *historicalPriceList) {
    fView->PushState();
    // Calculating time frame (for one Day for now)
    DataSeriesLimiter *dataSeriesLimiter = new DataSeriesLimiter();
    HistoricalPriceList *limitedHistoricalPrice = dataSeriesLimiter->LimitForRange(timeRange, historicalPriceList);

    (void) limitedHistoricalPrice;

    float maxPrice = limitedHistoricalPrice->GetMaxClosingPrice();
    float minPrice = limitedHistoricalPrice->GetMinClosingPrice();
    float priceRange = maxPrice - minPrice;

    printf("Max: %f, min: %f, range: %f\n ", maxPrice, minPrice, priceRange);

    float maxDataPoints = 480;  // Bei einem Tag - alle anderen gilt die Anzahl der datenpunkte in der Liste
    float xOld, yOld, xNew, yNew;
    int dataPointNumber = 0;
    for (const auto &item: *limitedHistoricalPrice->List()) {

        xNew = calculateXNew(maxDataPoints, dataPointNumber);
        yNew = calculateYNew(priceRange, minPrice, item);

        fView->StrokeLine(BPoint(xOld, yOld), BPoint(xNew, yNew));
        // printf("Drawing a line to x/y: %f.2/%f.2 \n", xNew, yNew);

        xOld = xNew;
        yOld = yNew;
        dataPointNumber++;
    }

    fView->PopState();
    delete limitedHistoricalPrice;
}

float
SeriesDrawer::calculateYNew(float priceRange, float minPrice, HistoricalPrice *const &item) const {
    return (1 + item->GetClose() - minPrice) * (fView->Bounds().Height() / priceRange);
}

float
SeriesDrawer::calculateXNew(float maxDataPoints, int dataPointNumber) const {
    return (float) dataPointNumber * (fView->Bounds().Width() / (float) maxDataPoints);
}
