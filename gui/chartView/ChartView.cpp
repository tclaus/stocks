
/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "ChartView.h"

ChartView::ChartView()
    : BView(BRect(0, 0, 300, 200), "mainView", B_FOLLOW_ALL, B_WILL_DRAW) {

  SetViewColor(10, 128, 10);
}

ChartView::~ChartView() {}
