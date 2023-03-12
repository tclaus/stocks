//
// Created by Thorsten Claus on 09.03.23.
//

#ifndef STOCKS_FINANCIALMODELINGPREP_H
#define STOCKS_FINANCIALMODELINGPREP_H

#include "StockConnector.h"
#include "HttpFields.h"
#include "HttpSession.h"

using BPrivate::Network::BHttpFields;
using BPrivate::Network::BHttpSession;

class Financialmodelingprep : public StockConnector {
public:
    Financialmodelingprep();

    ~Financialmodelingprep();

    void Search(const char *searchQuery) override;

private:
    void AddApiKey(BString &request);

private:
    static const char *baseUrl;
    static const char *apiKey;
    BHttpSession *session;
};


#endif //STOCKS_FINANCIALMODELINGPREP_H
