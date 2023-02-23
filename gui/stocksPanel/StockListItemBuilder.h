/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef STOCK_LIST_ITEM_H
#define STOCK_LIST_ITEM_H


#include <SupportDefs.h>
#include <View.h>
#include "BListItemView.h"

class StockListItemBuilder {

public:
	void StockListItem(const char* tickerName);
    void SetStockName(const char* stockName);
    void SetClosingPrice(float closingPrice);
    void SetStockExchangeName(const char* stockExchangeName);
    void SetProfitLoss(float profitLoss);
    BListItemView* Build();

private:
    BView* MakeLastPriceView();
    BView* MakeProfitLossView();
    const BString* _tickerName;
    const BString* _stockName;
    float _closingPrice;
    const BString* _stockExchangeName;
    float _profitLoss;
};

#endif // STOCK_LIST_ITEM_H
