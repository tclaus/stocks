
#include "DetailsView.h"
#include "DetailsHeadline.h"
#include "DetailsChart.h"
#include "DetailsDataList.h"
#include <LayoutBuilder.h>
#include <View.h>

DetailsView::DetailsView()
        : BView(BRect(), "chartView", B_FOLLOW_ALL, B_WILL_DRAW) {

    this->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

    this->SetExplicitMinSize(BSize(200, 500));

// a) placeholder text, until a symbol is selected    BLayoutBuilder::Group<>(this, B_VERTICAL)
// BStringView *placeholderText =
// new BStringView("placeholderLabel", "Choose a share from the shares fList");
//  BLayoutBuilder::Group<>(this, B_VERTICAL)
//            .SetInsets(10, 10, 10, 10)
//            .AddGrid()
//            .AddGlue(0, 1)
//            .Add(placeholderText, 1, 1)
//            .AddGlue(2, 1);

// b) Stocks details


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


