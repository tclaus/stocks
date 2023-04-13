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

    bool QuoteExists(const char *symbol);

    void RemoveQuote(Quote &quote);

    void RemoveQuoteBySymbol(std::string &symbol);

    /**
     * Retrieves or creates a quote by this symbol.
     * @param symbol A quote symbol
     * @return An existing quote or a new one.
     */
    Quote *RetrieveOrCreateQuoteBySymbol(const char *symbol);

    /**
     * Returns a copy of the list
     * @return
     */
    std::list<Quote *> *List();

    // Save to disk
    // Load from disk

private:
    Portfolio();

    void AddQuote(Quote *quote);

private:
    static Portfolio instance;
    /// Quotes by its symbol
    std::map<std::string, Quote *> *fQuotesMap;
};


#endif //STOCKS_PORTFOLIO_H
