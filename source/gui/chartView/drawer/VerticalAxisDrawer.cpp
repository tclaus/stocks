//
// Created by Thorsten Claus on 13.08.23.
//

#include <iomanip>
#include "VerticalAxisDrawer.h"
#include "DataSeriesLimiter.h"

VerticalAxisDrawer::VerticalAxisDrawer(BView *view) :
        fView(view) {
}

void VerticalAxisDrawer::DrawAxis(TimeRange timeRange, HistoricalPriceList *historicalPriceList) {
    fView->PushState();
    fView->SetPenSize(1.5);
    DrawVerticalAxisWithState(timeRange, historicalPriceList);
    fView->PopState();
}

void VerticalAxisDrawer::DrawVerticalAxisWithState(TimeRange timeRange, HistoricalPriceList *historicalPriceList) {
    auto *dataSeriesLimiter = new DataSeriesLimiter();
    HistoricalPriceList *limitedHistoricalPrice = dataSeriesLimiter->LimitForRange(timeRange, historicalPriceList);

    if (!limitedHistoricalPrice->List()->empty()) {
        DrawValues(limitedHistoricalPrice);
    }
}

void VerticalAxisDrawer::DrawValues(HistoricalPriceList *limitedHistoricalPrice) const {
    float maxPrice = limitedHistoricalPrice->GetMaxClosingPrice();
    float minPrice = limitedHistoricalPrice->GetMinClosingPrice();
    float priceRange = maxPrice - minPrice;

    for (int i = 0; i < PRICE_VALUE_COUNT; i++) {
        float x = CalculateX();
        float y = CalculateY(i);

        float priceValueForSegment = (priceRange / (float) PRICE_VALUE_COUNT) * (float) i;
        priceValueForSegment = priceValueForSegment + minPrice;

        std::ostringstream outStream;
        outStream << std::fixed << std::setprecision(2) << priceValueForSegment;

        BPoint drawingStartPoint(x, y);
        fView->SetPenSize(1.5);
        fView->DrawString(outStream.str().c_str(), drawingStartPoint);
    }
}

float VerticalAxisDrawer::CalculateY(int i) const {
    return fView->Bounds().Height() -
           (float) i * fView->Bounds().Height() /
           (float) PRICE_VALUE_COUNT
           - 5;
}

float VerticalAxisDrawer::CalculateX() const { return fView->Bounds().Width() - RIGHT_PLAT_AREA_MARGIN; }
