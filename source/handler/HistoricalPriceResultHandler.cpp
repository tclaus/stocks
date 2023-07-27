//
// Created by Thorsten Claus on 19.07.23.
//

#include "HistoricalPriceResultHandler.h"

#include "NetRequester.h"

using namespace std::string_view_literals;
using json = nlohmann::json;
using namespace nlohmann::literals;

HistoricalPriceResultHandler::HistoricalPriceResultHandler() = default;

HistoricalPriceList *
HistoricalPriceResultHandler::GenerateHistoricalDataObject(int requestId) {
    BString *resultJson = NetRequester::Instance().Result(requestId);
    return ConvertJsonToHistoricalData(resultJson);
}

HistoricalPriceList *
HistoricalPriceResultHandler::ConvertJsonToHistoricalData(BString *jsonString) {
    json parsedJson = json::parse(jsonString->String());

    auto *historicalPriceList = new HistoricalPriceList();
    for (auto &item: parsedJson.items()) {
        auto innerJsonElement = item.value();
        auto *historicalPrice = new HistoricalPrice();
        historicalPrice->SetDate(new BString(innerJsonElement["date"].get<std::string>().c_str()));
        historicalPrice->SetOpen(FloatValueFromJson("open", innerJsonElement));
        historicalPrice->SetLow(FloatValueFromJson("low", innerJsonElement));
        historicalPrice->SetHigh(FloatValueFromJson("high", innerJsonElement));
        historicalPrice->SetClose(FloatValueFromJson("close", innerJsonElement));
        historicalPriceList->List()->push_back(historicalPrice);
    }
    return historicalPriceList;
}

float
HistoricalPriceResultHandler::FloatValueFromJson(std::string const &key, nlohmann::basic_json<> &jsonElement) {
    if (jsonElement.at(key) == nullptr) {
        return NAN;
    }
    return float(jsonElement.value(key, 0.0));
}

