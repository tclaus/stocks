/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "SearchFieldControl.h"
#include <iostream>
#include "Window.h"

SearchFieldControl::SearchFieldControl()
        : BTextControl(BRect(), "searchField", "", "Search...", nullptr,
                       B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP) {

    Init();
};

SearchFieldControl::~SearchFieldControl() {}

void SearchFieldControl::Init() {
    SetModificationMessage(new BMessage(M_START_SHARES_SEARCH));
    SetViewColor(ui_color(B_PANEL_BACKGROUND_COLOR));
}

void
SearchFieldControl::AttachedToWindow() {
    SetTarget(this);
}

void
SearchFieldControl::MessageReceived(BMessage *message) {
    switch (message->what) {
        case (M_START_SHARES_SEARCH): {
            std::cout << "Forward message with text: " << this->Text() << std::endl;
            BMessage searchTerms(M_START_SHARES_SEARCH);
            searchTerms.AddString("search terms", this->Text());
            Window()->PostMessage(&searchTerms);
            break;
        }
        default:
            BTextControl::MessageReceived(message);
            break;
    }
}
