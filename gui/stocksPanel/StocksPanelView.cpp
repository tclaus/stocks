/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#include <iostream>

#include "StocksPanelView.h"
#include "SearchFieldControl.h"
#include "StockListItemBuilder.h"
#include "../../api/ApiBuilder.h"

#include <LayoutBuilder.h>
#include <ScrollView.h>
#include <private/netservices2/NetServicesDefs.h>
#include "../../api/NetRequester.h"

using BPrivate::Network::UrlEvent::RequestCompleted;

StocksPanelView::StocksPanelView()
        : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW),
          searchResultList(new SearchResultList()) {

    auto *searchFieldControl = new SearchFieldControl();

    listView = new BListView(BRect(), "stocksList",
                             B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL);
    listView->SetSelectionMessage(new BMessage(SearchFieldMessages::M_SET_STOCK));

    auto *scrollView =
            new BScrollView("scrollView", listView, B_FOLLOW_ALL, 0, false, true);

    BLayoutBuilder::Group<>(this, B_VERTICAL)
            .Add(searchFieldControl)
            .Add(scrollView);

    LoadDemoStocks();
    CreateApiConnection();
}

StocksPanelView::~StocksPanelView() {
    delete searchResultList;
    delete stockConnector;
}

void StocksPanelView::CreateApiConnection() {
    ApiBuilder apiBuilder = ApiBuilder();
    stockConnector = apiBuilder.CreateStockConnector(this);
}

void StocksPanelView::SearchForSymbol(const char *searchSymbol) {
    searchRequestId = stockConnector->Search(searchSymbol);
}

void
StocksPanelView::HandleResult(int requestId) {
    std::cout << "Handle result in StockPanelView" << std::endl;
    if (requestId == searchRequestId) {
        HandleSearchResult(requestId);
    }
}

void
StocksPanelView::HandleSearchResult(int searchResultId) {
    BString *searchResult = NetRequester::Instance().Result(searchResultId);
    searchResultList->ListFromJson(searchResult);
    ListSearchResultsInListView();
    searchRequestId = 0;
}

void StocksPanelView::ListSearchResultsInListView() {
    auto itemsList = searchResultList->List();
    std::cout << "Start creating the search list view" << std::endl;

    auto *foundSharesList = new BList();
    for (auto &foundShare: *itemsList) {
        foundSharesList->AddItem(new BStringItem(foundShare->DisplayText()->String()));
    }

    listView->MakeEmpty();
    listView->AddList(foundSharesList);
}

void StocksPanelView::LoadDemoStocks() {
    listView->AddItem(buildItem1());
    listView->AddItem(buildItem2());
    listView->AddItem(buildItem3());
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