//
// Created by Thorsten Claus on 09.03.23.
//

#ifndef STOCKS_PORTFOLIO_H
#define STOCKS_PORTFOLIO_H


#include "Quote.h"
#include "List.h"

class Portfolio {
public:
    void AddQuote(Quote *quote);

    void RemoveQuote(Quote *quote);

    // Iterator ?
private:
    BList *list;
};


#endif //STOCKS_PORTFOLIO_H
