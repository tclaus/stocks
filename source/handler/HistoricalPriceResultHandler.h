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

    /**
     * On a larger timescale the API wraps the inner array in something like
     * <pre>
     * {"symbol": "appl",
     * "historicData: [{a single datapoint}, {...}]}
     * </pre>
     * This method retrieves the inner array
     * @param parsedJson raw json from API
     * @return the array part with the datapoints ( [{data}, {data},...] )
     */
    nlohmann::basic_json<> &retrieveInnerArrayOnLargerTimeframes(nlohmann::basic_json<> &parsedJson) const;
};


#endif //STOCKS_HISTORICALPRICERESULTHANDLER_H
