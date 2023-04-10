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
        printf("Handle Quote Result with Id %d \n", requestId);
        BString *resultJson = NetRequester::Instance().Result(requestId);
        printf("Data from Request: %s\n", resultJson->String());
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
        printf("Updating existing quote with symbol %s.\n", quote->symbol->String());
        auto innerJsonElement = item.value();
        if (!JsonElementMatchesQuote(innerJsonElement, quote)) {
            continue;
        }

        // symbol not needed to transfer
        quote->companyName = new BString(innerJsonElement["name"].get<std::string>().c_str());
        quote->latestPrice = innerJsonElement["price"].get<float>();
        quote->changesPercentage = innerJsonElement["changesPercentage"].get<float>();
        quote->change = innerJsonElement["change"].get<float>();
        quote->dayLow = innerJsonElement["dayLow"].get<float>();
        quote->dayHigh = float(innerJsonElement.value("dayHigh", 0.0));
        quote->open = float(innerJsonElement.value("open", 0.0));
        quote->previousClose = float(innerJsonElement.value("previousClose", 0.0));
        quote->volume = float(innerJsonElement.value("volume", 0.0));
        quote->Notify();
    }
}

bool
QuoteResultHandler::JsonElementMatchesQuote(nlohmann::basic_json<> &jsonElement, Quote *quote) {

    if (jsonElement.at("symbol") == nullptr) {
        return false;
    }
    BString sentSymbol(jsonElement["symbol"].get<std::string>().c_str());
    return sentSymbol == *quote->symbol;

}

