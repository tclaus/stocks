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
    Financialmodelingprep(BHandler *receivingHandler);

    ~Financialmodelingprep();

    void Search(const char *searchQuery) override;


private:
    void AddApiKey(BString &request);

private:
    static const char *baseUrl;
    static const char *apiKey;
    BHandler *fHandler;
};


#endif //STOCKS_FINANCIALMODELINGPREP_H
