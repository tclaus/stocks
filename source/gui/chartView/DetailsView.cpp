
#include "DetailsView.h"
#include "DetailsHeadline.h"
#include "DetailsChart.h"
#include "DetailsDataList.h"
#include <LayoutBuilder.h>
#include <View.h>

DetailsView::DetailsView()
        : BView(BRect(), "chartView", B_FOLLOW_ALL, B_WILL_DRAW) {

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
    //TODO: Wie kann ein Parent mehrere Ebenen tiefer ein Nachricht senden?

    detailsChart->SetTimeRange(timeRange);

}
