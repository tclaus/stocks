//
// Created by Thorsten Claus on 19.07.23.
//

#include <cstdio>
#include "SeriesDrawer.h"
#include "DataSeriesLimiter.h"
#include "DateTimeCalculator.h"

SeriesDrawer::SeriesDrawer(BView *view) :
        fView(view) {
}

void
SeriesDrawer::DrawSeries(TimeRange timeRange, HistoricalPriceList *historicalPriceList) {
    fView->PushState();
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

        HistoricalPrice *firstItem = limitedHistoricalPrice->List()->front();
        BString *startItemTimestamp = firstItem->GetDate();
        // Hole die sekunden

        HistoricalPrice *lastItem = limitedHistoricalPrice->List()->back();
        BString *lastItemTimestamp = lastItem->GetDate();


        printf("Max price: %f, min price: %f, range: %f\n ", maxPrice, minPrice, priceRange);
        printf("StartDate: %s, EndDate: %s \n", startItemTimestamp->String(), lastItemTimestamp->String());

        printf("Datapoint count: %zu \n", limitedHistoricalPrice->List()->size());

        float maxDataPoints = (float) limitedHistoricalPrice->List()->size();  // Bei einem ganzen Tag - alle anderen gilt die Anzahl der Datenpunkte in der Liste

        // OK Kurs Seitenverkehrt?
        // TODO: Grüne / rote farbe der Linie. Grün, wenn Closing price/CurrentPrice > Opening Price
        // TODO: Linie etwas dicker machen. Pattern? an den endpunkten jeweils eine Linie genau daneben zeichnen?
        // TODO: Linie geht nicht bis zum rechten Rand

        float xOld, yOld, xNew, yNew;
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

float
SeriesDrawer::calculateYNew(float priceRange, float maxPrice, HistoricalPrice *const &item) const {
    return (maxPrice - item->GetClose()) * (fView->Bounds().Height() / priceRange);
}

float
SeriesDrawer::calculateXNew(float maxDataPoints, int dataPointNumber) const {
    return (float) dataPointNumber * (fView->Bounds().Width() / (float) maxDataPoints);
}
