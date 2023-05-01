/*
 * Copyright 2023, Your Name <your@email.address>
 * All rights reserved. Distributed under the terms of the MIT license.
 */
#ifndef CHARTVIEW_H
#define CHARTVIEW_H

#include <SupportDefs.h>
#include <View.h>
#include "Quote.h"

class ChartView : public BView {
public:
    ChartView();

    // SetActiveQuote
    /**
     * Sets the current active quote to view its details.
     * @param quote The quote to show details.
     */
    void SetActiveQuote(Quote &quote);

    // ClearActiveQuote
    //

private:
    Quote *fCurrentQuote;
};

#endif // CHARTVIEW_H
