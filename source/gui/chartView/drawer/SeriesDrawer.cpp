//
// Created by Thorsten Claus on 19.07.23.
//

#include "SeriesDrawer.h"
#include "DataSeriesLimiter.h"
#include "DateTimeCalculator.h"
#include "../Colors.h"
#include <cstdio>

SeriesDrawer::SeriesDrawer(BView *view) :
        fView(view) {
}

void
SeriesDrawer::DrawSeries(TimeRange timeRange, HistoricalPriceList *historicalPriceList) {
    fView->PushState();
    fView->SetPenSize(1.5);
    DrawSeriesWithState(timeRange, historicalPriceList);
    fView->PopState();
}

void
SeriesDrawer::DrawSeriesWithState(TimeRange &timeRange, HistoricalPriceList *historicalPriceList) {
    DataSeriesLimiter *dataSeriesLimiter = new DataSeriesLimiter();
    HistoricalPriceList *limitedHistoricalPrice = dataSeriesLimiter->LimitForRange(timeRange, historicalPriceList);

    if (!limitedHistoricalPrice->List()->empty()) {

        float maxPrice = limitedHistoricalPrice->GetMaxClosingPrice();
        float minPrice = limitedHistoricalPrice->GetMinClosingPrice();
        float priceRange = maxPrice - minPrice;

        SetGainLossColor(*limitedHistoricalPrice);

        float maxDataPoints = (float) limitedHistoricalPrice->List()->size();

        float xOld = 0.0, yOld = 0.0, xNew = 0.0, yNew = 0.0;
        int dataPointNumber = 0;
        for (const auto &item: *limitedHistoricalPrice->List()) {

            xNew = calculateXNew(maxDataPoints, dataPointNumber);
            yNew = calculateYNew(priceRange, maxPrice, item);

            fView->StrokeLine(BPoint(xOld, yOld), BPoint(xNew, yNew));

            xOld = xNew;
            yOld = yNew;
            dataPointNumber++;
        }
    }
    delete limitedHistoricalPrice;
}

void SeriesDrawer::SetGainLossColor(HistoricalPriceList &historicalPriceList) {
    HistoricalPrice *firstItem = historicalPriceList.List()->front();
    HistoricalPrice *lastItem = historicalPriceList.List()->back();

    if (firstItem->GetOpen() < lastItem->GetClose()) {
        fView->SetHighColor(Colors::PlotGain());
    } else {
        fView->SetHighColor(Colors::PlotLoss());
    }
}

float
SeriesDrawer::calculateYNew(float priceRange, float maxPrice, HistoricalPrice *const &item) const {
    return (maxPrice - item->GetClose()) * (fView->Bounds().Height() / priceRange);
}

float
SeriesDrawer::calculateXNew(float maxDataPoints, int dataPointNumber) const {
    return (float) dataPointNumber * (fView->Bounds().Width() / (float) maxDataPoints);
}
