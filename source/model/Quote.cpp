//
// Created by Thorsten Claus on 01.03.23.
//

#include "Quote.h"

Quote::Quote() :
        symbol(new BString()),
        market(new BString()),
        companyName(new BString()),
        currency(new BString()),
        lastUpdated(0s),
        change(0.0),
        latestPrice(0.0),
        high(0.0),
        low(0.0) {}

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

void Quote::SetLastUpdatedTimePoint() {
    lastUpdated = std::chrono::high_resolution_clock::now();
}
