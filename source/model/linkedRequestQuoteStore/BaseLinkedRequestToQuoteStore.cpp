//
// Created by Thorsten Claus on 08.04.23.
//

#include "BaseLinkedRequestToQuoteStore.h"


BaseLinkedRequestToQuoteStore::BaseLinkedRequestToQuoteStore()
        :
        fRequestIdToQuoteMap(new std::map<int32, Quote *>) {}

void
BaseLinkedRequestToQuoteStore::AddQuoteRequestId(int requestId, Quote &quote) {
    fRequestIdToQuoteMap->insert_or_assign(requestId, &quote);
}

void
BaseLinkedRequestToQuoteStore::RemoveQuoteByRequestId(int requestId) {
    (void) requestId;
    fRequestIdToQuoteMap->erase(requestId);
}

void
BaseLinkedRequestToQuoteStore::RemoveQuote(Quote &quote) {
    (void) quote;
    // If needed: Go to list of values and remove if found
}

bool
BaseLinkedRequestToQuoteStore::HasQuoteForRequestId(int requestId) {
    auto const &iterator = fRequestIdToQuoteMap->find(requestId);
    return !(iterator == fRequestIdToQuoteMap->end());
}

Quote *
BaseLinkedRequestToQuoteStore::RetrieveQuoteById(int requestId) {
    auto const &iterator = fRequestIdToQuoteMap->find(requestId);
    if (iterator == fRequestIdToQuoteMap->end()) {
        return nullptr;
    }
    return iterator->second;
}
