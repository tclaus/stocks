//
// Created by Thorsten Claus on 08.04.23.
//

#ifndef STOCKS_QUOTEREQUESTSTORE_H
#define STOCKS_QUOTEREQUESTSTORE_H

# include "BaseLinkedRequestToQuoteStore.h"

class QuoteRequestStore : public BaseLinkedRequestToQuoteStore {

public:
    QuoteRequestStore(const QuoteRequestStore &) = delete;

    static QuoteRequestStore &Instance();

private:
    QuoteRequestStore();

private:
    static QuoteRequestStore fInstance;
};


#endif //STOCKS_QUOTEREQUESTSTORE_H
