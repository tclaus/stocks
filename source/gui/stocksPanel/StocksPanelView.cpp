/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */


#include "listView/ShareListItem.h"
#include "StocksPanelView.h"
#include "Portfolio.h"
#include "SearchFieldControl.h"
#include "StockListItemBuilder.h"
#include "../../api/ApiBuilder.h"
#include "../../api/NetRequester.h"
#include <LayoutBuilder.h>
#include <ScrollView.h>
#include <ListView.h>
#include <Button.h>
#include <private/netservices2/NetServicesDefs.h>
#include <iostream>

using BPrivate::Network::UrlEvent::RequestCompleted;

StocksPanelView::StocksPanelView()
        : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW),
          fSearchFieldControl(new SearchFieldControl()),
          searchResultList(new SearchResultList()),
          fSelectionOfSymbols(new SelectionOfSymbols()),
          fCurrentViewState(statePortfolioList) {

    listView = new BListView(BRect(), "stocksList",
                             B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL);
    listView->SetSelectionMessage(new BMessage(SearchFieldMessages::M_SET_STOCK));

    auto *scrollView =
            new BScrollView("scrollView", listView, B_FOLLOW_ALL, 0, false, true);
    fSearchReadyButton = new BButton("btnReady", "Fertig",
                                     new BMessage(SearchFieldMessages::M_ACCEPT_SELECTION));
    InitSearchReadyButton();

    BLayoutBuilder::Group<>(this, B_VERTICAL)
            .AddGroup(B_HORIZONTAL)
            .Add(fSearchFieldControl)
            .Add(fSearchReadyButton)
            .End()
            .Add(scrollView);

    ShowPortfolio();
    CreateApiConnection();
}

StocksPanelView::~StocksPanelView() {
    delete searchResultList;
    delete stockConnector;
    delete fSelectionOfSymbols;
}

void
StocksPanelView::InitSearchReadyButton() {
    fSearchReadyButton->Hide();
}

void
StocksPanelView::CreateApiConnection() {
    ApiBuilder apiBuilder = ApiBuilder();
    stockConnector = apiBuilder.CreateStockConnector(this);
}

void
StocksPanelView::SearchForSymbol(const char *searchSymbol) {
    searchRequestId = stockConnector->Search(searchSymbol);
}

void
StocksPanelView::HandleResult(int requestId) {
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

void
StocksPanelView::ListSearchResultsInListView() {
    auto itemsList = searchResultList->List();
    auto *foundSharesList = new BList();
    for (auto &foundShare: *itemsList) {
        foundSharesList->AddItem(BuildFoundShareItem(*foundShare));
    }
    ClearUsersSelectionsWhenSearchStarts();
    ClearListView();
    listView->AddList(foundSharesList);
}

void
StocksPanelView::ClearUsersSelectionsWhenSearchStarts() {
    if (fCurrentViewState != stateSearchResultsList) {
        ActivateSearchView();
        InitializeCurrentSelection();
    }
}

void StocksPanelView::ActivateSearchView() {
    fCurrentViewState = stateSearchResultsList;
    fSearchReadyButton->Show();
    fSelectionOfSymbols->Clear();
}

void StocksPanelView::InitializeCurrentSelection() {
    Portfolio &portfolio = Portfolio::Instance();
    for (auto const &quote: *portfolio.List()) {
        fSelectionOfSymbols->ToggleUserSelection(quote->symbol->String());
    }
}

FoundShareListItem
*StocksPanelView::BuildFoundShareItem(const SearchResultItem &searchResultItem) {
    Quote *quote = new Quote();
    quote->change = 0.0;
    quote->symbol = new BString(*searchResultItem.symbol);
    quote->latestPrice = 0;
    quote->companyName = new BString(*searchResultItem.name);
    quote->market = new BString(*searchResultItem.stockExchange);
    quote->currency = new BString(*searchResultItem.currency);
    return new FoundShareListItem(quote);
}

void
StocksPanelView::DismissSearch() {
    if (fCurrentViewState != stateSearchResultsList) {
        return;
    }
    ActivatePortfolioList();
    ShowPortfolio();
}

void
StocksPanelView::AcceptSearch() {
    if (fCurrentViewState != stateSearchResultsList) {
        return;
    }

    ActivatePortfolioList();

    Portfolio &portfolio = Portfolio::Instance();

    // Remove deselectd symbols
    for (auto &symbol: *fSelectionOfSymbols->ListToBeRemoved()) {
        printf("Deselected:  %s \n", symbol.c_str());
        portfolio.RemoveSymbol(symbol);
    }

    // Add new symbols as empty quotes
    for (auto &symbol: *fSelectionOfSymbols->ListToBeAdded()) {
        printf("New:  %s \n", symbol.c_str());
        Quote *newQuote = new Quote(&symbol);
        portfolio.AddQuote(newQuote);
    }

    ShowPortfolio();
}

void StocksPanelView::ActivatePortfolioList() {
    fCurrentViewState = statePortfolioList;
    fSearchReadyButton->Hide();
    fSearchFieldControl->ResetField();
}

void
StocksPanelView::ShowPortfolio() {
    ClearListView();
    LoadPortfolioList();
}

void
StocksPanelView::ClearListView() {
    listView->DoForEach([](BListItem *item) {
        if (auto foundShareListItem = dynamic_cast<ShareListItem *>(item)) {
            foundShareListItem->DetachFromParent();
        }
        return false;
    });

    listView->MakeEmpty();
}

void
StocksPanelView::LoadPortfolioList() {
    Portfolio &portfolio = Portfolio::Instance();
    for (auto const &quote: *portfolio.List()) {
        listView->AddItem(BuildPortfolioListItem(*quote));
    }
}

QuoteListItem
*StocksPanelView::BuildPortfolioListItem(Quote &quote) {
    auto stockListBuilder = new StockListItemBuilder();
    stockListBuilder->SetCompanyName(quote.companyName->String());
    stockListBuilder->SetStockTickerName(quote.symbol->String());
    stockListBuilder->SetProfitLoss(quote.change);
    stockListBuilder->SetClosingPrice(quote.latestPrice);
    stockListBuilder->SetStockExchangeName(quote.market->String());
    return stockListBuilder->Build();
}

void
StocksPanelView::MessageReceived(BMessage *message) {
    switch (message->what) {
        case FoundShareListItemEnum::CHECKBOX_CLICKED: {
            const char *symbol = message->GetString(FoundShareListItem::SYMBOL_NAME);
            fSelectionOfSymbols->ToggleUserSelection(std::string(symbol));
            break;
        }
        default: {
            BView::MessageReceived(message);
            break;
        }
    }
}

