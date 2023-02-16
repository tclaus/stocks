/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "StockListItemBuilder.h"
#include <LayoutBuilder.h>
#include <StringView.h>
#include <iomanip>
#include <locale>
#include <iostream>
#include <sstream>


void StockListItemBuilder::StockListItem(const char* tickerName) {
    _tickerName = new BString(tickerName);
}

void StockListItemBuilder::SetClosingPrice(float closingPrice) {
    _closingPrice = closingPrice;
}

void StockListItemBuilder::SetStockExchangeName(const char* stockExchangeName) {
    _stockExchangeName = new BString(stockExchangeName);
}

void StockListItemBuilder::SetStockName(const char* stockName) {
    _stockName = new BString(stockName);
}

void StockListItemBuilder::SetProfitLoss(float profitLoss) {
    _profitLoss = profitLoss;
}

BListItemView *StockListItemBuilder::Build() {

    BString listItemName = BString("item_");
    listItemName.Append(listItemName);

    BRect rect = BRect();
    BView* view = new BView(rect, listItemName.String(),0,B_HORIZONTAL );

    BLayoutBuilder::Group<>(view, B_HORIZONTAL,B_USE_DEFAULT_SPACING)
            .AddGroup(B_VERTICAL,B_USE_DEFAULT_SPACING,1.0f)
                .Add(new BStringView("tickerNameView", _tickerName->String() ,B_WILL_DRAW))
                .Add(new BStringView("stockNameView", _stockName->String(), B_WILL_DRAW))
            .End()
            .AddGlue()
            .AddGroup(B_VERTICAL, B_USE_DEFAULT_SPACING, 1.0)
                .Add(MakeLastPriceView())
                .Add(MakeProfitLossView())
            .End();

}

BView *StockListItemBuilder::MakeLastPriceView() {
    BString* lastPriceString = new BString();
    lastPriceString->SetToFormat( "%f", _closingPrice);
    BStringView* lastPriceStringView = new BStringView("lastPriceView", lastPriceString->String(), B_WILL_DRAW);
    lastPriceStringView->SetAlignment(B_ALIGN_RIGHT);
    return lastPriceStringView;
}

BView *StockListItemBuilder::MakeProfitLossView() {
    BString* profitLossString = new BString();
    profitLossString->SetToFormat( "%f", _profitLoss);
    BStringView* profitLossStringView new BStringView("profitLossView", profitLossString, B_WILL_DRAW);
    profitLossStringView->SetAlignment(B_ALIGN_RIGHT);
    //TODO Grün/Rot einfärben bei profit/loss
    return profitLossStringView;
}


