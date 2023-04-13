//
// Created by Thorsten Claus on 19.03.23.
//

#include "SearchResultItem.h"

[[maybe_unused]] BString *
SearchResultItem::DisplayText() const {
    auto *displayText = new BString();
    displayText->Append(*name);
    displayText->Append(", ");
    displayText->Append(*stockExchange);
    displayText->Append(" ");
    displayText->Append(*currency);
    return displayText;
}