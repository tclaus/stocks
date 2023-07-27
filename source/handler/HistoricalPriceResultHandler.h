//
// Created by Thorsten Claus on 19.07.23.
//

#ifndef STOCKS_HISTORICALPRICERESULTHANDLER_H
#define STOCKS_HISTORICALPRICERESULTHANDLER_H

#include "nlohmann/json.hpp"
#include "HistoricalPriceList.h"

class HistoricalPriceResultHandler {

public:
    HistoricalPriceResultHandler();

/**
 * Generates a historical data object from the request id
 * @param requestId
 */
    HistoricalPriceList *GenerateHistoricalDataObject(int requestId);

private:
    HistoricalPriceList *ConvertJsonToHistoricalData(BString *jsonString);

    /**
     * Converts a json json key safely to a float value. If the key does not exists, a NAN is returned.
     * @param key
     * @param jsonElement
     * @return
     */
    float FloatValueFromJson(std::string const &key, nlohmann::basic_json<> &jsonElement);
};


#endif //STOCKS_HISTORICALPRICERESULTHANDLER_H
