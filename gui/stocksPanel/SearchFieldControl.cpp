/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "SearchFieldControl.h"

SearchFieldControl::SearchFieldControl()
        : BTextControl(BRect(), "searchField", "", "Search...", nullptr,
                       B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP) {

    SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
};

SearchFieldControl::~SearchFieldControl() {}
