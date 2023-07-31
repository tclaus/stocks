//
// Created by Thorsten Claus on 07.03.23.
//

#ifndef STOCKS_STOCKREQUESTS_H
#define STOCKS_STOCKREQUESTS_H

#include <HttpResult.h>
#include "TimeRange.h"

using BPrivate::Network::BHttpBody;

class StockConnector {

public:

    /**
     * Searches for a symbol or company name
     * @param searchQuery a symbol or part of a symbol.
     * @return the new request Id
     */
    virtual int Search(const char *searchQuery) = 0;

    /**
     * Requests the quote details from API for a given symbol.
     * @param symbol a known symbol
     * @return the new request Id
     */
    virtual int RetrieveQuote(const char *symbol) = 0;

    /**
     * Requests historical data for a given quote and a time range.
     * The algorithm requests the data from now an to the past. One Day means this day, 1 Year means
     * from now on one year in the past.
     * @param symbol the stocks symbol identifier
     * @param timeRange the time range specifier
     * @return the new request Id
     */
    virtual int RetrieveHistoricData(const char *symbol, TimeRange timeRange) = 0;

    virtual ~StockConnector() = default;

    //
    // void RequestBatchData(vector<String> symbols); // Aktualisiere alle Aktien aus dem Portfolio
    // void RequestHistoricalPrices(char* symbol, period); // 1 day, 1 Woche, 1 Monat, 3 Monate, 6 Monate, 1,2,5 10 Jahre
    // void RequestCompanyProfile(char* symbol); //https://financialmodelingprep.com/image-stock/AAPL.png

};


#endif //STOCKS_STOCKREQUESTS_H
