//
// Created by Thorsten Claus on 01.05.23.
//

#ifndef STOCKS_DETAILSHEADLINE_H
#define STOCKS_DETAILSHEADLINE_H

#include <View.h>
#include "Quote.h"

class DetailsHeadline : public BView {
public:

    DetailsHeadline();

    /**
     * Sets the current active quote to view its details.
     * @param quote The quote to show details.
     */
    void SetActiveQuote(Quote &quote);

private:
    Quote *fCurrentQuote;

};


#endif //STOCKS_DETAILSHEADLINE_H
