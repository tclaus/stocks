/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "SearchFieldControl.h"
#include "Window.h"

SearchFieldControl::SearchFieldControl()
        : BTextControl(BRect(), "searchField", "", "Search...", nullptr,
                       B_FOLLOW_LEFT_RIGHT | B_FOLLOW_TOP) {

    Init();
}

void SearchFieldControl::Init() {
    SetModificationMessage(new BMessage(SearchFieldMessages::M_START_SHARES_SEARCH));
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
            BMessage searchTerms(SearchFieldMessages::M_START_SHARES_SEARCH);
            searchTerms.AddString(SEARCH_TERM, this->Text());
            Window()->PostMessage(&searchTerms);
            break;
        }
        default:
            BTextControl::MessageReceived(message);
            break;
    }
}
