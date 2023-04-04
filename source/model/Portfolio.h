//
// Created by Thorsten Claus on 09.03.23.
//

#ifndef STOCKS_PORTFOLIO_H
#define STOCKS_PORTFOLIO_H


#include "Quote.h"
#include <map>
#include <clocale>
#include <string>
#include <list>

class Portfolio {
public:
    Portfolio(const Portfolio &) = delete;

    static Portfolio &Instance();

    void AddQuote(Quote *quote);

    void RemoveQuote(Quote &quote);

    void RemoveSymbol(std::string &symbol);

    /**
     * Returns a copy of the list
     * @return
     */
    std::list<Quote *> *List();

    // Save to disk
    // Load from disk

private:
    Portfolio();

private:
    static Portfolio instance;
    std::map<std::string, Quote *> *fQuotesMap;
};


#endif //STOCKS_PORTFOLIO_H
