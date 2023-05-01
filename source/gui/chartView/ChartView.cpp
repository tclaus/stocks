
#include "ChartView.h"
#include "DetailsHeadline.h"
#include "DetailsChart.h"
#include "DetailsDataList.h"
#include <LayoutBuilder.h>
#include <StringView.h>
#include <View.h>

ChartView::ChartView()
        : BView(BRect(), "chartView", B_FOLLOW_ALL, B_WILL_DRAW) {

    this->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

    this->SetExplicitMinSize(BSize(200, 500));

    //BStringView *placeholderText =
    new BStringView("placeholderLabel", "Choose a share from the shares fList");
// a) placeholder text, until a symbol is selected    BLayoutBuilder::Group<>(this, B_VERTICAL)
//  BLayoutBuilder::Group<>(this, B_VERTICAL)
//            .SetInsets(10, 10, 10, 10)
//            .AddGrid()
//            .AddGlue(0, 1)
//            .Add(placeholderText, 1, 1)
//            .AddGlue(2, 1);

// b) Stocks details


    DetailsHeadline *detailsHeadline = new DetailsHeadline();
    DetailsChart *detailsChart = new DetailsChart();
    DetailsDataList *detailsDataList = new DetailsDataList();

    BLayoutBuilder::Group<>(this, B_VERTICAL)
            .SetInsets(10, 10, 10, 10)
            .Add(detailsHeadline)
            .Add(detailsChart)
            .Add(detailsDataList)
            .AddGlue();
}

void ChartView::SetActiveQuote(Quote &quote) {
    // Observe this
    fCurrentQuote = &quote;
}
