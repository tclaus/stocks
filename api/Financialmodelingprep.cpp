//
// Created by Thorsten Claus on 09.03.23.
//

#include "Financialmodelingprep.h"

#include "private/netservices2/HttpRequest.h"
#include "private/netservices2/HttpSession.h"
#include "private/netservices2/HttpResult.h"
#include "Url.h"
#include <iostream>

const char *Financialmodelingprep::apiKey = "0e82c6b63df6e216f628f5c68a5e09a2";
const char *Financialmodelingprep::baseUrl = "https://financialmodelingprep.com/api/v3";

using BPrivate::Network::BHttpRequest;
using BPrivate::Network::BHttpSession;
using BPrivate::Network::BHttpResult;

void Financialmodelingprep::Search(const char *searchQuery) {
    // ?query=appl&apikey=skjxxwm// search

    // Add Search path and Query -query
    auto *urlWithPath = new BString(baseUrl);

    BHttpFields fields = BHttpFields();
    urlWithPath->Append("/search?");

    fields.AddField("query", searchQuery);
    AddApiKey(fields);

    BUrl *url = new BUrl(baseUrl);
    auto request = BHttpRequest(*url);
    request.SetFields(fields);

    // Creating and sharing a session
    auto session = BHttpSession();
    BHttpResult result = session.Execute(std::move(request));
    std::printf("%s", result.Body().text->String());
}

void
Financialmodelingprep::AddApiKey(BHttpFields &fields) {
    fields.AddField("apiKey", apiKey);
}
