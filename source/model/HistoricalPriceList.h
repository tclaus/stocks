//
// Created by Thorsten Claus on 19.07.23.
//

#ifndef STOCKS_HISTORICALPRICELIST_H
#define STOCKS_HISTORICALPRICELIST_H

#include "HistoricalPrice.h"

#include <List.h>
#include <list>

class HistoricalPriceList {
public:
    HistoricalPriceList();

    HistoricalPriceList(const HistoricalPriceList &historicalPriceList);

    ~HistoricalPriceList();

    float MaxPrice();

    std::list<HistoricalPrice *> *List();

    void Clear();

    float GetMinClosingPrice();

    float GetMaxClosingPrice();

private:
    std::list<HistoricalPrice *> *fHistoricalPrices;
    float fMinClosingPrice = 0.0;
    float fMaxClosingPrice = 0.0;

};


#endif //STOCKS_HISTORICALPRICELIST_H
