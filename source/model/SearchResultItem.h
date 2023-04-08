//
// Created by Thorsten Claus on 19.03.23.
//

#ifndef STOCKS_SEARCHRESULTITEM_H
#define STOCKS_SEARCHRESULTITEM_H

#include <String.h>

class SearchResultItem {
public:
    BString *symbol;
    BString *name;
    BString *currency;
    BString *stockExchange;

    [[maybe_unused]]
    BString *
    DisplayText() const;
};


#endif //STOCKS_SEARCHRESULTITEM_H
