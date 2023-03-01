/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "StocksPanelView.h"
#include "SearchFieldControl.h"
#include "StockListItemBuilder.h"

#include <LayoutBuilder.h>
#include <ScrollView.h>

StocksPanelView::StocksPanelView()
        : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW) {

    SearchFieldControl *searchFieldControl = new SearchFieldControl();

    BListView *listView = new BListView(BRect(), "stocksList",
                                        B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL);
    listView->SetSelectionMessage(new BMessage(M_SET_STOCK));

    BListItemView *stockItem = buildItem();

    listView->AddItem(stockItem);

    BScrollView *scrollView =
            new BScrollView("scrollView", listView, B_FOLLOW_ALL, 0, false, true);

    BLayoutBuilder::Group<>(this, B_VERTICAL)
            .Add(searchFieldControl)
            .Add(scrollView);
}

StocksPanelView::~StocksPanelView() {}

BListItemView *StocksPanelView::buildItem() {
    auto stockListBuilder = new StockListItemBuilder();
    stockListBuilder->SetStockName("Linde");
    stockListBuilder->SetProfitLoss(41.0f);
    stockListBuilder->SetStockTickerName("LIN");
    stockListBuilder->SetStockExchangeName("Ney York Stock Exchange");
    return stockListBuilder->Build();
}