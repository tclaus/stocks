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
Portfolio::RemoveSymbol(std::string &symbol) {
    fQuotesMap->erase(symbol);
}

BList *
Portfolio::List() {
    auto *listOfQuotes = new BList();
    for (auto const &pair: *fQuotesMap) {
        listOfQuotes->AddItem(pair.second);
    }
    return listOfQuotes;
}