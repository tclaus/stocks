//
// Created by Thorsten Claus on 10.07.23.
//

#include "ChartTimeRangeBar.h"

#include <Catalog.h>
#include <LayoutBuilder.h>
#include "Button.h"

#undef B_TRANSLATION_CONTEXT
#define B_TRANSLATION_CONTEXT "ChartTimeRangeBar"


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
    BButton *oneDayButton = createButton(B_TRANSLATE_COMMENT("1 D", "Abbreviation for 'one day', short as possible"),
                                         new BMessage(TimeRange::M_DAY));
    oneDayButton->SetValue(B_CONTROL_ON);

    BLayoutBuilder::Group<>(this, B_HORIZONTAL, 0)
            .Add(oneDayButton)
            .Add(createButton(B_TRANSLATE_COMMENT("1 W", "Abbreviation for 'one Week'"),
                              new BMessage(TimeRange::M_WEEK)))
            .Add(createButton(B_TRANSLATE_COMMENT("1 M", "Abbreviation for 'one month'"),
                              new BMessage(TimeRange::M_MONTH)))
            .Add(createButton(B_TRANSLATE_COMMENT("3 M", "Abbreviation for 'three months'"),
                              new BMessage(TimeRange::M_THREE_MONTH)))
            .Add(createButton(B_TRANSLATE_COMMENT("6 M", "Abbreviation for 'six months'"),
                              new BMessage(TimeRange::M_SIX_MONTH)))
            .Add(createButton(B_TRANSLATE_COMMENT("1 Y", "Abbreviation for 'one year', the last 12 months"),
                              new BMessage(TimeRange::M_YEAR)))
            .Add(createButton(B_TRANSLATE_COMMENT("2 Y", "Abbreviation for 'two years'"),
                              new BMessage(TimeRange::M_TWO_YEARS)))
            .Add(createButton(B_TRANSLATE_COMMENT("5 Y", "Abbreviation for '5 years', the longest possible period"),
                              new BMessage(TimeRange::M_FIVE_YEARS)));
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
