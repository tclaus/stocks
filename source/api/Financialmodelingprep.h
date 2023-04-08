//
// Created by Thorsten Claus on 09.03.23.
//

#ifndef STOCKS_FINANCIALMODELINGPREP_H
#define STOCKS_FINANCIALMODELINGPREP_H

#include <Handler.h>
#include <HttpResult.h>
#include "StockConnector.h"
#include "HttpFields.h"
#include "HttpSession.h"

using BPrivate::Network::BHttpFields;
using BPrivate::Network::BHttpSession;
using BPrivate::Network::BHttpResult;
using BPrivate::Network::BHttpBody;

class Financialmodelingprep : public StockConnector {
public:
    explicit Financialmodelingprep(BHandler *receivingHandler);

    /**
     * Searches a symbol and finds basic data such as company name, market, currency.
     * For a more detailed overview call the profile endpoint.
     * @param searchQuery
     * @return The request id
     */
    int
    Search(const char *searchQuery) override;

    /**
     * Requests details for a given symbol. Result is a array.
     * See https://site.financialmodelingprep.com/developer/docs/stock-api/ for details.
     */
    int
    Quote(const char *symbol) override;

private:
    void AddApiKey(BString &request);

    void AddLimit(BString &request);

private:
    static const char *baseUrl;
    static const char *apiKey;
    BHandler *fHandler;

    int SendRequest(const BUrl *url) const;
};


#endif //STOCKS_FINANCIALMODELINGPREP_H
