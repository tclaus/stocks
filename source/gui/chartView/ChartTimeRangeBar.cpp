//
// Created by Thorsten Claus on 10.07.23.
//

#include "ChartTimeRangeBar.h"

#include <LayoutBuilder.h>
#include "Button.h"

ChartTimeRangeBar::ChartTimeRangeBar() :
        BView(BRect(), "chartTimeRangeBar", B_FOLLOW_ALL, B_WILL_DRAW),
        fListOfButtons(new std::list<BButton *>()) {
    InitTabs();
}

ChartTimeRangeBar::~ChartTimeRangeBar() {
    delete fListOfButtons;
}

void
ChartTimeRangeBar::InitTabs() {
    BButton *oneDayButton = createButton("1 D", new BMessage(TimeRange::M_DAY));
    oneDayButton->SetValue(B_CONTROL_ON);

    BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
            .Add(oneDayButton)
            .Add(createButton("1 W", new BMessage(TimeRange::M_WEEK)))
            .Add(createButton("1 M", new BMessage(TimeRange::M_MONTH)))
            .Add(createButton("3 M", new BMessage(TimeRange::M_THREE_MONTH)))
            .Add(createButton("6 M", new BMessage(TimeRange::M_SIX_MONTH)))
            .Add(createButton("1 Y", new BMessage(TimeRange::M_YEAR)))
            .Add(createButton("2 Y", new BMessage(TimeRange::M_TWO_YEARS)))
            .Add(createButton("5 Y", new BMessage(TimeRange::M_FIVE_YEARS)));
}

BButton *
ChartTimeRangeBar::createButton(const char *label, BMessage *message) {
    auto *button = new BButton(label, message);
    button->SetFlat(true);
    button->SetBehavior(BButton::B_TOGGLE_BEHAVIOR);
    fListOfButtons->push_front(button);
    return button;
}

void ChartTimeRangeBar::SetTimeButton(TimeRange range) {
    for (const auto &button: *fListOfButtons) {
        uint32 timeRangeValue = button->Message()->what;
        if (timeRangeValue == range) {
            button->SetEnabled(false);
            continue;
        }
        button->SetValue(B_CONTROL_OFF);
        button->SetEnabled(true);
    }
}
