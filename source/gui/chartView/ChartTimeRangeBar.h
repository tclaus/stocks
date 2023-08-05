//
// Created by Thorsten Claus on 10.07.23.
//

#ifndef STOCKS_CHARTTIMERANGEBAR_H
#define STOCKS_CHARTTIMERANGEBAR_H

#include "TabView.h"
#include "ChartView.h"
#include "TimeRange.h"

#include <View.h>
#include <Button.h>

class ChartTimeRangeBar : public BView {
public:
    ChartTimeRangeBar();

    ~ChartTimeRangeBar();

    void InitTabs();

    /**
     * Signals the active button and releases any other button
     * @param range
     */
    void SetTimeButton(TimeRange range);

private:

    BButton *createButton(const char *label, BMessage *message);

    std::list<BButton *> *fListOfButtons;

};

#endif //STOCKS_CHARTTIMERANGEBAR_H
