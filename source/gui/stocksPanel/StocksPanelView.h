/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef StocksPanelView_H
#define StocksPanelView_H

#include "listView/QuoteListItem.h"
#include "listView/FoundShareListItem.h"
#include "StockConnector.h"
#include "SearchResultList.h"
#include "SelectionOfSymbols.h"
#include "SearchFieldControl.h"
#include <SupportDefs.h>
#include <ListView.h>
#include <View.h>
#include <list>

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
     * Cancels a running search and shows the portfolio list.
     */
    void DismissSearch();

    /**
     * Clears the current list and shows all share items of the portfolio.
     */
    void ShowPortfolio();

    void MessageReceived(BMessage *message) override;

private:

    void CreateApiConnection();

    void HandleSearchResult(int searchRequestId);

    void ListSearchResultsInListView();

    FoundShareListItem *BuildFoundShareItem(const SearchResultItem &searchResultItem);

    /**
     * Clears the listview.
     */
    void ClearListView();

    void LoadDemoStocks();

    QuoteListItem *buildItem1();

    QuoteListItem *buildItem2();

    QuoteListItem *buildItem3();

private:
    BListView *listView;
    StockConnector *stockConnector;
    int searchRequestId;
    SearchFieldControl *fSearchFieldControl;
    SearchResultList *searchResultList;
    SelectionOfSymbols *fSelectionOfSymbols;
    enum ViewState {
        stateSearchResultsList,
        statePortfolioList
    };
/**
 * Provides the current state what the list shows. If a search result is currently showing and a esc key is pressed by the user,
 * no new reload of the list should be done.
 */
    ViewState fCurrentViewState;

    void ClearUsersSelectionsWhenSearchStarts();
};

#endif // StocksPanelView_H
