//
// Created by Thorsten Claus on 10.07.23.
//

#ifndef STOCKS_CHARTTIMERANGEBAR_H
#define STOCKS_CHARTTIMERANGEBAR_H

#include <View.h>
#include <Button.h>
#include "TabView.h"
#include "ChartView.h"

class ChartTimeRangeBar : public BView {
public:
    ChartTimeRangeBar();

    void InitTabs();

private:

    BButton *createButton(const char *label, BMessage *message);

private:


};

#endif //STOCKS_CHARTTIMERANGEBAR_H
