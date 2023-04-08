//
// Created by Thorsten Claus on 09.03.23.
//

#include "NetRequester.h"
#include <algorithm>

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
NetRequester::Result(int resultId) {

    auto const httpResultIterator = fHttpResultContainer.find(resultId);
    if (httpResultIterator != fHttpResultContainer.end()) {
        printf("Requesting result of %d. Found it and returning it! \n", resultId);
        auto resultBody = new BString(httpResultIterator->second.Body().text.value());
        // Remove the hit
        //std::remove(fHttpResultContainer.begin(), fHttpResultContainer.end(), resultId);
        return resultBody;
    }

    return new BString("{}");
}
