//
// Created by Thorsten Claus on 08.04.23.
//

#ifndef STOCKS_REQUESTIDQUOTESTORE_H
#define STOCKS_REQUESTIDQUOTESTORE_H

#include "Quote.h"
#include <map>

/**
 * Links request ids to its corresponding Quotes.
 */
class BaseLinkedRequestToQuoteStore {

public:
    BaseLinkedRequestToQuoteStore();

    /**
     * Links a ongoing requestId together with its related quote.
     * @param requestId The Id of the current request
     * @param quote The quote which is handled by the request
     * @return
     */
    void AddQuoteRequestId(int requestId, Quote &quote);

    void RemoveQuoteByRequestId(int requestId);

    void RemoveQuote(Quote &quote);

    /**
     * Returns the quote by the request id if found.
     * @param requestId
     * @return Returns the quote corresponding to the request id, returns a null pointer if nothing was found.
     */
    Quote *RetrieveQuoteById(int requestId);

    bool HasQuoteForRequestId(int requestId);
    
private:
    std::map<int32, Quote *> *fRequestIdToQuoteMap;
};


#endif //STOCKS_REQUESTIDQUOTESTORE_H
