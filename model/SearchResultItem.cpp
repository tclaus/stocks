//
// Created by Thorsten Claus on 19.03.23.
//

#include "SearchResultItem.h"

BString *
SearchResultItem::DisplayText() {
    auto *displayText = new BString();
    displayText->Append(*name);
    displayText->Append(", ");
    displayText->Append(*stockExchange);
    displayText->Append(" ");
    displayText->Append(*currency);
    return displayText;
}