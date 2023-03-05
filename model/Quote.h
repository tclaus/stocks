//
// Created by Thorsten Claus on 01.03.23.
//

#ifndef STOCKS_QUOTE_H
#define STOCKS_QUOTE_H

#include <String.h>

class Quote {

public:
    BString *symbol;
    BString *market;
    BString *companyName;
    double change;
    double latestPrice;
    double high;
    double low;

};


#endif //STOCKS_QUOTE_H
