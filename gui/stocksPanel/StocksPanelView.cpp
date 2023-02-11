/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "StocksPanelView.h"

StocksPanelView::StocksPanelView()
    : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW) {

  SetViewColor(128, 10, 10);
}

StocksPanelView::~StocksPanelView() {}
