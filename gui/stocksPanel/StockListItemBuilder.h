/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef STOCK_LIST_ITEM_H
#define STOCK_LIST_ITEM_H

#include <SupportDefs.h>
#include <View.h>
#include "listView/QuoteListItem.h"

class StockListItemBuilder {

public:
    void SetStockTickerName(const char *tickerName);

    void SetCompanyName(const char *companyName);

    void SetClosingPrice(float closingPrice);

    void SetStockExchangeName(const char *stockExchangeName);

    void SetProfitLoss(float profitLoss);

    QuoteListItem *Build();

private:

    const BString *_tickerName;
    const BString *_companyName;
    float _closingPrice;
    const BString *_stockExchangeName;
    float _profitLoss;
};

#endif // STOCK_LIST_ITEM_H
