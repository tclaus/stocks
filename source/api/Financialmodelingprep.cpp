//
// Created by Thorsten Claus on 09.03.23.
//



#include "Financialmodelingprep.h"
#include "FinancialmodelingApiKey.h"

#include "private/netservices2/HttpRequest.h"
#include "private/netservices2/HttpSession.h"
#include "private/netservices2/HttpResult.h"
#include "private/netservices/HttpForm.h"

#include "Url.h"
#include "NetRequester.h"

const char *Financialmodelingprep::baseUrl = "https://financialmodelingprep.com/api/v3";

using BPrivate::Network::BHttpRequest;
using BPrivate::Network::BHttpSession;
using BPrivate::Network::BHttpResult;
using BPrivate::Network::BHttpBody;
using BPrivate::Network::BHttpForm;

Financialmodelingprep::Financialmodelingprep(BHandler *receivingHandler)
        :
        fHandler(receivingHandler) {
}

int
Financialmodelingprep::Search(const char *searchQuery) {
    // search?query=appl&apikey=THE_KEY
/**
 * Search fResult:
    {
        "symbol": "APC.F",
                "name": "Apple Inc.",
                "currency": "EUR",
                "stockExchange": "Frankfurt",
                "exchangeShortName": "XETRA"
    }
    **/
    BString requestString = BString();
    requestString.Append("query=");
    requestString.Append(searchQuery);

    requestString.Append("&");
    AddApiKey(requestString);
    requestString.Append("&");
    AddLimit(requestString);

    auto url = new BUrl(baseUrl);
    url->SetPath("/api/v3/search");
    url->SetRequest(requestString);

    printf("Search Request: %s \n", url->UrlString().String());

    return SendRequest(url);
}

int
Financialmodelingprep::RetrieveQuote(const char *symbol) {
    // See https://site.financialmodelingprep.com/developer/docs/stock-api/ for details

    BString requestString = BString();
    requestString.Append("/api/v3/quote/");
    requestString.Append(symbol);
    requestString.Append("?");
    AddApiKey(requestString);

    auto url = new BUrl(baseUrl);
    url->SetPath(requestString);
    printf("RetrieveQuote Request: %s \n", symbol);
    return SendRequest(url);
}

int
Financialmodelingprep::RetrieveHistoricData(const char *symbol, TimeRange timeRange) {
    // https://site.financialmodelingprep.com/developer/docs/#Stock-Historical-Price

    BString requestString = BString();
    requestString.Append("/api/v3/");
    requestString.Append(DeterminePathForHistoricalData(timeRange));
    requestString.Append(symbol);
    requestString.Append("?");
    AddApiKey(requestString);

    auto url = new BUrl(baseUrl);
    url->SetPath(requestString);
    printf("Retrieve historic data Request: %s \n", symbol);
    return SendRequest(url);
}

const char *
Financialmodelingprep::DeterminePathForHistoricalData(TimeRange timeRange) {
    switch (timeRange) {
        case M_DAY:
            return "historical-chart/1min/";
        case M_WEEK:
            return "historical-chart/5min/";
        case M_MONTH:
        case M_THREE_MONTH:
            return "historical-chart/1hour/";
        case M_SIX_MONTH:
        case M_YEAR:
        case M_TWO_YEARS:
        case M_FIVE_YEARS:
        default:
            return "historical-price-full/";
    }
}

void
Financialmodelingprep::AddApiKey(BString &request) {
    request.Append("apikey=");

    request.Append(
            FinancialmodelingApiKey::GetApiKey().c_str()
    );
}

void
Financialmodelingprep::AddLimit(BString &request) {
    request.Append("limit=50");
}

int Financialmodelingprep::SendRequest(const BUrl *url) const {
    auto request = BHttpRequest(*url);
    auto &requester = NetRequester::Instance();
    return requester.AddRequest(&request, fHandler);
}
