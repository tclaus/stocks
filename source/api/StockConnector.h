//
// Created by Thorsten Claus on 07.03.23.
//

#ifndef STOCKS_STOCKREQUESTS_H
#define STOCKS_STOCKREQUESTS_H

#include <HttpResult.h>

using BPrivate::Network::BHttpBody;

class StockConnector {

public:

    /**
     * Searches for a symbol or company name
     * @param searchQuery A symbol or part of a symbol.
     * @return The new request Id
     */
    virtual int Search(const char *searchQuery) = 0;

    /**
     * Requests the quote for a given symbol.
     * @param symbol A known symbol
     * @return The new request Id
     */
    virtual int RetrieveQuote(const char *symbol) = 0;

    // https://site.financialmodelingprep.com/developer/docs/#Stock-Historical-Price
    // virtual int RequestHistoricalPrice(const char* symbol);

    virtual ~StockConnector() = default;

    //
    // void RequestBatchData(vector<String> symbols); // Aktualisiere alle Aktien aus dem Portfolio
    // void RequestHistoricalPrices(char* symbol, period); // 1 day, 1 Woche, 1 Monat, 3 Monate, 6 Monate, 1,2,5 10 Jahre
    // void RequestCompanyProfile(char* symbol); //https://financialmodelingprep.com/image-stock/AAPL.png

};


#endif //STOCKS_STOCKREQUESTS_H
