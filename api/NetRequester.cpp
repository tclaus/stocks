//
// Created by Thorsten Claus on 09.03.23.
//

#include "NetRequester.h"

NetRequester NetRequester::instance = NetRequester();

NetRequester &NetRequester::Instance() {
    return instance;
}

void NetRequester::AddRequest(BHttpRequest *request, BHandler *handler) {
    fHttpResultContainer.push_back(
            fHttpSession->Execute(std::move(*request), nullptr, BMessenger(handler))
    );
}

NetRequester::NetRequester()
        : fHttpSession(new BHttpSession()),
          fHttpResultContainer() {}

BString *
NetRequester::Result() {
    auto &httpResult = fHttpResultContainer.back();
    fHttpResultContainer.pop_back();

    return new BString(httpResult.Body().text.value());
}
