//
// Created by Thorsten Claus on 12.03.23.
//

#ifndef STOCKS_URLBUILDER_H
#define STOCKS_URLBUILDER_H

#include "Url.h"

class UrlBuilder {
public:
    UrlBuilder();

    UrlBuilder(BUrl &url);

    UrlBuilder &
    AddQuery(const BString &key, const BString &value);

private:
    BUrl *url;
};


#endif //STOCKS_URLBUILDER_H
