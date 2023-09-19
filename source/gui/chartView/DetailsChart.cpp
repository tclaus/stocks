//
// Created by Thorsten Claus on 01.05.23.
//

#include <Catalog.h>
#include <LayoutBuilder.h>
#include "DetailsChart.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "DetailsChart"

DetailsChart::DetailsChart() :
        BView(BRect(), "detailsChartView", B_FOLLOW_ALL, B_WILL_DRAW) {
    InitView();
}

DetailsChart::~DetailsChart() {
    delete fChartView;
    delete fChartTimeRangeBar;
}

void DetailsChart::InitView() {
    fChartView = new ChartView();
    fChartTimeRangeBar = new ChartTimeRangeBar();
    BLayoutBuilder::Group<>(this, B_VERTICAL, 0)
            .SetInsets(0, B_USE_DEFAULT_SPACING, 0, 0)
            .AddGroup(B_VERTICAL, B_USE_DEFAULT_SPACING)
            .Add(fChartTimeRangeBar)
            .End()
            .Add(fChartView);
}

void
DetailsChart::SetTimeRange(TimeRange timeRange) {
    fChartView->SetTimeRange(timeRange);
    fChartTimeRangeBar->SetTimeButton(timeRange);
}