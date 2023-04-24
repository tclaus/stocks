//
// Created by Thorsten Claus on 15.04.23.
//

#ifndef STOCKS_QUOTESREPOSITORY_H
#define STOCKS_QUOTESREPOSITORY_H

#include "Quote.h"
#include "RepositoryConfig.h"
#include "Repository.h"
#include "nlohmann/json.hpp"
#include <list>

class QuotesRepository {

public:
    QuotesRepository();

    void StoreQuotes(const std::list<Quote *> &quotes);

    void RestoreQuotes(const std::list<Quote *> &quotes);

private:

    char GetConfigFilePath() const;

    void InitProjectFolder();

    nlohmann::json_abi_v3_11_2::basic_json<> buildJsonArrayOfSymbols(const std::list<Quote *> &quotes) const;
};


#endif //STOCKS_QUOTESREPOSITORY_H
