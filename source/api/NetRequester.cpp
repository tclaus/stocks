//
// Created by Thorsten Claus on 09.03.23.
//

#include "NetRequester.h"
#include <algorithm>

using BPrivate::Network::BHttpStatusCode;

NetRequester
        NetRequester::instance = NetRequester();

NetRequester::NetRequester()
        : fHttpSession(new BHttpSession()),
          fHttpResultContainer() {}

NetRequester &
NetRequester::Instance() {
    return instance;
}

int
NetRequester::AddRequest(BHttpRequest *request, BHandler *handler) {
    BHttpResult expectingResult = fHttpSession->Execute(std::move(*request), nullptr, BMessenger(handler));
    int32 id = expectingResult.Identity();
    fHttpResultContainer.emplace(id, std::move(expectingResult));
    return id;
}

BString *
NetRequester::Result(int requestId) {

    auto const httpResultIterator = fHttpResultContainer.find(requestId);
    if (httpResultIterator != fHttpResultContainer.end()) {
        BHttpResult &result = httpResultIterator->second;

        if (result.Status().StatusCode() == BHttpStatusCode::Ok) {
            auto resultBody = new BString(httpResultIterator->second.Body().text.value());
            fHttpResultContainer.erase(requestId);
            return resultBody;
        }
    }

    return new BString("{}");
}
