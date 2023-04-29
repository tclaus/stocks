//
// Created by Thorsten Claus on 01.03.23.
//

#include "Quote.h"

Quote::Quote() :
        symbol(new BString()),
        market(new BString()),
        companyName(new BString()),
        currency(new BString()),
        change(0.0),
        changesPercentage(0.0),
        latestPrice(0.0),
        dayLow(0.0),
        dayHigh(0.0),
        open(0.0),
        previousClose(0.0),
        volume(0),
        isWaitingForRequest(false),
        lastUpdatedAt(0s) {}

Quote::Quote(BString &symbolName)
        :
        Quote() {
    this->symbol = new BString(symbolName);
}

Quote::Quote(std::string *symbolName)
        :
        Quote() {
    this->symbol = new BString(symbolName->c_str());
}

void
Quote::SetLastUpdatedTimePoint() {
    lastUpdatedAt = std::chrono::high_resolution_clock::now();
}

timePoint
Quote::GetLastUpdatedTimePoint() {
    return lastUpdatedAt;
}
