/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef StocksPanelView_H
#define StocksPanelView_H

#include "listView/QuoteListItem.h"
#include "listView/FoundShareListItem.h"
#include "Quote.h"
#include "StockConnector.h"
#include "SearchResultList.h"
#include "SelectionOfSymbols.h"
#include "SearchFieldControl.h"
#include <SupportDefs.h>
#include <ListView.h>
#include <View.h>
#include <list>
#include <Button.h>
#include <unordered_set>
#include <map>

typedef std::unordered_set<std::string> StringSet;

class StocksPanelView : public BView {

public:
    StocksPanelView();

    ~StocksPanelView() override;

    /**
     * Handles the completed request with id requestID.
     * @param requestId
     */
    void HandleResult(int requestId);

    void SearchForSymbol(const char *searchSymbol);

    /**
     * Cancels a running search and shows the portfolio fList.
     */
    void DismissSearch();

    /**
     * Accepts the search selection
     */
    void AcceptSearch();

    /**
     * Clears the current fList and shows all share items of the portfolio.
     */
    void ShowPortfolio();

    void MessageReceived(BMessage *message) override;

    void StockSelected();

private:

    void CreateApiConnection();

    void HandleSearchResult(int searchRequestId);

    void ListSearchResultsInListView();

    FoundShareListItem *BuildFoundShareItem(const SearchResultItem &searchResultItem);

    /**
     * Clears the listview.
     */
    void ClearListView();

    void LoadPortfolioList();

private:

    BListView *listView;

    std::map<BString, QuoteListItem *> *fQuoteListItems;
    StockConnector *stockConnector;
    SearchFieldControl *fSearchFieldControl;
    BButton *fSearchReadyButton;
    SearchResultList *searchResultList;
    SelectionOfSymbols *fSelectionOfSymbols;
    int fSearchRequestId;
    enum ViewState {
        modeSearchResultsList,
        modePortfolioList
    };

/**
 * Provides the current state what the fList shows. If a search result is currently showing and a esc key is pressed by the user,
 * no new reload of the fList should be done.
 */
    ViewState fCurrentViewMode;

    StringSet *CreateSetOfSymbolsInPortfolio();

    void ClearUsersSelectionsWhenSearchStarts();

    void InitSearchReadyButton();

    void ActivatePortfolioMode();

    void ActivateSearchMode();

    /**
     * set up the search selection with symbols already in the portfolio.
     */
    void InitializeCurrentSelection();

    void RemoveCachedQuoteListItem(const std::string &symbol);

    QuoteListItem *AddOrCreateCachedQuoteListItem(Quote *const &quote);

    void InitStoredSymbols();
};

#endif // StocksPanelView_H
