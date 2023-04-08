//
// Created by Thorsten Claus on 09.03.23.
//

#include <cstdio>

#include "Financialmodelingprep.h"
#include "private/netservices2/HttpRequest.h"
#include "private/netservices2/HttpSession.h"
#include "private/netservices2/HttpResult.h"
#include "private/netservices/HttpForm.h"

#include "Url.h"
#include "NetRequester.h"

const char *Financialmodelingprep::apiKey = "0e82c6b63df6e216f628f5c68a5e09a2";
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
    // search?query=appl&apikey=skjxxwm// search
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
Financialmodelingprep::Quote(const char *symbol) {
    // See https://site.financialmodelingprep.com/developer/docs/stock-api/ for details

    BString requestString = BString();
    requestString.Append("/api/v3/quote/");
    requestString.Append(symbol);
    requestString.Append("?");
    AddApiKey(requestString);

    auto url = new BUrl(baseUrl);
    url->SetPath(requestString);
    printf("Quote Request: %s \n", url->UrlString().String());
    return SendRequest(url);
}

void
Financialmodelingprep::AddApiKey(BString &request) {
    request.Append("apikey=");
    request.Append(apiKey);
}

void
Financialmodelingprep::AddLimit(BString &request) {
    request.Append("limit=50");
}

// Ctest oder GTest?
int Financialmodelingprep::SendRequest(const BUrl *url) const {
    auto request = BHttpRequest(*url);
    auto &requester = NetRequester::Instance();
    return requester.AddRequest(&request, fHandler);
}
