//
// Created by Thorsten Claus on 01.05.23.
//

#ifndef STOCKS_DETAILSCHART_H
#define STOCKS_DETAILSCHART_H

#include <View.h>
#include "Quote.h"
#include "ChartTimeRangeBar.h"

class DetailsChart : public BView {
public:
    DetailsChart();

    ~DetailsChart();

/**
 * Sets the current active quote to view its details.
 * @param quote The quote to show details.
 */
    void SetActiveQuote(Quote &quote);

    void InitView();

    void SetTimeRange(TimeRange timeRange);

private:
    ChartView *fChartView;
    ChartTimeRangeBar *fChartTimeRangeBar;
};


#endif //STOCKS_DETAILSCHART_H
