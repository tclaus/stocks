/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "StockListItemBuilder.h"
#include <LayoutBuilder.h>
#include <StringView.h>
#include <String.h>
#include <iostream>

void StockListItemBuilder::SetStockTickerName(const char *tickerName) {
    _tickerName = new BString(tickerName);
}

void StockListItemBuilder::SetClosingPrice(float closingPrice) {
    _closingPrice = closingPrice;
}

void StockListItemBuilder::SetStockExchangeName(const char *stockExchangeName) {
    _stockExchangeName = new BString(stockExchangeName);
}

void StockListItemBuilder::SetCompanyName(const char *companyName) {
    _companyName = new BString(companyName);
}

void StockListItemBuilder::SetProfitLoss(float profitLoss) {
    _profitLoss = profitLoss;
}

QuoteListItem *StockListItemBuilder::Build() {

    Quote *quote = new Quote();
    quote->change = _profitLoss;
    quote->symbol = new BString(_tickerName->String());
    quote->latestPrice = _closingPrice;
    quote->companyName = new BString(_companyName->String());
    quote->market = new BString("NYSE");
    return new QuoteListItem(quote);
}



