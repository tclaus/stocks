
#include "DetailsView.h"
#include "DetailsHeadline.h"
#include "DetailsChart.h"
#include "DetailsDataList.h"
#include <Catalog.h>
#include <LayoutBuilder.h>
#include <View.h>

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "DetailsView"

DetailsView::DetailsView()
        : BView(BRect(), B_TRANSLATE("chartView"), B_FOLLOW_ALL, B_WILL_DRAW) {

    SetExplicitMinSize(BSize(200, 500));

    detailsHeadline = new DetailsHeadline();
    detailsChart = new DetailsChart();
    detailsDataList = new DetailsDataList();

    BLayoutBuilder::Group<>(this, B_VERTICAL)
            .SetInsets(25, 25, 25, 25)
            .Add(detailsHeadline)
            .Add(detailsChart)
            .Add(detailsDataList)
            .AddGlue();
}

void
DetailsView::SetTimeRange(TimeRange timeRange) {
    detailsChart->SetTimeRange(timeRange);
}
