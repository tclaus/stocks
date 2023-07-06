//
// Created by Thorsten Claus on 09.04.23.
//

#include <cstring>
#include "QuoteResultHandler.h"
#include "NetRequester.h"
#include "Portfolio.h"
#include "QuoteRequestStore.h"

using namespace std::string_view_literals;
using json = nlohmann::json;
using namespace nlohmann::literals;

void QuoteResultHandler::HandleQuoteResults(int requestId) {

    QuoteRequestStore &quoteRequestStore = QuoteRequestStore::Instance();
    if (quoteRequestStore.HasQuoteForRequestId(requestId)) {
        BString *resultJson = NetRequester::Instance().Result(requestId);
        Quote *quote = quoteRequestStore.RetrieveQuoteById(requestId);
        UpdateQuoteWithResponseData(quote, resultJson);
    }
}

void
QuoteResultHandler::UpdateQuoteWithResponseData(Quote *quote, BString *jsonString) {
    // See references here: https://site.financialmodelingprep.com/developer/docs/#Company-Quote

    if (quote == nullptr) {
        return;
    }

    json parsedJson = json::parse(jsonString->String());

    for (auto &item: parsedJson.items()) {
        auto innerJsonElement = item.value();
        if (!JsonElementMatchesQuote(innerJsonElement, quote)) {
            continue;
        }

        // Symbol not needed to transfer
        quote->companyName = new BString(innerJsonElement["name"].get<std::string>().c_str());
        quote->latestPrice = ValueFromJson("price", innerJsonElement);
        quote->changesPercentage = ValueFromJson("changesPercentage", innerJsonElement);
        quote->change = ValueFromJson("change", innerJsonElement);
        quote->dayLow = ValueFromJson("dayLow", innerJsonElement);
        quote->dayHigh = ValueFromJson("dayHigh", innerJsonElement);

        quote->yearHigh = ValueFromJson("yearHigh", innerJsonElement);
        quote->yearLow = ValueFromJson("yearLow", innerJsonElement);

        quote->open = ValueFromJson("open", innerJsonElement);
        quote->previousClose = ValueFromJson("previousClose", innerJsonElement);
        quote->volume = ValueFromJson("volume", innerJsonElement);
        quote->avgVolume = ValueFromJson("avgVolume", innerJsonElement);

        quote->pe = ValueFromJson("pe", innerJsonElement);
        quote->eps = ValueFromJson("eps", innerJsonElement);
        quote->marketCap = ValueFromJson("marketCap", innerJsonElement);
        quote->SetLastUpdatedTimePoint();
        quote->isWaitingForRequest = false;

        quote->Notify();
    }
}

float
QuoteResultHandler::ValueFromJson(std::string key, nlohmann::basic_json<> &jsonElement) {
    if (jsonElement.at(key) == nullptr) {
        return NAN;
    }
    return float(jsonElement.value(key, 0.0));
}

bool
QuoteResultHandler::JsonElementMatchesQuote(nlohmann::basic_json<> &jsonElement, Quote *quote) {

    if (jsonElement.at("symbol") == nullptr) {
        return false;
    }
    BString sentSymbol(jsonElement["symbol"].get<std::string>().c_str());
    return sentSymbol == *quote->symbol;

}

