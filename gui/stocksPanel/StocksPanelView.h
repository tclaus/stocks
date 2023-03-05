/*
 * Copyright 2018, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef StocksPanelView_H
#define StocksPanelView_H

#include "QuoteListItem.h"
#include <SupportDefs.h>
#include <ListView.h>
#include <View.h>

class StocksPanelView : public BView {

public:
    StocksPanelView();

    virtual ~StocksPanelView();

private:
    BListView *fListView;

    // Textfield
    QuoteListItem *buildItem();
};

#endif // StocksPanelView_H
