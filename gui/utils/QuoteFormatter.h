//
// Created by Thorsten Claus on 06.03.23.
//

#ifndef STOCKS_QUOTEFORMATTER_H
#define STOCKS_QUOTEFORMATTER_H

#include "Quote.h"
#include <GraphicsDefs.h>

class QuoteFormatter {
public:
    QuoteFormatter(Quote *quote);

    ~QuoteFormatter() {};

    const char *ChangeToString() const;

    const rgb_color *ChangeBackground() const;

private:
    Quote *fQuote;
};


#endif //STOCKS_QUOTEFORMATTER_H
