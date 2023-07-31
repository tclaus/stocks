//
// Created by Thorsten Claus on 09.03.23.
//

#include "Portfolio.h"

Portfolio Portfolio::instance = Portfolio();

Portfolio::Portfolio()
        :
        fQuotesMap(new std::map<std::string, Quote *>),
        fCurrentQuote(nullptr) {
}

Portfolio &
Portfolio::Instance() {
    return instance;
}

Quote *Portfolio::RetrieveOrCreateQuoteBySymbol(const char *symbol) {
    std::string symbolAsString = symbol;

    auto const &iterator = fQuotesMap->find(symbolAsString);
    if (iterator != fQuotesMap->end()) {
        return iterator->second;
    }

    auto *newQuote = new Quote(new std::string(symbol));
    AddQuote(newQuote);
    return newQuote;
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

bool
Portfolio::QuoteExists(const char *symbol) {
    auto const &iterator = fQuotesMap->find(symbol);
    return (iterator != fQuotesMap->end());
}

void
Portfolio::SetCurrentQuote(Quote *quote) {
    if (fCurrentQuote != quote) {
        fCurrentQuote = quote;
        Notify();
    }
}

Quote *
Portfolio::GetCurrentQuote() {
    return fCurrentQuote;
}

void Portfolio::ClearCurrentSelection() {
    if (fCurrentQuote != nullptr) {
        fCurrentQuote = nullptr;
        Notify();
    }
}

