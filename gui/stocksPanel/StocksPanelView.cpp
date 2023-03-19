/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "StocksPanelView.h"
#include "SearchFieldControl.h"
#include "StockListItemBuilder.h"
#include "../../api/ApiBuilder.h"

#include <LayoutBuilder.h>
#include <ScrollView.h>
#include <private/netservices2/NetServicesDefs.h>

using BPrivate::Network::UrlEvent::RequestCompleted;

StocksPanelView::StocksPanelView()
        : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW) {

    SearchFieldControl *searchFieldControl = new SearchFieldControl();

    listView = new BListView(BRect(), "stocksList",
                             B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL);
    listView->SetSelectionMessage(new BMessage(M_SET_STOCK));

    BScrollView *scrollView =
            new BScrollView("scrollView", listView, B_FOLLOW_ALL, 0, false, true);

    BLayoutBuilder::Group<>(this, B_VERTICAL)
            .Add(searchFieldControl)
            .Add(scrollView);

    LoadDemoStocks();
    CreateApiConnection();
}

StocksPanelView::~StocksPanelView() {}

void StocksPanelView::MessageReceived(BMessage *message) {
    switch (message->what) {
        case RequestCompleted: {
            auto identifier = message->GetInt32(BPrivate::Network::UrlEventData::Id, -1);
            printf("Search Message received: %d", identifier);
            break;
        }
        default: {
            BView::MessageReceived(message);
            break;
        }
    }
}

void StocksPanelView::CreateApiConnection() {
    ApiBuilder apiBuilder = ApiBuilder();
    stockConnector = apiBuilder.CreateStockConnector(this);
}

void StocksPanelView::SearchForSymbol() {

    const char *searchSymbol = "APPL";
    stockConnector->Search(searchSymbol);

}

void StocksPanelView::LoadDemoStocks() {
    listView->AddItem(buildItem1());
    listView->AddItem(buildItem2());
    listView->AddItem(buildItem3());
}

void StocksPanelView::FillCustomStocksList() {

    SearchForSymbol();
}

QuoteListItem *StocksPanelView::buildItem1() {
    auto stockListBuilder = new StockListItemBuilder();
    stockListBuilder->SetCompanyName("Linde PLC");
    stockListBuilder->SetStockTickerName("LIN.DE");
    stockListBuilder->SetProfitLoss(1.8f); // Absolut oder Prozent?
    stockListBuilder->SetClosingPrice(338.10f);
    stockListBuilder->SetStockExchangeName("New York Stock Exchange");
    return stockListBuilder->Build();
}

QuoteListItem *StocksPanelView::buildItem2() {
    auto stockListBuilder = new StockListItemBuilder();
    stockListBuilder->SetCompanyName("2G Energy AG");
    stockListBuilder->SetStockTickerName("2GB.DE");
    stockListBuilder->SetProfitLoss(-2.01f); //Prozent?
    stockListBuilder->SetClosingPrice(22.80f);
    stockListBuilder->SetStockExchangeName("XETRA");
    return stockListBuilder->Build();
}

QuoteListItem *StocksPanelView::buildItem3() {
    auto stockListBuilder = new StockListItemBuilder();
    stockListBuilder->SetCompanyName("Vimeo, Inc");
    stockListBuilder->SetStockTickerName("VMEO");
    stockListBuilder->SetProfitLoss(6.81f); //Prozent?
    stockListBuilder->SetClosingPrice(3.920f); // bei kleinen zahlen drei nachkommas?
    stockListBuilder->SetStockExchangeName("NYSE");
    return stockListBuilder->Build();
}