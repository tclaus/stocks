//
// Created by Thorsten Claus on 10.07.23.
//

#include "ChartTimeRangeBar.h"

#include <LayoutBuilder.h>
#include "Button.h"
#include "TimeRange.h"

ChartTimeRangeBar::ChartTimeRangeBar() :
        BView(BRect(), "chartTimeRangeBar", B_FOLLOW_ALL, B_WILL_DRAW) {
    InitTabs();
}

void
ChartTimeRangeBar::InitTabs() {
    BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
            .Add(createButton("1 D", new BMessage(TimeRange::M_DAY)))
            .Add(createButton("1 W", new BMessage(TimeRange::M_WEEK)))
            .Add(createButton("1 M", new BMessage(TimeRange::M_MONTH)))
            .Add(createButton("3 M", new BMessage(TimeRange::M_THREE_MONTH)))
            .Add(createButton("6 M", new BMessage(TimeRange::M_SIX_MONTH)))
            .Add(createButton("1 Y", new BMessage(TimeRange::M_YEAR)));
}

BButton *
ChartTimeRangeBar::createButton(const char *label, BMessage *message) {
    auto *button = new BButton(label, message);
    button->SetFlat(true);
    return button;
}

