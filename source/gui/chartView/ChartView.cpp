
#include "ChartView.h"
#include <LayoutBuilder.h>
#include <StringView.h>
#include <View.h>

ChartView::ChartView()
        : BView(BRect(0, 0, 300, 200), "chartView", B_FOLLOW_ALL, B_WILL_DRAW) {

    this->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

    BStringView *placeholderText =
            new BStringView("placeholderLabel", "Choose a share from the shares fList");

    BLayoutBuilder::Group<>(this, B_VERTICAL)
            .AddGrid()
            .AddGlue(0, 1)
            .Add(placeholderText, 1, 1)
            .AddGlue(2, 1);
}
