//
// Created by Thorsten Claus on 13.08.23.
//

#ifndef STOCKS_VERTICALAXISDRAWER_H
#define STOCKS_VERTICALAXISDRAWER_H

#include <View.h>
#include "HistoricalPriceList.h"
#include "TimeRange.h"

static const int PRICE_VALUE_COUNT = 4;

static const float RIGHT_PLAT_AREA_MARGIN = 40.0f;

/**
 * Draws the values on the vertical axis on the right side for orientation of the range of values that the graph includes
 */
class VerticalAxisDrawer {
public:
    /**
     * Initializes the vertical axis drawer with the provided view.
     * @param view
     */
    explicit
    VerticalAxisDrawer(BView *view);

    /**
     * Draws the values on the right side of the view.
     * @param historicalPriceList the raw list of series data
     */
    void DrawAxis(TimeRange timeRange, HistoricalPriceList *historicalPriceList);

private:
    BView *fView;

    void DrawVerticalAxisWithState(TimeRange range, HistoricalPriceList *historicalPriceList);

    void DrawValues(HistoricalPriceList *limitedHistoricalPrice) const;

    [[nodiscard]]
    float CalculateX() const;

    [[nodiscard]]
    float CalculateY(int i) const;
};


#endif //STOCKS_VERTICALAXISDRAWER_H
