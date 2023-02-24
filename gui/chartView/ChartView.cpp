
/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "ChartView.h"
#include <LayoutBuilder.h>
#include <StringView.h>
#include <View.h>

ChartView::ChartView()
    : BView(BRect(0, 0, 300, 200), "mainView", B_FOLLOW_ALL, B_WILL_DRAW) {

  this->SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));

  BStringView *placeholderText =
      new BStringView("placeholderLabel", "Choose a share from the shares list");

  BLayoutBuilder::Group<>(this, B_VERTICAL)
      .AddGrid()
      .Add(placeholderText, 1, 1);
}

ChartView::~ChartView() = default;
