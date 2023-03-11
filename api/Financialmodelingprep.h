//
// Created by Thorsten Claus on 09.03.23.
//

#ifndef STOCKS_FINANCIALMODELINGPREP_H
#define STOCKS_FINANCIALMODELINGPREP_H

#include "StockConnector.h"
#include "HttpFields.h"


using BPrivate::Network::BHttpFields;

class Financialmodelingprep : public StockConnector {
public:
    void Search(const char *searchQuery) override;

private:
    void AddApiKey(BHttpFields &fields);

private:
    static const char *baseUrl;
    static const char *apiKey;
};


#endif //STOCKS_FINANCIALMODELINGPREP_H
