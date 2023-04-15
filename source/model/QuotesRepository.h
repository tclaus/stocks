//
// Created by Thorsten Claus on 15.04.23.
//

#ifndef STOCKS_QUOTESREPOSITORY_H
#define STOCKS_QUOTESREPOSITORY_H

#include "Quote.h"
#include <list>

class QuotesRepository {

public:
    void StoreQuotes(const std::list<Quote *> &quotes);

    void RestoreQuotes(const std::list<Quote *> &quotes);

private:
    status_t ReadFile(const char &content);

    void WriteFile(const char &content);
};


#endif //STOCKS_QUOTESREPOSITORY_H
