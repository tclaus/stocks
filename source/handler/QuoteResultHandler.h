//
// Created by Thorsten Claus on 09.04.23.
//

#ifndef STOCKS_QUOTERESULTHANDLER_H
#define STOCKS_QUOTERESULTHANDLER_H

#include "Quote.h"
#include "nlohmann/json.hpp"

/**
 * Handles results from requesting quote details from Api.
 * Updates the Quotes stored in the Portfolio.
 */
class QuoteResultHandler {
public:
    void HandleQuoteResults(int requestId);

private:
    void UpdateQuoteWithResponseData(Quote *quote, BString *jsonString);

    bool JsonElementMatchesQuote(nlohmann::basic_json<> &jsonElement, Quote *quote);
};


#endif //STOCKS_QUOTERESULTHANDLER_H
