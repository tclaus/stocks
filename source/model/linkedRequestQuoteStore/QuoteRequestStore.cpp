//
// Created by Thorsten Claus on 08.04.23.
//

#include "QuoteRequestStore.h"


QuoteRequestStore QuoteRequestStore::fInstance = QuoteRequestStore();

QuoteRequestStore::QuoteRequestStore()
        :
        BaseLinkedRequestToQuoteStore() {}

QuoteRequestStore &
QuoteRequestStore::Instance() {
    return fInstance;
}
