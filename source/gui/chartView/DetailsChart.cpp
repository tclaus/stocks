//
// Created by Thorsten Claus on 01.05.23.
//

#include "DetailsChart.h"

DetailsChart::DetailsChart() :
        BView(BRect(), "detailsChartView", B_FOLLOW_ALL, B_WILL_DRAW) {
    this->SetViewColor(240, 0, 0);
}
