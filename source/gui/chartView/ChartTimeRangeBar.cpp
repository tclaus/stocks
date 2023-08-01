//
// Created by Thorsten Claus on 10.07.23.
//

#include "ChartTimeRangeBar.h"

#include <Catalog.h>
#include <LayoutBuilder.h>
#include "Button.h"
#include "TimeRange.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "ChartTimeRangeBar"


ChartTimeRangeBar::ChartTimeRangeBar() :
        BView(BRect(), B_TRANSLATE("chartTimeRangeBar"), B_FOLLOW_ALL, B_WILL_DRAW) {
    InitTabs();
}

void
ChartTimeRangeBar::InitTabs() {
    BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
            .Add(createButton(B_TRANSLATE("1 D"), new BMessage(TimeRange::M_DAY)))
            .Add(createButton(B_TRANSLATE("1 W"), new BMessage(TimeRange::M_WEEK)))
            .Add(createButton(B_TRANSLATE("1 M"), new BMessage(TimeRange::M_MONTH)))
            .Add(createButton(B_TRANSLATE("3 M"), new BMessage(TimeRange::M_THREE_MONTH)))
            .Add(createButton(B_TRANSLATE("6 M"), new BMessage(TimeRange::M_SIX_MONTH)))
            .Add(createButton(B_TRANSLATE("1 Y"), new BMessage(TimeRange::M_YEAR)))
            .Add(createButton(B_TRANSLATE("2 Y"), new BMessage(TimeRange::M_TWO_YEARS)))
            .Add(createButton(B_TRANSLATE("5 Y"), new BMessage(TimeRange::M_FIVE_YEARS)));
}

BButton *
ChartTimeRangeBar::createButton(const char *label, BMessage *message) {
    auto *button = new BButton(label, message);
    button->SetFlat(true);
    return button;
}

