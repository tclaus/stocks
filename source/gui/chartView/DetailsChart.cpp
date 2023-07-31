//
// Created by Thorsten Claus on 01.05.23.
//

#include <LayoutBuilder.h>
#include "DetailsChart.h"

DetailsChart::DetailsChart() :
        BView(BRect(), "detailsChartView", B_FOLLOW_ALL, B_WILL_DRAW) {

    InitView();
}

void DetailsChart::InitView() {
    fChartView = new ChartView();
    BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
            .SetInsets(0, B_USE_DEFAULT_SPACING, 0, 0)
            .AddGroup(B_VERTICAL, B_USE_DEFAULT_SPACING)
            .Add(new ChartTimeRangeBar())
            .End()
            .Add(fChartView);
}

void
DetailsChart::SetTimeRange(TimeRange timeRange) {
    fChartView->SetTimeRange(timeRange);
}