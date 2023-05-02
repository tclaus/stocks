//
// Created by Thorsten Claus on 01.05.23.
//

#ifndef STOCKS_DETAILSHEADLINE_H
#define STOCKS_DETAILSHEADLINE_H

#include <View.h>
#include <StringView.h>
#include "Quote.h"

class DetailsHeadline : public BView, Observer {
public:

    DetailsHeadline();

    /**
     * Sets the current active quote to view its details.
     * @param quote The quote to show details.
     */
    void SetActiveQuote(Quote *quote);

private:
    Quote *fCurrentQuote;
    BStringView *fSymbolShortNameLabel;
    BStringView *fSymbolFullNameLabel;
    BStringView *fSymbolPriceLabel;

    void CreateSymbolShortNameLabel();

    void CreateSymbolFullNameLabel();

    void CreateSymbolPriceLabel();

    void InitStringViews();

    void UpdateStatus();

    void UpdateLabels();
};


#endif //STOCKS_DETAILSHEADLINE_H
