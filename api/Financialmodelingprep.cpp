//
// Created by Thorsten Claus on 09.03.23.
//

#include "Financialmodelingprep.h"

#include "private/netservices2/HttpRequest.h"
#include "private/netservices2/HttpSession.h"
#include "private/netservices2/HttpResult.h"
#include "Url.h"
#include <cstdio>

const char *Financialmodelingprep::apiKey = "0e82c6b63df6e216f628f5c68a5e09a2";
const char *Financialmodelingprep::baseUrl = "https://financialmodelingprep.com/api/v3";

using BPrivate::Network::BHttpRequest;
using BPrivate::Network::BHttpSession;
using BPrivate::Network::BHttpResult;

Financialmodelingprep::Financialmodelingprep(BHandler *receivingHandler) {
    session = new BHttpSession();
    handler = receivingHandler;
}

Financialmodelingprep::~Financialmodelingprep() {
    delete session;
}

void Financialmodelingprep::Search(const char *searchQuery) {
    // search?query=appl&apikey=skjxxwm// search
/**
 * Search result:
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

    BUrl *url = new BUrl(baseUrl);
    url->SetPath("/api/v3/search");
    url->SetRequest(requestString);

    std::printf("URL Request: %s \n", url->UrlString().String());

    auto request = BHttpRequest(*url);
    // Creating and sharing a session
    printf("Is valíd: %d\n", BMessenger(handler).IsValid());

    BHttpResult result = session->Execute(std::move(request), nullptr, BMessenger(handler));
    std::printf("Result: %s", result.Body().text->String());
    delete url;
}

void
Financialmodelingprep::AddApiKey(BString &request) {
    request.Append("&apikey=");
    request.Append(apiKey);
}
