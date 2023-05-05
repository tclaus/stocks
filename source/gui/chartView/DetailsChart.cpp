//
// Created by Thorsten Claus on 01.05.23.
//

#include "DetailsChart.h"

DetailsChart::DetailsChart() :
        BView(BRect(), "detailsChartView", B_FOLLOW_ALL, B_WILL_DRAW) {

    SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}
