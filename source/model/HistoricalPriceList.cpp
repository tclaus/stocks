//
// Created by Thorsten Claus on 19.07.23.
//

#include <cstdio>
#include <cmath>
#include "HistoricalPriceList.h"

HistoricalPriceList::HistoricalPriceList() :
        fHistoricalPrices(new std::list<HistoricalPrice *>()) {
}

HistoricalPriceList::HistoricalPriceList(const HistoricalPriceList &original) {
    fHistoricalPrices = new std::list<HistoricalPrice *>(*original.fHistoricalPrices);
}


HistoricalPriceList::~HistoricalPriceList() {
    delete fHistoricalPrices;
}

std::list<HistoricalPrice *> *
HistoricalPriceList::List() {
    return fHistoricalPrices;
}

float
HistoricalPriceList::GetMaxClosingPrice() {
    if (fMaxClosingPrice < 0.1) {
        for (const auto &item: *fHistoricalPrices)
            fMaxClosingPrice = std::max(fMaxClosingPrice, item->GetClose());
    }
    return fMaxClosingPrice;
}

float
HistoricalPriceList::GetMinClosingPrice() {
    if (fMinClosingPrice < 0.1) {
        fMinClosingPrice = MAXFLOAT;
        for (const auto &item: *fHistoricalPrices)
            fMinClosingPrice = std::min(fMinClosingPrice, item->GetClose());
    }
    return fMinClosingPrice;
}
