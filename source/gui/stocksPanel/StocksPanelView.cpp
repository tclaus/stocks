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
#include "QuoteRequestStore.h"

#include <LayoutBuilder.h>
#include <ScrollView.h>
#include <ListView.h>
#include <Button.h>
#include <private/netservices2/NetServicesDefs.h>
#include <unordered_set>

using BPrivate::Network::UrlEvent::RequestCompleted;

StocksPanelView::StocksPanelView()
        : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW),
          fSearchFieldControl(new SearchFieldControl()),
          searchResultList(new SearchResultList()),
          fSelectionOfSymbols(new SelectionOfSymbols()),
          fSearchRequestId(0),
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
    fSearchRequestId = stockConnector->Search(searchSymbol);
}

void
StocksPanelView::RequestQuoteDetailsForSymbol(const char *symbol) {
    int quoteRequestId = stockConnector->RetrieveQuote(symbol);
    printf("New RetrieveQuote RequestId: %d. \n", quoteRequestId);

    Portfolio &portfolio = Portfolio::Instance();
    Quote *requestingQuote = portfolio.RetrieveQuoteBySymbol(symbol);
    if (requestingQuote) {
        QuoteRequestStore &quoteRequestStore = QuoteRequestStore::Instance();
        quoteRequestStore.AddQuoteRequestId(quoteRequestId, *requestingQuote);
    }
}

void
StocksPanelView::HandleResult(int requestId) {
    if (requestId == fSearchRequestId) {
        HandleSearchResult(requestId);
    }
}

void
StocksPanelView::HandleSearchResult(int searchResultId) {
    BString *searchResult = NetRequester::Instance().Result(searchResultId);
    searchResultList->ListFromJson(searchResult);
    ListSearchResultsInListView();
    fSearchRequestId = 0;
}

void
StocksPanelView::ListSearchResultsInListView() {
    auto itemsList = searchResultList->List();
    auto *foundSharesList = new BList();
    StringSet *alreadySelectedSymbol = CreateSetOfSymbolsInPortfolio();
    for (auto &foundShare: *itemsList) {
        FoundShareListItem *foundShareListItem = BuildFoundShareItem(*foundShare);

        if (alreadySelectedSymbol->find(std::string(foundShare->symbol->String())) !=
            alreadySelectedSymbol->end()) {

            foundShareListItem->Select();
        }

        foundSharesList->AddItem(foundShareListItem);
    }
    delete alreadySelectedSymbol;

    ClearUsersSelectionsWhenSearchStarts();
    ClearListView();
    listView->AddList(foundSharesList);
}

StringSet *
StocksPanelView::CreateSetOfSymbolsInPortfolio() {
    Portfolio &portfolio = Portfolio::Instance();
    StringSet *alreadySelectedSymbol = new StringSet;
    // Fill a set from List
    for (auto const &quote: *portfolio.List()) {
        alreadySelectedSymbol->insert(std::string(quote->symbol->String()));
    }
    return alreadySelectedSymbol;
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

/**
 * Already selected symbols are remembered during the search. The current symbols are copied to the search results list
 * so that a deselection can remove an existing symbol and new ones can be added to the portfolio.
 */
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

    // Remove deselected symbols
    for (auto &symbol: *fSelectionOfSymbols->ListToBeRemoved()) {
        printf("Deselected:  %s \n", symbol.c_str());
        portfolio.RemoveQuoteBySymbol(symbol);
    }

    // Add new symbols as empty quotes
    for (auto &symbol: *fSelectionOfSymbols->ListToBeAdded()) {
        printf("New:  %s \n", symbol.c_str());
        Quote *newQuote = new Quote(&symbol);
        portfolio.AddQuote(newQuote);
        RequestQuoteDetailsForSymbol(newQuote->symbol->String());
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

