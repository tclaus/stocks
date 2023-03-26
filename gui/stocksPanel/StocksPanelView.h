/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef StocksPanelView_H
#define StocksPanelView_H

#include "QuoteListItem.h"
#include "FoundShareListItem.h"
#include "../../api/StockConnector.h"
#include "../../model/SearchResultList.h"
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

private:

    void CreateApiConnection();

    void HandleSearchResult(int searchRequestId);

    void ListSearchResultsInListView();

    FoundShareListItem *BuildFoundShareItem(const SearchResultItem &searchResultItem);

    void LoadDemoStocks();

    QuoteListItem *buildItem1();

    QuoteListItem *buildItem2();

    QuoteListItem *buildItem3();

private:
    BListView *listView;
    StockConnector *stockConnector;
    int searchRequestId;
    SearchResultList *searchResultList;
};

#endif // StocksPanelView_H
