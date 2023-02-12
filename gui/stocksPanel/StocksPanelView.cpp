/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */

#include "StocksPanelView.h"
#include "SearchFieldControl.h"
#include <LayoutBuilder.h>
#include <ScrollView.h>

StocksPanelView::StocksPanelView()
    : BView(BRect(), "stocksView", B_FOLLOW_ALL, B_WILL_DRAW) {

  SearchFieldControl *searchFieldControl = new SearchFieldControl();

  BListView *listView = new BListView(BRect(), "stocksList",
                                      B_SINGLE_SELECTION_LIST, B_FOLLOW_ALL);
  listView->SetSelectionMessage(new BMessage(M_SET_STOCK));
  listView->AddItem(new BStringItem("Dax"));
  listView->AddItem(new BStringItem("Apple Inc."));
  listView->AddItem(new BStringItem("Tesla"));
  listView->AddItem(new BStringItem("Volkswagen"));

  BScrollView *scrollView =
      new BScrollView("scrollView", listView, B_FOLLOW_ALL, 0, false, true);

  BLayoutBuilder::Group<>(this, B_VERTICAL)
      .Add(searchFieldControl)
      .Add(scrollView);
}

StocksPanelView::~StocksPanelView() {}
