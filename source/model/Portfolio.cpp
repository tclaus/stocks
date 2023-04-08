//
// Created by Thorsten Claus on 09.03.23.
//

#include "Portfolio.h"
#include "List.h"

Portfolio Portfolio::instance = Portfolio();

Portfolio::Portfolio()
        :
        fQuotesMap(new std::map<std::string, Quote *>) {
}

Portfolio &
Portfolio::Instance() {
    return instance;
}

void
Portfolio::AddQuote(Quote *quote) {
    fQuotesMap->insert_or_assign(
            std::string(quote->symbol->String()), quote
    );
}

void
Portfolio::RemoveQuote(Quote &quote) {
    fQuotesMap->erase(std::string(quote.symbol->String()));
}

void
Portfolio::RemoveQuoteBySymbol(std::string &symbol) {
    fQuotesMap->erase(symbol);
}

std::list<Quote *> *
Portfolio::List() {
    auto *listOfQuotes = new std::list<Quote *>();
    for (auto const &pair: *fQuotesMap) {
        listOfQuotes->push_back(pair.second);
    }
    return listOfQuotes;
}

/**
 * Find the RetrieveQuote identified by its symbol name.
 * @param symbol
 * @return The quote found in the portfolio, a nullptr if not found.
 */
Quote *Portfolio::RetrieveQuoteBySymbol(const char *symbol) {
    std::string symbolAsString = symbol;

    auto const &iterator = fQuotesMap->find(symbolAsString);
    if (iterator != fQuotesMap->end()) {
        return iterator->second;
    }
    return nullptr;
}
