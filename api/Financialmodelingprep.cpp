//
// Created by Thorsten Claus on 09.03.23.
//

#include <cstdio>

#include "Financialmodelingprep.h"
#include "private/netservices2/HttpRequest.h"
#include "private/netservices2/HttpSession.h"
#include "private/netservices2/HttpResult.h"
#include "Url.h"
#include "NetRequester.h"

const char *Financialmodelingprep::apiKey = "0e82c6b63df6e216f628f5c68a5e09a2";
const char *Financialmodelingprep::baseUrl = "https://financialmodelingprep.com/api/v3";

using BPrivate::Network::BHttpRequest;
using BPrivate::Network::BHttpSession;
using BPrivate::Network::BHttpResult;
using BPrivate::Network::BHttpBody;

Financialmodelingprep::Financialmodelingprep(BHandler *receivingHandler)
        :
        fHandler(receivingHandler) {
}

Financialmodelingprep::~Financialmodelingprep() {
    delete fHandler;
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

    AddApiKey(requestString);

    auto url = new BUrl(baseUrl);
    url->SetPath("/api/v3/search");
    url->SetRequest(requestString);

    printf("URL Request: %s \n", url->UrlString().String());

    auto request = BHttpRequest(*url);
    auto &requester = NetRequester::Instance();
    return requester.AddRequest(&request, fHandler);
}

void
Financialmodelingprep::AddApiKey(BString &request) {
    request.Append("&apikey=");
    request.Append(apiKey);
}
