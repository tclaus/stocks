//
// Created by Thorsten Claus on 09.03.23.
//

#include "NetRequester.h"
#include <iostream>

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
    int id = expectingResult.Identity();
    fHttpResultContainer.push_back(
            std::move(expectingResult)
    );
    return id;
}

BString *
NetRequester::Result(int resultId) {
    (void) resultId;
    // TODO: Returns a request by its Id, not just the latest!
    auto &httpResult = fHttpResultContainer.back();
    auto resultBody = new BString(httpResult.Body().text.value());
    fHttpResultContainer.pop_back();

    return resultBody;
}
